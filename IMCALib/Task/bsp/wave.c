#include "bsp_can.h"
#include "stm32f4xx_hal.h"
#include "usart.h"
#include "wave.h"

extern int32_t set_ag1, set_ag2;
short  wave_form_data[6] = {0};

void send_data(uint8_t date)
{
	HAL_UART_Transmit(&huart1,&date,1,10);
	//while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);  
	
}

void shanwai_send_wave_form(void)
{
	uint8_t i;
	
	send_data(0x03);
	send_data(0xfc);
	for(i = 0;i<6;i++)
	{
	  send_data((wave_form_data[i]&0xff)); //现发送低位在发送高位
//	  send_data((wave_form_data[i]>>8));
	}
	
	send_data(0xfc);
	send_data(0x03);
}

void shanwai_sprintf()
{
	  wave_form_data[0] = (float)set_ag1;
	  wave_form_data[1] = (float)moto_chassis[4].total_angle/100;
	  wave_form_data[2] = (float)set_ag2;
	  wave_form_data[3] = (float)moto_chassis[5].ecd_angle;
	  wave_form_data[4] = (float)moto_chassis[5].ecd_angle;
	  wave_form_data[5] = (float)moto_chassis[5].ecd_angle;
	shanwai_send_wave_form();   //将数据传输到三外上位机，可以看到实时波形
}

