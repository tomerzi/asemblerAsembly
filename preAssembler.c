/*Find all mcros and open them in outputAm file*/
#include "preAssembler.h"
void PreAssembler(FILE* input,FILE* outputAm){/*input-the assembly file, outputAm-file to print after opened mcros*/
    	linkedMcros* list= LinkedMcro(input);   /*Find the mcros and lines bewteen mcro and end mcro*/
	OpenMcro(input,outputAm, list);/*Open in outputAm the mcros.*/ 
 	FreeLinkedMcros(list);    
}

