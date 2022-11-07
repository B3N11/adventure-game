#include <stdio.h>
#include "../lib/debugmalloc.h"
#include <string.h>

char* Test(char *asd){

	char *tmp = (char*) malloc(5);
	strcpy(tmp, "1111");

	return tmp;
}

int main(void){

	char *asd = NULL;
	asd = Test(asd);
	free(asd);

	return 0;
}
