#include "ext_string.h"

//Counts the occurences of a character in a string
//Returns: an integer containing the result of the operation (number of occurences)
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
//         returns NULL if the parameters were invalid
char **Split(char *text, char splitChar, int *arrayLength){

  //Check for parameter validity
  if(text == NULL || arrayLength == NULL)
    return NULL;

  //Check how many elements the array will have and allocate for that size
  int length = CountChar(text, splitChar) + 1;
  char **result = malloc(sizeof(char*) * length);

  int offset = 0;
  for(int i = 0; i < length; i++){

    //Get the length of the substring without the splitChar
    int subLength = 0;
    while(text[subLength + offset] != splitChar && text[subLength + offset] != '\0')
      subLength++;

    //Create a tmp buffer for the substring
    char *buffer = (char*) malloc(subLength + 1);

    //Copy the substring and add a null terminator
    memcpy(buffer, text + offset, subLength);
    *(buffer + subLength) = '\0';
    //strncat(buffer, "\0", 1);

    //Add the substring to the array and set offset
    result[i] = buffer; 
    offset += subLength + 1;
  }

  free(text);

  //Give back the length of the array
  *arrayLength = length;
  return result;
}

//Adds the given text to the given destination string
//Returns: a pointer to the new string (given string is freed)
//         returns NULL when either parameter is NULL
//         the returned string will only be null-terminated if the given text is null terminated
char* Append(char *dst, const char *text){

  //Check for parameter validity
  if(dst == NULL || text == NULL)
    return NULL;

  //Get length of the parameters and create a total length (+1 byte for the \0)
  int dstLength = strlen(dst);
  int textLength = strlen(text);
  int length = dstLength + textLength + 1;

  //Allocate memory and copy both strings, then free destination
  char *tmp = (char*) malloc(sizeof(char) * length);
  memcpy(tmp, dst, dstLength);
  memcpy(tmp + dstLength, text, textLength + 1);
  free(dst);

  return tmp;
}
