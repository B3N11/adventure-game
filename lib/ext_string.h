#include <stdio.h>
#include <string.h>
#include "debugmalloc.h"

char *Crop(char *text, unsigned int front, unsigned int back);
int CountChar(const char *text, char find);
char **Split(const char *text, char splitChar, int *arrayLength);
char* Append(char *dst, const char *text);
