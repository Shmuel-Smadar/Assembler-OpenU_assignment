/*
* File Name: compare.h
* contains method that are responsible for making all sort of comprasions
* on given input, for example figuring out if a word is a label or struct.
*/
#ifndef COMPARE_H
#define COMPARE_H

#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "print.h"
#include "label.h"
#include "first_pass.h"

/* check if a given string is equal to the word "macro" */ 
int isMacro(char* word);

/* check if a given string is equal to the word "endmacro" */ 
int isEndMacro(char is_end[8]);

/* check if a given word stand in the struct criteria */ 
int isStruct(char* word);

/* check if a given line is a directive sentence */ 
int isDirectiveLine(char* line);

/* check if a given line is comment line */ 
int isCommentLine(char* word);

/* first look at what type the operand is. (i.e not a number address if doesn't start at '#') */ 
int readOperand(char* word);

/* check if a given word stand in the label criteria */ 
int isLabel(char* word, int is_definition);

/* check if a gives string is equal to the word ".extern" or ".entry" */ 
int isExternOrEntry(char* word);

/* try to determine what error should be given (the operand is known to be illegal  */
int checkOpErr(char* op);

/* check if a given word is one of the keywords */
int isKeyword(char* word);

/* check if a given word is an operation */ 
int isOperation(char* word);

#endif
