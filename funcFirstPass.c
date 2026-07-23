#include "firstPass.h"
void AddNode(LabelList** head, const char* nameOfLabel, int lineNumber) {

	LabelList* newNode = (LabelList*)malloc(sizeof(LabelList));     
	if (newNode == NULL){
		printf("%s", "Memory allocation failed-newNode\n");
		return;  
	}
	strncpy(newNode->nameOfLabel, nameOfLabel, MAX_LABEL_LENGTH - 1);
	newNode->nameOfLabel[MAX_LABEL_LENGTH - 1] = '\0';
	newNode->lineNumber = lineNumber;
	newNode->next = NULL;  
	if (*head == NULL) 
		*head = newNode;
	else {
		LabelList* current = *head;
		while (current->next != NULL) 
	  		current = current->next;
		current->next = newNode;
	}
}

int CountNumbersInLine(const char *line) {
	char copyLine[strlen(line) + 1]; 
	strcpy(copyLine, line);
	int count = 0;
	char *token = strtok(copyLine, ","); 
	while (token != NULL) {
		count++; 
		token = strtok(NULL, ","); 
	}
	return count;
} 
int NumbersOfLines(char* line,Data* dcIc) { 
	char oprand[MAX_LINE_LENGTH];
	char arg1[MAX_LINE_LENGTH];
	char arg2[MAX_LINE_LENGTH];
	sscanf(line,"%s", oprand);
	if (strcmp(oprand, "rts") == 0 || strcmp(oprand, "stop") == 0){ 
		dcIc->ic=dcIc->ic+1;
		return 1;
		}
 	else if (strcmp(oprand, "not") == 0 || strcmp(oprand, "clr") == 0 ||
		strcmp(oprand, "inc") == 0 || strcmp(oprand, "dec") == 0 ||
		strcmp(oprand, "jmp") == 0 || strcmp(oprand, "bne") == 0 ||
		strcmp(oprand, "red") == 0 || strcmp(oprand, "prn") == 0 ||
		strcmp(oprand, "jsr") == 0) {
			dcIc->ic=dcIc->ic+2;
			return 2;
			}
	 else if (strcmp(oprand, "lea") == 0 || strcmp(oprand, "sub") == 0 ||
	strcmp(oprand, "add") == 0 || strcmp(oprand, "cmp") == 0 ||
	strcmp(oprand, "mov") == 0) {	
		sscanf(line, "%s%s%s\n",oprand ,arg1,arg2);
		if(strchr(arg1, AT)!=0 && strchr(arg2, AT)!=0){
			dcIc->ic=dcIc->ic+2;
			return 2;
			}
		dcIc->ic=dcIc->ic+3;
		return 3;
	} 
	else if (strcmp(oprand, ".data") == 0){	
		sscanf(line, "%s%s", oprand,arg1);
		int sum=CountNumbersInLine(arg1);
		 dcIc->dc=dcIc->dc+sum;
		return sum; 					
	}
	else if (strcmp(oprand, ".string") == 0){	
		char* token;		
		sscanf(line,"%s%s",oprand,arg1);	
		 token = strtok(arg1, "\"");	
		 dcIc->dc=dcIc->dc+strlen(token)+1;
		return strlen(token)+1;/*Size of string+NULL*/				 
	 }	  
	return 0;
 }  
 int NumberOfLines(char* line) { 
	char oprand[MAX_LINE_LENGTH];
	char arg1[MAX_LINE_LENGTH];
	char arg2[MAX_LINE_LENGTH];
	sscanf(line,"%s", oprand);
	if (strcmp(oprand, "rts") == 0 || strcmp(oprand, "stop") == 0)
		return 1;
	else if (strcmp(oprand, "not") == 0 || strcmp(oprand, "clr") == 0 ||
		strcmp(oprand, "inc") == 0 || strcmp(oprand, "dec") == 0 ||
		strcmp(oprand, "jmp") == 0 || strcmp(oprand, "bne") == 0 ||
		strcmp(oprand, "red") == 0 || strcmp(oprand, "prn") == 0 ||
		strcmp(oprand, "jsr") == 0) 
			return 2;
	 else if (strcmp(oprand, "lea") == 0 || strcmp(oprand, "sub") == 0 ||
	strcmp(oprand, "add") == 0 || strcmp(oprand, "cmp") == 0 ||
	strcmp(oprand, "mov") == 0) {	
		sscanf(line, "%s%s%s\n",oprand ,arg1,arg2);
		if(strchr(arg1, AT)!=0 && strchr(arg2, AT)!=0){
			return 2;
			}
		return 3;
	} 
	else if (strcmp(oprand, ".data") == 0){	
		sscanf(line, "%s%s", oprand,arg1);
		int sum=CountNumbersInLine(arg1);
		return sum; 					
	}
	else if (strcmp(oprand, ".string") == 0){	
		char* token;		
		sscanf(line,"%s%s",oprand,arg1);	
		 token = strtok(arg1, "\"");	
		 return strlen(token)+1;/*Size of string+NULL*/				 
	 }	  
	return 0;
 }  
