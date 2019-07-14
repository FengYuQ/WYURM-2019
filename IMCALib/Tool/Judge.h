#ifndef  __Judge_H
#define  __Judge_H

#include "main.h"

unsigned char Get_CRC8_Check_Sum(unsigned char *pchMessage,unsigned int dwLength,unsigned char ucCRC8);
unsigned int Verify_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength);
void Append_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength);
uint16_t Get_CRC16_Check_Sum(uint8_t *pchMessage,uint32_t dwLength,uint16_t wCRC);
uint32_t Verify_CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength);
void Append_CRC16_Check_Sum(uint8_t * pchMessage,uint32_t dwLength);

//��ʽת��������(�����ڴ棬����ֱ���໥ת��)
typedef union
{
    uint8_t U[4];
    float F;
    int I;
		
}FormatTrans;    


//����������״̬(0x0001)
typedef __packed struct {
uint16_t stageRemianTime; //����ʣ��ʱ��
uint8_t gameProgress;  //��ǰ�����׶�
uint8_t robotLevel; 	//�����˵ȼ�
uint16_t remainHP;    //�����˵�ǰѪ��
uint16_t maxHP;				//��������Ѫ��
}extGameRobotState_t;

/*************************2018����ϵͳ��������**************************************/
//�˺�����(0x0002)
typedef __packed struct
{
	uint8_t armorType : 4;   
	uint8_t hurtType : 4;
}extRobotHurt_t;

//ʵʱ�����Ϣ(0x0003)
typedef __packed struct
{
	uint8_t bulletType;  
	uint8_t bulletFreq;	 
	float bulletSpeed;
}exShootData_t;

//ʵʱ������������
typedef __packed struct
{
	float chassisVolt;
	float chassisCurrent;
	float chassisPower;
	float chassisPowerBuffer;
	uint16_t shooterHeat0;
	uint16_t shooterHeat1;
}exPowerHeatData_t;

/*************************2018����ϵͳ��������**************************************/



/*************************2019����ϵͳ��������**************************************/

//ʵʱ������������
typedef __packed struct
{ 
	uint16_t chassis_volt;    //�����ѹ
  uint16_t chassis_current;		//�������
  float chassis_power;				//�������
  uint16_t chassis_power_buffer; 
  uint16_t shooter_heat0; 
  uint16_t shooter_heat1;
} ext_power_heat_data_t;

//������״̬�ṹ��
typedef __packed struct
{
	uint8_t robot_id;
  uint8_t robot_level;
  uint16_t remain_HP;   //ʣ��Ѫ��
  uint16_t max_HP;			//��ѪѪ��
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

