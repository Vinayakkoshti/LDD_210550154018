#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/wait.h>
int main()
{
	int fd;
	char wbuff[] = "hello kernal.... this is user";
	char rbuff[] = "\0";

	fd = open("/dev/compdevice",O_RDWR);
	
	if(fd<0)
	{
		printf("\nerror opening file\n");
		exit(1);
	}
	if(fork() == 0)
	{
		write(fd,wbuff,sizeof(wbuff));

	}

	else
	{
		read(fd,rbuff,sizeof(rbuff));

		printf("Value read: %s\n",rbuff);
		wait(NULL);
	}

	close(fd);
	return 0;
}

