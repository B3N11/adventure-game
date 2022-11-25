#include "logger.h"

//Exits the program with an error message
void ExitError(const char* msg){

  printf("%s\n", msg);
  exit(1);
}
