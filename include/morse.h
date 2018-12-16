#ifndef MORSE_H
#define MORSE_H

typedef struct {
	char *boxStr; // Box content
	int boxStrSize; // String max length
	int boxCursor; // Current cursor position
} textBox;

// Create a box
textBox *initBox(Vect boxTextSize);

// Reset boxes when swapping mode
void resetTextBoxes(int mode, Vect boxLatTextSize, Vect boxMorTextSize, textBox *morBox, textBox *latBox);
// Append a character to the box (deletes the previous one in case backspace is provided)
void appendBox(textBox *tBox, char c);

void lat2Mor(textBox *latBox, textBox *morBox);
void mor2Lat(textBox *morBox, textBox *latBox);

#endif
