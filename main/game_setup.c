#include "game_setup.h"
#include "../lib/filehandler.h"
#include "../lib/debugmalloc.h"

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

  if(argc <= 1){
    printf("Too few arguments!");
    return -1;
  }

  GameData *result = HandleRootfile(args[1]);
  puts(result->title);
  puts(result->creator);

  void **ptrs = malloc (sizeof(void*)*3);
  ptrs[0] = result->title;
  ptrs[1] = result->creator;
  ptrs[2] = result;

  for(int i = 0; i < 3; i++)
    free(ptrs[i]);

  free(ptrs);
  return 0;
}
