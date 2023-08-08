#include "assembler.h"

void freeAll(list labels, list commands, list directives)
{
	freeList(labels, freeLabel);
	freeList(commands, freeBinaryLine);
	freeList(directives, freeBinaryLine);
}

void commandLineParamNumCheck(int argc, char* programName)
{
	if(argc < 2)
	{
        printf("Usage: %s <files names seperated by whitespace>\n", programName);
        exit(0);
   	}
}

void translateFile(char* filename)
{
	int has_errors, IC, DC;
	list labels, commands, directives;
	has_errors = IC = DC =  0;
	/* call the function that handles macro, exit if there is an error */
	if(macroHandler(filename, &has_errors) == E_error_occured)
	{
		printNoLine(E_print_message, E_error_pre_assembler);
		return;
	}
	labels = createList();
	commands = createList();
	directives = createList();

	/* first part of the translating, mark a flag if there is an error */
	if(firstParsing(filename, labels, commands, directives, &IC, &DC) == E_error_occured)
	{
		has_errors = 1;
	}
	/* second part of the translating, mark a flag if there is an error */
	else if(secondParsing(labels, commands) == E_error_occured)
	{
		has_errors = 1;
	}
	/* if there are no errors, call the function to create the output files,
	if there are errors print appropriate message */
	if(!has_errors)
	{
		createOBFile(filename, commands, directives, IC, DC);
		createENTFile(filename, labels);
		createEXTFile(filename, commands, labels);
		printNoLine(E_print_message, E_files_created);
	}
	else
	{
		printNoLine(E_print_message, E_err_found);
	}
	freeAll(labels, commands, directives);
	
}

int main(int argc, char *argv[])
{
	int i;

	/* */
	commandLineParamNumCheck(argc, argv[0]);

	/* go through all the files */
	for(i = 1; i < argc; ++i)
	{
		translateFile(argv[i]);
	}
	printNoLine(E_print_message, E_exiting_program);
	return 0;
}
