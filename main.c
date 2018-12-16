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

// Morse.c update commit dans struct
// UI update according to append : reuse current cursor et add ou delete
// TODO : manage '\0' when writing
// TODO : write as long as both aren't full
// TODO : disclaimer : déparateurs and all
// TODO add program status indicators etc
// TODO LP : make more complete specs for UI functions and fix edge behaviors
// TODO LP : make containers definition better and more organized (subcontainers and such)
// REM : morse.h can be over and used by ui.h since graphical methods will only be called by main and ui.c

int main(void) {

	int mode = 0;
	Vect uiCursor; // TODO init


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

	int xOrigin = (((100-(double)WINDOW_XSIZE)/100)*ws.ws_col)/2; // Number of col on each side of the box
	int yOrigin = ((double)WINDOW1_YPOS/100)*ws.ws_row;
	termGoto(xOrigin+2,yOrigin+2); // Compensating from left frame and top frame + title row

	//updateUI(&mode, boxLatTextSize, boxMorTextSize, *boxRelSize, ws);
	//printf("%d",morBox->boxStrSize);

	// Cursor var + replace cursor 	

	// Main loop/
	char c;
	int running = 1;
  	// Main character acquisition loop
	while(read(STDIN_FILENO, &c, 1) == 1 && running) {
		if (!iscntrl(c)) { 
			if(isalnum(c)) appendUIBox(c);
		} else { // If it is a control character
			switch(c) {
				case 127 : 
					appendUIBox(-1);
					break;
				case 20 :
					// Translate
					break;
				case 19 :
					// Switch mode
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
