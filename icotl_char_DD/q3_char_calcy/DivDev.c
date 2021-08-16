#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	int fd,result,num[2];
	printf("Enter two number for division operation: ");
	scanf("%d %d",&num[0],&num[1]);

	fd = open("/dev/DivDev",O_RDWR, 0777);
	if(fd <0)
	{
		printf("error opening device\n");
		return -1;
	}

	write(fd,num,sizeof(num));
	read(fd,&result,sizeof(result));
	printf("the result of division from kernel side: %d\n",result);
	close(fd);
	return 0;
}
