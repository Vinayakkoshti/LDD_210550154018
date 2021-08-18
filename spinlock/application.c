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
	fd = open("/dev/spindevice",O_RDWR,0777);
	
	if(fd<0)
	{
		printf("\nerror opening file\n");
		exit(1);
	}
	id=fork();
	if(id == 0)
	{
		read(fd,&var1,sizeof(var1));
		printf("First Value: %d\n", var1);
	}

	else
	{
		read(fd,&var2,sizeof(var2));
		printf("Second Value: %d\n",var2);
	}

	close(fd);
	return 0;
}
