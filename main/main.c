#include "main.h"

int main(int argc, char **args){

  //Turn off output buffer
  setbuf(stdout, NULL);

  //Run the program
  Run(argc, args);
  
  return 0;
}

//Run the main functions of the program
void Run(int argc, char **args){

  //Handle arguments and initiate program data
  HandleStartingArgs(argc, args);

  //Read game data (panels and items)
  GameData *data =  HandleRootfile(args[1]);
  /*GameData *data = HandleRootfile("root/root.txt");*/

  //Read save file
  HandleSaveFile(args[2], data);
  /*HandleSaveFile("root/save.txt", data);*/

  //Create a new screen that determines the size
  Screen *screen = CreateScreen();

  //Create title screen and wait for input to progress
  DrawTitleScreen(screen, data, COL_DARKGRAY, COL_LIGHTYELLOW);
  GetPressedKey();

  //Run game loop
  RunGame(screen, data);
  ClearScreen();
  
  //Release resources
  FreeGameData(data);
  free(screen);
}

//Checks for the validity of the program starting arguments
void HandleStartingArgs(int argc, char **args){

  //If the user didn't provide enough arguments, close the program
  if(argc < 3)
    ExitError("Invalid parameters.\n      kalandjatek [rootfile] [characterfile]");

  //If the rootfile doesn't exist, close the program
  if(!FileExists(args[1]))
    ExitError("The rootfile does not exist.");
}

//Creates the basic data from the rootfile
GameData *HandleRootfile(char *path){

  //Check for parameter validity
  if(path == NULL)
   return NULL; 

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
  result->firstItem = NULL;
  result->firstPanel = NULL;

  //Iterate trough the files listed in the roofile
  for(int i = 2; i < rootfileLength; i++){
    
    //Extract the raw filepath from the line
    char *line = rootfile[i];
    char *path = Crop(line, 2, 0);
    
    //If one of the files listed in rootfile doesnt exist, quit
    if(!FileExists(path)){
      if(path != NULL)
       free(path);
      FreeStringArray(rootfile, rootfileLength);
      FreeGameData(result);
      ExitError("One of the files in rootfile are invalid.");
    }

    //If the current file path points to an item file
    if(line[0] == 'I')
      result->firstItem = CreateItemsFromFile(result->firstItem, path); 
    
    //If the current file path points to a panel file
    if(line[0] == 'P')
      result->firstPanel = CreateAndAddPanel(result->firstPanel, path);

    free(path);
  }

  //Free the file content from the memory
  FreeStringArray(rootfile, rootfileLength);

  return result;
}

//Reads the savefile and handles its content
void HandleSaveFile(char *path, GameData *data){

  //Check parameter validity
  if(data == NULL || path == NULL)
    return;

  //Save file path for later access
  data->saveFile = CreateCopyString(path);

  //Read file
  int length;
  char **file = ReadAllLines(path, &length);

  //It's not a problem if the file doesn't extist, we will create it when saving
  if(file == NULL){
    FreeStringArray(file, length);
    return;
  }

  //If nothing is in the file yet, return 
  if(length == 0){
    FreeStringArray(file, length);
    return;
  }

  //Set the active panel to the saved one
  SetActivePanel(data->firstPanel, file[0]);

  //If there are no saved items, return
  if(length == 1){
    FreeStringArray(file, length);
    return;
  }

  //Split up the items
  int splitLength;
  char **split = Split(file[1], ' ', &splitLength);

  //Set all the items in the savefile as owned
  for(int i = 0; i < splitLength; i++)
    SetItemOwnership(data->firstItem, split[i], true);

  //Free resources
  FreeStringArray(split, splitLength);
  FreeStringArray(file, length);
}

//Create new screen
Screen *CreateScreen(){

  //Allocate memory
  Screen *result = (Screen*) malloc(sizeof(Screen));

  //Set size
  result->width = 70;
  result->height = 32;

  //Split is where the two windows are separated
  result->split = result->height - (result->height * 0.2);

  //Set the parameters of the top and bottom windows
  result->topWindow = (Window){.minX=2, .minY=2, .maxX = result->width - 2, .maxY=result->split - 1};
  result->bottomWindow = (Window) {.minX=2, .minY=result->split+1, .maxX=result->width-2, .maxY=result->height-2};

  return result;
}

//Exits the program with an error message
void ExitError(const char* msg){

  if(msg != NULL)
   printf("%s\n", msg);
  exit(1);
}
