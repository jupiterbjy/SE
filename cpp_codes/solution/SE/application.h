#pragma once

#include <iostream>
#include <string>
#include "entities.h"

#define RETURN_OK 0
#define RETURN_ERROR -1

using namespace std;


//Controll Class
//회사 즉시 지원
class NowApplication {
private:
    Application* application;

public:
    NowApplication(Application* app) : application(app) {}
    Application* application()
    {
        Employment* emp = EmploymentCollection::getEmploymentByBussinessNum(application->get_business_number());  //지원했던 회사 가져오기
        ApplicationCollection* aCollection = emp->getApplicationCollection();  //해당 회사의 지원서 뭉치 가져오기
        aCollection->add_application(application);  //지원서 삭제
        return application;
    }

    Application* getApplication() { return application; }
};

//Boundary Class
//회사 즉시 지원 UI
class NowApplicationUI {// 사업자번호 -> 회사이름, 사업자번호, 업무
private:
    NowApplication control;

public:
    NowApplicationUI(NowApplication application) : control(application) {};

    void startInterface(User* loginUser) {
        cout << "4.2. 채용 지원" << endl;
        Application* app = control.application();
        cout << "> "
            << app->get_company_name() << " "
            << app->get_business_number() << " "
            << app->get_work_type() << endl;
    }
};

//Controll Class
//지원 정보 조회 클래스
//일반 유저가 지원한 회사 전부를 보여줌

class ApplicationCheck {
private:
    Application* applications[11];
    User* user;
    int max_applications = 0;

public:
    ApplicationCheck(User* user) : user(user) {
    }

    Application** getApplications()
    {
        Application* tmp;
        for (Employment* emp : EmploymentCollection::employmentList)
        {
            tmp = emp->getApplicationCollection()->get_application_by_user_id(user->get_id());
            if (tmp != nullptr) applications[max_applications++] = tmp;
            if (max_applications >= 11) break;
        }
        applications[max_applications] = nullptr;

        return applications;
    }
    /* 어디서 사용?
    static Employment* getEmployments(User* loginUser) {
        CompanyUser* companyUser = manager.get_company_user(loginUser->get_id());
        string businessNum = companyUser->get_business_num();
        string companyName = companyUser->get_company_name();
        string workType = employment.get_work_type();
        int applicantNum = employment.get_applicantNum();
        int employmentDeadline = employment.get_deadline();
    }
    */
};

//Boundary Class
//지원 정보 조회 UI 클래스
class ApplicationCheckUI { // { user_id -> 회사이름, 사업자번호, 업무, 인원 수, 신청마감일 }*
private:
    ApplicationCheck* control;

public:
    ApplicationCheckUI(User* user) {
        control = new ApplicationCheck(user);
    };

    //void startInterface(User* loginUser) {
    void startInterface() {
        cout << "4.3. 지원 정보 조회" << endl;
        Application** applications = control->getApplications();
        for (Application* app = *applications; app != nullptr; ++app)
            cout << "> "
            << app->get_company_name() << " "
            << app->get_business_number() << " "
            << app->get_work_type() << " "
            << app->get_people_number() << " "
            << app->get_dead_line() << endl;
    }
};

//Controll Class
//지원 취소 클래스
class CancelApplication {
private:
    User* user;

public:
    //회사이름 오름차순 정렬 필요
    CancelApplication(User* user) : user(user) {
    }

    Application* getApplication(string businessNum)
    {
        Application* tmp;
        Employment* emp = EmploymentCollection::getEmploymentByBussinessNum(businessNum);  //지원했던 회사 가져오기
        ApplicationCollection* aCollection = emp->getApplicationCollection();  //해당 회사의 지원서 뭉치 가져오기
        tmp = aCollection->get_application_by_user_id(user->get_id());  //지울 지원서 가져오기
        aCollection->cancel_application(aCollection->get_index_by_user_id(user->get_id()));  //지원서 삭제

        return tmp;
    }
};

//Boundary Class
//지원 취소 UI 클래스
class CancelApplicationUI { // 사업자번호 -> 회사이름, 사업자번호, 업무
private:
    CancelApplication* control;

public:
    CancelApplicationUI(User* user) {
        control = new CancelApplication(user);
    }

    void startInterface(string businessNum) {
        cout << "4.4. 지원 취소" << endl;
        Application* application = control->getApplication(businessNum);
        cout << "> "
            << application->get_company_name() << " "
            << application->get_business_number() << " "
            << application->get_work_type() << endl;
    }
};
