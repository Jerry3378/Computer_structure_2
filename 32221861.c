#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* FILE NAME: register.h
 * Description: This header file contains the declarations of global variables representing registers.
 * These registers are used for various purposes such as storing return values, temporary data,
 * or saved values during program execution.
 */

#define NUM_REGISTERS 32
#define REGISTER_SIZE 32


// Define op codes for different instruction types
#define R_TYPE_OP "000000"
#define J_TYPE_OP "000010"
#define J_TYPE_OP_JAL "000011"
#define I_TYPE_OP_BEQ "000100"
#define I_TYPE_OP_BNE "000101"
#define I_TYPE_OP_ADDI "001000"
#define I_TYPE_OP_ADDIU "001001"
#define I_TYPE_OP_SLTI "001010"
#define I_TYPE_OP_SLTIU "001011"
#define I_TYPE_OP_ANDI "001100"
#define I_TYPE_OP_ORI "001101"
#define I_TYPE_OP_XORI "001110"
#define I_TYPE_OP_LUI "001111"
#define I_TYPE_OP_LB "100000"
#define I_TYPE_OP_LH "100001"
#define I_TYPE_OP_LWL "100010"
#define I_TYPE_OP_LW "100011"
#define I_TYPE_OP_LBU "100100"
#define I_TYPE_OP_LHU "100101"
#define I_TYPE_OP_LWR "100110"
#define I_TYPE_OP_SB "101000"
#define I_TYPE_OP_SH "101001"
#define I_TYPE_OP_SWL "101010"
#define I_TYPE_OP_SW "101011"
#define I_TYPE_OP_SWR "101110"
#define I_TYPE_OP_LWC1 "110001"
#define I_TYPE_OP_LWC2 "110010"
#define I_TYPE_OP_SWC1 "111001"
#define I_TYPE_OP_SWC2 "111010"

// Define register names for easy reference
#define zero "00000"
#define at "00001"
#define v0 "00010"
#define v1 "00011"
#define a0 "00100"
#define a1 "00101"
#define a2 "00110"
#define a3 "00111"
#define t0 "01000"
#define t1 "01001"
#define t2 "01010"
#define t3 "01011"
#define t4 "01100"
#define t5 "01101"
#define t6 "01110"
#define t7 "01111"
#define s0 "10000"
#define s1 "10001"
#define s2 "10010"
#define s3 "10011"
#define s4 "10100"
#define s5 "10101"
#define s6 "10110"
#define s7 "10111"
#define t8 "11000"
#define t9 "11001"
#define k0 "11010"
#define k1 "11011"
#define gp "11100"
#define sp "11101"
#define fp "11110"
#define ra "11111"

// Define funct values as binary strings for MIPS R-type instructions
#define FUNCT_ADD   "100000"
#define FUNCT_ADDU  "100001"
#define FUNCT_SUB   "100010"
#define FUNCT_SUBU  "100011"
#define FUNCT_AND   "100100"
#define FUNCT_OR    "100101"
#define FUNCT_XOR   "100110"
#define FUNCT_NOR   "100111"
#define FUNCT_SLT   "101010"
#define FUNCT_SLTU  "101011"
#define FUNCT_SLL   "000000"
#define FUNCT_SRL   "000010"
#define FUNCT_SRA   "000011"
#define FUNCT_JR    "001000"
#define FUNCT_JALR  "001001"

///////////////////////////ALUop Set///////////////////////////////////
#define ALU_AND "0000"
#define ALU_OR  "0001"
#define ALU_ADD "0010"
#define ALU_SUB "0110"
#define ALU_SLT "0111"
#define ALU_NOR "1100"
///////////////////////////////////////////////////////////////////////

/* Global variable for registers
 * Each element of the array represents a specific register
 * 0 is zero register (always returns 0)
 * 1 is at (assembler temporary)
 * 2~3 are v0~v1 (return value)
 * 4~7 are a0~a3 (arguments)
 * 8~15 are t0~t7 (temporary)
 * 16~23 are s0~s7 (saved)
 * 24~25 are t8~t9 (temporary)
 * 26 is k0 (reserved for kernel)
 * 27 is k1 (reserved for kernel)
 * 28 is gp (global pointer)
 * 29 is sp (stack pointer)
 * 30 is fp (frame pointer)
 * 31 is ra (return address)
 */

