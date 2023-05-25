#pragma once

#include <iostream>
#include <string>
#include "entities.h"

using namespace std;

// control(5.1. 등록 통계 출력)
class ShowEmploymentStat {
private:
    EmploymentCollection eCollection;
    ApplicationCollection aCollection;
    EmploymentStatUI boundary;

    int runStatistics(string keyword, string id) {
        int total = 0;

        for (int idx = 0; idx < eCollection.statisticsEmployment(); idx++) { // -> 현재 진짜 collection에 statics로 돼있어서 오류날 예정 변경 필요
            // 모든 주어진 키워드 업무에 대해
            // ID 동일한지, 키워드 동일한지 확인
            // 동일하면 통계 += 1
            Employment* employment = eCollection.getEmploymentByIndex(idx);   // EmploymentCollection에 getEmploymentByIndex 정의 필요
            // (본인이 등록한 채용에 대하여)채용문서 작성한 사람의 id와 로그인 유저의 id 같을 때 + 업무 이름 같을 때
            if (employment->getCompanyUserId() == id && keyword == employment->getWork()) {
                // 지원 전체 목록에서 해당 채용일 때 모두 확인하여 +1
                Application* application = aCollection.getApplicationByIndex(idx);  // ApplicationCollection에 getApplicationByIndex 정의 필요
                for (int j = 0; j < aCollection->statisticsApplication(); j++)   // statisticsApplication은 EmploymentCollection 형식과 동일하다 생각하고 작성
                { 
                    // 등록한 채용정보의 사업자번호와 지원서의 사업자번호가 같을 때(지원시 사업자 번호를 제출하므로 따로 업무 또한 같은지 확인할 필요 없어보임)
                    if (application->getSSN() == employment->getSSN()) {    // getSSN() 정의 필요 (attribute도 추가 필요)
                        // 지원 목록 중 현재 로그인한 회사회원이 등록한 채용일 때 +1
                        total++;
                    }
                }
            }
            // 통계 반환
            return total;
        }
    }

public:
	ShowEmploymentStat(const EmploymentCollection& eCollection, const ApplicationCollection& aCollection, const ApplicationStatUI& boundary) {
        this->eCollection = eCollection;
        this->aCollection = aCollection;
        this->boundary = boundary;
    }

    void runAllStatistics(string id) {
        // EmploymentCollection에 등록된 전체 업무 키워드에 대해
        for (int idx = 0; idx < collection.getWorkTypesTotal(); idx++) {    // EmploymentCollection에 getWorkTypesTotal() 정의 필요
            // 각 업무 키워드 마다
            string keyword = collection.getWorkTypeIdx(idx);    // EmploymentCollection에 getWorkTypeIdx(idx) 정의 필요

            // 해당 키워드와 유저 ID에 대한 통계
            int count = runStatistics(keyword, id);

            // 바운더리 클래스에게 해당 업무 키워드에 대한 통계 출력 위임
            boundary.outputStatistics(keyword, count);
        }
    }
}

// boundary(5.1. 등록 통계 출력)
class EmploymentStatUI
{
private:
	ShowEmploymentStat control;
public:
	EmploymentStatUI(const EmploymentCollection& collection) : control(collection) {}

    void outputStatistics(string workKeyword, int total) 
    {
        cout << workKeyword << " " << total << endl;
    }

    void startInterface(User* loginUser)
	{
		cout << "5.1. 지원 정보 통계" << endl;
        control.runAllStatistics(loginUser->getId());
    }
}

// control(5.1. 지원 통계 출력)
class ShowApplicationStat {
private:
    ApplicationCollection aCollection;
    EmploymentCollection eCollection;
    ApplicationStatUI boundary;

    int runStatistics(string keyword, string id) {
        int total = 0;

        for (int idx = 0; idx < aCollection.statisticsApplication(); idx++) {   // ApplicationCollection에 statisticsApplication() 정의 필요
            // 모든 주어진 키워드 업무에 대해
            // ID 동일한지, 키워드 동일한지 확인
            // 동일하면 통계 += 1
            Application* application = aCollection.getApplicationByIndex(idx);   // ApplicationCollection에 getApplicationByIndex() 정의 필요
            if (application->getCommonUserId() == id && keyword == application->getWork()) { // ApplicationCollection에 getCommonUserId(), getWork() 정의 필요 - 지원한 사람의 id
                // 채용 전체 목록에서 해당 지원일 때 모두 확인하여 +1
                Employment* employment = eCollection.getEmploymentByIndex(idx);  // EmploymentCollection에 getEmploymentByIndex 정의 필요
                for (int j = 0; j < eCollection->statisticsEmployment(); j++)
                { 
                    // 등록한 채용정보의 사업자번호와 지원서의 사업자번호가 같을 때(지원시 사업자 번호를 제출하므로 따로 업무 또한 같은지 확인할 필요 없어보임)
                    if (application->getSSN() == employment->getSSN()) {    // getSSN() 정의 필요 (attribute도 추가 필요)
                        // 지원 목록 중 현재 로그인한 회사회원이 등록한 채용일 때 +1
                        total++;
                    }
                }
            }
            // 통계 반환
            return total;
        }
    }
public:
    ShowApplicationStat(const ApplicationCollection& aCollection, const EmploymentCollection& eCollection, const ApplicationStatUI& boundary) {
        this->aCollection = aCollection;
        this->eCollection = eCollection;
        this->boundary = boundary;
    }

    void runAllStatistics(string id) {
        // ApplicationCollection에 있는 전체 지원한 업무 키워드에 대해
        for (int idx = 0; idx < collection.getWorkTypesTotal(); idx++) {
            // 각 업무 키워드 마다
            string keyword = collection.getWorkTypeIdx(idx);

            // 해당 키워드와 유저 ID에 대한 통계
            int count = runStatistics(keyword, id);

            // 바운더리 클래스에게 해당 업무 키워드에 대한 통계 출력 위임
            boundary.outputStatistics(keyword, count);
        }
    }
}

// boundary(5.1. 지원 통계 출력)
class ApplicationStatUI
{
private:
	ShowApplicationStat control;
public:
	ApplicationStatUI(const ApplicationCollection& collection) : control(collection) {}

    void outputStatistics(string workKeyword, int total) 
    {
        cout << workKeyword << " " << total << endl;
    }

	void startInterface(User* loginUser)
	{
		cout << "5.1. 지원 정보 통계" << endl;
		control.runAllStatistics(loginUser->getId());
	}
}