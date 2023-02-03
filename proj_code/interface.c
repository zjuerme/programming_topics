/*this is the interface
  The coordinate system is set to Cartesian Cartesian coordinate system 
  according to libgraphics.c*/

#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include "imgui.h"
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#include "extgraph.h"
#include "htmlParser.h"
#include "interface.h"


static double winwidth, winheight;   // ���ڳߴ�

static char interfacehtml[80]="google";//��ַ������е�����

char reinterfacehtml[80]="��Google����������������һ����ַ";//��ַ������е�����

static int  MYFOREPOINTSIZE;//��ʼ��С 
int UseHelpFlag=0;//���ʹ���˰����˵�Ϊ��������ûʹ��Ϊ0
int TranslationFlag=0; //0��ʾ������
int DefineTranslationFlag=0;//0��ʾ�ر��Զ�����
int ColorTheme=0;//0��ʾĬ�������Ƥ��
extern int nowlable;
extern char *fspt;

void DisplayClear(void);//��ʼ����ҳ 
int labelstate=0;
int isFirRun = 1;
char * selectedLabel = NULL;
int SearchFlag=1;//�ж������ĸ���1��ʾ�Ϸ�������0��ʾ��ҳ�������� 

// ��ʾ
void display()
{
/*	if (isFirRun)
	{
		initialization(nowlabel);//provided in inteface.h.��ʼ�����ܺ��治��Ҫ�� 
		isFirRun = !isFirRun;
	}*/
	
	
	/*
	if (gs_UIState.mousedown == 0)
	{
		return;
	}*/
	//���� 
	DisplayClear();
	drawLabels();
	MYFOREPOINTSIZE=GetPointSize();//ʹ���水ť��С����html�������С��ͬ���ı� 
	//�Ŵ󾵵�ͼ��
	SetPenColor("Black");
	MovePen(2.5,9.3); 
	DrawArc(0.1, 0, 360);
	MovePen(2.45,9.25); 
	DrawLine(0.12,-0.12);	
	
	SetPenColor("MediumVioletRed");
	
	if(UseHelpFlag==0){
		if(strcmp(labels[nowlabel]->labelname,"google")==0){
			UseHelpFlag=5;
		}
		if(strcmp(labels[nowlabel]->labelname,"wrong")==0){
			UseHelpFlag=4;
		}	
	}
	

	switch(UseHelpFlag){
		case 0:
			//��ɫ 
			switch(ColorTheme){
				case 0:
					SetPenColor("WhiteSmoke");
					//SetPenColor("Beige"); 
					break;
				case 1:
					SetPenColor("Snow"); 
					break;
				case 2:
					SetPenColor("FloralWhite");
					break;
				case 3:
					SetPenColor("Honeydew");
					break;
				case 4:
					SetPenColor("GhostWhite");
					//SetPenColor("Lavender");
					break;
			}
			drawRectangle(1.1,0.8,9.2,8.2,1);
			drawRectangle(10.5,0.8,8.8,8.2,1);
			//��ҳ���� 
			HtmlAnalyse();
			break;
		case 1:
			HelpSwitchOne();
			break;
		case 2:
			HelpSwitchTwo();
			break;
		case 3: 
			HelpSwitchThree();
			break;
		case 4:
			Wrong_Site();
			break;
		case 5:
			DrawHome();
			break; 
	} 


	//��ԭ 
	SetPointSize(MYFOREPOINTSIZE);
	SetStyle(0);
	DefineColorTheme();//��������ɫ 
	drawButtons();
	drawTextIn();
	drawMenu();

	//���˵�ͼ�� 
	SetPenColor("Green");
	MovePen(18.7,9.35); 
	DrawLine(-0.15,0); 
	DrawLine(0,0.07); 	
	DrawLine(-0.13,-0.13);
	DrawLine(0.13,-0.13); 
	DrawLine(0,0.07);
 	DrawLine(0.15,0); 
	DrawLine(0,0.11); 
	
	//ǰ����ͼ�� 
	SetPenColor("Green");
	MovePen(19.11,9.35); 
	DrawLine(0.15,0); 
	DrawLine(0,0.07); 	
	DrawLine(0.13,-0.13);
	DrawLine(-0.13,-0.13); 
	DrawLine(0,0.07);
 	DrawLine(-0.15,0); 
	DrawLine(0,0.11);

}
//��ҳ���� 
char oldUrl[1024] = "",oldUrl2[1024]="";

