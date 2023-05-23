// 헤더 선언 
#include <stdio.h> 
#include <string.h>
#include "entities.h"

// 상수 선언
#define MAX_STRING 32
#define INPUT_FILE_NAME "input.txt“ 
#define OUTPUT_FILE_NAME "output.txt"

// 함수 선언
void doTask();
void join();
void withdrawal(User* loginUser);
void statics_output(User *loginUser, int loginUserType);
void program_exit();

// 변수 선언
FILE* in_fp, *out_fp;

int main() 
{
    // 파일 입출력을 위한 초기화
    FILE* in_fp = fopen(INPUT_FILE_NAME, "r+"); FILE* out_fp = fopen(OUTPUT_FILE_NAME, "w+");
    ...
    doTask();
    ...
    return 0; 
}

void doTask() 
{
    // 메뉴 파싱을 위한 level 구분을 위한 변수 
    int menu_level_1 = 0, menu_level_2 = 0; 
    int is_program_exit = 0;
    User* loginUser;
    int loginUserType = 0; // 0: 로그인 회원 없음 1: 회사 회원, 2: 일반 회원

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
                        join();
                        break; 
                    }
                    case 2: // "1.2. 회원탈퇴" 메뉴 부분
                    {
                        withdrawal(loginUser);
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
                        break;
                    }
                    case 2:
                    {
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
                        statics_output(loginUser, loginUserType);   // "5.1. 지원 정보 통계"
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
                        ..
                        program_exit(); 
                        is_program_exit = 1; 
                        break;
                    }
                }
            }
        }
    ....
    }
    return
}

void join() {
    /* !!!!!!! 중요
    * 단순히 파일을 통해 입출력하는 방법을 보이기 위한 코드이므로 이 함수에서 그대로 사용하면 안됨. * control 및 boundary class를 이용해서 해당 기능이 구현되도록 해야 함.
    */
    char user_type[MAX_STRING], name[MAX_STRING], SSN[MAX_STRING], 
        address[MAX_STRING], ID[MAX_STRING], password[MAX_STRING];
    // 입력 형식 : 이름, 주민번호, ID, Password를 파일로부터 읽음 
    fscanf(in_fp, "%s %s %s %s", name, SSN, ID, password);
    
    // 해당 기능 수행 ...
    // 출력 형식
    fprintf(out_fp, "1.1. 회원가입\n");
    fprintf(out_fp, "%s %s %s %s\n", name, SSN, ID, password);
}

void UserCollection::deleteUserByID(char[] ID);

// 회원 탈퇴
void withdrawal(User* loginUser) {
    // 해당 기능 수행
    UserManager.delete_user_by_id(loginUser->get_id());
    // 출력 형식
    fprintf(out_fp, "1.2. 회원탈퇴\n");
    fprintf(out_fp."%s\n", loginUser->get_id());
}

// 통계 출력
void statics_output(User* loginUser, int loginUserType) {
    // 출력 형식
    fprintf(out_fp, "5.1. 지원 정보 통계\n");
    // 회사 회원 -> 등록 통계 출력
    if (loginUserType == 1) {
        EmplementCollection.registration_statics_output();
    } else if (loginUserType == 2) {
        ApplicationCollection.application_statics_output();
    }
}


void program_exit() 
{
    .... 
}