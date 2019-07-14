/******************************************************************************
/// @brief
/// @copyright Copyright (c) 2017 <dji-innovations, Corp. RM Dept.>
/// @license MIT License
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction,including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense,and/or sell
/// copies of the Software, and to permit persons to whom the Software is furnished
/// to do so,subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
/// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
*******************************************************************************/

#ifndef __BSP_CAN
#define __BSP_CAN

#ifdef STM32F4
#include "stm32f4xx_hal.h"
#elif defined STM32F1
#include "stm32f1xx_hal.h"
#endif
#include "mytype.h"
#include "can.h"

/*CAN发送或是接收的ID*/
typedef enum
{

	CAN_2006Moto_ALL_ID = 0x200,
	CAN_M3508Moto1_ID = 0x201,
	CAN_M3508Moto2_ID = 0x202,
//	CAN_M3508Moto3_ID = 0x203,
//	CAN_M3508Moto4_ID = 0x204,
  CAN_YawMoto5_ID   = 0x208,
  CAN_PitchMoto6_ID = 0x206,
  CAN_M2006Moto7_ID = 0x207,
	}CAN_Message_ID;             //205与207相干扰，改Yaw为208

#define FILTER_BUF_LEN		5
#define RATE_BUF_SIZE     6
/*接收到的云台电机的参数结构体*/
typedef struct{
	int16_t	 	speed_rpm;
  float  	real_current;
  int16_t  	given_current;
  uint8_t  	hall;
	int32_t 	angle;				//编码器不经处理的原始值
	int32_t 	last_angle;	  //上一次编码器原始值
	int32_t	offset_angle;   //初始编码器值
	//////new
	float  ecd_angle;       //角度
	uint8_t  buf_count;
	int32_t  ecd_raw_rate;  //通过编码器计算得到速度原始值
	int32_t  diff;          //差值
	int32_t  temp_count;
	int32_t  filter_rate;   //速度
	int32_t rate_buf[RATE_BUF_SIZE];
	//////
	int32_t		round_cnt;
	int32_t		total_angle;
	u8			buf_idx;
	u16			angle_buf[FILTER_BUF_LEN];
	u16			fited_angle;
	u32			msg_cnt;
}moto_measure_t;

//typedef struct{
//  int32_t ecd_bias;				//初始编码器值
//	uint16_t ecd;           //机械角度（编码器不经处理原始值）
//  int16_t speed_rpm;      //转速
//  int16_t given_current;  //实际转矩电流
//  uint8_t temperate;      //电机温度
//  int16_t last_ecd;       //上一次机械角度（上一次的编码器原始值）
//	int32_t diff;			      //两次编码器之间的差值
//	int32_t round_cnt;			//圈数
//	int32_t temp_count;     //计数用
//	int32_t ecd_value;      //经过处理后连续的编码器值
//	float   ecd_angle_bias; //初始角度
//	float   ecd_angle;      //角度
//}Encoder_t;

//typedef enum{
//	false = 0,
//	true = 1
//}Bool;

/* Extern  ------------------------------------------------------------------*/
extern moto_measure_t  moto_chassis[];

float Angle_Precision_Filter(volatile moto_measure_t *Y);
void my_can_filter_init(CAN_HandleTypeDef* hcan);
void my_can_filter_init_recv_all(CAN_HandleTypeDef* _hcan);
void can_filter_recv_special(CAN_HandleTypeDef* hcan, uint8_t filter_number, uint16_t filtered_id);
void get_moto_measure(moto_measure_t *ptr, CAN_HandleTypeDef* hcan);
//void get_gimbal_measure(volatile Encoder_t *v, CAN_HandleTypeDef*_hcan);

void can_receive_onetime(CAN_HandleTypeDef* _hcan, int time);
void set_moto_current(CAN_HandleTypeDef* hcan, s16 iq1, s16 iq2);
void set_cloud_current(CAN_HandleTypeDef* hcan, s16 iq1, s16 iq2, s16 iq3, s16 iq4);

#endif
