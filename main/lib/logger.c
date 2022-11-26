#include "logger.h"

//Exits the program with an error message
void ExitError(const char* msg){

  if(msg != NULL)
   printf("%s\n", msg);
  exit(1);
}
