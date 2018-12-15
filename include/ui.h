#ifndef UI_H
#define UI_H

// Commands related constants
#define COMMANDS_COLOR_BG 15
#define COMMANDS_COLOR 0
#define COMMANDS_TEXT " Ctrl+T : Translate the text currently in the top window ; Ctrl+S : Switch translation mode ; Ctrl+Q : Leave the translator"

// Textboxes related constants
#define TEXTBOX_COLOR_OUTSIDE 239
#define TEXTBOX_COLOR_INSIDE 247
#define WINDOW_XSIZE 90
#define WINDOW_YSIZE 40
#define WINDOW1_YPOS 5
#define WINDOW2_YPOS 45

typedef struct {
	int x;
	int y;
} Vect;

/***********************************
 * Lower level UI drawing routines *
 ***********************************/
// Fill the whole screen with the background color
void fillScreen(Winsize winSize);
// Draw the bottom line explaining the commands
void drawCommands(char *commands, Winsize winSize);
// Draw a textbox
// size is the relative size of the box in % to the window
// relativeVertOffset is the relative vertical offset in % (i.e. the "number of %" between the top of the screen and the beginning of the box
Vect *drawTextBox(Vect size, int relativeVertOffset, Winsize winSize);

/***************************
 * Upper level UI routines *
 ***************************/
// Get box relative size to window (initializes if not existing already)
Vect *getBoxRelSize(Vect *boxRelSize);
// Initialize UI
void initUI(Winsize ws, Vect boxRelSize);
// Update and redraw the whole screen to current terminal size
void updateScreen();
// Update UI, displays boxes and their titles in the correct configuration, deletes all text currently written
// mode 0 is Latin -> Morse, mode 1 is Morse -> Latin
void updateUI(int mode);
// Update the master textbox according to current keypresses ; commits changes accordingly to slave box using morse routines
// Also handles special sequences to delete everything in a box
void updateTextBoxes();

#endif
