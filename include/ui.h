#ifndef UI_H
#define UI_H

#define TEXTBOX_COLOR_OUTSIDE 239
#define TEXTBOX_COLOR_INSIDE 247
#define COMMANDS_COLOR_BG 15
#define COMMANDS_COLOR 0
#define COMMANDS_TEXT " t : Translate the text currently in the top window ; s : Twitch translation mode ; q : Leave the translator"

typedef struct {
	int x;
	int y;
} Vect;

typedef struct winsize Winsize;

void fillScreen(Winsize winSize);
// size is the relative size in % to the window
// relativeVertOffset is the relative vertical offset in % (i.e. the "number of %" between the top of the screen and the beginning of the box
void drawTextBox(Vect size, int relativeVertOffset, Winsize winSize);
void drawCommands(char *commands, Winsize winSize);
void initScreen();

void refreshScreen();

#endif
