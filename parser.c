#include "parser.h"

int skipSpaceAndTabs(char* line, int delete_white_spaces)
{
	int i;
	i = 0;
	
	while(line[i] == ' ' || line[i] == '\t')
	{
		i++;
	}
	if(delete_white_spaces)
	{
		substring(line, i);
		return 0;
	}
	else
		return i;
}

int isCommentLine(char* line)
{
	skipSpaceAndTabs(line, 1);
	if(strlen(line) > 0 && line[0] == ';')
		return 1;
	return 0;
}

int checkLineValidity(char* line)
{
	int i;
	for(i = 0; i < LINE_LENGTH - 1; ++i)
	{
		if(line[i] == '\n' || line[i] == EOF || line[i] == '\0')
			return E_success;
	}
	return E_error_occured;
}

void deleteNextWord(char* line)
{
	int i;
	i = 0;
	skipSpaceAndTabs(line, 1);
	while(line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != EOF)
	{
		i++;
	}
	substring(line, i);
}

void substring(char* line, int num)
{
	int i = num;
	int j = 0;
	while(line[i] != '\0')
	{
		line[j] = line[i];
		++j;
		++i;
	}
	line[j] = '\0';
}

char* storeNextWord(char* line, int delete_word, int stop_at_comma)
{
	int size, i, j;
	char* word;
	i =  skipSpaceAndTabs(line, delete_word);
	size = 0;
	/* if comma is a sign to stop, we check if the next character is  a comma in addition to spaces \ tabs \ etc */
	if(stop_at_comma)
	{
		while(line[i + size] != ' ' && line[i + size] != '\n' && line[i + size] != '\t' && line[i + size] != ',' && line[i + size] != EOF  && line[i + size] != '\0')
		{
			 ++size;
		}
	}
	else
	{
		while(line[i + size] != ' ' && line[i + size] != '\n' && line[i + size] != '\t' && line[i + size] != EOF  && line[i + size] != '\0')
		{
			 ++size;
		}
	}
	/* after we found the size of the word, we allocate memory for it and copy into it */
	word = calloc(1, sizeof(char) * size + 1);
	size = size + i;
	for(j = 0; i < size ; ++i, ++j)
	{
		word[j] = line[i];
	}
	/* if the flag for deleting the word was on, we delete it */
	if(delete_word)
		substring(line, i);
	
	return word;
	
}

char* concat(char *s1, char *s2)
{
	/* allocate memory for the merged string and copy both of the given strings into it */
    char *result = calloc(1, sizeof(char) * (strlen(s1) + strlen(s2)) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int isEndOfLine(char* line)
{
	skipSpaceAndTabs(line, 1);
	if(line[0] != '\n' && line[0] != EOF && line[0] != '\0')
	{
		return 0;
	}
	return 1;
}

int getNumber(char* line, int *num)
{
	int is_defined, is_neg, i;
	is_defined = is_neg = i = *num = 0;
	skipSpaceAndTabs(line, 1);
	if(line[i] == '-') /* number is negative */
	{
		is_neg = -1;
		++i;
	}
	else if(line[i] == '+')
	{
		i++;
	}
	while((line[i] >= '0' && line[i] <= '9'))
	{
		is_defined = 1; 
		*num *= 10;
		*num +=  (line[i++] - '0');
	}
	substring(line, i);
	if(!isNextCharLegal(line)) /* if the next character inside the number is an illegal character, return apropriate enum */
		return E_illegal_number;
		
	if(is_neg) 
		*num *= -1;

	if(!is_defined)
		return E_missing_number;
	
	return E_success;
}

int isNextCharLegal(char* line)
{
	if(line[0] == '\n' || line[0] == ' ' || line[0] == '\0' || line[0] == '\t' || line[0] == ',')
		return 1;
	return 0;
}

int getComma(char* line)
{
	skipSpaceAndTabs(line, 1);
	if(line[0] == ',')
	{
		substring(line, 1);
		skipSpaceAndTabs(line, 1);
		if(line[0] == ',')
		{
			return E_multiple_commas;
		}
		return E_success;
	}
	return E_missing_comma;
}

char* getString(char* line, int *has_err)
{
	char* str;
	int size, i, end_of_string_index, is_defined;
	size = is_defined = 0;
	
	skipSpaceAndTabs(line, 1);
	
	/* if the next character is not a start of a string */
	if(line[0] != '\"' || isEndOfLine(line))
	{
		*has_err = E_missing_string;
		return NULL;
	}
	substring(line, 1);
	while(line[size] != '\n' && line[size] != '\0' && line[size] != EOF)
	{
		if(line[size] == '\"') /* we encountered a possible end for the string (we will take the last '"') */
		{
			is_defined = 1;
			end_of_string_index = size;
		}
		++size;
	}
	if(!is_defined) /* if the string did not have '"' as en end */
	{
		*has_err = E_illegal_string;
		return NULL;
	}
	str = calloc(1, sizeof(char) * end_of_string_index + 1);
	
	for(i = 0; i < end_of_string_index ; ++i)
	{
		str[i] = line[i];
	}
	substring(line, end_of_string_index + 1);
	*has_err = E_success;
	return str;
}
