/*
 * file name: ex03.c
 * Description: use linklist to realize employees basic information management system
 * creator: Allan xing
 * create time: 2012-09-25
 */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//staff basic information
struct staff
{
	char name[20];
	char num[10];
	int  age;
	char sex;
	struct staff *next;
};

struct staff *head,*p1,*p2;
int n;

//create and add into information to the linklist
struct staff* create()
{
	p1=(struct staff*)malloc(sizeof(struct staff));
	if(p1==NULL)
	{
		printf("create error! resart again!\n");
		return NULL;
	}
	else
	{
		printf("Please input number: ");
		scanf("%s",p1->num);
		printf("Please input name: ");
		scanf("%s",p1->name);
		printf("Please input sex(male=m female=f): ");
		getchar();
		scanf("%c",&p1->sex);
		while(!(((p1->sex)=='f')||((p1->sex)=='m')))
		{
			getchar();
			printf("Input error!!Please input again:\n");
			printf("Please input sex(male=m female=f): ");
			scanf("%c",&p1->sex);
		}
		printf("Please input age: ");
		scanf("%d",&p1->age);
		while(p1->age <= 0 || p1->age > 200)
		{
			printf("Input the age error!!Please input again:\n");
			printf("Please input age: ");
			scanf("%d",&p1->age);
		}
	}

	if(head==NULL)
	{
		head=p1;
		p1->next=NULL;
	}
	else
	{
		p1->next=head;
		head=p1;
	}
	return head;
}

//print the list of staff information
struct staff* print_list(struct staff* head)
{
	struct staff *p;
	p=head;
	if(p==NULL)
	{
		printf("No records!!\n");
	}
	else
	{
		printf("----------------------------------\n");
		printf(" Number   Name     Sex      Age\n");
		printf("----------------------------------\n");
		while(p!=NULL)
		{
			printf("%2s %10s %6c %9d\n",p->num,p->name,p->sex,p->age);
			p=p->next;
		}	
			printf("==================================\n");
			printf("the n is %d\n",n);
	}
}

//delete a staff information
struct staff *del(struct staff *head,char index[10])
{
	if(head == NULL)
	{
		printf("Error,there is no information!!\n");
		return head;
	}
	p1 = head;
	while((strcmp(p1->num,index)!=0) && p1->next != NULL)
	{
		p2 = p1;
		p1 = p1->next;
	}
	if((strcmp(index,p1->num)==0))
	{
		if(p1 == head)
		{
			head = p1->next;
		}
		else
		{
			p2->next = p1->next;
		}
		free(p1);
		p1 = NULL;
		printf("Delete %s success!\n",index);
		n -=1;
	}
	else
	{
		printf("There is not number[%s] staff information!\n",index);
	}
	return head;
}

int main(void)
{
	n = 0;
	char ch;
	char no[10];
	head=NULL;
	while(1)
	{
		printf("1: Input a staff record\n2: Output all datas\n3: Delete the staff information\n0: Exit\n");
		printf("----------------------------------\n");
		printf("^-^Please choose: ");
		scanf("%c",&ch);
		if(ch=='1')
		{ 
			n++;           
			create();
		}
		else if(ch=='2')
		{
			print_list(head);
		}
		else if(ch == '3')
		{
			printf("Input the num you want to delete:");
			scanf("%s",no);
			del(head,no);
		}
		else
			break;
		getchar();
	}
	return 0;
}
