#include "pid.h"
#include "tim.h"
#include "gpio.h"
#include "ramp.h"
#include "mode.h"
#include <stdlib.h>
#include "bsp_can.h"
#include "motor_ctr.h"
#include "Remote_Control.h"


pid_t pid_pos[5];
pid_t pid_spd[5];


ramp_t TurnDir1 = RAMP_GEN_DAFAULT;
ramp_t TurnDir2 = RAMP_GEN_DAFAULT;
ramp_t TurnDir3 = RAMP_GEN_DAFAULT;
int rander = 40, Gimspd, Gimspds;

extern Flag_t Flag;
extern int16_t ref_spd[2];




extern int Tim, text5, text6;
extern int32_t Yaw, Pitch, Poke;
extern moto_measure_t moto_chassis[5];

/* 角度限制 */
void Agl_limit()
{
	VAL_LIMIT(Yaw, -4000, 3000);
	VAL_LIMIT(Pitch, -800, 1100);
}

/* 斜坡初始化 */
void RampInit()
{
	ramp_init(&TurnDir1,80000);
	ramp_init(&TurnDir2,80000);
	ramp_init(&TurnDir3,80000);
}

/* pid初始化 */
void Pid_init()  
{
	
	 for (int k = 0; k < 2; k++)  //底盘电机pid
  {
//    PID_struct_init(&pid_pos[k], POSITION_PID, 1000, 10, 20, 0.01f, 0);   //初始限幅
		PID_struct_init(&pid_spd[k], POSITION_PID, 8000, 0, 7.5f, 0, 0);   
	}
	  
//		PID_struct_init(&pid_pos[2], POSITION_PID, 8000, 0, 20, 0, 0);         // 6020 yaw
//    PID_struct_init(&pid_spd[2], POSITION_PID, 20000, 100, 4, 0.6f, 0);  
//		PID_struct_init(&pid_pos[3], POSITION_PID, 8000, 0, 20, 0, 0);         // 6020 pitch
//    PID_struct_init(&pid_spd[3], POSITION_PID, 20000, 1000, 10, 1, 0);  
	
		PID_struct_init(&pid_pos[2], POSITION_PID, 2000, 0, 22, 0, 0);   // 6020 yaw
    PID_struct_init(&pid_spd[2], POSITION_PID, 30000, 10, 2, 0.6f, 0);  
	  PID_struct_init(&pid_pos[3], POSITION_PID, 2000, 0, 8, 0, 0);   // 6020 pitch
    PID_struct_init(&pid_spd[3], POSITION_PID, 30000, 100, 2.8f, 1, 0);  
	
	  PID_struct_init(&pid_pos[4], POSITION_PID, 1000, 10, 20, 0.01f, 0);    // M2006
    PID_struct_init(&pid_spd[4], POSITION_PID, 8000, 0, 8, 0.1f, 0);  
		
}

/* 随机改变左右方向 */
void Change_direction()
{
	if((moto_chassis[1].round_cnt <= -rander) ||  (moto_chassis[1].round_cnt >= rander))
	{
		Flag.RedFlag = 1;
		text5 = ref_spd[0];
		text6 = ref_spd[1];
		RampInit();
		moto_chassis[1].round_cnt = 0;
		
		if(ref_spd[0] > 0)
		  Flag.Direction = 1;    //Turn Right
		else
			Flag.Direction = 0; 	 //Turn Left
		
		/* 产生 40-60 间的随机数 */
		srand(Tim);
		rander = random(40, 60);
		
	}
}

/* 底盘和拨弹 */
void Chassis_task()
{
	SpdCut();
	
//	pid_calc(&pid_pos[4],moto_chassis[4].total_angle/100,Poke);
  pid_calc(&pid_spd[4],moto_chassis[4].speed_rpm,Poke);
	
//	Change_direction();
	
	pid_calc(&pid_spd[0], moto_chassis[0].speed_rpm, ref_spd[0]);
  pid_calc(&pid_spd[1], moto_chassis[1].speed_rpm, ref_spd[1]);
}

