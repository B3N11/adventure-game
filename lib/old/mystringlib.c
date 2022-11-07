#include "mystringlib.h"

bool AppendStr(String *dst, const char *text, int n){

	if(dst == NULL || text == NULL)
		return false;

	int newLength = dst->length + strlen(text);
	dst->data = (char*) realloc(dst->data, newLength);
	memcpy(dst->data + dst->length, text, n);
	dst->length = newLength;

	return true;
}

//Creates a new string instance
String* CreateString(const char *text){

	String *result = (String*)malloc(sizeof(int));
	result->data = NULL;
	result->length=0;
	if(text != NULL)
		SetTextStr(result, text);
	else
		SetTextStr(result, "");
	
	return result;
}

//Clears the content of a string and replaces it wit ""
bool ClearStr(String *mystring){

	if(mystring == NULL)
		return false;

	//Reallocate data to only 1 char
	mystring->data = (char*)realloc(mystring->data, 1);	

	//Set data to an empty string;
	strcpy(mystring->data, "");

	//Set new length of data
	mystring->length = 0;
	return true;
}

//Adds text tolan existing string
bool AddTextStr(String *mystring, const char *text){

	//Calculate size of the text
	int length = 0;
	while(text[length] != '\0')
		length++;

	//Expand the size of the data to contain the text
	mystring->data = (char*)realloc(mystring->data, mystring->length + length);

	//Copy the text to the end of data
	memcpy(mystring->data+mystring->length, text, length);

	//Calculate the new length of the data
	mystring->length = mystring->length + length;

	return true;
}

//Reads user input from console until the user types the "readUntil" char and then replaces that with "replaceWith" char
bool ReadConsoleInput(String *myString, int maxLength, const char readUntil, const char replaceWith){

	//Free data if it had content previously
	if(myString->data != NULL)
		free(myString->data);	

	//Allocate memory
	char *result = (char*)malloc(maxLength *  sizeof(char));

	//If allocation was unsuccessful
	if(result == NULL)
		exit(-1);
	
	int i = -1;

	//Read character from console input until the user enters the specified char
	do{

		i++;
		scanf("%c", &result[i]);

	//If we reached the replaceWith char, we escape
	}while(result[i] != readUntil && i < maxLength);
	
	//If we reached the 'readUntil' char, we replace it with the 'replaceWith'
	if(i < maxLength)
		result[i] = replaceWith;

	//Free remaining space
	myString->data = realloc(result, i * sizeof(char));
	myString->length = i;

	return true;
}

bool SetTextStr(String *mystring, const char *text){

	if(mystring == NULL || text == NULL)
		return false;

	if(mystring->data != NULL)
		free(mystring->data);

	int length = 0;
	while(text[length] != '\0')
		length++;

	mystring->data = (char*)malloc(length * sizeof(char));
	mystring->length = length;

	strcpy(mystring->data, text);

	return true;
}

bool TrimStr(String *mystring, const char trim){

	if(mystring == NULL)
		return false;

 	int start = 0;
	while(mystring->data[start] == trim)
		start++;

	int index = mystring->length - 1;
	int end = 0; 
	while(mystring->data[index] == trim && mystring->data[index] != '\0' && index >= 0){
		index--;
		end++;
	}

	int length = mystring->length - (start + end);

	char *result = (char*)malloc(length * sizeof(char));

	memmove(result, mystring->data + start, length);
	free(mystring->data);

	mystring->data = result;
	mystring->length = length;

	return true;
}
