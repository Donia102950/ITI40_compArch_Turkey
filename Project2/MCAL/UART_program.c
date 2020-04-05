/*
 * UART_program.c
 *
 *  Created on: Mar 27, 2020
 *      Author: MennaTullah Mostafa
 */

/***************************************Libraries*********************************************************************/
#include "UART_interface.h"
#include "UARTHandler_interface.h"

/***************************************structure of UART Registers**************************************************/
typedef struct{
	uint_32t USART_SR;
	uint_32t USART_DR;
	uint_32t USART_BRR;
	uint_32t USART_CR1;
	uint_32t USART_CR2;
	uint_32t USART_CR3;
	uint_32t USART_GTPR;
}UART_Reg;

/***************************************Data Buffer to send or receive***********************************************/
typedef struct
{
	uint_8t *ptr;
	uint_32t Position;
	uint_8t size;
	uint_8t state;
} data_Buffer;

/*************************************create variables from data buffer structure for data buffer transmission and data buffer receive**********************/
static data_Buffer txBuffer;
static data_Buffer rxBuffer;

/*	Description: Function used to initialize UART1
 * Input parameters: void
 * Output parameters:
 * */
void UART_Init(void){
	/*
	 * 1. Enable the USART by writing the UE bit in USART_CR1 register to 1.
	 * 2. Clear TC flag to indicate transmission complete as its reset value is 1
	 * */
	USART1->USART_CR1 |= USART_CR1_UE;
	USART1->USART_SR &= ~(USART_SR_TC);
	/*
	 * 3. Enable Interrupt of UART in NVIC but this step is done by Handler in HAL layer
	 * */
	HUART_Init();
	/*
	 * 4. Enable TXE interrupt as a USART interrupt is generated whenever TXE=1 in the USART_SR register
	 * 5. Enable Transmission complete interrupt as a USART interrupt is generated whenever TC=1 in the USART_SR register
	 * 6. Enable RXNE interrupt as a USART interrupt is generated whenever ORE=1 or RXNE=1 in the USART_SR register
	 * */
	USART1->USART_CR1 |= USART_CR1_TXEIE;
	USART1->USART_CR1 |= USART_CR1_TCIE;
	USART1->USART_CR1 |= USART_CR1_RXNEIE;
}

void UART_Config(uint_32t baudRate,uint_8t stopBits,uint_8t parity,uint_8t dataBits,uint_32t *SysClk){

	uint_32t bR = baudRate;
	uint_32t DIV_mantissa = *SysClk/bR*16;
	float fraction = ((((float)*SysClk)/((float)bR*16))-(float)DIV_mantissa)*16;
	uint_32t DIV_fraction = (uint_32t)fraction;
	USART1->USART_BRR = (DIV_mantissa<<4)|(DIV_fraction);

	/***********************************************************************************************/
	if(stopBits == STOP_ONE){
		USART1->USART_CR2 &= CLEAR_MASK_STOP_BITS;
		USART1->USART_CR2 |= ONE_STOP_BIT;
	}else if(stopBits == STOP_TWO){
		/*USART1->USART_CR2 &= CLEAR_MASK_STOP_BITS;*/
		USART1->USART_CR2 |= TWO_STOP_BIT;
	}
	/***********************************************************************************************/
	USART1->USART_CR1 |= USART_CR1_PCE;
	if(parity == PARITY_EVEN){
		USART1->USART_CR1 &= ~(USART_CR1_PS);
	}else if(parity == PARITY_ODD){
		USART1->USART_CR1 |= (USART_CR1_PS);
	}
	/***********************************************************************************************/
	if(dataBits == WORD_LEN_DATA_8){
		/*
		 * 2. Program the M bit in USART_CR1 to define the word length.
		 * This bit determines the word length. It is set or cleared by software.
		   0: 1 Start bit, 8 Data bits, n Stop bit
		 * */
		USART1->USART_CR1 &= ~(USART_CR1_M);
	}else if(dataBits == WORD_LEN_DATA_9){
		USART1->USART_CR1 |= (USART_CR1_M);
	}

}
/*********************************************************************************************************************/

void UART_sendBuffer(uint_8t *buffer , uint_16t len)
{
	if(buffer && len!=0)
	{
		if(txBuffer.state == IDLE_STATE)
		{
			txBuffer.ptr = buffer;
			txBuffer.size = len;
			txBuffer.state = BUSY_STATE;
			txBuffer.Position = 0;
			USART1->USART_DR = txBuffer.ptr[txBuffer.Position];
			txBuffer.Position++;
			USART1->USART_CR1 |= USART_CR1_TE;
		}
	}
}
/*********************************************************************************************************************/

void UART_receiveBuffer(uint_8t *buffer , uint_16t len){
	if(buffer && len!=0){
		if(rxBuffer.state == IDLE_STATE){
			rxBuffer.ptr = buffer;
			rxBuffer.size = len;
			rxBuffer.Position = 0;
			rxBuffer.state = BUSY_STATE;
			USART1->USART_CR1 |= USART_CR1_RE;
		}
	}

}
/*********************************************************************************************************************/

void USART1_IRQHandler(void){
	if(USART1->USART_SR & USART_SR_TXE){
		if((txBuffer.state == BUSY_STATE) && (txBuffer.Position != txBuffer.size)){
			USART1->USART_DR = txBuffer.ptr[txBuffer.Position];
			txBuffer.Position++;
			USART1->USART_SR &= ~(USART_SR_TXE);
		}else{
			txBuffer.ptr = NULL;
			txBuffer.Position = 0;
			txBuffer.size = 0;
			txBuffer.state = IDLE_STATE;
			appTxNotify();
		}
	}
	if(USART1->USART_SR & USART_SR_RXNE){
		if((rxBuffer.state == BUSY_STATE) && (rxBuffer.Position != rxBuffer.size)){
			rxBuffer.ptr[rxBuffer.Position] = USART1->USART_DR;
			rxBuffer.Position++;
		}else{
			rxBuffer.Position = 0;
			rxBuffer.ptr = NULL;
			rxBuffer.size = 0;
			rxBuffer.state = IDLE_STATE;
			appRxNotify();
		}
	}
}
/*********************************************************************************************************************/

void UART_setTXcbf(txcbf_t txcbf){
	if(txcbf){
		appTxNotify = txcbf;
	}
}
/*********************************************************************************************************************/

void UART_setRXcbf(rxcbf_t rxcbf){
	if(rxcbf){
		appRxNotify = rxcbf;
	}
}
