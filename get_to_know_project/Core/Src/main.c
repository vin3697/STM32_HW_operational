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


// const char *led_on_msg = "LED On \r\n"; // stored in ROM

/**
  * @brief  The application entry point.
  * @retval int
  */


int main(void)
{

	project_init();

	project_uart_init(&g_system);

	while(1)
	{

		project_uart_main(&g_system);

	}
}




