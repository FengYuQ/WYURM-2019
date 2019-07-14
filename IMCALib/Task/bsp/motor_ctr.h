#ifndef _MOTOR_CTR_H_
#define _MOTOR_CTR_H_

void Gimbal_task(void);
void Chassis_task(void);
void Send_Can(void);
void Pid_init(void);
void Change_direction(void);
void SpdCut(void);
void RampInit(void);
void Gimpar(void);

//#define TwoMove 0
#define random(x,y) (rand()%(y-x+1)+x)
#define VAL_LIMIT(val, min, max)\
if(val<=min)\
{\
	val = min;\
}\
else if(val>=max)\
{\
	val = max;\
}\


#endif
