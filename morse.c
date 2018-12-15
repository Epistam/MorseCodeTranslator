#include <stdio.h>
#include <stdlib.h>
#include "include/term.h"
#include "include/ui.h"

typedef struct {
	char *boxText; // Box content
	int boxSize; // String max length
	int boxPos; // Current cursor position
} Box;

Box *initBox(Vect boxSize) { // Initializes a box TODO add size
	Box *box = malloc(sizeof(Box));
	box->boxText = malloc(42);
	box->boxSize = boxSize.x*boxSize.y;
	box->boxPos = 0;
	
	return box;
}

void editBox() {

}

void clearText();

//box append
