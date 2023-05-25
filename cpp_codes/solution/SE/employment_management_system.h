#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include "entities.h"

using namespace std;


//채용 정보 등록(3.1)
//[업무] [인원 수] [신청 마감일]
class EmploymentAdd;
class EmploymentAddUI{
private:
    EmploymentAdd * employmentAdd;
public:
//show First 함수 사라짐.
    void start_interface(){
        cout << "3.1 UI is running" << endl;
        //
        //getline(cin, returnString);
        //return returnString;
        return;
    }
};


class EmploymentAdd{
private:
    EmploymentAddUI * employmentAddUI;
    EmploymentCollection * employmentCollection;
public:
    void addEmployment(){
        employmentCollection->addEmployment("Companytest", "testDate","testWork");

        int number = employmentCollection->getEmploymentNum();
        string temp = employmentCollection-> getCompanyName(0);

        cout << temp << endl;
        employmentAddUI->start_interface();
        return;
	}
};

//등록된 채용 정보 리스트 조회 (3.2)
//[회사이름] [사업자번호] [업무] [인원 수] [신청마감일]
class ShowEmploymentList;
class ShowEmploymentListUI{
private:
    ShowEmploymentList *showEmploymentList;
public:
    void start_interface(string companyName, string work, string deadline){
        cout << "3.2 UI is running" << endl;
        cout << companyName << work << deadline <<endl;
		//ofstream ofs(OUTPUT_FILE_NAME);
        //ofs << employment->getCompanyName() << employment->getWork() << employment->getDeadline() << endl;
        return;
    }
};

class ShowEmploymentList{
private:
    ShowEmploymentListUI* showEmploymentListUI;
    EmploymentCollection* employmentCollection;
public:
    void showEmploymentInfo(){
        int index;
        int total = employmentCollection->getEmploymentNum();
		//int형 선언함 
        for(index=0;index<total;index++){
            string temp = employmentCollection->getCompanyName(index);
            cout << temp << endl;
            showEmploymentListUI->start_interface(employmentCollection->getCompanyName(index), employmentCollection->getWork(index), employmentCollection->getDeadline(index));;
            index++;
			//  if 사용자랑 == 현재 유저가 같으면 
			//	지금 조건이 맞는지 검사 후 int 자료형 하나 선언해둔거++  
        }
		// UI에 출력 요청을 보냄
		return;
    }
};



// Boundary
class CompanyNameSearch;
class CompanyNameSearchUI{
private:
    CompanyNameSearch control;
public:
    CompanyNameSearchUI(EmploymentCollection collection) : control(collection) {}

    void startInterface()
    {
	    
    }
};


// Control
class CompanyNameSearch
{
private:
    EmploymentCollection collection;
public:
    CompanyNameSearch(EmploymentCollection collection)
    {
        this->collection = collection;
    }

    void searchCompanyName()
    {
	    
    }
};
