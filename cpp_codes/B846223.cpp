/*#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

vector<string> split(string str, char Delimiter) {
    istringstream iss(str);             // istringstream에 str을 담는다.
    string buffer;                      // 구분자를 기준으로 절삭된 문자열이 담겨지는 버퍼
 
    vector<string> result;
 
    // istringstream은 istream을 상속받으므로 getline을 사용할 수 있다.
    while (getline(iss, buffer, Delimiter)) {
        result.push_back(buffer);               // 절삭된 문자열을 vector에 저장
    }
 
    return result;
}

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

    void getEmployment();// [업무] [인원 수] [신청 마감일]
    void getEmploymentDetails(); //<- 이제 필요없을 것 같음(삭제필)
    void addEmployment(); //[업무] [인원 수] [신청 마감일]
    void updateEmployment();
    void deleteEmployment();
    void getClosedEmployment();
    void getClosingEmployment();

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

//등록된 채용 정보 리스트 조회 (3.2)
//[회사이름] [사업자번호] [업무] [인원 수] [신청마감일]
class ShowEmploymentListUI{
private:
    ShowEmploymentList showEmploymentList;
public:
    void showEmploymentListFunction(Employment* employment){
        cout << employment->getCompanyName() << employment->getWork() << employment->getDeadline() << endl;
        return;
    }
};
class ShowEmploymentList{
private:
    ShowEmploymentListUI showEmploymentListUI;
    EmploymentCollection employmentCollection;
public:
    void ShowEmploymentInfo(){
        int index = 0;
        Employment* employment = employmentCollection.getEmployment(index);
        while(employment!=NULL){
            showEmploymentListUI.showEmploymentListFunction(employment);
            index++;
            employment = employmentCollection.getEmployment(index);        
        }
    }
};
//채용 정보 등록(3.1)
//[업무] [인원 수] [신청 마감일]
class EmploymentAdd;
class EmploymentAddUI{
private:
    EmploymentAdd employmentAdd;
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
    EmploymentAddUI employmentAddUI;
    EmploymentCollection employmentCollection;
public:
    void addEmployment(){
        string returnString = employmentAddUI.addEmployment();
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