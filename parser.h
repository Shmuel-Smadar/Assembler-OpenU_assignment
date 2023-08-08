/*
* File Name: read_line.h
* contains methods that are responsible for filtering and getting specific input from the line the user has written.
*/
#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "enum.h"

/* additional space for the '/n' and another to know if there is an error*/
#define LINE_LENGTH 82

/* check if the length of the line is valid */
int checkLineValidity(char* line);

/*cut the line by the given index */
void substring(char* line, int num);

/* cut the white spaces from the start of the line */
int skipSpaceAndTabs(char* line, int delete_white_spaces);

/* delete the next word from the line */
void deleteNextWord(char* line);

/*combine two strings, this method allocates memory that needs freeing */
char* concat(char *s1, char *s2);

/* check if the line is at its end (only white spaces left) */
int isEndOfLine(char* line);

/* return the next word from the line, another values are to determine 
if to delete the word from the line and if comma means end of the word */
char* storeNextWord(char* line, int delete_word, int stop_at_comma);

/* check if next character is a white space or comma*/
int isNextCharLegal(char* line);

/* returns the appropriate enum for (excluding which spaces):
if next character is not a comma
if next character is a comma 
if next two characters are commas */
int getComma(char* line);

/* return the upcoming number from the line, return appropriate enum if missing or illegal */
int getNumber(char* line, int *num);

/* returns the next string from the line */
char* getString(char* line, int *has_err);

/* check if the given line is comment line */
int isCommentLine(char* line);

#endif

