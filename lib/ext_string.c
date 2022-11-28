#include "ext_string.h"

//Counts the characters until next space
int CharsUntilNextSpace(const char *text, int index){

  //Check parameter validity
	if(text == NULL || index >= strlen(text))
		return -1;

  //Iterate trough the text from the index until we find a space or \0
	int result = 0;
	for(int i = index; text[i] != '\0'; i++){
		if(text[i] == ' ')
			return result;
		result++;
	}

	return result;
}

//Creates a new string and copies the data from the src string to the new one. Src must be null-terminated
//Returns: a string (char*) with the copied data
//         returns NULL if src is NULL or its length is 0 (excluding null-terminator)
char *CreateCopyString(char *src){

  //Check for src validity
  if(src == NULL)
    return NULL;

  //Get the length of the source string
  int length = strlen(src) + 1;

  //Check if there is valid data to copy
  if(length == 0)
    return NULL;

  //Allocate memory and copy data
  char *result = (char *) malloc(length);
  strcpy(result, src);

  return result;
}

//Frees an array of strings. Array cannot be NULL 
void FreeStringArray(char **array, int length){

  //Check for parameter validity
  if(array == NULL)
    return;

  //Free every element if they are not NULL
  for(int i = 0; i < length; i++)
    if(array[i] != NULL)
      free(array[i]);
  free(array);
}

//Takes off the given amount of characters from the front and back of the given string
//Returns: a new string that contains the cropped text. The original data is not freed
//         returns NULL if the given string is NULL
//         if the sum(front, back) is larger than or equal to the lenght of the string, the original text is returned and it is not freed
char *Crop(char *text, unsigned int front, unsigned int back){

  //Check for parameter validity
  if(text == NULL)
    return NULL;

  //Get length of the text
  int length = strlen(text);

  //Check if cropping even makes sense
  if((front + back) >= length)
    return text;

  //Allocate memory
  int totalLength = length - (front + back) + 1;
  char *result = (char *) malloc(totalLength);

  //Copy memory
  memcpy(result, text+front, (totalLength - 1));
  *(result + totalLength - 1) = '\0';

  return result;
}

//Counts the occurences of a character in a string
//Returns: an integer containing the result of the operation (number of occurences)
int CountChar(const char *text, char find){

  //Check for parameter validity
  if(text == NULL)
    return -1;

  int result = 0;

  //Iterate trough the text
  for(int i = 0; text[i] != '\0'; i++)
    if(text[i] == find)
      result++;

  return result;
}

//Splits the given string into substrings separated by the given character
//Returns: a string array (char**) where each element is a substring separated by the given character
//         needs the address of an integer to store the length of the array
//         returns NULL if the parameters were invalid
char **Split(const char *text, char splitChar, int *arrayLength){

  //Check for parameter validity
  if(text == NULL || arrayLength == NULL)
    return NULL;

  //Check how many elements the array will have and allocate for that size
  int length = CountChar(text, splitChar) + 1;
  char **result = malloc(sizeof(char*) * length);

  //Offset stores how far we are from the beginning of the text
  int offset = 0;

  //Go trough the text
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

  //Give back the length of the array
  *arrayLength = length;
  return result;
}

//Adds the given text to the given destination string and returns a new string with those values. Destination string is freed
//Returns: a pointer to the new string (given string is freed)
//         returns NULL when either parameter is NULL
//         the returned string will only be null-terminated if the given text is null terminated
char* Append(char *dst, const char *text){

  //Check for parameter validity
  if(text == NULL)
    return NULL;

  //Get length of the parameters and create a total length (+1 byte for the \0)
  int dstLength = dst == NULL ? 0 : strlen(dst);
  int textLength = strlen(text);
  int length = dstLength + textLength + 1;

  //Allocate memory and copy both strings, then free destination
  char *tmp = (char*) malloc(sizeof(char) * length);
  memcpy(tmp, dst, dstLength);
  memcpy(tmp + dstLength, text, textLength + 1);
  free(dst);

  return tmp;
}
