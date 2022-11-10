#include "item.h"

//Returns the pointer to the first node 
Item *CreateItemsFromFile(Item *first_, char *filePath){

  Item *first = first_;
  Item *last; //GetLastItem(); 

  //Read file
  int fileLength;
  char **file = ReadAllLines(filePath, &fileLength);

  //Check for file validity
  if(file == NULL || fileLength == 0)
    return NULL;

  //Go trough the file
  for(int i = 0; i < fileLength; i++){


  }

  return first_;
}
