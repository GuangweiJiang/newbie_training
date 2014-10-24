#include <stdio.h>
#include <time.h>
int sort1()
{
	int a[7]={2,4,1,8,3,9,5};
	int i,p,tmp;
	for (i=1;i<7;i++)
	{
		tmp=a[i];
		p=i-1;
		while (tmp<a[p]&&p>=0)
		{
			a[p+1]=a[p];
			p--;
		}	
		a[p+1]=tmp;
	}
	for(i=0;i<7;i++)
	{
		printf("%d\n",a[i]);
	}
	return 0;	
}

int sort2()
{
	int a[7]={2,4,1,8,3,9,5};
	int i,p,tmp;
	for (i=1;i<7;i++)
	{
		tmp=a[i];
		p=i-1;
		while (tmp<a[p]&&p>=0)
		{
			a[p+1]=a[p];
			p--;
		}	
		a[p+1]=tmp;
	}
	for(i=0;i<7;i++)
	{
		printf("%d\n",a[i]);
	}
	return 0;	
}


main()
{	int a;
	double duration;
	clock_t start,finish;
	printf("please input number:1 or 2 \n");
	scanf("%d",&a);
	switch(a)
	{
		case 1:
			start = clock();
			sort1();
			finish = clock();
			duration =(double) (finish - start) / CLOCKS_PER_SEC;
			printf("sort1 cost %f second \n",duration);
			break;
		case 2:
			start = clock();
			sort2();
			finish =clock();
			duration = (double)(finish - start) / CLOCKS_PER_SEC;
			printf("sort2 cost %f second \n",duration);
			break;
		default:
			break;
	}

}
