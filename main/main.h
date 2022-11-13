#include "../lib/gameData.h"
#include "../lib/filehandler.h"
/*#include "../lib/linkedlist.c"*/
#include "../lib/ext_string.h"
#include "../lib/debugmalloc.h"
#include "../lib/logger.h"
#include <unistd.h>

void HandleStartingArgs(int argc, char **args);
GameData *HandleRootfile(char *path);
