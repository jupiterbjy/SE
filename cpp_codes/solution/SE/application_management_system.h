#pragma once

#include <iostream>
#include <string>
#include "entities.h"

using namespace std;


//Control Class
//회사 즉시 지원
class NowApplication {
private:
    EmploymentCollection* employment_collection;
    ApplicationCollection* application_collection;

public:
    NowApplication(ApplicationCollection* application_collection, EmploymentCollection* employment_collection)
    {
        this->application_collection = application_collection;
        this->employment_collection = employment_collection;
    }

    Application* add_new_application(string const& logged_in_user_id, string const& business_num) const
    {
        // get applied employment by business_num
        Employment* employment = employment_collection->get_employment_by_business_num(business_num);

        // apply & return new obj ref
        return application_collection->add_application(employment, logged_in_user_id);
    }
};


//Boundary Class
//회사 즉시 지원 UI
class NowApplicationUi {// 사업자번호 -> 회사이름, 사업자번호, 업무
private:
    NowApplication control;

public:
    NowApplicationUi(ApplicationCollection* application_collection, EmploymentCollection* employment_collection) : control(application_collection, employment_collection) {};

    void start_interface(string const& logged_in_user_id, ifstream& in_fp, ofstream& out_fp) const
    {
        // get input
    	string business_num;
        in_fp >> business_num;

        // Echo back command & run action, then output again
        out_fp << "4.2. 채용 지원" << endl;
        auto application = control.add_new_application(logged_in_user_id, business_num);
        out_fp << "> "<< application->get_company_name() << " " << application->get_business_number() << " " << application->get_work_type() << endl;
    }
};


//Controll Class
//지원 정보 조회 클래스
//일반 유저가 지원한 회사 전부를 보여줌
class ApplicationCheckUi;
class ApplicationCheck {
private:
    ApplicationCollection* collection;
    ApplicationCheckUi* ui;

public:
    ApplicationCheck(ApplicationCollection* collection, ApplicationCheckUi* ui)
    {
        this->collection = collection;
        this->ui = ui;
    }

    void show_applications_info(string const& logged_in_user_id);
};


//Boundary Class
//지원 정보 조회 UI 클래스
class ApplicationCheckUi { // { user_id -> 회사이름, 사업자번호, 업무, 인원 수, 신청마감일 }*
private:
    ApplicationCheck* control;
    ofstream* out_stream;

public:
    ApplicationCheckUi(ApplicationCollection* collection)
    {
        out_stream = nullptr;
        this->control = new ApplicationCheck(collection, this);
    }

    //void startInterface(User* loginUser) {
    void start_interface(string const& logged_in_user_id, ofstream& out_fp)
	{
        out_fp << "4.3. 지원 정보 조회" << endl;
        control->show_applications_info(logged_in_user_id);
    }

    void write_application(string const& company_name, string const& business_num, string const& work_type, int const max_applicants, string const& dead_line) const
    {
        *(out_stream) << "> " << company_name << " " << business_num << " " << work_type << " " << max_applicants << " " << dead_line << endl;
    }
};


inline void ApplicationCheck::show_applications_info(string const& logged_in_user_id)
{
	for (int idx=0; idx < collection->total_applications_count(); idx++)
	{
        auto application = collection->get_employment_by_index(idx);

        // if same id, write it out
        if (application->get_user_id() == logged_in_user_id)
            ui->write_application(application->get_company_name(), application->get_business_number(), application->get_work_type(), application->get_max_applicants(), application->get_dead_line());
	}
}



//Control Class
//지원 취소 클래스
class CancelApplication {
private:
    ApplicationCollection* collection;

public:
    CancelApplication(ApplicationCollection* collection) {
        this->collection = collection;
    }

    Application* cancel_application(string const& logged_in_user_id, string const& business_num) const
    {
        return collection->remove_application(logged_in_user_id, business_num);
    }
};


//Boundary Class
//지원 취소 UI 클래스
class CancelApplicationUi { // 사업자번호 -> 회사이름, 사업자번호, 업무
private:
    CancelApplication control;

public:
    CancelApplicationUi(ApplicationCollection* collection) : control(collection) {}

    void start_interface(string const& logged_in_user_id, ifstream& in_fp, ofstream& out_fp) const
    {
        string business_num;
        in_fp >> business_num;

        out_fp << "4.4. 지원 취소" << endl;
        Application* application = control.cancel_application(logged_in_user_id, business_num);
        cout << "> "
            << application->get_company_name() << " "
            << application->get_business_number() << " "
            << application->get_work_type() << endl;
    }
};
