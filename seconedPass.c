/*Function to go over outputAm that conatin only  assembly commands(without .entry and .extern)*/
#include "seconedPass.h"

const char* opecodes[] = {
    "mov", "cmp", "add", "sub", "not", "clr", "lea", "inc",
    "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop"
};

void SeconedPass(FILE* outputAm,FILE* outputObj,LabelList* label_index){

	FILE* noEntryExtern=DeleteExternEntry(outputAm);/* delete .extern and .entry from file*/
	BinaryLines* line_list=Linestlist(noEntryExtern);/*list of all assembly lines*/
	LabelList* data_string_list=DataStringList(outputAm);/*List of data and string labels and location in table*/
	BinaryLines* word_list=WordList(noEntryExtern,data_string_list,label_index);/*list of all binary words*/
	EncodeBinaryLines(word_list,outputObj);/*print lines and words*/
	
	FreeLabelList(data_string_list);
 	FreeLines(line_list);
 	FreeLines(word_list);
}

