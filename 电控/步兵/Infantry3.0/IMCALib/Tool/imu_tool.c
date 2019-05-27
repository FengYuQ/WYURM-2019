#include "imu_task.h"
#include "inv_mpu.h"
#include "mpu9250.h"
#include "main.h"
#include "cmsis_os.h"

IMU_data_t  IMU_data;
IMU_t IMU;

uint8_t Get_IMU_Data(void)
{	
	uint8_t result;  
	result = mpu_dmp_get_data(&IMU_data.pitch, &IMU_data.roll, &IMU_data.yaw);
	if(result)return 1;
	IMU.pitch = IMU_data .pitch + 180.0f;
	IMU.yaw   = IMU_data .yaw   + 180.0f;
	IMU.roll  = IMU_data .roll  + 180.0f;
	result = MPU9250_GetGyro(&IMU.gyrox, &IMU.gyroy, &IMU.gyroz);
	if(result)return 1;
//	result = MPU9250_GetAccel(&IMU.accx, &IMU.accy, &IMU.accz);
//	if(result)return 1;
	return 0;
}

/**
  * @brief  ��ȡmpu9250���ٶ�
  * @param  X����ٶȴ洢��ַ
  * @param  Y����ٶȴ洢��ַ
  * @param  Z����ٶȴ洢��ַ
  * @note   Ĭ�����̡�2000��
  * @retval 0��ȡ�ɹ�       1��ȡʧ��
  */
uint8_t MPU9250_GetGyro(float *X, float *Y, float *Z)
{
    unsigned long timestamp;
    
    if(mpu_get_gyro_reg(IMU_data.gyro, &timestamp))
    {
        return 1;
    }
    else
    {
        *X = 0.0610352F * IMU_data.gyro[0];
        *Y = 0.0610352F * IMU_data.gyro[1];
        *Z = 0.0610352F * IMU_data.gyro[2];
        
        return 0;
    }
}

/**
  * @brief  ��ȡmpu9250�������ٶ�
  * @param  X���������ٶȴ洢��ַ
  * @param  Y���������ٶȴ洢��ַ
  * @param  Z���������ٶȴ洢��ַ
  * @note   Ĭ�����̡�2g��
  * @retval 0��ȡ�ɹ�       1��ȡʧ��
  */
uint8_t MPU9250_GetAccel(float *X, float *Y, float *Z)
{
    unsigned long timestamp;
    
    if(mpu_get_accel_reg(IMU_data.acc, &timestamp))
    {
        return 1;
    }
    else
    {
        *X = 2 * Acceleration_Of_Gravity * IMU_data.acc[0] / 32768;
        *Y = 2 * Acceleration_Of_Gravity * IMU_data.acc[1] / 32768;
        *Z = 2 * Acceleration_Of_Gravity * IMU_data.acc[2] / 32768;
        
        return 0;
    }
}

