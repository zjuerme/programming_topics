/*��32bitͼ��ģʽ��ʹ�ö�ά�ṹ���㣬�ԣ�300��200��Ϊ���Ͻǣ��ԣ�500��350��
Ϊ���½ǻ�һ��ʵ�ĵİ�ɫ����*/ 
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
 

