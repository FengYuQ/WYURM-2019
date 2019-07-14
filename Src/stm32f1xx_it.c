/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
#include "Driver_Judge.h"
#include "commondatastructure.h" //用于16进制转换小数
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
FloatTrans  FT;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
client_custom_data_t client_custom_data;
client_custom_data_t receive_407_data;
uint8_t usart2_rx_buffer[BUFFER_SIZE] = {0};
uint8_t usart2_tx_buffer[28] = {0};
uint8_t usart1_rx_buffer[BUFFER_SIZE] = {0};
uint8_t usart1_tx_buffer[28] = {0};
/* 串口接收完成标记 */
uint8_t usart2_recv_end_flag = 0;
uint8_t usart1_recv_end_flag = 0;
/* 串口接收数据长度 */
uint16_t usart2_rx_len = 0;
uint16_t usart1_rx_len = 0;
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 channel4 global interrupt.
  */
void DMA1_Channel4_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel4_IRQn 0 */

  /* USER CODE END DMA1_Channel4_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_tx);
  /* USER CODE BEGIN DMA1_Channel4_IRQn 1 */

  /* USER CODE END DMA1_Channel4_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel5 global interrupt.
  */
void DMA1_Channel5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel5_IRQn 0 */

  /* USER CODE END DMA1_Channel5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_rx);
  /* USER CODE BEGIN DMA1_Channel5_IRQn 1 */

  /* USER CODE END DMA1_Channel5_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel6 global interrupt.
  */
void DMA1_Channel6_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel6_IRQn 0 */

  /* USER CODE END DMA1_Channel6_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_rx);
  /* USER CODE BEGIN DMA1_Channel6_IRQn 1 */

  /* USER CODE END DMA1_Channel6_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel7 global interrupt.
  */
void DMA1_Channel7_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel7_IRQn 0 */

  /* USER CODE END DMA1_Channel7_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_tx);
  /* USER CODE BEGIN DMA1_Channel7_IRQn 1 */

  /* USER CODE END DMA1_Channel7_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */
	uint32_t tmp_flag = 0;
	uint32_t temp;
	uint8_t usart2_crc8;
	uint16_t usart2_wcrc;
	const unsigned char usart2_CRC8_INIT = 0xff;
	uint16_t CRC_INIT = 0xffff;
  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */
