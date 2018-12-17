#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "include/term.h"
#include "include/ui.h"
#include "include/morse.h"

textBox *initBox(Vect boxTextSize) { // Initializes a box TODO add size
	textBox *box = malloc(sizeof(textBox));
	box->boxStr = malloc(boxTextSize.x*boxTextSize.y); // Allocate the number of chars in the box
	box->boxStr[0] = '\0';
	box->boxStrSize = boxTextSize.x*boxTextSize.y;
	box->boxCursor = 0;
	
	return box;
}

// Clear boxes when swapping mode
void resetTextBoxes(int mode, Vect boxLatTextSize, Vect boxMorTextSize, textBox *morBox, textBox *latBox) {
	// Reset latin text box
	int k;
	latBox->boxCursor = 0;
	for(k = 0 ; k < latBox->boxStrSize ; k++) latBox->boxStr[k] = '\0';
	latBox->boxStrSize = boxLatTextSize.x*boxLatTextSize.y;

	// Reset morse text box
	morBox->boxCursor = 0;
	for(k = 0 ; k < morBox->boxStrSize ; k++) morBox->boxStr[k] = '\0';
	morBox->boxStrSize = boxMorTextSize.x*boxMorTextSize.y;

}

void appendBox(textBox *tBox, char c, Vect *uiCursor, int boxWidth, Vect *orig) {
	if(c == 127) { // Backspace
		if(tBox->boxCursor > 0) { // Check if there's something to delete
			tBox->boxStr[tBox->boxCursor - 1] = '\0'; // Delete current char
			tBox->boxCursor--; // Make cursor fallback
			appendUIBox(-1, uiCursor, tBox->boxCursor, boxWidth, orig);
		}
	} else if(tBox->boxCursor < tBox->boxStrSize - 2) { // -1 for size to index conversion, and -1 cause cursor is always on the next index
			tBox->boxStr[tBox->boxCursor] = c;
			tBox->boxCursor++;
			appendUIBox(c, uiCursor, tBox->boxCursor, boxWidth, orig);
	}
}

void lat2Mor(textBox *latBox, textBox *morBox) {
	int i;
	int curpos=0;
	char *str = strdup(latBox->boxStr);
	for(i = 0 ; i < latBox->boxStrSize && str[i] != '\0' && latBox->boxStrSize - curpos > 5 ; i++) {
		if(str[i] >= 'a' && str[i] <= 'z') str[i] = str[i] - ('a'-'A'); // Putting everything in upper case
		if(str[i] >= 'A' && str[i] <= 'Z') {
			switch(str[i]) {
				case 'A' :
					strcat(morBox->boxStr,".-");
					break;
				case 'B' :
					strcat(morBox->boxStr,"-...");
					break;
				case 'C' :
					strcat(morBox->boxStr,"-.-.");
					break;
				case 'D' :
					strcat(morBox->boxStr,"-..");
					break;
				case 'E' :
					strcat(morBox->boxStr,".");
					break;
				case 'F' :
					strcat(morBox->boxStr,"..-.");
					break;
				case 'G' :
					strcat(morBox->boxStr,"--.");
					break;
				case 'H' :
					strcat(morBox->boxStr,"....");
					break;
				case 'I' :
					strcat(morBox->boxStr,"..");
					break;
				case 'J' :
					strcat(morBox->boxStr,".---");
					break;
				case 'K' :
					strcat(morBox->boxStr,"-.-");
					break;
				case 'L' :
					strcat(morBox->boxStr,".-..");
					break;
				case 'M' :
					strcat(morBox->boxStr,"--");
					break;
				case 'N' :
					strcat(morBox->boxStr,"-.");
					break;
				case 'O' :
					strcat(morBox->boxStr,"---");
					break;
				case 'P' :
					strcat(morBox->boxStr,".--.");
					break;
				case 'Q' :
					strcat(morBox->boxStr,"--.-");
					break;
				case 'R' :
					strcat(morBox->boxStr,".-.");
					break;
				case 'S' :
					strcat(morBox->boxStr,"...");
					break;
				case 'T' :
					strcat(morBox->boxStr,"-");
					break;
				case 'U' :
					strcat(morBox->boxStr,"..-");
					break;
				case 'V' :
					strcat(morBox->boxStr,"...-");
					break;
				case 'W' :
					strcat(morBox->boxStr,".--");
					break;
				case 'X' :
					strcat(morBox->boxStr,"-..-");
					break;
				case 'Y' :
					strcat(morBox->boxStr,"-.--");
					break;
				case 'Z' :
					strcat(morBox->boxStr,"--..");
					break;
			}
		}
		if(str[i] >= '0' && str[i] <= '9') {
			switch(str[i]) {
				case '0' :
					strcat(morBox->boxStr,"-----");
					break;
				case '1' :
					strcat(morBox->boxStr,".----");
					break;
				case '2' :
					strcat(morBox->boxStr,"..---");
					break;
				case '3' :
					strcat(morBox->boxStr,"...--");
					break;
				case '4' :
					strcat(morBox->boxStr,"....-");
					break;
				case '5' :
					strcat(morBox->boxStr,".....");
					break;
				case '6' :
					strcat(morBox->boxStr,"-....");
					break;
				case '7' :
					strcat(morBox->boxStr,"..---");
					break;
				case '8' :
					strcat(morBox->boxStr,"---..");
					break;
				case '9' :
					strcat(morBox->boxStr,"----.");
					break;
			}
		}
		strcat(morBox->boxStr," ");
		for(;morBox->boxStr[curpos] != '\0';curpos++); // get top of the pile
	}
	


	// + display morbox
}

