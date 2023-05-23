#pragma once

#include <iostream>
#include <string>
#include "entities.h"

using namespace std;

// control(등록 통계 출력)
class ShowEmploymentStat {
private:
    UserManager manager;
    EmploymentCollection collection;

public:
	ShowEmploymentStat(const EmploymentCollection& collection) {
        this->manager = manager;
        this->collection = collection;
    }

	Employment* getEmployments(User* loginUser)
	{
        CompanyUser* companyUser = manager.get_company_user(loginUser->get_id());
        string business_num = companyUser->get_business_num();
        
    }
}

// boundary(등록 통계 출력)
class EmploymentStatUI
{
private:
	ShowEmploymentStat control;
public:
	EmploymentStatUI(const EmploymentCollection& collection, const UserManager& manager) : control(collection, manager) {}

	void startInterface(User* loginUser)
	{
		cout << "5.1. 지원 정보 통계" << endl;
		control.withdrawalUser(loginUser);
		cout << "> " << loginUser->get_id() << endl;
	}
}

// control(지원 통계 출력)
class ShowEmploymentStat {
private:
    UserManager manager;
    ApplicationCollection collection;

public:
	ShowEmploymentStat(const ApplicationCollection& collection) {
        this->manager = manager;
        this->collection = collection;
    }

	Employment* getEmployments(User* loginUser)
	{
        CompanyUser* companyUser = manager.get_company_user(loginUser->get_id());
        string business_num = companyUser->get_business_num();
        
    }
}

// boundary(지원 통계 출력)
class ApplicationStatUI
{
private:
	ShowApplicationStat control;
public:
	ApplicationStatUI(const ApplicationCollection& collection, const UserManager& manager) : control(collection, manager) {}

	void startInterface(User* loginUser)
	{
		cout << "5.1. 지원 정보 통계" << endl;
		control.withdrawalUser(loginUser);
		cout << "> " << loginUser->get_id() << endl;
	}
}