#include <stdio.h>
#include <stdlib.h>
#define LEN sizeof(struct student)

struct student
{
    long num;                
    char name[128];           
    struct student *next;    
};
int n=0;

link_creat()
{
	struct student *head;
	struct student *p1;
	struct student *p2;
	head=NULL;
	
	

	p2=p1=(struct student *)malloc(LEN);
	printf("请输入员工XINXI\n");
	scanf("%ld %s\n",&p1->num,p1->name);
	//scanf("%*[^\n]");
	//scanf("%*c");

	while((*p1).num!=0)
	{
	  
		n=n+1;
		if(n == 1)
		{
				head=p1;
				//p1->next=NULL;
		}
		else
		{
				p2->next=p1;
		}
		p2=p1;
		p1=(struct student *)malloc(LEN);
		printf("请输入员工的信息\n");
		scanf("%ld %s\n",&p1->num,p1->name);
		//scanf("%*[^\n]");
		//scanf("%*c");
		printf("........\n");
	}
        p2->next=NULL;
        return head;
}

link_printf(struct student *head)
{
	 struct student *p;
	 p=head;
	 if(head==NULL)
	 {
	       printf(" 链表为空！\n");
	       return -1;
	 }
	 else
	 {
	 	printf("记录分别为\n");
	        while(p!=NULL)
	        {
	        	printf("%ld %s",(*p).num,(*p).name);
	        	p=p->next;
	        }     
	 }

}


link_del( struct student *head,long num)
{
  struct student *p1;
  struct student *p2;
 if (head==NULL)
 {
 	printf("error\n");
 	return head;
 }
  p1=head;
  while(p1->name!=num && p1->next!=NULL)
  {
  	p2=p1;
  	p1=p1->next;
  }
  
  if(num == p1->num)
  {
  	if (p1==head)
  	{
  		head=p1->next;
  	}
  	else
  	{
  		p2->next=p1->next;
  	}
  	free(p1);
  	p1=NULL;
  	printf("\n delete success!\n");
  	n=n-1;
  }
  else
  {
  
  	printf("not find\n");
  }
  return head;
}
int main(void)
{
	struct student *head;
	int num;                
	printf("/////////dang an lu lu xi tong/////////\n");
	head=link_creat();
	link_printf(head);
	printf("which one delete\n");
	scanf("%ld",&num);
	head=link_del(head,num);
	link_printf(head);
	return 0;
	
}


