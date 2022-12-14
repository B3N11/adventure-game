#ifndef MAIN_H
#define MAIN_H

#include "lib/gameData.h"
#include "lib/game.h"
#include "lib/filehandler.h"
#include "lib/ext_string.h"
#include "lib/debugmalloc.h"
#include "lib/ioHandle.h"
#include <unistd.h>

#define SCRWIDTH 70
#define SCRHEIGHT 39

void Run(int argc, char **args);
int main(int argc, char **args);
void HandleStartingArgs(int argc, char **args);
GameData *HandleRootfile(char *path);
Screen *CreateScreen();
void HandleSaveFile(char *path, GameData *data);
void ExitError(const char* msg);

#endif
