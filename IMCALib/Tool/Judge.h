#ifndef  __Judge_H
#define  __Judge_H

#include "main.h"

unsigned char Get_CRC8_Check_Sum(unsigned char *pchMessage,unsigned int dwLength,unsigned char ucCRC8);
unsigned int Verify_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength);
void Append_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength);
uint16_t Get_CRC16_Check_Sum(uint8_t *pchMessage,uint32_t dwLength,uint16_t wCRC);
uint32_t Verify_CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength);
void Append_CRC16_Check_Sum(uint8_t * pchMessage,uint32_t dwLength);

//格式转换联合体(共用内存，里面直接相互转换)
typedef union
{
    uint8_t U[4];
    float F;
    int I;
		
}FormatTrans;    


//比赛机器人状态(0x0001)
typedef __packed struct {
uint16_t stageRemianTime; //比赛剩余时间
uint8_t gameProgress;  //当前比赛阶段
uint8_t robotLevel; 	//机器人等级
uint16_t remainHP;    //机器人当前血量
uint16_t maxHP;				//机器人满血量
}extGameRobotState_t;

/*************************2018裁判系统定义数据**************************************/
//伤害数据(0x0002)
typedef __packed struct
{
	uint8_t armorType : 4;   
	uint8_t hurtType : 4;
}extRobotHurt_t;

//实时射击信息(0x0003)
typedef __packed struct
{
	uint8_t bulletType;  
	uint8_t bulletFreq;	 
	float bulletSpeed;
}exShootData_t;

//实时功率热量数据
typedef __packed struct
{
	float chassisVolt;
	float chassisCurrent;
	float chassisPower;
	float chassisPowerBuffer;
	uint16_t shooterHeat0;
	uint16_t shooterHeat1;
}exPowerHeatData_t;

/*************************2018裁判系统定义数据**************************************/



/*************************2019裁判系统定义数据**************************************/

//实时功率热量数据
typedef __packed struct
{ 
	uint16_t chassis_volt;    //输出电压
  uint16_t chassis_current;		//输出电流
  float chassis_power;				//输出功率
  uint16_t chassis_power_buffer; 
  uint16_t shooter_heat0; 
  uint16_t shooter_heat1;
} ext_power_heat_data_t;

//机器人状态结构体
typedef __packed struct
{
	uint8_t robot_id;
  uint8_t robot_level;
  uint16_t remain_HP;   //剩余血量
  uint16_t max_HP;			//满血血量
  uint16_t shooter_heat0_cooling_rate; 
  uint16_t shooter_heat0_cooling_limit; 
  uint16_t shooter_heat1_cooling_rate; 
  uint16_t shooter_heat1_cooling_limit; 
  uint8_t mains_power_gimbal_output : 1; 
  uint8_t mains_power_chassis_output : 1; 
  uint8_t mains_power_shooter_output : 1;
} ext_game_robot_state_t;


void data_2018_analysis(void);
void data_2019_analysis(void);

#endif

