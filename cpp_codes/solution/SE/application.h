#pragma once

#include <iostream>
#include <string>
#include "entities.h"


//Controll Class
class NowApplication { // 사업자번호 -> 회사이름, 사업자번호, 업무
private:
    ApplicationCollection collection;
    
public:
    collection.getBusinessNum(); // businessNum 받고
    collection.add_application(); // 채용건에 지원자수++
    //workType = employment.getworkType();
};

//Boundary Class
class NewApplicationUI {
private:
    nowApplication control;
    
public:
    nowApplicationUI(string companyName, businessNum, workType)
    
    void startInterface(User* loginUser) {
        cout << "4.2. 채용 지원" << endl;
        cout << "> " << companyName << " " << businessNum << " " << workType << endl;
    }
};

//Controll Class
class ApplicationCheck { // { NULL -> 회사이름, 사업자번호, 업무, 인원 수, 신청마감일 }*
private:
    ApplicationCollection collection;
    
public:
    Employments* getEmployments(User* loginUser) {
        CompanyUser* companyUser = manager.get_company_user(loginUser->get_id());
        string businessNum = companyUser->get_business_num();
        string companyName = companyUser->get_company_name();
        string workType = employment.get_work_type();
        int applicantNum = employment.get_applicantNum();
        int employmentDeadline = employment.get_deadline();
    }
};

//Boundary Class
class ApplicationCheckUI {
private:
    applicationCheckUI control;
    
public:
    applicationCheckUI(string companyName, businessNum, workType, int applicantNum, deadline)
    
    void startInterface(User* loginUser) {
        cout << "4.3. 지원 정보 조회" << endl;
        cout << "> " << companyName << " " << businessNum << " " << workType << " " << application << " " << deadline << endl;
    }
};

//Controll Class
class CancelApplication { // 사업자번호 -> 회사이름, 사업자번호, 업무
private:
    ApplicationCollection collection;
public:
    collection.getBusinessNum(int businessNum); // businessNum 받고
    collection.cancelApplication(); // 채용건에 지원자수--
    //workType = employment.getworkType();
    
    if(collection.checkBusinessNumb == true) {
        collection.cancelApplication();
    }
};

//Boundary Class
class CancelApplicationUI {
private:
    CancelApplicationUI control;
    
public:
    CancelApplicationUI(string companyName, businessNum, workType)
    
    void startInterface(User* loginUser) {
        cout << "4.4. 지원 취소" << endl;
        cout << "> " << companyName << " " << businessNum << " " << workType << endl;
    }
};
