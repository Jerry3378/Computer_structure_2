/* FILE NAME: register.h
 * Description: This header file contains the declarations of global variables representing registers.
 * These registers are used for various purposes such as storing return values, temporary data,
 * or saved values during program execution.
 */

#ifndef GLOBAL_REGISTER_H
#define GLOBAL_REGISTER_H

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

extern int register_num[NUM_REGISTERS][REGISTER_SIZE];

#endif