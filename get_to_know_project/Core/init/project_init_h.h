

#ifndef __INIT_HEADER__
#define __INIT_HEADER__

	#include "global_header_file.h"

	/* function prototypes -----------------------------------------------*/
	void SystemClock_Config(void);
	void MPU_Config(void);
	void MX_GPIO_Init(void);
	void MX_ETH_Init(void);
	void MX_I2C1_Init(void);
	void MX_USART3_UART_Init(void);
	void MX_USB_OTG_FS_PCD_Init(void);
	void project_init(void);



#endif // __INIT_HEADER__
