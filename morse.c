#include <stdio.h>
#include <stdlib.h>
#include "include/term.h"
#include "include/ui.h"
#include "include/morse.h"

textBox *initBox(Vect boxSize) { // Initializes a box TODO add size
	textBox *box = malloc(sizeof(textBox));
	box->boxStr = malloc(boxSize.x*boxSize.y); // Allocate the number of chars in the box
	box->boxStrSize = boxSize.x*boxSize.y;
	box->boxCursor = 0;
	
	return box;
}

void editBox() { // updatebox box with char and all

}

void clearText();

//box append
