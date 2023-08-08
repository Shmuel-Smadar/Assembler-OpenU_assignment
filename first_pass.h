/*
* File Name: first_pass.h
* contains method that are responsible for the two stages of the assembler procces
*/
#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "compare.h"
#include "linked_list.h"
#include "print.h"
#include "base.h"
#include "label.h"
#include "binary_line.h"
#include "enum.h"
#include "output_files.h"
#include "store.h"

/* first stage of the assembler, responsible for building  the labels, commands and directives lists without the
labels adresses (which sometimes cannot be known until the end of the first stage) */
int firstParsing(char* filename, list labels, list commands, list directives, int *IC, int *DC);


/* gets a line of input and responsible for sending it to the right functions for translation */
int manageLine(char* line, list commands, list directives, list labels, int line_num, int *IC, int *DC);

/* manages a line that has started with ".extern" or ".entry" by getting and storing the next label aproprietly */
int manageExtOrEntLabel(char* line, int is_ext_or_ent, list labels, int line_num);

/* manages the defintion of a label and checks for erros i.e redefintion of label \ invalid name */
int manageLabelDefinition(list labels, char* line, int* IC, int *DC, int line_num);

/* gets a command sentence,
responsible for sending it to the right functions for translation */
int manageInstructionLine(list commands, int *IC, char* line, int line_num);

/* gets a command sentence that has 2 operands,
responsible for sending it to the right functions for translation */
int manageLine2Operands(list commands, int* IC, char* line, int command_num, int line_num);

/* gets a command sentence that has 1 operand,
responsible for sending it to the right functions for translation */
int manageLine1Operand(list commands, int* IC, char* line, int command_num, int line_num);

/* gets a command sentence that has no operands,
 responsible for sending it to the right functions for translation */
int manageLineNoOperands(list commands, int* IC, char* line, int command_num, int line_num);

/* gets a line which has operand as the next word, responsible for 
extracting it and sending for translation, if there is an error, return appropriate enum */
int manageOperand(list ls, char* binary_line,  char* line, int line_num, int command_num, int src_or_dest, int *IC);

/* gets a line which has number operand as the next word,
 call the right function to store it, if there is error print it*/
int manageNum(list ls, char* line, int line_num, int *IC, int src_or_dest);


/* gets an operand, responsible for figuring which type it is
 and sending it to the right function for storage */
int storeOpLines(list ls, int command_num, char* op_name, int op_type, int src_or_dest, int *IC, int line_num);

/* gets a directive line and respnsible for figuring which type
 of line it is, (".string for example") and storing it in the directives list */
int manageDirectiveLine(list directives, list labels, int *DC, char* line, int line_num, int directive_type);

/* gets a line and returns appropriate enum if there the next character is a comma or if there is multiple commas */
int commaHandler(char* line, int line_num);

/* gets a binary line and initialize it to '0' */
void initBinaryRep(char* binary_rep);

/* gets a number and checks if its in the legal range (for either directive or command sentence) */
int isNumInRange(int num, int is_directive);

#define NUM_OF_COMMANDS 16

#endif


