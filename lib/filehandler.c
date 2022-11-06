#include <stdio.h>
#include <string.h>
#include "debugmalloc.h"

int CountChar(const char *text, char find){

  int result = 0;

  for(int i = 0; text[i] != '\0'; i++)
    if(text[i] == find)
      result++;

  return result;
}

//Splits the given string into substrings separated by the given character
//Returns: a string array (char**) where each element is a substring separated by the given character
//         needs the address of an integer to store the length of the array
char **Split(const char *text, char splitChar, int *arrayLength){

  //Check for parameter validity
  if(text == NULL || arrayLength == NULL)
    return NULL;

  //Check how many elements the array will have and allocate for that size
  int length = CountChar(text, splitChar) + 1;
  char **result = malloc(sizeof(char*) * length);

  int offset = 0;
  for(int i = 0; i < length; i++){

    int lineLength = 0;
    while(text[lineLength + offset] != splitChar && text[lineLength + offset] != '\0')
      lineLength++;

    char *buffer = (char*) malloc(lineLength + 1);

    memcpy(buffer, text + offset, lineLength);
    *(buffer + lineLength) = '\0';
    //strncat(buffer, "\0", 1);

    result[i] = buffer; 
    offset += lineLength + 1;
  }

  *arrayLength = length;
  return result;
}

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

char *ReadAllLines(const char *path){

  FILE *fp = fopen(path, "r");

  if(fp == NULL)
    return NULL;

  int index = 0;
  char buffer[1024];
  char *current = (char*) malloc(sizeof(char) * 1);
  strcpy(current, "\0");

  //Read into buffer
  while(fgets(buffer, sizeof(buffer), fp) != NULL)
    current = Append(current, buffer);

  fclose(fp);
  return current;
}

int main(void){

  char *result = ReadAllLines("test.txt");

  int length;
  char **array= Split(result, '\n', &length);

  printf("Array length: %d\n", length);
  for(int i = 0; i < length; i++){
    puts(array[i]);
    free(array[i]);
  }

  free(array);
  free(result);
  /*String **hey = malloc(10 * sizeof(String *));*/

  /*for(int i = 0; i < 10; i++){*/
    /*hey[i] = CreateString("Anyád");*/
    /*puts(hey[i]->data);*/
    /*//free(hey[i]);*/
  /*}*/
  /*free(hey);*/
  return 0;
}
