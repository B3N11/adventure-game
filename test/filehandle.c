#include <stdio.h>
#include <stdbool.h>
#include "/home/brokkr/uni/sub/prog/lib/debugmalloc.h"

void GetFiles(char *rootfile);
void ErrorExit(const char *error);

int main(int argc, char **args){

  if(argc < 3)
    ErrorExit("Not enought arguments.\n    kalandjatek [rootfile] [characterfile]\n");
 
  GetFiles(args[1]);

  return 0;
}

void GetFiles(char *rootfile){

  FILE* fp;
  fp = fopen(rootfile, "r");

  if(fp == NULL)
    ErrorExit("The root file could not be opened.");
}

void ErrorExit(const char *error){

  puts(error);
  exit(1);
}
