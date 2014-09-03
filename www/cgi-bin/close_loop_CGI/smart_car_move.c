#include "xil_io.h"
#include "smart_car_move.h"

#define AXI_GPIO_BASEADDR 0x41200000

#define XPAR_MOTOR_CTRL_L_MOTOR_S_AXI_BASEADDR 0x43C01000
#define XPAR_MOTOR_CTRL_R_MOTOR_S_AXI_BASEADDR 0x43C02000


void init_LED()
{
    fd = open(gpio_addr[0], MODE);
    if (fd < 0)
        printf("can't open gpio export\n");
    write(fd, "243", 2);
    close(fd);

    fd = open(gpio_addr[0], MODE);
    if (fd < 0)
        printf("can't open gpio export\n");
    write(fd, "244", 2);
    close(fd);

    fd = open(gpio_addr[0], MODE);
    if (fd < 0)
        printf("can't open gpio export\n");
    write(fd, "245", 2);
    close(fd);
    fd = open(gpio_addr[0], MODE);
    if (fd < 0)
        printf("can't open gpio export\n");
    write(fd, "246", 2);
    close(fd);
}


void smart_car_init()
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

	Xil_Out32(AXI_GPIO_BASEADDR+12, 0x0);
	Xil_Out32(AXI_GPIO_BASEADDR+8, 0x0);
}

// speed 0 ~ +45
void set_car_front(int speed)
{
	//set the for motor direction to be 0
	Xil_Out32(AXI_GPIO_BASEADDR+8, 1<<0);
	if(speed == 0)
		Xil_Out32(AXI_GPIO_BASEADDR+8, 0xf);
		
	//set the four motor's speed
	Xil_Out32(XPAR_MOTOR_CTRL_L_MOTOR_S_AXI_BASEADDR+4,-speed);
	Xil_Out32(XPAR_MOTOR_CTRL_R_MOTOR_S_AXI_BASEADDR+4,-speed);
}

// speed 0 ~ +45
void set_car_back(int speed)
{
	//set the for motor direction to be 0
	Xil_Out32(AXI_GPIO_BASEADDR+8, 1<<1);
	//set the four motor's speed
	Xil_Out32(XPAR_MOTOR_CTRL_L_MOTOR_S_AXI_BASEADDR+4,speed);
	Xil_Out32(XPAR_MOTOR_CTRL_R_MOTOR_S_AXI_BASEADDR+4,speed);
}

//speed 0 ~ +45
void set_car_right(int speed)
{
	Xil_Out32(AXI_GPIO_BASEADDR+8, 1<<3);
	Xil_Out32(XPAR_MOTOR_CTRL_L_MOTOR_S_AXI_BASEADDR+4,-speed);
    Xil_Out32(XPAR_MOTOR_CTRL_R_MOTOR_S_AXI_BASEADDR+4,speed);
}

//speed 0 ~ +45
void set_car_left(int speed)
{
	Xil_Out32(AXI_GPIO_BASEADDR+8, 1<<2);
	Xil_Out32(XPAR_MOTOR_CTRL_L_MOTOR_S_AXI_BASEADDR+4,speed);
    Xil_Out32(XPAR_MOTOR_CTRL_R_MOTOR_S_AXI_BASEADDR+4,-speed);
}


