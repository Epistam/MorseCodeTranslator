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
	setBgColor(BG_COLOR);
	for(i = 0 ; i < winSize.ws_row ; i++) for(j = 0 ; j < winSize.ws_col ; j++) fputs(" ",stdout);
	resetColors();
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

Vect *drawTextBox(Vect size, Vect *textBoxSize, int relativeVertOffset, Winsize winSize, char *boxTitle) {  
	int i,j;
	int titleSize = strlen(boxTitle);
	int yOrigin = round(((double)relativeVertOffset/100)*winSize.ws_row);
	int xSize = round(winSize.ws_col*((double)size.x/100)) + 4; // +4 accounts for frames
	int yMax = round((((double)size.y)/100)*(double)winSize.ws_row); // yMax relative to the yOrigin
	double sideMargin = (((100-(double)size.x)/100)*winSize.ws_col)/2; // Number of col on each side of the box
	
	// Skipping the un-needed height + left margin
	termGoto(sideMargin,yOrigin);

	// Top frame and title
	setBgColor(TEXTBOX_COLOR_TITLEBG);
	setColor(TEXTBOX_COLOR_TITLE);
	fputs("  ",stdout);
	for(j = 0 ; j < xSize - 5 && j < titleSize  ; j++) printf("%c",boxTitle[j]); // Write until we reach the end of the line or the end of the string
	for(; j < xSize - 3 ; j++) fputs(" ",stdout); // Complete the line if need be 
	if(j < titleSize) { // Add ellipsis if the window is not wide enough
		termGoto(sideMargin+j-3, yOrigin); // Go to the end of the line, go back 3 char, write ellipsis
		fputs("...",stdout);
	}

	// Box body
	termGoto(0,yOrigin+1);
	for(i = yOrigin+1 ; (i < yOrigin + yMax - 1 && i < winSize.ws_row - 1) ; i++) { // Until end of box size or end of window -1 cuz last line will be blank
		// Left margin skip
		j = sideMargin; // ??? idk, idc tbf
		// Left frame
		termGoto(sideMargin,i); // Goto left frame
		setBgColor(TEXTBOX_COLOR_FRAME);
		fputs(" ",stdout);
		fputs(" ",stdout);
		// Middle box
		setBgColor(TEXTBOX_COLOR_INSIDE); // Box content
		for(; j < winSize.ws_col - sideMargin - 2 ; j++) fputs(" ",stdout); // -2 accounts for the yet to be displayed margin
		// Right frame
		setBgColor(TEXTBOX_COLOR_FRAME); // Goto right frame
		fputs(" ",stdout);
		fputs(" ",stdout);
	}
	
	// Bottom frame
	termGoto(sideMargin,(int)fminf((float)winSize.ws_row,(float)(yMax+yOrigin-1))); // Skip right margin
	setBgColor(TEXTBOX_COLOR_FRAME); // Set background color
	for(j = 1 ; j < xSize ; j++) fputs(" ",stdout); // Draw bottom frame

	// Reset colors for subsequent operations
	resetColors();

	if(textBoxSize == NULL) textBoxSize = malloc(sizeof(Vect));
	// Return text box size in characters
	textBoxSize->x = winSize.ws_col - 2*sideMargin;
	textBoxSize->y = (int)fminf((float)yMax,(float)(winSize.ws_row - yOrigin)) - 2; // Get rid of top and bottom lines

	return textBoxSize;	
}

void appendUIBox(int c) {
	setBgColor(TEXTBOX_COLOR_INSIDE);
	setColor(TEXTBOX_COLOR_TEXT);
	if(c == -1) {
		termBack();
		fputs(" ",stdout);
		termBack();
	} else { // TODO : add retour à la ligne
		printf("%c",c);

	}
}

Vect *getBoxRelSize(Vect *boxRelSize) {
	if(boxRelSize == NULL) boxRelSize = malloc(sizeof(Vect));
	boxRelSize->x = WINDOW_XSIZE;
	boxRelSize->y = WINDOW_YSIZE;
	return boxRelSize;
}

void initUI(Winsize ws) {

	// Terminal preparation
	initTerm();
	termClear();

	// Screen initial setup
	fillScreen(ws);
	drawCommands(COMMANDS_TEXT, ws);

}

void swapUIBoxes(int *mode, Vect *boxLatTextSize, Vect *boxMorTextSize, Vect boxRelSize, Winsize ws) {

	// Swap the boxes graphicaly
	boxLatTextSize = drawTextBox(boxRelSize, boxLatTextSize, mode ? WINDOW2_YPOS : WINDOW1_YPOS, ws,TEXTBOX_TITLE_LATIN);
	boxMorTextSize = drawTextBox(boxRelSize, boxMorTextSize, mode ? WINDOW1_YPOS : WINDOW2_YPOS, ws,TEXTBOX_TITLE_MORSE);

	// Swap mode
	*mode = *mode ? 0 : 1;

}

void updateScreen();

void updateTextBoxes();
