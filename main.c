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

// TODO : write as long as both aren't full
// TODO : disclaimer : déparateurs and all
// TODO add program status indicators etc
// TODO add title to each window
// TODO add procedure to delete everything in a box
// TODO LP : make more complete specs for UI functions and fix edge behaviors
// TODO LP : make containers definition better and more organized (subcontainers and such)
// REM : morse.h can be over and used by ui.h since graphical methods will only be called by main and ui.c

int main(void) {

	// Initialize screen
	Winsize ws; // Global window size (may change if the user resizes the window during execution)
	updateTermSize(&ws);
	
	// Initialize text boxes
	Vect *boxRelSize = getBoxRelSize(NULL); // Relative default textbox size
	
	// Display the basic UI layout
	initUI(ws);


	// Drawing boxes and getting boxes size
	Vect *boxLatTextSize = drawTextBox(*boxRelSize, WINDOW1_YPOS, ws,TEXTBOX_TITLE_LATIN); 
	Vect *boxMorTextSize = drawTextBox(*boxRelSize, WINDOW2_YPOS, ws,TEXTBOX_TITLE_MORSE); 

	// Initializing textboxes as an abstract object (note : there is a distinct difference between UI boxes and "morse.h" boxes, 
	// the latter only containing the boxes CONTENTS which will be processed later on during morse translation)
	textBox *latBox = initBox(*boxLatTextSize); 
	textBox *morBox = initBox(*boxMorTextSize); 

	//printf("%d",morBox->boxStrSize);

	// Cursor var + replace cursor 	

	// Main loop
//	char c;
//	int running = 1;
//	while(running) {
		// Main character acquisition loop
//		while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q' && c != 't' && c != 's') {
//			if (!iscntrl(c)) {
//			} else {
//				// Escape sequence
//			}
//		}
		// Escape processing
		/*switch(c) {
			case 'q': // Leave
				running = 0;
				break;
			case 's': // Switch translation direction
				
				break;
			case 't': // Translate

				break;
		}*/
//	}

	return EXIT_SUCCESS;
}
