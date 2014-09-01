#include "package_c.h"

int main()
{
	int left_speed,right_speed;
	int opt_val;
	float ult_val[3],ult_single;

	Devices_Open();
	/* test pwm pid*/
	Pwm_Left_Speed_Set(25);
	sleep(1);
	Pwm_Left_Speed_Set(-35);	
	sleep(1);
	Pwm_Right_Speed_Set(35);
	sleep(1);
	Pwm_Right_Speed_Set(-25);
	sleep(1);
	Pwm_Left_Speed_Get(&left_speed);
	Pwm_Right_Speed_Get(&right_speed);
	printf("left speed = %d, right speed = %d\n", left_speed, right_speed);
	
	/*optical test*/
	Optical_Read_Single(1,&opt_val);
	printf("opt 1 = 0x%x\n",opt_val);	
	sleep(1);
	Optical_Read_All(&opt_val);
	printf("opt all = 0x%x\n",opt_val);	
	sleep(1);
	Optical_Read_Wait(&opt_val);
	printf("opt new = 0x%x\n",opt_val);	
	sleep(1);

	/*ultrasonic test*/
	Ultrasonic_Read_All(ult_val);
	printf("ult 1=%f, ult 2=%f, ult 3=%f\n",ult_val[0],ult_val[1],ult_val[2]);
	sleep(1);
	Ultrasonic_Read_Single(1, &ult_single);
	printf("ult 1=%f\n",ult_single);
	Devices_Close();
}	
