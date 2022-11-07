#include <stdio.h>
#include "debugmalloc.h"

int CountChar(const char *text, char find);
char **Split(char *text, char splitChar, int *arrayLength);
char* Append(char *dst, const char *text);
