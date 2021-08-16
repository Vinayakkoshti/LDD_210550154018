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
	printf("enter two number for subtraction: ");
	scanf("%d %d",&num[0],&num[1]);

	fd = open("/dev/SubDev",O_RDWR,0777);
	if(fd <0)
	{
		printf("not able to oprn device\n");
		return -1;
	}

	write(fd,num,sizeof(num));
	read(fd,&result,sizeof(result));
	printf("the result of subtraction from kernel is: %d\n",result);
	close(fd);
	return 0;
}