void HtmlAnalyse(){
//	if (0 != strcmp(oldUrl, labels[nowlabel].labelurl))//�����ظ��򿪣���ɿ��� 
/*
	{
		if (fspt != NULL)
		{
			freeFileStr();
		}
		readHtml(labels[nowlabel].labelurl);
		strcpy(oldUrl, labels[nowlabel].labelurl);
	}
*/	
	if (fspt == NULL) readHtml(labels[nowlabel]->labelurl);
	drawCode();
	if(DefineTranslationFlag==1){
		TranslationFlag=1;
	}
	if(DefineTranslationFlag==1 || labels[nowlabel]->isParsing == 1){
		drawHtml();
		//�ָ���
		SetPenColor("Brown");
		MovePen(10.4,0.5);
		DrawLine(0,8);
	}
	if (labelstate)
	selectedLabel="���سɹ�"; 
    // freeFileStr();
} 

// ��ʱ��
void TimerEventProcess(int timerID){	
	if ( timerID==1){
		display();
	}
}

// �ַ��¼�
void CharEventProcess(char ch){
	uiGetChar(ch); // GUI�ַ�
	display();
}

// �����¼�
void KeyboardEventProcess(int key, int event){
	uiGetKeyboard(key,event); // GUI��ȡ����
	display(); 
}

// ����¼�
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI��ȡ���
	ClickHyper(x,y,button,event); //������
	//if(UseHelpFlag==5){
	SearchWhich(x,y,button,event);//�ж�������		
	//}
	display();
}


