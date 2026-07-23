#include "share.h"
void removeSubstring(char *string,  char *substring) {
    char *found = strstr(string, substring);

    if (found != NULL) {
        int subLen = strlen(substring);
        memmove(found, found + subLen, strlen(found + subLen) + 1);
    }
    else
    	return;
}
int isAsmOprand( char* line) {/*If its one of assembler word return true.*/
	char oprand[81];	 	
	sscanf(line,"%s", oprand);
	if (strcmp(oprand, "rts") == 0 || strcmp(oprand, "stop") == 0
		|| strcmp(oprand, "not") == 0 || strcmp(oprand, "clr") == 0 ||
		strcmp(oprand, "inc") == 0 || strcmp(oprand, "dec") == 0 ||
		strcmp(oprand, "jmp") == 0 || strcmp(oprand, "bne") == 0 ||
		strcmp(oprand, "red") == 0 || strcmp(oprand, "prn") == 0 ||
		strcmp(oprand, "jsr") == 0 ||strcmp(oprand, "lea") == 0 || strcmp(oprand, "sub") == 0 ||
	strcmp(oprand, "add") == 0 || strcmp(oprand, "cmp") == 0 ||
	strcmp(oprand, "mov") == 0 || strcmp(oprand, ".data") == 0 || strcmp(oprand, ".entry") == 0 || strcmp(oprand, ".extern") == 0|| strcmp(oprand, ".string") == 0)
        return 1;
	return 0;
}
