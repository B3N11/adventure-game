#include "filehandler.h"

//Checks for the existance of a file
//Returns: true if the file exists
//         false if the file doesn't exist or the argument is NULL
bool FileExists(char *file){

  //Check for parameter validity
  if(file == NULL)
    return false;

  return access(file, F_OK) == 0; 
}

//Writes all elements of a string array into a file (each element into a new line)
void WriteAllLines(const char *path, char **array, int length){

  //Check for parameter validity
  if(path == NULL || array == NULL || length == 0)
    return;

  //Open file
  FILE *fp = fopen(path, "w");

  //Check if the opening was successfull
  if(fp == NULL)
    return;

  //If the element is not NULL, write it into the file
  for(int i = 0; i < length; i++)
    if(array[i] != NULL)
      fprintf(fp, "%s\n", array[i]);

  fclose(fp);
}

//Reads all lines of a file and stores them in a string array
//Returns: a string array (char **) with each element containing a line of the file
//         returns NULL if the file can't be opened
char **ReadAllLines(const char *path, int *length){

  //Read the content of the file
  char *lines = ReadAllLinesStr(path);

  //Check if the reading was successfull
  if(lines == NULL)
    return NULL;

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

  if(path == NULL)
    return NULL;

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

  //If empty file
  if(strlen(result) == 0){
    free(result);
    fclose(fp);
    return NULL;
  }

  //Crop down the empty line from the end of the file
  if(result[strlen(result) - 1] == '\n'){
    char* crop = Crop(result, 0, 1);
    free(result);
    fclose(fp);
    return crop;
  }
  
  //Close file
  fclose(fp);
  return result;
}
