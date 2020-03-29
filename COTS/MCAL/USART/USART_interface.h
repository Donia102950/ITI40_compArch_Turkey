
#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_
#include "STD_Types.h"

typedef void (*cbf_t) (void);


extern void uart_init(void);

extern u8 uart_send(u8 * buffer, u16 len);
extern u8 uart_Receive(u8 * buffer, u16 len);

extern void uart_configure(u32 baudrate, u8 stopBits, u8 parity);

extern void uart_setTxCbf(cbf_t txcbf);

extern void uart_setRxCbf(cbf_t rxcbf);


#endif
