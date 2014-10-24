//==========================================
// Filename:
//      ex02.c
//
// Description:
//      This file is used to count number of 1
//
// Author/Created Date:
//      jimmy jiang, 7.7'14
//--------------------------------------------------------------------------------------
// Include Files
//--------------------------------------------------------------------------------------
#include <stdio.h>
//-----------------------------------------------------------------

 int main()
{ int i;
  printf("please input a number\n");
  scanf("%d",&i);
  printf("%d\n",conut_number(i));
  return 0;
}

 int conut_number(int x)
{
		int count = 0;
		unsigned int flag = 1;
 		while(flag)
	    {
		 if(x & flag)              //做与的运算，来判断该位是否为1
  			count ++;
 			flag = flag << 1;  //向左移动一位
 	    }
        return count;
}
