#include "ioHandle.h"

//Displays the title screen for the game
void DrawTitleScreen(Screen *screen, GameData *data){

	//Check for parameter validity
	if(screen == NULL || data == NULL)
		return;

	DrawScreen(screen);

	//Display title
	int verticalCenter = (screen->topWindow.maxY - screen->topWindow.minY) / 2;
	int titlePos = (screen->width - strlen(data->title) - 2) / 2;
	econio_gotoxy(titlePos, verticalCenter);
	for(int i = 0; data->title[i] != '\0'; i++)
		printf("%c", toupper(data->title[i]));

	//Display creator name
	int creatorPos = (screen->width - strlen(data->creator) - 2) / 2;
	econio_gotoxy(creatorPos, verticalCenter + 1);
	puts(data->creator);

	DisplayPressAnyKey(screen);

	ResetCursor();
}

//Waits until the user presses a key. Returns the pressed key.
char GetPressedKey(){

	//Switchs to raw mode, waits for input and returns to normal mode
	econio_rawmode();
	char result = (char) econio_getch();
	econio_normalmode();

	return result;
}

//Displays the screen
void DrawScreen(Screen *screen){

	if(screen == NULL)
		return;

	//Clear the screen and set the colors
	econio_clrscr();
	econio_textbackground(screen->background);
	econio_textcolor(screen->foreground);
	
	//Go trought the edges of the screen
	for(int i = 0; i < screen->height; i++){

		econio_gotoxy(0, i);
		for(int j = 0; j < screen->width; j++){

			if(i == 0 || i == screen->height - 1 || i == screen->split || j == 0 || j == screen->width - 1)
				econio_textbackground(screen->foreground);
			else
				econio_textbackground(screen->background);

			printf(" ");
		}
	}

	//Display the default controls
	econio_gotoxy(2, screen->split);
	econio_textbackground(screen->foreground);
	econio_textcolor(screen->background);
	puts("[q] Quit [s] Save");

	//Reset values
	econio_textbackground(screen->background);
	econio_textcolor(screen->foreground);
	ResetCursor();
}

//Fills a window with spaces
void ClearWindow(Window window){

	//Get the dimensions of the window
	int verticalMove = window.maxY - window.minY;
	int horizontalMove = window.maxX - window.minX;

	//Go trought the window
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
	int offset = 0;
	int verticalMove = window.maxY - window.minY;
	int horizontalMove = window.maxX - window.minX;
	
	//Go trough the window
	for(int i = 0; i < verticalMove && text[index] != '\0'; i++){
		
		//Go to new line
		econio_gotoxy(window.minX, window.minY + i);
		offset = 0;

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
				if((untilSpace + offset) >= leftFromScreen){
					index++;
					break;
				}
			}

			//Break line when operator reached
			if((index == 0 && text[index] == '\\' && text[index + 1] == 'n') || (index > 0 && text[index - 1] != '\\' && text[index] == '\\' && text[index + 1] == 'n')){
				index += 2;
				break;
			}

			//Insert tab when operator reached
			if((index == 0 && text[index] == '\\' && text[index + 1] == 't') || (index > 0 && text[index - 1] != '\\' && text[index] == '\\' && text[index + 1] == 't')){
				printf("    ");
				offset += 4;
				index += 2;
			}

			//If everything is normal, we display the character
			printf("%c", text[index]);
			index++;
		}
	}

	ResetCursor();
}

//Displays the content and choices of a panel
void DisplayPanel(Panel *panel, Screen *screen, Item *firstItem){

	//Check parameter validity
	if(screen == NULL || panel == NULL || firstItem == NULL)
		return;

	//Clear windows
	ClearWindow(screen->topWindow);
	ClearWindow(screen->bottomWindow);

	//Display content
	DisplayText(panel->text, screen->topWindow);

	//If it is the last panel, dont show choices
	if(panel->type == end)
		DisplayPressAnyKey(screen);
	
	//Otherwise, shot choices
	else{
		int offset = 0;
		for(int i = 0; i < panel->choiceCount; i++){

			if(panel->choices[i]->type == 'I' && ItemOwned(firstItem, panel->choices[i]->contentID)){
				offset++;
				continue;
			}

			econio_gotoxy(2, screen->split + 1 + i - offset);
			printf("[%d] ", i);
			puts(panel->choices[i]->text);
		}
	}
	
	ResetCursor();
}

//Displays the GAME OVER title screen
void DisplayEndgame(Screen *screen, Item *firstItem){

	if(screen == NULL || firstItem == NULL)
		return;

	//Clear windows
	ClearWindow(screen->topWindow);
	ClearWindow(screen->bottomWindow);

	//Display GAME OVEr
	int titelPos = (screen->width - 21) / 2;
	econio_gotoxy(titelPos, 2);
	puts("------GAME OVER------");

	//Display item title
	titelPos = (screen->width - 18) / 2;
	econio_gotoxy(titelPos, 3);
	puts("[YOUR INVENTORY]");

	//Displays owned items
	int offset = 0;
	Item *current = firstItem;
	while(current != NULL){
		if(!current->owned){
			current = current->next;
			continue;
		}

		int currentPos = (screen->width - strlen(current->name) - 2) / 2;
		econio_gotoxy(currentPos, 5 + offset);
		puts(current->name);
		offset++;
		current = current->next;
	}

	DisplayPressAnyKey(screen);
}

//Displays the Press Any Key! text in the bottom window
void DisplayPressAnyKey(Screen *screen){

	if(screen == NULL)
		return;

	int promptPos = (screen->width - 16) / 2;
	int verticalCenter = (((screen->bottomWindow.maxY - screen->bottomWindow.minY) + 1) / 2) + screen->split;
	econio_gotoxy(promptPos, verticalCenter);
	puts("Press any key!");

}

//Shows the player what item they got
void DisplayItem(Screen *screen, Item *item){

	//Check for parameter validity
	if(screen == NULL || item == NULL)
		return;

	//Clear windows
	ClearWindow(screen->topWindow);
	ClearWindow(screen->bottomWindow);

	//Display title
	int titlePos = (screen->width - 29) / 2;
	int verticalCenter = (screen->topWindow.maxY - screen->topWindow.minY) / 2;
	econio_gotoxy(titlePos, verticalCenter);
	puts("YOU HAVE PICKED UP AND ITEM:");

	//Display item name
	int namePos = (screen->width - strlen(item->name) - 2) / 2;
	econio_gotoxy(namePos, verticalCenter + 1);
	puts(item->name);

	DisplayPressAnyKey(screen);
	
	ResetCursor();
}

//Clears the whole screen and resets the cursor
void ClearScreen(){

	econio_clrscr();
	econio_gotoxy(0, 0);
}

//Resets cursor position
void ResetCursor(){

	econio_gotoxy(0, 0);
}
