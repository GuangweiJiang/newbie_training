#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MEM_CLEAR 0x100004
#define MEM_SET   0x100005
int main()
{int fd;
fd=open("/dev/globalmem_dev",O_RDWR);
if(fd == -1)
{
printf("fail to open file\n");
return -1;
}
printf(".....\n");
if((write(fd,"jiang",strlen("jiang")))<=0)
    return -1;
ioctl(fd,MEM_CLEAR);
close(fd);
}