void AddExternLabel(linekdExtern** head, const char* label_name) {
	linekdExtern* newNode = (linekdExtern*)malloc(sizeof(linekdExtern));
	if (newNode == NULL) {
	perror("Error allocating memory");
        		return;
    }
	strncpy(newNode->externLabel, label_name, MAX_LABEL_LENGTH - 1);
	newNode->externLabel[MAX_LABEL_LENGTH - 1] = '\0';  
	newNode->next = NULL;
	if (*head == NULL) 
		*head = newNode;
	else {
		linekdExtern* current = *head;
		while (current->next != NULL) 
		current = current->next;
		current->next = newNode;
	}
}
/*Function to print all extern labels name and location where using the label as oprand*/
/*Go over outputAm file and check if using the label as oprand in that line  then take the name and search in extern label list and print the location*/
LabelList* LabelsExtern(FILE* outputAm,FILE* outputExt) {
	rewind(outputAm);
    	linekdExtern* headExternLabel=ExternList(outputAm);
    	int lineCnt=MEMORY;
    	LabelList* headExternLinelList=NULL;
    	rewind(outputAm); 
    	while (fgets(line, MAX_LABEL_LENGTH, outputAm)) {
    	 	sscanf(line, "%s", first_word);/*Potntial labelName*/
 	 	if(first_word!=NULL){
			char *colonPos = strstr(line, COLON);
	    	if (colonPos != NULL)  /* If label-there is : */	    		        	    				memmove(line, colonPos + 1, strlen(colonPos + 1) + 1);/*Take line to left*/ 
 		int scannedItems=sscanf(line, "%s%s%s", first_word,arg1,arg2);
		if( scannedItems >= 2){
			char *commaPtr;  
			while ((commaPtr = strstr(arg1, COMMA)) != NULL) /*Remove ,*/
				memmove(commaPtr, commaPtr + 1, strlen(commaPtr));
			while ((commaPtr = strstr(arg2, COMMA)) != NULL) /*Remove ,*/
				memmove(commaPtr, commaPtr + 1, strlen(commaPtr));
			if(strcmp(first_word,EXTERN)!=0){/*If first word is extern*/
				if(FindExternLabel(headExternLabel,arg1)!=NULL )/*If arg1 in the list of extern names and first word is extern*/
	   	 			AddExternLineLabel(&headExternLinelList, arg1, lineCnt+1);/*+1 becaues is in arguemnt 1*/   	
				if(scannedItems == 3){
	 	   			if(FindExternLabel(headExternLabel,arg2) )
		   	 			AddExternLineLabel(&headExternLinelList, arg2, lineCnt+2); 
		   	 	strcpy(arg2, " ");
		   	 	}
		  	}
		}
		}
        		lineCnt=lineCnt+NumberOfLines(line);                      
	}
	return headExternLinelList;	
}

