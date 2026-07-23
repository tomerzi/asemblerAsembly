#include "share.h"
#include "erros.h"
int line_idx;
char err_buf[MAX_LINE_LENGTH];
labels* listOfLabels = NULL;
labels* listOfExtern = NULL;
labels* listOfEntry  = NULL;
int flag = 0;
int vars = 0;
char new_line[MAX_LINE_LENGTH];
int error_printed;
int AddLabel(labels** head, const char* name) { /* Check if a label with the same name already exists*/
	
	labels* current = *head;
	while (current != NULL) {
		if (strcmp(current->nameOfLabel, name) == 0) {
			printf("Error: A label with the name '%s' already exists.\n", name);
			return -1; 
		}
		current = current->next;
	}
	labels* newLabel = (labels*)malloc(sizeof(labels));
	if (newLabel == NULL) {
		printf("Error: Memory allocation failed.\n");
		return -1;
	}
	strncpy(newLabel->nameOfLabel, name, MAX_LABEL_LENGTH);
	newLabel->next = NULL;
	if (*head == NULL) {
		*head = newLabel;
		return 0;
	}
	current = *head;
	while (current->next != NULL) 
		current = current->next;	
	current->next = newLabel;
	
	return 0;
}
int VaildStringData(FILE* output_am){
	line_idx=0;
	error_printed=0;
	rewind(output_am);
	strcpy(new_line,line);
	while (fgets(line, sizeof(line), output_am)) {	
		char *colonPos = strstr(line, COLON);
	    	if (colonPos != NULL)  /* If label-there is : */	    		        	    	
			        	memmove(line, colonPos + 1, strlen(colonPos + 1) + 1);/*Take line to left*/   	 	   	int count =sscanf(line, "%s%s%s",  oprand, arg1, arg2);
	       	if (strcmp(oprand, ".string") == 0 ){
	       		if( count==2){
		       		if (strstr(arg1, "\"") == NULL) {
			  		printf("Error: Second word is not valid.\n");
				   	printf("in line :%s %d\n",new_line, line_idx);
				   	error_printed++;
				  	  flag= -1;
			  	}
		  	}
		  	else if (count!=2){
        				printf("Error: invaild number of arguemnts.\n");
	   			printf("in line :%s %d\n",line, line_idx);
	   			error_printed++;
  	  			flag= -1;
	  	  	}
	        	}
	        	if (strcmp(oprand, ".data") == 0 ){  /* After data need to be number,number,number..*/
			if (count!=2){
				printf("Error: invaild number of arguemnts.\n");
	   			printf("in line :%s %d\n",line, line_idx);
	   			error_printed++;
  	  			flag= -1;
  			}
  			if (count==2){/*Check if in format of number,number,number..*/
				int number;
		        	 	const char* ptr = arg1;
				while (*ptr != '\0' && *ptr != '\n') {
					while (isspace(*ptr))
					 ptr++;/* Skip any whitespace */
			 		if (sscanf(ptr, "%d", &number) != 1) {
		  				printf("Error: Second word is not valid.\n");
			   			printf("in line :%s %d\n",line, line_idx);	  /* Failed to read a number*/					error_printed++;
			   	 		flag= -1;
	        				}
	        				while (isdigit(*ptr) || *ptr == '-' || *ptr == '+')
	        					 ptr++;
					 /* If there's more to the line, expect a comma next*/
        					if (*ptr != '\0' && *ptr != '\n') {
	  					if (*ptr != ',') {
      						 	printf("Error: Second word is not valid.\n");
		   					printf("in line :%s %d\n",line, line_idx);	  /* Failed to read a number*/					error_printed++;
		   	 				flag= -1; /* Expected a comma*/
	  					}
	  					ptr++; /* Move past the comma*/
						while (isspace(*ptr))
							 ptr++;/* Skip any whitespace after the comma*/
        					}
    				}
			}
		
		}
	}return error_printed;
}
		
