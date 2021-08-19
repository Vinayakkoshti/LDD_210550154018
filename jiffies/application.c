#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "jiff.h"

int main()
{
	int fd;
	char k_rd_buff[50];
	int delay; 
	ssize_t result; 
	printf("how much delay you want in second: ");
	scanf("%d",&delay);
	fd = open("/dev/MyCharDevice",O_RDWR,0777); 
	if(fd < 0) 
	{
		printf("not able to open the device\n");
		return -1;
	}
	printf("Ther data we got from the kernel is:\n\n");
	result = read(fd,k_rd_buff,50); 
	ioctl(fd,DATA_DELAY,delay);
	while(result != 16)
	{
		continue;
	}
	printf("%s\n",k_rd_buff);
	close(fd);
	return 0;
}
