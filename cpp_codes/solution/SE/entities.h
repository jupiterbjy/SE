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
class EmploymentCollection;
class Application
{
private:
	Employment* parent;
	const string user_id_;
	string businessNum_;
	string work_type_;

public:
	Application(Employment* parent, const string& user_id, const string& businessNum, const string& work_type)
		: parent(parent),
		user_id_(user_id),
		businessNum_(businessNum),
		work_type_(work_type)
	{};

	string get_user_id() { return user_id_; }

	string get_employment();
	string get_company_name();
	string get_business_number();
	string get_dead_line();
	int get_people_number();
	string get_work_type() { return work_type_; }
};


class ApplicationCollection {
private:
	Application* applications[100];
	Employment* employment_;
	int applicationTotal = 0;

public:

	ApplicationCollection(Employment* employment) : employment_(employment) {}

	int totalCount() { return applicationTotal; } // 합계 카운터


	void add_application(Application* application) { // 노예지원서 추가하기

		applications[applicationTotal++] = application; // 지원서 합계
	}

	void cancel_application(int idx) { // 마감안했으면 지원취소 가능
		//if (idx >= applicationTotal) return RETURN_ERROR;  //예외처리의 흔적
		delete applications[idx];
		for (int i = idx + 1; i < applicationTotal; ++i)
		{
			applications[i - 1] = std::move(applications[i]);
		}
		--applicationTotal;
	}

	//지원서 가져오기 중 필요 없는 것 찾아서 지워야 함
	Application& get_application_by_index(int idx) { //인덱스로 지원서 뽀려오기
		return *applications[idx];
	}

	Application* get_application_by_user_id(string user_id) { //유저아이디로 지원서 뽀려오기
		for (Application* app : applications)
			if (app->get_user_id() == user_id)
				return app;
		return nullptr;
	}

	int get_index_by_user_id(string user_id) { //유저아이디로 지원서 번호 가져오기
		for (int i = 0; i < applicationTotal; ++i)
			if (applications[i]->get_user_id() == user_id)
				return i;
		return -1;
	}
};


class Employment
{
private:
	string companyName;
	string deadline;
	string work;
	int peopleNumber;
	string businessNum;
	ApplicationCollection* applicationCollection;
public:
	Employment(string companyName, string deadline, string work, string businessNum) {
		this->companyName = companyName;
		this->deadline = deadline;
		this->work = work;
		this->peopleNumber = 0;
		this->businessNum = businessNum;
		this->applicationCollection = new ApplicationCollection(this);
	}

	string getCompanyName() {
		return this->companyName;
	}
	string getDeadline() {
		return this->deadline;
	}
	string getWork() {
		return this->work;
	}
	int getPeopleNumber() {
		return this->peopleNumber;
	}
	string getBusinessNumber() {
		return this->businessNum;
	}
	ApplicationCollection* getApplicationCollection() {
		return this->applicationCollection;
	}
	/*
		void getEmployment();// [업무] [인원 수] [신청 마감일]
		void getEmploymentDetails(); //<- 이제 필요없을 것 같음(삭제필)
		void addEmployment(); //[업무] [인원 수] [신청 마감일]
		void updateEmployment();
		void deleteEmployment();
		void getClosedEmployment();
		void getClosingEmployment();
	*/
};

class EmploymentCollection
{
public:
	static Employment* employmentList[10];
	static int numEmployments;
	Employment* getEmployment(int index) {
		return employmentList[index];
	}

	static void addEmployment(const string& companyName, const string& deadline, const string& work, const string bussinessNum) {
		Employment* new_employment = new Employment(companyName, deadline, work, bussinessNum);

		employmentList[numEmployments] = new_employment;
		numEmployments++;
	}

	static int getEmploymentNum() {
		return numEmployments;
	}

	static string getCompanyName(int index) {
		return employmentList[index]->getCompanyName();
	}

	static string getDeadline(int index) {
		return employmentList[index]->getDeadline();
	}

	static string getWork(int index) {
		return employmentList[index]->getWork();
	}

	static int getPeopleNumber(int index) {
		return employmentList[index]->getPeopleNumber();
	}

	static string getBusinessNumber(int index) {
		return employmentList[index]->getBusinessNumber();
	}

	static Employment* getEmploymentByIndex(int index)
	{
		return employmentList[index];
	}
	static Employment* getEmploymentByBussinessNum(string bussinessNum)
	{
		for (int i = 0; i < numEmployments; ++i)
			if (employmentList[i]->getBusinessNumber() == bussinessNum) return employmentList[i];
		return nullptr;
	}
	static Employment* getEmploymentByName(string name)
	{
		for (int i = 0; i < numEmployments; ++i)
			if (employmentList[i]->getCompanyName() == name) return employmentList[i];
		return nullptr;
	}
};

Employment* EmploymentCollection::employmentList[10] = {};
int EmploymentCollection::numEmployments = 0;



string Application::get_employment()
{
	return parent->getBusinessNumber();
}
string Application::get_company_name()
{
	return parent->getCompanyName();
}
string Application::get_business_number()
{
	return parent->getBusinessNumber();
}
string Application::get_dead_line()
{
	return parent->getDeadline();
}
int Application::get_people_number()
{
	return parent->getPeopleNumber();
}
