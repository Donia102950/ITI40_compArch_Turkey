
#include "USART_interface.h"
#include "USART_config.h"
#include "NVIC_interface.h"
#include "STD_Types.h"
#include "RCC.h"
#define OK 0
#define NOK 1
#define NULL (void *) 0
typedef struct {
	u32 USART_SR;
	u32 USART_DR;
	u32 USART_BRR;
	u32 USART_CR1;
	u32 USART_CR2;
	u32 USART_CR3;
	u32 USART_GTPR;
}uartPeri_t;
typedef struct {
	u8* ptr;
	u32 position;
	u32 size;
	u32 state;
}dataBuffer_t;


#define IDLE_STATE  0
#define BUSY_STATE  1

#define USART1 ((volatile uartPeri_t*)0x40013800)
#define USART2 ((volatile uartPeri_t*)0x40004400)
#define USART3 ((volatile uartPeri_t*)0x40004800)
#define USART4 ((volatile uartPeri_t*)0x40004C00)
#define USART5 ((volatile uartPeri_t*)0x40005000)


#define UART1_NUMBER_IN_VECTORTABLE 37
#define UART2_NUMBER_IN_VECTORTABLE 38
#define UART3_NUMBER_IN_VECTORTABLE 39
#define UART4_NUMBER_IN_VECTORTABLE 59
#define UART5_NUMBER_IN_VECTORTABLE 60

#define UART_ENABLE_MASK 0x00002000
#define WORDLENGTH_MASK_CLEAR   0xFFFFEFFF
#define RARITY_MASK_CLEAR       0xFFFFF9FF
#define STOP_MASK_CLEAR         0xFFFFCFFF


#define TX_ENABLE_CLEAR_MASK    0xFFFFFFF7
#define RX_ENABLE_CLEAR_MASK    0xFFFFFFFB



#define TX_ENABLE_MASK          0x00000008
#define TXE_FLAG_MASK           0x00000080


#define RX_ENABLE_MASK 			0x00000004
#define RXEN_FLAG_MASK 			0x00000020





static dataBuffer_t TxBuffer;
static dataBuffer_t RxBuffer;

static u8 Send_req;
static u8 recieve_req;

static void UART_CALBaudRate(u32 baudRate);

u32 mantisa;
u32 fraction;

static cbf_t appTxNotif;
static cbf_t appRxNotif;


extern void uart_init(void)
{
	/*Enable usart*/
	USART1->USART_CR1 |= UART_ENABLE_MASK ;

	USART1->USART_CR1&=TX_ENABLE_CLEAR_MASK;
	USART1->USART_CR1|=TX_ENABLE_MASK;

	USART1->USART_CR1|=TXE_FLAG_MASK;

	USART1->USART_CR1&=RX_ENABLE_CLEAR_MASK;
	USART1->USART_CR1|=RX_ENABLE_MASK;

	USART1->USART_CR1|=RXEN_FLAG_MASK;

	NVIC_VoidClrPendingFlag(UART1_NUMBER_IN_VECTORTABLE);
	NVIC_VoidEnableExtInt (UART1_NUMBER_IN_VECTORTABLE);
}
extern void uart_configure(u32 baudrate, u8 stopBits, u8 parity)
{
	/*confg  buadrate*/
	UART_CALBaudRate(baudrate);
	USART1->USART_BRR=(mantisa <<4)|(fraction);

	USART1->USART_CR1&=WORDLENGTH_MASK_CLEAR;
	USART1->USART_CR1|=DATA_8_BITS;

	USART1->USART_CR1&=RARITY_MASK_CLEAR;
	USART1->USART_CR1|=parity;

	USART1->USART_CR2&=STOP_MASK_CLEAR;
	USART1->USART_CR2|=stopBits;

}
extern u8 uart_send(u8 * buffer, u16 len)
{
	if(buffer && len!=0)
	{
		if(TxBuffer.state==IDLE_STATE)
		{
			TxBuffer.ptr=buffer;
			TxBuffer.size=len;
			TxBuffer.position=0;
			Send_req=1;
			USART1->USART_DR=TxBuffer.ptr[TxBuffer.position];
			
			TxBuffer.position++;
			TxBuffer.state=BUSY_STATE;


		}
		else
		{
			return NOK;
		}
	}
	else
	{
		return NOK;
	}
	return OK;
}
extern u8 uart_Receive(u8 * buffer, u16 len)
{
	if(buffer && len!=0)
	{
		if(TxBuffer.state==IDLE_STATE)
		{
			RxBuffer.ptr=buffer;
			RxBuffer.size=len;
			RxBuffer.position=0;
			recieve_req=1;
			RxBuffer.state=BUSY_STATE;

		}
		else
		{
			return NOK;
		}
	}
	else
	{
		return NOK;
	}
	return OK;
}

extern void uart_setTxCbf(cbf_t txcbf_app)
{
	if(txcbf_app)
	{
		appTxNotif=txcbf_app;
	}
}
extern void uart_setRxCbf(cbf_t rxcbf_app)
{
	if(rxcbf_app)
	{
		appRxNotif=rxcbf_app;
	}
}

void USART1_IRQHandler (void)
{
	if (USART1->USART_SR & TXE_FLAG_MASK && Send_req)
	{
		if (TxBuffer.size!=TxBuffer.position)
		{
			USART1->USART_DR = TxBuffer.ptr [TxBuffer.position];
			TxBuffer.position++;
		}

		else
		{//transmission done
			TxBuffer.ptr=NULL;
			TxBuffer.position=0;
			TxBuffer.size=0;
			appTxNotif();
			Send_req=0;
			TxBuffer.state=IDLE_STATE;
		}
	}

	if (USART1->USART_SR & RXEN_FLAG_MASK && recieve_req)
	{

		if ((RxBuffer.size != RxBuffer.position) && (RxBuffer.state == BUSY_STATE))
		{
			RxBuffer.ptr [TxBuffer.position]=USART1->USART_DR ;
			RxBuffer.position++;
			if(RxBuffer.size == RxBuffer.position)
				//recieve done
			{RxBuffer.ptr=NULL;
			RxBuffer.position=0;
			RxBuffer.size=0;
			appRxNotif();
			recieve_req=0;
			RxBuffer.state=IDLE_STATE;
			}
		}
	}

}
static void UART_CALBaudRate(u32 baudRate)
{

	u32 clk;
	float number;

	RCC_GetBusClock(APB2_BUS,&clk);

	mantisa=((clk)/(baudRate*16));
	number=((((float)clk)/((float)baudRate*16))-(float)mantisa)*16;
	fraction =(int)number;
	if(fraction > 15)
	{
		fraction=0;
		mantisa++;
	}

}


