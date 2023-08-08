#include "first_pass.h"

int firstParsing(char* filename, list labels, list commands, list directives, int *IC, int *DC)
{
	FILE* am_file;
	char line[LINE_LENGTH], *filename_with_am;
	int curr_line, has_errors;
	curr_line = has_errors =  0;
	printNoLine(E_print_message, E_assembler_first_part_started);
	/* open the .am file */
	filename_with_am = concat(filename, ".am");
	am_file = fopen(filename_with_am, "r");
	free(filename_with_am);
	/* go through the .am file and call a function to manage every line */
	while(fgets(line, LINE_LENGTH, am_file))
	{
		curr_line++;
		if(manageLine(line, commands, directives, labels, curr_line, IC, DC) == E_error_occured)
			has_errors = E_error_occured;
	}
	/* call a function to add the final IC value */
	listForEachWithValue(labels, *IC, labelFixAddress);

	fclose(am_file);
	if(has_errors == 0)
		printNoLine(E_print_message, E_assembler_first_part_finished_success);
	else
		printNoLine(E_print_message, E_assembler_first_part_finished_fail);
	return has_errors;
}




int manageLine(char* line, list commands, list directives, list labels, int line_num, int *IC, int *DC)
{
	int is_directive, is_label_defined;

	/* check if line is  a comment or empty */
	if(isCommentLine(line) || isEndOfLine (line))
		return E_success;
	/* check if the first word is label, if so, store it */
	is_label_defined = manageLabelDefinition(labels, line, IC, DC, line_num);
	if(is_label_defined == E_error_occured)
	{
		return E_error_occured;
	}

	if(isEndOfLine(line))
	{
		print(E_print_error, E_label_defined_empty_line, line_num);
		return E_error_occured;
	}

	/* check what is the type of the line and call the appropriate function to store it */
	is_directive = isDirectiveLine(line);
	if(is_directive == E_not_directive)
	{
		/* checks if the line is a valid commands line and if so store it */
		if(manageInstructionLine(commands, IC, line, line_num) == E_error_occured)
		{
			/* if a label was defined before invalid line we delete it */
			if(is_label_defined == E_label_defined)
				removeLastNode(labels, freeLabel);
			return E_error_occured;
		}
	}
	else
	{
		/* delete the directive type word e.g ".entry" */
		deleteNextWord(line);
		/* checks if the line is a valid directive line and if so store it */
		if(manageDirectiveLine(directives, labels, DC, line, line_num, is_directive) == E_error_occured)
		{
			/* if a label was defined before invalid line we delete it */
			if(is_label_defined == E_label_defined)
				removeLastNode(labels, freeLabel);
			return E_error_occured;
		}
	}
	return E_success;
}



int manageLabelDefinition(list labels, char* line, int* IC, int *DC, int line_num)
{
	char* word;
	int is_label, is_directive;
	word = storeNextWord(line, 0, 0);
	is_label = isLabel(word, 1);
	if(is_label == E_success)
	{
		deleteNextWord(line);
		is_directive = isDirectiveLine(line);
		
		/*if the line is not ".extern" or ".entry" type of directive, keep the label, otherwise discard it */
		if(is_directive != E_ext && is_directive != E_ent)
		{
			if(storeLabel(labels, word, is_directive, IC, DC, line_num) == E_error_occured)
			{
				free(word);
				return E_error_occured;
			}
			else
			{
				free(word);
				return E_label_defined;
			}
		}
		else
		{
			print(E_print_message, E_label_defined_before_ext_ent, line_num);
			free(word);
			return E_label_defined_before_ext_ent;
		}
	}
	else if(is_label == E_label_cross_limit || is_label == E_illegal_characters_in_label_name)
	{
		free(word);
		print(E_print_error, is_label, line_num);
		return E_error_occured;
	}
	free(word);
	/* E_success is also returned in case that a label was not defined */
	return E_label_not_defined;
}


int manageInstructionLine(list commands, int *IC, char* line, int line_num)
{
	char* word = storeNextWord(line, 1, 0);
	int command_num = isOperation(word);
	free(word);
	if(command_num == E_not_operation)
	{
		print(E_print_error, E_undefind_command, line_num);
		return E_error_occured;
	}
	/* operations that have 2 operands */
	if(command_num == E_mov || command_num == E_cmp || command_num == E_add || command_num == E_sub || command_num == E_lea)
	{
		return manageLine2Operands(commands, IC, line, command_num, line_num);
	}
	/* operations that have no operands */
	else if(command_num == E_rts || command_num == E_hlt)
	{
		return manageLineNoOperands(commands, IC, line, command_num, line_num);
	}
	/* operations that have 1 operand */
	else
	{
		return manageLine1Operand(commands, IC, line, command_num, line_num);
	}
}

