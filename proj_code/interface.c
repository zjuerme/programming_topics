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


static double winwidth, winheight;   // 窗口尺寸

static char interfacehtml[80]="google";//网址输入框中的内容

char reinterfacehtml[80]="在Google上搜索，或者输入一个网址";//网址输入框中的内容

static int  MYFOREPOINTSIZE;//初始大小 
int UseHelpFlag=0;//如果使用了帮助菜单为正整数，没使用为0
int TranslationFlag=0; //0表示不翻译
int DefineTranslationFlag=0;//0表示关闭自动翻译
int ColorTheme=0;//0表示默认浏览器皮肤
extern int nowlable;
extern char *fspt;

void DisplayClear(void);//初始化主页 
int labelstate=0;
int isFirRun = 1;
char * selectedLabel = NULL;
int SearchFlag=1;//判断搜索哪个，1表示上方搜索框，0表示主页的搜索框 

// 显示
void display()
{
/*	if (isFirRun)
	{
		initialization(nowlabel);//provided in inteface.h.初始化可能后面不需要了 
		isFirRun = !isFirRun;
	}*/
	
	
	/*
	if (gs_UIState.mousedown == 0)
	{
		return;
	}*/
	//清屏 
	DisplayClear();
	drawLabels();
	MYFOREPOINTSIZE=GetPointSize();//使界面按钮大小不随html中字体大小不同而改变 
	//放大镜的图像
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
			//底色 
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
			//网页解析 
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


	//复原 
	SetPointSize(MYFOREPOINTSIZE);
	SetStyle(0);
	DefineColorTheme();//设置主题色 
	drawButtons();
	drawTextIn();
	drawMenu();

	//后退的图像 
	SetPenColor("Green");
	MovePen(18.7,9.35); 
	DrawLine(-0.15,0); 
	DrawLine(0,0.07); 	
	DrawLine(-0.13,-0.13);
	DrawLine(0.13,-0.13); 
	DrawLine(0,0.07);
 	DrawLine(0.15,0); 
	DrawLine(0,0.11); 
	
	//前进的图像 
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
//网页解析 
char oldUrl[1024] = "",oldUrl2[1024]="";

void HtmlAnalyse(){
//	if (0 != strcmp(oldUrl, labels[nowlabel].labelurl))//避免重复打开，造成卡顿 
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
		//分割线
		SetPenColor("Brown");
		MovePen(10.4,0.5);
		DrawLine(0,8);
	}
	if (labelstate)
	selectedLabel="加载成功"; 
    // freeFileStr();
} 

// 计时器
void TimerEventProcess(int timerID){	
	if ( timerID==1){
		display();
	}
}

// 字符事件
void CharEventProcess(char ch){
	uiGetChar(ch); // GUI字符
	display();
}

// 键盘事件
void KeyboardEventProcess(int key, int event){
	uiGetKeyboard(key,event); // GUI获取键盘
	display(); 
}

// 鼠标事件
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI获取鼠标
	ClickHyper(x,y,button,event); //超链接
	//if(UseHelpFlag==5){
	SearchWhich(x,y,button,event);//判断搜索框		
	//}
	display();
}


// 菜单演示程序
void drawMenu(){   
	double fH = GetFontHeight();
	double y = winheight-0.95;
	double h = fH*1.5; // 控件高度
	static int selection;
	
	static char * menuColorTheme[] = {"主题",  
		"经典原色",
		"清新水粉",
		"阳光明媚",
		"缤纷果盘",
		"摩登时代"};
	static char * menuTool[] = {"工具",
		"请使用F5刷新",
		"自动解析|Ctrl-R",
		"退出|Ctrl-E"};
	/* 
	static char * menuColorTheme[] = {"经典原色",
		"清新水粉",
		"阳光明媚",
		"缤纷果盘"};
	*/
	static char * menuHelp[] = {"帮助",
		"关于我们|Ctrl-W",
		"使用帮助|Ctrl-H", 
		"想要更多|Ctrl-C"};
	static char * menufavourite[] = {"收藏夹",
		"home",
		"example",
		"北京大学",
		"浙江大学",
		"CMU",
		"菜鸟"};
	
	double w = TextStringWidth(menuHelp[0])*2; // 控件宽度
	double wlist = TextStringWidth(menuTool[3])*1.2;
	drawMenuBar(0,y-h,winwidth,h);
	// Theme 菜单
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
	
	// Tool 菜单
	menuTool[2] = (DefineTranslationFlag==0) ? "自动解析|Ctrl-R" : "取消自动解析|Ctrl-R";
	selection = menuList(GenUIID(0),w,  y-h, w, wlist*1.4,h, menuTool,sizeof(menuTool)/sizeof(menuTool[0]));
	if( selection>0 ) {
	selectedLabel = menuTool[selection];
    labelstate=0;
    }
	if( selection==1 ){
		//refresh(0,0,5,5);  
		//DisplayClear();//全清 
		//DisplayClear();//清屏两次，增加延迟	
	}
	if( selection==2 ){	
		DefineTranslationFlag=!DefineTranslationFlag;
	}
	if( selection==3 )
		exit(-1); 
	/*二级菜单的尝试 
	if( selection==3 ){	
		selection = menuList(GenUIID(0), x+3*w, y-3*h, w, wlist, h, menuColorTheme, sizeof(menuColorTheme)/sizeof(menuColorTheme[0]));
		if( selection>0 ) selectedLabel = menuColorTheme[selection];
		if( selection==1 )
		exit(-1); 
	}*/

	
	// Help 菜单
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
		
	// Fovourite 收藏夹 
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
		strcpy(interfacehtml,"北京大学.html");
		DoSearch();
	}
	if( selection==4 ){
		strcpy(interfacehtml,"浙江大学.html");
		DoSearch();
	}
	if( selection==5 ){
		strcpy(interfacehtml,"CMU.html");
		DoSearch();
	}
	if( selection==6 ){
		strcpy(interfacehtml,"菜鸟.html");
		DoSearch();
	}
	
		
	// 状态栏 
	SetPenColor("Red");
	drawLabel(0.5,0.5, "status:");
	SetPenColor("Gray");
	drawLabel(1.5,0.5, selectedLabel);
}


