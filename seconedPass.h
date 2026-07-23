/*Header of seconed pass*/


#include "share.h"
#define WORD 12
extern const char* opecodes[];
/* A linked list structure that holds assembly lines.*/
typedef struct BinaryLines {/*All assembly lines  */
    char line[MAX_LINE_LENGTH];  
    struct BinaryLines* next;  
} BinaryLines;
/* A linked list structure that holds binary words.*/
typedef struct Word {/*All assembly lines  */
    char line[WORD+1];  
    struct Word* next;  
} Word;

/*Deletes external and entry labeled lines from a given file.*/
FILE* DeleteExternEntry(FILE* outputAm);
/*Returns a linked list containing the lines from the provided file.*/
BinaryLines* Linestlist(FILE* noEntryExtern);
/* Creates a list of data and string labels from the provided file.*/
LabelList* DataStringList(FILE* noEntryExtern);
/* Creates a binary word list from the given file and provided label lists.*/
BinaryLines* WordList(FILE* noEntryExtern,LabelList* data_string_list,LabelList* label_index );
/* Encodes binary lines and writes them to the specified output file.*/
void EncodeBinaryLines(BinaryLines* word_list,FILE* outputObj) ;
/* Frees the memory allocated for the provided label list.*/
void FreeLabelList(LabelList* head);
/* Frees the memory allocated for the provided binary lines list.*/
void FreeLines(BinaryLines* head);
/*: Returns the source binary lines from the provided file and data string list*/
BinaryLines* SourceBinary(FILE* noEntryExtern,LabelList* data_string_list);
/* Returns the opcode binary lines from the provided file.*/
BinaryLines* OpecodeBinary(FILE* noEntryExtern);
/* Returns the target binary lines from the provided file and data string list.*/
BinaryLines* TargetBinary(FILE* noEntryExtern,LabelList* data_string_list);
/*Returns the ARE (Absolute, Relocatable, External) binary lines from the provided file.*/
BinaryLines* AreBinary(FILE* noEntryExtern);
/* Combines different binary line categories into a single linked list.*/
BinaryLines* CombinedBinaryLines(BinaryLines* source_binary, BinaryLines* opecode_binary, BinaryLines* target_binary, BinaryLines* are_binary);
/*Returns all binary lines from the provided file and combined binary list.*/
BinaryLines* AllBinary(FILE* noEntryExtern,BinaryLines* combined_binary,LabelList* label_index);
/* Adds a node to the provided label list with the given name and line number.*/
void AddNode(LabelList** head, const char* nameOfLabel, int lineNumber);
/*: Returns the number of binary words in the given character array.*/
 int NumberOfLines(char* line);
 /*Prints the lines in the provided binary lines list.*/
void PrintLines(BinaryLines* head);
/*: Adds a line to the provided binary lines list.*/
void AddLine(BinaryLines** head, const char* line);
/*: Finds a label with the given name in the provided label list.*/
LabelList* FindInfoLabel(LabelList* head, const char* nameOfLabel);
/*Return the binary word if there is regestir in arg1 or in both argemnts*/
void AtBinary(char *number_binary,char *arg1,char *arg2);
/* Checks if a given string represents a valid number and returns the int if it is.*/
int IsValidNumber(const char *str, int *number);
/*Converts a given number to its binary representation.*/
void NumberBinary(char* number_binary,int number);
/*Performs binary operations related to labels.*/
void LabelBinary(LabelList* label_index,char *number_binary,LabelList* foundLabel);
/*Return the binary word if there is regestir in arg2*/
void Arg2Binary(char *number_binary,char *arg2);
/* Converts a given string to its ASCII representation.*/
BinaryLines* StringAscii(char* first_word);
/* Gets the ASCII representation of a character.*/
void GetStringASCII(char c, char *result);
/*Returns the opcode for a given operand.*/
char* Opecode(char* oprand);
/*Encodes a given input into base bits.*/
void EncodeBaseBits(unsigned short input, char output[2]);
/* Converts data to its ASCII representation.*/
BinaryLines* DataAscii(const char* arg1);
/*Finds the label with the given name in the provided list.*/
int FindLabel(LabelList* head, const char* nameOfLabel);
/* Gets the 12-bit binary representation of a given number.*/
void Get12BitBinary(int number, char *result);
/*Processes external labels and writes them to the specified files.*/
LabelList* LabelsExtern(FILE* outputAm,FILE* outputExt);
