#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>

static int pwm_fd;

int main(void)
{
    int i;
    // open device
    pwm_fd = open("/dev/pwm_mod", 0);
    if (pwm_fd < 0) {
        perror("open device pwm_mod error!\n");
        exit(1);
    }
    while(1)
    {
	ioctl(pwm_fd,5,1);
	ioctl(pwm_fd,1,10000);
	sleep(10);
	ioctl(pwm_fd,1,0);
	sleep(1);
	
	ioctl(pwm_fd,5,0);
	ioctl(pwm_fd,1,10000);
	sleep(10);
	ioctl(pwm_fd,1,0);
	sleep(1);

	ioctl(pwm_fd,4,1);
	ioctl(pwm_fd,3,10000);
	sleep(10);
	ioctl(pwm_fd,3,0);
	sleep(1);
	
	ioctl(pwm_fd,4,0);
	ioctl(pwm_fd,3,10000);
	sleep(10);
	ioctl(pwm_fd,3,0);
    }	
    	
}