tmp_flag =__HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE);
	if((tmp_flag != RESET)){

	__HAL_UART_CLEAR_IDLEFLAG(&huart1);

	/* 读取串口状态寄存器（芯片型号不同，寄存器名称可能需要修改） */
	temp = huart1.Instance->SR;
	/* 读取串口数据寄存器（芯片型号不同，寄存器名称可能需要修改） */
	temp = huart1.Instance->DR;
	HAL_UART_DMAStop(&huart1);
	/* 读取DMA剩余传输数量（芯片型号不同，寄存器名称可能需要修改） */
	temp= hdma_usart1_rx.Instance->CNDTR;

	if(temp == BUFFER_SIZE - 28)
		{
			if (usart1_rx_buffer[5] == 01 &&usart1_rx_buffer[6] == 03 && Verify_CRC16_Check_Sum(usart1_rx_buffer, 28))
			{
					FT.U[3] = usart1_rx_buffer[16];
					FT.U[2] = usart1_rx_buffer[15];
					FT.U[1] = usart1_rx_buffer[14];
					FT.U[0] = usart1_rx_buffer[13];
					receive_407_data .data1  = FT.F;
					FT.U[3] = usart1_rx_buffer[20];
					FT.U[2] = usart1_rx_buffer[19];
					FT.U[1] = usart1_rx_buffer[18];
					FT.U[0] = usart1_rx_buffer[17];
					receive_407_data .data2  = FT.F;
					FT.U[3] = usart1_rx_buffer[24];
					FT.U[2] = usart1_rx_buffer[23];
					FT.U[1] = usart1_rx_buffer[22];
					FT.U[0] = usart1_rx_buffer[21];
					receive_407_data .data3  = FT.F;
				  receive_407_data .masks = usart1_rx_buffer[25];
				
			}
		client_custom_data.data1 = Supercap_percent;
		client_custom_data.data2 = receive_407_data .data2;
		client_custom_data.data3 = receive_407_data .data3;
		client_custom_data.masks = receive_407_data .masks;
		usart2_crc8 = Get_CRC8_Check_Sum(&usart2_tx_buffer[0],5-1,usart2_CRC8_INIT);
		usart2_wcrc = Get_CRC16_Check_Sum(usart2_tx_buffer,28-2,CRC_INIT);
		usart2_tx_buffer[0] = 0xA5;
		usart2_tx_buffer[1] = 19;
		usart2_tx_buffer[2] = 0x00;
		usart2_tx_buffer[3] = 1;
		usart2_tx_buffer[4] = usart2_crc8;
		
		usart2_tx_buffer[5] = 0x01;
		usart2_tx_buffer[6] = 0x03;
		usart2_tx_buffer[7] = 0x80;
		usart2_tx_buffer[8] = 0xD1;
		usart2_tx_buffer[9] = 14;
		usart2_tx_buffer[10] = 0;
		usart2_tx_buffer[11] = 0x14;	
		usart2_tx_buffer[12] = 0x01;
		Float_to_Byte(&client_custom_data.data1,usart2_tx_buffer,13);
		Float_to_Byte(&client_custom_data.data2,usart2_tx_buffer,17);
		Float_to_Byte(&client_custom_data.data3,usart2_tx_buffer,21);
		usart2_tx_buffer[25] = client_custom_data.masks ;
		usart2_tx_buffer[26] = usart2_wcrc& 0x00ff;;
		usart2_tx_buffer[27] =(usart2_wcrc >> 8) & 0xff;
		}			
		
	usart1_rx_len =BUFFER_SIZE - temp;
	usart1_recv_end_flag = 1;
	}
  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */
	uint32_t tmp_flag = 0;
	uint32_t temp;
	uint8_t usart1_crc8;
	uint16_t usart1_wcrc;
	const unsigned char usart1_CRC8_INIT = 0xff;
	uint16_t CRC_INIT = 0xffff;
  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */
	tmp_flag =__HAL_UART_GET_FLAG(&huart2,UART_FLAG_IDLE);
	if((tmp_flag != RESET)){

	__HAL_UART_CLEAR_IDLEFLAG(&huart2);

	/* 读取串口状态寄存器（芯片型号不同，寄存器名称可能需要修改） */
	temp = huart2.Instance->SR;
	/* 读取串口数据寄存器（芯片型号不同，寄存器名称可能需要修改） */
	temp = huart2.Instance->DR;
	HAL_UART_DMAStop(&huart2);
	/* 读取DMA剩余传输数量（芯片型号不同，寄存器名称可能需要修改） */
	temp= hdma_usart2_rx.Instance->CNDTR;
	//A5 14 00 89 07 04 00 13 A8 B3 41 18 2F 27 3D 73 81 6A 3F 00 00 70 42 00 00 00 00 97 EC   实时热量数据
	//A5 10 00 8A 7B 08 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 31 44               机器人位置信息

	//29是实时热量数据长度，25是机器人位置信息数据长度,都为50HZ发送一次，而且为同时发送的
	if(temp == BUFFER_SIZE - 23 - 25 || temp == BUFFER_SIZE - 23 - 25 -24)
		{
			if (usart2_rx_buffer[5] == 02 &&usart2_rx_buffer[6] == 02 && Verify_CRC16_Check_Sum(usart2_rx_buffer, 23))
			{
					FT.U[3] = usart2_rx_buffer[14];
					FT.U[2] = usart2_rx_buffer[13];
					FT.U[1] = usart2_rx_buffer[12];
					FT.U[0] = usart2_rx_buffer[11];
					ext_power_heat_data .chassis_power = FT.F;
				  FT.U[1] = usart2_rx_buffer[18];
				  FT.U[0] = usart2_rx_buffer[17];
				  ext_power_heat_data .shooter_heat0 = FT.I;			
			}
				if (usart2_rx_buffer[53] == 01 &&usart2_rx_buffer[54] == 02 && Verify_CRC16_Check_Sum(&usart2_rx_buffer[48],24))
					{
						FT.U[1] = usart2_rx_buffer[64];
				    FT.U[0] = usart2_rx_buffer[63];
						ext_game_robot_state .shooter_heat0_cooling_limit = FT.I;
					}	
		}			
		
	usart2_rx_len =BUFFER_SIZE - temp;
	usart2_recv_end_flag = 1;
	}
    send_out_407_data .chassis_power = ext_power_heat_data .chassis_power ;
	  send_out_407_data .shooter_heat0 = ext_power_heat_data .shooter_heat0 ;
	  send_out_407_data .shooter_heat0_cooling_limit = ext_game_robot_state .shooter_heat0_cooling_limit;
		usart1_crc8 = Get_CRC8_Check_Sum(&usart1_tx_buffer[0],5-1,usart1_CRC8_INIT);
		usart1_wcrc = Get_CRC16_Check_Sum(usart1_tx_buffer,17-2,CRC_INIT);
		usart1_tx_buffer[0] = 0xA5;
		usart1_tx_buffer[1] = 19;
		usart1_tx_buffer[2] = 0x00;
		usart1_tx_buffer[3] = 1;
		usart1_tx_buffer[4] = usart1_crc8;
		usart1_tx_buffer[5] = 0x02;
		usart1_tx_buffer[6] = 0x02;
		Float_to_Byte(&send_out_407_data .chassis_power,usart1_tx_buffer,7);
		usart1_tx_buffer[11] = send_out_407_data .shooter_heat0 & 0x00ff;
		usart1_tx_buffer[12] = (send_out_407_data .shooter_heat0 >> 8) & 0xff;
		usart1_tx_buffer[13] = send_out_407_data .shooter_heat0_cooling_limit & 0x00ff;
		usart1_tx_buffer[14] = (send_out_407_data .shooter_heat0_cooling_limit >> 8) & 0xff;
		usart1_tx_buffer[15] = usart1_wcrc& 0x00ff;
		usart1_tx_buffer[16] =(usart1_wcrc >> 8) & 0xff;
  	HAL_UART_Transmit_DMA(&huart1,usart1_tx_buffer,17);
  /* USER CODE END USART2_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
