#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <termios.h> // Terminal attributes
#include <unistd.h> // For STDIN_FILENO
#include <sys/ioctl.h> // For term interaction / sending flags to it 
#include "include/term.h"
#include "include/ui.h"

// TODO : low priority
// make more complete specs for UI functions and fix edge behaviors

void fillScreen(Winsize winSize) {
	int i,j;
	setBgColor(TEXTBOX_COLOR_OUTSIDE);
	for(i = 0 ; i < winSize.ws_row ; i++) for(j = 0 ; j < winSize.ws_col ; j++) fputs(" ",stdout);
	resetColors();
}

// size is the relative size in % to the window
// relativeVertOffset is the relative vertical offset in % (i.e. the "number of %" between the top of the screen and the beginning of the box
void drawTextBox(Vect size, int relativeVertOffset, Winsize winSize) {
	int i,j;
	int yOrigin = round(((double)relativeVertOffset/100)*winSize.ws_row);
	int yMax = round((((double)size.y)/100)*(double)winSize.ws_row); // yMax relative to the yOrigin
	double sideMargin = (((100-(double)size.x)/100)*winSize.ws_col)/2; // Number of col on each side of the box

	// Skipping the un-needed height
	for(i = 1 ; i < yOrigin ; i++);
	termGoto(1,yOrigin);

	// Print blank line in BG color on top of the box
	setBgColor(TEXTBOX_COLOR_OUTSIDE);
	for(j = 1 ; j < winSize.ws_col + 1; j++) fputs(" ",stdout);

	// TODO define containers better
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

void initScreen() {

}

void refreshScreen() {

}
