#include "debugmalloc.h"
#include "item.h"
#include "panel.h"

typedef struct PlayerSave{

}PlayerSave;

typedef struct GameData{

  char *title;
  char *creator;
  Panel *firstPanel;
  Item *firstItem;
  PlayerSave *save;
}GameData;

GameData *CreateGameData();
void FreeGameData(GameData *data);
