#include "global_header_file.h"

uint8_t g_u8_uart_rxByte[1] = {255};

// global instance for system specific to UART communication
g_system_t g_system;


void project_uart_init(g_system_t *const arg_g_system)
{

	arg_g_system->u32_cycle_time_ms 			= 0;
	arg_g_system->u32_current_time_instace		= 0;

	arg_g_system->system_mode					= inactive_mode;
	arg_g_system->u8_operation_command			= 0xFF;

	return;
}


// UART receive call back
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART3)
  {
    // handle rxByte
	HAL_UART_Receive_IT(&huart3, g_u8_uart_rxByte, 1);
	// HAL_UART_Transmit(&huart3, g_u8_uart_rxByte, 1, 100);

  }
}

void turn_off_system(void)
{

	// turn off the system
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);

	return;
}


void control_LEDs( 	GPIO_TypeDef *toggle_GPIOx, GPIO_TypeDef *off_firstLED_GPIOx, GPIO_TypeDef *off_secondLED_GPIOx,
					uint16_t toggle_GPIO_Pin  ,	uint16_t off_firstLED_GPIO_Pin  , uint16_t off_secondLED_GPIO_Pin )
{

	HAL_GPIO_TogglePin( (GPIO_TypeDef *) toggle_GPIOx, toggle_GPIO_Pin); // yellow
	//HAL_Delay (500);   /* Insert delay 100 ms */

	HAL_GPIO_WritePin( 	(GPIO_TypeDef *) off_firstLED_GPIOx, off_firstLED_GPIO_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin( 	(GPIO_TypeDef *) off_secondLED_GPIOx, off_secondLED_GPIO_Pin, GPIO_PIN_RESET);

	return;

}

void execute_control( g_system_t *const arg_g_system )
{

	switch (arg_g_system->u8_operation_command)
	{

		case TOGGGLE_LED_YELLOW:
		{

			control_LEDs( 	GPIOB, 		GPIOB, 		GPIOB,
							GPIO_PIN_0, GPIO_PIN_7, GPIO_PIN_14);

			break;
		}

		case TOGGGLE_LED_BLUE:
		{

			control_LEDs( 	GPIOB, 		GPIOB, 		GPIOB,
							GPIO_PIN_7, GPIO_PIN_0, GPIO_PIN_14);

			break;
		}

		case TOGGGLE_LED_RED:
		{

			control_LEDs( 	GPIOB, 		GPIOB, 		GPIOB,
							GPIO_PIN_14, GPIO_PIN_0, GPIO_PIN_7);

			break;
		}

		default:
		{

			// turn_off_system();
			break;
		}

	 }

	return;
}


void project_uart_main(g_system_t *const arg_g_system)
{

	if(arg_g_system == NULL)
	{
		arg_g_system->system_mode = inactive_mode;
	}
	else
	{
		// do nothing
	}

	arg_g_system->u32_current_time_instace 	= HAL_GetTick();

	if( ( arg_g_system->u32_current_time_instace - arg_g_system->u32_cycle_time_ms ) >= CYCLE_TIME )
	{

		// read the input
		// done at the UART interrupt receiving
		arg_g_system->u8_operation_command 		= g_u8_uart_rxByte[0];

		// processing the inputs
		// none


		// system mode selection : work mode and system off
		if( (OP_CMD_MIN <= arg_g_system->u8_operation_command) && ( arg_g_system->u8_operation_command <= OP_CMD_MAX))
		{
			arg_g_system->system_mode = work_mode;
		}
		else
		{
			arg_g_system->system_mode = inactive_mode;
		}


		// execution of the system operations
		switch(arg_g_system->system_mode)
		{

			case work_mode:
			{
				// Operation
				execute_control( arg_g_system );
				break;
			}

			case inactive_mode:
			{
				turn_off_system();
				break;
			}

			default:
			{
				turn_off_system();
				break;
			}

		}

		// send the information to GUI or on UART
		HAL_UART_Transmit(&huart3, &arg_g_system->u8_operation_command, 1, 100);

		arg_g_system->u32_cycle_time_ms = HAL_GetTick();

	}else{
			// do nothing
	}


	return;
}




