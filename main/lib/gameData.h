#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "debugmalloc.h"
#include "item.h"
#include "panel.h"
#include "ioHandle.h"

typedef struct GameData{

  char *title;
  char *creator;
  Panel *firstPanel;
  Item *firstItem;
  Screen *screen;
}GameData;

GameData *CreateGameData();
void FreeGameData(GameData *data);

#endif
