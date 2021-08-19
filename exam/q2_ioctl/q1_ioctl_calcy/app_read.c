#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <asm/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "ioctl.h"

struct data {
	int size;
	char buff[];
	int r_w;
};

int main()
{
	int FileDesc;
	int output;
	struct data senddata;
	char ubuf[];
	char kbuf[100];
	FileDesc=open("/dev/MyCharDev",O_RDWR,0777);
	if(FileDesc < 0)
	{
		printf("Error in opening device\n");
		return 0;
	}
	
	/*printf("Reading data from driver\n");
	ioctl(FileDesc,Read_data, (int*) &output);
	printf("output is : %d\n",output);
	*/

	write(FileDesc,ubuf,sizeof(ubuf));
	read(FileDesc,kbuf,50);
	printf("closing driver\n");
	close(FileDesc);
}
