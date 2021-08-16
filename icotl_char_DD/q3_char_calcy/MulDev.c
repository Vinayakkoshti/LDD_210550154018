#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	int fd;
	int result;
	int num[2];
	
	printf("Enter the two number for multiplication operation: ");
	scanf("%d %d",&num[0],&num[1]);

	fd = open("/dev/MulDev",O_RDWR,0777);
	if(fd <0)
	{
		printf("the device not open\n");
		return -1;
	}

	write(fd,num,sizeof(num));
	read(fd,&result,sizeof(result));
	printf("the result of multiplication from kernel side: %d\n",result);
	close(fd);
	return 0;
}
