#include "panel.h"

//Returnes the last panel in the list
Panel *GetLastPanel(Panel *first){

  if(first == NULL)
    return NULL;

  Panel *result = first;
  while(result->next != NULL)
    result = result->next;

  return result;
}

//Returnes the panel with a starting flag
Panel *GetStartPanel(Panel *first){

  if(first == NULL)
    return NULL;

  Panel *result = first;
  while(result != NULL){
    if(result->type == start)
      return result;

    result = result->next;
  }

  return NULL;
}

//Returns the active panel
Panel *GetActivePanel(Panel *first){

  if(first == NULL)
    return NULL;

  Panel *result = first;
  while(result != NULL){
    if(result->active)
      return result;

    result = result->next;
  }

  return NULL;
}

//Sets the panel with the matching id as active
Panel *SetActivePanel(Panel *first, char *id){

  if(first == NULL || id == NULL)
    return NULL;

  Panel *result = GetPanel(first, id);

  if(result == NULL)
    return NULL;

  result->active = true;

  return result;
}

//Returnes a panel based on id
Panel *GetPanel(Panel *first, char *id){

  if(id == NULL || first == NULL)
    return NULL;

  Panel *result = first;
  while(result != NULL){
    
    if(strcmp(result->id, id) == 0)
      return result;

    result = result->next;
  }
  
  return NULL;
}

//Creates a new panel and adds it to the list
Panel *CreateAndAddPanel(Panel *first, char *path){

  if(path == NULL)
    return first;

  Panel *new = CreatePanel(path);
  Panel *result = AddPanelNode(first, new);
 
  return result;
}

//Creates a panel from a file
Panel *CreatePanel(char *path){

  //Checks for parameter validity
  if(path == NULL)
    return NULL;

  //Read the file
  int fileLength;
  char **file = ReadAllLines(path, &fileLength);

  //Check if the file is valid or not
  if(fileLength < 2 || file == NULL){
    FreeStringArray(file, fileLength);
    return NULL;
  }

  //If there was less then 2 values in the line skip that line
  Panel *result = (Panel*) malloc(sizeof(Panel));

  //Get data from first line
  int splitLength;
  char **split = Split(file[0], ' ', &splitLength);

  //Check if the first line is in correct format
  if(splitLength <= 1){
    FreeStringArray(file, fileLength);
    FreeStringArray(split, splitLength);
    return NULL;
  }

  //Set basic data
  result->id = CreateCopyString(split[0]);
  result->text = CreateCopyString(file[1]);
  result->active = false;
  result->next = NULL;

  //Set the type of the panel
  if(strcmp(split[1], "start") == 0)
    result->type = start;
  else if(strcmp(split[1], "end") == 0)
    result->type = end;
  else
    result->type = normal;

  //Create the choices
  result->choiceCount = fileLength - 2;
  result->choices = malloc(sizeof(Choice*) * result->choiceCount);
  for(int i = 0; i < result->choiceCount; i++)
    result->choices[i] = CreateChoice(file[i + 2]);

  //Free resources
  FreeStringArray(file, fileLength);
  FreeStringArray(split, splitLength);

  return result;
}

//Adds a panel to the list, always returnes the first node in list
Panel *AddPanelNode(Panel *first, Panel *node){

  //If the new node is NULL, return the first node
  if(node == NULL)
    return first;

  Panel *last = GetLastPanel(first);

  //If the last is NULL, the list is empty, we return the new node as the first node
  if(last == NULL)
    return node;

  //Add the new node to the last one
  last->next = node;
  
  return first;
}

//Creates a choice from a text
Choice *CreateChoice(char *text){

  if(text == NULL)
    return NULL;

  //Split up the text
  Choice *result = (Choice*) malloc(sizeof(Choice));
  int length;
  char **split = Split(text, ' ', &length);

  //Check text format
  if(length <= 2){
    FreeStringArray(split, length);
    return NULL;
  }

  //Set values
  result->type = split[0][0];
  result->contentID = CreateCopyString(split[1]);

  //Crop the first 2 character, the ID and the opening " from the beginning and the closing " from the end
  int cropFromStart = strlen(split[1]) + 4;
  result->text = Crop(text, cropFromStart, 1); 

  //Free the split array
  FreeStringArray(split, length);

  return result;
}

//Free a choice instance
void FreeChoice(Choice *choice){
  
  if(choice == NULL)
    return;

  if(choice->text != NULL)
    free(choice->text);
  if(choice->contentID != NULL)
    free(choice->contentID);

  free(choice);
}

//Free a panel instance
void FreePanel(Panel *panel){

  //Check parameter validity
  if(panel == NULL)
    return;

  //Free the id
  if(panel->id != NULL)
      free(panel->id);

   //Free the text
  if(panel->text != NULL)
      free(panel->text);

  //Free the choices
  if(panel->choiceCount != 0)
    for(int i = 0; i < panel->choiceCount; i++)
      FreeChoice(panel->choices[i]);
  free(panel->choices);

  free(panel);
}

//Free the whole panel list
void FreePanelList(Panel *first){

  if(first == NULL)
    return;

  Panel *tmp;
  Panel *current = first;
  while(current != NULL){
    tmp = current->next;
    FreePanel(current);
    current = tmp;
  }
}
