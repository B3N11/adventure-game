#include <stdio.h>
#include "mystringlib.h"
#include "debugmalloc.h"
#include <string.h>

char* Append(char *dst, const char *text){

  if(dst == NULL || text == NULL)
    return NULL;

  int dstLength = strlen(dst);
  int textLength = strlen(text);
  int length = dstLength + textLength + 1;

  char *tmp = (char*) malloc(sizeof(char) * length);
  memcpy(tmp, dst, dstLength);
  memcpy(tmp + dstLength, text, textLength + 1);
  free(dst);

  return tmp;
}

String **ReadAllLines(const char *path){

  FILE *fp = fopen(path, "r");

  if(fp == NULL)
    return NULL;

  int length = 0;
  char buffer[1024];
  char *current = (char*) malloc(sizeof(char) * 1);
  strcpy(current, "\0");

  //Read into buffer
  while(fgets(buffer, sizeof(buffer), fp) != NULL)
    current = Append(current, buffer);

  puts(current);
  fclose(fp);
  free(current);
  return NULL;
}

int main(void){

  String **array = ReadAllLines("test.txt");
  if(array == NULL)
    printf("Error!");
  /*String **hey = malloc(10 * sizeof(String *));*/

  /*for(int i = 0; i < 10; i++){*/
    /*hey[i] = CreateString("Anyád");*/
    /*puts(hey[i]->data);*/
    /*//free(hey[i]);*/
  /*}*/
  /*free(hey);*/
  return 0;
}
