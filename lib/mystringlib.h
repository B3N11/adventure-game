#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//Typedef
typedef struct String{
	char *data;
	int length;
}String;

//Function declaration
String* CreateString();
bool TrimStr(String *mystring, const char trim);
bool SetTextStr(String *mystring, const char *text);
bool ReadConsoleInput(String *myString, int maxLength, const char readUntil, const char replaceWith);
void Log();
