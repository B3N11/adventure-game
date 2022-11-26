#include "item.h"

//Returns the last item in the list
Item *GetLastItem(Item *first){

  if(first == NULL)
    return NULL;

  Item *result = first;
  while(result->next != NULL)
    result = result->next;
  
  return result;
}

//Checks if an item is owned
bool ItemOwned(Item *first, char *id){
  
  if(first == NULL || id == NULL)
    return false;

  Item* current = first;
  while(current != NULL){

    if(strcmp(current->id, id) == 0 && current->owned)
      return true;

    current = current->next;
  }

  return false;
}

//Returnes an item with the matching id
Item *GetItem(Item *first, char *id){

  if(first == NULL || id == NULL)
    return NULL;

  Item *result = first;
  while(result != NULL){
    if(strcmp(result->id, id) == 0)
      return result;

    result = result->next;
  }
  
  return NULL;
}

//Owns or disowns an item
Item *SetItemOwnership(Item *first, char *id, bool owned){

  if(first == NULL || id == NULL)
    return NULL;

  Item *result = GetItem(first, id);

  if(result == NULL)
    return NULL;

  result->owned = owned;

  return result;
}

//Creates an item from a text
Item *CreateItem(char *text){

  if(text == NULL)
    return NULL;

  int idLenght = CharsUntilNextSpace(text, 0);
  int nameLength = strlen(text) - idLenght - 1;

  Item *result = (Item*) malloc(sizeof(Item));
  result->id = Crop(text, 0, nameLength + 1);
  result->name = Crop(text, idLenght + 2, 1);
  result->next = NULL;
  result->owned = false;

  return result;
}

//Adds a new item to the list
Item *AddItemNode(Item *first, Item *node){

  if(node == NULL)
    return first;

  Item *last = GetLastItem(first);

  if(last == NULL)
    return node;

  last->next = node;
  
  return first;
}

//Returns the pointer to the first node 
Item *CreateItemsFromFile(Item *first, char *filePath){

  Item *result = first;

  //Read file
  int fileLength;
  char **file = ReadAllLines(filePath, &fileLength);

  //Check for file validity
  if(file == NULL)
    return NULL;

  //POTENTIAL ERROR (an empty line remains in file)
  if(fileLength == 0){
    free(file);
    return NULL;
  }

  //Go trough the file
  for(int i = 0; i < fileLength; i++){

    Item *new = CreateItem(file[i]);

    //If data was invalid
    if(new ==  NULL)
      continue;

    result = AddItemNode(result, new);
  }

  FreeStringArray(file, fileLength);
  return result;
}

//Frees an item from memory
void FreeItem(Item *item){

  if(item == NULL)
    return;

  if(item->id != NULL)
    free(item->id);
  if(item->name != NULL)
    free(item->name);

  free(item);
}

//Frees the whole list of items
void FreeItemList(Item *first){

  if(first == NULL)
    return;
  
  Item *tmp;
  Item *current = first;
  while(current != NULL){
    tmp = current->next;
    FreeItem(current);
    current = tmp;
  }
}
