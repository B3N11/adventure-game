#include "gameData.h"

GameData *CreateGameData(){

    GameData *result = (GameData*) malloc(sizeof(GameData));
    result->firstItem = NULL;
    result->firstPanel = NULL;
    result->creator = NULL;
    result->title = NULL;
    result->saveFile = NULL;

    return result;
}

void FreeGameData(GameData *data){

  if(data == NULL)
    return;

  if(data->title != NULL)
    free(data->title);

  if(data->creator != NULL)
    free(data->creator);

  if(data->saveFile != NULL)
    free(data->saveFile);

  if(data->firstItem != NULL)
    FreeItemList(data->firstItem);

  if(data->firstPanel != NULL)
    FreePanelList(data->firstPanel);

  //Free save
  free(data);
}
