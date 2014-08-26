#include "xil_io.h"
#include <stdio.h>

#define AXI_PWM_BASEADDR 0x43C01000

void set_car_front(int speed)
{
        //set the for motor direction to be 0
        //Xil_Out32(AXI_GPIO_BASEADDR, 0x00);
        //set the four motor's speed
        Xil_Out32(AXI_PWM_BASEADDR,      speed == 0 ? 0 : 0x80000000 | speed);
        Xil_Out32(AXI_PWM_BASEADDR + 4,  0);
        Xil_Out32(AXI_PWM_BASEADDR + 8,  speed == 0 ? 0 : 0x80000000 | speed);
        Xil_Out32(AXI_PWM_BASEADDR + 12, 0);
}


int main(void)
{
         set_car_front(10000);
}

