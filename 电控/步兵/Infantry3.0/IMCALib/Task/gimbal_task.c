#include "gimbal_task.h"
#include "control_task.h"
#include "can.h"
#include "pid.h"
#include <arm_math.h>

Can_Send_t  can_send;
extern Encoder_t M6623_encoder_yaw,M6623_encoder_pitch,
	               M6020_encoder_yaw,M6020_encoder_pitch,
                 encoder_pluck;
 pid_t M6623_yaw_speed_pid,M6623_pitch_speed_pid,M6623_yaw_angle_pid,M6623_pitch_angle_pid,
	           M6020_yaw_speed_pid,M6020_pitch_speed_pid,M6020_yaw_angle_pid,M6020_pitch_angle_pid,
             M2006_speed_pid,    M2006_angle_pid;

Gimbal_Motor_t yaw_gimbal_motor,pitch_gimbal_motor,pluck_motor;

static uint8_t can_send_mode;

void gimbal_init(void)
{
	/***** 6623��ز�����ʼ�� *****/
	//6623PID�������鸳ֵ
	const static float M6623_yaw_speed[3]   = {M6623_YAW_SPEED_PID_KP,  M6623_YAW_SPEED_PID_KI,  M6623_YAW_SPEED_PID_KD  };
	const static float M6623_pitch_speed[3] = {M6623_PITCH_SPEED_PID_KP,M6623_PITCH_SPEED_PID_KI,M6623_PITCH_SPEED_PID_KD};
	const static float M6623_yaw_angle[3]   = {M6623_YAW_ANGLE_PID_KP,  M6623_YAW_ANGLE_PID_KI,  M6623_YAW_ANGLE_PID_KD  };
	const static float M6623_pitch_angle[3] = {M6623_PITCH_ANGLE_PID_KP,M6623_PITCH_ANGLE_PID_KI,M6623_PITCH_ANGLE_PID_KD};
	//6623yaw��ǶȻ� �ٶȻ� PID��ʼ��
	PID_Init(&M6623_yaw_speed_pid          ,M6623_yaw_speed            ,
	          M6623_YAW_SPEED_VOLTAFE_MAX  ,M6623_YAW_SPEED_VOLTAFE_MIN,
	          M6623_YAW_SPEED_MAXOUTPUT    ,M6623_YAW_SPEED_MINOUTPUT   );
	PID_Init(&M6623_yaw_angle_pid          ,M6623_yaw_angle            ,
	          M6623_YAW_ANGLE_VOLTAFE_MAX  ,M6623_YAW_ANGLE_VOLTAFE_MIN,
	          M6623_YAW_ANGLE_MAXOUTPUT    ,M6623_YAW_ANGLE_MINOUTPUT   );
	//6623pitch��ǶȻ� �ٶȻ� PID��ʼ��
	PID_Init(&M6623_pitch_speed_pid        ,M6623_pitch_speed            ,
	          M6623_PITCH_SPEED_VOLTAFE_MAX,M6623_PITCH_SPEED_VOLTAFE_MIN,
	          M6623_PITCH_SPEED_MAXOUTPUT  ,M6623_PITCH_SPEED_MINOUTPUT   );
	PID_Init(&M6623_pitch_angle_pid        ,M6623_pitch_angle            ,
	          M6623_PITCH_ANGLE_VOLTAFE_MAX,M6623_PITCH_ANGLE_VOLTAFE_MIN,
	          M6623_PITCH_ANGLE_MAXOUTPUT  ,M6623_PITCH_ANGLE_MINOUTPUT   );
	
	
	/***** 6020��ز�����ʼ�� *****/
	const static float M6020_yaw_speed[3]   = {M6020_YAW_SPEED_PID_KP,  M6020_YAW_SPEED_PID_KI,  M6020_YAW_SPEED_PID_KD  };
	const static float M6020_pitch_speed[3] = {M6020_PITCH_SPEED_PID_KP,M6020_PITCH_SPEED_PID_KI,M6020_PITCH_SPEED_PID_KD};
	const static float M6020_yaw_angle[3]   = {M6020_YAW_ANGLE_PID_KP,  M6020_YAW_ANGLE_PID_KI,  M6020_YAW_ANGLE_PID_KD  };
	const static float M6020_pitch_angle[3] = {M6020_PITCH_ANGLE_PID_KP,M6020_PITCH_ANGLE_PID_KI,M6020_PITCH_ANGLE_PID_KD};
	//6623yaw��ǶȻ� �ٶȻ� PID��ʼ��
	PID_Init(&M6020_yaw_speed_pid          ,M6020_yaw_speed            ,
	          M6020_YAW_SPEED_VOLTAFE_MAX  ,M6020_YAW_SPEED_VOLTAFE_MIN,
	          M6020_YAW_SPEED_MAXOUTPUT    ,M6020_YAW_SPEED_MINOUTPUT   );
	PID_Init(&M6020_yaw_angle_pid          ,M6020_yaw_angle            ,
	          M6020_YAW_ANGLE_VOLTAFE_MAX  ,M6020_YAW_ANGLE_VOLTAFE_MIN,
	          M6020_YAW_ANGLE_MAXOUTPUT    ,M6020_YAW_ANGLE_MINOUTPUT   );
	//6623pitch��ǶȻ� �ٶȻ� PID��ʼ��
	PID_Init(&M6020_pitch_speed_pid        ,M6020_pitch_speed            ,
	          M6020_PITCH_SPEED_VOLTAFE_MAX,M6020_PITCH_SPEED_VOLTAFE_MIN,
	          M6020_PITCH_SPEED_MAXOUTPUT  ,M6020_PITCH_SPEED_MINOUTPUT   );
	PID_Init(&M6020_pitch_angle_pid        ,M6020_pitch_angle            ,
	          M6020_PITCH_ANGLE_VOLTAFE_MAX,M6020_PITCH_ANGLE_VOLTAFE_MIN,
	          M6020_PITCH_ANGLE_MAXOUTPUT  ,M6020_PITCH_ANGLE_MINOUTPUT   );
	
	/***** 2006��ز�����ʼ�� *****/
	const static float M2006_speed[3] = {M2006_SPEED_PID_KP, M2006_SPEED_PID_KI, M2006_SPEED_PID_KD};
	const static float M2006_angle[3] = {M2006_ANGLE_PID_KP, M2006_ANGLE_PID_KI, M2006_ANGLE_PID_KD};
	PID_Init(&M2006_speed_pid          ,M2006_speed            ,
	          M2006_SPEED_VOLTAFE_MAX  ,M2006_SPEED_VOLTAFE_MIN,
	          M2006_SPEED_MAXOUTPUT    ,M2006_SPEED_MINOUTPUT   );
	PID_Init(&M2006_angle_pid          ,M2006_angle            ,
	          M2006_ANGLE_VOLTAFE_MAX  ,M2006_ANGLE_VOLTAFE_MIN,
	          M2006_ANGLE_MAXOUTPUT    ,M2006_ANGLE_MINOUTPUT   );
}