void mor2Lat(textBox *morBox, textBox *latBox) {
	int i;
	//int curpos=0;
	char *tok; 
	char *str = strdup(morBox->boxStr);
	// Not optimized for shit, a more performance friendly answer would be to use a binary tree, but heck that for now
	for(i = 0 ; (tok = strsep(&str, " ")) != NULL ; i++) { // morse takes more space than latin so no overflwo check needed
		if(!strcmp(tok,".-")) strcat(latBox->boxStr,"A");
		if(!strcmp(tok,"-...")) strcat(latBox->boxStr,"B");
		if(!strcmp(tok,"-.-.")) strcat(latBox->boxStr,"C");
		if(!strcmp(tok,"-..")) strcat(latBox->boxStr,"D");
		if(!strcmp(tok,".")) strcat(latBox->boxStr,"E");
		if(!strcmp(tok,"..-.")) strcat(latBox->boxStr,"F");
		if(!strcmp(tok,"--.")) strcat(latBox->boxStr,"G");
		if(!strcmp(tok,"....")) strcat(latBox->boxStr,"H");
		if(!strcmp(tok,"..")) strcat(latBox->boxStr,"I");
		if(!strcmp(tok,".---")) strcat(latBox->boxStr,"J");
		if(!strcmp(tok,"-.-")) strcat(latBox->boxStr,"K");
		if(!strcmp(tok,".-..")) strcat(latBox->boxStr,"L");
		if(!strcmp(tok,"--")) strcat(latBox->boxStr,"M");
		if(!strcmp(tok,"-.")) strcat(latBox->boxStr,"N");
		if(!strcmp(tok,"---")) strcat(latBox->boxStr,"O");
		if(!strcmp(tok,".--.")) strcat(latBox->boxStr,"P");
		if(!strcmp(tok,"--.-")) strcat(latBox->boxStr,"Q");
		if(!strcmp(tok,".-.")) strcat(latBox->boxStr,"R");
		if(!strcmp(tok,"...")) strcat(latBox->boxStr,"S");
		if(!strcmp(tok,"-")) strcat(latBox->boxStr,"T");
		if(!strcmp(tok,"..-")) strcat(latBox->boxStr,"U");
		if(!strcmp(tok,"...-")) strcat(latBox->boxStr,"V");
		if(!strcmp(tok,".--")) strcat(latBox->boxStr,"W");
		if(!strcmp(tok,"-..-")) strcat(latBox->boxStr,"X");
		if(!strcmp(tok,"-.--")) strcat(latBox->boxStr,"Y");
		if(!strcmp(tok,"--..")) strcat(latBox->boxStr,"Z");
		if(!strcmp(tok,"-----")) strcat(latBox->boxStr,"0");
		if(!strcmp(tok,".----")) strcat(latBox->boxStr,"1");
		if(!strcmp(tok,"..---")) strcat(latBox->boxStr,"2");
		if(!strcmp(tok,"...--")) strcat(latBox->boxStr,"3");
		if(!strcmp(tok,"....-")) strcat(latBox->boxStr,"4");
		if(!strcmp(tok,".....")) strcat(latBox->boxStr,"5");
		if(!strcmp(tok,"-....")) strcat(latBox->boxStr,"6");
		if(!strcmp(tok,"--...")) strcat(latBox->boxStr,"7");
		if(!strcmp(tok,"---..")) strcat(latBox->boxStr,"8");
		if(!strcmp(tok,"----.")) strcat(latBox->boxStr,"9");
		if(!strcmp(tok,"/")) strcat(latBox->boxStr," ");
	}
	
// TODO : ternary autism
//		buf = (tok[0] == '.') ? : (c=='-')
}