int register_num[NUM_REGISTERS][REGISTER_SIZE];
/////////////////////////////////////////////////////

// this structrue type is only for display the instruction/////////////
typedef struct Field{
    char op[7];
    char rs[6];
    char rt[6];
    char rd[6];     //only for R-format
    char shamt[6];  //only for R-format
    char funct[7];  //only for R-format
    char immediate[17];  //only for I-format
    char address[27];    //only for J-format
}Field_register;
/////////////////////////////////////////////////////////////////////


//this structure type is only for set the registers/////////////////

typedef struct Registers {
    char Read_register1[6];  // 읽기 레지스터 1
    char Read_register2[6];  // 읽기 레지스터 2
    char Write_register[6];  // 쓰기 레지스터
    int Write_Data;  // 쓰기 데이터
    long Read_Data1;  // 읽기 데이터 1
    long Read_Data2;  // 읽기 데이터 2
} registers;

////////////////////////////////////////////////////////////////////

//this structure type is only for set the control signal////////////
typedef struct control_signal{
    int RegDst;     //decision the destination register (R-format : 1, I-format : 0)
    int ALUSrc;     //ALU 두번째 피연산자가 레지스터인지 즉시 값인지 결정(I-format : 1, R-format : 0) 
    int PCSrc;      //pc가 0이면 +4해서 연산, 1이면 분기연산
    int MemtoReg;   //메모리에서 읽은 데이터를 레지스터에 쓸지 여부 결정(로드 명령어일때 1)
    int RegWrite;   //레지스터 파일에 쓰기 활성화 신호(로드와 R-format)
    int MemRead;    //데이터 메모리 읽기 활성화 신호 (로드 명령어 일시 1)
    int MemWrite;   //데이터 메모리 쓰기 활성화 신호 (스토어 명령어일때 1)
    int Branch;     //분기 명령어 활성화 신호
    char ALUOp[5];  //ALU가 수행할 연산을 결정(ex: ADD,SUB,AND,OR등)

}control_signal;

///////////////////instruction_fetch part///////////////////////////


void hex_to_bin(char *hex_code ,char *bin);
void instruction_decode(char *bin_code);

int instruction_fetch(char *file_name) {
    FILE *file;
    //const char *filename = "sum.bin";
    unsigned char buffer[4];
    size_t bytesRead;
    int i;

    char hex[9] = {0};

    char bin[33] = {0};

    int count = 0;

    // 파일 열기 (바이너리 모드로)
    file = fopen(file_name, "rb");
    if (file == NULL) {
        perror("파일을 열 수 없습니다");
        return EXIT_FAILURE;
    }

    /*
    fseek(file, 0, SEEK_END); // 파일 끝으로 이동
    long file_size = ftell(file); // 파일 크기 확인
    fseek(file, 0, SEEK_SET); // 파일의 처음으로 이동

    printf("%ld",file_size);

    */

    // 파일에서 바이트 읽기
    while(bytesRead = fread(buffer, sizeof(unsigned char), sizeof(buffer), file)){
        
    if (bytesRead == 0) {
        perror("파일에서 데이터를 읽을 수 없습니다");
        fclose(file);
        return EXIT_FAILURE;
    }

    printf("[instruction Fetch] ");

    // 읽어온 바이트 값 출력
    
    for (i = 0; i < bytesRead; i++) {
        sprintf(hex+i * 2,"%02x",buffer[i]);   //hex배열을 buffer에서 불러온 02x형태의 문자열로 저장
    }
    
    printf("0x%s ",hex);

    for (i = 0; i < sizeof(hex)-1; i++) {
        hex_to_bin(hex+i,bin+i*4);
    }
    
    printf("(PC=%#08x)\n", count*4);

    instruction_decode(bin);

    memset(hex,0,sizeof(hex));
    memset(bin,0,sizeof(bin));

    }
    
    // 파일 닫기
    fclose(file);

    return EXIT_SUCCESS;
}

