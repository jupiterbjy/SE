#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include "entities.h"

using namespace std;


//채용 정보 등록(3.1)
//[업무] [인원 수] [신청 마감일]
// Control
class EmploymentAddUI;
class EmploymentAdd {
private:
    EmploymentCollection* collection;
public:
    EmploymentAdd(EmploymentCollection* collection)
    {
        this->collection = collection;
    }

    void addEmployment(string const& company_name, string const& work_type, int max_applicants, string const& deadline);
};


// Boundary
class EmploymentAddUI{
private:
    EmploymentAdd control;
public:
    EmploymentAddUI(EmploymentCollection* collection) : control(collection) {}

    void start_interface(string const& user_id, ifstream& in_fp, ofstream& out_fp)
	{
        string work_type, deadline;
        int max_applicants;

        in_fp >> work_type >> max_applicants >> deadline;

        out_fp << "3.1. 채용 정보 등록" << endl;
        control.addEmployment(user_id, work_type, max_applicants, deadline);
        out_fp << "> " << work_type << " " << max_applicants << " " << deadline << endl;
    }
};


inline void EmploymentAdd::addEmployment(string const& company_name, string const& work_type, int max_applicants, string const& deadline)
{
    collection->addEmployment(company_name, work_type, max_applicants, deadline);
}



//등록된 채용 정보 리스트 조회 (3.2)
//[회사이름] [사업자번호] [업무] [인원 수] [신청마감일]
// Control class
class ShowEmploymentListUI;
class ShowEmploymentList {
private:
    EmploymentCollection* collection;
    ShowEmploymentListUI* ui;
public:
    ShowEmploymentList(EmploymentCollection* collection, ShowEmploymentListUI* ui)
    {
        this->collection = collection;
        this->ui = ui;
    }

    void showEmploymentInfo(string const& logged_in_user_id);
};


// Boundary class
class ShowEmploymentListUI{
private:
    ShowEmploymentList* control;
    ofstream* out_stream;
public:
    ShowEmploymentListUI()
    {
	    
    }

    void start_interface(string const &logged_in_user_id, ofstream& out_fp)
	{
        out_fp << "3.2. 등록된 채용 정보 조회" << endl;
        control->showEmploymentInfo(logged_in_user_id);
    }

    void write_employment(string const& work_type, int total_applicants, string const& dead_line) const
    {
        *(out_stream) << "> " << work_type << total_applicants << dead_line << endl;
    }
};


inline void ShowEmploymentList::showEmploymentInfo(string const& logged_in_user_id)
{
    // TODO: missing collection get total count method
    for (int idx=0; idx < collection->numEmployments; idx++)
    {
        auto employment = collection->getEmployment(idx);

        // if same user id, write it out
        if (employment->getCompanyName() == logged_in_user_id)
            ui->write_employment(employment->getWork(), employment->getPeopleNumber(), employment->getDeadline());
    }
}



// 4.1.
// Control class
class CompanyNameSearchUI;
class CompanyNameSearch
{
private:
    EmploymentCollection* collection;
    CompanyNameSearchUI* ui;

public:
    CompanyNameSearch(EmploymentCollection *collection, CompanyNameSearchUI* ui)
    {
        this->collection = collection;
        this->ui = ui;
    }

    void searchCompanyName(string const& company_name);
};


// Boundary class
class CompanyNameSearchUI{
private:
    CompanyNameSearch* control;
    string company_names[100];
    ofstream* out_stream;
public:
    CompanyNameSearchUI(EmploymentCollection *collection)
    {
        out_stream = nullptr;
        control = new CompanyNameSearch(collection, this);
    }

    void start_interface(ifstream& in_fp, ofstream& out_fp)
    {
        // cache out_fp so we can write in writeCompanyOutput
        this->out_stream = &out_fp;

        string company_name;
        in_fp >> company_name;

        out_fp << "4.1. 채용 정보 검색" << endl;
        this->control->searchCompanyName(company_name);
    }

    void write_employment(string const &company_name, string const &business_num, string const &work_type, int total_applicants, string const &dead_line) const
    {
        *(out_stream) << "> " << company_name << business_num << work_type << total_applicants << dead_line << endl;
    }
};


inline void CompanyNameSearch::searchCompanyName(string const& company_name)
{
    // iterate and find target company name
    // TODO: missing collection get total count method
    for (int idx = 0; idx < collection->numEmployments; idx++)
    {
        auto employment = collection->getEmployment(idx);

        // if matches, print it out
        if (employment->getCompanyName() == company_name)
            ui->write_employment(employment->getCompanyName(), employment.getBusinessNum(), employment.getWorkType(), employment->getPeopleNumber(), employment->getDeadline());
    }
}
