/*在32bit图形模式下使用二维结构画点，以（300，200）为左上角，以（500，350）
为右下角画一个实心的白色矩形*/ 
#include<stdio.h>
#include<graphics.h>
typedef struct{
	char blue;
	char green;
	char red;
	char zero;
}RGB;
void rgbfilling(){
	int driver=0,mode=VESA_1024*768*32 bit;
	int x,y;
	RGB c={0xFF,0xFF,0xFF,0x00};
	RGB (*p)[1024];
	initgraph(&driver,&mode,"");
	p=(RGB(*)[1024])_vp;
	for(y=200;y<=350;y++){
		for(x=300;x<=500;x++){
			p[y][x]=c;
		}
	}
	getchar();
	closegraph(); 
}
 

