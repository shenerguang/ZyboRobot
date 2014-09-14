#include <stdio.h>
#include <stdlib.h>
#include "xil_io.h"
#include "addr_define.h"

int main()
{
        printf("hello world\n");
        Xil_Out32(AXI_GPIO_BASEADDR+12, 0x0);
    Xil_Out32(AXI_GPIO_BASEADDR+8, 0x3);
        return 0;
}
