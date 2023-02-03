#include "htmlParser.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

extern int searchflag;

enum Tag {
	H1, _H1, H2, _H2, H3, _H3, H4, _H4, H5, _H5, H6, _H6, P, _P, 
		A, _A, B, _B, I, _I, Title, _Title, Head, _Head, Body, _Body, Html, _Html
};

static double lasHei, px, py;
static char *p, *col, *url;

double max(double x, double y) { return x > y ? x : y; }

void tagError() {
	// unrecognized tag!
	assert(0);
}

enum Tag getTag() {
	char c;
	while(*(p++) != '<');
	c = *(p++);
	enum Tag ret = 0;
	if(c == 'a') ret = A;
	else if(c == 'p') ret = P;
	else if(c == 'h') {
		c = *(p++);
		if(c == '1') ret = H1;
		else if(c == '2') ret = H2;
		else if(c == '3') ret = H3;
		else if(c == '4') ret = H4;
		else if(c == '5') ret = H5;
		else if(c == '6') ret = H6;
		else if(c == 'e') ret = Head;
		else if(c == 't') ret = Html;
		else tagError();
	}
	else if(c == 'b') {
		c = *(p++);
		if(c == 'o') ret = Body;
		else if(c == '>') --p, ret = B;
		else tagError();
	}
	else if(c == 't') ret = Title;
	else if(c == 'i') ret = I;
	else if(c == '/') {

		c = *(p++);
		if(c == 'a') ret = _A;
		else if(c == 'p') ret = _P;
		else if(c == 'h') {
			c = *(p++);
			if(c == '1') ret = _H1;
			else if(c == '2') ret = _H2;
			else if(c == '3') ret = _H3;
			else if(c == '4') ret = _H4;
			else if(c == '5') ret = _H5;
			else if(c == '6') ret = _H6;
			else if(c == 'e') ret = _Head;
			else if(c == 't') ret = _Html;
			else tagError();
		}
		else if(c == 'b') {
			c = *(p++);
			if(c == 'o') ret = _Body;
			else if(c == '>') --p, ret = _B;
			else tagError();
		}
		else if(c == 't') ret = _Title;
		else if(c == 'i') ret = _I;

	}
	while(*p != '"' && *p != '>') ++p;
	++p;
	int i; 
	if(*(p-1) == '>') return ret;
	if(ret == A) {
		char *q = p;
		while(*(p++) != '"');
		url = (char*)malloc(sizeof(char)*(p-q+5));
		memset(url, 0, sizeof(url));
		for(i = 0; q + 1 < p; ++q, ++i) url[i] = *q;
	} else {
		//for(i = 1; i <= 6; ++i) ++p;
		p=p+6;
		char *q = p;
		while(*(p++) != ';');
		col = (char*)malloc(sizeof(char)*(p-q+5));
		// col = (char*)malloc(sizeof(char)*(20));
		memset(col, 0, sizeof(col));
		for(i = 0; q + 1 < p; ++q, ++i) col[i] = *q;
		col[i]='\0';//²»¼Ó´ËÐÐ´úÂë¿ÉÄÜ±È½ÏÊ±»á³ö´í 
	}
	while(*(p++) != '>');
	return ret;
}

double getHei(enum Tag t) {
	if(t == H1) return H1HEI;
	if(t == H2) return H2HEI;
	if(t == H3) return H3HEI;
	if(t == H4) return H4HEI;
	if(t == H5) return H5HEI;
	if(t == H6) return H6HEI;
	if(t == P) return TEXTHEI;
	return 0;
}

void preTreat(char *pt) {
	int len = strlen(pt), j = 0,i;
	for(i = 0; i < len; ++i) {
		if(pt[i] == '\n') continue;
		pt[j++] = pt[i];
	}
	while(j <= len) pt[j++] = 0;
}
//?Ò²????? 

void parse(enum Tag cur) {
	enum Tag next;
	char c;
	int isFir = 1;
	char *tmpCol = 0;
	while(1) {
		if(cur <= 21) {
			int len = 0,i; 
			char *q = p;
			while(*p != '<') ++len, ++p;
			char *pt = (char*)malloc(sizeof(char)*(len+1)), ret[2];
			for(i = 0; i < len; ++i) pt[i] = *(q++);
			pt[len] = 0;
			/*preTreat(pt);*/
			if(cur == Title) { 
				memset(titleR, '/0', sizeof(titleR));
				memcpy(titleR, pt, sizeof(char)*(len+1));
			}
			else {
				if(cur == H1) SetPointSize(H1SIZE), SetStyle(Bold);
				if(cur == H2) SetPointSize(H2SIZE), SetStyle(Bold);
				if(cur == H3) SetPointSize(H3SIZE), SetStyle(Bold);
				if(cur == H4) SetPointSize(H4SIZE), SetStyle(Bold);
				if(cur == H5) SetPointSize(H5SIZE), SetStyle(Bold);
				if(cur == H6) SetPointSize(H6SIZE), SetStyle(Bold);
				if(cur == P) SetStyle(Normal), SetPointSize(TEXTSIZE);
				if(cur == B) SetStyle(Bold);
				if(cur == I) SetStyle(Italic);
				if(col) SetPenColor(col);
				if(cur == A) {
					SetPenColor("Blue");
					++hyperCnt;
					hyperLink[hyperCnt].x1 = GetCurrentX();
					hyperLink[hyperCnt].y1 = GetCurrentY();
					hyperLink[hyperCnt].x2 = GetCurrentX() + TextStringWidth(pt);
					hyperLink[hyperCnt].y2 = GetCurrentY() + GetFontHeight();
					hyperLink[hyperCnt].url = url;
				}
				if(cur <= 13 && isFir) {
					px = RBEGINX;
					py -= max(lasHei, getHei(cur)) + GetFontHeight();
					lasHei = getHei(cur);
				}
				len = strlen(pt);
				int i;
				for(i = 0; i < len; ++i) {
					ret[0] = pt[i]; ret[1] = 0;
					if(pt[i] < 0) {
						ret[1] = pt[++i];
						ret[2] = 0;
					}
					/*if(px + TextStringWidth(ret) > RBEGINX + RWIDTH) {*/
					if(pt[i] == '\n') {
						px = RBEGINX;
						py -= GetFontHeight();
						lasHei = getHei(cur);
						continue;
					} 
					MovePen(px, py);
					DrawTextString(ret); 
					if(cur == A) { 
						MovePen(px, py);
						DrawLine(TextStringWidth(ret), 0);
					}
					px += TextStringWidth(ret);
				}
				if(col) SetPenColor(col);
				else SetPenColor("Black");
			}
			free(pt);
			pt = 0;
		}

		next = getTag();
		if((next ^ cur) == 1) break;
		else { 
			parse(next);
		}
		isFir = 0;	
	}
	if(col && cur <= 13) {
		free(col);
		col = 0;
		SetPenColor("Black");
	}
}

