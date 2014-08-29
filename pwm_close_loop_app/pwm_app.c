#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>

#define LEFT_SPEED_SET 3
#define LEFT_SPEED_GET 4
#define RIGHT_SPEED_SET 5
#define RIGHT_SPEED_GET 6

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
    printf("open and init successful!");
/*
    while(1)
    {
	ioctl(pwm_fd,LEFT_SPEED_SET,20);
	ioctl(pwm_fd,RIGHT_SPEED_SET,20);
	sleep(10);
	ioctl(pwm_fd,LEFT_SPEED_SET,0);
	ioctl(pwm_fd,RIGHT_SPEED_SET,0);
	sleep(1);
	ioctl(pwm_fd,LEFT_SPEED_SET,-20);
	ioctl(pwm_fd,RIGHT_SPEED_SET,-20);
	sleep(10);
	ioctl(pwm_fd,LEFT_SPEED_SET,0);
	ioctl(pwm_fd,RIGHT_SPEED_SET,0);
	sleep(1);
	
    }
*/	
	ioctl(pwm_fd,LEFT_SPEED_SET,20);
	ioctl(pwm_fd,RIGHT_SPEED_SET,20);
	while(1)
	{
		int left_val,right_val;
		ioctl(pwm_fd,LEFT_SPEED_GET,&left_val); 
		ioctl(pwm_fd,RIGHT_SPEED_GET,&right_val); 
		printf("left=%d;right=%d\n",left_val,right_val);
		sleep(1);
	}
    	
}

