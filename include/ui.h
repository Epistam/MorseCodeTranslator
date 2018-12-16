#ifndef UI_H
#define UI_H

#define COMMANDS_TEXT " Ctrl+T : Translate the text currently in the top window ; Ctrl+S : Switch translation mode ; Ctrl+Q : Leave the translator"

/*********************
 * Graphical "style" *
 *********************/
#define BG_COLOR 234

#define COMMANDS_COLOR_BG 15
#define COMMANDS_COLOR 0

#define TEXTBOX_COLOR_TEXT 15
#define TEXTBOX_COLOR_TITLE 15
#define TEXTBOX_COLOR_TITLEBG 244
#define TEXTBOX_COLOR_FRAME 236
#define TEXTBOX_COLOR_INSIDE 240

/************************
 * Windows positionning *
 ************************/
#define WINDOW_XSIZE 90
#define WINDOW_YSIZE 40
#define WINDOW1_YPOS 5
#define WINDOW2_YPOS 48

/***************
 * Boxes names *
 ***************/
#define TEXTBOX_TITLE_MORSE "Morse Code :"
#define TEXTBOX_TITLE_LATIN "Latin Alphabet :"

typedef struct {
	int x;
	int y;
} Vect;

// TODO future refactor
/*typedef struct { // should separate structs if you want to keep separation between morse and ui. Don't want both operating at the same time.
	char *boxTitle; // Box... title
	Size boxRelSize; // i.e in 
} uiBox;*/

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
Vect *drawTextBox(Vect size, Vect *textBoxSize, int relativeVertOffset, Winsize winSize, char *boxTitle);
void appendUIBox(int c);

void gotoTBOrigin(Winsize ws);

/***************************
 * Upper level UI routines *
 ***************************/
// Get box relative size to window (initializes if not existing already)
Vect *getBoxRelSize(Vect *boxRelSize);
// Initialize UI
void initUI(Winsize ws);
// Swap boxes, displays boxes and their titles in the correct configuration, deletes all text currently written
// mode 0 is Latin -> Morse, mode 1 is Morse -> Latin
void swapUIBoxes(int *mode, Vect *boxLatTextSize, Vect *boxMorTextSize, Vect boxRelSize, Winsize ws);
// Update and redraw the whole screen to current terminal size
void updateScreen();
// Update the master textbox according to current keypresses ; commits changes accordingly to slave box using morse routines
// Also handles special sequences to delete everything in a box
void updateTextBoxes();

#endif
