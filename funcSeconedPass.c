/*Functions of seconed pass*/

#include "seconedPass.h"
/*Function that return the binary of the numbers between 0 to 15 in 4 digits format*/
void AddLine(BinaryLines** head, const char* line) {
	BinaryLines* newNode = (BinaryLines*)malloc(sizeof(BinaryLines));
	if (newNode) {
		strncpy(newNode->line, line, MAX_LINE_LENGTH);
		newNode->next = NULL;  
		if (*head == NULL) 
			*head = newNode;  
		 else {
			BinaryLines* current = *head;
			while (current->next != NULL) 
				current = current->next;  
		current->next = newNode;  
		}
	}
}
/*Prints the binary lines.*/
void PrintLines(BinaryLines* head) {
	BinaryLines* current = head;
	while (current != NULL) {
		printf("%s\n", current->line);
		current = current->next;
    	}
}
/* Frees the memory allocated for the binary lines.*/
void FreeLines(BinaryLines* head) {
	BinaryLines* current = head;
	while (current != NULL) {
		BinaryLines* temp = current;
		current = current->next;
		free(temp);
	}
}
/*Converts a number to a 4-bit binary string.*/
char* ToBinary(int number) {

	char* binary = (char*)malloc(5 * sizeof(char));
	if (binary == NULL) 
		return NULL;
	for ( i = OPECODESIZE-1; i >= 0; i--) 
		binary[OPECODESIZE-1 - i] = ((number >> i) & 1) + '0';
	binary[OPECODESIZE] = '\0';
	return binary;
}
/*Function that return the opecode of first word*/

char* Opecode(char* oprand){
	for ( i = 0; i < OPRANDS+1; i++) {
		if (strcmp(oprand, opecodes[i]) == 0) 
            		return ToBinary(i);
        	}
    	return NULL; 
}

