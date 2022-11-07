#include <stdio.h>
#include "debugmalloc.h"

int CountChar(const char *text, char find);
char **Split(const char *text, char splitChar, int *arrayLength);
char* Append(char *dst, const char *text);
