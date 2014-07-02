//==========================================
// Filename:
//      ex01.c
//
// Description:
//      This file is used to sort
//
// Author/Created Date:
//      jimmy jiang, 6.26'14
//--------------------------------------------------------------------------------------
// Include Files
//--------------------------------------------------------------------------------------
#include <stdio.h>

//-----------------------------------------------------------------
// DEFINES
//-----------------------------------------------------------------
#define BITSPERWORD 32  
#define SHIFT 5  
#define MASK 0x1F  
#define N 10000000 	
int a[1 + N/BITSPERWORD];  //申请内存的大小 

//-----------------------------------------------------------------

//----------------------------------------------------------------------------
void set(int n) 
{        
      a[n>>SHIFT]=a[n>>SHIFT]|(1<<(n&MASK));  //set 设置所在的bit位为1
}  

void clr(int n) 
{        
      a[n>>SHIFT]=a[n>>SHIFT]&(~(1<<(n&MASK)));  //clr 初始化所有的bit位为0
}  

int  test(int n)
{     
      return a[n>>SHIFT]&(1<<(n&MASK)); //test 测试所在的bit为是否为1
} 

int main(int argc, char *argv[])  
{   
    int i,n;
    FILE *fp;  
    for (i=0;i<=N;i++) 
        	clr(i);
	if((fp=fopen("argv[1]","r"))==NULL)
	{
		printf("Cannot open fire %s",argv[1]);
		getch();
		exit(1);
	}
    while(!feof(fp))
	{
		fscanf(fp,"%d",&n);  //  读出的值在n里
		set(n);
	}
		fclose(fp);
    for (i = 0;i<=N; i++)  
        	if (test(i))  
                printf("%d\n", i);  
                return 0;  
}

