#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

	FILE *fp = fopen("asd.txt", "w");

	char *asd = malloc(13);
	strcpy(asd, "Hello there!");
	fprintf(fp, "%s", asd);
	fclose(fp);
	free(asd);
}
