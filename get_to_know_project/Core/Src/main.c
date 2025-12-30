/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */


#include "global_header_file.h"


#define CYCLE_TIME							1000u

static uint32_t u32_cycle_time_ms 			= 0;
static uint32_t u32_current_time_instace 	= 0;

const char *led_on_msg = "LED On \r\n"; // stored in ROM

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

	project_init();

	while(1)
	{

		u32_current_time_instace = HAL_GetTick();

		// g_u8_uart_rxByte_ascii = (uint8_t)('0' + g_u8_uart_rxByte[0]);

		if( ( u32_current_time_instace - u32_cycle_time_ms ) >= CYCLE_TIME )
		{

			switch (g_u8_uart_rxByte[0])
			{

				case 0:
				{
					HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0); // yellow
					//HAL_Delay (500);   /* Insert delay 100 ms */
					break;
				}

				case 1:
				{
					HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);	// blue
					//HAL_Delay (500);   /* Insert delay 100 ms */
					break;
				}

				case 2:
				{
					HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);	// red
					//HAL_Delay (500);   /* Insert delay 100 ms */
					break;
				}

				default:
				{
					break;
				}

			 }

			HAL_UART_Transmit(&huart3, g_u8_uart_rxByte, 1, 100);

			u32_cycle_time_ms = HAL_GetTick();
		}
		else
		{
				// do nothing
		}

	}
}




