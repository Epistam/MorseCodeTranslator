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

int main(void) {

	// Initialize screen
	Winsize ws = (Winsize)getTermSize();
	initTerm();
	termClear();

	// Set text boxes size
	Vect *boxRelSize = malloc(sizeof(Vect));
	boxRelSize->x = WINDOW_XSIZE;
	boxRelSize->y = WINDOW_YSIZE;

	// Initial screen drawings TODO use routine for that
	fillScreen(ws);
	Vect *box1TextSize = drawTextBox(*boxRelSize, WINDOW1_YPOS, ws);  // write as long as both aren't full
	Vect *box2TextSize = drawTextBox(*boxRelSize, WINDOW2_YPOS, ws); 
	drawCommands(COMMANDS_TEXT, ws);

	// Cursor var + replace cursor 	

	// Main loop
	char c;
	int running = 1;
	while(running) {
		// Main character acquisition loop
		while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q' && c != 't' && c != 's') {
			if (!iscntrl(c)) {
			} else {
				// Escape sequence
			}
		}
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
	}

	return EXIT_SUCCESS;
}
