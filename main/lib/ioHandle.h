#ifndef IOHANDLE_H
#define IOHANDLE_H

#include "econio.h"
#include "gameData.h"
#include "ext_string.h"
#include <string.h>
#include <stdio.h>

typedef struct Window{

  int minX;
  int minY;
  int maxX;
  int maxY;
}Window;

typedef struct Screen{

    int width;
    int height;
    int split;
    Window topWindow;
    Window bottomWindow;
}Screen;

void DisplayText(const char *text, Window window);
void ClearWindow(Window window);
void DrawScreen(Screen *screen, int background, int foreground);
char GetPressedKey();
void DrawTitleScreen(Screen *screen, GameData *data, int background, int foreground);
void DisplayPanel(Panel *panel, Screen *screen);
void DisplayItem(Screen *screen, Item *item);
void ClearScreen();
void ResetCursor();

#endif
