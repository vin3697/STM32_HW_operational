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


#define CYCLE_TIME							100u

static uint32_t u32_cycle_time_ms 			= 0;
static uint32_t u32_current_time_instace 	= 0;

static uint8_t	b_first_cycle				= 0xFF;
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	while(1)
	{
		if(b_first_cycle == 0xFF)
		{
			project_init();
		}
		else
		{
			// do nothing
		}

		u32_current_time_instace = HAL_GetTick();

		if( ( u32_current_time_instace - u32_cycle_time_ms ) == CYCLE_TIME )
		{
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
			//HAL_Delay (500);   /* Insert delay 100 ms */

			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
			//HAL_Delay (500);   /* Insert delay 100 ms */

			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
			//HAL_Delay (500);   /* Insert delay 100 ms */

			u32_cycle_time_ms = HAL_GetTick();
		}

		b_first_cycle = 0x00;
	}
}




