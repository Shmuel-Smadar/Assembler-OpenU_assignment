/*
* File Name: base.h
* contains method that are responsible for converting numbers between bases. 
* (and specifically our newly defined custom 32 base)
*/
#ifndef BASE_H
#define BASE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "parser.h"
#include "enum.h"

/* gets a binary number as a string and returns an appropriate string converted to the new 32 base */
char* stringBinaryToNewBase(char* binary, char res[3]);

/* gets a binary number as a string and returns an appropriate int converted to decimal  */
int stringBinaryToDecimal(char* binary);

/* gets a decimal number and a string sized 2 returns an appropriate string converted to the new 32 base */
char* DecToNewBase(int num, char res[3]);

#endif