/*Ascii code of chars in string*/
void GetStringASCII(char c, char *result) {/*Function that return string ascii words*/
	int asciiValue = (int)c;
	for ( i = BINARYWORD-1; i >= 0; i--) {
		result[i] = (asciiValue & 1) ? '1' : '0';
		asciiValue >>= 1;
	}
	result[BINARYWORD] = '\0'; 
}
/* Converts a string to its ASCII binary representation.*/
 BinaryLines* StringAscii(char* first_word){
	BinaryLines* string_binary=NULL;
	char ascii_code[BINARYWORD+1];
	char *start = strchr(first_word, '\"');
	char *end = strrchr(first_word, '\"');
	if (start && end && start != end) {
		start++;  
		*end = '\0'; /* Null at the closing quote*/
	}
	while (*start) {
	GetStringASCII(*start, ascii_code);
	 	AddLine(&string_binary, ascii_code);
		start++;
	}
	return string_binary;		
}
void Get12BitBinary(int number, char *result) {
	int value = number;
	if (number < 0) 
		value = (~(-number) & 0xFFF) + 1;  
	for ( i = BINARYWORD-1; i >= 0; i--) {
		result[i] = (value & 1) ? '1' : '0';
		value >>= 1;
	}
	result[BINARYWORD] = '\0';  
}
/*Converts a data argument into a linked list of binary lines*/
BinaryLines* DataAscii(const char* arg1){/*Function that return all data ascii words*/
	BinaryLines* head=NULL;
	char *numbers = malloc(strlen(arg1) + 1);
	if (numbers == NULL) {
		fprintf(stderr, "Memory allocation error\n");
		return NULL;
	}
	strcpy(numbers, arg1); 
	char *token = strtok(numbers, ",");
	while (token != NULL) {
		int number = atoi(token);
		char binary_code[BINARYWORD+1];
		Get12BitBinary(number, binary_code);
		AddLine(&head, binary_code);
		token = strtok(NULL, ",");
	}
	free(numbers);
	return head;  
}
int IsValidNumber(const char *str, int *number) {
	const char *original_str = str; 
	if (*str == '-') /*Minus*/
		str++;
	while (*str != '\0') {
		if (!isdigit(*str)) 
		  return 0; /* Return false if any character is not a digit */
		str++;
	} 
	*number = atoi(original_str); /* Convert to integer using the original pointer */
	return 1;  
}
/*Converts a number to a 12-bit binary string with additional formatting.*/
void NumberBinary(char *number_binary,int number){
	Get12BitBinary(number,number_binary);
	memmove(number_binary, number_binary + 2, 10);
	number_binary[BINARYWORD-2] = '0';
	number_binary[BINARYWORD-1] = '0';
	number_binary[BINARYWORD] = '\0';
}
/*Processes '@' character in assembly code and returns binary representation.*/
void AtBinary(char *number_binary,char *arg1,char *arg2){
	int flag_two_at=0;
	char *token = strtok(arg1, ",");
	char *numberPart1 = strchr(token, AT) + 2; /* Skip the '@' character and one more character*/
	int number1 = atoi(numberPart1);
	if (strchr(arg2, AT)) {
		char *numberPart2 = strchr(arg2, AT) + 2;
		int number2 = atoi(numberPart2);	
	    	int result1 = number1 << 7;/* Shift the first number 7 bits to the left*/	
	    	 int result2 = number2 << 2; /* Shift the second number 3 bits to the left*/
		 int finalResult = result1 | result2; /*Combine the two numbers*/
		number_binary[BINARYWORD] = '\0'; 
		for ( i = BINARYWORD-1; i >= 0; i--)  /* Fill the string with the binary representation*/
			number_binary[BINARYWORD-1 - i] = ((finalResult >> i) & 1) ? '1' : '0';	
		flag_two_at=1;
	}
	if(!flag_two_at){
		Get12BitBinary(number1, number_binary);  	 	     
		char temp_binary[BINARYWORD+1];
		strcpy(temp_binary, number_binary);  	   	    
		memmove(number_binary, temp_binary + 7, 5);	  
		number_binary[BINARYWORD-3] = '0';
		number_binary[BINARYWORD-2] = '0';
		number_binary[BINARYWORD-1] = '0';	    
		number_binary[BINARYWORD] = '\0';
		
	}
}
void LabelBinary(LabelList* label_index,char *number_binary,LabelList* foundLabel){
				
	Get12BitBinary(label_index->lineNumber,number_binary);
	memmove(number_binary, number_binary + 2, 10);
	number_binary[BINARYWORD-2] = '1';
	number_binary[BINARYWORD-1] = '0';
	number_binary[BINARYWORD] = '\0'; 
}
void Arg2Binary(char *number_binary,char *arg2){
 
	char *numberPart = strchr(arg2, AT) + 2; /* Skip the '@' character and one more character*/
	int number = atoi(numberPart);
	Get12BitBinary(number, number_binary);  	 	     
	char temp_binary[BINARYWORD+1];
	strcpy(temp_binary, number_binary);  	   	    
	memmove(number_binary, temp_binary + 7, 5);	  
	number_binary[BINARYWORD-3] = '0';
	number_binary[BINARYWORD-2] = '0';
	number_binary[BINARYWORD-1] = '0';	    
	number_binary[BINARYWORD] = '\0';
}
const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


void EncodeBaseBits(unsigned short input, char output[2]) {
    unsigned char segment1 = (input & 0xFC0) >> 6; /* Extract the 6-bit segments */
    unsigned char segment2 = input & 0x03F;
    output[0] = base64_chars[segment1]; /* Convert to Base64 characters */
    output[1] = base64_chars[segment2];
}
/*Encodes the binary lines into base64 and writes to a file.*/
void EncodeBinaryLines(BinaryLines* word_list, FILE* outputObj) {
    BinaryLines* current = word_list;
    
    while (current != NULL) {
        unsigned short input = 0;
        for ( i = 0; i < BINARYWORD; i++) {
            input <<= 1;
            input |= (current->line[i] == '1') ? 1 : 0; 
        }
        char output[2];
        EncodeBaseBits(input, output);
        
        fprintf(outputObj, "%c%c\n", output[0], output[1]);
        
        current = current->next;
    }
}
/*Function that delete .extern and enyry decleation from file*/

FILE* DeleteExternEntry(FILE* outputAm){

	rewind(outputAm);
	FILE* noEntryExtern = fopen("noEntryExtern.txt", "w+");
	if (noEntryExtern == NULL) {
		perror("Failed to open noEntryExtern file");
		return NULL;
	}
	while (fgets(line, sizeof(line), outputAm) != NULL) {
		sscanf(line, "%s", first_word);
		if (strcmp(first_word, ".extern") == 0 || strcmp(first_word, ".entry") == 0)
		continue;
		fputs(line, noEntryExtern);
	}
	return noEntryExtern;
}
/*Function that return all assembly lines in linked list*/
BinaryLines* Linestlist(FILE* noEntryExtern){
	rewind(noEntryExtern);  /* Move the file pointer back to the beginning of the file*/ 	
	BinaryLines* line_list=NULL;
	while (fgets(line, sizeof(line), noEntryExtern) != NULL) {
		sscanf(line, "%s", first_word);	
		char *colonPos = strstr(line, COLON);
		if (colonPos != NULL)  /* If label */
			memmove(line, colonPos + 1, strlen(colonPos + 1) + 1);/*Move line left -no label in line*/
		AddLine(&line_list,line);
	}	   	 
	return line_list;
}
/*Function that return  data string labels names and location in table*/

