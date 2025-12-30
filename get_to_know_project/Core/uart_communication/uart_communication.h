/*
 * uart_communication.h
 *
 *  Created on: 30 Dec 2025
 *      Author: vinay
 */

#ifndef UART_COMMUNICATION_UART_COMMUNICATION_H_
#define UART_COMMUNICATION_UART_COMMUNICATION_H_

	#include "global_header_file.h"

	// System defines
	#define CYCLE_TIME				100u
	#define TOGGGLE_LED_YELLOW		0x00
	#define TOGGGLE_LED_BLUE		0x01
	#define TOGGGLE_LED_RED 		0x02

	#define OP_CMD_MIN				0x00
	#define OP_CMD_MAX				0x0A

	typedef enum
	{
		work_mode		 = 0,
		inactive_mode		,
	}system_mode_t;

	typedef struct
	{

		// timing operations
		uint32_t u32_cycle_time_ms 			;
		uint32_t u32_current_time_instace 	;

		system_mode_t	system_mode;

		// received information from UAR
		uint8_t u8_operation_command;

	}g_system_t;

#endif /* UART_COMMUNICATION_UART_COMMUNICATION_H_ */