// �˵���ʾ����
void drawMenu(){   
	double fH = GetFontHeight();
	double y = winheight-0.95;
	double h = fH*1.5; // �ؼ��߶�
	static int selection;
	
	static char * menuColorTheme[] = {"����",  
		"����ԭɫ",
		"����ˮ��",
		"��������",
		"�ͷ׹���",
		"Ħ��ʱ��"};
	static char * menuTool[] = {"����",
		"��ʹ��F5ˢ��",
		"�Զ�����|Ctrl-R",
		"�˳�|Ctrl-E"};
	/* 
	static char * menuColorTheme[] = {"����ԭɫ",
		"����ˮ��",
		"��������",
		"�ͷ׹���"};
	*/
	static char * menuHelp[] = {"����",
		"��������|Ctrl-W",
		"ʹ�ð���|Ctrl-H", 
		"��Ҫ����|Ctrl-C"};
	static char * menufavourite[] = {"�ղؼ�",
		"home",
		"example",
		"������ѧ",
		"�㽭��ѧ",
		"CMU",
		"����"};
	
	double w = TextStringWidth(menuHelp[0])*2; // �ؼ����
	double wlist = TextStringWidth(menuTool[3])*1.2;
	drawMenuBar(0,y-h,winwidth,h);
	// Theme �˵�
	selection = menuList(GenUIID(0), 0, y-h, w, wlist, h, menuColorTheme, sizeof(menuColorTheme)/sizeof(menuColorTheme[0]));
	if( selection>0 ) {
	labelstate=0;
	selectedLabel = menuColorTheme[selection];
	}
	if( selection==1 ){
		ColorTheme=0;
	}
	if( selection==2 ){
		ColorTheme=1;
	}
	if( selection==3 ){
		ColorTheme=2;
	}
	if( selection==4 ){
		ColorTheme=3;
	}
	if( selection==5 ){
		ColorTheme=4;
	}
	
	// Tool �˵�
	menuTool[2] = (DefineTranslationFlag==0) ? "�Զ�����|Ctrl-R" : "ȡ���Զ�����|Ctrl-R";
	selection = menuList(GenUIID(0),w,  y-h, w, wlist*1.4,h, menuTool,sizeof(menuTool)/sizeof(menuTool[0]));
	if( selection>0 ) {
	selectedLabel = menuTool[selection];
    labelstate=0;
    }
	if( selection==1 ){
		//refresh(0,0,5,5);  
		//DisplayClear();//ȫ�� 
		//DisplayClear();//�������Σ������ӳ�	
	}
	if( selection==2 ){	
		DefineTranslationFlag=!DefineTranslationFlag;
	}
	if( selection==3 )
		exit(-1); 
	/*�����˵��ĳ��� 
	if( selection==3 ){	
		selection = menuList(GenUIID(0), x+3*w, y-3*h, w, wlist, h, menuColorTheme, sizeof(menuColorTheme)/sizeof(menuColorTheme[0]));
		if( selection>0 ) selectedLabel = menuColorTheme[selection];
		if( selection==1 )
		exit(-1); 
	}*/

	
	// Help �˵�
	selection = menuList(GenUIID(0),2*w,y-h, w, wlist*1.4, h, menuHelp,sizeof(menuHelp)/sizeof(menuHelp[0]));
	if( selection>0 ) {
	selectedLabel = menuHelp[selection];
    labelstate=0;
    }
	if( selection==1 ){
		UseHelpFlag=1; 
	}
	if( selection==2 ){
		UseHelpFlag=2; 
	}
	if( selection==3 ){
		UseHelpFlag=3; 
	}
		
	// Fovourite �ղؼ� 
	selection = menuList(GenUIID(0),winwidth-1.5*w,y-h, w, wlist, h, menufavourite,sizeof(menufavourite)/sizeof(menufavourite[0]));
	if( selection>0 ) {
	selectedLabel = menufavourite[selection];
    labelstate=0;
	}
	if( selection==1 ){
		strcpy(interfacehtml,"google.html");
		DoSearch();
	}
	if( selection==2 ){
		strcpy(interfacehtml,"example.html");
		DoSearch();
	}
	if( selection==3 ){
		strcpy(interfacehtml,"������ѧ.html");
		DoSearch();
	}
	if( selection==4 ){
		strcpy(interfacehtml,"�㽭��ѧ.html");
		DoSearch();
	}
	if( selection==5 ){
		strcpy(interfacehtml,"CMU.html");
		DoSearch();
	}
	if( selection==6 ){
		strcpy(interfacehtml,"����.html");
		DoSearch();
	}
	
		
	// ״̬�� 
	SetPenColor("Red");
	drawLabel(0.5,0.5, "status:");
	SetPenColor("Gray");
	drawLabel(1.5,0.5, selectedLabel);
}


