//==========================================
// Filename:
//      ex03.c
//
// Description:
//      This file is used to manage employee information
//
// Author/Created Date:
//      jimmy jiang, 7.15'14
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

//-----------------------------------------------------------------
// DEFINES
//-----------------------------------------------------------------
#define LEN sizeof(struct student)

struct student
{
    long num;                
    char name[128]; 
    char sex;
    int  age;       	
    struct student *next;    
};
int n=0;
//-----------------------------------------------------------------

//-----------------------------------------------------------------
struct student *link_creat()     //创建链表
{
	struct student *head;
	struct student *p1;
	struct student *p2;
	head=NULL;
	
	

	p2=p1=(struct student *)malloc(LEN);
	printf("请输入学号 名字 性别 年纪\n");
	scanf("%ld %s %c %d",&p1->num,p1->name,&p1->sex,&p1->age);
	while((*p1).num!=0)   //判断输入的信息是否为空，可以用来结束输入
	{
	  
		n=n+1;
		if(n == 1)    //需要将头指向第一个节点
		{
				head=p1;
				//p1->next=NULL;
		}
		else
		{
				p2->next=p1; //将上一个节点指向下一个新申请的节点
		}
		p2=p1;
		p1=(struct student *)malloc(LEN);//申请内存
		printf("请输入学号 名字 性别 年纪\n");
		printf("输入0退出输入\n");
		scanf("%ld %s %c %d",&p1->num,p1->name,&p1->sex,&p1->age);
		//scanf("%*[^\n]");
		//scanf("%*c");
		printf("........\n");
	}
        p2->next=NULL; //将最后一个节点指向空
        return head;   //返回头
}

struct student *link_printf(struct student *head)   //打印链表信息
{
	 struct student *p;
	 p=head;
	 if(head==NULL)   //判断是否为空链表
	 {
	       printf(" 链表为空！\n");
	       return head;
	 }
	 else
	 {
	 	printf("记录分别为\n");
	        while(p!=NULL)
	        {
	        	printf("%ld %s %c %d\n",(*p).num,(*p).name,p->sex,p->age);
	        	p=p->next;
	        }     
	 }

}


struct student *link_del( struct student *head,int num)// 删除链表信息
{
	struct student *p1;
	struct student *p2;
	if (head==NULL)    //判断是否为空链表
	{
	 	printf("error\n");
	 	return head;
	}
	p1=head;
	while(p1->num!=num && p1->next!=NULL) //遍历
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
  	printf("\n delete success!\n");
  	n=n-1;
 	}
  	else
  	{
  		printf("not find\n");
  	}
  	return head;
}
  
struct student *link_insert(struct student *head,struct student *p0)//信息插入
{       
	struct student *p1;
	struct student *p2;
	p1=head;
	if(head==NULL)  //判断是否是空
	{
	 	p0=head;
  		p0->next=NULL;
	}
	else
	{

  		while((p0->num > p1->num)&&(p1->next!=NULL))
  		{
  			p2=p1;
  			p1=p1->next;
  		}
  		if(p0->num <= p1->num)
  		{ 
     			if(p1==head)
     			{
     				head=p0;
     			}
  			else
  			{
  				p2->next=p0;
 			}
  				p0->next=p1;
  		}
  		else
  		{
  			p1->next=p0;
  			p0->next=NULL;
  		}

	}
	n=n+1;
	printf(" 插入成功 \n");
	return head;
}

int main(void)
{
	struct student *head;
	struct student *p0;
	int num; 
	printf("\n"); 
	printf("\n");              
	printf("\n/////////学生信息系统/////////\n");
	head=link_creat();
	link_printf(head);
	printf("输入要删除的学号\n");
	scanf("%d",&num);   
	printf("..........\n");
	head=link_del(head,num);
	p0=(struct student *)malloc(LEN);
	printf("请输入学号 名字 性别 年纪\n");
	scanf("%ld %s %c %d",&p0->num,p0->name,&p0->sex,&p0->age);
	head=link_insert(head,p0);
	link_printf(head);
	free(p0);
	return 0;	
}

