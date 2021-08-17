#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/wait.h>
int main()
{
	int fd,var1,var2,id;
	fd = open("/dev/Mysem",O_RDWR,0777);
	if(fd<0)
	{
		printf("\nError opening file\n");
		exit(1);
	}
	id=fork();

	if(id == 0)
	{
		read(fd,&var1,sizeof(var1));
		printf("process 1: %d\n", var1);
	}
	else
	{
		read(fd,&var2,sizeof(var2));
		printf("process 2: %d\n",var2);
	}

	close(fd);
	return 0;
}