int manageLine2Operands(list commands, int* IC, char* line, int command_num, int line_num)
{
	list to_insert;
	binaryLine bl;
	char* binary_line;
	int has_errors;

	to_insert = createList();
	has_errors = 0;
	binary_line = calloc(1, sizeof(char) * 10 + 1);
	/* insert the opcode of the operation */
	storeOperationOpcode(binary_line, command_num);

	/* insert the code of the source operand, check for errors */
	if(manageOperand(to_insert, binary_line, line, line_num, command_num, E_src_op, IC) == E_error_occured)
		has_errors = E_error_occured;

	/* check that comma is present after source operand */
	if(commaHandler(line, line_num) != E_success)
	{
		freeList(to_insert, freeBinaryLine);
		free(binary_line);
		return E_error_occured;
	}
		
	/* insert the code of the destination operand, check for errors */
	if(manageOperand(to_insert, binary_line, line, line_num, command_num, E_dest_op, IC) == E_error_occured)
		has_errors = E_error_occured;

	/* check for errors */
	if(has_errors == E_error_occured)
	{
		freeList(to_insert, freeBinaryLine);
		free(binary_line);
		return E_error_occured;
	}
	if(!isEndOfLine(line))
	{
		freeList(to_insert, freeBinaryLine);
		free(binary_line);
		print(E_print_error, E_extra_text, line_num);
		return E_error_occured;
	}
	/* if there are no errors insert the newly created binary lines into the list */
	bl = createBinaryLine(0, 0,"",binary_line, line_num);
	insert(commands, bl);
	(*IC)++;
	insertList(commands, to_insert);
	freeList(to_insert,freeBinaryLine);
	free(binary_line);
	return E_success;
}


int manageLine1Operand(list commands, int *IC, char* line, int command_num, int line_num)
{
	list to_insert;
	binaryLine bl;
	char* binary_line;
	int has_errors;
	has_errors = 0;
	to_insert = createList();
	binary_line = calloc(1, sizeof(char) * 10 + 1);
	initBinaryRep(binary_line);

	/* insert the opcode of the operation */
	storeOperationOpcode(binary_line, command_num);

	/* insert the code of the destination operand, check for errors */
	if(manageOperand(to_insert, binary_line, line, line_num, command_num, E_dest_op, IC) == E_error_occured)
	{
		freeList(to_insert, freeBinaryLine);
		free(binary_line);
		return E_error_occured;
	}

	if(!isEndOfLine(line))
	{
		freeList(to_insert, freeBinaryLine);
		free(binary_line);
		print(E_print_error, E_extra_text, line_num);
		return E_error_occured;
	}
	/* if there are no errors insert the newly created binary lines into the list */
	bl = createBinaryLine(0, 0, "", binary_line, line_num);
	free(binary_line);
	insert(commands, bl);
	(*IC)++;
	insertList(commands, to_insert);
	freeList(to_insert,freeBinaryLine);
	return has_errors;
}	

int manageLineNoOperands(list commands, int* IC, char* line, int command_num, int line_num)
{
	binaryLine bl;
	char* binary_line;
	binary_line = calloc(1, sizeof(char) * 10 + 1);

	/* insert the opcode of the operation */
	storeOperationOpcode(binary_line, command_num);

	/* check for error */
	if(!isEndOfLine(line))
	{
		print(E_print_error, E_extra_text, line_num);
		return E_error_occured;
	}
	bl = createBinaryLine(0, 0, "", binary_line, line_num);
	free(binary_line);
	insert(commands, bl);
	(*IC)++;
	return E_success;
}


int manageOperand(list ls, char* binary_line,  char* line, int line_num, int command_num, int src_or_dest, int *IC)
{
	char *op;
	int op_res;
	op = storeNextWord(line, 1, 1);
	op_res = readOperand(op); 
	storeOperandOpcode(binary_line, op_res, src_or_dest);
	if(storeOpLines(ls, command_num, op, op_res, src_or_dest, IC, line_num) == E_error_occured)
	{
		free(op);
		return E_error_occured;
	}
	free(op);
	return E_success;
}