void gimbal_pid_calc(volatile float *yaw_angle_set,volatile float *pitch_angle_set,volatile float *pluck_angle_set,
	                   volatile float *yaw_angle    ,volatile float *pitch_angle    ,volatile float *pluck_angle     )
{
//	/***** 6623���˫�ջ����� *****/
//	//�Ա���������ֵ������ٶ� rad/s
//	yaw_gimbal_motor .angle_last      = yaw_gimbal_motor .angle_now;
//	yaw_gimbal_motor .angle_now       = M6623_encoder_yaw.ecd_angle;
//	yaw_gimbal_motor .angular_speed   = (yaw_gimbal_motor .angle_now - yaw_gimbal_motor .angle_last)/(0.001f*57.32f);
//	pitch_gimbal_motor .angle_last    = pitch_gimbal_motor .angle_now;
//	pitch_gimbal_motor .angle_now     = M6623_encoder_pitch.ecd_angle;
//	pitch_gimbal_motor .angular_speed = (pitch_gimbal_motor .angle_now - pitch_gimbal_motor .angle_last)/(0.001f*57.32f);
//	
//	//yaw�ᴮ��PID����
//	PID_Calc(&M6623_yaw_angle_pid, *yaw_angle, *yaw_angle_set );
//	PID_Calc(&M6623_yaw_speed_pid,-yaw_gimbal_motor .angular_speed,-M6623_yaw_angle_pid.pidout);
//	//pitch�ᴮ��PID����
//	PID_Calc(&M6623_pitch_angle_pid, *pitch_angle , *pitch_angle_set );
//	PID_Calc(&M6623_pitch_speed_pid,-pitch_gimbal_motor .angular_speed,-M6623_pitch_angle_pid.pidout);
//	can_send .yaw    = M6623_yaw_speed_pid.pidout  ;
//  can_send .pitch  = M6623_pitch_speed_pid.pidout;
	
	/***** 6020���˫�ջ����� *****/
	yaw_gimbal_motor .angular_speed   = M6020_encoder_yaw .speed_rpm *(2.0f*3.14f/60.0f);
	pitch_gimbal_motor .angular_speed = M6020_encoder_pitch .speed_rpm *(2.0f*3.14f/60.0f);
	pluck_motor .angular_speed        = encoder_pluck .speed_rpm *2.0f*3.14f/60.0f;
		//yaw�ᴮ��PID����
	PID_Calc(&M6020_yaw_angle_pid, *yaw_angle, *yaw_angle_set );
	PID_Calc(&M6020_yaw_speed_pid,yaw_gimbal_motor .angular_speed,M6020_yaw_angle_pid .pidout);
	//pitch�ᴮ��PID����
	PID_Calc(&M6020_pitch_angle_pid, *pitch_angle , *pitch_angle_set );
	PID_Calc(&M6020_pitch_speed_pid,pitch_gimbal_motor .angular_speed,M6020_pitch_angle_pid .pidout);
	//pluck����PID����
	PID_Calc(&M2006_angle_pid, *pluck_angle , *pluck_angle_set );
	PID_Calc(&M2006_speed_pid, pluck_motor .angular_speed,M2006_angle_pid .pidout);
	
}



