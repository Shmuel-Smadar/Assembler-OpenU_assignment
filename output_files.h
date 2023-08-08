/*
* File Name: output_files.h
* contains method that are responsible for translating and 
* creating output files from the data gathered during the assembler proccess
*/
#ifndef OUTPUT_FILES_H
#define OUTPUT_FILES_H

#include "parser.h"
#include "label.h"
#include "binary_line.h"
#include "linked_list.h"
#include "first_pass.h"
#include "base.h"
#include <stdio.h>
#include <stdlib.h> 

/*create and write to the .ob file */
void createOBFile(char* filename, list commands, list directives, int IC, int DC);

/*create and write to the .ent file, file will be deleted if there are no entry labels */
void createENTFile(char* filename, list labels);

/*create and write to the .ext file, file will be deleted if there are no external labels */
void createEXTFile(char* filename, list commands, list labels);

#endif
