#include "filehandler.h"
#include "ext_string.h"
#include <stdbool.h> 

typedef struct Choice{

    char type;
    char *text;
    char *contentID;
}Choice;

typedef struct Panel{

    char *id;
    char *type;
    char *text;
    int choiceCount;
    Choice **choices;
    struct Panel *next;
}Panel;

Panel *GetLastPanel(Panel *first);
Panel *CreateAndAddPanel(Panel *first, char *path);
static Panel *CreatePanel(char *path);
Panel *AddPanelNode(Panel *first, Panel *node);
static void FreePanel(Panel *item);
void FreePanelList(Panel *first);
static Choice *CreateChoice(char *text);
static void FreeChoice(Choice *choice);