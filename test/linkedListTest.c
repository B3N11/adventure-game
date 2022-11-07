#include <stdio.h>
#include "../lib/filehandler.h"
#include "../lib/ext_string.h"

typedef struct Person{

	char *name;
	int age;
	char *gender;
	struct Person *next;
	struct Person *prev;
}Person;

Person *GetLastPerson(Person *first){
	
	Person *current = first;
	while(current->next != NULL)
		current = current->next;

	return current;
}

Person *CreatePerson(char *line){

	int length;
	char **split = Split(line, ' ', &length);

	Person *result;
	result = malloc(sizeof(Person));
	result->name = split[0];
	result->age = atoi(split[1]);
	result->gender = split[2];
	result->next = NULL;
	result->prev = NULL;

	free(split[1]);
	free(split);

	return result;
}

Person *AddNode(Person *add, Person *first){

	Person *last = GetLastPerson(first);
	Person *tmp = add;
	tmp->prev = last;
	last->next = tmp;

	return tmp;
}

void FreePerson(Person *person){

	free(person->name);
	free(person->gender);
	free(person);
}

void Run(){
	
	int fileLength;
	char **file = ReadAllLines("test.txt", &fileLength);

	Person *first = CreatePerson(file[0]);
	/*Person *second = CreatePerson(file[1]);*/
	/*Person *third = CreatePerson(file[2]);*/

	/*first->next = second;*/
	/*second->prev = first;*/
	/*second->next = third;*/
	/*third->prev = second;*/
	/*third->next = NULL;*/
	
	for(int i = 1; i < fileLength; i++){
		Person *new = CreatePerson(file[i]);
		new = AddNode(new, first);
	}

	Person *tmp;
	Person *current = first;
	while(true){
		printf("%p %s %d %s %p\n", current, current->name, current->age, current->gender, current->next);

		if(current->next == NULL)
			break;
		
		tmp = current->next;
		FreePerson(current);
		current = tmp;
	}

	FreePerson(current);	

	for(int i = 0; i < fileLength; i++)
		free(file[i]);
	free(file);
}

int main(void){

	Run();
	return 0;
}