void hex_to_bin(char *hex_code ,char* bin){

    switch(*hex_code) {
        case '0': strcpy(bin, "0000"); break;
        case '1': strcpy(bin, "0001"); break;
        case '2': strcpy(bin, "0010"); break;
        case '3': strcpy(bin, "0011"); break;
        case '4': strcpy(bin, "0100"); break;
        case '5': strcpy(bin, "0101"); break;
        case '6': strcpy(bin, "0110"); break;
        case '7': strcpy(bin, "0111"); break;
        case '8': strcpy(bin, "1000"); break;
        case '9': strcpy(bin, "1001"); break;
        case 'A': case 'a': strcpy(bin, "1010"); break;
        case 'B': case 'b': strcpy(bin, "1011"); break;
        case 'C': case 'c': strcpy(bin, "1100"); break;
        case 'D': case 'd': strcpy(bin, "1101"); break;
        case 'E': case 'e': strcpy(bin, "1110"); break;
        case 'F': case 'f': strcpy(bin, "1111"); break;
        case 0:  break;
        default: strcpy(bin, "????"); break; // 오류 처리
    }

}
/////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////

void slice(int start, int end, char *dst, char *src) {
    for (int i = start; i <= end; i++) {
        dst[i - start] = src[i];  // 원본에서 목적지로 문자 복사
    }
    dst[end - start + 1] = '\0';  // 목적지 문자열에 널 종료 추가
}

