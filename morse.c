#include <stdio.h>
#include <stdlib.h>
#include "include/term.h"
#include "include/ui.h"
#include "include/morse.h"

textBox *initBox(Vect boxTextSize) { // Initializes a box TODO add size
	textBox *box = malloc(sizeof(textBox));
	box->boxStr = malloc(boxTextSize.x*boxTextSize.y); // Allocate the number of chars in the box
	box->boxStrSize = boxTextSize.x*boxTextSize.y;
	box->boxCursor = 0;
	
	return box;
}

// Clear boxes when swapping mode
void resetTextBoxes(int mode, Vect boxLatTextSize, Vect boxMorTextSize, textBox *morBox, textBox *latBox) {
	// Reset latin text box
	latBox->boxCursor = 0;
	latBox->boxStr[0] = '\0';
	latBox->boxStrSize = boxLatTextSize.x*boxLatTextSize.y;

	// Reset morse text box
	morBox->boxCursor = 0;
	morBox->boxStr[0] = '\0';
	morBox->boxStrSize = boxMorTextSize.x*boxMorTextSize.y;

}

void appendBox(textBox *tBox, char c) {
	if(c == 8) { // Backspace
		if(tBox->boxCursor > 0) { // Check if there's something to delete
			tBox->boxStr[tBox->boxCursor - 1] = '\0'; // Delete current char
			tBox->boxCursor--; // Make cursor fallback
		}
	} else if(tBox->boxCursor < tBox->boxStrSize - 2) { // -1 for size to index conversion, and -1 cause cursor is always on the next index
			tBox->boxStr[tBox->boxCursor] = c;
			tBox->boxCursor++;
	}
}

void editBox() { // updatebox box with char and all

}

void clearText();

//box append
