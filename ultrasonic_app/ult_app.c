#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>

static int ult_fd;

int main(void)
{
    int i;
    int val[3];
    // open device
    ult_fd = open("/dev/ult_mod", 0);
    if (ult_fd < 0) {
        perror("open device ult_mod error!\n");
        exit(1);
    }
    printf("open and init successful!");
	while(1)
	{
		ioctl(ult_fd,1,val);
		printf("%d;%d;%d\n",val[0],val[1],val[2]);
		printf("echo1 = %f\n",val[0]*0.0017);
		printf("echo2 = %f\n",val[1]*0.0017);
		printf("echo3 = %f\n",val[2]*0.0017);
		sleep(1);
	}
    	
}

