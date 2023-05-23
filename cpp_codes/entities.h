#pragma once

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

// Unifying style to Google's C++ style For now
// maybe excluding class name, class name using snake-case doesn't feel right
// Written with support of Code inspection by ReSharper C++

/*
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

	CompanyUser* get_company_user(const string& id)
	{
		// Downcast to CompanyUser
		User user = *company_collection_.get_user_by_id(id);
		CompanyUser* company_user = (CompanyUser*)&user;
		return company_user;
	}

	CommonUser* get_common_user(const string& id)
	{
		// Downcast to CommonUser
		User user = *common_collection_.get_user_by_id(id);
		CommonUser* common_user = (CommonUser*)&user;
		return common_user;
	}

	bool is_user_company(const string& id)
	{
		// Check if user is company user
		return company_collection_.does_user_exist(id);
	}

	bool is_user_common(const string& id)
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
*/

class Employment
{
private:
    string EcompanyName;
    string Edeadline;
    string Ework;
    int peopleNumber;
public:
    Employment(string companyName, string deadline, string work){
        EcompanyName = companyName;
        Edeadline = deadline;
        Ework = work;
        peopleNumber = 0;
    }
	
    string getCompanyName(){
        return this->EcompanyName;
    }
    string getDeadline(){
        return this->Edeadline;
    }
    string getWork(){
        return this->Ework;
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
private:
    static Employment* employmentList[50];
    static int numEmployments;
public:
    static Employment* getEmployment(int index){
        return employmentList[index];
    }
    static void addEmployment(const string& companyName, const string& deadline, const string& work){
        Employment new_employment = Employment(companyName, deadline, work);
        employmentList[numEmployments] = &new_employment;
        numEmployments++;
    }
    static int staticsEmployment(){
        return numEmployments;
    }
};

//채용 정보 등록(3.1)
//[업무] [인원 수] [신청 마감일]
class EmploymentAdd;
class EmploymentAddUI{
private:
    EmploymentAdd * employmentAdd;
public:
//show First 함수 사라짐.
    string addEmployment(){
        string returnString="";
        getline(cin, returnString);
        return returnString;
    }
};
class EmploymentAdd{
private:
    EmploymentAddUI * employmentAddUI;
    EmploymentCollection * employmentCollection;
public:
    void addEmployment(){
        string returnString = employmentAddUI->addEmployment();
		cout << returnString << endl;
	}
};

//등록된 채용 정보 리스트 조회 (3.2)
//[회사이름] [사업자번호] [업무] [인원 수] [신청마감일]
class ShowEmploymentList;
class ShowEmploymentListUI{
private:
    ShowEmploymentList *showEmploymentList;
public:
    void showEmploymentListFunction(Employment* employment){
		ofstream ofs(OUTPUT_FILE_NAME);
        ofs << employment->getCompanyName() << employment->getWork() << employment->getDeadline() << endl;
        return;
    }
};
class ShowEmploymentList{
private:
    ShowEmploymentListUI* showEmploymentListUI;
    EmploymentCollection* employmentCollection;
public:
    void showEmploymentInfo(){
        int index = 0;
		//int형 선언함
        Employment* employment = employmentCollection->getEmployment(index);
        while(employment!=NULL){
            showEmploymentListUI->showEmploymentListFunction(employment);
            index++;
            employment = employmentCollection->getEmployment(index);     
			//  if 사용자랑 == 현재 유저가 같으면 
			//	지금 조건이 맞는지 검사 후 int 자료형 하나 선언해둔거++  
        }
		// UI에 출력 요청을 보냄
		return;
    }
};
// istringstream은 istream을 상속받으므로 getline을 사용할 수 있다.
	/*
    while (getline(returnString, buffer, Delimiter)) {
        result.push_back(buffer);               // 절삭된 문자열을 vector에 저장
    }
        vector<string> result = split(returnString, ' ');
        employmentCollection.addEmployment(result[0],result[1],result[2]);
    }
};
//회사 이름 검색(4.1)
class CompanyNameSearch;
class CompanyNameSearchUI{
private:
    CompanyNameSearch companyNameSearch;
public:
    //void startInterface(); 삭제해야할수도?
    void searchCompanyName();
};

class CompanyNameSearch
{
private:
    EmploymentCollection employmentCollection;
public:
};
*/