#include "global_header_file.h"

uint8_t g_u8_uart_rxByte[1] = {255};

// UART receive call back
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  // if (huart->Instance == USART3)
  {
    // handle rxByte
	HAL_UART_Receive_IT(&huart3, g_u8_uart_rxByte, 1);
	HAL_UART_Transmit(&huart3, g_u8_uart_rxByte, 1, 100);

  }
}
