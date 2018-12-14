#ifndef UI_H
#define UI_H

#define TEXTBOX_COLOR_OUTSIDE 239
#define TEXTBOX_COLOR_INSIDE 247
#define COMMANDS_COLOR_BG 15
#define COMMANDS_COLOR 0
#define COMMANDS_TEXT " Ctrl+T : Translate the text currently in the top window ; Ctrl+S : Switch translation mode ; Ctrl+Q : Leave the translator"

#define WINDOW_XSIZE 90
#define WINDOW_YSIZE 40
#define WINDOW1_YPOS 5
#define WINDOW2_YPOS 45


typedef struct {
	int x;
	int y;
} Vect;

typedef struct winsize Winsize;

void fillScreen(Winsize winSize);
// size is the relative size in % to the window
// relativeVertOffset is the relative vertical offset in % (i.e. the "number of %" between the top of the screen and the beginning of the box
Vect *drawTextBox(Vect size, int relativeVertOffset, Winsize winSize);
void drawCommands(char *commands, Winsize winSize);
//void initScreen();

//void refreshScreen();

void updateScreen(int mode); // Displays boxes + commands in given configuration, deletes all text written
//void 


#endif
