
#include "share.h" 


/*A linked list to store information about external labels.*/
typedef struct linekdExtern {
    char externLabel[MAX_LABEL_LENGTH];
    struct linekdExtern* next;
} linekdExtern;
/*Performs the first pass over the assembly code, collecting necessary information.Returns: A pointer to the head of a linked list of labels.*/
LabelList* FirstPass(FILE* output_am,FILE* output_ent,FILE* output_ext,FILE* output_obj);
/*Move down in file  the .string and .data lines*/
void MoveDown(FILE* output_am);
/*Find the label names and location in table+print find ic and dc ,returns A pointer to the head of a linked list of labels.*/
LabelList* LabelIndex(FILE* output_am,Data* dcIc);
/*Prints the contents of a label linked list to the specified file.*/
void PrintList(LabelList* head,FILE* file);
/*Adds a node to a label linked list.Parameters: Pointer to the head of the linked list, label name, line number.*/
void AddNode(LabelList** head, const char* nameOfLabel, int lineNumber);
/*Finds and returns entry nodes from the assembly file.*/
LabelList* EntryNodes(FILE* output_am ,LabelList* labels);
/*Handles labels marked as external in the assembly file.*/
LabelList* LabelsExtern(FILE* output_am,FILE* output_ext);
/*Prints entry nodes to the specified file.*/
void PrintEntry(FILE* output_ent,LabelList* entryNodes);
/*Frees memory allocated to a label linked list.*/
void FreeLabelList(LabelList* head);
/*Counts the number of lines in a given string, considering instruction counters.

Parameters: Pointer to the line, data containing instruction counters.
Returns: Number of lines.
ExternList(FILE*)
Creates a list of external labels.

Parameters: Pointer to the assembly file.
Returns: Pointer to the head of the linked list of external labels.
AddExternLabel(linekdExtern**, const char*)
Adds an external label to a linked list.

Parameters: Pointer to the head of the external labels linked list, label name.
PrintExtern(LabelList*, FILE*)
Prints external labels to the specified file.

Parameters: Pointer to the head of the linked list of labels, pointer to the file.
AddExternLineLabel(LabelList**, const char*, int)
Adds an external line label to the linked list.

Parameters: Pointer to the head of the linked list, label name, line number.
FindExternLabel(linekdExtern*, const char*)
Finds an external label in the linked list.

Parameters: Pointer to the head of the linked list, label name.
Returns: Pointer to the node containing the label, if found.
PrintExternLabels(FILE*, FILE*, LabelList*)
Prints external labels and their line numbers to the specified files.

Parameters: Pointers to the assembly file, external file, and the head of the linked list of external line labels.
FreeLinkedExtern(linekdExtern*)
Frees memory allocated to a linked list of external labels.

Parameters: Pointer to the head of the linked list.
NumberOfLines(char*)
Counts the number of lines in a given string. parameters: Pointer to the line. returns: Number of lines.*/
int NumbersOfLines(  char* line,Data* dcIc);
/*Creates a list of external labels.*/
linekdExtern* ExternList(FILE* output_am);
/*Adds an external label to a linked list.*/
void AddExternLabel(linekdExtern** head, const char* label_name);
/*Adds an external line label to the linked list.*/
void AddExternLineLabel(LabelList** head, const char* nameOfLabel, int lineNumber);
/*Finds an external label in the linked list.*/
linekdExtern* FindExternLabel(linekdExtern* head, const char* label_name);
/*Frees memory allocated to a linked list of external labels.*/
void FreeLinkedExtern(linekdExtern* head);
/*Counts the number of words create in binary in a given line.*/
 int NumberOfLines(char* line);



