#pragma once

#include<string>
#include <utility>

// Unifying style to Google's C++ style For now
// maybe excluding class name, class name using snake-case doesn't feel right
// Written with support of Code inspection by ReSharper C++

using namespace std;

class User
{
private:
	string id_;
	string pw_;

public:
	User(const string& id, const string& pw)
	{
		id_ = id;
		pw_ = pw;
	}

	string get_id() { return id_; }
	bool is_pwd_valid(const string& password) const { return password == pw_; }
};



class CompanyUser : public User
{
private:
	string company_name_;
	string business_num_;

public:
	CompanyUser(const string& id, const string& pw, string company_name, string business_num): User(id, pw)
	{
		company_name_ = std::move(company_name);
		business_num_ = std::move(business_num);
	}

	string get_company_name() { return company_name_; }
	string get_business_num() { return business_num_; }
};


class CommonUser : public User
{
private:
	string name_;
	string ssn_;

public:
	CommonUser(const string& id, const string& pw, string name, string ssn) : User(id, pw)
	{
		name_ = std::move(name);
		ssn_ = std::move(ssn);
	}

	string get_name() { return name_; }
	string get_ssn() { return ssn_; }
};


class UserCollection
{
private:
	User* users_[100] = {nullptr,};
	int total_users_ = 0;

	int find_user_idx_by_id(const string& id) const
	{
		// Linear search if there's matching idx
		for (int idx = 0; idx < total_users_; idx++)
			if (users_[idx]->get_id() == id)
				return idx;

		// Otherwise -1
		return -1;
	}

public:
	bool does_user_exist(const string& id) const
	{
		return find_user_idx_by_id(id) != -1;
	}

	void add_user(User* user)
	{
		users_[total_users_++] = user;
	}

	void del_user(const string& id)
	{
		const int user_idx = find_user_idx_by_id(id);

		// copy user ref
		const User* user = users_[user_idx];
		delete &user;

		// move user refs to fill in the gap
		for (int idx = 0; idx < --total_users_; idx++)
			users_[idx] = users_[idx + 1];
	}

	User* get_user_by_id(const string& id) const
	{
		return users_[find_user_idx_by_id(id)];
	}

	int get_user_count() const { return total_users_; }
};


class UserManager
{
private:
	UserCollection company_collection_ = UserCollection();
	UserCollection common_collection_ = UserCollection();

public:
	void add_company_user(const string& id, const string& pw, const string& company_name, const string& business_num)
	{
		User* new_user = new CompanyUser(id, pw, company_name, business_num);
		company_collection_.add_user(new_user);
	}

	void add_common_user(const string& id, const string& pw, const string& name, const string& ssn)
	{
		User* new_user = new CommonUser(id, pw, name, ssn);
		company_collection_.add_user(new_user);
	}

	void delete_user_by_id(const string& id)
	{
		// Check if it's in company collection, delete it if so
		if (company_collection_.does_user_exist(id))
			company_collection_.del_user(id);
		else
			// Otherwise delete in other collection
			common_collection_.del_user(id);
	}
};
