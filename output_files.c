#include "output_files.h"

void createOBFile(char* filename, list commands, list directives, int IC, int DC)
{
    binaryLine bl;
    FILE *ob;
	char *filename_with_ob, res[3];
    int address = 100;

    /* create .ob file */
	filename_with_ob = concat(filename, ".ob");
	ob = fopen(filename_with_ob, "w");
    free(filename_with_ob);
    
    /* writes IC and DC values in machine code */
    fputs(DecToNewBase(IC, res), ob);
    fputs("\t", ob);
    fputs(DecToNewBase(DC, res), ob);

    /* go through the command list and write the address and the sentences in machine code */
    startGoingThroughList(commands);
    bl = getNextNodeData(commands);
    while(bl != NULL)
    {
        fputs("\n", ob);
        fputs(DecToNewBase(address++, res), ob);
        fputs("\t", ob);
        fputs(stringBinaryToNewBase(binaryLineGetBinaryCode(bl), res), ob);
        bl = getNextNodeData(commands);
        
    }
    /* go through the directives list and write the address and the sentences in machine code */
    startGoingThroughList(directives);
    bl = getNextNodeData(directives);
    while(bl != NULL)
    {
        fputs("\n", ob);
        fputs(DecToNewBase(address++, res), ob);
        fputs("\t", ob);
        fputs(stringBinaryToNewBase(binaryLineGetBinaryCode(bl), res), ob);
        bl = getNextNodeData(directives);
    }
     fclose(ob);
}

void createENTFile(char* filename, list labels)
{
    label l1;
    FILE* ent;
    char* filename_with_ent, res[3];
    int is_file_empty = 1;

    /* create .ent file */
    filename_with_ent = concat(filename, ".ent");
    ent = fopen(filename_with_ent, "w");
    
    /* go through the list and write the name of the entry labels and the definition address in machine code */
    startGoingThroughList(labels);
    l1 = getNextNodeData(labels);
    while(l1 != NULL)
    {
        if(labelGetExtOrEnt(l1) == E_ent)
        {
            if(!is_file_empty)
                fputs("\n", ent);
            is_file_empty = 0;
            fputs(labelGetName(l1), ent);
            fputs("\t", ent);
            fputs(DecToNewBase(labelGetDecAddress(l1), res), ent);
            
        }
        l1 = getNextNodeData(labels);
    }
    if(is_file_empty)
    {
        printNoLine(E_print_message, E_ent_labels_not_found);
        remove(filename_with_ent);
    }
    free(filename_with_ent);
    fclose(ent);
}

void createEXTFile(char* filename, list commands, list labels)
{
    label l1, l2;
    binaryLine bl;
    FILE *ext;
	char *filename_with_ext, res[3];
    int i, is_file_empty;
    i = 100;
    is_file_empty = 1;

     /* create .ext file */
	filename_with_ext = concat(filename, ".ext");
	ext = fopen(filename_with_ext, "w");

     /* go through the list and write the names of the external labels and the addresses where they are used in machine code */
    startGoingThroughList(commands);
    bl = getNextNodeData(commands);
    while(bl != NULL)
    {
        if(binaryLineGetOpType(bl) == E_op_label || binaryLineGetOpType(bl) == E_op_struct)
        {
            l1 = createLabel(E_not_ext_or_ent, E_not_ext_or_ent, 0, binaryLineGetLabelName(bl),0, -1);
            l2 = listSearch(labels, l1, compareLabel);
            if(labelGetExtOrEnt(l2) == E_ext)
            {
                if(!is_file_empty)
                    fputs("\n", ext);
                is_file_empty = 0;
                fputs(binaryLineGetLabelName(bl), ext);
                fputs("\t", ext);
                fputs(DecToNewBase(i, res),ext);
            }
            freeLabel(l1);
        }
        i++;
        bl = getNextNodeData(commands);
    }
    if(is_file_empty)
    {
        printNoLine(E_print_message, E_ext_labels_not_found);
        remove(filename_with_ext);
    }        
    free(filename_with_ext);
    fclose(ext);
}