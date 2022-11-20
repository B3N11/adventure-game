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

    activePanel = HandleInput(screen, data, activePanel, input);

    if(activePanel == NULL)
      return;

    DisplayPanel(activePanel, screen);

    input = GetPressedKey();
  }
}

Panel *HandleInput(Screen *screen, GameData *data, Panel *activePanel, char input){

  if(data == NULL || activePanel == NULL)
    return activePanel;

  //Remove the ASCII "offset". If input was 1, the ascii code is 49
  int normalInput = input - 48;

  //Chek if input is 0-9. That means, one of the choices were pressed
  if(normalInput >= 0 && normalInput <= 9)
    activePanel = EvaluateChoice(screen, data, activePanel, normalInput);

  //If the input is S, save the current state
  else if(normalInput == 67)
    Save(screen, data, activePanel);

  return activePanel;
}

void Save(Screen *screen, GameData *data, Panel *activePanel){
  
  if(screen == NULL || data == NULL || activePanel == NULL)
    return;

  char **file = malloc(sizeof(char*) * 2);
  file[0] = CreateCopyString(activePanel->id); 
  file[1] = NULL; 

  Item *current = data->firstItem;
  while(current != NULL){
    if(current->owned){
      file[1] = Append(file[1], current->id);

      if(current->next != NULL)
        file[1] = Append(file[1], " ");
    }

    current = current->next;
  }

  WriteAllLines(data->saveFile, file, 2);
  FreeStringArray(file, 2);
}

Panel *EvaluateChoice(Screen *screen, GameData *data, Panel *activePanel, int choiceIndex){

  if(activePanel == NULL || data == NULL)
    return activePanel;

  if(activePanel->choices[choiceIndex]->type == 'P' && choiceIndex < activePanel->choiceCount)
    activePanel = ActivateNewPanel(activePanel, data->firstPanel, activePanel->choices[choiceIndex]->contentID);

  else if(activePanel->choices[choiceIndex]->type == 'I' && choiceIndex < activePanel->choiceCount)
    PickupItem(screen, data->firstItem, activePanel->choices[choiceIndex]->contentID);

  return activePanel;
}

void PickupItem(Screen *screen, Item *first, char *id){

  if(screen == NULL || id == NULL)
    return;

  Item *item = SetItemOwnership(first, id);

  if(item == NULL)
    return;

  DisplayItem(screen, item);
  GetPressedKey();
}

Panel *ActivateNewPanel(Panel *activePanel, Panel *first, char *id){

  if(activePanel == NULL || first == NULL || id == NULL)
    return activePanel;

  activePanel->active = false;
  activePanel = SetActivePanel(first, id);

  if(activePanel == NULL)
    return activePanel;

  return activePanel;
}
