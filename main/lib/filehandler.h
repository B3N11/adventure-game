#ifndef FILEHANDLE_H
#define FILEHANDLE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "ext_string.h"

bool FileExists(char *file);
char **ReadAllLines(const char *path, int *length);
char *ReadAllLinesStr(const char *path);

#endif
