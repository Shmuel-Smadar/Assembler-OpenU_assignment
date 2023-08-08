/*
* File Name: read_line.h
* contains methods that are responsible for translating data into binary and storing it in the given list.
*/
#ifndef STORE_H
#define STORE_H

#include "linked_list.h"
#include "label.h"
#include "binary_line.h"
#include "parser.h"
#include "enum.h"
#include "compare.h"

/* check if the given label name is legal (i.e illegal if was already defined)
and if so, store it in the labels list */
int storeLabel(list labels, char* label_name, int is_directive, int *IC, int* DC, int line_num);

/* extract and store number/s from the line (amount depends if struct or ".data" sentence)
if there is an error, print it  */
int storeData(list ls, char* line, int line_num, int is_struct, int *IC_or_DC);

/* call the appropriate functions to extract from the line data required for a struct, print if there is an error*/
int storeStructData(list directives, char* line, int line_num, int *DC);

/* call the appropriate functions to extract from the line data required for a string, print if there is an error*/
int storeString(list directives, char* line, int line_num, int *DC);

/* gets a number and store it inside the given list,
 if the sentence is directive we have 10 bits for the storage, otherwise -8 */
void storeNum(list ls, int num, int is_directive);

/* gets an operand type and store its opcode in the given binary line */
void storeOperandOpcode(char* binary_line, int op_res, int src_or_dest);

/* gets a number of regiser and create a new binaryLine object and store it in the given list
(if the previous operand was a register too they will be combined) */
void storeRegister(list ls, int register_num,  int src_or_dest, int* IC);

/* gets a label and store its address in a given binary line */
void storeLabelAddress(binaryLine bl, label l1);

/* store the opcode of the given operation num inside the given binary line */
void storeOperationOpcode(char* binary_line, int command_num);

/* gets a line after the word ".entry" ot ".extern" has been read from it,
if the upcoming label is legal store it, otherwise print an error */
int storeExtOrEntLabel(list labels, char* label_name, int ext_ot_ent, int line_num);

/* create a binaryLine object for a label, it won't have a code until the second stage of the assembler */
int storeLabelInBinaryLine(list ls, char* label_name, int line_num, int src_or_dest, int *IC);

/*  create a binaryLine object for a label and another one for the place
 we want to access in the struct (1 or 2) and store it in the given list */
int storeStructInBinaryLine(list ls, char* op_name, int line_num, int *IC, int src_or_dest);
#endif
