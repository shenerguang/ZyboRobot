#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>

/************ pwm pid defination ***********/ 
#define LEFT_SPEED_SET 3
#define LEFT_SPEED_GET 4
#define RIGHT_SPEED_SET 5
#define RIGHT_SPEED_GET 6

/************ optical defination ***********/ 
#define READ_ALL 1 
#define READ_1 3
#define READ_2 4
#define READ_3 5
#define READ_4 6
#define READ_5 7
#define READ_WAIT 9

/************ ultrasonic defination ***********/ 
#define ULTRASONIC_READ 1
#define ULTRASONIC_PARAM 0.0017


static int pwm_fd;
static int opt_fd; 
static int ult_fd;

int Devices_Open()
{

	pwm_fd = open("/dev/pwm_mod", 0);
	if (pwm_fd < 0)	{
		perror("open device pwm_mod error!\n");
        	return -1;
	}
	opt_fd = open("/dev/opt_mod", 0);
	if (opt_fd < 0) {
		perror("open device opt_mod error!\n");
        	return -1;
	}
	ult_fd = open("/dev/ult_mod", 0);
	if (ult_fd < 0) {
		perror("open device ult_mod error!\n");
        	return -1;
	}
	return 0;
}

int Devices_Close()
{
	close(pwm_fd);
	close(opt_fd);
	close(ult_fd);
	return 0;
}

/*
 * Set up speed of left wheel
 * speed range -45 ~ +45
*/
int Pwm_Left_Speed_Set(int speed)
{
	ioctl(pwm_fd,LEFT_SPEED_SET,speed);
	return 0;
}

/*
 * Set up speed of right wheel
 * speed range -45 ~ +45
*/
int Pwm_Right_Speed_Set(int speed)
{
	ioctl(pwm_fd,RIGHT_SPEED_SET,speed);
	return 0;
}

/*
 * Get speed of left wheel
 * input should be address of an int number
*/
int Pwm_Left_Speed_Get(int *speed)
{
	ioctl(pwm_fd,LEFT_SPEED_GET,speed);
	return 0;
}

/*
 * Get speed of right wheel
 * input should be address of an int number
*/
int Pwm_Right_Speed_Get(int *speed)
{
	ioctl(pwm_fd,RIGHT_SPEED_GET,speed);
	return 0;
}

/*
 * Get value of five optical
 * input should be address of an unsigned int number
*/
int Optical_Read_All(unsigned int *val)
{
	ioctl(opt_fd,READ_ALL,val);	
	close(opt_fd);
	return 0;
}

/*
 * Get value of five optical
 * input should be address of an unsigned int number
*/
int Optical_Read_Single(int num, unsigned int *val)
{
	if(num < 1 || num > 5){
		perror("argument wrong!\n");
		return -1;
	}
	ioctl(opt_fd,num+2,val);	
	return 0;
}

/*
 * This func will hang on if no optical value change
 * Get value of five optical
 * input should be address of an unsigned int number
 * input should be the value you want to test
 * you can use value monitored last time as default input
*/
int Optical_Read_Wait(unsigned int *val)
{
	printf("in opt wait!!,val = 0x%x\n",*val);
	printf("READ_WAIT=%d\n",READ_WAIT);
	ioctl(opt_fd,READ_WAIT,val);
	return 0;
}

/*
 * Get all value of ultrasonic 
 * input should be address of an float array of three elements
*/
int Ultrasonic_Read_All(float *val)
{
	int data[3];
	ioctl(ult_fd,ULTRASONIC_READ,data);
	val[0] = data[0]*ULTRASONIC_PARAM;
	val[1] = data[1]*ULTRASONIC_PARAM;
	val[2] = data[2]*ULTRASONIC_PARAM;
	return 0;
}

/*
 * Get single value of ultrasonic 
 * input should be address of an float
*/
int Ultrasonic_Read_Single(int num, float *val)
{
	int data[3];
	if(num < 1 || num > 3){
		perror("param error!\n");
        	return -1;
	}
	ioctl(ult_fd,ULTRASONIC_READ,data);
	*val = data[num-1]*ULTRASONIC_PARAM;
	return 0;
}
