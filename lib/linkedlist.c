#include <stdio.h>
#include <stdbool.h>
#include "../lib/filehandler.h"
#include "../lib/ext_string.h"

typedef struct Panel{

	char *id;
	char *description;
	struct Panel *next;
	struct Panel *prev;
}Panel;

Panel *GetLastPanel(Panel *first){
	
	Panel *current = first;
	while(current->next != NULL)
		current = current->next;

	return current;
}

Panel *CreatePanel(char *line){

	int length;
	char **split = Split(line, ' ', &length);

	//bug if split length is 1
	//
	Panel *result;
	/*result = malloc(sizeof(Person));*/
	/*result->name = split[0];*/
	/*result->age = atoi(split[1]);*/
	/*result->gender = split[2];*/
	/*result->next = NULL;*/
	/*result->prev = NULL;*/

	free(split[1]);
	free(split);

	return result;
}

Panel *AddPanelNode(Panel *add, Panel *first){

	Panel *last = GetLastPanel(first);
	Panel *tmp = add;
	tmp->prev = last;
	last->next = tmp;

	return tmp;
}

bool FreePanel(Panel *person){

	if(person == NULL)
		return false;

	free(person->id);
	free(person->description);
	free(person);

	return true;
}

bool FreeList(Panel *first){

	if(first == NULL)
		return false;

	Panel *tmp;
	Panel *current = first;
	while(true){
		if(current->next == NULL)
			break;
		
		tmp = current->next;
		FreePanel(current);
		current = tmp;
	}

	FreePanel(current);	

	return true;
}

/*void Run(){*/
	
	/*int fileLength;*/
	/*char **file = ReadAllLines("test.txt", &fileLength);*/

	/*Person *first = CreatePerson(file[0]);*/
	
	/*for(int i = 1; i < fileLength; i++){*/
		/*Person *new = CreatePerson(file[i]);*/
		/*new = AddNode(new, first);*/
	/*}*/

	
	/*for(int i = 0; i < fileLength; i++)*/
		/*free(file[i]);*/
	/*free(file);*/
/*}*/
