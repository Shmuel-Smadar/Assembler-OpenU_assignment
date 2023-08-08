#include "second_pass.h"

int secondParsing(list labels, list commands)
{
	binaryLine bl;
	label l1;
	int has_errors = 0;
	printNoLine(E_print_message, E_assembler_second_part_started);
	/* go through the binary line and labels lists */
	startGoingThroughList(labels);
	startGoingThroughList(commands);
	l1 = getNextNodeData(labels);
	bl = getNextNodeData(commands);
	while(l1 != NULL || bl != NULL)
	{
		/* if the current binary line is not null and does not represnet a label or a struct */
		if(bl != NULL && binaryLineGetOpType(bl) != E_op_label && binaryLineGetOpType(bl) != E_op_struct)
		{
			bl = getNextNodeData(commands); /* get the next one */
		}
		/* if the current label is not null and is not external or entry */
		else if(l1 != NULL && labelGetExtOrEnt(l1) == E_not_ext_or_ent)
		{
			l1 = getNextNodeData(labels); /* get the next one */
		}
		/* if the current binary line is null or if the current label declaration line as entry or external is lower than the line of the binaryLine */
		else if(bl == NULL || (l1 != NULL && labelGetExtEntLineNum(l1) < binaryLineGetLineNum(bl)))
		{
			/* check if the label had been declared as entry without definition */
			if(labelGetExtOrEnt(l1) == E_ent && labelGetDefLineNum(l1) == E_label_not_yet_defined)
			{
				has_errors = E_error_occured;
				print(E_print_error, E_ent_label_not_defined, labelGetExtEntLineNum(l1));
			}
			l1 = getNextNodeData(labels);	
		}
		/* if the current label is null or if the current binaryLine has lower line num that the label */
		else if(l1 == NULL || (bl != NULL && binaryLineGetLineNum(bl) < labelGetExtEntLineNum(l1)))
		{
			/* call a function to write the address of the label in the binaryLine, if the label will not be found
			it will print an error */
			if(manageLabelAddress(labels, bl) == E_error_occured)
				has_errors = E_error_occured;
			bl = getNextNodeData(commands);
		}
	} 
	if(has_errors == 0)
		printNoLine(E_print_message, E_assembler_second_part_finished_success);
	else
		printNoLine(E_print_message, E_assembler_second_part_finished_fail);
	return has_errors;
}

int manageLabelAddress(list labels, binaryLine bl)
{
	label l1, l2;
	l1 = createLabel(-1, -1, -1, binaryLineGetLabelName(bl), -1, E_label_not_yet_defined);
	l2 = listSearch(labels, l1, compareLabel);
	freeLabel(l1);
	if(l2 == NULL || (labelGetExtOrEnt(l2) != E_ext && labelGetDefLineNum(l2) == E_label_not_yet_defined))
	{
		printErrorWithOperandTargert(E_label_used_not_defined, binaryLineGetLineNum(bl), binaryLineGetSrcOrDest(bl));
		return E_error_occured;
	}
	storeLabelAddress(bl,l2);
	return E_success;
}
