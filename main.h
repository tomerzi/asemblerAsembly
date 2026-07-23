#include "firstPass.h"
#include "seconedPass.h"
/* Struct to encapsulate the result of the first pass, including labels and data. */
typedef struct {
    LabelList* labelList;
    Data* dcIcData;
} FirstPassResult;

char name[MAX_LINE_LENGTH];
char ext_file[MAX_LINE_LENGTH];
char ent_file[MAX_LINE_LENGTH];
char obj_file[MAX_LINE_LENGTH];
int error;
FILE* input;
FILE* output_am;
FILE* output_ext;
FILE* output_ent;
FILE* output_obj;
LabelList* entry_nodes;


/* Processes the input file, find the macros and open them into output_am. Input: File pointers to the input and output .am files.*/
void PreAssembler(FILE* input,FILE* output_am);

/* Checks for errors in the output .am file. Output: Returns 1 if errors are found, 0 otherwise.*/
int Errors(FILE* output_am);

/* Performs the first pass on the .am file. Output: Returns a LabelList* containing labels and location in table, prints .ext and .ent files, and prints ic,dc to .ob file.*/
LabelList* FirstPass(FILE* output_am,FILE* output_ent,FILE* output_ext,FILE* output_obj);

/* Prints the binary file. */
void SeconedPass(FILE* output_am,FILE* output_obj,LabelList* label_index );











 

 
