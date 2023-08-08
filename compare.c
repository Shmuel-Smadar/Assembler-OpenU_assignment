#include "compare.h"

#define NUM_OF_KEYWORDS 29

int isMacro(char* is_macro)
{	
	if(strcmp("macro", is_macro) == 0)
		return 1;
	return 0;
}

int isEndMacro(char is_end[8])
{
	if(strcmp(is_end, "endmacro") == 0)
		return 1;
	return 0;
}

int isExternOrEntry(char* word)
{
	if(strcmp(word, ".extern") == 0)
		return E_ext;
	if(strcmp(word, ".entry") == 0)
		return E_ent;
	return E_not_ext_or_ent;
}


int isLabel(char* word, int is_definition)
{
	int i;
	int len = strlen(word);
	if(strcmp(word, "") == 0)
		return E_missing_label;

	if(isKeyword(word))
		return E_label_cannot_use_keyword;
	if(is_definition)
	{
		if(word[len - 1] != ':')
			return E_missing_colons_in_label;
		word[len -1] = '\0';
		len--;
	}
	if(!(word[0] >= 'a' && word[0] <= 'z') && !(word[0] >= 'A' && word[0] <= 'Z'))
		return E_illegal_characters_in_label_name;
	for(i = 1; i < len; ++i)
	{
		if(!(word[i] >= 'a' && word[i] <= 'z') &&  !(word[i] >= 'A' && word[i] <= 'Z') && !(word[i] >= '0' && word[i] <= '9'))
			return E_illegal_characters_in_label_name;
		if(i == MAX_LABEL_LENGTH)
		{
			return E_label_cross_limit;
		}
	}
	return E_success;
}

int readOperand(char* word)
{   
	int len = strlen(word);
	if(len == 2 && word[0] == 'r' && (word[1] >= '0' && word[1] <= '7'))
	{
		return E_op_register;
	}
	else if(word[0] == '#')
	{
		return E_op_num;
	}
	/* even though struct cannot have more than 2 fields (0 is also illegal)
	 I still classify that as a "struct" to be able to give appropriate error*/
	else if(len >= 3 && word[len - 2] == '.' && word[len - 1] >= '0' && word[len - 1] <= '9')
	{
		return E_op_struct;
	}
	return E_op_label;
}


int isDirectiveLine(char* line)
{
	char* word;
	word = storeNextWord(line, 0, 0);
	
	if(strcmp(word, ".data") == 0)
	{
		free(word);
		return E_data;
	}
	else if (strcmp(word, ".string") == 0)
	{
		free(word);
		return E_string;
	}
	else if(strcmp(word, ".struct") == 0)
	{
		free(word);
		return E_struct;
	}
	else if(strcmp(word, ".entry") == 0)
	{
		free(word);
		return E_ent;
	}
	else if(strcmp(word, ".extern") == 0)
	{
		free(word);
		return E_ext;
	}
	else
	{
		free(word);
		return E_not_directive;
	}	
	
}

int isKeyword(char* word)
{
	int i;
	const char* keywords[] = {"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec", "jmp", "bne", "get", "prn", "jsr", "rts", "hlt",
 ".struct", ".data", ".string", ".entry", ".extern", "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"};

	for(i = 0; i < NUM_OF_KEYWORDS; ++i)
	{
		if(strcmp(word, keywords[i]) == 0)
			return 1;
	}
	return 0;
}

int checkOpErr(char* op)
{
	if(strlen(op) == 0)
		return E_missing_op;
	else if(isKeyword(op))
		return E_op_is_saved_word;
	return E_illegal_op;
}

int isStruct(char* word)
{
    int len, is_label;
    len = strlen(word);
    if(word[len - 1] == '0' || (word[len - 1] >= '3' && word[len - 1] <= '9') )
    {
        return E_illegal_num_of_struct_member;
    }
    word[len - 2] = '\0';
    is_label = isLabel(word,0);
    word[len - 2] = '.';
    return is_label;
}

int isOperation(char* word)
{
	const char* command_names[] = {"mov", "cmp", "add", "sub", "not", "clr",
	 "lea", "inc", "dec", "jmp", "bne", "get", "prn", "jsr", "rts", "hlt"};
	int i;
	if(strlen(word) != 3)
		return E_not_operation;
	for(i = 0; i < NUM_OF_COMMANDS; ++i)
	{
		if(strcmp(word, command_names[i]) == 0)
			return i;
	}
	return E_not_operation;
}

