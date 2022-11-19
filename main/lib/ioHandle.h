#ifndef IOHANDLE_H
#define IOHANDLE_H

#include "econio.h"
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

int CharsUntilNextSpace(const char *text, int index);
void DisplayText(const char *text, Window window);
void ClearWindow(Window window);
void DrawScreen(Screen *screen, int background, int foreground);
char GetPressedKey();

#endif
