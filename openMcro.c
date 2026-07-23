/*Open in outputAm the mcros.*/ 
#include "preAssembler.h"
void  OpenMcro(FILE* input,FILE* outputAm, linkedMcros* mcroList){
	rewind(input);  /* Move the file pointer back to the beginning of the file*/
       	char line[MAX_LINE_LENGTH];
        	linkedMcros* currentLinkedMcros = mcroList; 
        	int insideMcro=0;
    	while (fgets(line, sizeof(line), input) != NULL) {
        		if(sscanf(line,"%s",first_word)){
            		if( strstr(first_word,COMMENT) || first_word[0] == '\0' ||first_word[0] == '\n' )
		        		continue;
			if(strstr(first_word,COLON)!=0){/*If label*/
			/*insertLabel(labelOrMcro);*/
			char *part1;
    			part1 = strtok(first_word, COLON); 
		    		removeSubstring(part1,first_word);/*Minus label*/
			}	
	    	}
		if(strstr(line,MCRO)!=NULL && strstr(line,ENDMCRO)==NULL){ /*If its mcro decleration*/
            		insideMcro = 1; /*I dont want to print  what is between mcro and endmcro.*/
            		continue;
            		}
	 	if (insideMcro) { 
            		if (strstr(line, ENDMCRO) != NULL)  
                			insideMcro = 0; 
            		continue; 
        		}     			
		sscanf(line,"%s",nameOfMcro);
		Mcros* currentMcros=FindMcroByName(currentLinkedMcros, nameOfMcro);
		if(currentMcros!=NULL){
		    PrintMcroLines(outputAm,currentMcros);
		}
		else /*its not a mcro name*/
			fputs(line, outputAm);	
		}
    }
/*Open in outputAm the mcros.*/ 

void  openMcro(FILE* input,FILE* outputAm, linkedMcros* mcroList){
	rewind(input);  /* Move the file pointer back to the beginning of the file*/
       	char line[MAX_LINE_LENGTH];
        	linkedMcros* currentLinkedMcros = mcroList; 
        	int insideMcro=0;
    	while (fgets(line, sizeof(line), input) != NULL) {
        		if(sscanf(line,"%s",first_word)){
            		if( strstr(first_word,COMMENT) || first_word[0] == '\0' ||first_word[0] == '\n' )
		        		continue;
			if(strstr(first_word,COLON)!=0){/*If label*/
			/*insertLabel(labelOrMcro);*/
			char *part1;
    			part1 = strtok(first_word, COLON); 
		    		removeSubstring(part1,first_word);/*Minus label*/
			}	
	    	}
		if(strstr(line,MCRO)!=NULL && strstr(line,ENDMCRO)==NULL){ /*If its mcro decleration*/
            		insideMcro = 1; /*I dont want to print  what is between mcro and endmcro.*/
            		continue;
            		}
	 	if (insideMcro) { 
            		if (strstr(line, ENDMCRO) != NULL)  
                			insideMcro = 0; 
            		continue; 
        		}     			
		sscanf(line,"%s",nameOfMcro);
		Mcros* currentMcros=FindMcroByName(currentLinkedMcros, nameOfMcro);
		if(currentMcros!=NULL){
		    PrintMcroLines(outputAm,currentMcros);
		}
		else /*its not a mcro name*/
			fputs(line, outputAm);	
		}
}