void PrintList(LabelList* head,FILE* file) {

	LabelList* current = head;
	while (current != NULL) {
	fprintf(file, "  %s   %d\n ", current->nameOfLabel, current->lineNumber);
        	current = current->next;
    	}
}
/*Function to process the file and find the location of labels */
LabelList* LabelIndex(FILE* outputAm,Data* dcIc) {	
	rewind(outputAm);  /* Move the file pointer back to the beginning of the file*/
 	char* nameLabel;
 	int labelFlag=0;	
 	int lineCnt=MEMORY;
	LabelList* headList=NULL;		
	while (fgets(line, sizeof(line), outputAm) != NULL) {
		sscanf(line, "%s", first_word);/*Potntial labelName*/		
	 	colonPos = strstr(line, COLON);
	    	if (colonPos != NULL) { /* If label */
        			labelFlag = 1;
		        	nameLabel = strtok(first_word, COLON);
		        	memmove(line, colonPos + 1, strlen(colonPos + 1) + 1);/*Take the line left*/
	   	 }	
	   	if(labelFlag){
			labelFlag=0;
			AddNode(&headList, nameLabel, lineCnt);
			labelFlag=0;
		}
		lineCnt=lineCnt+NumbersOfLines(line,dcIc);
	}
	return headList;
}
/*Function that move down .data and .string line
Print all line are not include .data and .string
Then print all line are  include .data and .string */
void MoveDown(FILE* outputAm) {
	rewind(outputAm);
	FILE* tempFile = tmpfile();
    	if (tempFile == NULL) {
        		perror("Error creating temporary file");
        		return ;
    	}/* Print all lines that are not .data and .string */
     	while (fgets(line, MAX_LINE_LENGTH, outputAm)) {
		if (strstr(line , ".data") == NULL && strstr(line , ".string") == NULL)
			fputs(line, tempFile);		
	}
	rewind(outputAm);
	/* Print all lines that are .data and .string */
	while (fgets(line, MAX_LINE_LENGTH, outputAm)) {
		if (strstr(line, ".data") != NULL || strstr(line, ".string") != NULL)	
    			fputs(line, tempFile);
    	}
    	rewind(tempFile);
    	/* Copy back the temp file to outputAm */
    	outputAm = freopen(am_file, "w+", outputAm);
    	while (fgets(line, MAX_LINE_LENGTH, tempFile)) 
			fputs(line, outputAm);
    	rewind(outputAm);
}
/*Function to print all entry labels name and location*/
/*Go over output_am file and check if its entry then take the name and search in label list and print the location*/
LabelList* EntryNodes(FILE* output_am,LabelList* labels) {
	rewind(output_am);
	char entry[MAX_LABEL_LENGTH];
	LabelList* entry_list=NULL; /*Will contain entry names and location in table*/
	LabelList* current;
    	while (fgets(line, MAX_LABEL_LENGTH, output_am)) {
		sscanf(line, "%s%s", entry,label_name);
		if (strcmp(entry, ".entry") == 0){/*If entry line*/ 
			current = labels;/*Contain all labels data and location*/
			while (current != NULL) {
				if (strcmp(current->nameOfLabel, label_name) == 0) 
					AddNode(&entry_list, current->nameOfLabel, current->lineNumber);
				current = current->next;
			}
		}
    	}   
	return entry_list;
}
void PrintEntry(FILE* outputEnt,LabelList* entryNodes){/*Print the labels to file*/
	LabelList* current = entryNodes;
	while (current != NULL) {
      		fprintf(outputEnt," %s   %d\n", current->nameOfLabel, current->lineNumber);
                    current = current->next;
	}
 }
linekdExtern* ExternList(FILE* outputAm) {
	rewind(outputAm);
    	char line[MAX_LABEL_LENGTH];
    	char isExtern[MAX_LABEL_LENGTH];
    	char label_name[MAX_LABEL_LENGTH];
    	linekdExtern* headExternLabel=NULL;   
    	while (fgets(line, MAX_LABEL_LENGTH, outputAm)) {
		if (strstr(line, ".extern") != NULL) {            
			sscanf(line, "%s%s", isExtern,label_name);
  		 	AddExternLabel( &headExternLabel, label_name);
            	}	                       
        }
        return headExternLabel;
    }
linekdExtern* FindExternLabel(linekdExtern* head, const char* label_name) {
	linekdExtern* current = head;
	while (current != NULL) {
		if (strcmp(current->externLabel, label_name) == 0) 
	  		return current;  
	current = current->next;
	}
	return NULL;  
}
void AddExternLineLabel(LabelList** head, const char* nameOfLabel, int lineNumber) {
	LabelList* newNode = (LabelList*)malloc(sizeof(LabelList));
    	if (newNode == NULL) {
        		perror("Error allocating memory");
	return;
    	}
	strncpy(newNode->nameOfLabel, nameOfLabel, MAX_LABEL_LENGTH - 1);
	newNode->nameOfLabel[MAX_LABEL_LENGTH - 1] = '\0';  
	newNode->lineNumber = lineNumber;
	newNode->next = NULL;
	if (*head == NULL) 
      		*head = newNode;
    	else {
        		LabelList* current = *head;
        		while (current->next != NULL) 
            		current = current->next;
	 	current->next = newNode;
    	}
}

int FindLabel(LabelList* head, const char* nameOfLabel) {
	LabelList* current = head;
	while (current != NULL) {
		if (strcmp(current->nameOfLabel, nameOfLabel) == 0) 
	  		return 1;  
	current = current->next;
	}
	return 0;  
}
LabelList* FindInfoLabel(LabelList* head, const char* nameOfLabel) {
	LabelList* current = head;
	LabelList* temp = head;
	while (current != NULL) {
		if (strcmp(current->nameOfLabel, nameOfLabel) == 0) {
			strcpy(temp->nameOfLabel, nameOfLabel);
			temp->lineNumber= current->lineNumber;
	  		return temp;  
		}
	current = current->next;
	}
	return NULL;  
}
void FreeLabelList(LabelList* head) {
	LabelList* current = head;
	while (current != NULL) {
		LabelList* temp = current;
		current = current->next;
		free(temp);
	}
}
void FreeLinkedExtern(linekdExtern* head) {
	linekdExtern* current = head;
	while (current != NULL) {
		linekdExtern* temp = current;
		current = current->next;
		free(temp);
	}
}

