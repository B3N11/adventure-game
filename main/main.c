#include "../lib/filehandler.h"
/*#include "../lib/linkedlist.c"*/
#include "../lib/ext_string.h"
#include "../lib/debugmalloc.h"
#include "../lib/logger.h"

void HandleStartingArgs(int argc, char **args);

int main(int argc, char **args){

   HandleStartingArgs(argc, args);
  
   return 0;
}

void HandleStartingArgs(int argc, char **args){

  if(argc < 3)
    ExitError("Invalid parameters.\n      kalandjatek [rootfile] [characterfile]");

  int rootLength; 
  char **rootfile = ReadAllLines(args[1], &rootLength);

  if(rootfile == NULL)
    ExitError("There was a problem with opening the rootfile.");
  if(rootLength < 4){
    for(int i = 0; i < rootLength; i++)
      free(rootfile[i]);
    free(rootfile);

    ExitError("The rootfile structure is invalid.\n     1.[game title]\n     2.[creator name]\n     3.[panel/item file path]\n     .\n     .\n     .");
  }
}

void HandleRootfile(char *path){

  if(path == NULL)
    ExitError("Parameter can't be NULL. (HandleRootfile(char *path))");
}