char *fspt = NULL;
extern UseHelpFlag;

void GettitleR(){
    char *pf=fspt;
	int i=0;
    while (*pf!='<'||*(pf+1)!='t')   pf++;
    pf=strchr(pf,'>')+1;
    while(*pf!='<')
	titleR[i++]=*(pf++);
	titleR[i]='\0';
	// free(fspt);
}

int readHtml(string fname) {
	if(!fname) return 0;
	FILE *fp = fopen(fname, "rb+");
	if(fp == NULL){
		/*UseHelpFlag=4;
		return 0;*/
		fp = fopen("wrong.html", "rb+");//¿ÉÄÜ»á¶ÁÈ¡´íÎó£¬ÅÐ¶ÏÒ»ÏÂ»òÕß»òÕßÌáÇ°°Ñwrong.htmlÀïµÄÄÚÈÝ´æÔÚÒ»¸ö±äÁ¿ÖÐ 
		if (fp == NULL)//ÈÔÈ»ÐèÒª¶ÁÈëÒ»¸ö±¸ÓÃµÄ±¨´íhtmlÎÄ¼þ£¬·ÀÖ¹ºóÐøµÄ±ÀÀ£ 
		{
			return 0;
		}
		UseHelpFlag=4;//Ìø³ö±¨´íÒ³ 
		//return 0;	
		
	}
	char c;
	int len = 0,i;
	
	long begin, end;
	fseek(fp, 0, SEEK_SET);
	begin = ftell(fp);
	fseek(fp, 0, SEEK_END);
	end = ftell(fp);
	
	len = end - begin;
	
	fspt = (char*)malloc(sizeof(char)*(len + 10));
	
	fseek(fp, 0, SEEK_SET);
	// for(i = 0; i < len; ++i) fspt[i] = fgetc(fp);
	fread(fspt, len, 1, fp);
	fspt[len] = 0;
	fclose(fp);
	return 1;
}

void freeFileStr() {
	free(fspt);
	fspt = 0;
	int i;
	for(i = 1; i <= hyperCnt; i++) free(hyperLink[i].url);
}

void drawCode() {
	double x = LBEGINX, y = LBEGINY;
	MovePen(x, y); 
	SetFont(LFONT);
	char *pt = (char*)malloc(sizeof(char)*MAXLEN),  ret[5];
	int len = 0;
	p = fspt;
	int lev = 0, isStr = 0;
	
	while(*p) {
		len = 0;
		while(*p && *(p++) != '\n') pt[len++] = *(p-1);
		pt[len] = 0;
		SetPointSize(CODESIZE);
		SetStyle(Normal);
		int i;
		for(i = 0; i < len; ++i) { 
			ret[0] = pt[i]; ret[1] = 0;
			if(pt[i] < 0) {
				ret[1] = pt[++i];
				ret[2] = 0;
			}
			if(pt[i] == '<') ++lev;
			
			if(lev && pt[i] == '"') { 
				isStr ^= 1;
			}
			if(lev && i + 3 < len && pt[i] == 'h' && pt[i+1] == 'r' && pt[i+2] == 'e' && pt[i+3] == 'f') {
				SetPenColor("DarkBlue");
				ret[0] = 'h'; ret[1] = 'r'; ret[2] = 'e', ret[3] = 'f'; ret[4] = 0;
				DrawTextString(ret);
				SetPenColor("Black");
				i += 3;
				continue;
			}
			if(lev && (isStr || pt[i] == '"')) SetPenColor("Brown");
			else if(lev) SetPenColor("DarkGreen");
			if(pt[i] == '>') --lev;
			DrawTextString(ret);
			SetPenColor("Black");
		}
		y -= CODEHEI;
		MovePen(x, y);
	}
	
	free(pt);
	pt = 0;
}

void drawHtml(string fname) {
	hyperCnt = 0;
	px = RBEGINX, py = RBEGINY;
	MovePen(px, py); 
	SetFont(RFONT);
	p = fspt;
	while(*p && *(p++) != '>'); // è·³è¿‡<!DOCTYPE html>
	 
	enum Tag fir = getTag();
	assert(fir == Html); // ç¬¬ä¸€ä¸ªtagå¿…é¡»æ˜¯<html>
	parse(fir);
}


