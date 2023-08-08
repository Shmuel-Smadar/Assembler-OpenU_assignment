#include "store.h"


int storeData(list ls, char* line, int line_num, int is_struct, int *IC_or_DC)
{
	int num, res;
	int has_data;
	num = 0;
	has_data = 0;
	res = 0;

	res = getComma(line);
	if(res != E_missing_comma)
	{
		print(E_print_error, E_missing_number_before_comma, line_num);
		return E_error_occured;
	}

	while((res = getNumber(line, &num)) == E_success) /* continue as long as we get a number from the line */
	{
		if(isNumInRange(num, E_directive) == 0) /* check if the number is in range */
		{
			print(E_print_error, E_num_out_of_range_directive, line_num);
			return E_error_occured;
		}
		storeNum(ls, num , 1);
		has_data = 1;
		(*IC_or_DC)++;
		if(is_struct)
			break;
		res = getComma(line); /* get the next comma */
		if(res == E_multiple_commas) /* if there were multiple commas */
		{
			print(E_print_error, E_multiple_commas, line_num);
			return E_error_occured;
		}
		else if(res == E_missing_comma) /* if there was no comma */
		{
			if(isEndOfLine(line)) /* if there is no argument next in line */
			{
				return E_success;
			}
			else /* if there is an argument next but comma was not found */
			{
				print(E_print_error, E_missing_comma, line_num);
				return E_error_occured;
			}
		}
		
	}
	if(res == E_success)
		return res;
	
	if(res == E_illegal_number)
	{
		print(E_print_error, E_illegal_number, line_num);
		return E_error_occured;
	}
	else if(res == E_missing_number && has_data != 0)
	{
		print(E_print_error, E_missing_number_after_comma, line_num);
		return E_error_occured;
	}
	else if(res == E_missing_number && has_data == 0)
	{
		print(E_print_error, E_missing_number, line_num);
		return E_error_occured;
	}
	return E_success;
}


void storeNum(list ls, int num, int is_directive)
{
	int i;
	char* binary_num;
	binaryLine bl;

	binary_num = calloc(1, sizeof(char) * 10 + 1);
	if(is_directive)
	{
		i = 9;
	}
	else
	{
		binary_num[8] = '0';
		binary_num[9] = '0';
		i = 7;
	}
	for(; i >= 0; --i)
	{
		binary_num[i] = '0' + (num & 1);
		num = (num >> 1);
	}
	bl = createBinaryLine(E_op_num, 0, "", binary_num, -1);
	insert(ls, bl);
	free(binary_num);
}


int storeString(list directives, char* line, int line_num, int *DC)
{
	char* str;
	int i, res;
	res = i = 0;
	str = getString(line, &res);
	if(res == E_missing_string)
	{
		print(E_print_error, E_missing_string, line_num);
		return E_error_occured;
	}
	else if(res == E_illegal_string)
	{
		print(E_print_error, E_illegal_string, line_num);
		return E_error_occured;
	}
	while(str[i] != '\0')
	{
		storeNum(directives, str[i], 1);
		++i;
		(*DC)++;
	}
	storeNum(directives, 0, 1);
	(*DC)++;
	free(str);
	return E_success;
}

void storeOperandOpcode(char* binary_line, int op_res, int src_or_dest)
{
	int i;
	if(src_or_dest == E_src_op)
		i = 4;
	else
		i = 6;
	if(op_res == E_op_register)
	{
		binary_line[i++] = '1';
		binary_line[i] = '1';
	}
	else if(op_res == E_op_num)
	{
		binary_line[i++] = '0';
		binary_line[i] = '0';
	}
	else if(op_res == E_op_label)
	{
		binary_line[i++] = '0';
		binary_line[i] = '1';
	}
	else if(op_res == E_op_struct)
	{
		binary_line[i++] = '1';
		binary_line[i] = '0';
	}
}

void storeRegister(list ls, int register_num, int src_or_dest, int* IC)
{
	binaryLine b1;
	int i, j, second_reg;
	char* binary_rep;
	second_reg = 0;
	
	/* check if previous binarycode that was stored is also a register, in that case merge them */
	if(src_or_dest == E_dest_op && ((binaryLine)getLast(ls)) != NULL
	 && binaryLineGetOpType(((binaryLine)getLast(ls))) == E_op_register)
	{
		second_reg = 1;
		binary_rep = binaryLineGetBinaryCode(((binaryLine)getLast(ls)));
	}
	else
	{
		binary_rep = calloc(1, 10 * sizeof(char) + 1);
		initBinaryRep(binary_rep);
	}
	if(src_or_dest == E_src_op)
	{
		i = 0;
		j = 3;
	}
	else if(src_or_dest == E_dest_op)
	{
		i = 4;
		j = 7;
	}
	for(; i <= j; --j)
	{
		binary_rep[j] = (register_num & 1) + '0';
		register_num = (register_num >> 1);
	}
	if(second_reg)
		return;

	b1 = createBinaryLine(E_op_register, 0, "", binary_rep, -1);
	insert(ls, b1);
	free(binary_rep);
	(*IC)++;
}