int storeOpLines(list ls, int command_num, char* op_name, int op_type, int src_or_dest, int *IC, int line_num)
{
	/* check for the type of the operand and call the epropriate function to store it */
	if(op_type == E_op_register)
	{	
		if(command_num == E_lea && src_or_dest == E_src_op)
		{
			print(E_print_error, E_illegal_lea_src_op_register, line_num);
			return E_error_occured;
		}
		storeRegister(ls, op_name[1] - '0', src_or_dest, IC);
		return E_success;
	}
	else if(op_type == E_op_num)
	{
		if(command_num == E_lea && src_or_dest == E_src_op)
		{
			print(E_print_error, E_illegal_lea_src_op_number_address, line_num);
			return E_error_occured;
		}
		if(command_num != E_cmp && command_num != E_prn && src_or_dest == E_dest_op)
		{
			print(E_print_error, E_illegal_command_dest_op_number_address, line_num);
			return E_error_occured;
		}
		substring(op_name, 1);
		manageNum(ls, op_name, line_num, IC, src_or_dest);
		return E_success;
	}
	else if(op_type == E_op_label)
	{
		if(storeLabelInBinaryLine(ls, op_name, line_num, src_or_dest, IC) == E_error_occured)
			return E_error_occured;
		else
			return E_success;
	}
	else /* operand is struct */
	{
		if(storeStructInBinaryLine(ls, op_name, line_num, IC, src_or_dest) == E_error_occured)
			return E_error_occured;
		else
			return E_success;
	}
}


int manageDirectiveLine(list directives, list labels, int *DC, char* line, int line_num, int directive_type)
{
	if(directive_type == E_data)
	{
		if(storeData(directives, line, line_num, 0, DC) == E_error_occured)
		{
			return E_error_occured;
		}
	}
	else if(directive_type == E_string)
	{
		if(storeString(directives, line, line_num, DC) == E_error_occured)
		{
			return E_error_occured;
		}
	}
	else if(directive_type == E_struct)
	{
		if(storeStructData(directives, line, line_num, DC) == E_error_occured)
		{
			return E_error_occured;
		}
	}
	else if(directive_type == E_ent || directive_type == E_ext)
	{
		if(manageExtOrEntLabel(line, directive_type, labels, line_num) == E_error_occured)
			return E_error_occured;
	}
	if(!isEndOfLine(line))
	{
		print(E_print_error, E_extra_text, line_num);
		return E_error_occured;
	}
	return E_success;
}


int commaHandler(char* line, int line_num)
{
	int is_comma = getComma(line);
	if(is_comma == E_missing_comma)
	{
		print(E_print_error, E_missing_comma, line_num);
		return E_error_occured;
		
	}
	else if(is_comma == E_multiple_commas)
	{
		print(E_print_error, E_multiple_commas, line_num);
		return E_error_occured;
	}
	return E_success;
}

void initBinaryRep(char* binary_rep)
{
	int i;
	for(i = 0; i < 10; ++i)
	{
		if(binary_rep[i] < '0')
			binary_rep[i] = '0';
	}
}

int manageExtOrEntLabel(char* line, int is_ext_or_ent, list labels, int line_num)
{
	char* label_name;
	int res;
	label_name = storeNextWord(line, 1, 0);
	res = isLabel(label_name, 0);
	if(res == E_success)
	{
		if(isEndOfLine(line))
		{
			storeExtOrEntLabel(labels, label_name, is_ext_or_ent, line_num);
			return E_success;
		}
		else
		{
			free(label_name);
			print(E_print_error, E_extra_text, line_num);
			return E_error_occured;
		}
	}
	else
	{
		free(label_name);
		print(E_print_error, res, line_num);
		return E_error_occured;
	}
}


int manageNum(list ls, char* line, int line_num, int *IC, int src_or_dest)
{
	int num, res;
	if((res = getNumber(line, &num)) == E_success) 
	{
		if(isNumInRange(num, E_not_directive) == 0) /* check if number is in range */
		{
			printErrorWithOperandTargert(E_num_out_of_range_instruction, line_num, src_or_dest);
			return E_error_occured;
		}
		(*IC)++;
		storeNum(ls, num, 0);
		return E_success;
	}
	else if(res == E_missing_number)
		printErrorWithOperandTargert(E_missing_number, line_num, src_or_dest);
	else if(res == E_illegal_number)
		printErrorWithOperandTargert(E_illegal_number, line_num, src_or_dest);
	return E_error_occured;
}

int isNumInRange(int num, int is_directive)
{
	if(is_directive == E_not_directive)
		return (num >= -128 && num <= 127);
	else
		return (num >= -512 && num <= 511);
}
