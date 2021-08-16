#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include "ioctl_header.h"

struct operator
{
	int num1;
	int num2;
	char operation;
};

int main()
{
	int fd, result;
	struct operator data;
	printf("Enter two number: ");
	scanf("%d %d",&data.num1,&data.num2);

	printf("Menu:\n'+' for Addition\n'-' for Subtraction\n'*' for Multiplication\n'/' for Division\n");
	scanf(" %c",&data.operation);

	fd = open("/dev/MyIoctl",O_RDWR,0777);
	if(fd<0) 
	{
		printf("not able to open the device\n");
		return -1;
	}
	
	ioctl(fd,OPT,&data);
	close(fd);
	return 0;
}
