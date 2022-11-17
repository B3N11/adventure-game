#include <stdio.h>
#include <string.h>
#include "../main/lib/econio.h"

typedef struct Coordinates{

	int minx;
	int miny;
	int maxx;
	int maxy;
}Coordinates;

void DrawScreen(int height, int width, int background, int foreground){

	econio_clrscr();
	econio_textbackground(background);
	econio_textcolor(foreground);
	
	int splitPlace = height - (0.2 * height);
	for(int i = 0; i < height; i++){

		printf("*");
		for(int j = 1; j < width - 1; j++){
			if(i == 0 || i == height - 1 || i == splitPlace)
				printf("*");
			else
				printf(" ");
		}
		printf("*\n");
	}
}

int CharsUntilNextSpace(const char *text, int index){

	if(text == NULL || index >= strlen(text))
		return -1;

	int result = 0;
	for(int i = index + 1; text[i] != '\0'; i++){
		if(text[i] == ' ')
			return result;
		result++;
	}

	return result;
}

//Displays a text in the given window
void DisplayText(const char *text,Coordinates window){

	//Check for parameter validity
	if(text == NULL)
		return;

	//Calculate how many steps it takes to walk trought the whole window
	int index = 0;
	int verticalMove = window.maxy - window.miny;
	int horizontalMove = window.maxx - window.minx;
	
	//Go trough the window
	for(int i = 0; i < verticalMove && text[index] != '\0'; i++){
		
		//Go to new line
		econio_gotoxy(window.minx, window.miny + i);

		//Go trough the line and display every character
		for(int j = 0; j < horizontalMove && text[index] != '\0'; j++){

			//Remove white spaces from the start of the line
			if(text[index] == ' ' && j == 0){
				index++;
				j = -1;
				continue;
			}

			//If the next word couldn't be displayed in a whole, go to new line.
			if(text[index] == ' '){

				//Calculate how long the next word is and how far is the end of the line
				int untilSpace = CharsUntilNextSpace(text, index);
				int leftFromScreen = horizontalMove - j;

				//If the word is longer than the space left until the end of line, we break out
				if(untilSpace >= leftFromScreen){
					index++;
					break;
				}
			}

			//If everything is normal, we display the character
			printf("%c", text[index]);
			index++;
		}
	}
}


int main(){

	int height = 30;
	int widht = 70;
	DrawScreen(height, widht, COL_BLACK, COL_LIGHTGREEN);

	Coordinates data = {.minx=2, .miny=1, .maxx=68, .maxy=28};
	DisplayText("Hello there fellow kids! How is it going out there? Are the otherthing big kids as scary as I am? I hope not, altough what I'm      saying is completely improvised.", data);

	/*econio_rawmode();*/
	/*econio_gotoxy(50, 2);*/

	/*while(true)*/
		/*printf("%c", (char)econio_getch());*/

	return 0;
}