int CheckForCommonLabels(labels* listOfExtern, labels* listOfEntry) {/*check if there is common label in extern and entry - return 1 if there is*/
	error_printed=0;
	labels* externPtr = listOfExtern;
	while (externPtr != NULL) {
		labels* entryPtr = listOfEntry;
		while (entryPtr != NULL) {
			if (strcmp(externPtr->nameOfLabel, entryPtr->nameOfLabel) == 0){ 
				printf("Error: label name '%s' are decleared extern and entry.\n",externPtr->nameOfLabel);
			error_printed++;	
			}
			entryPtr = entryPtr->next;
		}
		externPtr = externPtr->next;
	}
	return error_printed; 
}
void PrintLabels(labels* head) {
	labels* current = head;
	while (current != NULL) {
		printf("Label: %s\n", current->nameOfLabel);
		current = current->next;
	}
}
int CheckLabelsForLettersAndDigits(labels* head) {
	error_printed=0;
	labels* current = head;
	while (current != NULL) {
		int all_letter_digit = 1;
		for ( i = 0; i < strlen(current->nameOfLabel); i++) {
			if (!islower(current->nameOfLabel[i]) &&!isupper(current->nameOfLabel[i]) && !isdigit(current->nameOfLabel[i])) 
				all_letter_digit = 0;
			if (!all_letter_digit) {
				printf("Error: label name '%s' must contain only uppercase letters or digits.\n", current->nameOfLabel);
				error_printed++;
			}
		}
		
		
		current = current->next;
	}
	return error_printed;
}
/*List of all labels- checkes that there is no 2 same labels andcheck that there is no label before .extern or .entry-if there is error is_vaild is turn into 1*/
labels* Labels(FILE* output_am,int* is_vaild) {
	
	rewind(output_am);
	char isLabel[MAX_LABEL_LENGTH];
	char is_extern_entry[MAX_LABEL_LENGTH];
	char *labelNoColon;
	int all_letter_digit ;
	labels* listOfLabels=NULL;
 	line_idx=0;
 	error_printed=0;
	while(fgets(line,MAX_LINE_LENGTH, output_am)!=NULL) {
		sscanf(line, "%s%s", isLabel,is_extern_entry);
		if (strstr(isLabel,COLON)){/* Check if first word ends with ':'*/
			if(strcmp(is_extern_entry,".extern")!=0 && strcmp(is_extern_entry,".entry")!=0){/* check if its not .extern or .enrty line*/
				labelNoColon = strtok(isLabel, COLON);/* Remove the colon from word1 */
	    			while (isspace((unsigned char)*labelNoColon)) 
	        				labelNoColon++;
	        				
				if(AddLabel(&listOfLabels,labelNoColon)!=0){/* Add and Check if a label with the same name already exists*/		
					printf("Error: Two same labels.\n");
					printf("in line :%s\n", line);
					*is_vaild=1;
				}
			}
			else{
			  	printf("Error: label name can not be before .extern or .entry.\n");
				printf("in line :%s\n", line);
				*is_vaild=1;
				continue;
			}
			
		}
				
	}		
	return listOfLabels;
}
labels* Extern(FILE* output_am,int* is_vaild){/*Function that give all extern labels*/
	
	rewind(output_am);
	char isLabel[MAX_LABEL_LENGTH];
	char labelName[MAX_LABEL_LENGTH];
	labels* listOfExtern=NULL;
	while (fgets(line,MAX_LINE_LENGTH, output_am)!=NULL) {
		sscanf(line, "%s%s", isLabel,labelName);
		if (strcmp(isLabel,".extern")==0){/* Check if first word is .extern*/
			if(AddLabel(&listOfExtern,labelName)!=0){/* Add and check if a label with the same name already exists*/			printf("Error: Two same labels.\n");
				printf("in line :%s\n", line);
				*is_vaild=1;
				}
        		}
        		  
	}
	return listOfExtern;
}
labels* Entry(FILE* output_am,int* is_vaild){/*Function that give all entry labels*/
	rewind(output_am);
	char isLabel[MAX_LABEL_LENGTH];
	char labelName[MAX_LABEL_LENGTH];	
	while (fgets(line,MAX_LINE_LENGTH, output_am)!=NULL) {
		sscanf(line, "%s%s", isLabel,labelName);
		if (strcmp(isLabel,".entry")==0){/* Check if first word is .extern*/
			if(AddLabel(&listOfEntry,labelName)!=0){/* Add and check if a label with the same name already exists*/
				printf("Error: Two same labels.\n");
				printf("in line :%s\n", line);
				*is_vaild=1;
			}
        		}
	}
	return listOfEntry;
}
int CountTwoWords(FILE*  output_am,const char* validWordsNeedTwo[],int size){
	error_printed=0;
	rewind(output_am);
	flag=0;
	line_idx=0;
	while (fgets(line,MAX_LINE_LENGTH, output_am)!=NULL) {
	strcpy(new_line,line);
		colonPos = strstr(line, COLON);
	 	if (colonPos != NULL) /* If label-there is : */	
	 		memmove(new_line, colonPos + 1, strlen(colonPos + 1) + 1);/*Take line to left*/
		vars=sscanf(new_line, "%s%s%s%s",oprand,arg1,arg2,err_buf);
		for ( i = 0; i <size; i++) {/*If oprand is need 2 arguemnts */
		if (strcmp(oprand, validWordsNeedTwo[i]) == 0) 
				{
				flag=1;}
       		 }
       		 if(flag && vars!=3){/*Must to be 2 arguemnts*/
			
			printf("Error: must to be 2 aruemnts for %s\n",oprand);
			printf("in line : %d %s\n",line_idx, line);
			error_printed++;
			continue;	
		}
       		 if(flag) flag=0;
       		
		
			
	line_idx++;
	}
	return error_printed;
}
int CountOneWord(FILE* output_am,const char* vaildWordsNeedOne[],int size){
	error_printed=0;
	flag=0;
	rewind(output_am);
	line_idx=0;
	while (fgets(line,MAX_LINE_LENGTH, output_am)!=NULL) {
		strcpy(new_line,line);
		colonPos = strstr(line, COLON);
	 	if (colonPos != NULL){ /* If label-there is : */				
			memmove(new_line, colonPos + 1, strlen(colonPos + 1) + 1);/*Take line to left*/
		}
		
		vars=sscanf(new_line,"%s%s%s",oprand,arg1,arg2);
		
		for ( i = 0; i <size; i++) {/*If oprand is need 2 arguemnts */
			 if (strcmp(oprand, vaildWordsNeedOne[i]) == 0) 
				flag=1;
		}
	 	if(flag && vars !=2){/*Must to be 1 argemnts*/
			printf("Error: must to be 1 aruemnts for %s\n",oprand);
			printf("in line : %d %s\n",line_idx, line);
			error_printed++;
			continue;	
		}
		if(flag)	flag=0;	
		line_idx++;
	}
	return error_printed;		
}
int CountZeroWord(FILE* output_am,const char* vaildWordsNeedZero[],int size){
	error_printed=0;
	rewind(output_am);
	line_idx=0;
	flag=0;
	while (fgets(line,MAX_LINE_LENGTH, output_am)!=NULL) {
	strcpy(new_line,line);
		colonPos = strstr(line, COLON);
	 	if (colonPos != NULL){ /* If label-there is : */		
			memmove(new_line, colonPos + 1, strlen(colonPos + 1) + 1);/*Take line to left*/
		}
		int vars=sscanf(new_line, "%s%s", oprand,err_buf);
		 for ( i = 0; i <size; i++) {/*If oprand is need 0 arguemnts */
	       		 if (strcmp(oprand, vaildWordsNeedZero[i]) == 0)
	       		 	flag=1;
	       	}	 	
		if(flag && vars !=1){/*Must to be 1 argemnts*/
			
			printf("Error: must to be 0 aruemnts for %s\n",oprand);
			printf("in line : %d %s\n",line_idx, line);
			error_printed++;
			continue;	
		}
		if(flag) flag=0;		
	line_idx++;
	}
return error_printed;		
}
   		
