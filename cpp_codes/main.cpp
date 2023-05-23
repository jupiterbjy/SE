// 헤더 선언 
//#include <stdio.h> 
//#include <string>
#include "entities.h"

// 상수 선언
#define MAX_STRING 32
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

// 함수 선언
void doTask();
//void join();
//void withdrawal(User* loginUser);
//void statics_output(User *loginUser, int loginUserType);
//void program_exit();
void aaddEmployment();
void sshowEmploymentList();

// 변수 선언
FILE* in_fp, *out_fp;

int main() 
{
    // 파일 입출력을 위한 초기화
    FILE* out_fp = fopen(OUTPUT_FILE_NAME, "w+");
    FILE* in_fp = fopen("input.txt", "r+"); 
    doTask();
    return 0; 
}

void doTask() 
{
    // 메뉴 파싱을 위한 level 구분을 위한 변수 
    int menu_level_1 = 0, menu_level_2 = 0; 
    int is_program_exit = 0;
    //User* loginUser;
    //int loginUserType = 0; // 0: 로그인 회원 없음 1: 회사 회원, 2: 일반 회원

    while(!is_program_exit) 
    {
        // 입력파일에서 메뉴 숫자 2개를 읽기
        fscanf(in_fp, "%d %d ", &menu_level_1, &menu_level_2);

        // 메뉴 구분 및 해당 연산 수행 
        switch(menu_level_1)
        {
            case 1: 
            {
                switch(menu_level_2) 
                {
                    case 1: // "1.1. 회원가입“ 메뉴 부분 
                    {
                        // join() 함수에서 해당 기능 수행 
                        //join();
                        break; 
                    }
                    case 2: // "1.2. 회원탈퇴" 메뉴 부분
                    {
                        //withdrawal(loginUser);
                        break; 
                    }
                }
            }
            case 2:
            {
                switch(menu_level_2) 
                {
                    case 1:
                    {
                        break;
                    }
                    case 2:
                    {
                        break;
                    }
                }
            }
            case 3:
            {
                switch(menu_level_2)
                {
                    case 1: // "3.1. 채용 정보 등록"
                    {
                        aaddEmployment();
                        break;
                    }
                    case 2:
                    {
                        sshowEmploymentList();
                        break;
                    }
                }
            }
            case 4:
            {
                switch(menu_level_2)
                {
                    case 1:
                    {
                        break;
                    }
                    case 2:
                    {
                        break;
                    }
                    case 3:
                    {
                        break;
                    }
                    case 4:
                    {
                        break;
                    }
                }
            }
            case 5:
            {
                switch(menu_level_2)
                {
                    case 1:
                    {
                        //statics_output(loginUser, loginUserType);   // "5.1. 지원 정보 통계"
                        break;
                    }
                }
            }
            case 7: 
            {
                switch(menu_level_2) 
                {
                    case 1: // "6.1. 종료“ 메뉴 부분 
                    {
                        //program_exit(); 
                        //is_program_exit = 1; 
                        break;
                    }
                }
            }
        }
    }
    return;
}

void aaddEmployment() {
    EmploymentAdd employmentAdd;
    employmentAdd.addEmployment();
}

void sshowEmploymentList() {
   ShowEmploymentList showEmploymentList;
   showEmploymentList.showEmploymentInfo();
}
