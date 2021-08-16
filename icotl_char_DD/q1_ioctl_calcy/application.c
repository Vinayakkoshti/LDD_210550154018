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
};

int main()
{
	char op;
	int fd, result;
	struct operator val;
	printf("Enter two number: ");
	scanf("%d %d",&val.num1,&val.num2);

	printf("Menu:\n'+' for Addition\n'-' for Subtraction\n'*' for Multiplication\n'/' for Division\n");
	scanf(" %c",&op);

	fd = open("/dev/MyIoctl",O_RDWR,0777);
	if(fd<0) 
	{
		printf("not able to open the device\n");
		return -1;
	}
	
	switch(op) 
	{
		case '+': ioctl(fd, ADD, &val);
			  break;
		case '-': ioctl(fd,SUB, &val);
			  break;
		case '*': ioctl(fd, MUL,&val);
			  break;
		case '/': ioctl(fd,DIV,&val);
			  break;
		default:printf("invalid operation\n");
			break;
	}
	close(fd);
	return 0;
}
