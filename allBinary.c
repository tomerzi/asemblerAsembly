 #include "seconedPass.h"
 char* colonPos;
 char arg1[MAX_LINE_LENGTH];
 char arg2[MAX_LINE_LENGTH];

BinaryLines* AllBinary(FILE* noEntryExtern,BinaryLines* combined_binary,LabelList* label_index){
	rewind(noEntryExtern);
 	BinaryLines* all_binary=NULL;
 	BinaryLines* temp_combined_binary=combined_binary;
 	char number_binary[BINARYWORD+1];
	int conditionMet = 0;
 	while (fgets(line, MAX_LABEL_LENGTH, noEntryExtern)!=NULL && temp_combined_binary!=NULL) { 
	 	AddLine(&all_binary, temp_combined_binary->line);/*Command binary code*/
	 	colonPos = strstr(line, COLON);
	 	if (colonPos != NULL) /* If label-there is : */			
			memmove(line, colonPos + 1, strlen(colonPos + 1) + 1);	/*Take line to left*/ 			int scanned=sscanf(line, "%s%s%s", first_word,arg1,arg2);	
	  	conditionMet = 0;
		int number;
 		if(scanned>=2){
	    		if (IsValidNumber(arg1, &number) && strcmp(first_word,".string")!=0 && strcmp(first_word,".data")!=0 ) {/*If arg1 is number*/  
		    		NumberBinary(number_binary,number);/*If arg1 is number*/
				AddLine(&all_binary, number_binary);
				conditionMet=1;
			}
			LabelList* foundLabel1=FindInfoLabel(label_index,arg1);/*If arg1 is label*/		
			if(foundLabel1!=NULL){
				LabelBinary(label_index,number_binary,foundLabel1);	
				AddLine(&all_binary, number_binary);
				conditionMet=1;
				strcpy(arg1, "");/*To stop it from add extrea line*/
			}
		}
    		if(scanned==3){
    		if (strchr(arg1, AT)) {
				AtBinary(number_binary,arg1,arg2);/*Handle if arg1 and arg2 include @ or if only arg1 has @*/
				conditionMet=1;
				AddLine(&all_binary, number_binary);
			}
    			if (IsValidNumber(arg2, &number) && strcmp(first_word,".string")!=0 && strcmp(first_word,".data")!=0 )      {/*If arg2 is number*/  
		    		NumberBinary(number_binary,number);/*If arg2 is number*/
				AddLine(&all_binary, number_binary);
				conditionMet=1;		        		
			}
    			char *comma = strstr(arg2, COMMA);
			if (comma != NULL) {
		        		char *nextPart = comma + 1; 
			 	LabelList* foundLabel2=FindInfoLabel(label_index,nextPart);/*If arg2 is label*/				if(foundLabel2!=NULL){
					LabelBinary(label_index,number_binary,foundLabel2);	
					AddLine(&all_binary, number_binary);
					conditionMet=1;
				}
			}
			if (strchr(arg2, AT)&& !strchr(arg1, AT)) {
				Arg2Binary(number_binary,arg2);/*Handle if its  arg2 has @*/
				conditionMet=1;
				AddLine(&all_binary, number_binary);
				strcpy(arg2, "");/*To stop it from add extrea line*/
			}
			
		}		
	temp_combined_binary=temp_combined_binary->next;/*Next command binary line*/
	}
	rewind(noEntryExtern);
	while (fgets(line, MAX_LABEL_LENGTH, noEntryExtern)!=NULL){/*Print string and data*/
 		conditionMet = 0;
		colonPos = strstr(line, COLON);
	 	if (colonPos != NULL) /* If label-there is : */			
			memmove(line, colonPos + 1, strlen(colonPos + 1) + 1);/*Take line to left*/ 			 sscanf(line, "%s%s", first_word,arg1);/*first_word=.data/.string arg1=the data*/
		if( strcmp(first_word,".string")==0){
			BinaryLines* string_binary =StringAscii(arg1);
			BinaryLines* temp_string= string_binary;
			while(temp_string!=NULL){
			 	AddLine(&all_binary, temp_string->line);
		 		temp_string=temp_string->next;				 			 	}
		 	AddLine(&all_binary, "000000000000");/*NULL*/
		 	conditionMet=1;
		 }				 					
		if( strcmp(first_word,".data")==0){				
			BinaryLines* data_binary =DataAscii(arg1);
			BinaryLines* temp_data= data_binary;
			while(temp_data!=NULL){
			 	AddLine(&all_binary, temp_data->line); 
			 	temp_data=temp_data->next;
		 	}
		 	conditionMet=1;		 	
		}
	}
	if(!conditionMet)/*Extern*/
		AddLine(&all_binary, "000000000001");
		
	return all_binary;
}	 	