LabelList* DataStringList(FILE* outputAm){
	rewind(outputAm);
    	char* name_label;
    	int line_cnt=MEMORY;
    	LabelList* head_data_string_list=NULL;
    	while (fgets(line, MAX_LABEL_LENGTH, outputAm)) {
    		sscanf(line, "%s", first_word);/*Potntial labelName*/
		if(first_word!=NULL){	
			char *colonPos = strstr(line, COLON);
		    	if (colonPos != NULL){  /* If label-there is : */	
	    			name_label=strtok(line, ":");	
	    			char label_copy[MAX_LABEL_LENGTH]; /*Store the label name*/
            			strcpy(label_copy, name_label); 
	    			memmove(line, colonPos + 1, strlen(colonPos + 1) + 1);	/*Take line to left*/ 
				sscanf(line, "%s", first_word);
	 			if(strcmp(first_word,".data")==0 || strcmp(first_word,".string")==0)	        						AddNode(&head_data_string_list,label_copy, line_cnt);        		
        			}
        			else if(strcmp(first_word,".extern")==0){
        				sscanf(line, "%s%s", oprand,arg1);
        				AddNode(&head_data_string_list,arg1, line_cnt); 
        				}  	 	  	 				
    		}
    		line_cnt=line_cnt+NumberOfLines(line);		    	   	     
	}	
	return head_data_string_list;		
}
/*Function that return the binary of source*/
BinaryLines* SourceBinary(FILE* noEntryExtern,LabelList* data_extern_list){
	char source_binary[4];
 	BinaryLines* head_source_list=NULL;
 	rewind(noEntryExtern);
	while (fgets(line, MAX_LINE_LENGTH, noEntryExtern)) {	
		sscanf(line, "%s", first_word);/*Potntial labelName*/
		if(first_word!=NULL){	
			char *colonPos = strstr(line, COLON);
		    	if (colonPos != NULL)  /* If label-there is : */	
	    			memmove(line, colonPos + 1, strlen(colonPos + 1) + 1);	/*Take line to left*/ 
		}
		sscanf(line, "%s%s", first_word,arg1);
			if(strcmp(first_word,"mov")==0 || strcmp(first_word,"cmp")==0 || strcmp(first_word,"add")==0 ||  strcmp(first_word,"sub")==0 ||strcmp(first_word,"lea")==0){
		        		
	        			int number;
				if(IsValidNumber(arg1,&number)) 
			        		strcpy(source_binary,"001");
			        	else{
			        		sscanf(line, "%s%s", first_word,arg1);
			        		char *temp = strtok(arg1, ",");
					if (FindLabel(data_extern_list,temp))
			        			strcpy(source_binary,"011");
			        		else if(strchr(temp,AT))				        
				        		strcpy(source_binary,"101");
				 }
	        		}
			else strcpy(source_binary,"000");
        			AddLine(&head_source_list,source_binary);
	        		       }
	return head_source_list;
}            	
/*Function that return the binary code of opecode of all first word in file */
BinaryLines* OpecodeBinary(FILE* noEntryExtern){
	rewind(noEntryExtern);  /* Move the file pointer back to the beginning of the file*/ 	
 	BinaryLines* headOpecodeList=NULL;
 	while (fgets(line, sizeof(line), noEntryExtern) != NULL) {
		sscanf(line, "%s", first_word);	
		colonPos = strstr(line, COLON);
	    	if (colonPos != NULL)  /* If label */
		        	memmove(line, colonPos + 1, strlen(colonPos + 1) + 1);/*Move line left -no label in line*/
	   	sscanf(line, "%s",first_word);/*No label*/
	   	if(strcmp(first_word,".data")==0 || strcmp(first_word,".string")==0)
   	 		continue; 
		char* opecode_binary=Opecode(first_word);
	       	AddLine( &headOpecodeList,opecode_binary);
	}	
return headOpecodeList;
}
/*Function that return the binary of target*/
BinaryLines* TargetBinary(FILE* noEntryExtern,LabelList* data_string_list){
	char target_binary[TARGETSIZE];
 	char arg1[MAX_LINE_LENGTH];	 
 	int arg;
 	int flag=0;
 	BinaryLines* head_target_list=NULL;
 	rewind(noEntryExtern);
	while (fgets(line, MAX_LINE_LENGTH, noEntryExtern)) {	
		sscanf(line, "%s", first_word);/*Potntial labelName*/
		if(first_word!=NULL){	
			char *colonPos = strstr(line, COLON);
		    	if (colonPos != NULL)  /* If label-there is : */	
	    			memmove(line, colonPos + 1, strlen(colonPos + 1) + 1);	/*Take line to left*/ 
		}
		sscanf(line, "%s", first_word);
		if(strcmp(first_word,"rts")!=0 && strcmp(first_word,"stop")!=0 && strcmp(first_word,".data")!=0 && strcmp(first_word,".string")!=0 ){/*Have no target*/
			if(strcmp(first_word,"mov")==0 || strcmp(first_word,"cmp")==0 || strcmp(first_word,"add")==0 ||  strcmp(first_word,"sub")==0 ||strcmp(first_word,"lea")==0){/*Have  two arguemnt*/			
				char *firstPart = strtok(line, ",");
				char *arg2 = strtok(NULL, ",");
				char label_copy[MAX_LABEL_LENGTH]; /*Store the label name*/
				sscanf(arg2, "%s", label_copy);				
				for ( i = 0; arg2[i] != '\0'; i++) {
					if (!isdigit(label_copy[i])) 
						flag=1; /*Not number*/
				}	
				if(!flag){/* number*/
					flag=0;
					strcpy(target_binary,"001");
				}		
				else if(flag){/* Not number*/	
					if (FindLabel(data_string_list,label_copy)!=0)
	        	 				strcpy(target_binary,"011");
			        		else if(strchr(label_copy,AT))
						strcpy(target_binary,"101");
				}
			}
		        	else{/*Has only one arguemnt*/			        		
	        			int result=sscanf(line, "%s%d", first_word,&arg);	
				if(result == 2) /*If its number*/
	        				strcpy(target_binary,"001");
		        		else{
	        				sscanf(line, "%s%s", first_word,arg1);
		        			char *temp = strtok(arg1, ",");
			        	 	if (FindLabel(data_string_list,temp))
		        				strcpy(target_binary,"011");
			        		else if(strchr(temp,AT))
		        				strcpy(target_binary,"101");
        				}
			}
		}
		else {strcpy(target_binary,"000");}
		AddLine(&head_target_list,target_binary);
       }
	return head_target_list;
}	        			        			        
/*Function that return the binary of ARE*/
BinaryLines* AreBinary(FILE* noEntryExtern){
	char target_binary[3];
 	BinaryLines* head_target_list=NULL;
 	rewind(noEntryExtern);
	while (fgets(line, MAX_LINE_LENGTH, noEntryExtern)) {	
		sscanf(line, "%s", first_word);/*Potntial labelName*/
		if(first_word!=NULL){	
			char *colonPos = strstr(line, COLON);
		    	if (colonPos != NULL)  /* If label-there is : */	
	    			memmove(line, colonPos + 1, strlen(colonPos + 1) + 1);	/*Take line to left*/ 
		}
		sscanf(line, "%s", first_word);
		if(strcmp(first_word,".data")!=0 && strcmp(first_word,".string") ){		
			strcpy(target_binary,"00");
			AddLine(&head_target_list,target_binary);
		}		
	}		
	return head_target_list;
}
/*Function that add the binary words from the linked list and make one binary word of 12 bits*/
BinaryLines* CombinedBinaryLines(BinaryLines* source_binary, BinaryLines* opecode_binary, BinaryLines* target_binary, BinaryLines* are_binary) {
	BinaryLines* head_combined = NULL;
		while (source_binary && opecode_binary && target_binary && are_binary) {
		char combined_line[BINARYWORD+1] = {0};
		strcat(combined_line, source_binary->line);
		strcat(combined_line, opecode_binary->line);
		strcat(combined_line, target_binary->line);
		strcat(combined_line, are_binary->line);    
		AddLine(&head_combined, combined_line);
		source_binary = source_binary->next;
		opecode_binary = opecode_binary->next;
		target_binary = target_binary->next;
		are_binary = are_binary->next;
	}
return head_combined;
}	        		        
