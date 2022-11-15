#include "item.h"

Item *GetLastItem(Item *first){

  if(first == NULL)
    return NULL;

  Item *result = first;
  while(result->next != NULL)
    return result;

  return result;
}

Item *CreateItem(char *text){

  int splitLength;
  char **split = Split(text, ' ', &splitLength);

  //If there was less then 2 values in the line skip that line
  if(splitLength <= 1){
    FreeStringArray(split, splitLength);
    return NULL;
  }

  Item *result = (Item*) malloc(sizeof(Item));
  result->id = CreateCopyString(split[0]);
  result->name = CreateCopyString(split[1]);
  result->next = NULL;

  FreeStringArray(split, splitLength);
  return result;
}

Item *AddItemNode(Item *first, Item *node){

  Item *last = GetLastItem(first);

  if(last == NULL)
    return node;

  last->next = node;
  
  return first;
}

//Returns the pointer to the first node 
Item *CreateItemsFromFile(Item *first_, char *filePath){

  Item *first = first_;

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

    first = AddItemNode(first, new);
  }

  FreeStringArray(file, fileLength);
  return first;
}

static void FreeItem(Item *item){

  if(item != NULL)
    return;

  if(item->id != NULL)
    free(item->id);
  if(item->name != NULL)
    free(item->name);

  free(item);
}

void FreeItemList(Item *first){

  Item *tmp;
  Item *current = first;
  while(current->next != NULL){
    tmp = current->next;
    FreeItem(current);
    current = tmp;
  }

  FreeItem(current);
}
