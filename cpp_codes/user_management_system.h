#pragma once

#include <iostream>
#include <string>
#include "entities.h"


using namespace std;


// Control Class
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

// Boundary Class
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

// Control Class
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

// Boundary Class
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

// Control Class
class LoginManager
{
private:
	UserManager manager;

public:
	LoginManager(const UserManager& manager)
	{
		this->manager = manager;
	}

	User* login(const string& id, const string& pw)
	{
		// Very wanky due to initial User designs
		// Check if given ID is common user or not
		if (manager.is_user_common(id))
		{
			// if so, get user and check password - Not sure if required
			// Not factoring in pw verification fail case, as it's undefined
			User* user = manager.get_common_user(id);
			if (user->is_pwd_valid(pw))
				return user;
		}
		else
		{
			User* user = manager.get_company_user(id);
			if (user->is_pwd_valid(pw))
				return user;
		}

		return nullptr;
	}
};

// Boundary Class
class LoginUI
{
private:
	LoginManager control;

public:
	LoginUI(const UserManager& manager) : control(manager) {}

	User* start_interface(const string& id, const string& pw)
	{
		User* user = control.login(id, pw);
		cout << "> " << id << " " << pw << endl;

		return user;
	}
};

// Control Class
class LogoutManager
{
private:
	UserManager manager;

public:
	LogoutManager(const UserManager& manager)
	{
		this->manager = manager;
	}

	void logout(const string& id)
	{
		// Due to design change, this method got nothing to do
		// This feels VERY wrong
		return;
	}
};

// Boundary Class
class LogoutUI
{
private:
	LogoutManager control;

public:
	LogoutUI(const UserManager& manager) : control(manager) {}

	void start_interface(const string& id)
	{
		control.logout(id);
		cout << "> " << id << endl;
	}
};

// control(회원 탈퇴)
class UserWithdrawal {
private:
	UserManager manager;
public:
	UserWithdrawal(const UserManager& manager) {
		this->manager = manager;
	}

	void withdrawalUser(User* loginUser)
	{
		manager.delete_user_by_id(loginUser->get_id());
	}
}

// boundary(회원 탈퇴)
class UserWithdrawalUI
{
private:
	UserWithdrawal control;
public:
	UserWithdrawalUI(const UserManager& manager) : control(manager) {}

	void startInterface(User* loginUser)
	{
		cout << "1.2. 회원탈퇴" << endl;
		control.withdrawalUser(loginUser);
		cout << "> " << loginUser->get_id() << endl;
	}
}
