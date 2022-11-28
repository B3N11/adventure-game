#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <string.h>
#include "debugmalloc.h"
#include "filehandler.h"
#include "gameData.h"
#include "ioHandle.h"
#include "panel.h"

void RunGame(Screen *screen, GameData *data);
Panel *HandleInput(Screen *screen, GameData *data, Panel *activePanel, char input);
Panel *EvaluateChoice(Screen *screen, GameData *data, Panel *activePanel, int choiceIndex);
Panel *ActivateNewPanel(Panel *activePanel, Panel *first, char *id);
void PickupItem(Screen *screen, Item *first, char *id);
void Save(GameData *data, Panel *activePanel);
void EndGame(Screen *screen, GameData *data, Panel *activePanel);

#endif
