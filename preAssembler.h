#include "share.h"

/* Defines macros for "mcro" and "endmcro" keywords. */
#define MCRO "mcro"
#define ENDMCRO "endmcro"

/* Command structure representing a line within a macro. */
typedef struct Command {
        char line[MAX_LINE_LENGTH]; 
} Command;

/* Node structure to hold commands in a linked list. */
typedef struct CommandNode{
       Command* commandData; 
       struct CommandNode* next;
} CommandNode;

/* Represents a macro along with its associated commands. */
typedef struct Mcros {
  CommandNode* allLines;
  char* mcroName;
  struct Mcros* next;
} Mcros;

/* Structure for linking multiple macros in a linked list. */
typedef struct linkedMcros {
    Mcros* mcroNode;
    struct linkedMcros* nextNode;
} linkedMcros;

extern char dataLine[MAX_LINE_LENGTH];
extern char line[MAX_LINE_LENGTH];
extern char label[MAX_LINE_LENGTH];
extern char label_name[MAX_LINE_LENGTH];
extern char firstWord[MAX_LINE_LENGTH];
extern char nameOfMcro[MAX_LINE_LENGTH];

/* Find all macros in the input and open them in the outputAm file. */
void PreAssembler(FILE* input,FILE* outputAm);

/* Add a line to a macro. */
void AddLineToMcro(Mcros* mcro, const char* line);

/* Link macros found in the input file. */
linkedMcros* LinkedMcro(FILE *input);

/* Free memory associated with linked macros. */
void FreeLinkedMcros(linkedMcros* mcros);

/* Open a macro and write it to the outputAm file. */
void OpenMcro(FILE* input,FILE* outputAm, linkedMcros* mcroList);

/* Print the lines associated with a specific macro to the output file. */
void PrintMcroLines(FILE* file, Mcros* macro);

/* Find a macro by name in the linked list of macros (alternative function). */
Mcros* FindMcroByName(linkedMcros* head, const char* name);