// ��ť��ʾ����
void drawButtons(){// �ؼ��߶�
	double fH = GetFontHeight();
	double x = winwidth/2.5;  
	double y = winheight-0.4-0.5; 
	double w = x/2; // �ؼ����
	
	drawLabel(1, y+0.1, "������ַ"); 
	//if( button(GenUIID(0), 18, y, 0.5, 0.4, "�˳�") )
		//exit(-1);

	if( button(GenUIID(0), 17, y, 0.5, 0.4, "����") ){//���»س���������imgui.c�ĵ�210��ʵ�� 
        selectedLabel = "����";
        labelstate=1; 
		DoSearch();
	}
	//���˵İ�ť 
	if(labels[nowlabel]->previous!=NULL){
	
	if( button(GenUIID(0), 18.3, y, 0.5, 0.4, "") ){

		    labels[nowlabel] = labels[nowlabel]->previous;
			UseHelpFlag=0; 
			labelstate=1;
		    selectedLabel="����"; 
		    strcpy(interfacehtml,labels[nowlabel]->labelurl);
		    if (fspt != NULL)
		    {
		    	freeFileStr();
		    }
	
	}}else{
		MovePen(18.3,y);
		DrawLine(0.5,0);
		DrawLine(0,0.4);
		DrawLine(-0.5,0);
		DrawLine(0,-0.4);
	} 
	//ǰ���İ�ť
	if(labels[nowlabel]->next!=NULL)	{
	if( button(GenUIID(0), 19, y, 0.5, 0.4, "") ){
		    labels[nowlabel]=labels[nowlabel]->next;
		    UseHelpFlag=0; 
		    labelstate=1;
		    selectedLabel="ǰ��";
		    strcpy(interfacehtml,labels[nowlabel]->labelurl);
			if (fspt != NULL)
		    {
		    	freeFileStr();
		    }
	}
	}else{
		MovePen(19,y);
		DrawLine(0.5,0);
		DrawLine(0,0.4);
		DrawLine(-0.5,0);
		DrawLine(0,-0.4);
	} 
	//�����İ�ť
	if(UseHelpFlag==0){
		if( button(GenUIID(0), 9, 8, 1, 0.4, "�������") ){
			// TranslationFlag=1;
			labels[nowlabel]->isParsing = 1;
			selectedLabel = "����";
		    labelstate=1; 
		}	
	} 	
}

// ��ť��ʾ����
void drawLabels()
{
	int i,j;
	double fH = GetFontHeight();
	double h = fH*2;  // �ؼ��߶�  
	double y = winheight-h; 
	double w1 = (winwidth-3/2*h)/5;//��ǩ��� 
	double w2 = h; // +���
	double w3 = fH;
	static labelnumber = 1;  //��ǩ���� 
	char* Font=GetFont();    //����֮ǰ���� 
	static struct label{          //��ҳ���� 
		char* web,title;//������ַ
		bool ifnow;	
	}  labellist[15];
	if (labelnumber>=5) w1=(winwidth-3/2*h)/labelnumber;
	  else w1 = (winwidth-3/2*h)/5;

	SetFont("Times");      //�������� 
	setButtonColors ("White", "Gray", "Gray", "Black", 1);//��ʼbutton 
	if (button(GenUIID(0), w1*labelnumber, y, w2, h, "+"))
		{
			labelnumber++;
			nowlabel=labelnumber-1;			
		
			initialization(nowlabel);
			strcpy(interfacehtml,"google");
			strcpy(reinterfacehtml,"��Google����������������һ����ַ");
        }
 
     for (i=0;i<labelnumber;i++)
         if (button(GenUIID(i), (i)*w1, y, w1, h,labels[i]->labelname)){ //blank��Ӧ����title 
         	UseHelpFlag = 0;
         	if (fspt != NULL)
         	{
         		freeFileStr();
         	}
           nowlabel=i;
           strcpy(interfacehtml,labels[nowlabel]->labelurl);
           strcpy(reinterfacehtml,"��Google����������������һ����ַ");
           //webд��
		 }
	 for (i=0;i<labelnumber;i++)
         if (button(GenUIID(i), (i+1)*w1-1.5*w3, y+w3/2, w3, w3, "��")){ 
          	  for (j=i;j<labelnumber-1;j++){
          	  	    strcpy(labels[j]->labelname,labels[j+1]->labelname);   // ��дtitle��˳�� 
                    strcpy(labels[j]->labelurl,labels[j+1]->labelurl);
                }
           	    if (nowlabel>=i) nowlabel--;
           	  		labelnumber--;  
			    if (labelnumber==0) {
		            labelnumber++;
		            nowlabel=0;
		            initialization(nowlabel);
		    } 	      
		 }
	SetPenColor("Black");
	MovePen(0,y);
	DrawLine(20,0); 
	SetFont(Font);  //��ԭ����
}

