#ifndef UARTHANDLER_INTERFACE_H
#define UARTHANDLER_INTERFACE_H

#define USART1_VECTORTABLE_NUM		 37ul
/*********************************************************************************************************************/


void HUART_Init(void);
/*********************************************************************************************************************/

void RCC_Handler(uint_32t baudRate,uint_8t stopBits,uint_8t parity,uint_8t dataBits);
/*********************************************************************************************************************/

void HUART_SendData(uint_8t *buffer , uint_16t len);
/*********************************************************************************************************************/

void HUART_ReceiveData(uint_8t *buffer , uint_16t len);

#endif
