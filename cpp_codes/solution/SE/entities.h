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
	string get_employment();
	string get_company_name();
	string get_business_number();
	string get_dead_line();
	int get_max_applicants();
	string get_work_type();
};


class ApplicationCollection
{
private:
	Application* applications[100] = {nullptr,};
	int total_applicants = 0;

public:
	Application* addApplication(Employment* parent, const string& logged_in_user_id)
	{
		// Create new application and return it
		applications[total_applicants] = new Application(parent, logged_in_user_id);
		return applications[total_applicants++];
	}

	void removeApplication(string const& business_num, string const& logged_in_user_id)
	{
		// find application
		int target_idx = -1;

		for (int idx=0; idx < total_applicants; idx++)
		{
			if (applications[idx]->get_business_number() == business_num)
			{
				target_idx = idx;
				break;
			}
		}

		// (Assuming search always succeeds) delete application
		delete applications[target_idx];

		// fill in gap
		for (int idx=target_idx; idx < --total_applicants; idx++)
			applications[idx] = applications[idx + 1];
	}

	int total_applications_count()
	{
		return total_applicants;
	}

	int getEmploymentNum() {
		return total_applicants;
	}

	string getCompanyName(int index) {
		return applications[index]->get_company_name();
	}

	string getDeadline(int index) {
		return applications[index]->get_dead_line();
	}

	string getWork(int index) {
		return applications[index]->get_work_type();
	}

	string getBusinessNumber(int index) {
		return applications[index]->get_business_number();
	}

	Application* getEmploymentByIndex(int index)
	{
		return applications[index];
	}

	Application* getEmploymentByBussinessNum(string bussinessNum)
	{
		for (int i = 0; i < total_applicants; ++i)
			if (applications[i]->get_business_number() == bussinessNum) return applications[i];
		return nullptr;
	}
};


class Employment
{
private:
	string companyName;
	string deadline;
	string work_type;
	int max_applicants;
	string businessNum;

public:
	Employment(const string& companyName, const string& work_type, int max_applicants, const string& business_num, const string& deadline) {
		this->companyName = companyName;
		this->deadline = deadline;
		this->work_type = work_type;
		this->max_applicants = max_applicants;
		this->businessNum = business_num;
	}

	string getCompanyName() {
		return this->companyName;
	}
	string getDeadline() {
		return this->deadline;
	}
	string getWork() {
		return this->work_type;
	}
	int getPeopleNumber() {
		return this->max_applicants;
	}
	string getBusinessNumber() {
		return this->businessNum;
	}
};

class EmploymentCollection
{
public:
	Employment* employmentList[10];
	int numEmployments;
	Employment* getEmployment(int index) {
		return employmentList[index];
	}

	Employment* addEmployment(const string& companyName, const string& work_type, int max_applicants, const string& business_num, const string& deadline) {
		// Create new employment and return ref
		Employment* new_employment = new Employment(companyName, work_type, max_applicants, business_num, deadline);

		employmentList[numEmployments] = new_employment;
		return employmentList[numEmployments++];
	}

	int getEmploymentNum() {
		return numEmployments;
	}

	string getCompanyName(int index) {
		return employmentList[index]->getCompanyName();
	}

	string getDeadline(int index) {
		return employmentList[index]->getDeadline();
	}

	string getWork(int index) {
		return employmentList[index]->getWork();
	}

	int getPeopleNumber(int index) {
		return employmentList[index]->getPeopleNumber();
	}

	string getBusinessNumber(int index) {
		return employmentList[index]->getBusinessNumber();
	}

	Employment* getEmploymentByIndex(int index)
	{
		return employmentList[index];
	}
	Employment* getEmploymentByBussinessNum(string bussinessNum)
	{
		for (int i = 0; i < numEmployments; ++i)
			if (employmentList[i]->getBusinessNumber() == bussinessNum) return employmentList[i];
		return nullptr;
	}
	Employment* getEmploymentByName(string name)
	{
		for (int i = 0; i < numEmployments; ++i)
			if (employmentList[i]->getCompanyName() == name) return employmentList[i];
		return nullptr;
	}
};


inline string Application::get_employment()
{
	return parent->getBusinessNumber();
}

inline string Application::get_company_name()
{
	return parent->getCompanyName();
}

inline string Application::get_business_number()
{
	return parent->getBusinessNumber();
}

inline string Application::get_dead_line()
{
	return parent->getDeadline();
}

inline int Application::get_max_applicants()
{
	return parent->getPeopleNumber();
}

inline string Application::get_work_type()
{
	return parent->getWork();
}