// 按钮演示程序
void drawButtons(){// 控件高度
	double fH = GetFontHeight();
	double x = winwidth/2.5;  
	double y = winheight-0.4-0.5; 
	double w = x/2; // 控件宽度
	
	drawLabel(1, y+0.1, "输入网址"); 
	//if( button(GenUIID(0), 18, y, 0.5, 0.4, "退出") )
		//exit(-1);

	if( button(GenUIID(0), 17, y, 0.5, 0.4, "搜索") ){//按下回车搜索，在imgui.c的第210行实现 
        selectedLabel = "加载";
        labelstate=1; 
		DoSearch();
	}
	//后退的按钮 
	if(labels[nowlabel]->previous!=NULL){
	
	if( button(GenUIID(0), 18.3, y, 0.5, 0.4, "") ){

		    labels[nowlabel] = labels[nowlabel]->previous;
			UseHelpFlag=0; 
			labelstate=1;
		    selectedLabel="后退"; 
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
	//前进的按钮
	if(labels[nowlabel]->next!=NULL)	{
	if( button(GenUIID(0), 19, y, 0.5, 0.4, "") ){
		    labels[nowlabel]=labels[nowlabel]->next;
		    UseHelpFlag=0; 
		    labelstate=1;
		    selectedLabel="前进";
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
	//解析的按钮
	if(UseHelpFlag==0){
		if( button(GenUIID(0), 9, 8, 1, 0.4, "点击解析") ){
			// TranslationFlag=1;
			labels[nowlabel]->isParsing = 1;
			selectedLabel = "加载";
		    labelstate=1; 
		}	
	} 	
}

// 按钮演示程序
void drawLabels()
{
	int i,j;
	double fH = GetFontHeight();
	double h = fH*2;  // 控件高度  
	double y = winheight-h; 
	double w1 = (winwidth-3/2*h)/5;//标签宽度 
	double w2 = h; // +宽度
	double w3 = fH;
	static labelnumber = 1;  //标签数量 
	char* Font=GetFont();    //储存之前字体 
	static struct label{          //网页链表 
		char* web,title;//储存网址
		bool ifnow;	
	}  labellist[15];
	if (labelnumber>=5) w1=(winwidth-3/2*h)/labelnumber;
	  else w1 = (winwidth-3/2*h)/5;

	SetFont("Times");      //调整字体 
	setButtonColors ("White", "Gray", "Gray", "Black", 1);//初始button 
	if (button(GenUIID(0), w1*labelnumber, y, w2, h, "+"))
		{
			labelnumber++;
			nowlabel=labelnumber-1;			
		
			initialization(nowlabel);
			strcpy(interfacehtml,"google");
			strcpy(reinterfacehtml,"在Google上搜索，或者输入一个网址");
        }
 
     for (i=0;i<labelnumber;i++)
         if (button(GenUIID(i), (i)*w1, y, w1, h,labels[i]->labelname)){ //blank处应该用title 
         	UseHelpFlag = 0;
         	if (fspt != NULL)
         	{
         		freeFileStr();
         	}
           nowlabel=i;
           strcpy(interfacehtml,labels[nowlabel]->labelurl);
           strcpy(reinterfacehtml,"在Google上搜索，或者输入一个网址");
           //web写入
		 }
	 for (i=0;i<labelnumber;i++)
         if (button(GenUIID(i), (i+1)*w1-1.5*w3, y+w3/2, w3, w3, "×")){ 
          	  for (j=i;j<labelnumber-1;j++){
          	  	    strcpy(labels[j]->labelname,labels[j+1]->labelname);   // 改写title的顺序 
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
	SetFont(Font);  //还原字体
}

// 输入框,一般行距0.5 
void drawTextIn()
{
	double y = winheight-0.9;
	textbox(GenUIID(0), 3 , y , 13 , 0.4 , interfacehtml, sizeof(interfacehtml));
}

void HelpSwitchOne(){
	drawLabel(2,8, "该简易浏览器由浙江大学程序设计专题，张彤彧老师，李宗宜助教班级的xxx,xxx,xx三位同学合作开发");
	drawLabel(2,7,"浏览器基于libgraphics和simpleGUI，能够进行检索、展示、传递Web信息；借助超链接（Hyperlinks），实现互相关联的信息的浏览。" );
}
void HelpSwitchTwo(){
	drawLabel(3,8,"以下是对这个简易浏览器基本功能的一些说明"); 
	drawLabel(3,7.5, "点击收藏夹中，你可以快速访问已经存储的网页");
	SetPenColor("Maroon");
	drawLabel(3,7, "按照题目要求，本浏览器只需要进行本地的html文件的搜索和解析（如果需要上网，必须调用C++的库）");
	SetPenColor("MediumVioletRed");
	drawLabel(3,6.5, "你可以在输入框中输入网页的地址，点击搜索或者按下回车搜索跳转网页");
	drawLabel(3,6, "按下F5可以刷新网页");
	drawLabel(3,5.5, "按下“解析”，解析html文件，或者在工具一栏中点击“自动解析”，之后网页的解析都将自动完成,你也可以使用Ctrl+或关闭自动解析");
	drawLabel(3,5,"你可以在主题工具栏中换取你想要的皮肤颜色，具体包括“经典原色”，“清新水粉”，“阳光明媚”，“缤纷果盘”");
	drawLabel(3,4.5,"有关于浏览器的进一步功能，你可以通过按下“+”按钮新建一个标签页，点击“X”按钮关闭标签页，点击标签页实现标签的跳转");
	drawLabel(3,4,"点击“<-”实现当前标签的后退，点击“->”实现当前标签的前进"); 
	drawLabel(3,3.5,"如果想要了解我们可以访问“帮助工具栏”或者按下“Ctrl+W”，如果想要获取更多信息，请按“Ctrl+C”与我们取得联系"); 
    drawLabel(3,3,"你可以使用菜单栏或者按下“Ctrl+E”退出浏览器"); 
    drawLabel(3,2.5,"如果想要了解大致的html解析的功能，可以点击‘收藏夹’中的‘example’"); 
}
void HelpSwitchThree(){
	drawLabel(2,8, "如果想要更多信息或者提供一些建议，可以与我们取得联系，TEL 0571-xxxxxx, Email xxxxxx@gmail.com,或者查看我们的github主页www.xxxx.com");
    drawLabel(2,7,"我们期待进一步优化我们的产品，以求更佳的用户体验，欢迎你的参与、交流与支持，万分感谢！"); 
}

//设置皮肤 
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
	//static char wrongurl[80];如果需要显示哪个网页无法输出，可以取消注释 
	//strcpy(wrongurl,interfacehtml);
	SetPointSize(35);
	SetPenColor("Black");
	SetFont("Times");
	drawLabel(7, 7, "嗯...无法访问此网页");
	SetPenColor("Gray");
	SetPointSize(20);
	drawLabel(7, 6, "似乎");
	SetPenColor("Black");
	//drawLabel(7.7, 6, wrongurl);
	drawLabel(7.7, 6, "你输入的网页");
	SetPenColor("Gray");
	//drawLabel(8.5+strlen(wrongurl)/6, 6, "关闭了连接");
	drawLabel(9.6, 6, "关闭了连接");
	SetPointSize(22);
	SetPenColor("Black");
	drawLabel(7, 5.5, "请尝试：");
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
	drawLabel(7.6, 5-0.15, "检查连接");
	SetPenColor("Navy");
	drawLabel(7.6, 4.5-0.15, "检查代防和防火墙？");
	drawLabel(7.6, 4-0.15, "运行Windows网络诊断?");
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

//判断在主页时，按照哪个框的内容进行搜索 
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
			strcpy(reinterfacehtml,"在Google上搜索，或者输入一个网址");
		}
		*/
	}
		
	/*角点 
	drawLabel(2.5, 8.5, "1111");
	drawLabel(16.5, 10, "2222");
	drawLabel(5, 3, "3333");
	drawLabel(15, 5, "4444");
	*/
}


//部分刷新 
void refresh(double x1, double y1,double x2, double y2){//（x1,y1）左下，（x2,y2)右下 
	x1 = ScaleXInches(x1);
	x2 = ScaleYInches(x2)+9.3;
	y1 = ScaleXInches(y1)+0.7;
	y2 = ScaleYInches(y2)-1.4;//坐标变换，否则（x1,y1）右下，（x2,y2)左下
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
		strcpy(reinterfacehtml,"在Google上搜索，或者输入一个网址");//初始化网址输入框中的内容
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
	
	//下方与上方重复，但是加上代码可以让报错和主页切换时减小出现“进行解析”这个按钮的概率 
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