//У׼����
#define GIMBAL_CALI_CALCULATE(angle_last, cmd_time, angle, angle_set, step)\
{                                                                          \
	if ((fabs(angle-angle_last)) < GIMBAL_CALI_GYRO_LIMIT){                  \
		(cmd_time)++;                                                          \
		if ((cmd_time) > GIMBAL_CALI_STEP_TIME){                               \
				(cmd_time) = 0;                                                    \
				(angle_set) = (angle);                                             \
				(step)++;}}                                                        \
}	
/***** ��̨У׼ģʽ��ִ��һ�Σ��õ���̨��λ�Ƕ� *****/
extern uint8_t chassis_mode , gimbal_mode;
extern uint8_t Gimbal_Cali_Complete;
void gimbal_cali(volatile Angle_t *pitch,volatile Angle_t *yaw,Encoder_t *encoder_yaw,Encoder_t *encoder_pitch)
{
	static uint16_t cali_time = 0;
	static uint16_t gimbal_cali_step =1 ;
	if(gimbal_cali_step == GIMBAL_CALI_YAW_MAX_STEP)
		{
			yaw ->angle_limit.last_angle  = encoder_yaw ->ecd_angle;
			can_send .yaw    = GIMBAL_CALI_MOTOR_SET ;
			can_send .pitch  = 0 ;
			can_send .pluck  = 0 ;
			can_send_mode = GIMBAL_CALI ;
			GIMBAL_CALI_CALCULATE(yaw ->angle_limit.last_angle , cali_time ,
			encoder_yaw ->ecd_angle , yaw ->angle_limit.max  , gimbal_cali_step);
		}
		else if(gimbal_cali_step == GIMBAL_CALI_YAW_MIN_STEP)
			{
				yaw ->angle_limit. last_angle = encoder_yaw ->ecd_angle;
			  can_send .yaw    = -GIMBAL_CALI_MOTOR_SET ;
			  can_send .pitch  = 0 ;
			  can_send .pluck  = 0 ;
				can_send_mode = GIMBAL_CALI ;
				GIMBAL_CALI_CALCULATE(yaw ->angle_limit. last_angle , cali_time ,
				encoder_yaw ->ecd_angle , yaw ->angle_limit. min  , gimbal_cali_step);
			}
			else if(gimbal_cali_step == GIMBAL_CALI_PITCH_MAX_STEP)
				{
					pitch ->angle_limit. last_angle = encoder_pitch ->ecd_angle;
					can_send .yaw    = 0 ;
					can_send .pitch  = GIMBAL_CALI_MOTOR_SET ;
					can_send .pluck  = 0 ;
					can_send_mode = GIMBAL_CALI ;
					GIMBAL_CALI_CALCULATE(pitch ->angle_limit. last_angle , cali_time ,
					encoder_pitch ->ecd_angle , pitch ->angle_limit. max , gimbal_cali_step);
				}
				else if(gimbal_cali_step == GIMBAL_CALI_PITCH_MIN_STEP)
					{
						pitch ->angle_limit. last_angle = encoder_pitch ->ecd_angle;
						can_send .yaw    = 0 ;
						can_send .pitch  = -GIMBAL_CALI_MOTOR_SET ;
						can_send .pluck  = 0 ;
						can_send_mode = GIMBAL_CALI ;
						GIMBAL_CALI_CALCULATE(pitch ->angle_limit. last_angle , cali_time ,
						encoder_pitch ->ecd_angle , pitch ->angle_limit. min  , gimbal_cali_step);
					}
					else if(gimbal_cali_step == GIMBAL_CALI_END_STEP)
						{
							pitch ->angle_limit. middle = (pitch ->angle_limit. max + pitch ->angle_limit. min)/2;
							yaw ->angle_limit. middle   = (yaw ->angle_limit. max   + yaw ->angle_limit. min)  /2;
							pitch ->angle_set = pitch ->angle_limit .middle;
							yaw  ->angle_set  = yaw ->angle_limit .middle  ;
							can_send_mode = GIMBAL_NORMAL ;
							gimbal_mode = GIMBAL_ENCODER ; 
							Gimbal_Cali_Complete ++ ;
						}
}
	
void GIMBAL_CAN_SEND()
{
	switch( can_send_mode )
	{
		case GIMBAL_CALI :
	  Set_Gimbal_Current(&hcan1, can_send .yaw , can_send .pitch , can_send .pluck );break;
		case GIMBAL_NORMAL :
		Set_Gimbal_Current(&hcan1,(int16_t)M6020_yaw_speed_pid.pidout ,(int16_t)M6020_pitch_speed_pid.pidout ,(int16_t)M2006_speed_pid .pidout);break;
		default :
	  Set_Gimbal_Current(&hcan1, 0 ,0 , 0 );break;
	}
}
