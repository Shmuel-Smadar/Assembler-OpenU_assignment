#include "print.h"

const char* error_prints[] = {"label cannot be declared twice as entry or extern or both.", "label defined in this file cannot be declared as external.",
"label declared as external in this file cannot be defined.", "label definiton does not have colons.",
"label cannot use keyword as a name.", "label is missing.", "comma is missing.", "illegal use of comma.", "multiple concecutive commas is illegal.", 
"illegal number", "number is missing", "number is missing before comma", "number is missing after comma", "label contains illegal characters", "extra text after end of line."
, "operation is undefined.", "illegal operand.", "string is missing.", "string is illegal.",
 "the operation \"lea\" source operand cannot be a register.", "the operation \"lea\" source operand cannot be a number address.",
  "the only operations that can have destination operand as a number address are \"cmp\" and \"prn\".",
"struct only have 2 members which can be accessed by using the numbers 1 or 2.", "label used but not defined or declared as external.",
 "line cannot have more than 80 characters.",
 "operand is missing.", "the file does not exist.", "operand is a saved word.",
  "label crosses the 30 characters limit.",  "illegal macro naming, cannot use a keyword."
  , "extra text after macro definition.", "duplicate macro naming.", "macro name cannot be \"macro\".", "macro name cannot be \"endmacro\".",
  "macro does not have \"endmacro\" declaration.",
   "duplicate label defintions.", "label declared as \".entry\" have to be defined in the file.", "label was defined before empty line",
   "number is out of the range -128 - 127 for command sentence",
    "number is out of the range -512 - 511 for directive sentence", "label that is not a struct is used as a struct."};

const char* msg_prints[] = {"***Your files are ready!***\n", "Program is done, exiting.", "No external labels found, file for external labels was not created.",
 "No entry labels found, file for entry labels was not created.", "***Errors found in your file, translated files can not be created.***\n"
 , "Starting macro handling in the file: ", "", "Macros were handled successfully, result is in the file: ", 
 "Error found in the pre assembler stage, translation of this file cannot continue.\n", "Starting first part of the translation of the file: "
 ,"Warning: label defined in \".extern\" or \".entry\" sentence will be discarded.", "\nStarting first part of the assembler:"
 , "\nFirst part of the assembler has been finished successfully.\n", "\nFirst part of the assembler has been finished with errors.\n"
 , "Starting second part of the assembler:", "\nSecond part of the assembler has been finished successfully.\n", 
 "\nSecond part of the assembler has been finished with errors.\n"};


void printWithString(int type, int arr_num, char* string)
{
    if(type == E_print_error)
        printf("Error found: %s%s\n", error_prints[arr_num], string);
    else if(type == E_print_message)
        printf("%s%s\n", msg_prints[arr_num], string);
    
}

void print2Lines(int type, int arr_num, int line1, int line2)
{
    if(type == E_print_error)
         printf("Error found in lines %d, %d: %s\n",  line1, line2, error_prints[arr_num]);
    else if(type == E_print_message)
        printf("in lines %d ,%d:%s\n", line1, line2, msg_prints[arr_num]);

}

void printNoLine(int type, int arr_num)
{
    if(type == E_print_error)
        printf("Error found: %s\n", error_prints[arr_num]);
    else if(type == E_print_message)
        printf("%s\n", msg_prints[arr_num]);

}
void print(int type, int arr_num, int line_num)
{
    if(type == E_print_error)
    {
        printf("Error found in line %d: ", line_num);
        printf("%s\n", error_prints[arr_num]);
    }
    else if(type == E_print_message)
    {
        printf("in line: %d: ", line_num);
        printf("%s\n", msg_prints[arr_num]);
    } 
}

void printErrorWithOperandTargert(int arr_num, int line_num, int src_or_dest)
{
    if(src_or_dest == E_src_op)
        printf("Error found in line %d at the source operand: ", line_num);
    else
        printf("Error found in line %d at the destination operand: ", line_num);
    printf("%s\n", error_prints[arr_num]);
}