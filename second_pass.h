/*
* File Name: second_pass.h
* contains method that are responsible for the two stages of the assembler procces
*/
#ifndef SECOND_PASS_H
#define SECOND_PASS_H


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


/* scrond stage of the assembler, completes the commands list by filling the labels addresses */
int secondParsing(list labels, list commands);


/* gets list of labels and binaryline of label address
 that couldn't be filled in the first stage, the function checks that the label exist,
  and if so calls the function to fill in the address */
int manageLabelAddress(list labels, binaryLine bl);


#endif
