#ifndef ITEM_H
#define ITEM_H

#include "filehandler.h"
#include "ext_string.h"
#include <stdbool.h> 

typedef struct Item{

    char *id;
    char *name;
    bool owned;
    struct Item *next;
}Item;

Item *GetLastItem(Item *first);
Item *CreateItem(char *text);
Item *AddItemNode(Item *first, Item *node);
Item *CreateItemsFromFile(Item *first, char *filePath);
void FreeItem(Item *item);
void FreeItemList(Item *first);
Item *SetItemOwnership(Item *first, char *id, bool owned);
Item *GetItem(Item *first, char *id);
bool ItemOwned(Item *first, char *id);

#endif
