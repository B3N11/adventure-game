#ifndef GAME_H
#define GAME_H

#include "debugmalloc.h"
#include "item.h"
#include "panel.h"

typedef struct GameData{

  char *title;
  char *creator;
  Panel *firstPanel;
  Item *firstItem;
}GameData;

GameData *CreateGameData();
void FreeGameData(GameData *data);

#endif
