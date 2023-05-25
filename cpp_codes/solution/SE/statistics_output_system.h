#pragma once

#include <iostream>
#include <string>
#include "entities.h"

using namespace std;


// control(5.1. 등록 통계 출력)
class EmploymentStatUI;
class ShowEmploymentStat {
private:
    EmploymentCollection* employment_collection;
    ApplicationCollection* application_collection;
    EmploymentStatUI* ui;

    int run_statistics(const string& keyword, const string& id) const
    {
        int total = 0;

        for (int idx = 0; idx < employment_collection->get_total_employment_count(); idx++) {

            Employment* employment = employment_collection->getEmploymentByIndex(idx);

            // 주어진 키워드 업무에 대해
            // ID 동일한지, 키워드 동일한지 확인
            // 동일하면 통계 += 1
            if (employment->getCompanyName() == id && keyword == employment->getWork())
                total++;
        }

        // 통계 반환
        return total;
    }

public:
    ShowEmploymentStat(EmploymentCollection* employment_collection, ApplicationCollection* application_collection, EmploymentStatUI* ui) {
        this->employment_collection = employment_collection;
        this->application_collection = application_collection;
        this->ui = ui;
    }

    void runAllStatistics(string const& id);
};


// ui(5.1. 등록 통계 출력)
class EmploymentStatUI
{
private:
    ShowEmploymentStat* control;
    ofstream* out_stream;

public:
    EmploymentStatUI(EmploymentCollection* employment_collection, ApplicationCollection* application_collection)
    {
        out_stream = nullptr;
        control = new ShowEmploymentStat(employment_collection, application_collection, this);
    }

    void outputStatistics(const string& workKeyword, int total)
    {
        cout << "> " << workKeyword << " " << total << endl;
    }

    void startInterface(string const& logged_in_user_id, ofstream& out_fp)
    {
        out_stream = &out_fp;

        out_fp << "5.1. 지원 정보 통계" << endl;
        control->runAllStatistics(logged_in_user_id);
    }
};


inline void ShowEmploymentStat::runAllStatistics(string const& id)
{
    // EmploymentCollection에 등록된 전체 업무 키워드에 대해
    for (int idx = 0; idx < employment_collection->get_total_type_count(); idx++) {
        // EmploymentCollection에 getWorkTypesTotal() 정의 필요
        // 각 업무 키워드 마다
        string keyword = employment_collection->get_work_type_by_index(idx);    // EmploymentCollection에 getWorkTypeIdx(idx) 정의 필요

        // 해당 키워드와 유저 ID에 대한 통계 계산 후
        // 바운더리 클래스에게 해당 업무 키워드에 대한 통계 출력 위임
        ui->outputStatistics(keyword, run_statistics(keyword, id));
    }
}


// control(5.2. 지원 통계 출력)
class ApplicationStatUI;
class ShowApplicationStat {
private:
    EmploymentCollection* employment_collection;
    ApplicationCollection* application_collection;
    ApplicationStatUI* ui;

    int run_statistics(const string& keyword, const string& id) const
    {
        int total = 0;

        for (int idx = 0; idx < employment_collection->get_total_employment_count(); idx++) {

            Application* application = application_collection->getEmploymentByIndex(idx);

            // 주어진 키워드 업무에 대해
            // ID 동일한지, 키워드 동일한지 확인
            // 동일하면 통계 += 1
            if (application->get_company_name() == id && keyword == application->get_work_type())
                total++;
        }
        // 통계 반환
        return total;
    }

public:
    ShowApplicationStat(EmploymentCollection* employment_collection, ApplicationCollection* application_collection, ApplicationStatUI* ui) {
        this->employment_collection = employment_collection;
        this->application_collection = application_collection;
        this->ui = ui;
    }

    void runAllStatistics(string const& id);
};


// ui(5.2. 지원 통계 출력)
class ApplicationStatUI
{
private:
    ShowApplicationStat* control;
    ofstream* out_stream;

public:
    ApplicationStatUI(EmploymentCollection* employment_collection, ApplicationCollection* application_collection)
    {
        out_stream = nullptr;
        control = new ShowApplicationStat(employment_collection, application_collection, this);
    }

    void outputStatistics(const string& workKeyword, int total)
    {
        cout << "> " << workKeyword << " " << total << endl;
    }

    void startInterface(string const& logged_in_user_id, ofstream& out_fp)
    {
        out_stream = &out_fp;

        out_fp << "5.1. 지원 정보 통계" << endl;
        control->runAllStatistics(logged_in_user_id);
    }
};


inline void ShowApplicationStat::runAllStatistics(string const& id)
{
    // EmploymentCollection에 등록된 전체 업무 키워드에 대해
    for (int idx = 0; idx < employment_collection->get_total_type_count(); idx++) {
        // EmploymentCollection에 getWorkTypesTotal() 정의 필요
        // 각 업무 키워드 마다
        string keyword = employment_collection->get_work_type_by_index(idx);    // EmploymentCollection에 getWorkTypeIdx(idx) 정의 필요

        // 해당 키워드와 유저 ID에 대한 통계 계산 후
        // 바운더리 클래스에게 해당 업무 키워드에 대한 통계 출력 위임
        ui->outputStatistics(keyword, run_statistics(keyword, id));
    }
}

