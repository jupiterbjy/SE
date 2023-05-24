#pragma once


class EmploymentCollection {
private:
    Employment* employments[100]; //배열로 채용건수 선언
    int employments_total = 0;

    String* work_types[100]; //배열로 업무타입 선언
    int work_types_total = 0;

    bool check_if_work_type_exists(string keyword) {
        // 주어진 업무 타입이 이미 존재하는지 확인
        for (int idx = 0; idx < work_types_total; idx++)
            if (work_types[idx] == keyword)
                return true;

        return false;
    }
public:
    void add_employment(Employment employment) {
        // 업무 추가
        // 업무 키워드가 이미 존재하는지 확인
        // 존재하지 않을 시 업무 키워드 목록에 추가
        if (!check_if_work_type_exists(employment.keyword))
            work_types[work_types_total++] = employment.keyword;

        employment[employment_total++] = employment;
    }
    
    Employment* get_employment_by_index(int idx) {
        // 인덱스로 업무 가져옴
        return employment[idx];
    }

    // 전체 업무 수 반환
    int total_employments() { return employment_total; }

    string get_work_type_idx(int idx) {
        // 업무 키워드를 인덱스로 받아옴
        return employments[idx];
    }

    // 전체 업무 키워드 수 반환
    int total_work_type() { return work_types_total; }
};


class Boundary {
private:
    Control control;

public:
    void output_statistics(string work_keyword, int total) {
        // 컨트롤이 바운더리의 이 메소드 호출해 한 업무의 통계 출력
        cout << work_keyword << " " << total << endl;
    }
};


class Control {
private:
    EmploymentCollection collection;
    Boundary boundary;

    int run_statistics(string keyword, string id) {
        int total = 0;

        for (int idx = 0; idx < collection.employments_total; idx++) {
            // 모든 주어진 키워드 업무에 대해
            // ID 동일한지, 키워드 동일한지 확인
            // 동일하면 통계 += 1
            Employment* employment = collection.get_employment_by_index(idx);
            if (employment.id == id && keyword == employment.keyword)
                total += employment;

            // 통계 반환
            return total;
        }
    }

public:
    void run_all_statistics(string id) {
        // EmploymentCollection에 등록된 전체 업무 키워드에 대해
        for (int idx = 0; idx < collection.work_types_total; idx++) {
            // 각 업무 키워드 마다
            string keyword = collection.get_work_type_idx(idx);

            // 해당 키워드와 유저 ID에 대한 통계
            int count = run_statistics(keyword, id);

            // 바운더리 클래스에게 해당 업무 키워드에 대한 통계 출력 위임
            boundary.output_statistics(keyword, count);
        }
    }
};
