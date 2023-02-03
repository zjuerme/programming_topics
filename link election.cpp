#include <stdio.h>
#include <stdlib.h>
typedef struct node    /*这个结构类型包括三个域 */
{	int number;        /*猴子的编号*/
	int mydata;        /* 猴子的定数 */
	struct node *next; /* 指向下一只猴子的指针 */
}linklist;

linklist *CreateCircle(int n){
    linklist *head,*p,*s; 
	int i;
    	        
	head =(linklist*)malloc(sizeof(linklist)); /*首节点创建*/
	p = head;
	p->number = 1;
	scanf("%d",&p->mydata); /* 定数(正整数)，确定下一只出局的猴子*/
	p->next = NULL;
	
	/*链表创建*/
	for(i=2;i<=n;i++){
		s = (linklist*)malloc(sizeof(linklist));
		s->number = i;
		scanf("%d",&s->mydata); /* 定数(正整数)，确定下一只出局的猴子*/
		p->next = s;
		p = s;
	}
	
	/*链表首尾相接构成循环链表*/
	p->next=head;
	return p;  /* 返回最后一只猴子的指针，因为它指向第一只猴子 */
}
 
linklist *DeleteNext(linklist *p)    /* 删除单循环链表的p所指的下一个结点 */
{       linklist   *s;
         if ( p && p->next!=p) {       
               s = p->next;           /*s指向p所指的下一个结点  */
               p->next = s->next;     /*从链表中删除*/
               free(s);               /*释放被删除结点 */
               return p;
         }else if(p){             /* 若单循环链表只有一个结点 */
               free(p);
               return NULL;
         }else 
               return NULL;
}

int KingOfMonkey(int n,linklist *head){
    linklist *p = head;
    int i, j, steps = p->mydata;       /* 用最后一只猴子的定数开始 */ 
	for(j=1;j<=n-1;j++){   /*重复该过程n-1次*/ 
	    for(i=1;i<steps;i++){
	        p=p->next;
		}
	
	    /* 将p所指的下一个节点删除, 删除前取其定数 */
        steps = p->next->mydata; 
		printf(" %d ", p->next->number);
		DeleteNext(p);
	}   
    return p->number;
 } 

int main(){
	linklist *head;
	int n;
	printf("请输入猴子的总数和每只猴子的定数(必须是正整数)：");
	scanf("%d",&n); 

	if(n>0){    
		head = CreateCircle(n);
		printf("\nThe king is monkey[%d].\n", KingOfMonkey(n,head));
	}else
         printf("猴子数量应该大于 0 !");
	return 0;
}