// �����,һ���о�0.5 
void drawTextIn()
{
	double y = winheight-0.9;
	textbox(GenUIID(0), 3 , y , 13 , 0.4 , interfacehtml, sizeof(interfacehtml));
}

void HelpSwitchOne(){
	drawLabel(2,8, "�ü�����������㽭��ѧ�������ר�⣬��ͮ����ʦ�����������̰༶��xxx,xxx,xx��λͬѧ��������");
	drawLabel(2,7,"���������libgraphics��simpleGUI���ܹ����м�����չʾ������Web��Ϣ�����������ӣ�Hyperlinks����ʵ�ֻ����������Ϣ�������" );
}
void HelpSwitchTwo(){
	drawLabel(3,8,"�����Ƕ��������������������ܵ�һЩ˵��"); 
	drawLabel(3,7.5, "����ղؼ��У�����Կ��ٷ����Ѿ��洢����ҳ");
	SetPenColor("Maroon");
	drawLabel(3,7, "������ĿҪ�󣬱������ֻ��Ҫ���б��ص�html�ļ��������ͽ����������Ҫ�������������C++�Ŀ⣩");
	SetPenColor("MediumVioletRed");
	drawLabel(3,6.5, "��������������������ҳ�ĵ�ַ������������߰��»س�������ת��ҳ");
	drawLabel(3,6, "����F5����ˢ����ҳ");
	drawLabel(3,5.5, "���¡�������������html�ļ��������ڹ���һ���е�����Զ���������֮����ҳ�Ľ��������Զ����,��Ҳ����ʹ��Ctrl+��ر��Զ�����");
	drawLabel(3,5,"����������⹤�����л�ȡ����Ҫ��Ƥ����ɫ���������������ԭɫ����������ˮ�ۡ������������ġ������ͷ׹��̡�");
	drawLabel(3,4.5,"�й���������Ľ�һ�����ܣ������ͨ�����¡�+����ť�½�һ����ǩҳ�������X����ť�رձ�ǩҳ�������ǩҳʵ�ֱ�ǩ����ת");
	drawLabel(3,4,"�����<-��ʵ�ֵ�ǰ��ǩ�ĺ��ˣ������->��ʵ�ֵ�ǰ��ǩ��ǰ��"); 
	drawLabel(3,3.5,"�����Ҫ�˽����ǿ��Է��ʡ����������������߰��¡�Ctrl+W���������Ҫ��ȡ������Ϣ���밴��Ctrl+C��������ȡ����ϵ"); 
    drawLabel(3,3,"�����ʹ�ò˵������߰��¡�Ctrl+E���˳������"); 
    drawLabel(3,2.5,"�����Ҫ�˽���µ�html�����Ĺ��ܣ����Ե�����ղؼС��еġ�example��"); 
}
void HelpSwitchThree(){
	drawLabel(2,8, "�����Ҫ������Ϣ�����ṩһЩ���飬����������ȡ����ϵ��TEL 0571-xxxxxx, Email xxxxxx@gmail.com,���߲鿴���ǵ�github��ҳwww.xxxx.com");
    drawLabel(2,7,"�����ڴ���һ���Ż����ǵĲ�Ʒ��������ѵ��û����飬��ӭ��Ĳ��롢������֧�֣���ָ�л��"); 
}

//����Ƥ�� 
void DefineColorTheme(){
	switch(ColorTheme){
		case 0:
			Color_Oringal(); 
			break;
		case 1:
			Color_QingXing();
			break;
		case 2:
			Color_MingMei();
			break;
		case 3:
			Color_BinFeng();
			break;
		case 4:
			Color_Moden(); 
			break;
	}
}

