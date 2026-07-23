/*Function that get the source file and return NodeMcro that has all the lines of mcro and their name.*/
#include "preAssembler.h"
char nameOfMcro[MAX_LINE_LENGTH];
char label[MAX_LINE_LENGTH];

linkedMcros* LinkedMcro(FILE *input){
	linkedMcros* head_mcros = NULL;
 	linkedMcros** current_linked_mcro = &head_mcros;
  	Mcros*currentMcro = NULL;  
	int mcroFlag=0;
	while( fgets( dataLine , sizeof( dataLine ), input ) != NULL){
		strcpy(line,dataLine);
	 	if(sscanf(line,"%s",first_word)){
			if( strchr(first_word,';') || first_word[0] == '\0' || first_word[0] == '\n' )
		    		continue;
			if(strchr(first_word,':')!=0){/*If label*/
				char *part1;					
			    	part1 = strtok(first_word, COLON); 				    	
				removeSubstring(part1,first_word);/*Minus label*/
				}
		}
		if(strstr(line,MCRO)!=NULL && strstr(line,ENDMCRO)==NULL) {/*If its mcro decleration*/
			mcroFlag=1;	
			removeSubstring(line,MCRO);
			if(sscanf(line,"%s",nameOfMcro)!=0){
				if(!isAsmOprand(nameOfMcro)){/*If its not one of the words of assembly*/ 
					currentMcro = (Mcros*)malloc(sizeof(Mcros));
					if (currentMcro == NULL){
					    printf("%s\n","No memory for newMcrodNode");
					    return NULL;
					}
					currentMcro->mcroName = (char*)malloc(strlen(nameOfMcro) + 1);
					if (currentMcro->mcroName == NULL) {
				    		free(currentMcro);
					    	return NULL;
					}
				    	strcpy(currentMcro->mcroName,nameOfMcro);
				         	currentMcro->allLines = NULL;
					currentMcro->next = NULL;
				        	continue;
				}
			        	else{
		    			printf("%s","Name of mcro invaild");
					break;
				}
			}		
    		}	
		if(strstr(line,ENDMCRO)!=NULL){/*endmcro*/
			mcroFlag=0;	
			*current_linked_mcro = (linkedMcros*)malloc(sizeof(linkedMcros));
			(*current_linked_mcro)->mcroNode = currentMcro;
			(*current_linked_mcro)->nextNode = NULL;
			current_linked_mcro = &(*current_linked_mcro)->nextNode;
			currentMcro = NULL; /* Reset the currentMcro pointer*/
			    continue;
		}							
		if(mcroFlag)         
  			AddLineToMcro(currentMcro, line);              				  		}				  
   return head_mcros;
}			 	             
