#include "xil_io.h"
#include <stdio.h>

#define XPAR_ULTRASONIC_0_S00_AXI_BASEADDR 0x43C10000

void test_ult()
{
	int val;
	int i;
	Xil_Out32(XPAR_ULTRASONIC_0_S00_AXI_BASEADDR, 0x1);

	for(i = 1;i < 4; i++)
	{
		while(!(Xil_In32(XPAR_ULTRASONIC_0_S00_AXI_BASEADDR) & (1 << i)));
		val = Xil_In32(XPAR_ULTRASONIC_0_S00_AXI_BASEADDR + 4 * i); 
		printf("u%d : %f mm\r\n",i,0.0017 * val);
	}
}


int main(void)
{
while(1)
{
    test_ult();
    sleep(1);
}
}

