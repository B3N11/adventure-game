#include "main.h"

int main(int argc, char **args){

  setbuf(stdout, NULL);

  //Run the program
  bool result = Run(argc, args);
  
  if(!result)
    return -1;
  return 0;
}

//Run the main functions of the program
bool Run(int argc, char **args){

  char *result;
  //Handle arguments and initiate program data
  //result = HandleStartingArgs(argc, args);
  //if(result != NULL)
  //  ExitError(result);
  GameData *data =  HandleRootfile(args[1]);
  result = HandleSaveFile(args[2], data);
  Screen *screen = CreateScreen();

  //Create title screen and wait for input to progress
  DrawTitleScreen(screen, data, COL_DARKGRAY, COL_LIGHTYELLOW);
  GetPressedKey();

  //Run game
  RunGame(screen, data);
  ClearScreen();
  
  //Release resources
  FreeGameData(data);
  free(screen);

  return true;
}

//Checks for the validity of the program starting arguments
char *HandleStartingArgs(int argc, char **args){

  if(argc < 3)
    return "Invalid parameters.\n      kalandjatek [rootfile] [characterfile]";

  if(!FileExists(args[1]))
    return "The rootfile does not exist.";

  if(!FileExists(args[2]))
    return "The character file does not exist.";

  return NULL;
}

//Creates the basic data from the rootfile
GameData *HandleRootfile(char *path){

  //Check for parameter validity
  /*if(path == NULL)*/
    /*ExitError("Parameter can't be NULL. (HandleRootfile(char *path))");*/

  //Read the rootfile
  int rootfileLength;
  //char **rootfile = ReadAllLines(path, &rootfileLength);
  char **rootfile = ReadAllLines("root/root.txt", &rootfileLength);

  //Check if file structure is valid
  if(rootfile == NULL || rootfileLength <= 2){
    FreeStringArray(rootfile, rootfileLength);
    ExitError("The rootfile does not exist or the structure is invalid.\n     1.[game title]\n     2.[creator name]\n     3.[panel/item file path]\n     .\n     .\n     .");
  }

  //Create game data
  GameData *result = CreateGameData();
  result->title = CreateCopyString(rootfile[0]); 
  result->creator = CreateCopyString(rootfile[1]);
  result->firstItem = NULL;
  result->firstPanel = NULL;

  for(int i = 2; i < rootfileLength; i++){
    
    char *line = rootfile[i];
    char *path = Crop(line, 2, 0);
    
    if(line[0] == 'I')
      result->firstItem = CreateItemsFromFile(result->firstItem, path); 
    if(line[0] == 'P')
      result->firstPanel = CreateAndAddPanel(result->firstPanel, path);

    free(path);
  }

  //Free the file content from the memory
  FreeStringArray(rootfile, rootfileLength);

  return result;
}

char *HandleSaveFile(char *path, GameData *data){

  if(path == NULL)
    return "Parameter cannot be NULL";

  int length;
  char **file = ReadAllLines(path, &length);

  if(file == NULL)
    return "Problem opening the save file.";

  if(length <= 1){
    FreeStringArray(file, length);
    return "Invalid save file format.";
  }

  SetActivePanel(data->firstPanel, file[0]);

  int splitLength;
  char **split = Split(file[1], ' ', &splitLength);

  for(int i = 0; i < splitLength; i++)
    SetItemOwnership(data->firstItem, split[i]);

  FreeStringArray(split, splitLength);
  FreeStringArray(file, length);

  return NULL;
}

//Create new screen
Screen *CreateScreen(){

  Screen *result = (Screen*) malloc(sizeof(Screen));

  result->width = 70;
  result->height = 30;
  result->split = result->height - (result->height * 0.2);

  result->topWindow = (Window){.minX=2, .minY=2, .maxX = result->width - 2, .maxY=result->split - 1};
  result->bottomWindow = (Window) {.minX=2, .minY=result->split+1, .maxX=result->width-2, .maxY=result->height-2};

  return result;
}
