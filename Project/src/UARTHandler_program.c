/*
 * Handler_program.c
 *
 *  Created on: Mar 27, 2020
 *      Author: MennaTullah Mostafa
 */
#include "GPIO_interface.h"
#include "RCC_interface.h"
#include "NVIC_interface.h"
#include "UART_interface.h"
#include "UARTHandler_interface.h"
#include "UART_interface.h"

/*********************************************************************************************************************/

void HUART_Init(void){
	UART_Init();
	GPIO_t TxPin;
	GPIO_t RxPin;
	TxPin.pin=PIN9;
	TxPin.mode=MODE_ALTERNATIVROUTPUT_PUSHPULL;
	TxPin.port=PORTA;
	TxPin.speed=SPEED_50MHZ;
	RxPin.pin=PIN10;
	RxPin.mode=MODE_INPUT_INPUTFLOATING;
	RxPin.port=PORTA;
	RxPin.speed=SPEED_50MHZ;

	GPIO_u8SetConfiguration(&TxPin);
	GPIO_u8SetConfiguration(&RxPin);

	NVIC_ClearPending(USART1_VECTORTABLE_NUM);
	NVIC_EnableInterrupt(USART1_VECTORTABLE_NUM);
	NVIC_setPending(USART1_VECTORTABLE_NUM);
	RCC_voidEnPeriClk(USART1_PERIPHERAL);

}
/*********************************************************************************************************************/

void HUART_Configuration(uint_32t baudRate,uint_8t stopBits,uint_8t parity,uint_8t dataBits)
{
	uint_32t SysClk;
	SysClk = RCC_u32GetSysClkValue();
	UART_Config(baudRate,stopBits,parity,dataBits,&SysClk);
}
/*********************************************************************************************************************/

void HUART_SendData(uint_8t *buffer , uint_16t len)
{
	UART_sendBuffer(buffer,len);
}
/*********************************************************************************************************************/


void HUART_ReceiveData(uint_8t *buffer , uint_16t len)
{
	UART_receiveBuffer(buffer,len);
}