int IsValidArgument(const char arg[MAX_LINE_LENGTH], const char* registers[],int registersSize, labels* listOfLabels) {
    /* Check if the argument is one of the registers*/
	for ( i = 0; i < registersSize; i++) {
    	    	if (strcmp(arg, registers[i]) == 0){ 
    		        	return 1; }
    	}
    /* Check if the argument is one of the labels in listOfLabels*/
	labels* current = listOfLabels;
    	while (current != NULL) {
        		if (strcmp(arg, current->nameOfLabel) == 0) {
            		return 1;}
  		 current = current->next; 
        }
    /* Check if the argument is a number */
	char* end;
	strtol(arg, &end, 10); /* Convert to long int, base 10*/
	if (*end == '\0') { 
		return 1;} 
	return 0;
}
/*Checkes if arguemnt is not a number or register or label*/
int VaildArguemnts(FILE* output_am, const char* registers[],int registersSize, labels* listOfLabels,const char* vaildWordsNeedTwo[],int sizeNeedTwo, const char* vaildWordsNeedOne[],int sizeNeedOne) {
	rewind(output_am);
	line_idx=0; 
	
	int vaildOprand=0;
	while(fgets(line,MAX_LINE_LENGTH, output_am)!=NULL) {
	flag=0;
	vaildOprand=0;
	strcpy(new_line,line);
		colonPos = strstr(line, COLON);
	 	if (colonPos != NULL) /* If label-there is : */			
			memmove(new_line, colonPos + 1, strlen(colonPos + 1) + 1);/*Take line to left*/
		sscanf(new_line, "%s%s%s", oprand,arg1,arg2);
		for ( i = 0; i <sizeNeedTwo; i++) {
			if (strcmp(oprand, vaildWordsNeedTwo[i]) == 0 &&   arg1!=NULL) 
				flag=1;
		}
		for ( i = 0; i <sizeNeedOne; i++) {
			 if(flag ||(  strcmp(oprand,".extern")!=0 && strcmp(oprand,".entry")!=0 && strcmp(oprand,".data")!=0 && strcmp(oprand,".string")!=0 && strcmp(oprand, vaildWordsNeedOne[i] )== 0  &&   (arg1!=NULL)))
			 vaildOprand=1;
		 }
		if(vaildOprand){
			char *commaPos = strstr(arg1, COMMA); /* Find the position of the comma*/
			if (commaPos != NULL) 
				*commaPos = '\0'; /* Replace the comma with a null terminator*/
			if(!IsValidArgument(arg1,registers,registersSize,listOfLabels)){
				printf("Error: arguemnt 1 is not vaild\n");
				printf("in line : %d %s\n",line_idx, line);
				error_printed++;
				continue;	
			}
		}
		
		for ( i = 0; i <sizeNeedOne; i++) {
			if ((strcmp(oprand, vaildWordsNeedTwo[i]) == 0)){
				if(arg2!=NULL){
				 char *commaPos = strstr(arg2, COMMA);
				if (commaPos != NULL){	
     					char *new_arg2 = commaPos + 1;/* Move the pointer one position after the comma*/strcpy(arg2,new_arg2);
     					}
					if(!IsValidArgument(arg2,registers,registersSize,listOfLabels)){
						printf("Error: arguemnt 2 is not vaild\n");
						printf("in line : %d %s\n",line_idx, line);
						error_printed++;	
						continue;
					}
				}
			}
		}		
		line_idx++;
	}
	return error_printed;	
}

