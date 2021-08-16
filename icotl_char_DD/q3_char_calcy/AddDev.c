#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	int fd;
	int num[2];
	int result;
	printf("Enter two number for addition operation: ");
	scanf("%d %d",&num[0],&num[1]); 

	fd = open("/dev/AddDev",O_RDWR,0777); 
	if(fd < 0)
	{
		printf("Not able to open the device\n");
		return -1;
	}

	write(fd,num,sizeof(num));
	read(fd,&result,sizeof(result));
	printf("the result of addtion from kernel: %d\n",(int)result);
	close(fd);
	return 0;
}
