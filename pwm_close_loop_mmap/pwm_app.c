#include "xil_io.h"
#include <stdio.h>

#define XPAR_MOTOR_CTRL_L_MOTOR_S_AXI_BASEADDR 0x43C01000
#define XPAR_MOTOR_CTRL_R_MOTOR_S_AXI_BASEADDR 0x43C02000

void init_motor()
{
//MOTOR Controller IP Initialize
    Xil_Out32((XPAR_MOTOR_CTRL_L_MOTOR_S_AXI_BASEADDR) + (0 * 4), (0x0));
    Xil_Out32((XPAR_MOTOR_CTRL_L_MOTOR_S_AXI_BASEADDR) + (1 * 4), (-0)); //in_speed_set
    Xil_Out32((XPAR_MOTOR_CTRL_L_MOTOR_S_AXI_BASEADDR) + (2 * 4), (1 << 8)); //in_kp_param
    Xil_Out32((XPAR_MOTOR_CTRL_L_MOTOR_S_AXI_BASEADDR) + (3 * 4), (1 << 8)); //in_ki_param
    Xil_Out32((XPAR_MOTOR_CTRL_L_MOTOR_S_AXI_BASEADDR) + (4 * 4), (63)); //in_pid_out_max
    Xil_Out32((XPAR_MOTOR_CTRL_L_MOTOR_S_AXI_BASEADDR) + (5 * 4), (-63)); //in_pid_out_min
    Xil_Out32((XPAR_MOTOR_CTRL_L_MOTOR_S_AXI_BASEADDR) + (6 * 4), (70 << 8)); //in_pid_ui_limit

    Xil_Out32((XPAR_MOTOR_CTRL_L_MOTOR_S_AXI_BASEADDR) + (14 * 4), (0)); //in_pid_ui_limit
    Xil_Out32((XPAR_MOTOR_CTRL_L_MOTOR_S_AXI_BASEADDR) + (14 * 4), (0x0ff)); //in_pid_ui_limit
    //Control reg
    // bit 0 : in_module_en
    // bit 1 : in_fwd_dir
    // *    if in_fwd_dir == 1 out_w_PWMdir = pid_out_sign
    // *    else out_w_PWMdir = ~pid_out_sign
    // bit 2:  in_PID_passby, if == 1, PID Controller bypass
    Xil_Out32((XPAR_MOTOR_CTRL_L_MOTOR_S_AXI_BASEADDR) + (0 * 4), (0x01));

    //MOTOR Controller IP Initialize
    Xil_Out32((XPAR_MOTOR_CTRL_R_MOTOR_S_AXI_BASEADDR) + (0 * 4), (0x0));
//    usleep(2000 * 100);
    Xil_Out32((XPAR_MOTOR_CTRL_R_MOTOR_S_AXI_BASEADDR) + (1 * 4), (0)); //in_speed_set
    Xil_Out32((XPAR_MOTOR_CTRL_R_MOTOR_S_AXI_BASEADDR) + (2 * 4), (1 << 8)); //in_kp_param
    Xil_Out32((XPAR_MOTOR_CTRL_R_MOTOR_S_AXI_BASEADDR) + (3 * 4), (1 << 8)); //in_ki_param
    Xil_Out32((XPAR_MOTOR_CTRL_R_MOTOR_S_AXI_BASEADDR) + (4 * 4), (63)); //in_pid_out_max
    Xil_Out32((XPAR_MOTOR_CTRL_R_MOTOR_S_AXI_BASEADDR) + (5 * 4), (-63)); //in_pid_out_min
    Xil_Out32((XPAR_MOTOR_CTRL_R_MOTOR_S_AXI_BASEADDR) + (6 * 4), (70 << 8)); //in_pid_ui_limit

    Xil_Out32((XPAR_MOTOR_CTRL_R_MOTOR_S_AXI_BASEADDR) + (14 * 4), (0)); //in_pid_ui_limit
    Xil_Out32((XPAR_MOTOR_CTRL_R_MOTOR_S_AXI_BASEADDR) + (14 * 4), (0x0ff)); //in_pid_ui_limit
    //Control reg
    // bit 0 : in_module_en
    // bit 1 : in_fwd_dir
    // *    if in_fwd_dir == 1 out_w_PWMdir = pid_out_sign
    // *    else out_w_PWMdir = ~pid_out_sign
    // bit 2:  in_PID_passby, if == 1, PID Controller bypass
    Xil_Out32((XPAR_MOTOR_CTRL_R_MOTOR_S_AXI_BASEADDR) + (0 * 4), (0x01));
}

void set_left(long arg)
{
Xil_Out32((XPAR_MOTOR_CTRL_R_MOTOR_S_AXI_BASEADDR) + (1 * 4), arg); //in_speed_set	
}

void set_right(long arg)
{
Xil_Out32((XPAR_MOTOR_CTRL_L_MOTOR_S_AXI_BASEADDR) + (1 * 4), arg); //in_speed_set
}

long get_left()
{
return Xil_In32((XPAR_MOTOR_CTRL_L_MOTOR_S_AXI_BASEADDR) + (15 * 4));
}

long get_right()
{
return Xil_In32((XPAR_MOTOR_CTRL_R_MOTOR_S_AXI_BASEADDR) + (15 * 4));
}

int main(void)
{
    init_motor();
    printf("motor init finished!\n");
    set_left(20);
    set_right(-20);	
    sleep(10);

    set_left(0);
    set_right(0);	
    sleep(10);
    set_left(-20);
    set_right(20);	
while(1)
{
    printf("left speed = %d\n",get_left());
    printf("right speed = %d\n",get_right());
    sleep(1);
}
}