labels* MergeLists(labels* list1, labels* list2) {
	if (list1 == NULL) 
		return list2;
	labels* temp = list1;
	while (temp->next != NULL) 
		temp = temp->next;
	temp->next = list2;
	return list1;
}
int IsOprandInArray(const char* oprand, const char* validWords[], int size) {
	for ( i = 0; i < size; i++) {
		if (strcmp(oprand, validWords[i]) == 0) 
			return 1;       
	}
	return 0;
}
int CheckOprand(FILE*  output_am, const char* validWordsNeedTwo[],int sizeTWo,const char* vaildWordsNeedOne[],int sizeNeedOne, const char* vaildWordsNeedZero[],int sizeNeedZero){
	error_printed=0;
	rewind(output_am);
	line_idx=0;
	while (fgets(line,MAX_LINE_LENGTH, output_am)!=NULL) {
		strcpy(new_line,line);
		colonPos = strstr(line, COLON);
	 	if (colonPos != NULL) /* If label-there is : */			
			memmove(new_line, colonPos + 1, strlen(colonPos + 1) + 1);/*Take line to left*/		
		sscanf(new_line,"%s",oprand);
		if (!IsOprandInArray(oprand,validWordsNeedTwo, sizeTWo) && !IsOprandInArray(oprand,vaildWordsNeedOne, sizeNeedOne) && !IsOprandInArray(oprand, vaildWordsNeedZero, sizeNeedZero)){
			printf("Error: invaild name of oprand\n");
			printf("in line :%s %d\n", line,line_idx);
			error_printed++;
			 
		}
	line_idx++;
	}
	return error_printed;	
}
