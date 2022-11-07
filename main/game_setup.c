#include "game_setup.h"
#include "../lib/filehandler.h"
#include "../lib/debugmalloc.h"
#include "../lib/logger.h"

typedef struct GameData{
  char *title;
  char *creator;
}GameData;

GameData *CreateGameData(char *title, char *creator){

  if(title == NULL || creator == NULL)
    return NULL;

  GameData *result;

  return result;
}

GameData *HandleRootfile(char *file){

  if(file == NULL)
    ExitError("Parameter can't have NULL value. (HandleRootfile(char *file))");

  int length;
  char **lines = ReadAllLines(file, &length); 

  GameData *result = malloc(sizeof(GameData));
  result->title = lines[0];
  result->creator = lines[1];

  for(int i = 2; i < length; i++)
    free(lines[i]);
  free(lines);

  return result;
}

int main(int argc, char **args){

  if(argc <= 1)
    ExitError("Invalid parameters.\n      kalandjatek [rootfile] [characterfile]");

   return 0;
}
