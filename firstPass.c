/*Move down .data and .string
Print ic and dc to final file
Get labels names and location in file
Get extern and entry labels names and location in file(create .ent , .ext files)
*/
#include "firstPass.h"

 
LabelList* FirstPass( FILE* output_am,FILE* output_ent,FILE* output_ext,FILE* output_obj){

	MoveDown(output_am);	/*Get .data and .string down in file*/
	Data node = {0,0};
    	Data* dcIc = &node;		/*ic and dc*/
	LabelList* label_index=LabelIndex(output_am,dcIc);/*All labels name and location in table*/
	fprintf(output_obj,"%d  %d\n",dcIc->ic,dcIc->dc);/*Print number of command lines and data lines to final file*/
	LabelList* entry_nodes =EntryNodes(output_am,label_index);/*Function to print all entry labels name and location*/
	if(entry_nodes!=NULL)/*If there is entry*/
		PrintEntry(output_ent,entry_nodes);
	LabelList* headExternLinelList=LabelsExtern(output_am, output_ext);/*Function to print all extern labels that are used as arguemnt and location in table*/ 
	if(headExternLinelList!=NULL)	/*If there is extern*/
		PrintList( headExternLinelList,output_ext);
			
	FreeLabelList(entry_nodes);
	entry_nodes = NULL;
	FreeLabelList(headExternLinelList);
	headExternLinelList = NULL;	
	return label_index;
} 
