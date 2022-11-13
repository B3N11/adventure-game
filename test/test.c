#include "../lib/filehandler.h"
#include <stdio.h>

int main(void){

	int length;
	char **result = ReadAllLines("test.txt", &length);

	for(int i = 0; i < length; i++)
		puts(result[i]);

	for(int i = 0; i < length; i++)
		free(result[i]);

	free(result);
	return 0;
}