void Wrong_Site(){
	//static char wrongurl[80];�����Ҫ��ʾ�ĸ���ҳ�޷����������ȡ��ע�� 
	//strcpy(wrongurl,interfacehtml);
	SetPointSize(35);
	SetPenColor("Black");
	SetFont("Times");
	drawLabel(7, 7, "��...�޷����ʴ���ҳ");
	SetPenColor("Gray");
	SetPointSize(20);
	drawLabel(7, 6, "�ƺ�");
	SetPenColor("Black");
	//drawLabel(7.7, 6, wrongurl);
	drawLabel(7.7, 6, "���������ҳ");
	SetPenColor("Gray");
	//drawLabel(8.5+strlen(wrongurl)/6, 6, "�ر�������");
	drawLabel(9.6, 6, "�ر�������");
	SetPointSize(22);
	SetPenColor("Black");
	drawLabel(7, 5.5, "�볢�ԣ�");
	SetPointSize(20); 
	MovePen(7.2,5);
	StartFilledRegion(1);
    DrawArc(0.025,0,360);
    EndFilledRegion();
    MovePen(7.2,4.5);
    StartFilledRegion(1);
    DrawArc(0.025,0,360);
    EndFilledRegion();
	MovePen(7.2,4); 
    StartFilledRegion(1);
    DrawArc(0.025,0,360);
    EndFilledRegion();
    SetPenColor("Gray");
	drawLabel(7.6, 5-0.15, "�������");
	SetPenColor("Navy");
	drawLabel(7.6, 4.5-0.15, "�������ͷ���ǽ��");
	drawLabel(7.6, 4-0.15, "����Windows�������?");
	SetPenColor("Gray");
	SetPointSize(12);
	drawLabel(7, 2.5, "ERR_CONNECTION_CLOSED");
	//SetPenColor("Black");//cloud 
	//MovePen(5,7.5);
    //DrawArc(0.05,0,360);
    //SetPenSize(20);
    //MovePen(5.2,8);
    //DrawArc(0.1,0,360);
}

void DrawHome(){
	int ix;
	int colorchoice=0;
	SetFont("Times");
	for(ix=-1;ix<=20;ix++){
		colorchoice=!colorchoice;
		if(colorchoice){
			switch(ColorTheme){
				case 0:
					SetPenColor("Azure"); 
					break;
				case 1:
					SetPenColor("LavenderBlush"); 
					break;
				case 2:
					SetPenColor("Linen"); 
					break;
				case 3:
					SetPenColor("MintCream");
					break;
				case 4:
					SetPenColor("WhiteSmoke");
					break;
			}	
		}
		else{
			switch(ColorTheme){
				case 0:
					SetPenColor("Ivory"); 
					break;
				case 1:
					SetPenColor("Snow"); 
					break;
				case 2:
					SetPenColor("MistyRose");
					break;
				case 3:
					SetPenColor("Honeydew");
					break;
				case 4:
					SetPenColor("AliceBlue");
					break;
			}
		}
		MovePen(ix, 0);
		StartFilledRegion(1);
		DrawLine(1,8.8);
		DrawLine(1,0);
		DrawLine(-1,-8.8);
		DrawLine(-1,0);
		EndFilledRegion();
	}
	SetPointSize(75);
	SetPenColor("Indigo");
	MovePen(8.4, 6);
	DrawTextString("Google");
	SetPointSize(MYFOREPOINTSIZE);
	textbox(GenUIID(0), 5.5 , 4 , 9 , 0.8 , reinterfacehtml, sizeof(reinterfacehtml)); 
}

//�ж�����ҳʱ�������ĸ�������ݽ������� 
void SearchWhich(int x,int y, int button, int event){
	double ix = ScaleXInches(x),iy = ScaleYInches(y);/*pixels --> inches*/	
	if(button==LEFT_BUTTON && event == BUTTON_DOWN){
		if(ix>=2.5&&ix<=16.5&&iy>=8.5&&iy<=9.6){
			SearchFlag=1;
			strcpy(interfacehtml,"");
		}
		else if(UseHelpFlag==5&&ix>=5&&ix<=15&&iy>=3&&iy<=5){
			SearchFlag=0;
			strcpy(reinterfacehtml,"");
		}
		/* 
		else{
			strcpy(interfacehtml,"enter the website!");
			strcpy(reinterfacehtml,"��Google����������������һ����ַ");
		}
		*/
	}
		
	/*�ǵ� 
	drawLabel(2.5, 8.5, "1111");
	drawLabel(16.5, 10, "2222");
	drawLabel(5, 3, "3333");
	drawLabel(15, 5, "4444");
	*/
}


