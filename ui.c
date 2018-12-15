#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <termios.h> // Terminal attributes
#include <unistd.h> // For STDIN_FILENO
#include <sys/ioctl.h> // For term interaction / sending flags to it 
#include "include/term.h"
#include "include/ui.h"

void fillScreen(Winsize winSize) {
	int i,j;
	printf("%d",winSize.ws_col);
/*	setBgColor(TEXTBOX_COLOR_OUTSIDE);
	for(i = 0 ; i < winSize.ws_row ; i++) for(j = 0 ; j < winSize.ws_col ; j++) fputs(" ",stdout);
	resetColors();*/
}

void drawCommands(char *commands, Winsize winSize) { 
	int i, l = strlen(commands);
	setColor(COMMANDS_COLOR);
	setBgColor(COMMANDS_COLOR_BG);
	termGoto(0,winSize.ws_row);
	fputs(" ", stdout);
	if(l > winSize.ws_col) {
		for(i = 0 ; i < winSize.ws_col - 5 ; i++) printf("%c", commands[i]); // -3 for ..., -1 for \n et -1 for margin symmetry
		printf("...");
	}
	else { 
		for(i = 0 ; i < l ; i++) printf("%c", commands[i]);
		for(; i < winSize.ws_col -1 ; i++) fputs(" ", stdout);
	}
	resetColors();
}

Vect *drawTextBox(Vect size, int relativeVertOffset, Winsize winSize) {  
	int i,j;

	int yOrigin = round(((double)relativeVertOffset/100)*winSize.ws_row);
	int yMax = round((((double)size.y)/100)*(double)winSize.ws_row); // yMax relative to the yOrigin
	double sideMargin = (((100-(double)size.x)/100)*winSize.ws_col)/2; // Number of col on each side of the box
	
	Vect *textBoxSize = malloc(sizeof(Vect));

	// Skipping the un-needed height
	for(i = 1 ; i < yOrigin ; i++);
	termGoto(1,yOrigin);

	// Print blank line in BG color on top of the box
	setBgColor(TEXTBOX_COLOR_OUTSIDE);
	for(j = 1 ; j < winSize.ws_col + 1; j++) fputs(" ",stdout);

	termGoto(0,yOrigin+1);
	for(i = yOrigin+1 ; (i < yOrigin + yMax - 1 && i < winSize.ws_row - 1) ; i++) { // Until end of box size or end of window -1 cuz last line will be blank
		// Left margin
		setBgColor(TEXTBOX_COLOR_OUTSIDE);
		for(j = 0 ; j < sideMargin ; j++) fputs(" ",stdout);

		// Middle box
		setBgColor(TEXTBOX_COLOR_INSIDE);
		for(; j < winSize.ws_col - sideMargin ; j++) fputs(" ",stdout);
		
		// Right margin
		setBgColor(TEXTBOX_COLOR_OUTSIDE);
		for(; j < winSize.ws_col ; j++) fputs(" ",stdout);
	}
	
	// Print blank line in BG color at bottom of the box
	termGoto(0,(int)fminf((float)winSize.ws_row,(float)(yMax+yOrigin-1)));
	for(j = 0 ; j < winSize.ws_col ; j++) {
		// Set background color
		setBgColor(TEXTBOX_COLOR_OUTSIDE);
		fputs(" ",stdout);
		resetColors();
	}

	textBoxSize->x = winSize.ws_col - 2*sideMargin;
	textBoxSize->y = (int)fminf((float)yMax,(float)(winSize.ws_row - yOrigin)) - 2; // Get rid of top and bottom lines
	return textBoxSize;	
}

Vect *getBoxRelSize(Vect *boxRelSize) {
	if(boxRelSize == NULL) boxRelSize = malloc(sizeof(Vect));
	boxRelSize->x = WINDOW_XSIZE;
	boxRelSize->y = WINDOW_YSIZE;
	return boxRelSize;
}

void initUI(Winsize ws, Vect boxRelSize) {

	// Terminal preparation
	initTerm();
	termClear();

	// Screen initial setup
	fillScreen(ws);
	Vect *box1TextSize = drawTextBox(boxRelSize, WINDOW1_YPOS, ws);  // write as long as both aren't full
	Vect *box2TextSize = drawTextBox(boxRelSize, WINDOW2_YPOS, ws); 
	drawCommands(COMMANDS_TEXT, ws);

}

void updateScreen();
void updateUI(int mode);
void updateTextBoxes();
