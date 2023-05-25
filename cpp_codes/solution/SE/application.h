#pragma once

#include <iostream>
#include <string>
#include "entities.h"

class ApplicationCollection {
private:
    Application* applications[100];
    int applicationTotal = 0;
    
    int* businessNum[100];
    
public:
    int total_count() { return total; } // 합계 카운터
    
    bool checkBusinessNum(int businessNum) { //입력한 사업자번호와 지원완료한 회사의 사업자번호 비교 (True -> cancelApplication();)
        for (int idx = 0; idx < total; idx++)
            if (application[idx] == businessNum)
                return true;
        
        return false;
    }

    void add_application(Application application) { // 노예지원서 추가하기
        applications[applicationTotal++] = applications; // 지원서 합계
    }
    
    void cancelApplication(int idx) { // 마감안했으면 지원취소 가능
        aapplication[total--] = application;
    }
    
    Application get_application_by_index(int idx) { //인덱스로 지원서 뽀려오기
        return applications[idx];
    }
    
    Application getBusinessNum(int businessNum){ //사업자번호 받아오기
        return businessNum;
    }
};

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
class NowApplicationUI {
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
