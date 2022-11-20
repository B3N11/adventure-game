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
  char input = GetPressedKey();

  //Run the game while player doesn't quit
  while(input != 'q'){

    activePanel = HandleInput(data, activePanel, input);

    if(activePanel == NULL)
      return;

    DisplayPanel(activePanel, screen);

    input = GetPressedKey();
  }
}

Panel *HandleInput(GameData *data, Panel *activePanel, char input){

  if(data == NULL || activePanel == NULL)
    return activePanel;

  //Remove the ASCII "offset". If input was 1, the ascii code is 49
  int normalInput = input - 48;

  //Chek if input is 0-9. That means, one of the choices were pressed
  if(normalInput >= 0 && normalInput <= 9)
    activePanel = EvaluateChoice(data, activePanel, normalInput);

  return activePanel;
}

Panel *EvaluateChoice(GameData *data, Panel *activePanel, int choiceIndex){

  if(activePanel == NULL || data == NULL)
    return activePanel;

  if(activePanel->choices[choiceIndex]->type == 'P')
    activePanel = ActivateNewPanel(activePanel, data->firstPanel, activePanel->choices[choiceIndex]->contentID);

  return activePanel;
}

Panel *ActivateNewPanel(Panel *activePanel, Panel *first, char *id){

  if(activePanel == NULL || first == NULL || id == NULL)
    return activePanel;

  activePanel->active = false;
  activePanel = SetActivePanel(first, id);
  activePanel->active = true;

  return activePanel;
}
