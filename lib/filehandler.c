#include "filehandler.h"

//Checks for the existance of a file
//Returns: true if the file exists
//         false if the file doesn't exist or the argument is NULL
bool FileExists(char *file){

  if(file == NULL)
    return false;

  return access(file, F_OK) == 0; 
}

//Reads all lines of a file and stores them in a string array
//Returns: a string array (char **) with each element containing a line of the file
//         returns NULL if the file can't be opened
char **ReadAllLines(const char *path, int *length){

  //Read the content of the file
  char *lines = ReadAllLinesStr(path);

  //Split the read lines
  char **result = Split(lines, '\n', length);

  //Free string
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
  char* crop = Crop(result, 0, 1);
  free(result);

  //Close file
  fclose(fp);
  return crop;
}
