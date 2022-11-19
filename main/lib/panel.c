#include "panel.h"

Panel *GetLastPanel(Panel *first){

  if(first == NULL)
    return NULL;

  Panel *result = first;
  while(result->next != NULL)
    result = result->next;

  return result;
}

Panel *GetPanel(Panel *first, char *id){

  if(id == NULL || first == NULL)
    return NULL;

  Panel *result = first;
  while(result->next != NULL){
    
    if(strcmp(result->id, id) == 0)
      return result;

    result = result->next;
  }
  
  return NULL;
}

Panel *CreateAndAddPanel(Panel *first, char *path){
  Panel *new = CreatePanel(path);
  Panel *result = AddPanelNode(first, new);
 
  return result;
}

static Panel *CreatePanel(char *path){

  //Checks for parameter validity
  if(path == NULL)
    return NULL;

  int fileLength;
  char **file = ReadAllLines(path, &fileLength);

  if(fileLength <= 2 || file == NULL){
    FreeStringArray(file, fileLength);
    return NULL;
  }

  //If there was less then 2 values in the line skip that line
  Panel *result = (Panel*) malloc(sizeof(Panel));

  //Get data from first line
  int splitLength;
  char **split = Split(file[0], ' ', &splitLength);

  if(splitLength <= 1){
    FreeStringArray(split, splitLength);
    return NULL;
  }

  result->id = CreateCopyString(split[0]);
  result->type = CreateCopyString(split[1]);
  result->text = CreateCopyString(file[1]);
  result->active = false;
  result->next = NULL;

  result->choiceCount = fileLength - 2;
  result->choices = malloc(sizeof(Choice*) * result->choiceCount);
  for(int i = 0; i < result->choiceCount; i++)
    result->choices[i] = CreateChoice(file[i + 2]);

  FreeStringArray(file, fileLength);
  FreeStringArray(split, splitLength);

  return result;
}

Panel *AddPanelNode(Panel *first, Panel *node){

  Panel *last = GetLastPanel(first);

  if(last == NULL)
    return node;

  last->next = node;
  
  return first;
}

static Choice *CreateChoice(char *text){

  if(text == NULL)
    return NULL;

  Choice *result = (Choice*) malloc(sizeof(Choice));
  int length;
  char **split = Split(text, ' ', &length);

  if(length <= 2){
    FreeStringArray(split, length);
    return NULL;
  }

  result->type = split[0][0];
  result->contentID = CreateCopyString(split[1]);

  //Crop the first 2 character, the ID and the opening " from the beginning and the closing " from the end
  int cropFromStart = strlen(split[1]) + 4;
  result->text = Crop(text, cropFromStart, 1); 

  //Free the split array
  FreeStringArray(split, length);

  return result;
}

static void FreeChoice(Choice *choice){
  
  if(choice == NULL)
    return;

  if(choice->text != NULL)
    free(choice->text);
  if(choice->contentID != NULL)
    free(choice->contentID);

  free(choice);
}

static void FreePanel(Panel *panel){

  //Check parameter validity
  if(panel == NULL)
    return;

  //Free the id
  if(panel->id != NULL)
      free(panel->id);

  //Free the type
  if(panel->type != NULL)
      free(panel->type);

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

void FreePanelList(Panel *first){

  Panel *tmp;
  Panel *current = first;
  while(current->next != NULL){
    tmp = current->next;
    FreePanel(current);
    current = tmp;
  }

  FreePanel(current);
}
