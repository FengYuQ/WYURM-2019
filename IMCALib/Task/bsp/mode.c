#include "tim.h"
#include "pid.h"
#include "mode.h"
#include "gpio.h"
#include "usart.h"
#include "bsp_can.h"
#include "motor_ctr.h"
#include "Remote_Control.h"

Flag_t Flag;
int16_t ref_spd[2]={0,0};
int text5, text6, Cmspd, moka;

extern pid_t pid_spd[5];
extern int Gimspd,Gimspds;
extern moto_measure_t moto_chassis[5];
extern int32_t Yaw, Pitch, Poke, AngleStep;

/* ������ʼ�� */
void ParamInit()
{
	Cmspd = 3000;							//�����ٶ�
	moka = 1150;						//Ħ����PWM
	Flag.Mode = 1;					//ģʽ
	Flag.FireFlag = 0;			//����ģʽ
	Flag.PatrolFlag = 1;		//Ѳ��ģʽ
	Flag.Partrol = 1;				//��̨�ٶȺ�λ���л�
	Flag.RedFlag = 0;				//����
	Flag.GreenFlag = 1;
	Flag.ResidueFlag = 0;		//��Ѫ
	Flag.GetPos = 1;
	
}

/* ң�ز���ģʽ */
void ModeTest()
{

	Gimspd = 0;
	Flag.RedFlag = 0;
	
	if(remote_control.switch_right == Switch_Up)  //Ħ��������
	{
			motor_pwm_setvalue1(1000);
		}
	if(remote_control.switch_right == Switch_Down)
	{
	   motor_pwm_setvalue1(moka);
	 }
	
	Yaw += remote_control.ch3/4;  //ң��������,0~660,Ϊ0~41����0~+180��
//  Pitch = -((remote_control.ch4)/3.67f);  //0~660,Ϊ0~180��
	Poke = -remote_control.ch2*1500/660;
	
	ref_spd[0] = -(remote_control.ch1*3000/660);  //ң��������
  ref_spd[1] = (remote_control.ch1*3000/660);

		Flag.Mode = 1;
}

/* ����ϵͳ */
void JudgeDriver()
{
	if(recv_end_flag == 1){
			HAL_UART_Transmit_DMA(&huart3,rx_buffer,BUFFER_SIZE);
			rx_len = 0;
			recv_end_flag = 0;
			HAL_UART_Receive_DMA(&huart3,rx_buffer,BUFFER_SIZE);
		}
}

/* ����ģʽ */
void ModeFire()
{
	Flag.FireFlag = 0;
	Flag.PatrolFlag = 1;
	Flag.RedFlag = 0;
	if(ref_spd[0] > 0){
		ref_spd[0] = Cmspd/2;
		ref_spd[1] = -Cmspd/2;
	}
	else{
		ref_spd[0] = -Cmspd/2;
		ref_spd[1] = Cmspd/2;
	}

//	Change_direction();
}

/* Ѳ��ģʽ */
void ModePatrol()
{
	Yaw = 0;
	Pitch = 400;
	Gimspd = 30;
	Flag.Partrol = 1;
	Flag.FireFlag = 1;
	Flag.PatrolFlag = 0;
	
	if(ref_spd[0] > 0){
		ref_spd[0] = Cmspd;
		ref_spd[1] = -Cmspd;
	}
	else{
		ref_spd[0] = -Cmspd;
		ref_spd[1] = Cmspd;
	}
	
	

}	

/* ģʽ�л� */
void ModeChoose()
{
	
	if(remote_control.switch_left == Switch_Up)
	{
		ModeTest();
	}
	else if( Flag.Mode==0 && Flag.PatrolFlag==1 )
	{
		ModePatrol();
	}
	else if( Flag.Mode==1 && Flag.FireFlag==1 )
	{
		ModeFire();
	}
	
 /* ��ѭ�����̺Ͳ��� */
	Chassis_task();
	
	/* ����ϵͳ */
	JudgeDriver();
	
	/* ��̨���� */
	  Gimpar();

}

