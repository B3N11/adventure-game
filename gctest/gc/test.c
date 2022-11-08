#include <stdio.h>
#include <string.h>
#include "garbageCollector.h"

int main(void){

  char *text = malloc_gc(sizeof(char) * 10);
  strcpy(text, "123456789"); 
  puts(text);

  RunGC();
  return 0;
}
