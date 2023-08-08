/*
* File Name: assembler.h
* the main file of the program contains methods that start and finish the translation proccess.
*/

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdio.h>
#include <stdlib.h> 
#include "macro.h"
#include "first_pass.h"
#include "second_pass.h"

/*A method that Checks that the number of commandline
* parameters is correct. exits from the program if its not */ 
void commandLineParamNumCheck(int argc, char* programName);

/*A method that responsible for freeing the data that has been save during the translation proccess */
void freeAll(list labels, list commands, list directives);

/*A method that calls the right function for the translation procces
 in the right order for every filename given by the user */
void translateFile(char* filename);

#endif
