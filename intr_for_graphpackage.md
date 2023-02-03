# 图形包使用说明

## include(.h)

.h中一般放的是同名.c文件中定义的变量、数组、函数的声明，需要让.c外部使用的声明

.c文件一般放的是变量、数组、函数的具体定义

*$\textcolor{RubineRed}{exception}$异常处理

$\textcolor{RubineRed}{extgraph}$$\textcolor{blue}{重要}$：设置颜色、线条

$\textcolor{RubineRed}{graphics}$$\textcolor{blue}{重要}$：绘制函数

$\textcolor{RubineRed}{random}$随机数



## libgraphics

DisplayClear(）清屏



libgraphics 预定义的颜色名称

 *  DefineColor("Black", 0, 0, 0);
 *  DefineColor("Dark Gray", .35, .35, .35);
 *  DefineColor("Gray", .6, .6, .6);
 *  DefineColor("Light Gray", .75, .75, .75);
 *  DefineColor("White", 1, 1, 1);
 *  DefineColor("Brown", .35, .20, .05);
 *  DefineColor("Red", 1, 0, 0);
 *  DefineColor("Orange", 1, .40, .1);
 *  DefineColor("Yellow", 1, 1, 0);
 *  DefineColor("Green", 0, 1, 0);
 *  DefineColor("Blue", 0, 0, 1);
 *  DefineColor("Violet", .93, .5, .93);
 *  DefineColor("Magenta", 1, 0, 1);
 *  DefineColor("Cyan", 0, 1, 1);

## imgui.c

inBox(double x, double y, double x1, double x2, double y1, double y2)是否在坐标范围内

颜色设置

setButtonColors(char *frame, char*label, char *hotFrame, char *hotLabel, int fillflag)

setMenuColors(char *frame, char*label, char *hotFrame, char *hotLabel, int fillflag)

setTextBoxColors(char *frame, char*label, char *hotFrame, char *hotLabel, int fillflag)

usePredefinedColors(int i)使用预定颜色方案

usePredefinedButtonColors(int k);
usePredefinedMenuColors(int k);
usePredefinedTexBoxColors(int k);



状态

uiGetMouse(int x, int y, int button, int event)

uiGetKeyboard(int key, int event)

uiGetChar(int ch)



button(int id, double x, double y, double w, double h, char *label)                 1表示按下了按钮

menuItem(int id, double x, double y, double w, double h, char *label)            1表示按下了按钮

menuList(int id, double x, double y, double w, double wlist, double h, char *labels[], int n)

$\textcolor{RubineRed}{textbox}$重点，去认真看看
