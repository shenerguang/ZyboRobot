#include<stdio.h>
#include "eye.h"
#include "roadctl.h"
#include "sign.h"
#include "motor.h"
//v 5000 d 250
#define SPEED 5000
#define D 250.0
#define T 170.0
#define MIDDLE_LINE_NUM 320
int err;
int hmid=320;
float cmid;
CvBox2D  line_box[8];
int line_num;
CvBox2D  corn_box[8];
int corn_num;
void sign_err()
{
	hmid=sign_rect.x;
	err =(int)( hmid- MIDDLE_LINE_NUM);
}	
void plane_err()
{
	printf("line num:%d conner num:%d\n",line_num,corn_num);
	err =(int)( hmid - MIDDLE_LINE_NUM);
}

void adjust_err()
{	
	double theta;
	int vl, vr,v;
	double r;
	v = SPEED;
	vl = v;
	vr = v;
	theta=atan(abs(err)/D);
	r=1.4*D/sin(2*theta)-T/2;
	if(err>3)
	{
		vl=2*(r+T)/(2*r+T)*v;
		vr=2*r/(2*r+T)*v;
	}
	else if(err < -3)
	{
		vr=2*(r+T)/(2*r+T)*v;
		vl=2*r/(2*r+T)*v;

	}
	state.lspd=vl;
	state.rspd=vr;
	car_set();
}
