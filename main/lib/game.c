#include "game.h"

void RunGame(Screen *screen, GameData *data){

  if(screen == NULL || data == NULL)
    return;

  Panel *activePanel;
  ClearWindow(screen->topWindow);
  ClearWindow(screen->bottomWindow);

  activePanel = GetActivePanel(data->firstPanel);

  //If there was no save before, the starting panel will be the active panel
  if(activePanel == NULL){
    activePanel = GetStartPanel(data->firstPanel);
    activePanel->active = true;
  }

  //If there is no starting panel, return completely
  if(activePanel == NULL)
    return;

  DisplayPanel(activePanel, screen); 
}
