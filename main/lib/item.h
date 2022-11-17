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
Item *CreateItemsFromFile(Item *first_, char *filePath);
static void FreeItem(Item *item);
void FreeItemList(Item *first);
