#ifndef MAIN_H
#define MAIN_H

#include "lib/gameData.h"
#include "lib/game.h"
#include "lib/filehandler.h"
#include "lib/ext_string.h"
#include "lib/debugmalloc.h"
#include "lib/logger.h"
#include "lib/ioHandle.h"
#include <unistd.h>

void Run(int argc, char **args);
int main(int argc, char **args);
void HandleStartingArgs(int argc, char **args);
GameData *HandleRootfile(char *path);
Screen *CreateScreen();

#endif
