#include "main.h"

int main(int argc, char **args){

   HandleStartingArgs(argc, args);
   GameData *result =  HandleRootfile(args[1]);
  
   if(result != NULL)
     printf("DONE!");

   FreeGameData(result);
   return 0;
}

//Checks for the validity of the program starting arguments
void HandleStartingArgs(int argc, char **args){

  if(argc < 3)
    ExitError("Invalid parameters.\n      kalandjatek [rootfile] [characterfile]");

  if(!FileExists(args[1]))
    ExitError("The rootfile does not exist.");

  if(!FileExists(args[2]))
    ExitError("The character file does not exist.");
}

//Creates the basic data from the rootfile
GameData *HandleRootfile(char *path){

  //Check for parameter validity
  if(path == NULL)
    ExitError("Parameter can't be NULL. (HandleRootfile(char *path))");

  //Read the rootfile
  int rootfileLength;
  char **rootfile = ReadAllLines(path, &rootfileLength);

  //Check if file structure is valid
  if(rootfile == NULL || rootfileLength <= 2){
    FreeStringArray(rootfile, rootfileLength);
    ExitError("The rootfile does not exist or the structure is invalid.\n     1.[game title]\n     2.[creator name]\n     3.[panel/item file path]\n     .\n     .\n     .");
  }

  //Create game data
  GameData *result = CreateGameData();
  result->title = CreateCopyString(rootfile[0]); 
  result->creator = CreateCopyString(rootfile[1]);

  for(int i = 2; i < rootfileLength; i++){
    
    char *line = rootfile[i];
    char *path = Crop(line, 2, 0);
    
    if(line[0] == 'I')
      result->firstItem = CreateItemsFromFile(result->firstItem, path); 
    if(line[0] == 'P')
      result->firstPanel = CreateAndAddPanel(result->firstPanel, path);
  }

  //Free the file content from the memory
  FreeStringArray(rootfile, rootfileLength);

  return result;
}