/* 云台 */
void Gimbal_task()
{	
	Agl_limit();  //角度限制
	
	switch(Flag.Partrol)
	{
		case 0:
		{
			PID_struct_init(&pid_spd[2], POSITION_PID, 30000, 10, 2, 0.6f, 0); 
//			PID_struct_init(&pid_spd[3], POSITION_PID, 30000, 100, 2.8f, 1, 0); 
		  pid_calc(&pid_pos[2],moto_chassis[2].total_angle,Yaw);
			pid_calc(&pid_spd[2],moto_chassis[2].speed_rpm ,pid_pos[2].pos_out);
		  pid_calc(&pid_pos[3],moto_chassis[3].total_angle,Pitch);
			pid_calc(&pid_spd[3],moto_chassis[3].speed_rpm ,pid_pos[3].pos_out);
		}break;
		case 1:
		{
//#if TwoMove
//			PID_struct_init(&pid_spd[2], POSITION_PID, 30000, 10, 140, 0.6f, 0); 
//			pid_calc(&pid_spd[2],moto_chassis[2].speed_rpm ,Gimspd);
//			PID_struct_init(&pid_spd[3], POSITION_PID, 30000, 100, 200, 1, 0); 
//			pid_calc(&pid_spd[3],moto_chassis[3].speed_rpm ,Gimspds);
//#else		
			PID_struct_init(&pid_spd[2], POSITION_PID, 30000, 10, 170, 0.6f, 0); 
			pid_calc(&pid_spd[2],moto_chassis[2].speed_rpm ,Gimspd);			
			pid_calc(&pid_pos[3],moto_chassis[3].total_angle,Pitch);
			pid_calc(&pid_spd[3],moto_chassis[3].speed_rpm ,pid_pos[3].pos_out);
//#endif
		}break;
		
	}
//	if( abs(Yaw - moto_chassis[2].total_angle) <= 10 )
//	{
//		Flag.GetPos = 1;
//	}

//	text1 = moto_chassis[2].total_angle;
//	text2 = Yaw;
//	text3 = moto_chassis[3].total_angle;
//	text4 = Pitch;
	
}

/* CAN通信 */
void Send_Can()
{	
		set_cloud_current(&hcan1,0,pid_spd[3].pos_out,
															 pid_spd[4].pos_out,
															 pid_spd[2].pos_out);  
	
	  set_moto_current(&hcan1, pid_spd[0].pos_out, 
														 pid_spd[1].pos_out );
}

/* 反转斜坡 */
void SpdCut()   
{
	if(Flag.RedFlag == 1)
	{
	  switch(Flag.Direction)
	 {
		case 1:
			ref_spd[0] = text5 - (text5 * ramp_calc(&TurnDir1));
			ref_spd[1] = text6 + ((-text6) * ramp_calc(&TurnDir1));

			break;
		case 0:
			ref_spd[0] = text5 + ((-text5) * ramp_calc(&TurnDir2));
			ref_spd[1] = text6 - (text6 * ramp_calc(&TurnDir2));

			break;
	 }

		if(ref_spd[0] == 0 && ref_spd[1] == 0)
	 {
		 Flag.GreenFlag = 1;
     switch(Flag.Direction)
	  {
		case 1:
		  ref_spd[0] = -((text5) * ramp_calc(&TurnDir3));
//		  ref_spd[1] = (-text6) * ramp_calc(&TurnDir3);
		ref_spd[1] = -ref_spd[0];
			break;
		case 0:
		  ref_spd[0] = (-text5) * ramp_calc(&TurnDir3);
//		  ref_spd[1] = -((text6) * ramp_calc(&TurnDir3));
				ref_spd[1] = -ref_spd[0];
			break;
	  }

	 }
	 else if(ref_spd[0] == -text5)
	 {
		 Flag.RedFlag = 0;
	 }
  }
	
//	 if(ref_spd[0] != -ref_spd[1])
//	{
//		 ref_spd[0] = -text5;
//		 ref_spd[1] = -text6;
//	}

}

/* 云台自旋 */
void Gimpar()
{
//#ifdef TwoMove
//		if( moto_chassis[2].total_angle >= 2800 )
//			Gimspd = -30;
//		else if(moto_chassis[2].total_angle <= -3500)
//			Gimspd = 30;
//		if( moto_chassis[3].total_angle >= 900)
//			Gimspds = -2;
//		else if(moto_chassis[3].total_angle <= 100)
//			Gimspds = 20;
//#else
		if( moto_chassis[2].total_angle >= 2800 )
		{
			Gimspd = -30;
			Pitch=400;
		}
		else if(moto_chassis[2].total_angle <= -3500)
		{
		 	Gimspd = 30;
			Pitch = 700;
	  }
//#endif
}