//����ˢ�� 
void refresh(double x1, double y1,double x2, double y2){//��x1,y1�����£���x2,y2)���� 
	x1 = ScaleXInches(x1);
	x2 = ScaleYInches(x2)+9.3;
	y1 = ScaleXInches(y1)+0.7;
	y2 = ScaleYInches(y2)-1.4;//����任������x1,y1�����£���x2,y2)����
	SetEraseMode(TRUE);
	StartFilledRegion(1);
    MovePen(x1,y1);
    DrawLine(x2-x1, 0);
    DrawLine(0,y2-y1);
    DrawLine(x1-x2,0);
    DrawLine(0,y1-y2);
    EndFilledRegion();
    SetEraseMode(FALSE);		
	Pause(0.2);
}

void ClickHyper(int x,int y, int button, int event){
	double ix = ScaleXInches(x),iy = ScaleYInches(y);/*pixels --> inches*/	
	if(button==LEFT_BUTTON && event == BUTTON_DOWN){
		int i;
		for(i=1;i<=hyperCnt;i++){
		 	if(button==LEFT_BUTTON && event == BUTTON_DOWN&&ix>=hyperLink[i].x1&&ix<=hyperLink[i].x2&&iy>=hyperLink[i].y1&&iy<=hyperLink[i].y2){				
				strcpy(interfacehtml,hyperLink[i].url);
		 		DoSearch();
			}
		}	
	}
}

void DoSearch(){
	//SearchFlag==1; 
	if(SearchFlag==0){
		strcpy(interfacehtml,reinterfacehtml);
		strcpy(reinterfacehtml,"��Google����������������һ����ַ");//��ʼ����ַ������е�����
		SearchFlag=1;
	} 
	int len = strlen(interfacehtml);
	if (!(interfacehtml[len - 1] == 'l' && interfacehtml[len - 2] == 'm' && interfacehtml[len - 3] == 't' && interfacehtml[len - 4] == 'h' && interfacehtml[len - 5] == '.')) 
		{
			strcat(interfacehtml,".html");
		}

	if (fspt != NULL) freeFileStr();
	UseHelpFlag=0;
	readHtml(interfacehtml);
   	GettitleR();
   	insertLabel(nowlabel, titleR, interfacehtml);
	TranslationFlag=0;
	
	//�·����Ϸ��ظ������Ǽ��ϴ�������ñ������ҳ�л�ʱ��С���֡����н����������ť�ĸ��� 
	if(UseHelpFlag==0){
		if(strcmp(labels[nowlabel]->labelname,"google")==0){
			UseHelpFlag=5;
		}
		if(strcmp(labels[nowlabel]->labelname,"wrong")==0){
			UseHelpFlag=4;
		}	
	}
}

void freeList(struct label *head){
	struct label *p = head;
	while (p != NULL)
	{
		struct label *tmp = p;
		p = p->next;
		free(tmp);
	}
}

void insertLabel(int labelInd, char *labelname, char *labelurl){
	struct label *head = labels[labelInd];
	
	struct label *tmp = (struct label *)malloc(sizeof(struct label));
	strcpy(tmp->labelname, labelname);
	strcpy(tmp->labelurl, labelurl);
	tmp->isParsing = 0;
	tmp->previous = head;
	
	tmp->next = NULL;
	if (head->next != NULL)
	{
		freeList(head->next);
	}
	head->next = tmp;
	labels[labelInd] = tmp;
}

