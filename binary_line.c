#include "binary_line.h"


struct binaryLine
{
	int op_type;
	int src_or_dest;
	int line_num;
	char* label_name;
	char* binary_code;
};

binaryLine createBinaryLine(int op_type, int src_or_dest, char* label_name, char* binary_code, int line_num)
{
	binaryLine bl = calloc(1, sizeof(struct binaryLine));
	bl->op_type = op_type;
	bl->src_or_dest = src_or_dest;
	bl->label_name = calloc(1, sizeof(char) * strlen(label_name) + 1);
	bl->binary_code = calloc(1, sizeof(char) * strlen(binary_code) + 1);
	bl->line_num = line_num;
	strcpy(bl->label_name, label_name);
	strcpy(bl->binary_code, binary_code);
	return bl;
}

char* binaryLineGetLabelName(binaryLine bl)
{
	return bl->label_name;
}

char* binaryLineGetBinaryCode(binaryLine bl)
{
	return bl->binary_code;
}

int binaryLineGetSrcOrDest(binaryLine bl)
{
	return bl->src_or_dest;
}

void binaryLineSetBinaryCode(binaryLine bl, char* binary_code)
{
	free(bl->binary_code);
	bl->binary_code = binary_code;
}

int binaryLineGetLineNum(binaryLine bl)
{
	return bl->line_num;
}

void printBinaryLine(void * bl)
{
	printf("binary code :|%s|\n", ((binaryLine)bl)->binary_code);
}

int binaryLineGetOpType(binaryLine bl)
{
	return bl->op_type;
}

void freeBinaryLine(void* data)
{
	if(data == NULL)
		return;
	free(((binaryLine)data)->binary_code);
	free(((binaryLine)data)->label_name);
    free(((binaryLine)data));
	data = NULL;
}
