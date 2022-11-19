#include "ioHandle.h"

//Displays the title screen for the game
void DrawTitleScreen(Screen *screen, GameData *data, int background, int foreground){

	if(screen == NULL)
		return;

	DrawScreen(screen, background, foreground);

	//Display title
	int verticalCenter = (screen->topWindow.maxY - screen->topWindow.minY) / 2;
	int titlePos = (screen->width - strlen(data->title) - 2) / 2;
	econio_gotoxy(titlePos, verticalCenter);
	puts(data->title);

	int creatorPos = (screen->width - strlen(data->creator) - 2) / 2;
	econio_gotoxy(creatorPos, verticalCenter + 1);
	puts(data->creator);

	int promptPos = (screen->width - 17) / 2;
	int botVerticalCenter = (screen->bottomWindow.maxY - screen->bottomWindow.minY) / 2 + 1;
	econio_gotoxy(promptPos,screen->split + botVerticalCenter);
	puts("Press any key!");

	ResetCursor();
}

//Waits until the user presses a key. Returns the pressed key.
char GetPressedKey(){

	econio_rawmode();
	char result = (char) econio_getch();
	econio_normalmode();

	return result;
}

void DrawScreen(Screen *screen, int background, int foreground){

	if(screen == NULL)
		return;

	econio_clrscr();
	econio_textbackground(background);
	econio_textcolor(foreground);
	
	for(int i = 0; i < screen->height; i++){

		econio_gotoxy(0, i);
		for(int j = 0; j < screen->width; j++){

			if(i == 0 || i == screen->height - 1 || i == screen->split || j == 0 || j == screen->width - 1)
				econio_textbackground(foreground);
			else
				econio_textbackground(background);

			printf(" ");
		}
	}

	econio_textbackground(background);
	econio_textcolor(foreground);
	ResetCursor();
}

void ClearWindow(Window window){

	int verticalMove = window.maxY - window.minY;
	int horizontalMove = window.maxX - window.minX;

	for(int i = 0; i < verticalMove; i++){
		econio_gotoxy(window.minX, window.minY + i);
		for(int j = 0; j < horizontalMove; j++)
			printf(" ");
	}

	ResetCursor();
}

//Displays a text in the given window
void DisplayText(const char *text, Window window){

	//Check for parameter validity
	if(text == NULL)
		return;

	//Calculate how many steps it takes to walk trought the whole window
	int index = 0;
	int verticalMove = window.maxY - window.minY;
	int horizontalMove = window.maxX - window.minX;
	
	//Go trough the window
	for(int i = 0; i < verticalMove && text[index] != '\0'; i++){
		
		//Go to new line
		econio_gotoxy(window.minX, window.minY + i);

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

	ResetCursor();
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

void ResetCursor(){

	econio_gotoxy(0, 0);
}
