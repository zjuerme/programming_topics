#include <stdio.h>
#include <stdlib.h>
typedef struct node    /*����ṹ���Ͱ��������� */
{	int number;        /*���ӵı��*/
	int mydata;        /* ���ӵĶ��� */
	struct node *next; /* ָ����һֻ���ӵ�ָ�� */
}linklist;

linklist *CreateCircle(int n){
    linklist *head,*p,*s; 
	int i;
    	        
	head =(linklist*)malloc(sizeof(linklist)); /*�׽ڵ㴴��*/
	p = head;
	p->number = 1;
	scanf("%d",&p->mydata); /* ����(������)��ȷ����һֻ���ֵĺ���*/
	p->next = NULL;
	
	/*������*/
	for(i=2;i<=n;i++){
		s = (linklist*)malloc(sizeof(linklist));
		s->number = i;
		scanf("%d",&s->mydata); /* ����(������)��ȷ����һֻ���ֵĺ���*/
		p->next = s;
		p = s;
	}
	
	/*������β��ӹ���ѭ������*/
	p->next=head;
	return p;  /* �������һֻ���ӵ�ָ�룬��Ϊ��ָ���һֻ���� */
}
 
linklist *DeleteNext(linklist *p)    /* ɾ����ѭ�������p��ָ����һ����� */
{       linklist   *s;
         if ( p && p->next!=p) {       
               s = p->next;           /*sָ��p��ָ����һ�����  */
               p->next = s->next;     /*��������ɾ��*/
               free(s);               /*�ͷű�ɾ����� */
               return p;
         }else if(p){             /* ����ѭ������ֻ��һ����� */
               free(p);
               return NULL;
         }else 
               return NULL;
}

int KingOfMonkey(int n,linklist *head){
    linklist *p = head;
    int i, j, steps = p->mydata;       /* �����һֻ���ӵĶ�����ʼ */ 
	for(j=1;j<=n-1;j++){   /*�ظ��ù���n-1��*/ 
	    for(i=1;i<steps;i++){
	        p=p->next;
		}
	
	    /* ��p��ָ����һ���ڵ�ɾ��, ɾ��ǰȡ�䶨�� */
        steps = p->next->mydata; 
		printf(" %d ", p->next->number);
		DeleteNext(p);
	}   
    return p->number;
 } 

int main(){
	linklist *head;
	int n;
	printf("��������ӵ�������ÿֻ���ӵĶ���(������������)��");
	scanf("%d",&n); 

	if(n>0){    
		head = CreateCircle(n);
		printf("\nThe king is monkey[%d].\n", KingOfMonkey(n,head));
	}else
         printf("��������Ӧ�ô��� 0 !");
	return 0;
}
