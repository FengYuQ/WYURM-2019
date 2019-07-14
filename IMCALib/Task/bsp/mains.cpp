#include <ros.h>
#include "mains.h"
#include "mode.h"
#include "bsp_can.h"
#include <skyguard_msgs/gimbal.h>

extern Flag_t Flag;
extern int Timcount;
int Ros_connect_tim = 90000;
int32_t Yaw, Pitch, Poke, AngleStep=1476;

//421*100/8192/36*360=51.3度   100为对应系数，PID也相应改变，36为减速比
//对应度数编码器值：8192*减速比*度数/(360*100)

//#if imca_msg

//void fire_callback(const imca_msgs::fire& r1xbuff);
//void gimbal_callback(const imca_msgs::gimbal& rxbuff);

//ros::NodeHandle nh;

//imca_msgs::gimbal gimbalctr_rec;
//imca_msgs::fire firectr_rec;

//ros::Subscriber<imca_msgs::fire> firectr("firectr", fire_callback);
//ros::Subscriber<imca_msgs::gimbal> gimbalctr("gimbalctr", gimbal_callback);

//void gimbal_callback( const imca_msgs::gimbal& rxbuff)
//{
//    gimbalctr_rec = rxbuff;
//		set_ag1 = gimbalctr_rec.yaw;
//	  set_ag2 = gimbalctr_rec.pitch;
//}

//void fire_callback( const imca_msgs::fire& rxbuff)
//{
//		firectr_rec = rxbuff;
//}

//#endif

//#if skyguard_msg

void gimbal_callback(const skyguard_msgs::gimbal& rxbuff);

ros::NodeHandle nh;

skyguard_msgs::gimbal gimbalctr_rec;
skyguard_msgs::gimbal gimbal_pos;

ros::Subscriber<skyguard_msgs::gimbal> gimbalctr("gimbalctr", gimbal_callback);
ros::Publisher gimbal_position("position", &gimbal_pos);

void gimbal_callback( const skyguard_msgs::gimbal& rxbuff)
{		
	if(Flag.ResidueFlag == 0)
 {
    gimbalctr_rec = rxbuff;
	  
	 if(gimbalctr_rec.shoot == 3)    //开始攻击模式
	 {
		 Yaw = gimbalctr_rec.yaw;
	   Pitch = gimbalctr_rec.pitch + 70;
		 Timcount = 0;
		 Flag.Mode = 1;
		 Flag.Partrol = 0;
	 }
	 else if(gimbalctr_rec.shoot == 1)  //到达目标点
	 {
//		 if(Flag.GetPos == 1){
		 Yaw = gimbalctr_rec.yaw;
	   Pitch = gimbalctr_rec.pitch + 70;
//		 Flag.GetPos = 0;
//		 }
		 Poke = -1300;
	  }
	 else if(gimbalctr_rec.shoot == 0)  //反馈位置
	 {
		 gimbal_pos.yaw = moto_chassis[2].total_angle;
		 gimbal_pos.pitch = moto_chassis[3].total_angle;
		 
		 if(Flag.Mode == 1){
			gimbal_pos.shoot = 1;
		}
		else if(Flag.Mode == 0){
			gimbal_pos.shoot = 0;
		}
		 gimbal_position.publish(&gimbal_pos);
		
	 }
	 else if(gimbalctr_rec.shoot == 2)  //无识别，清空拨弹
	{
//		Flag.Mode = 1;
		Poke = 0;
	}

 }
}

//#endif

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->flush();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->reset_rbuf();
}

void SETUP(void)
{
  nh.initNode();
	nh.advertise(gimbal_position);
	nh.subscribe(gimbalctr);
	
	while (!nh.connected()){
		if(HAL_GetTick()>Ros_connect_tim)
		{
			break;
		}
		nh.spinOnce();
	}   
	
	nh.loginfo("Skyguard Connected!");
	
}

void loop(void)
{  
	nh.spinOnce();
}

