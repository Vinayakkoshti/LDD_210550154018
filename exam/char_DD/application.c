#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

int main()
{
	int fd;
	char u_buff[]="hey i am from user and delivered to kernel";
	char k_buff[100];

	fd=open("/dev/add",O_RDWR,0777);
	if(fd<0)
	{
		printf("\nError opening file\n");
		exit(1);
	}
	

	read(fd,k_buff,50);
//	sleep(5);
	write(fd,u_buff,sizeof(u_buff));
	printf("data read from kernel : %s\n",k_buff);	
	close(fd);


	return 0;
}
