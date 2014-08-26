#include "xil_io.h"
#include "motor.h"

#define XPAR_MOTOR_CTRL_L_MOTOR_S_AXI_BASEADDR 0x43C01000
#define XPAR_MOTOR_CTRL_R_MOTOR_S_AXI_BASEADDR 0x43C02000

struct CAR_STATE state;

int cur_posL;
int cur_posR;

void car_set()
{
	left_wheel(state.lspd);
	right_wheel(state.rspd);
}
void car_init()
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

void left_wheel(long arg)
{
Xil_Out32((XPAR_MOTOR_CTRL_R_MOTOR_S_AXI_BASEADDR) + (1 * 4), -arg); //in_speed_set	
}

void right_wheel(long arg)
{
Xil_Out32((XPAR_MOTOR_CTRL_L_MOTOR_S_AXI_BASEADDR) + (1 * 4), -arg); //in_speed_set
}

long get_left()
{
return Xil_In32((XPAR_MOTOR_CTRL_L_MOTOR_S_AXI_BASEADDR) + (15 * 4));
}

long get_right()
{
return Xil_In32((XPAR_MOTOR_CTRL_R_MOTOR_S_AXI_BASEADDR) + (15 * 4));
}

void move(enum ACTION act,long spd)
{
	switch(act)
	{
		case FORW:
			state.lspd=spd;
			state.rspd=spd;
			break;
		case BACK:
			state.lspd=-spd;
			state.rspd=-spd;
			break;
		case LEFT:
			state.lspd=-spd;
			state.rspd=spd;
			break;
		case RIGHT:
			state.lspd=spd;
			state.rspd=-spd;
			break;
	}
	car_set();
}

void stop()
{
	left_wheel(0);
	right_wheel(0);
}

void position_ctrl(int wheelL_set, int wheelR_set, int wheelL_speed, int wheelR_speed)
{
	cur_posL += get_left();
	cur_posR += get_right();
	
	int pos_errL = wheelL_set - cur_posL;
	int pos_errR = wheelR_set - cur_posR;

	if(abs(pos_errL) > abs(wheelL_speed))
	{
		left_wheel(wheelL_speed);
	}
	else
	{
		left_wheel(pos_errL);
	}

	if(abs(pos_errR) > abs(wheelR_speed))
	{
		right_wheel(wheelR_speed);
	}
	else
	{
		right_wheel(pos_errR);
	}
}






