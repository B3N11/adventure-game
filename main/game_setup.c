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
  int asd = strlen(lines[0]) + strlen(lines[1]);
  printf("%d\n", asd);

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

  free(result->title);
  free(result->creator);
  free(result);
  return 0;
}
