#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <termios.h> // Terminal attributes
#include <unistd.h> // For STDIN_FILENO
#include <sys/ioctl.h> // For term interaction / sending flags to it
#include <ctype.h> // For iscntrl
#include "include/term.h"
#include "include/ui.h"
#include "include/morse.h"

// TODO : rewrite goto origin taking uiCursor into account
// TODO : write as long as both aren't full
// TODO : disclaimer : déparateurs and all
// TODO add program status indicators etc
// TODO LP : fix bug need to push twice on Ctrl Q to quit
// TODO LP : can't switch sides more than ocne (at least titles are bugging)
// TODO LP : fix cursor bottom of screen at beginning
// TODO LP : make more complete specs for UI functions and fix edge behaviors
// TODO LP : make containers definition better and more organized (subcontainers and such)
// REM : morse.h can be over and used by ui.h since graphical methods will only be called by main and ui.c

int main(void) {

	int mode = 0;
	Vect *uiCursor = malloc(sizeof(Vect)); // relative to top box origin 
	
	int k;

	// Initialize screen
	Winsize ws; // Global window size (may change if the user resizes the window during execution)
	updateTermSize(&ws);
	
	// Initialize text boxes
	Vect *boxRelSize = getBoxRelSize(NULL); // Relative default textbox size
	
	// Display the basic UI layout
	initUI(ws);


	// Drawing boxes and getting boxes size
	Vect *boxLatTextSize = drawTextBox(*boxRelSize, NULL, WINDOW1_YPOS, ws,TEXTBOX_TITLE_LATIN); 
	Vect *boxMorTextSize = drawTextBox(*boxRelSize, NULL, WINDOW2_YPOS, ws,TEXTBOX_TITLE_MORSE); 

	// Initializing textboxes as an abstract object (note : there is a distinct difference between UI boxes and "morse.h" boxes, 
	// the latter only containing the boxes CONTENTS which will be processed later on during morse translation)
	textBox *latBox = initBox(*boxLatTextSize); 
	textBox *morBox = initBox(*boxMorTextSize); 

	Vect *orig = malloc(sizeof(orig));
	gotoTBOrigin(ws, uiCursor, orig); // sets uiCusor and orig
	int xorig = uiCursor->x;
	fflush(stdout); // Flush since smh cache is still tied to newlines

	// Main loop
	char c;
	int running = 1;
  	// Main character acquisition loop
	while(read(STDIN_FILENO, &c, 1) == 1 && running) {

		if (!iscntrl(c)) { 
			appendBox(mode ? morBox : latBox, c, uiCursor, mode ? boxMorTextSize->x : boxLatTextSize->x, orig);
		} else { // If it is a control character
			switch(c) {
				case 127 : 
					appendBox(mode ? morBox : latBox, c, uiCursor, mode ? boxMorTextSize->x : boxLatTextSize->x, orig);
					break;
				case 20 :
					// Translate TODO erase lower box to avoid translations piling up on top of each otehr
					//for(k = 0 ; k < mode ? morBox->boxStrSize : latBox->boxStrSize ; k++) mode ? (morBox->boxStr[k] = '\0') : (latBox->boxStr[k] = '\0');
					mode ? mor2Lat(morBox,latBox) : lat2Mor(latBox,morBox);
					termGoto((((100-(double)WINDOW_XSIZE)/100)*ws.ws_col)/2+2,((double)WINDOW2_YPOS/100)*ws.ws_row+2); // Compensating from left frame and top frame + title row
					printf("%s", mode ? latBox->boxStr : morBox->boxStr);
					termGoto(orig->x + uiCursor->x, orig-> y + uiCursor->y);
					// Move cursor to previous position again
					break;
				case 19 :
					// Switch mode
					swapUIBoxes(&mode, boxLatTextSize, boxMorTextSize, *boxRelSize, ws, uiCursor, orig);
					resetTextBoxes(mode, *boxLatTextSize, *boxMorTextSize, morBox, latBox);
					break;
				case 17 :
					running = 0;
					break;
			}
		}
		//printf("%d\n",c);
		fflush(stdout); // Flush since smh cache is still tied to newlines
	}

	return EXIT_SUCCESS;
}
