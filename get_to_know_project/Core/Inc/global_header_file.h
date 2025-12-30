#ifndef __GLOBAL_HEADER__
#define __GLOBAL_HEADER__

	#include "main.h"
	#include "string.h"
	extern ETH_TxPacketConfig TxConfig;
	extern ETH_HandleTypeDef heth;
	extern I2C_HandleTypeDef hi2c1;
	extern UART_HandleTypeDef huart3;
	extern PCD_HandleTypeDef hpcd_USB_OTG_FS;


	// --------------------------------------------

	#include "project_init_h.h"
	#include "uart_communication.h"

	extern g_system_t g_system;
	// UART communication
	extern uint8_t g_u8_uart_rxByte[1];


	// function declaration
	void project_uart_init(g_system_t *const arg_g_system);
	void project_uart_main(g_system_t *const arg_g_system);
	void turn_off_system(void);
	void execute_control( g_system_t *const arg_g_system );


	// --------------------------------------------

#endif /* __GLOBAL_HEADER__ */
