#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

#include "STD_TYPES.h"


/*********************************************************************************************************************/

#define USART1				((UART_Reg*)(0x40013800))
#define USART2				((UART_Reg*)(0x40004400))
#define USART3				((UART_Reg*)(0x40004800))
#define USART4				((UART_Reg*)(0x40004C00))
#define USART5				((UART_Reg*)(0x40005000))
/*********************************************************************************************************************/

#define USART_SR_PE			0x00000001
#define USART_SR_FE			0x00000002
#define USART_SR_NE			0x00000004
#define USART_SR_ORE		0x00000008
#define USART_SR_IDLE		0x00000010
#define USART_SR_RXNE		0x00000020
#define USART_SR_TC			0x00000040
#define USART_SR_TXE		0x00000080
#define USART_SR_LBD		0x00000100
#define USART_SR_CTS		0x00000200
/*********************************************************************************************************************/

#define USART_CR1_SBK		0x00000001
#define USART_CR1_RWU		0x00000002
#define USART_CR1_RE		0x00000004
#define USART_CR1_TE		0x00000008
#define USART_CR1_IDLEIE	0x00000010
#define USART_CR1_RXNEIE	0x00000020
#define USART_CR1_TCIE		0x00000040
#define USART_CR1_TXEIE		0x00000080
#define USART_CR1_PEIE		0x00000100
#define USART_CR1_PS		0x00000200
#define USART_CR1_PCE		0x00000400
#define USART_CR1_WAKE		0x00000800
#define USART_CR1_M			0x00001000
#define USART_CR1_UE		0x00002000

/*********************************************************************************************************************/

#define ONE_STOP_BIT 			0x00000000
#define TWO_STOP_BIT 			0x00002000

#define STOP_ONE				0
#define STOP_TWO				2
/*********************************************************************************************************************/

#define CLEAR_MASK_STOP_BITS	0xFFFFCFFF
#define STOP_BITS				STOP_ONE
/*********************************************************************************************************************/

#define BAUDRATE_6900       6900
#define BAUDRATE_115200     115200
/*********************************************************************************************************************/

#define PARITY_EVEN         2
#define PARITY_ODD			1


/**
 * make pointer to fun as a data type
 **/
typedef void (*appTxNotify_t)(void);
typedef void (*appRxNotify_t)(void);
/**
 * define a variable from our typedef:pointer to fun
 */
static appTxNotify_t  appTxNotify;
static appRxNotify_t  appRxNotify;
/*********************************************************************************************************************/

typedef void (*txcbf_t)(void);
typedef void (*rxcbf_t)(void);

/*********************************************************************************************************************/

#define IDLE_STATE  		0
#define BUSY_STATE  		1
/*********************************************************************************************************************/

#define WORD_LEN_DATA_8		1
#define WORD_LEN_DATA_9		2
/*********************************************************************************************************************/

void UART_Init(void);
/*********************************************************************************************************************/

void UART_Config(uint_32t baudRate,uint_8t stopBits,uint_8t parity,uint_8t dataBits,uint_32t *SysClk);
/*********************************************************************************************************************/

void UART_sendBuffer(uint_8t *buffer , uint_16t len);
/*********************************************************************************************************************/

void UART_receiveBuffer(uint_8t *buffer , uint_16t len);
/*********************************************************************************************************************/

void UART_setTXcbf(txcbf_t txcbf);
/*********************************************************************************************************************/

void UART_setRXcbf(rxcbf_t rxcbf);

#endif
