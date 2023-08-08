#include "macro.h"

struct macro
{
	int start_pos;
	int start_line;
	int num_of_lines;
	char* macro_name;
};

macro createMacro(int start_pos, int start_line, int num_of_lines, char* name)
{
	macro mc = calloc(1, sizeof(struct macro));
	mc->start_pos = start_pos;
	mc->start_line = start_line;
	mc->num_of_lines = num_of_lines;
	mc->macro_name = calloc(1, sizeof(char) * strlen(name) + 1);
	strcpy(mc->macro_name, name);
	return mc;
}


int compareMacro(void* m1, void* m2)
{
	/* compare by the macro name */
	if(strcmp(((macro)m1)->macro_name,((macro)m2)->macro_name) == 0)
	{
		return 1;
	}
	return 0;
		
}

void freeMacro(void* data)
{
	if(data == NULL)
		return;
	free(((macro)data)->macro_name);
	free(((macro)data));
	data = NULL;
}

int macroHandler(char* filename, int* has_errors)
{
	FILE *as_file;
	FILE *as_file_for_search;
	FILE *am_file;
	char *filename_with_am, *filename_with_as;

	/* open the ".as" file */
	filename_with_as = concat(filename, ".as");
	printWithString(E_print_message, E_start_handeling_macro, filename_with_as);

	as_file = fopen(filename_with_as, "r");
	as_file_for_search = fopen(filename_with_as, "r");
	free(filename_with_as);

	/* check if the ".as" file exist */
	if(as_file == NULL)
	{
		printNoLine(E_print_error, E_file_not_exist);
		return E_error_occured;
	}
	
	/* create and write to the ".am" file */
	filename_with_am = concat(filename, ".am");
	am_file = fopen(filename_with_am, "w");
	writeWithMacros(as_file, as_file_for_search, am_file, has_errors);
	fclose(as_file);
	fclose(as_file_for_search);
	fclose(am_file);
	if(*has_errors)
	{
		remove(filename_with_am);
		free(filename_with_am);
		return E_error_occured;
	}
	printWithString(E_print_message, E_macros_were_handled, filename_with_am);
	free(filename_with_am);
	return E_success;
}



void writeWithMacros(FILE *as_file, FILE *as_file_for_search, FILE *am_file, int* has_errors)
{
	int curr_pos;
	int curr_line;
	char line[LINE_LENGTH];
	list ls;
	curr_pos = 0;
	curr_line = 0;
	ls = createList();
	
	while(fgets(line, LINE_LENGTH, as_file))
	{
		char* next_word;
		curr_pos += strlen(line);
		curr_line += 1;
		/* check if line is longer than permitted */
		if(checkLineValidity(line) == E_error_occured)
		{
			print(E_print_error, E_illegal_line_length, curr_line);
			*has_errors = 1;
			return;
		}
		/* check if the next word is "macro", if so store it */
		next_word = storeNextWord(line, 0, 0);
		if(isMacro(next_word))
		{
			skipSpaceAndTabs(line, 1);
			substring(line, strlen(next_word));
			free(next_word);
			if(storeMacro(as_file, ls, line, &curr_pos, &curr_line) == E_error_occured)
			{
				*has_errors = 1;
				return;
			}
		}
		else /* next line is not a macro definition */
		{
			macro for_search = createMacro(0, 0, 0, next_word);
			macro res = listSearch(ls, for_search, compareMacro);
			free(next_word);
			freeMacro(for_search);
			if(res != NULL) /* we found a macro */
				writeMacroContent(res, as_file_for_search, am_file);
			else
				fputs(line, am_file);
		}
	}
	freeList(ls, freeMacro);
}


int storeMacro(FILE* as_file, list ls, char* line, int *curr_pos, int *curr_line)
{
	char* macro_name;
	int start_pos;
	int start_line;
	int num_of_lines;
	macro mc;
	/* find macro name and position, create the macro and store it */
	macro_name = storeNextWord(line, 1, 0);
	start_pos = *curr_pos;
	start_line = *curr_line;
	num_of_lines = findMacroNumOfLines(as_file, curr_pos, curr_line);
	if(num_of_lines == E_error_occured)
	{
		print(E_print_error, E_endmacro_not_found, *curr_line);
		return E_error_occured;
	}
	mc = createMacro(start_pos, start_line, num_of_lines, macro_name);
			
	if(checkMacroValidity(ls, mc, line) == E_error_occured)
	{
		free(macro_name);
		return E_error_occured;
	}
	insert(ls, mc);
	free(macro_name);
	return E_success;
}

void writeMacroContent(macro m1, FILE* file_for_search, FILE* file_for_write)
{
	int i;
	char line[LINE_LENGTH];
	fseek(file_for_search, m1->start_pos, SEEK_SET );
	for(i = 0; i < m1->num_of_lines; ++i) /* go through the lines of the macro and write them to the ".am" file */
	{
		fgets(line, LINE_LENGTH, file_for_search);
		fputs(line, file_for_write);
	}
}

int findMacroNumOfLines(FILE *fptr, int *curr_pos, int *curr_line)
{
	int num_of_lines, is_defined;
	char line[LINE_LENGTH];
	num_of_lines =  is_defined = 0;
	while(fgets(line, LINE_LENGTH, fptr) != NULL)
	{
		char is_end_macro[8];
		*curr_pos += strlen(line);
		(*curr_line)++;
		skipSpaceAndTabs(line, 1);
		strncpy(is_end_macro, line, 8);
		is_end_macro[8] = '\0';
		
		if(isEndMacro(is_end_macro)) /* if "endmacro was encountered" */
		{
			is_defined = 1;
			break;
		}
		else
			num_of_lines++;
	}
	if(!is_defined)
		return E_error_occured;
	return num_of_lines;
}

int checkMacroValidity(list ls, macro mc, char* line)
{
	macro res;
	res = listSearch(ls, mc, compareMacro);
	/* check for various errors in the macro naming and the line itself */
	if(res != NULL)
	{
		print2Lines(E_print_error, E_duplicate_macro_name, res->start_line, mc->start_line);
		return E_error_occured;
	}
	else if(isMacro(mc->macro_name))
	{
		print(E_print_error, E_macro_named_macro, mc->start_line);
		return E_error_occured;
	}
	else if(isEndMacro(mc->macro_name))
	{
		print(E_print_error, E_macro_named_endmacro, mc->start_line);
		return E_error_occured;
	}
	else if(isKeyword(mc->macro_name))
	{
		print(E_print_error, E_macro_keyword, mc->start_line);
		return E_error_occured;
	}
	else if(!isEndOfLine(line))
	{
		print(E_print_error, E_extra_text_macro, mc->start_line);
		return E_error_occured;
	}
	return E_success;
}


