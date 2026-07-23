/*Checkes errors in assembly code*/
#include <string.h>
#include <ctype.h>
#include "share.h"
#include "erros.h"
 char newLine[MAX_LINE_LENGTH];
char oprand[MAX_LINE_LENGTH];
int Errors(FILE* output_am) {	/*Assembly code*/
	
	const char* validWordsNeedTwo[] = {"mov", "cmp", "add", "sub","lea" };
	const char* vaildWordsNeedOne[]={ "not", "clr", "inc", "dec", "jmp", "bne", "red", "prn", "jsr",   ".entry", ".extern", ".string", ".data"};
	const char* vaildWordsNeedZero[]={"rts", "stop"};
  	const char* registers[]={"@r1", "@r2","@r3","@r4","@r5","@r6","@r7"};
  	int sizeNeedTwo=sizeof(validWordsNeedTwo) / sizeof(validWordsNeedTwo[0]);
  	int sizeNeedOne=sizeof(vaildWordsNeedOne) / sizeof(vaildWordsNeedOne[0]);
  	int sizeNeedZero=sizeof(vaildWordsNeedZero) / sizeof(vaildWordsNeedZero[0]);
  	int sizeReg=sizeof(registers) / sizeof(registers[0]);
  	int error=0;
	int is_vaild=0;/*If there error in labels make it 1*/
	int is_printed=0;/*If there is error in assembly line*/
	
	listOfLabels=Labels(output_am, &is_vaild);/*List of all labels- checkes that there is no 2 same labels andcheck that there is no label before .extern or .entry-if there is error is_vaild is turn into 1*/
	if(is_vaild) error=1;/*If error in labels*/
	
	listOfExtern=Extern(output_am, &is_vaild);/*List of all extern- checkes that there is no 2 same extern labels*/  if(is_vaild) error=1;
	
	listOfEntry=Entry(output_am, &is_vaild);/*List of all entry -checkes that there is no 2 same entry labels*/
	if(is_vaild) error=1;/*If error in labels*/
	
	 is_printed=CheckLabelsForLettersAndDigits(listOfLabels);/*Check if all labels are letters and numbers in addition check there is no 2 same labels to add-return 1 if error*/
	 if(is_printed) error=1;
		
	 is_printed=CheckLabelsForLettersAndDigits(listOfExtern);/*Check if all entry labels are letters and numbers in addition check there is no 2 same labels to add-return 1 if error*/
 	 if(is_printed) error=1;
		
	 is_printed=CheckLabelsForLettersAndDigits(listOfEntry);/*Check if all extern labels are letters and numbers in addition check there is no 2 same labels to add-return 1 if error*/
 	 if(is_printed) error=1;
		
	 is_printed=CheckForCommonLabels(listOfExtern, listOfEntry);/*Check if there is label decleared enrty and etern in addition check there is no 2 same labels to add-return 1 if error*/
	 if(is_printed) error=1;
		
	/*Check if oprand is one of the vaild words-one of the save words-return 1 if error*/
	 is_printed=CheckOprand(output_am,validWordsNeedTwo,sizeNeedTwo,vaildWordsNeedOne,sizeNeedOne,vaildWordsNeedZero,sizeNeedZero);
	 if(is_printed) error=1;
		
	/*Merge the list of all labels*/
	listOfLabels = MergeLists(listOfLabels, listOfExtern);
    	listOfLabels = MergeLists(listOfLabels, listOfEntry);
    
	 is_printed=VaildArguemnts(output_am,registers,sizeReg,listOfLabels,validWordsNeedTwo,sizeNeedTwo,vaildWordsNeedOne,sizeNeedOne);/*Check if vaild arguemnts-number,label or register-return 1 if error*/
	 if(is_printed) error=1;
	
	/*check if there is the right number of arguemnt in each line-return -1 if error*/
	 is_printed=CountTwoWords(output_am,validWordsNeedTwo,sizeNeedTwo);
	 if(is_printed) error=1;
	 is_printed=CountOneWord(output_am,vaildWordsNeedOne,sizeNeedOne);
	  if(is_printed) error=1;
	 is_printed=CountZeroWord(output_am,vaildWordsNeedZero,sizeNeedZero);
	  if(is_printed) error=1;
	 
	is_printed= VaildStringData( output_am);/*Check if .string have " " and .data in format number,number,number..*/
	 if(is_printed) error=1;
	 	
	 free(listOfLabels);
	 free(listOfExtern);
	 free(listOfEntry);
	 
	return  error;
}