void storeOperationOpcode(char* binary_line, int command_num)
{
	int i;
	const char* commands_opcode[] = {"0000", "0001", "0010", "0011", "0100", "0101",
	 "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};

	initBinaryRep(binary_line);
	for(i = 0; i < 4; ++i)
	{
		binary_line[i] = commands_opcode[command_num][i];
	}
	binary_line[8] = '0';
	binary_line[9] = '0';
}

int storeStructData(list directives, char* line, int line_num, int *DC)
{
	int res = storeData(directives, line, line_num, 1, DC);
	if(res == E_error_occured)
		return res;

	res = commaHandler(line, line_num);
	if(res != E_success)
	{
		return E_error_occured;
	}
	res = storeString(directives, line, line_num, DC);
	return res;
}

int storeLabel(list labels, char* label_name, int is_directive, int *IC, int* DC, int line_num)
{
	label l1, l2;
	l1 = createLabel(E_not_ext_or_ent, E_not_ext_or_ent, -1 ,label_name, 0, line_num);
	l2 = listSearch(labels, l1, compareLabel);
	if(l2 != NULL)
	{
		if(labelGetDefLineNum(l2) != E_label_not_yet_defined)
		{
			freeLabel(l1);
			print2Lines(E_print_error, E_duplicate_label_definitions, labelGetDefLineNum(l2), line_num);
			return E_error_occured;
		}
		else if(labelGetExtOrEnt(l2) == E_ext)
		{
			freeLabel(l1);
			print2Lines(E_print_error, E_defined_label_declared_ext, labelGetExtEntLineNum(l2), line_num);
			return E_error_occured;
		}
		freeLabel(l1);
		l1 = l2;
		labelSetDefLineNum(l1, line_num);
	}
	else
	{
		insert(labels, l1);
	}
	if(is_directive == E_not_directive)
	{
		labelSetDecAddress(l1, *IC);
		labelSetICorDC(l1, E_IC);
	}
	else
	{
		labelSetDecAddress(l1, *DC);
		labelSetICorDC(l1, E_DC);
	}
	return E_success;
}

void storeLabelAddress(binaryLine bl, label l1)
{
	char* binary_rep;
	int i, num;
	binary_rep = calloc(1, sizeof(char) * 10 + 1);
	initBinaryRep(binary_rep);
	/* mark if the label is external */
	if(labelGetExtOrEnt(l1) == E_ext)
	{
		binary_rep[9] = '1';
		binaryLineSetBinaryCode(bl, binary_rep);
		return;
	}
	else
	{
		binary_rep[8] = '1';
	}
	/* copy to the binary code the address of the label */
	num  = labelGetDecAddress(l1);
	for(i = 7; i >= 0; --i)
	{
		binary_rep[i] = '0' + (num & 1);
		num = (num >> 1);
	}
	binaryLineSetBinaryCode(bl, binary_rep);
	return;
}

int storeExtOrEntLabel(list labels, char* label_name, int ext_ot_ent, int line_num)
{
	label l1, l2;
	l1 = createLabel(ext_ot_ent, line_num, -1, label_name, 0, E_label_not_yet_defined);
	
	/* search to see if label with the same name already present in the list */
	l2 = listSearch(labels, l1, compareLabel); 
	
	if(l2 != NULL) 
	{
		/* if the found label was already declared as extern or entry print an error */
		if(labelGetExtOrEnt(l2) == E_ext || labelGetExtOrEnt(l2) == E_ent)
		{
			free(label_name);
			free(l1);
			print2Lines(E_print_error, E_label_declared_twice,labelGetExtEntLineNum(l2), line_num);
			return E_error_occured;
		}
		/* if the label is declared as external but was already defined */
		else if(ext_ot_ent == E_ext && labelGetDefLineNum(l2) != E_label_not_yet_defined)
		{
			free(label_name);
			freeLabel(l1);
			print2Lines(E_print_error, E_ext_label_defined,labelGetDefLineNum(l2), line_num);
			return E_error_occured;
		}
		else /* if the found label wasn't already declared as extern or entry, declare it */
		{
			freeLabel(l1);
			free(label_name);
			labelSetExtOrEnt(l2, ext_ot_ent);
			labelSetExtEntLineNum(l2, line_num);
			return E_success;
		}
	}
	insert(labels, l1);
	free(label_name);
	return E_success;	
}

int storeLabelInBinaryLine(list ls, char* label_name, int line_num, int src_or_dest, int *IC)
{
	int is_label;
	is_label = isLabel(label_name, 0);
	if(is_label == E_success)
	{
		binaryLine b1;
		b1 = createBinaryLine(E_op_label, src_or_dest, label_name, "", line_num);
		insert(ls, b1);
		(*IC)++;
		return E_success;
	}
	/*the operand is not label, use 'checkOpErr' function to give appropriate error */
	printErrorWithOperandTargert(checkOpErr(label_name), line_num, src_or_dest);
	return E_error_occured;
}

int storeStructInBinaryLine(list ls, char* op_name, int line_num, int *IC, int src_or_dest)
{
	int is_struct = isStruct(op_name);
	if(is_struct == E_success)
	{
		binaryLine b1, b2;
		int len = strlen(op_name);
		op_name[len - 2] = '\0';
		b1 = createBinaryLine(E_op_struct, src_or_dest, op_name, "", line_num);
		
		if(op_name[len - 1] == '1')
			b2 = createBinaryLine(0, 0, "", "0000000100", line_num);
		else if(op_name[len - 1] == '2') /* we verified that the number is only 1 or 2 in the function 'isStruct' */
			b2 = createBinaryLine(0, 0, "", "0000001000", line_num);
		insert(ls, b1);
		insert(ls, b2);
		*IC += 2;
		return E_success;
	}
	printErrorWithOperandTargert(is_struct, line_num, src_or_dest);
	return E_error_occured;
}