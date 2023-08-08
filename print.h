/*
* File Name: print.h
* contains method that are responsible for printing messages and errors to the user.
*/
#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include <string.h>
#include "enum.h"


/* gets the appropriate error or message enum and the line,
 prints the related mesage  according to the errors / messages array stored in the .c file */
void print(int type, int arr_num, int line_num);

/* same as above, only those prints do not need a line number, i.e if user enterd a filename of file that does not exist */
void printNoLine(int type, int arr_num);

/* same as above, only that it prints the appropriate message with another string */
void printWithString(int type, int arr_num, char* string);

/* same as above, only that it prints the appropriate message with another line number */
void print2Lines(int type, int arr_num, int line1, int line2);

/* prints an error with operand target */
void printErrorWithOperandTargert(int arr_num, int line_num, int src_or_dest);






#endif