void instruction_decode(char *bin_code) {

    int op_flag = 0;
    char op[6];
    char r1[5];
    char r2[5];
    char r3[5];   

    char op_compare[7];

    Field_register R = {0};

    control_signal signal = {-1};

    slice(0,5,op_compare,bin_code);
    
    if (strcmp(op_compare,"000000") == 0)
    {
        op_flag = 1;
        slice(0,5,R.op,bin_code);
        slice(6,10,R.rs,bin_code);    //rs
        slice(11,15,R.rt,bin_code);   //rt
        slice(16,20,R.rd,bin_code);   //rd
        slice(21,25,R.shamt,bin_code);   //shamt
        slice(26,31,R.funct,bin_code);   //funct
    }else if (strcmp(op_compare,"000010") == 0)
    {
        op_flag = 2;
        slice(0,5,R.op,bin_code);
        slice(6,31,R.address,bin_code);
    }else if (strcmp(op_compare,"000011") == 0)
    {
        op_flag = 3;
        slice(0,5,R.op,bin_code);
        slice(6,31,R.address,bin_code);
    }else{
        op_flag = 4;
        slice(0,5,R.op,bin_code);
        slice(6,10,R.rs,bin_code);    //rs
        slice(11,15,R.rt,bin_code);   //rt
        slice(16,31,R.immediate,bin_code);    //int
        
    }
    
    printf("[Instruction Decode] ");

    //////////////////////////setting register//////////////////////////////////////////////
    //r1(rs)

    if (strcmp(r1, zero) == 0) {
        strcpy(r1, "zero");
    } else if (strcmp(R.rs, at) == 0) {
        strcpy(r1, "at");
    } else if (strcmp(R.rs, v0) == 0) {
        strcpy(r1, "v0");
    } else if (strcmp(R.rs, v1) == 0) {
        strcpy(r1, "v1");
    } else if (strcmp(R.rs, a0) == 0) {
        strcpy(r1, "a0");
    } else if (strcmp(R.rs, a1) == 0) {
        strcpy(r1, "a1");
    } else if (strcmp(R.rs, a2) == 0) {
        strcpy(r1, "a2");
    } else if (strcmp(R.rs, a3) == 0) {
        strcpy(r1, "a3");
    } else if (strcmp(R.rs, t0) == 0) {
        strcpy(r1, "t0");
    } else if (strcmp(R.rs, t1) == 0) {
        strcpy(r1, "t1");
    } else if (strcmp(R.rs, t2) == 0) {
        strcpy(r1, "t2");
    } else if (strcmp(R.rs, t3) == 0) {
        strcpy(r1, "t3");
    } else if (strcmp(R.rs, t4) == 0) {
        strcpy(r1, "t4");
    } else if (strcmp(R.rs, t5) == 0) {
        strcpy(r1, "t5");
    } else if (strcmp(R.rs, t6) == 0) {
        strcpy(r1, "t6");
    } else if (strcmp(R.rs, t7) == 0) {
        strcpy(r1, "t7");
    } else if (strcmp(R.rs, s0) == 0) {
        strcpy(r1, "s0");
    } else if (strcmp(R.rs, s1) == 0) {
        strcpy(r1, "s1");
    } else if (strcmp(R.rs, s2) == 0) {
        strcpy(r1, "s2");
    } else if (strcmp(R.rs, s3) == 0) {
        strcpy(r1, "s3");
    } else if (strcmp(R.rs, s4) == 0) {
        strcpy(r1, "s4");
    } else if (strcmp(R.rs, s5) == 0) {
        strcpy(r1, "s5");
    } else if (strcmp(R.rs, s6) == 0) {
        strcpy(r1, "s6");
    } else if (strcmp(R.rs, s7) == 0) {
        strcpy(r1, "s7");
    } else if (strcmp(R.rs, t8) == 0) {
        strcpy(r1, "t8");
    } else if (strcmp(R.rs, t9) == 0) {
        strcpy(r1, "t9");
    } else if (strcmp(R.rs, k0) == 0) {
        strcpy(r1, "k0");
    } else if (strcmp(R.rs, k1) == 0) {
        strcpy(r1, "k1");
    } else if (strcmp(R.rs, gp) == 0) {
        strcpy(r1, "gp");
    } else if (strcmp(R.rs, sp) == 0) {
        strcpy(r1, "sp");
    } else if (strcmp(R.rs, fp) == 0) {
        strcpy(r1, "fp");
    } else if (strcmp(R.rs, ra) == 0) {
        strcpy(r1, "ra");
    }
    /////////////////////////////////////////////////////

    ////////////////////////r2(rt)//////////////////////
    if (strcmp(R.rt, zero) == 0) {
        strcpy(r2, "zero");
    } else if (strcmp(R.rt, at) == 0) {
        strcpy(r2, "at");
    } else if (strcmp(R.rt, v0) == 0) {
        strcpy(r2, "v0");
    } else if (strcmp(R.rt, v1) == 0) {
        strcpy(r2, "v1");
    } else if (strcmp(R.rt, a0) == 0) {
        strcpy(r2, "a0");
    } else if (strcmp(R.rt, a1) == 0) {
        strcpy(r2, "a1");
    } else if (strcmp(R.rt, a2) == 0) {
        strcpy(r2, "a2");
    } else if (strcmp(R.rt, a3) == 0) {
        strcpy(r2, "a3");
    } else if (strcmp(R.rt, t0) == 0) {
        strcpy(r2, "t0");
    } else if (strcmp(R.rt, t1) == 0) {
        strcpy(r2, "t1");
    } else if (strcmp(R.rt, t2) == 0) {
        strcpy(r2, "t2");
    } else if (strcmp(R.rt, t3) == 0) {
        strcpy(r2, "t3");
    } else if (strcmp(R.rt, t4) == 0) {
        strcpy(r2, "t4");
    } else if (strcmp(R.rt, t5) == 0) {
        strcpy(r2, "t5");
    } else if (strcmp(R.rt, t6) == 0) {
        strcpy(r2, "t6");
    } else if (strcmp(R.rt, t7) == 0) {
        strcpy(r2, "t7");
    } else if (strcmp(R.rt, s0) == 0) {
        strcpy(r2, "s0");
    } else if (strcmp(R.rt, s1) == 0) {
        strcpy(r2, "s1");
    } else if (strcmp(R.rt, s2) == 0) {
        strcpy(r2, "s2");
    } else if (strcmp(R.rt, s3) == 0) {
        strcpy(r2, "s3");
    } else if (strcmp(R.rt, s4) == 0) {
        strcpy(r2, "s4");
    } else if (strcmp(R.rt, s5) == 0) {
        strcpy(r2, "s5");
    } else if (strcmp(R.rt, s6) == 0) {
        strcpy(r2, "s6");
    } else if (strcmp(R.rt, s7) == 0) {
        strcpy(r2, "s7");
    } else if (strcmp(R.rt, t8) == 0) {
        strcpy(r2, "t8");
    } else if (strcmp(R.rt, t9) == 0) {
        strcpy(r2, "t9");
    } else if (strcmp(R.rt, k0) == 0) {
        strcpy(r2, "k0");
    } else if (strcmp(R.rt, k1) == 0) {
        strcpy(r2, "k1");
    } else if (strcmp(R.rt, gp) == 0) {
        strcpy(r2, "gp");
    } else if (strcmp(R.rt, sp) == 0) {
        strcpy(r2, "sp");
    } else if (strcmp(R.rt, fp) == 0) {
        strcpy(r2, "fp");
    } else if (strcmp(R.rt, ra) == 0) {
        strcpy(r2, "ra");
    }
    ///////////////////////////////////////////////
    ///////////////////////////////////////////////////////////


    long address = 0;
    int immediate = 0;

    if (op_flag == 1)
    {
        printf("Type: R,");
        
        if (strcmp(R.funct, FUNCT_ADD) == 0) {
            strcpy(op, "ADD");
        } else if (strcmp(R.funct, FUNCT_ADDU) == 0) {
            strcpy(op, "ADDU");
        } else if (strcmp(R.funct, FUNCT_SUB) == 0) {
            strcpy(op, "SUB");
        } else if (strcmp(R.funct, FUNCT_SUBU) == 0) {
            strcpy(op, "SUBU");
        } else if (strcmp(R.funct, FUNCT_AND) == 0) {
            strcpy(op, "AND");
        } else if (strcmp(R.funct, FUNCT_OR) == 0) {
            strcpy(op, "OR");
        } else if (strcmp(R.funct, FUNCT_XOR) == 0) {
            strcpy(op, "XOR");
        } else if (strcmp(R.funct, FUNCT_NOR) == 0) {
            strcpy(op, "NOR");
        } else if (strcmp(R.funct, FUNCT_SLT) == 0) {
            strcpy(op, "SLT");
        } else if (strcmp(R.funct, FUNCT_SLTU) == 0) {
            strcpy(op, "SLTU");
        } else if (strcmp(R.funct, FUNCT_SLL) == 0) {
            strcpy(op, "SLL");
        } else if (strcmp(R.funct, FUNCT_SRL) == 0) {
            strcpy(op, "SRL");
        } else if (strcmp(R.funct, FUNCT_SRA) == 0) {
            strcpy(op, "SRA");
        } else if (strcmp(R.funct, FUNCT_JR) == 0) {
            strcpy(op, "JR");
        } else if (strcmp(R.funct, FUNCT_JALR) == 0) {
            strcpy(op, "JALR");
        } else {
            strcpy(op, "ERR");
        }


    //////////////////////r3(rd)///////////////////
        if (strcmp(R.rd, zero) == 0) {
            strcpy(r3, "zero");
        } else if (strcmp(R.rd, at) == 0) {
            strcpy(r3, "at");
        } else if (strcmp(R.rd, v0) == 0) {
            strcpy(r3, "v0");
        } else if (strcmp(R.rd, v1) == 0) {
            strcpy(r3, "v1");
        } else if (strcmp(R.rd, a0) == 0) {
            strcpy(r3, "a0");
        } else if (strcmp(R.rd, a1) == 0) {
            strcpy(r3, "a1");
        } else if (strcmp(R.rd, a2) == 0) {
            strcpy(r3, "a2");
        } else if (strcmp(R.rd, a3) == 0) {
            strcpy(r3, "a3");
        } else if (strcmp(R.rd, t0) == 0) {
            strcpy(r3, "t0");
        } else if (strcmp(R.rd, t1) == 0) {
            strcpy(r3, "t1");
        } else if (strcmp(R.rd, t2) == 0) {
            strcpy(r3, "t2");
        } else if (strcmp(R.rd, t3) == 0) {
            strcpy(r3, "t3");
        } else if (strcmp(R.rd, t4) == 0) {
            strcpy(r3, "t4");
        } else if (strcmp(R.rd, t5) == 0) {
            strcpy(r3, "t5");
        } else if (strcmp(R.rd, t6) == 0) {
            strcpy(r3, "t6");
        } else if (strcmp(R.rd, t7) == 0) {
            strcpy(r3, "t7");
        } else if (strcmp(R.rd, s0) == 0) {
            strcpy(r3, "s0");
        } else if (strcmp(R.rd, s1) == 0) {
            strcpy(r3, "s1");
        } else if (strcmp(R.rd, s2) == 0) {
            strcpy(r3, "s2");
        } else if (strcmp(R.rd, s3) == 0) {
            strcpy(r3, "s3");
        } else if (strcmp(R.rd, s4) == 0) {
            strcpy(r3, "s4");
        } else if (strcmp(R.rd, s5) == 0) {
            strcpy(r3, "s5");
        } else if (strcmp(R.rd, s6) == 0) {
            strcpy(r3, "s6");
        } else if (strcmp(R.rd, s7) == 0) {
            strcpy(r3, "s7");
        } else if (strcmp(R.rd, t8) == 0) {
            strcpy(r3, "t8");
        } else if (strcmp(R.rd, t9) == 0) {
            strcpy(r3, "t9");
        } else if (strcmp(R.rd, k0) == 0) {
            strcpy(r3, "k0");
        } else if (strcmp(R.rd, k1) == 0) {
            strcpy(r3, "k1");
        } else if (strcmp(R.rd, gp) == 0) {
            strcpy(r3, "gp");
        } else if (strcmp(R.rd, sp) == 0) {
            strcpy(r3, "sp");
        } else if (strcmp(R.rd, fp) == 0) {
            strcpy(r3, "fp");
        } else if (strcmp(R.rd, ra) == 0) {
            strcpy(r3, "ra");
        }
    /////////////////////////////////////////////////

    }
    else if (op_flag == 2)
    {
        printf("Type: J,");
        strcpy(op, "J");
        address = strtol(R.address,NULL,2);
    }else if (op_flag == 3)
    {
        printf("Type: J, ");
        strcpy(op, "Jal");
        address = strtol(R.address,NULL,2);
    }else{

        if (strcmp(R.op, I_TYPE_OP_BEQ) == 0) {
            printf("Type: I,");
            strcpy(op, "BEQ");
        } else if (strcmp(R.op, I_TYPE_OP_BNE) == 0) {
            printf("Type: I,");
            strcpy(op, "BNE");
        } else if (strcmp(R.op, I_TYPE_OP_ADDI) == 0) {
            printf("Type: I,");
            strcpy(op, "ADDI");
        } else if (strcmp(R.op, I_TYPE_OP_ADDIU) == 0) {
            printf("Type: I,");
            strcpy(op, "ADDIU");
        } else if (strcmp(R.op, I_TYPE_OP_SLTI) == 0) {
            printf("Type: I,");
            strcpy(op, "SLTI");
        } else if (strcmp(R.op, I_TYPE_OP_SLTIU) == 0) {
            printf("Type: I,");
            strcpy(op, "SLTIU");
        } else if (strcmp(R.op, I_TYPE_OP_ANDI) == 0) {
            printf("Type: I,");
            strcpy(op, "ANDI");
        } else if (strcmp(R.op, I_TYPE_OP_ORI) == 0) {
            printf("Type: I,");
            strcpy(op, "ORI");
        } else if (strcmp(R.op, I_TYPE_OP_XORI) == 0) {
            printf("Type: I,");
            strcpy(op, "XORI");
        } else if (strcmp(R.op, I_TYPE_OP_LUI) == 0) {
            printf("Type: I,");
            strcpy(op, "LUI");
        } else if (strcmp(R.op, I_TYPE_OP_LB) == 0) {
            printf("Type: I,");
            strcpy(op, "LB");
        } else if (strcmp(R.op, I_TYPE_OP_LH) == 0) {
            printf("Type: I,");
            strcpy(op, "LH");
        } else if (strcmp(R.op, I_TYPE_OP_LWL) == 0) {
            printf("Type: I,");
            strcpy(op, "LWL");
        } else if (strcmp(R.op, I_TYPE_OP_LW) == 0) {
            printf("Type: I,");
            strcpy(op, "LW");
        } else if (strcmp(R.op, I_TYPE_OP_LBU) == 0) {
            printf("Type: I,");
            strcpy(op, "LBU");
        } else if (strcmp(R.op, I_TYPE_OP_LHU) == 0) {
            printf("Type: I,");
            strcpy(op, "LHU");
        } else if (strcmp(R.op, I_TYPE_OP_LWR) == 0) {
            printf("Type: I,");
            strcpy(op, "LWR");
        } else if (strcmp(R.op, I_TYPE_OP_SB) == 0) {
            printf("Type: I,");
            strcpy(op, "SB");
        } else if (strcmp(R.op, I_TYPE_OP_SH) == 0) {
            printf("Type: I,");
            strcpy(op, "SH");
        } else if (strcmp(R.op, I_TYPE_OP_SWL) == 0) {
            printf("Type: I,");
            strcpy(op, "SWL");
        } else if (strcmp(R.op, I_TYPE_OP_SW) == 0) {
            printf("Type: I,");
            strcpy(op, "SW");
        } else if (strcmp(R.op, I_TYPE_OP_SWR) == 0) {
            printf("Type: I,");
            strcpy(op, "SWR");
        } else if (strcmp(R.op, I_TYPE_OP_LWC1) == 0) {
            printf("Type: I,");
            strcpy(op, "LWC1");
        } else if (strcmp(R.op, I_TYPE_OP_LWC2) == 0) {
            printf("Type: I,");
            strcpy(op, "LWC2");
        } else if (strcmp(R.op, I_TYPE_OP_SWC1) == 0) {
            printf("Type: I,");
            strcpy(op, "SWC1");
        } else if (strcmp(R.op, I_TYPE_OP_SWC2) == 0) {
            printf("Type: I,");
            strcpy(op, "SWC2");
        }

          // 16비트 immediate 값을 정수로 변환
        immediate = (int)strtol(R.immediate, NULL, 2);
        
        // 부호 확장 처리
        if (immediate & (1 << 15)) {  // If the sign bit is set
            immediate |= 0xFFFF0000;  // Sign extend the immediate value
        }
            
    }

    
    int rs_val = register_num[strtol(R.rs, NULL, 2)][0];  // rs 값을 십진수로 변환
    int rt_val = register_num[strtol(R.rt, NULL, 2)][0];  // rt값을 십진수로 변환
    int rd_val = register_num[strtol(R.rd, NULL, 2)][0];  // rd 값을 십진수로 변환
    

   /////////////////////////////////////print Instructions/////////////////////////////////////
    if ((op_flag == 1))
    {
        printf(" Inst: %s %s %s %s\n",op,r3,r1,r2);
    }else if (op_flag == 2)
    {
        printf(" Inst: %s %ld \n",op,address);
    }else if (op_flag == 3)
    {
        printf(" Inst: %s %ld \n",op,address);
    }else if (op_flag == 4)
    {
        if (strcmp(op,"LW") == 0 || strcmp(op,"SW") == 0 || strcmp(op,"LB") == 0 || strcmp(op,"SB") == 0)
        {
            printf(" Inst: %s %s %d(%s) \n",op,r2,immediate,r1);
            
        }else{
        
        printf(" Inst: %s %s %s %d \n",op,r1,r2,immediate);
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////print instructions/////////////////////////////////////    

    printf("\topcode: %s, rs: %s (%d), rt: %s (%d), rd: %s (%d), shamt: %s, funct: %s\n",R.op,r1,rs_val,r2,rt_val,r3,rd_val,R.shamt,R.funct);


        /////////////////////////////////set Control Signal Genertaion///////////////////////////////

    if (op_flag == 1)
    {
        signal.RegDst = 1;
        signal.ALUSrc = 0;
        signal.PCSrc = 0;
        signal.MemtoReg = 0;
        signal.RegWrite = 1;
        signal.MemRead = 0;
        signal.MemWrite = 0;
        signal.Branch = 0;
        
        /////////////////ALUop파트//////////////////////////
        if (strcmp(R.funct,ALU_AND)){
            strcpy(signal.ALUOp,ALU_AND);
        }else if(strcmp(R.funct,ALU_OR)){
            strcpy(signal.ALUOp,ALU_OR);
        }else if(strcmp(R.funct,ALU_ADD)){
            strcpy(signal.ALUOp,ALU_ADD);
        }else if(strcmp(R.funct,ALU_SUB)){
            strcpy(signal.ALUOp,ALU_SUB);
        }else if(strcmp(R.funct,ALU_SLT)){
            strcpy(signal.ALUOp,ALU_SLT);
        }else if(strcmp(R.funct,ALU_NOR)){
            strcpy(signal.ALUOp,ALU_NOR);
        }
        ////////////////////////////////////////////////////////////

    }else if (op_flag == 2 || op_flag == 3)
    {
        signal.RegDst = -1;
        signal.ALUSrc = -1;
        signal.PCSrc = 0;
        signal.MemtoReg = 0;
        signal.RegWrite = 0;
        signal.MemRead = 0;
        signal.MemWrite = 0;
        signal.Branch = 0;
        
                
    }else if (op_flag == 4)
{
    if (strcmp(R.op, I_TYPE_OP_LW) == 0 || strcmp(R.op, I_TYPE_OP_LB) == 0 || strcmp(R.op, I_TYPE_OP_LH) == 0 ||
        strcmp(R.op, I_TYPE_OP_LWL) == 0 || strcmp(R.op, I_TYPE_OP_LBU) == 0 || strcmp(R.op, I_TYPE_OP_LHU) == 0 ||
        strcmp(R.op, I_TYPE_OP_LWR) == 0 || strcmp(R.op, I_TYPE_OP_LWC1) == 0 || strcmp(R.op, I_TYPE_OP_LWC2) == 0)
    {
        signal.RegDst = 0;
        signal.ALUSrc = 1;
        signal.PCSrc = 0;
        signal.MemtoReg = 1;
        signal.RegWrite = 1;
        signal.MemRead = 1;
        signal.MemWrite = 0;
        signal.Branch = 0;
        strcpy(signal.ALUOp, ALU_ADD);
    }
    else if (strcmp(R.op, I_TYPE_OP_SW) == 0 || strcmp(R.op, I_TYPE_OP_SB) == 0 || strcmp(R.op, I_TYPE_OP_SH) == 0 ||
             strcmp(R.op, I_TYPE_OP_SWL) == 0 || strcmp(R.op, I_TYPE_OP_SWR) == 0 || strcmp(R.op, I_TYPE_OP_SWC1) == 0 ||
             strcmp(R.op, I_TYPE_OP_SWC2) == 0)
    {
        signal.RegDst = -1;
        signal.ALUSrc = 1;
        signal.PCSrc = 0;
        signal.MemtoReg = 0;
        signal.RegWrite = 0;
        signal.MemRead = 1;
        signal.MemWrite = 1;
        signal.Branch = 0;
        strcpy(signal.ALUOp, ALU_ADD);
    }
    else if (strcmp(R.op, I_TYPE_OP_BEQ) == 0 || strcmp(R.op, I_TYPE_OP_BNE) == 0)
    {
        signal.RegDst = -1;
        signal.ALUSrc = 0;
        signal.PCSrc = 1;
        signal.MemtoReg = 0;
        signal.RegWrite = 0;
        signal.MemRead = 0;
        signal.MemWrite = 0;
        signal.Branch = 1;
        strcpy(signal.ALUOp, ALU_SUB);
    }else if (strcmp(R.op, I_TYPE_OP_SLTI) == 0 || strcmp(R.op, I_TYPE_OP_SLTIU) == 0)
    {
        signal.RegDst = -1;
        signal.ALUSrc = 1;
        signal.PCSrc = 0;
        signal.MemtoReg = 0;
        signal.RegWrite = 1;
        signal.MemRead = 0;
        signal.MemWrite = 0;
        signal.Branch = 0;
        strcpy(signal.ALUOp, ALU_SLT);
    }
    else if (strcmp(R.op, I_TYPE_OP_ADDI) == 0 || strcmp(R.op, I_TYPE_OP_ADDIU) == 0)
    {
        signal.RegDst = -1;
        signal.ALUSrc = 1;
        signal.PCSrc = 0;
        signal.MemtoReg = 0;
        signal.RegWrite = 1;
        signal.MemRead = 0;
        signal.MemWrite = 0;
        signal.Branch = 0;
        strcpy(signal.ALUOp, ALU_ADD);
    }
}

    //////////////////////////////////////////////////////////////////////////////////////////    


    ///////////////////////////////////print Control_signal//////////////////////////////////
    printf("\tRegDst: %d, RegWrite: %d, ALUSrc: %d, PCSrc: %d, MemRead: %d, MemWrite: %d, MemtoReg: %d, ALUOp: %s\n",signal.RegDst,signal.RegWrite,signal.ALUSrc,signal.PCSrc,signal.MemRead,signal.MemWrite,signal.MemtoReg,signal.ALUOp);

}

int main(int argc, char *args[]){
    int execute = instruction_fetch("sum.bin");

    return 0;
}