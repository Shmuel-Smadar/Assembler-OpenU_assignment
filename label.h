/*
* File Name: label.h
* contains method that are responsible for creating and managing the label datatype
*/
#ifndef LABEL_H
#define LABEL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linked_list.h"
#include "enum.h"

typedef struct label *label;

#define MAX_LABEL_LENGTH 30

/* create and allocate memory for the label datatype.
 this datatype is used for storing labels found in the ".am" file.
contains:
label_name - the name of the label that is stored
ext_or_ent - is this label external or entry or not both
ext_ent_line_num - if this label is external or entry, this field saved where it was declared as such
ic_or_dc - is this labed used before command line or directive line
dec_address - this memory address that this line was defined it
def_line_num - the line number in the ".am" file that this label was defined in
*/
label createLabel(int ext_or_ent, int ext_ent_line_num, int dec_address, char* label_name, int ic_or_dc, int def_line_num);

/* getters */
int labelGetExtOrEnt(label l1);
int labelGetExtEntLineNum(label l1);
int labelGetICorDC(label l1);
char* labelGetName(label l1);
int labelGetDecAddress(label l1);
int labelGetDefLineNum(label l1);

/* setters*/
void labelSetDefLineNum(label l1, int def_line_num);
void labelSetExtOrEnt(label l1, int ext_or_ent);
void labelSetExtEntLineNum(label l1, int ext_ent_line_num);
void labelSetICorDC(label l1, int ic_or_dc);
void labelSetDecAddress(label l1, int dec_address);

/* add final IC value + 100 to every DC-type label and 100 to every IC-type label */
void labelFixAddress(void* l1, int IC);

/* compare between two labels (for linked lists), comprasion is done by the name */
int compareLabel(void* l1, void* l2);

/* free the memory that has been allocated for the given label */
void freeLabel(void* data);

#endif