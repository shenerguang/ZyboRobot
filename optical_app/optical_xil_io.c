#include "xil_io.h"
#include <stdio.h>

#define XPAR_OPTICAL_BASEADDR 0x41210000

void test_opt()
{
	int val;
	val = Xil_In32(XPAR_OPTICAL_BASEADDR);
	printf("0x%x\n",val);
}


int main(void)
{
while(1)
{
    test_opt();
    sleep(1);
}
}

