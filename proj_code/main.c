#include"interface.c"
#define MY_ROTATE_TIMER  1// ��ת��ʱ��

void Main() 
{	
    int i;
	SetWindowSize(20, 10);
	SetWindowTitle("���������");  
    InitGraphics();
    winwidth = GetWindowWidth();
	winheight = GetWindowHeight(); 
	for (i=0;i<15;i++){
		 initialization(i);
	}
	// ע��ʱ����Ӧ����
	registerCharEvent(CharEventProcess);        // �ַ�
	registerKeyboardEvent(KeyboardEventProcess);// ����
	registerMouseEvent(MouseEventProcess);      // ���
	registerTimerEvent(TimerEventProcess);      // ��ʱ��
 
	// ������ʱ��
	//startTimer(MY_ROTATE_TIMER, 50);      //������ת�����εĶ�ʱ��������Ϊ1         
	// �򿪿���̨��������printf/scanf���/�������Ϣ���������
	// InitConsole(); 
	
} 
