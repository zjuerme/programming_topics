#ifndef _HTMLPARSER_
#define _HTMLPARSER_

#include "graphics.h"
#include "extgraph.h"

#define LBEGINX 2 // x and y coordinate of the left panel (code part)
#define LBEGINY 7.8
#define RBEGINX 11 // x and y coordinate of the right panel (browser part)
#define RBEGINY 8.6
#define RWIDTH 8

#define LFONT "Consolas" // font of the left panel
#define RFONT "Times New Roman"


#define H1SIZE 36 // point size of H1 tag and so on
#define H2SIZE 26
#define H3SIZE 20
#define H4SIZE 16
#define H5SIZE 14
#define H6SIZE 12
#define TEXTSIZE 18 // point size of paragraph
#define CODESIZE 17 // point size of code (on the left panel)

#define H1HEI 0.22 // height of H1 tag and so on
#define H2HEI 0.2
#define H3HEI 0.2
#define H4HEI 0.2
#define H5HEI 0.2
#define H6HEI 0.2
#define TEXTHEI 0.15 // height of paragraph
#define CODEHEI 0.27 // height of code (on the left panel)

#define MAXLEN 1000 // maximum length of a line of text

struct Rec {
	double x1, x2, y1, y2; // coordinate of the lower_left cornor and upper_right cornor
	char *url;
}hyperLink[100000];
int hyperCnt; // totle number of hyperlinks

char titleR[100]; // title of the page

int readHtml(string fname);
void drawCode(); // draw the left panel (code part)
void drawHtml(); // draw the right panel (browser part)
void freeFileStr();

 
#endif
