#include "share.h"
typedef struct labels {
    char nameOfLabel[MAX_LABEL_LENGTH];
    struct labels* next;
} labels;
extern int line_idx;
extern char newLine[MAX_LINE_LENGTH];
extern char err_buf[MAX_LINE_LENGTH];
extern labels* listOfLabels;
extern labels* listOfExtern;
extern labels* listOfEntry;
extern int flag;
extern int vars;
 /*AddLabel: This function attempts to add a label to a linked list, checking for duplicates and handling errors appropriately.

VaildStringData: It looks like this function is intended to validate a specific line format within a file, likely within an assembly file. It processes lines with specific operations and checks their validity, printing errors when something is incorrect.

CheckForCommonLabels: This function checks if there are any common labels in two different lists of labels, probably corresponding to 'extern' and 'entry' in assembly language.

PrintLabels: This prints out all labels from a given linked list.

CheckLabelsForLettersAndDigits: Ensures that labels only contain letters and digits.

Labels, Extern, Entry: These functions seem to handle specific types of labels, possibly retrieving them from a file.

CountTwoWords, CountOneWord, CountZeroWord: These functions appear to be validating the number of operands for specific operations in an assembly language, presumably based on different instruction formats.*/
int AddLabel(labels** head, const char* name);/* Check if a label with the same name already exists*/
int CheckForCommonLabels(labels* listOfExtern, labels* listOfEntry);
void PrintLabels(labels* head);
labels* Labels(FILE* output_am,int* is_vaild);
int CheckLabelsForLettersAndDigits(labels* head);
labels* Extern(FILE* output_am,int* is_vaild);
labels* Entry(FILE* output_am,int* is_vaild);
int CountOneWord(FILE* output_am,const char* vaildWordsNeedOne[],int size);
int CountTwoWords(FILE* output_am,const char* vaildWordsNeedTwo[],int size);
int CountZeroWord(FILE* output_am,const char* vaildWordsNeedZero[],int size);
int IsValidArgument(const char* arg, const char* registers[],int registersSize, labels* listOfLabels);
int VaildArguemnts(FILE* output_am, const char* registers[],int registersSize, labels* listOfLabels,const char* vaildWordsNeedTwo[],int sizeNeedTwo, const char* vaildWordsNeedOne[],int sizeNeedOne);
int CheckOprand(FILE*  output_am, const char* validWordsNeedTwo[],int sizeTWo,const char* vaildWordsNeedOne[],int sizeNeedOne, const char* vaildWordsNeedZero[],int sizeNeedZero);
labels* MergeLists(labels* list1, labels* list2);
int VaildStringData(FILE* output_am);
