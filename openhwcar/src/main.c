#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "motor.h"
#include "sign.h"
#include "eye.h"
#include "roadctl.h"

void delayms(int count)
{
	int i,j,k;
	for(i=0;i<100;i++)
	{
		for(j=0;j<600;j++)
		{
			for(k=0;k<count;k++)
				;
		}
	}
}
int main(int argc,char * argv[])
{

	char c;
	char omem;
	car_init();
	sign_init();
	eye_open();
	printf("please choose mode: a:auto m:man r: recored q: quit\n");
	c=getchar();
	switch(c)
	{
		case 'a':
			while(1)
			{
				see();
				sharingan();
				if(sign_flag==1)
				{
					split_sign();
					sign_err();
					reg_sign();
					if(cur_sign!=last_sign)
					{
						switch(cur_sign)
						{
							case STOP:
								stop();
								delayms(600);
								break;
							case GO_AHEAD:
								move(FORW,6000);
								delayms(1000);
								break;
							case TURN_RIGHT:
								move(FORW,6000);
								delayms(1000);
								move(RIGHT,6000);
								delayms(500);
								move(FORW,6000);
								delayms(1000);
								break;
							default:
								break;

						}
						last_sign=cur_sign;
					}
				}
				else
				{
					plane_err();
				}
				if(err > 200)
					err = 200;
				else if(err < -200)
					err = -200;
				//adjust_err();
				//stop();
				fflush(stdout);
			}
			break;
		case 'm':
			c=getchar();
			while(1)
			{	
				switch(c)
				{
					case 'w':
						move(FORW,5000);
						delayms(1000);
						stop();
						break;
					case 'a':
						move(LEFT,5000);
						delayms(200);
						stop();
						break;
					case 's':
						move(BACK,5000);
						delayms(1000);
						stop();
						break;
					case 'd':
						move(RIGHT,5000);
						delayms(200);
						stop();
						break;
					case 'q':
						return;
					default: 
						break;
				}
					c=getchar();
				}

				break;
			default:
				return;
		}
		stop();
		sign_clean();
		eye_close();
		return 0;
}
