#include "label.h"

struct label
{
	int ic_or_dc;
	int ext_or_ent;
	int dec_address;
	int def_line_num;
	int ext_ent_line_num;
	char* label_name;
};

label createLabel(int ext_or_ent, int ext_ent_line_num, int dec_address, char* label_name, int ic_or_dc, int def_line_num)
{
	label l1;
	l1 = calloc(1, sizeof(struct label));
	l1->ext_or_ent = ext_or_ent;
	l1->ext_ent_line_num = ext_ent_line_num;
	l1->dec_address = dec_address;
	l1->label_name = calloc(1, sizeof(char) * strlen(label_name) + 1);
	l1->ic_or_dc = ic_or_dc;
	l1->def_line_num = def_line_num;
	strcpy(l1->label_name, label_name);
	return l1;
}

char* labelGetName(label l1)
{
    return l1->label_name;
}

int labelGetExtEntLineNum(label l1)
{
    return l1->ext_ent_line_num;
}

int labelGetDecAddress(label l1)
{
    return l1->dec_address;
}

int labelGetDefLineNum(label l1)
{
    return l1->def_line_num;
}

int labelGetExtOrEnt(label l1)
{
    return l1->ext_or_ent;
}

int labelGetICorDC(label l1)
{
    return l1->ic_or_dc;
}

void labelSetExtOrEnt(label l1, int ext_or_ent)
{
	l1->ext_or_ent = ext_or_ent;
}

void labelSetExtEntLineNum(label l1, int ext_ent_line_num)
{
    l1->ext_ent_line_num = ext_ent_line_num;
}

void labelSetDefLineNum(label l1, int def_line_num)
{
    l1->def_line_num = def_line_num;
}

void labelSetICorDC(label l1, int ic_or_dc)
{
    l1->ic_or_dc = ic_or_dc;
}

void labelSetDecAddress(label l1, int dec_address)
{
    l1->dec_address = dec_address;
}

int compareLabel(void* l1, void* l2)
{
	if(strcmp(((label)l1)->label_name,((label)l2)->label_name) == 0)
	{
		return 1;
	}
	return 0;		
}

void freeLabel(void* data)
{
	free(((label)data)->label_name);
	free(((label)data));
	data = NULL;
}

void labelFixAddress(void* l1, int IC)
{
	if(((label)l1)->ic_or_dc == E_DC)
	{
		((label)l1)->dec_address += IC + 100;
	}
	else if(((label)l1)->ic_or_dc == E_IC)
	{
		((label)l1)->dec_address += 100;
	}
}