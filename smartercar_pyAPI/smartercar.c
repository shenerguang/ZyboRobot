#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <Python.h>

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

int Devices_Open();
int Devices_Close();
int Pwm_Left_Speed_Set(int speed);
int Pwm_Right_Speed_Set(int speed);
int Pwm_Left_Speed_Get(int *speed);
int Pwm_Right_Speed_Get(int *speed);
int Optical_Read_Single(int num, unsigned int *val);
int Optical_Read_Wait(unsigned int *val);
int Ultrasonic_Read_All(float *val);
int Ultrasonic_Read_Single(int num, float *val);

//python wrap
PyObject * wrap_DeviceOpen(PyObject * self,PyObject * args)
{
	int result;
	result=Devices_Open();
	printf("Don't forget to close the device!\r\n");
	return Py_BuildValue("i",result);
}

PyObject * wrap_DeviceClose(PyObject * self,PyObject * args)
{
	int result;
	result=Devices_Close();
	return Py_BuildValue("i",result);
}

PyObject * wrap_PwmLeftSpeedSet(PyObject * self,PyObject * args)
{
	int speed,result;
	if(!PyArg_ParseTuple(args,"i",&speed))
		return NULL;
	result=Pwm_Left_Speed_Set(speed);
	return Py_BuildValue("i",result);
}

PyObject * wrap_PwmRightSpeedSet(PyObject * self,PyObject * args)
{
	int speed,result;
	if(!PyArg_ParseTuple(args,"i",&speed))
		return NULL;
	result=Pwm_Right_Speed_Set(speed);
	return Py_BuildValue("i",result);
}

PyObject * wrap_PwmLeftSpeedGet(PyObject * self,PyObject * args)
{
	int speed;
	Pwm_Left_Speed_Get(&speed);
	return Py_BuildValue("i",speed);
}

PyObject * wrap_PwmRightSpeedGet(PyObject * self,PyObject * args)
{
	int speed;
	Pwm_Right_Speed_Get(&speed);
	return Py_BuildValue("i",speed);
}

PyObject * wrap_OpticalReadSingle(PyObject * self,PyObject * args)
{
	int num,val;
	if(!PyArg_ParseTuple(args,"i",&num))
		return NULL;
	Optical_Read_Single(num,&val);
	return Py_BuildValue("i",val);
}

PyObject * wrap_OpticalReadWait(PyObject * self,PyObject * args)
{
	int val;
	Optical_Read_Wait(&val);
	return Py_BuildValue("i",val);
}

PyObject * wrap_UltrasonicReadAll(PyObject * self,PyObject * args)
{
	float val[3];
	Ultrasonic_Read_All(val);
	return Py_BuildValue("fff",val[0],val[1],val[2]);
}

PyObject * wrap_UltrasonicReadSingle(PyObject * self,PyObject * args)
{
	int num;
	float val;
	if(!PyArg_ParseTuple(args,"i",&num))
		return NULL;
	Ultrasonic_Read_Single(num,&val);
	return Py_BuildValue("f",val);
}

static PyMethodDef smartercarMethods[]=
{
	{"OpenSensor",wrap_DeviceOpen,METH_VARARGS,""},
	{"CloseSensor",wrap_DeviceClose,METH_VARARGS,""},
	{"SetLeftSpeed",wrap_PwmLeftSpeedSet,METH_VARARGS,""},
	{"SetRightSpeed",wrap_PwmRightSpeedSet,METH_VARARGS,""},
	{"GetLeftSpeed",wrap_PwmLeftSpeedGet,METH_VARARGS,""},
	{"GetRightSpeed",wrap_PwmRightSpeedGet,METH_VARARGS,""},
	{"OpticalSingle",wrap_OpticalReadSingle,METH_VARARGS,""},
	{"OpticalAll",wrap_OpticalReadWait,METH_VARARGS,""},
	{"SonicSingle",wrap_UltrasonicReadSingle,METH_VARARGS,""},
	{"SonicAll",wrap_UltrasonicReadAll,METH_VARARGS,""},
	{NULL,NULL}
};

void initsmartercar()
{
	PyObject *m;
	m=Py_InitModule("smartercar",smartercarMethods);
}
//smartcar C API implementation
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
	int i;
	ioctl(pwm_fd,LEFT_SPEED_SET,speed);
	i=0;
	return i;
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
