//���ļ�������ȫ�ֱ�����������ÿ����ҳ����Ϣ 
#ifndef _GLOBALHTML_
#define _GLOBALHTML_
#include<string.h>
struct label{
	char labelname[15];
	char labelurl[20];	
	char isParsing;
	struct label *next,*previous;
}*labels[15],*plabel=NULL,*pp;


extern int UseHelpFlag;
int nowlabel=0;
extern char reinterfacehtml[80];

void initialization(int n){
	labels[n] = (struct label *)malloc(sizeof(struct label));
	labels[n]->isParsing = 0;
//struct label *p1=labels[n],*p2=labels[n];
//while (p1->previous!=NULL)  ԭ�����ͷ��ڴ� 
	strcpy(labels[n]->labelname,"google");
	strcpy(labels[n]->labelurl,"google.html");
	UseHelpFlag=5;
	strcpy(reinterfacehtml,"��Google����������������һ����ַ");
	labels[n]->next=NULL;
	labels[n]->previous=NULL;
}

#endif
