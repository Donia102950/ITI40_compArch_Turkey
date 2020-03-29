/*
 * USART_config.h
 *
 *  Created on: Mar 27, 2020
 *      Author: User
 */

#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_




/*DATABITS CONFIGURE*/
#define DATA_8_BITS  0x00000000
#define DATA_9_BITS  0x00001000

#define DATA_BITS  DATA_8_BITS


/*Buad rate cinfig*/
#define UART_BUADRATE_9600 		9600
#define UART_BUADRATE_115200 	115200

#define BUAD_RATE 	UART_BUADRATE_9600

/*Parity bit config*/
#define NOPARITY		0x00000000
#define PAIRTY_EVEN		0x00000400
#define PARITY_ODD		0x00000600
#define PARITY			NOPARITY
/*Stop bits config*/

#define ONE_STOP_BIT	0x00000000
#define TWO_STOP_BIT	0x00020000

#define STOP_BITS_NUMBER ONE_STOP_BIT





#endif /* USART_CONFIG_H_ */
