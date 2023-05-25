#pragma once

#include <iostream>
#include <string>
#include "entities.h"


using namespace std;


// Control Class
class AddNewCommonUser
{
private:
	UserManager* manager;

public:
	AddNewCommonUser(UserManager* manager)
	{
		this->manager = manager;
	}

	void add_user(string id, string pw, string name, string ssn)
	{
		manager->add_common_user(id, pw, name, ssn);
	}
};


// Boundary Class
class AddCommonUserUI {
private:
	AddNewCommonUser control;

public:
	AddCommonUserUI(UserManager* manager) : control(manager) {}

	void start_interface(ifstream& in_fp, ofstream& out_fp)
	{
		string id, pw, name, ssn;
		in_fp >> id >> pw >> name >> ssn;

		out_fp << "1.1. 회원가입" << endl;
		control.add_user(id, pw, name, ssn);
		out_fp << "> " << name << " " << ssn << " " << id << " " << pw << endl;
	}
};


// Control Class
class AddNewCompanyUser
{
private:
	UserManager* manager;

public:
	AddNewCompanyUser(UserManager* manager)
	{
		this->manager = manager;
	}

	void add_user(string id, string pw, string company_name, string business_num)
	{
		manager->add_company_user(id, pw, company_name, business_num);
	}
};


// Boundary Class
class AddCompanyUserUI {
private:
	AddNewCompanyUser control;

public:
	AddCompanyUserUI(UserManager* manager) : control(manager) {}

	void start_interface(ifstream& in_fp, ofstream& out_fp)
	{
		// Get param from file
		string id, pw, company_name, business_num;
		in_fp >> id >> pw >> company_name >> business_num;

		// Echo back command, run action & write string
		out_fp << "1.1. 회원가입" << endl;
		control.add_user(id, pw, company_name, business_num);
		out_fp << "> " << company_name << " " << business_num << " " << id << " " << pw << endl;
	}
};


// Control Class
class LoginManager
{
private:
	UserManager* manager;

public:
	LoginManager(UserManager* manager)
	{
		this->manager = manager;
	}

	User* login(const string& id, const string& pw)
	{
		// Very wanky due to initial User designs
		// Check if given ID is common user or not
		if (manager->is_user_common(id))
		{
			// if so, get user and check password - Not sure if required
			// Not factoring in pw verification fail case, as it's undefined
			User* user = manager->get_common_user(id);
			if (user->is_pwd_valid(pw))
				return user;
		}
		else
		{
			User* user = manager->get_company_user(id);
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
	LoginUI(UserManager* manager) : control(manager) {}

	string start_interface(ifstream& in_fp, ofstream& out_fp)
	{
		string id, pw;
		in_fp >> id >> pw;

		out_fp << "2.1. 로그인" << endl;
		User* user = control.login(id, pw);
		out_fp << "> " << id << " " << pw << endl;

		return user->get_id();
	}
};

// Control Class
class LogoutManager
{
private:
	UserManager* manager;

public:
	LogoutManager(UserManager* manager)
	{
		this->manager = manager;
	}

	void logout(const string& id)
	{
		// Due to design change, this method got nothing to do
		// This feels VERY wrong
	}
};

// Boundary Class
class LogoutUI
{
private:
	LogoutManager control;

public:
	LogoutUI(UserManager* manager) : control(manager) {}

	void start_interface(string const& logged_in_user_id, ofstream& out_fp)
	{
		out_fp << "2.2. 로그아웃" << endl;
		control.logout(logged_in_user_id);
		cout << "> " << logged_in_user_id << endl;
	}
};

// control(회원 탈퇴)
class UserWithdrawal {
private:
	UserManager* manager;
public:
	UserWithdrawal(UserManager* manager) {
		this->manager = manager;
	}

	void withdrawalUser(const string& logged_in_user_id)
	{
		manager->delete_user_by_id(logged_in_user_id);
	}
};

// boundary(회원 탈퇴)
class UserWithdrawalUI
{
private:
	UserWithdrawal control;
public:
	UserWithdrawalUI(UserManager* manager) : control(manager) {}

	void startInterface(const string& logged_in_user_id, ofstream& out_fp)
	{
		// jupiterbjy: Maybe we should've design this to have super class with static var
		// that is keeping logged in user's ID, so we can unify interfaces

		out_fp << "1.2. 회원탈퇴" << endl;
		control.withdrawalUser(logged_in_user_id);
		out_fp << "> " << logged_in_user_id << endl;
	}
};
