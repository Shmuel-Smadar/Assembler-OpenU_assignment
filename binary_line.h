/*
* File Name: binary_line.h
* contains method that are responsible for creating and managing the binaryLine datatype
*/
#ifndef BINARY_LINE
#define BINARY_LINE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "enum.h"

typedef struct binaryLine *binaryLine;

/* create and allocate memory for the binaryLine data type 
this datatype is used for translating a command or directive line into binary.
contains:
op_type - the operand type that this binaryLine store, 0 if not an operand
src_or_dest - if the binary line contains operand, this is its target, 0 if not an operand or not relevant
label_name - if this line stores a label address, this is the label's name
binary_code - the line in binary
line_num - the line number in the ".am" file that this binaryLine is created from
*/
binaryLine createBinaryLine(int op_type, int src_or_dest, char* label_name, char* binary_code, int line_num);

/* getters */
char* binaryLineGetLabelName(binaryLine bl);
char* binaryLineGetBinaryCode(binaryLine bl);
int binaryLineGetLineNum(binaryLine bl);
int binaryLineGetOpType(binaryLine bl);
int binaryLineGetSrcOrDest(binaryLine bl);

/* setter */
void binaryLineSetBinaryCode(binaryLine bl, char* binary_code);

/* free the memory that has been allocated for the given binaryLine */ 
void freeBinaryLine(void* data);

#endif
