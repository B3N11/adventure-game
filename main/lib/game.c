#include "game.h"

//Runs the main loop of the game
void RunGame(Screen *screen, GameData *data){

  //Check for parameter validity
  if(screen == NULL || data == NULL)
    return;

  //Clear windows
  Panel *activePanel;
  ClearWindow(screen->topWindow);
  ClearWindow(screen->bottomWindow);

  //Get the active panel
  activePanel = GetActivePanel(data->firstPanel);

  //If there was no save before, the starting panel will be the active panel
  if(activePanel == NULL){
    activePanel = GetStartPanel(data->firstPanel);
    activePanel->active = true;
  }

  //If there is no starting panel, return completely
  if(activePanel == NULL)
    return;

  //Display the first panel and wait for input
  DisplayPanel(activePanel, screen, data->firstItem, false); 
  char input = GetPressedKey();

  //Run the game while player doesn't quit
  while(input != 'q'){

    //Progress in the game based on the input of the player
    activePanel = HandleInput(screen, data, activePanel, input);

    //If someone went wrong, close the game
    if(activePanel == NULL)
      return;

    //If the panel is an end panel, end the game
    if(strcmp(activePanel->type, "end") == 0){
      EndGame(screen, data, activePanel);
      return;
    }

    //If the current panel is normal or starting panel, progress with the game
    DisplayPanel(activePanel, screen, data->firstItem, false);
    input = GetPressedKey();
  }
}

//Ends the game when END panel is reached
void EndGame(Screen *screen, GameData *data, Panel *activePanel){

  //Check for parameter validity
  if(screen == NULL || data == NULL || activePanel == NULL)
    return;

  //First, display the panel
  DisplayPanel(activePanel, screen, data->firstItem, true);
  GetPressedKey();

  //Then, display the end screen
  DisplayEndgame(screen, data->firstItem);
  GetPressedKey();
}

//Progress in the game based on the input of the player
Panel *HandleInput(Screen *screen, GameData *data, Panel *activePanel, char input){

  if(data == NULL || activePanel == NULL)
    return activePanel;

  //Remove the ASCII "offset". If input was 1, the ascii code is 49
  int normalInput = input - 48;

  //Chek if input is 0-9. That means, one of the choices were pressed
  if(normalInput >= 0 && normalInput < activePanel->choiceCount)
    activePanel = EvaluateChoice(screen, data, activePanel, normalInput);

  //If the input is S, save the current state
  else if(input == 's')
    Save(screen, data, activePanel);

  return activePanel;
}

//Saves the current state of the game
void Save(Screen *screen, GameData *data, Panel *activePanel){
  
  //Check for parameter validity
  if(screen == NULL || data == NULL || activePanel == NULL)
    return;

  //Allocate memory for the string array that will contain the data
  char **file = malloc(sizeof(char*) * 2);

  //First line will be the id of activePanel
  file[0] = CreateCopyString(activePanel->id); 
  file[1] = NULL; 

  //Set the second line by writing every owned item id separated by spaces
  Item *current = data->firstItem;
  while(current != NULL){

    //If the current item is owned, add it to the current line and separate it with spaces
    if(current->owned){
      file[1] = Append(file[1], current->id);
      file[1] = Append(file[1], " ");
    }

    current = current->next;
  }

  //Save into file and free resources
  WriteAllLines(data->saveFile, file, 2);
  FreeStringArray(file, 2);
}

//Progresses in game based on the type of the choice the player made
Panel *EvaluateChoice(Screen *screen, GameData *data, Panel *activePanel, int choiceIndex){

  //Check for parameter validity
  if(activePanel == NULL || data == NULL || screen == NULL)
    return activePanel;

  //Checks if the input number is bigger than the count of choices on this panel
  if(choiceIndex >= activePanel->choiceCount)
    return activePanel;

  //If the choice type is a panel, move to that panel 
  if(activePanel->choices[choiceIndex]->type == 'P')
    activePanel = ActivateNewPanel(activePanel, data->firstPanel, activePanel->choices[choiceIndex]->contentID);

  //If the choice type is an item, pick up the item
  else if(activePanel->choices[choiceIndex]->type == 'I')
    PickupItem(screen, data->firstItem, activePanel->choices[choiceIndex]->contentID);

  return activePanel;
}

//Sets an item as owned and displays it
void PickupItem(Screen *screen, Item *first, char *id){

  //Check for parameter validity and if the Item is owned already, dont pick it up
  if(screen == NULL || id == NULL || first == NULL || ItemOwned(first, id))
    return;

  //Set item to owned
  Item *item = SetItemOwnership(first, id, true);

  //If the item is not found, return without displaying
  if(item == NULL)
    return;

  //Displays the item and waits for input
  DisplayItem(screen, item);
  GetPressedKey();
}

//Sets the panel with "id" as active and the current panel as inactive
Panel *ActivateNewPanel(Panel *activePanel, Panel *first, char *id){

  //Check for paramater validity
  if(activePanel == NULL || first == NULL || id == NULL)
    return activePanel;

  //Deactivate current panel and set the new one as active
  activePanel->active = false;
  activePanel = SetActivePanel(first, id);

  return activePanel;
}
