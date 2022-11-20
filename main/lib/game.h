#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <string.h>
#include "gameData.h"
#include "ioHandle.h"
#include "panel.h"

void RunGame(Screen *screen, GameData *data);
Panel *HandleInput(GameData *data, Panel *activePanel, char input);
Panel *EvaluateChoice(GameData *data, Panel *activePanel, int choiceIndex);
Panel *ActivateNewPanel(Panel *activePanel, Panel *first, char *id);

#endif
