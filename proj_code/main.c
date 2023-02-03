#include"interface.c"
#define MY_ROTATE_TIMER  1// 旋转计时器

void Main() 
{	
    int i;
	SetWindowSize(20, 10);
	SetWindowTitle("简易浏览器");  
    InitGraphics();
    winwidth = GetWindowWidth();
	winheight = GetWindowHeight(); 
	for (i=0;i<15;i++){
		 initialization(i);
	}
	// 注册时间响应函数
	registerCharEvent(CharEventProcess);        // 字符
	registerKeyboardEvent(KeyboardEventProcess);// 键盘
	registerMouseEvent(MouseEventProcess);      // 鼠标
	registerTimerEvent(TimerEventProcess);      // 定时器
 
	// 开启定时器
	//startTimer(MY_ROTATE_TIMER, 50);      //设置旋转三角形的定时器的类型为1         
	// 打开控制台，方便用printf/scanf输出/入变量信息，方便调试
	// InitConsole(); 
	
} 
