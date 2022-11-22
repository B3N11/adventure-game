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

	DisplayPressAnyKey(screen);

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
				int untilSpace = CharsUntilNextSpace(text, index + 1);
				int leftFromScreen = horizontalMove - j;

				//If the word is longer than the space left until the end of line, we break out
				if(untilSpace >= leftFromScreen){
					index++;
					break;
				}
			}

			//Break line when operator reached
			if((index == 0 && text[index] == '\\' && text[index + 1] == 'n') || (index > 0 && text[index - 1] != '\\' && text[index] == '\\' && text[index + 1] == 'n')){
				index += 2;
				break;
			}

			//If everything is normal, we display the character
			printf("%c", text[index]);
			index++;
		}
	}

	ResetCursor();
}

void DisplayPanel(Panel *panel, Screen *screen, bool endpanel){

	if(screen == NULL || panel == NULL)
		return;

	ClearWindow(screen->topWindow);
	ClearWindow(screen->bottomWindow);

	DisplayText(panel->text, screen->topWindow);

	if(endpanel)
		DisplayPressAnyKey(screen);
	
	else{
		for(int i = 0; i < panel->choiceCount; i++){

			econio_gotoxy(2, screen->split + 1 + i);
			printf("[%d] ", i);
			puts(panel->choices[i]->text);
		}
	}
	
	ResetCursor();
}

void DisplayEndgame(Screen *screen, Item *firstItem){

	ClearWindow(screen->topWindow);
	ClearWindow(screen->bottomWindow);

	int titelPos = (screen->width -11) / 2;
	econio_gotoxy(titelPos, 2);
	puts("GAME OVER");


	titelPos = (screen->width - 31) / 2;
	econio_gotoxy(titelPos, 3);
	puts("YOU HAVE GADERED THESE ITEMS:");

	int offset = 0;
	Item *current = firstItem;
	while(current != NULL){
		if(!current->owned){
			current = current->next;
			continue;
		}

		int currentPos = (screen->width - strlen(current->name) - 2) / 2;
		econio_gotoxy(currentPos, 4 + offset);
		puts(current->name);
		offset++;
		current = current->next;
	}

	DisplayPressAnyKey(screen);
}

void DisplayPressAnyKey(Screen *screen){

	int promptPos = (screen->width - 16) / 2;
	int verticalCenter = (((screen->bottomWindow.maxY - screen->bottomWindow.minY) + 1) / 2) + screen->split;
	econio_gotoxy(promptPos, verticalCenter);
	puts("Press any key!");

}

void DisplayItem(Screen *screen, Item *item){

	if(screen == NULL || item == NULL)
		return;

	ClearWindow(screen->topWindow);
	ClearWindow(screen->bottomWindow);

	int titlePos = (screen->width - 29) / 2;
	int verticalCenter = (screen->topWindow.maxY - screen->topWindow.minY) / 2;
	econio_gotoxy(titlePos, verticalCenter);
	puts("YOU HAVE PICKED UP AND ITEM:");

	int namePos = (screen->width - strlen(item->name) - 2) / 2;
	econio_gotoxy(namePos, verticalCenter + 1);
	puts(item->name);

	DisplayPressAnyKey(screen);
	
	ResetCursor();
}

void ClearScreen(){
	econio_clrscr();
	econio_gotoxy(0, 0);
}

void ResetCursor(){

	econio_gotoxy(0, 0);
}
