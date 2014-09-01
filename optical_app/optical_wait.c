#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>

#define READ_WAIT 9

static int opt_fd;

int main(void)
{
    unsigned int val;
    // open device
    opt_fd = open("/dev/opt_mod", 0);
    if (opt_fd < 0) {
        perror("open device opt_mod error!\n");
        exit(1);
    }
    printf("open successful!\n");

	while(1)
	{
		ioctl(opt_fd,READ_WAIT,&val);
		printf("new=0x%x\n",val);
		sleep(1);
	}
}

