#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "global_register.h"

#define NUM_REGISTERS 10
#define REGISTER_SIZE 32

int register_num[NUM_REGISTERS][REGISTER_SIZE];

/*
typedef struct Registers {
    char Read_register1[6];  // 읽기 레지스터 1
    char Read_register2[6];  // 읽기 레지스터 2
    char Write_register[6];  // 쓰기 레지스터
    int Write_Data;  // 쓰기 데이터
    long Read_Data1;  // 읽기 데이터 1
    long Read_Data2;  // 읽기 데이터 2
} Registers;

typedef struct send_Data{
    int Data1;
    int Data2;
}sending_data;
*/

// 레지스터 정보 추출을 위한 함수
int r_format(int rs, int rt, int rd) {
    //Registers r_members;

    //sending_data sending_datas;

    // 레지스터 번호를 위한 가짜 데이터
    register_num[1][0] = 1;
    register_num[2][0] = 2;

    // 이진 문자열에서 레지스터 정보 추출
    /*
    slice(0, 4, r_members.Read_register1, bin);  // 읽기 레지스터 1 추출
    slice(5, 9, r_members.Read_register2, bin);  // 읽기 레지스터 2 추출
    slice(10, 14, r_members.Write_register, bin);  // 쓰기 레지스터 추출
    

    // 이진 레지스터 값을 십진수로 변환
    r_members.Read_Data1 = register_num[strtol(r_members.Read_register1, NULL, 2)][0];  // 읽기 레지스터 1 값을 십진수로 변환
    r_members.Read_Data2 = register_num[strtol(r_members.Read_register2, NULL, 2)][0];  // 읽기 레지스터 2 값을 십진수로 변환

    // 추출된 레지스터 정보 출력
    
    printf("rs : %s\n", r_members.Read_register1);  // 읽기 레지스터 1 출력
    printf("rt : %s\n", r_members.Read_register2);  // 읽기 레지스터 2 출력
    printf("rd : %s\n", r_members.Write_register);  // 쓰기 레지스터 출력
    

    printf("rs 값: %ld\n", r_members.Read_Data1);  // 읽기 레지스터 1 값 출력
    printf("rt 값: %ld\n", r_members.Read_Data2);  // 읽기 레지스터 2 값 출력
    */

    //sending_datas.Data1 = r_members.Read_Data1;
    //sending_datas.Data2 = r_members.Read_Data2;

    ALU(rs,rt);

    return EXIT_SUCCESS;
}

// ALU 연산 수행을 위한 함수
void ALU(int data1, int data2) {
    // ALU 연산: 덧셈
    int result = data1 + data2;  // data1과 data2를 더함
    printf("ALU 결과: %d\n", result);  // ALU 결과 출력
}

// 문자열에서 일부를 추출하는 함수
void slice(int start, int end, char *dst, char *src) {
    for (int i = start; i <= end; i++) {
        dst[i - start] = src[i];  // 원본에서 목적지로 문자 복사
    }
    dst[end - start + 1] = '\0';  // 목적지 문자열에 널 종료 추가
}

int main() {

    int data = extract_register_info("0000100010");  // 이진 문자열로부터 레지스터 정보 추출

    ALU(data.Data1, data.Data2);

    return 0;
}
