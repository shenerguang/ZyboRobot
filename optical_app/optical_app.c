#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>

#define READ_ALL 1
#define READ_1 3
#define READ_2 4
#define READ_3 5
#define READ_4 6
#define READ_5 7

static int opt_fd;

int main(void)
{
    unsigned int a,b,c,d,e;
    unsigned int val;
    // open device
    opt_fd = open("/dev/opt_mod", 0);
    if (opt_fd < 0) {
        perror("open device opt_mod error!\n");
        exit(1);
    }
    printf("open successful!");

	while(1)
	{
		ioctl(opt_fd,READ_ALL,&val);
		ioctl(opt_fd,READ_1,&a);
		ioctl(opt_fd,READ_2,&b);
		ioctl(opt_fd,READ_3,&c);
		ioctl(opt_fd,READ_4,&d);
		ioctl(opt_fd,READ_5,&e);
		printf("all=0x%x;#1=%d#2=%d#3=%d#4=%d#5=%d\n",val,a,b,c,d,e);
		sleep(1);
	}
}

