#ifndef TERM_H
#define TERM_H

/********************************
 * Terminal function / routines *
 ********************************/

typedef struct winsize Winsize;

// Whole terminal / screen routines
void termClear();
struct winsize getTermSize();
void initTerm();
void resetTerm();

// Single line
void termClearLine();

// Cursor movement 
void termUp();
void termDown();
void termFwd();
void termBack();
void termGoto(int x, int y);

// Cursor color
void resetColors();
void setColor(int color); 
void setBgColor(int color);

#endif
