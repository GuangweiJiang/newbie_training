#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(void)
{
	int counter = 0;
	int old_counter = 0;
	int fd = open("/dev/globalmem_dev",O_RDONLY);
	if(fd != -1)
	{
		while(1)
		{
			read(fd,&counter,sizeof(unsigned int));
			if(counter != old_counter)
			{
				printf("%d\n",counter);
				old_counter = counter;
			}		
		}
	}
	else
		printf("fail to open\n");
	return 0;
}
