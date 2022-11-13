#include "gameData.h"

GameData *CreateGameData(){

    GameData *result = (GameData*) malloc(sizeof(GameData));

    return result;
}

void FreeGameData(GameData *data){

  if(data == NULL)
    return;

  if(data->title != NULL)
    free(data->title);

  if(data->creator != NULL)
    free(data->creator);

  if(data->firstItem != NULL)
    FreeItemList(data->firstItem);

  if(data->firstPanel != NULL)
    FreePanelList(data->firstPanel);

  //Free save
  free(data);
}
