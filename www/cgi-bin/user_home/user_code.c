#include "xil_io.h"
#include "addr_define.h"
#include "package_c.h"

int main()
{
	int sw;
	int left_speed,right_speed;
	unsigned int opt_val;
	float ult_val[3],ult_single;

	printf("now output led.\n");
	//offset 12 means led direction, 0 means out
	Xil_Out32(AXI_GPIO_BASEADDR+12, 0x0);
	//turn on all leds
	Xil_Out32(AXI_GPIO_BASEADDR+8, 0xff);

	printf("now input swithc.\n");
	//offset 4 means led direction, 1 means in 
	Xil_Out32(AXI_GPIO_BASEADDR+4, 0x1);
	//get value of 4 switches
	sw = Xil_In32(AXI_GPIO_BASEADDR);
	printf("sw value = 0x%x\n",sw);
	
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
	Pwm_Left_Speed_Set(0);	
	Pwm_Right_Speed_Set(0);
	
	/*optical test*/
	Optical_Read_Single(1,&opt_val);
	printf("opt 1 = 0x%x\n",opt_val);	
	sleep(1);
	//read all conflict with read wait!!!!!!!!
	Optical_Read_All(&opt_val);
	printf("opt all = 0x%x\n",opt_val);	
	sleep(1);
	opt_val = 0;
	Optical_Read_Wait(&opt_val);
	printf("opt new = 0x%x\n",opt_val);	
	sleep(1);

	/*ultrasonic test*/
	Ultrasonic_Read_All(ult_val);
	printf("ult 1=%.6f, ult 2=%.6f, ult 3=%.6f\n",ult_val[0],ult_val[1],ult_val[2]);
	sleep(1);
	Ultrasonic_Read_Single(1, &ult_single);
	printf("ult 1=%.6f\n",ult_single);
	Devices_Close();

	return 0;
}