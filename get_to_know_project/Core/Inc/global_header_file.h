#ifndef __GLOBAL_HEADER__
#define __GLOBAL_HEADER__

	#include "main.h"
	#include "string.h"

	#include "project_init_h.h"
	
	extern ETH_TxPacketConfig TxConfig;
	extern ETH_HandleTypeDef heth;
	extern I2C_HandleTypeDef hi2c1;
	extern UART_HandleTypeDef huart3;
	extern PCD_HandleTypeDef hpcd_USB_OTG_FS;

	extern 	uint8_t g_u8_uart_rxByte[1];
	
#endif /* __GLOBAL_HEADER__ */
