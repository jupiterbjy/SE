#include <fstream>

#include "employment_management_system.h"
#include "application.h"
#include "statistics_output_system.h"
#include "user_management_system.h"


// 상수 선언
#define MAX_STRING 32
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

typedef enum
{
	NOT_LOGGED_IN,
    COMPANY_USER,
    COMMON_USER

} LoginState;


// 함수 선언
void doTask(const ifstream& in_fp, ofstream& out_fp);
void program_exit();


int main() 
{
    // prep file
    ifstream in_fp;
    ofstream out_fp;

    // open file
    in_fp.open(INPUT_FILE_NAME, ios_base::in);
    out_fp.open(OUTPUT_FILE_NAME, ios_base::out);

    doTask(in_fp, out_fp);

    // close file
    in_fp.close();
    out_fp.close();

    return 0; 
}

void doTask(ifstream& in_fp, ofstream& out_fp) 
{
    // 메뉴 파싱을 위한 level 구분을 위한 변수 
    int menu_level_1, menu_level_2, menu_level_3;
    bool is_running = true;

    // Instantiate collections
    UserManager user_manager;
    EmploymentCollection employment_collection;
    ApplicationCollection application_collection;

    // Instantiate controls & boundaries
    // User management system
    AddCompanyUserUI add_company_ui(&user_manager);
    AddCommonUserUI add_common_ui(&user_manager);
    LoginUI login_ui(&user_manager);
    LogoutUI logout_ui(&user_manager);
    UserWithdrawalUI user_withdrawal_ui(&user_manager);

    // Employment Management system
    EmploymentAddUI employment_add_ui(&employment_collection);
    ShowEmploymentListUI employment_list_ui(&employment_collection);

    // statistics system
    ApplicationStatUI application_stat_ui(&application_collection);
    EmploymentStatUI employment_stat_ui(&employment_collection);

    // Application Management system
    NewApplicationUI apply_now_ui;
    CancelApplicationUI application_cancel_ui(&application_collection);
    ApplicationCheckUI application_check_ui(&application_collection);
    CompanyNameSearchUI company_search_ui(&application_collection);


    // Keep logged in user's info - default is empty, so safe to init like this
	string logged_in_user_id;
    LoginState state = NOT_LOGGED_IN;

    // Run code
    while(is_running) 
    {
        // cout << "[DEBUG] doTask is running" << endl;
        // 입력파일에서 메뉴 숫자 2개를 읽기
        in_fp >> menu_level_1 >> menu_level_2;
        
        // Switching Start
        switch(menu_level_1)
        {
            case 1: 
            {
                switch(menu_level_2) 
                {
                    case 1: // 1.1.1. / 1.1.2. 회원가입
                    {
                        in_fp >> menu_level_3;
                        if (menu_level_3 == 0)
                            add_company_ui.start_interface(in_fp, out_fp);
                        else
                            add_common_ui.start_interface(in_fp, out_fp);
                        
                        break; 
                    }
                    case 2: // 1.2. 회원탈퇴
                    {
                        user_withdrawal_ui.startInterface(logged_in_user_id, out_fp);
                        break; 
                    }
                }
            }
            case 2:
            {
                switch(menu_level_2) 
                {
                    case 1: // 2.1. Login
                    {
                        logged_in_user_id = login_ui.start_interface(in_fp, out_fp);
                        break;
                    }
                    case 2: // 2.2. Logout
                    {
                        // Just in case, check if empty
                        if (logged_in_user_id.empty())
                            break;

                        logout_ui.start_interface(logged_in_user_id, out_fp);
                        logged_in_user_id = "";
                        break;
                    }
                }
            }
            case 3:
            {
                switch(menu_level_2)
                {
                    case 1: // 3.1. 채용 정보 등록
                    {
                        employment_add_ui.start_interface(logged_in_user_id, in_fp, out_fp);
                        break;
                    }
                    case 2: // 3.2. 등록된 채용 정보 조회
                    {
                        employment_list_ui.start_interface(logged_in_user_id, out_fp);
                        break;
                    }
                }
            }
            case 4:
            {
                switch(menu_level_2)
                {
                    case 1: // 4.1. 채용 정보 검색
                    {
                        company_search_ui.start_interface(in_fp, out_fp);
                        break;
                    }
                    case 2: // 4.2. 채용 지원
                    {
                        apply_now_ui.startInterface(logged_in_user_id, in_fp, out_fp);
                        break;
                    }
                    case 3: // 4.3. 지원 정보 조회
                    {
                        application_check_ui.startInterface(logged_in_user_id, out_fp);
                        break;
                    }
                    case 4: // 4.4. 지원 취소
                    {
                        application_cancel_ui.startInterface(logged_in_user_id, in_fp, out_fp);
                        break;
                    }
                }
            }
            case 5:
            {
                switch(menu_level_2)
                {
                    case 1: // "5.1. 지원 정보 통계"
                    {
                        
                        employment_stat_ui.startInterface(logged_in_user_id, out_fp);
                        break;
                    }
                }
            }
            case 6: 
            {
                switch(menu_level_2) 
                {
                    case 1: // "6.1. 종료" 메뉴 부분 
                    {
                        program_exit(); 
                        is_running = false; 
                        break;
                    }
                }
            }
        }
    }
}


void program_exit()
{
    cout << "6.1. 종료" << endl;
}
