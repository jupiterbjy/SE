#pragma once

#include <string>
#include <utility>

// Unified with Google's C++ C++ Code style excluding class name.
// Written with ReSharper C++ code re-formatter

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
	CompanyUser(const string& id, const string& pw, string company_name, string business_num) : User(id, pw)
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
	User* users_[100] = { nullptr, };
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
		delete& user;

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

	CompanyUser* get_company_user(const string& id) const
	{
		// Downcast to CompanyUser
		User* user = company_collection_.get_user_by_id(id);
		auto* company_user = reinterpret_cast<CompanyUser*>(&user);
		return company_user;
	}

	CommonUser* get_common_user(const string& id) const
	{
		// Downcast to CommonUser
		User* user = common_collection_.get_user_by_id(id);
		auto* common_user = reinterpret_cast<CommonUser*>(&user);
		return common_user;
	}

	bool is_user_company(const string& id) const
	{
		// Check if user is company user
		return company_collection_.does_user_exist(id);
	}

	bool is_user_common(const string& id) const
	{
		// Check if user is company user
		// Now I think we'd better off adding company/common flag in user...
		return common_collection_.does_user_exist(id);
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


class Employment;
class Application
{
private:
	Employment* parent;
	string user_id;

public:
	Application(Employment* parent, const string& user_id)
	{
		this->parent = parent;
		this->user_id = user_id;
	}

	string get_user_id() { return user_id; }
	string get_employment() const;
	string get_company_name() const;
	string get_business_number() const;
	string get_dead_line() const;
	int get_max_applicants() const;
	string get_work_type() const;
};


class ApplicationCollection
{
private:
	Application* applications[100] = {nullptr,};
	int total_applicants = 0;

public:
	Application* add_application(Employment* parent, const string& logged_in_user_id)
	{
		// Create new application and return it
		applications[total_applicants] = new Application(parent, logged_in_user_id);
		return applications[total_applicants++];
	}

	Application* remove_application(string const& logged_in_user_id, string const& business_num)
	{
		// find application
		int target_idx = -1;

		for (int idx=0; idx < total_applicants; idx++)
		{
			if (applications[idx]->get_business_number() == business_num && applications[idx]->get_user_id() == logged_in_user_id)
			{
				target_idx = idx;
				break;
			}
		}

		// (Assuming search always succeeds) cache application
		const auto deleted_application = applications[target_idx];

		// fill in gap
		for (int idx=target_idx; idx < --total_applicants; idx++)
			applications[idx] = applications[idx + 1];

		// return
		return deleted_application;
	}

	int total_applications_count() const
	{
		return total_applicants;
	}

	int get_employment_num() const
	{
		return total_applicants;
	}

	string get_company_name(const int index) const
	{
		return applications[index]->get_company_name();
	}

	string get_deadline(const int index) const
	{
		return applications[index]->get_dead_line();
	}

	string get_work(const int index) const
	{
		return applications[index]->get_work_type();
	}

	string get_business_number(const int index) const
	{
		return applications[index]->get_business_number();
	}

	Application* get_employment_by_index(const int index) const
	{
		return applications[index];
	}

	Application* get_employment_by_business_num(const string& business_num) const
	{
		for (int i = 0; i < total_applicants; ++i)
			if (applications[i]->get_business_number() == business_num) return applications[i];
		return nullptr;
	}
};


class Employment
{
private:
	string company_name;
	string deadline;
	string work_type;
	int max_applicants;
	string business_num;

public:
	Employment(const string& company_name, const string& work_type, const int max_applicants, const string& business_num, const string& deadline) {
		this->company_name = company_name;
		this->deadline = deadline;
		this->work_type = work_type;
		this->max_applicants = max_applicants;
		this->business_num = business_num;
	}

	string get_company_name() {
		return this->company_name;
	}
	string get_deadline() {
		return this->deadline;
	}
	string get_work() {
		return this->work_type;
	}
	int get_max_applicants() const
	{
		return this->max_applicants;
	}
	string get_business_number() {
		return this->business_num;
	}
};

class EmploymentCollection
{
private:
	Employment* employment_list[100] = {};
	int num_employments = 0;

	string work_types[100];
	int work_type_count = 0;

	bool does_type_exists(string const& work_type) const
	{
		for (int idx = 0; idx < work_type_count; idx++)
			if (work_types[0] == work_type)
				return true;

		return false;
	}

	void add_new_type(string const& work_type)
	{
		work_types[work_type_count++] = work_type;
	}

public:
	Employment* get_employment(int index) const
	{
		return employment_list[index];
	}

	Employment* add_employment(const string& company_name, const string& work_type, const int max_applicants, const string& business_num, const string& deadline) {
		// Check if type exists, add if not
		if (!does_type_exists(work_type))
			add_new_type(work_type);

		// Create new employment and return ref
		auto* new_employment = new Employment(company_name, work_type, max_applicants, business_num, deadline);

		employment_list[num_employments] = new_employment;
		return employment_list[num_employments++];
	}

	int get_total_type_count() const
	{
		return work_type_count;
	}

	int get_total_employment_count() const
	{
		return num_employments;
	}

	string get_work_type_by_index(const int idx)
	{
		return work_types[idx];
	}

	int get_employment_num() const
	{
		return num_employments;
	}

	string get_company_name(const int index) const
	{
		return employment_list[index]->get_company_name();
	}

	string get_deadline(const int index) const
	{
		return employment_list[index]->get_deadline();
	}

	string get_work(const int index) const
	{
		return employment_list[index]->get_work();
	}

	int get_max_applicants(const int index) const
	{
		return employment_list[index]->get_max_applicants();
	}

	string get_business_number(const int index) const
	{
		return employment_list[index]->get_business_number();
	}

	Employment* get_employment_by_index(const int index) const
	{
		return employment_list[index];
	}
	Employment* get_employment_by_business_num(const string& business_num) const
	{
		for (int i = 0; i < num_employments; ++i)
			if (employment_list[i]->get_business_number() == business_num) return employment_list[i];
		return nullptr;
	}
	Employment* get_employment_by_name(const string& name) const
	{
		for (int i = 0; i < num_employments; ++i)
			if (employment_list[i]->get_company_name() == name) return employment_list[i];
		return nullptr;
	}
};


inline string Application::get_employment() const
{
	return parent->get_business_number();
}

inline string Application::get_company_name() const
{
	return parent->get_company_name();
}

inline string Application::get_business_number() const
{
	return parent->get_business_number();
}

inline string Application::get_dead_line() const
{
	return parent->get_deadline();
}

inline int Application::get_max_applicants() const
{
	return parent->get_max_applicants();
}

inline string Application::get_work_type() const
{
	return parent->get_work();
}
