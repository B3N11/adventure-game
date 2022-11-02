#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
	//int check = mkdir("./asd", 0777);
	DIR* dir = opendir("./asd");

	if(dir)
		printf("Successfull\n");
	else{
		int check = mkdir("./asd", 0777);
		dir = opendir("./asd");

		if(dir)
			printf("Successfully created");
		else
			printf("Fuck you");
	}
	return 0;
}
