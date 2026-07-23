/*File Overview:
This program is responsible for reading Assembly files, performing checks, and printing output files with specific extensions like .am, .ext, .ent, and .ob. The program consists of pre-assembly processing, error checking, two passes through the file, and cleaning up resources.*/

#include "main.h"
int i=0;
char dataLine[MAX_LINE_LENGTH];
char line[MAX_LINE_LENGTH];
char *colonPos;
char label_name[MAX_LINE_LENGTH];
char first_word[MAX_LINE_LENGTH];
char arg1[MAX_LINE_LENGTH];
char arg2[MAX_LINE_LENGTH];

/* Prints status messages and errors, if any. Calls other functions to generate output files.*/
int main(int argc,char *argv[]){
    	 
	if(argc<2){/*Need to be 2*/
		printf("%s","Invaild name of file.\n");
		exit(1);
	}
	else{/*If there are valid files:*/
		for (i = FIRST; i < argc; i++){ /*Go over all files from command line*/         
			strcpy(name,argv[i]);
			strcpy(am_file,argv[i]);
			strcat(am_file, ".am");/* Add ".am" extension to the file name*/
			strcpy(ext_file,argv[i]);
			strcat(ext_file, ".ext");
			strcpy(ent_file,argv[i]);
			strcat(ent_file, ".ent");
			strcpy(obj_file,argv[i]);
			strcat(obj_file, ".ob");
			input = fopen(name, "r");/*Open Source file */
			if (input == NULL) {
			printf("%s\n","Failed to open the input file" );
				continue;
			}
			output_am = fopen(am_file,"w+");
			if (output_am == NULL) {
				printf("Failed to open the file outputAm"); 
			 	continue;
			}
			output_ext = fopen(ext_file,"w");
			if (output_ext == NULL) {
				printf("Failed to open the file outputExt"); 
			 	continue;
			}
			output_ent = fopen(ent_file,"w");
			if (output_ent == NULL) {
				printf("Failed to open the file outputEnt"); 
			 	continue;
			}
			output_obj = fopen(obj_file,"w");
			if (output_obj == NULL) {
	    			printf("Failed to open the file outputObj"); 
	    		 	continue;
	    	    	}
	    	   
/* Processes the input file, find the mcros and open them into output_am.
Input: File pointers to the input and output .am files.*/
			PreAssembler( input, output_am);
		 	error=0;
			error=Errors(output_am);/* Checks for errors in the output .am file.
Output: Returns 1 if errors are found, 0 otherwise.*/
			if(!error){
				entry_nodes=FirstPass( output_am,output_ent,output_ext,output_obj);/* Performs the first pass on the .am file.  Output: Returns a LabelList* containing labels and location in table, prints .ext and .ent files.and print ic,dc to .ob file*/ 
				SeconedPass(output_am,output_obj,entry_nodes);/*Print the binary file*/
				
				}
			if(error)
				printf("%s","Errors were found so there is no output files");
				
		  	
		 fclose(input);
		fclose(output_am);
		fclose(output_ext);
		fclose(output_ent);
		fclose(output_obj); 	
			
		} 
		
	} 
	FreeLabelList(entry_nodes);	
return 0;
}





