/*
* File Name: macro.h
* contains method that are responsible for creating and managing the macro datatype and handeling them in files.
*/

#ifndef MACRO_H
#define MACRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "enum.h"
#include "print.h"
#include "node.h"
#include "linked_list.h"
#include "parser.h"
#include "compare.h"

typedef struct macro *macro;

/* allocate memory for the macro struct 
* contains:
* start_pos - the start position of the content of the macro
* start_line - the number of the start line of the content of the macro
* num_of_lines - number of line of the content of the macro
* name - the name of the macro
*/
macro createMacro(int start_pos, int start_line, int num_of_lines, char* name);

/* free the memory that has been allocated for the macro datatype */
void freeMacro(void* data);

/* compare between two macros (for linked lists), comprasion is done by the name */
int compareMacro(void* m1, void* m2);

/* find the number of lines the content of the macro has */
int findMacroNumOfLines(FILE *fptr, int *curr_pos, int *curr_line);

/* write the .am file with the content of the macros*/
void writeWithMacros(FILE *as_file, FILE *as_file_for_search, FILE *am_file, int* has_errors);

/* create the .am file and calls the appropriate functions to handle the macros */
int macroHandler(char* filename, int* has_errors);

/* check if the macro that has been fpund stand in the macro criteria */
int checkMacroValidity(list ls, macro mc, char* line);

/* store the macro inside the given list */
int storeMacro(FILE* as_file, list ls, char* line, int *curr_pos, int *curr_line);

/* write the given macro content into the .am file */
void writeMacroContent(macro m1, FILE* file_for_search, FILE* file_for_write);

#endif


