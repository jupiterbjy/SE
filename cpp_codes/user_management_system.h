#pragma once

#include <iostream>
#include <string>
#include "entities.h"


using namespace std;


class AddNewCommonUser
{
private:
	UserManager manager;

public:
	AddNewCommonUser(const UserManager& manager)
	{
		this->manager = manager;
	}

	void add_user(string id, string pw, string name, string ssn)
	{
		manager.add_common_user(id, pw, name, ssn);
	}
};

class AddCommonUserUI {
private:
	AddNewCommonUser control;

public:
	AddCommonUserUI(const UserManager& manager) : control(manager) {}

	void start_interface(string id, string pw, string name, string ssn)
	{
		control.add_user(id, pw, name, ssn);
		cout << "> " << name << " " << ssn << " " << id << " " << pw << endl;
	}
};


class AddNewCompanyUser
{
private:
	UserManager manager;

public:
	AddNewCompanyUser(const UserManager& manager)
	{
		this->manager = manager;
	}

	void add_user(string id, string pw, string company_name, string business_num)
	{
		manager.add_company_user(id, pw, company_name, business_num);
	}
};


class AddCompanyUserUI {
private:
	AddNewCompanyUser control;

public:
	AddCompanyUserUI(const UserManager& manager) : control(manager) {}

	void start_interface(string id, string pw, string company_name, string business_num)
	{
		control.add_user(id, pw, company_name, business_num);
		cout << "> " << company_name << " " << business_num << " " << id << " " << pw << endl;
	}
};


class LoginManager
{
private:
	LoginUI ui;

public:

};


class LoginUI
{
	
};