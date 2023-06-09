#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include "entities.h"

using namespace std;


//채용 정보 등록(3.1)
//[업무] [인원 수] [신청 마감일]
// Control
class EmploymentAddUi;

class EmploymentAdd
{
private:
	EmploymentCollection* collection;
	UserManager* manager;

public:
	EmploymentAdd(EmploymentCollection* collection, UserManager* manager)
	{
		this->collection = collection;
		this->manager = manager;
	}

	void add_employment(string const& user_id, string const& work_type, const int max_applicants, string const& deadline) const;
};


// Boundary
class EmploymentAddUi
{
private:
	EmploymentAdd control;


public:
	EmploymentAddUi(EmploymentCollection* collection, UserManager* manager) : control(collection, manager) {};

	void start_interface(string const& user_id, ifstream& in_fp, ofstream& out_fp) const
	{
		string work_type, deadline;
		int max_applicants;

		in_fp >> work_type >> max_applicants >> deadline;

		out_fp << "3.1. 채용 정보 등록" << endl;
		control.add_employment(user_id, work_type, max_applicants, deadline);
		out_fp << "> " << work_type << " " << max_applicants << " " << deadline << endl;
	}
};


inline void EmploymentAdd::add_employment(string const& user_id, string const& work_type, const int max_applicants, string const& deadline) const
{
	// get user from user_id
	const auto user = reinterpret_cast<CompanyUser*>(manager->get_company_user(user_id));

	collection->add_employment(user->get_company_name(), work_type, max_applicants, user->get_business_num(), deadline);
}


//등록된 채용 정보 리스트 조회 (3.2)
//[회사이름] [사업자번호] [업무] [인원 수] [신청마감일]
// Control class
class ShowEmploymentListUi;

class ShowEmploymentList
{
private:
	EmploymentCollection* collection;
	ShowEmploymentListUi* ui;
	UserManager* manager;

public:
	ShowEmploymentList(EmploymentCollection* collection, UserManager* manager, ShowEmploymentListUi* ui)
	{
		this->collection = collection;
		this->manager = manager;
		this->ui = ui;
	}

	void show_employment_info(string const& logged_in_user_id) const;
};


// Boundary class
class ShowEmploymentListUi
{
private:
	ShowEmploymentList* control;
	ofstream* out_stream;

public:
	ShowEmploymentListUi(EmploymentCollection* collection, UserManager* manager)
	{
		out_stream = nullptr;
		this->control = new ShowEmploymentList(collection, manager, this);
	}

	void start_interface(string const& logged_in_user_id, ofstream& out_fp)
	{
		out_stream = &out_fp;

		out_fp << "3.2. 등록된 채용 정보 조회" << endl;
		control->show_employment_info(logged_in_user_id);
	}

	void write_employment(string const& work_type, const int total_applicants, string const& dead_line) const
	{
		*(out_stream) << "> " << work_type << " " << total_applicants << " " << dead_line << endl;
	}
};


inline void ShowEmploymentList::show_employment_info(string const& logged_in_user_id) const
{
	for (int idx = 0; idx < collection->get_total_employment_count(); idx++)
	{
		// get user
		const auto user = reinterpret_cast<CompanyUser*>(manager->get_company_user(logged_in_user_id));

		// get employment
		const auto employment = collection->get_employment(idx);

		// if same business_num, write it out
		if (employment->get_company_name() == user->get_company_name())
			ui->write_employment(employment->get_work(), employment->get_max_applicants(), employment->get_deadline());
	}
}


// 4.1.
// Control class
class CompanyNameSearchUi;

class CompanyNameSearch
{
private:
	EmploymentCollection* collection;
	CompanyNameSearchUi* ui;

public:
	CompanyNameSearch(EmploymentCollection* collection, CompanyNameSearchUi* ui)
	{
		this->collection = collection;
		this->ui = ui;
	}

	void search_company_name(string const& company_name) const;
};


// Boundary class
class CompanyNameSearchUi
{
private:
	CompanyNameSearch* control;
	string company_names[100];
	ofstream* out_stream;

public:
	CompanyNameSearchUi(EmploymentCollection* collection)
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
		this->control->search_company_name(company_name);
	}

	void write_employment(string const& company_name, string const& business_num, string const& work_type,
						  int total_applicants, string const& dead_line) const
	{
		*(out_stream) << "> " << company_name << " " << business_num << " " << work_type << " " << total_applicants << " " << dead_line << endl;
	}
};


inline void CompanyNameSearch::search_company_name(string const& company_name) const
{
	// iterate and find target company name
	for (int idx = 0; idx < collection->get_total_employment_count(); idx++)
	{
		const auto employment = collection->get_employment(idx);

		// if matches, print it out
		if (employment->get_company_name() == company_name)
			ui->write_employment(employment->get_company_name(), employment->get_business_number(), employment->get_work(),
								 employment->get_max_applicants(), employment->get_deadline());
	}
}
