#include "share.h"
#include "preAssembler.h"
void AddLineToMcro(Mcros* mcro, const char* line) {

	Command* newCommand = (Command*)malloc(sizeof(Command));
	if (newCommand == NULL) {
		printf("%s","No memory for newMcrodNode");
		exit(1);
	}
	strncpy(newCommand->line, line, MAX_LINE_LENGTH);
	CommandNode* newNode = (CommandNode*)malloc(sizeof(CommandNode));
	if (newNode == NULL) {
		printf("%s","No memory for newMcrodNode");
		exit(1);
	}
	newNode->commandData = newCommand;
	newNode->next = NULL;
	CommandNode** current = &mcro->allLines;
	while (*current != NULL) 
		current = &(*current)->next;
	*current = newNode;
}

Mcros* FindMcroByName(linkedMcros* head, const char* name) {
	linkedMcros* current = head;
	while (current != NULL) {
		if (current->mcroNode != NULL && strcmp(current->mcroNode->mcroName, name) == 0) {
		return current->mcroNode;
		}
	current = current->nextNode;
	}
	return NULL; 
}

void PrintMcroLines(FILE* outputAm, Mcros* macro) {
	if (macro == NULL){
		printf("Macro o NULL\n");
		return;
	}
	if( outputAm == NULL) {
		printf("Output file is NULL\n");
		return;
	}
	CommandNode* currentLine = macro->allLines;
    	while (currentLine != NULL) {
        		if (currentLine->commandData != NULL) 
            		fputs(currentLine->commandData->line, outputAm);
	currentLine = currentLine->next;
    }
}

void FreeLinkedMcros(linkedMcros* mcros) {
	linkedMcros* currentMcroNode = mcros;
	while (currentMcroNode != NULL) {
		linkedMcros* nextMcroNode = currentMcroNode->nextNode;
		Mcros* mcro = currentMcroNode->mcroNode;
		free(mcro->mcroName); 
		CommandNode* currentCommandNode = mcro->allLines;
		while (currentCommandNode != NULL) {
			CommandNode* nextCommandNode = currentCommandNode->next;
			free(currentCommandNode->commandData); 
			free(currentCommandNode); 
			currentCommandNode = nextCommandNode;
		}
		free(mcro); 
		free(currentMcroNode); 
		currentMcroNode = nextMcroNode;
	}
}
