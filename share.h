#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#ifndef SHARE_H
#define SHARE_H

#define MAX_LINE_LENGTH 81
#define MAX_LABEL_LENGTH 31
#define MEMORY 100
#define EXTERN ".extern"
#define ENTRY ".entry"
#define SPACE " "
#define COMMA ","
#define COLON ":"
#define COMMENT ";"
#define FIRST 1
#define MAX_LINES 1024
#define AT '@'
#define BINARYWORD 12
#define OPRANDS 15
#define TARGETSIZE 4
#define OPECODESIZE 4
typedef struct LabelList {
    char nameOfLabel[MAX_LABEL_LENGTH];
    int lineNumber;
    struct LabelList* next;
} LabelList;

 typedef struct Data {
	int dc;
	int ic;
} Data;



char am_file[MAX_LINE_LENGTH];
extern int i;
extern char dataLine[MAX_LINE_LENGTH];
extern char line[MAX_LINE_LENGTH];
extern char line[MAX_LINE_LENGTH];
extern char *colonPos;
extern char label_name[MAX_LINE_LENGTH];
extern char first_word[MAX_LINE_LENGTH];
extern char oprand[MAX_LINE_LENGTH];
extern char arg1[MAX_LINE_LENGTH];
extern char arg2[MAX_LINE_LENGTH];
void removeSubstring(char *string,  char *substring);
int isAsmOprand( char* line);
#endif /* SHARE_H */



