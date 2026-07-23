/*Function that make a binary words of 12 bits and return the list*/

#include "seconedPass.h"
BinaryLines* OpecodeBinary(FILE* outputAm);
BinaryLines* SourceBinary(FILE* noEntryExtern,LabelList* data_string_list);

/*Find all lists of binary and then combined all togheter , there is the same amount of words in every list because its go over the same input */
BinaryLines* WordList(FILE* noEntryExtern,LabelList* data_string_list,LabelList* label_index ){
	
	BinaryLines* source_binary=SourceBinary(noEntryExtern,data_string_list);/*list of all source in binary*/	
	BinaryLines* opecode_binary=OpecodeBinary(noEntryExtern);/*list of all opecode in binary*/
	BinaryLines* target_binary=TargetBinary(noEntryExtern,label_index);/*list of all target in binary*/
	BinaryLines* are_binary=AreBinary(noEntryExtern);/*list of all ARE in binary*/
	BinaryLines* combined_binary=CombinedBinaryLines( source_binary,  opecode_binary,  target_binary,  are_binary);/*List of all command binary code*/  
	BinaryLines* all_binary=AllBinary(noEntryExtern,combined_binary,label_index);

return all_binary;
}
