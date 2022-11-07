#include "filehandler.h"

//Reads all lines of a file and stores them in a string array
//Returns: a string array (char **) with each element containing a line of the file
//         returns NULL if the file can't be opened
char **ReadAllLines(const char *path, int *length){

  //Open file in read mode
  FILE *fp = fopen(path, "r");

  //Check for file validity
  if(fp == NULL)
    return NULL;

  //Create tmp buffer to read the file content into
  char buffer[1024];

  //Allocate memory for storing string
  char *lines = (char*) malloc(sizeof(char) * 1);
  *lines = '\0';
  //strcpy(result, "\0");

  //Read into buffer, copy that into result until EOF is reached
  while(fgets(buffer, sizeof(buffer), fp) != NULL)
    lines = Append(lines, buffer);

  //Crop down the empty line from the end of the file
  lines = Crop(lines, 0, 1);

  //Split the read lines
  char **result = Split(lines, '\n', length);

  //Release resources
  fclose(fp);
  free(lines);

  return result;
}

//Reads all lines of a file and stores them in a string
//Returns: a string with the content of a file
//         returns NULL if the file can't be opened
char *ReadAllLinesStr(const char *path){

  //Open file in read mode
  FILE *fp = fopen(path, "r");

  //Check for file validity
  if(fp == NULL)
    return NULL;

  //Create tmp buffer to read the file content into
  char buffer[1024];

  //Allocate memory for storing string
  char *result = (char*) malloc(sizeof(char) * 1);
  *result = '\0';
  //strcpy(result, "\0");

  //Read into buffer, copy that into result until EOF is reached
  while(fgets(buffer, sizeof(buffer), fp) != NULL)
    result = Append(result, buffer);

  //Crop down the empty line from the end of the file
  result = Crop(result, 0, 1);

  //Close file
  fclose(fp);
  return result;
}
