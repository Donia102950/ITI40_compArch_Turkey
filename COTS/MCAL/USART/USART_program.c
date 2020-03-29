
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

typedef struct {
	u32 DMA1_CCR;
	u32 DMA1_CNDTR;
	u32 DMA1_CPAR;
	u32 DMA1_CMAR;
}dma1Peri_t;


#define IDLE_STATE  0
#define BUSY_STATE  1


#define DMA1_ISR			(*(volatile u32*)0x40020000)
#define DMA1_IFCR			(*(volatile u32*)0x40020000)
#define DMA1_CHANNEL_FOUR	((volatile dma1Peri_t*)0x40020044)
#define DMA1_CHANNEL_FIVE	((volatile dma1Peri_t*)0x40020058)

#define USART1 				((volatile uartPeri_t*)0x40013800)
#define USART2 				((volatile uartPeri_t*)0x40004400)
#define USART3 				((volatile uartPeri_t*)0x40004800)
#define USART4 				((volatile uartPeri_t*)0x40004C00)
#define USART5 				((volatile uartPeri_t*)0x40005000)


#define UART1_NUMBER_IN_VECTORTABLE 37
#define UART2_NUMBER_IN_VECTORTABLE 38
#define UART3_NUMBER_IN_VECTORTABLE 39
#define UART4_NUMBER_IN_VECTORTABLE 59
#define UART5_NUMBER_IN_VECTORTABLE 60

#define DMA1_CHANNEL4_NUMBER_IN_VECTORTABLE 14
#define DMA1_CHANNEL5_NUMBER_IN_VECTORTABLE	15


#define UART_ENABLE_MASK 		0x00002000
#define WORDLENGTH_MASK_CLEAR   0xFFFFEFFF
#define RARITY_MASK_CLEAR       0xFFFFF9FF
#define STOP_MASK_CLEAR         0xFFFFCFFF


#define TX_ENABLE_CLEAR_MASK    0xFFFFFFF7
#define RX_ENABLE_CLEAR_MASK    0xFFFFFFFB



#define TX_ENABLE_MASK          0x00000008
#define TXE_FLAG_MASK           0x00000080


#define RX_ENABLE_MASK 			0x00000004
#define RXEN_FLAG_MASK 			0x00000020


#define DMA1_TRANSFER_COMPLETE_FLAG_CH4_MASK 			0x00002000
#define DMA1_TRANSFER_COMPLETE_FLAG_CH5_MASK 			0x00080000

#define DMA1_DATA_DIRECTION_MASK_FOR_TX	 				0x00000010
#define DMA1_DATA_DIRECTION_MASK_FOR_RX	 				0x00000000

#define DMA1_TRANSFER_COMPLETE_INTERRUPT_ENABLE_MASK	0x00000002
#define DMA1_ENABLE_MASK								0x00000001


static dataBuffer_t TxBuffer;
static dataBuffer_t RxBuffer;


static void UART_CALBaudRate(u32 baudRate);

u32 mantisa;
u32 fraction;

static cbf_t appTxNotif;
static cbf_t appRxNotif;

static u8 Send_req;
static u8 recieve_req;

extern void uart_init(void)
{
	/*Enable usart*/
	USART1->USART_CR1 |= UART_ENABLE_MASK ;
	/*Enable tx pin*/
	USART1->USART_CR1&=TX_ENABLE_CLEAR_MASK;
	USART1->USART_CR1|=TX_ENABLE_MASK;
	/*Enable RX pin*/
	USART1->USART_CR1&=RX_ENABLE_CLEAR_MASK;
	USART1->USART_CR1|=RX_ENABLE_MASK;

#if (USART_DMA==USART_DMA_DISABLE)

	/*Enable Interrupt for TXE*/
	USART1->USART_CR1|=TXE_FLAG_MASK;
	/*Enable interrupt for RXE*/
	USART1->USART_CR1|=RXEN_FLAG_MASK;
	/*Enable interrupt for UART*/
	NVIC_VoidClrPendingFlag(UART1_NUMBER_IN_VECTORTABLE);
	NVIC_VoidEnableExtInt (UART1_NUMBER_IN_VECTORTABLE);
#elif (USART_DMA==USART_DMA_ENABLE)

	/*Enable Interrupt for DMA1 channel4*/
	NVIC_VoidClrPendingFlag(DMA1_CHANNEL4_NUMBER_IN_VECTORTABLE);
	NVIC_VoidEnableExtInt (DMA1_CHANNEL4_NUMBER_IN_VECTORTABLE);

	/*Enable Interrupt for DMA1 channel5*/
	NVIC_VoidClrPendingFlag(DMA1_CHANNEL5_NUMBER_IN_VECTORTABLE);
	NVIC_VoidEnableExtInt (DMA1_CHANNEL5_NUMBER_IN_VECTORTABLE);

#endif

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
#if (USART_DMA==USART_DMA_DISABLE)

			TxBuffer.ptr=buffer;
			TxBuffer.size=len;
			TxBuffer.state=BUSY_STATE;
			TxBuffer.position=0;
			Send_req=1;

			USART1->USART_DR=TxBuffer.ptr[TxBuffer.position];
			TxBuffer.position++;

#elif (USART_DMA==USART_DMA_ENABLE)

			/*Configure Channel 4 for TX in DMA*/
			/*Clear transfer complete flag for CH4*/
			DMA1_IFCR|=DMA1_TRANSFER_COMPLETE_FLAG_CH4_MASK;

			/*set priority for channel 4*/
			DMA1_CHANNEL_FOUR->DMA1_CCR&=PRIORITY_CLEAR_MASK;
			DMA1_CHANNEL_FOUR->DMA1_CCR|=(CHANNEL4_PRIORITY_FOR_DMA1);

			/*config ptr Size*/
			DMA1_CHANNEL_FOUR->DMA1_CCR&=BITS_CONFG_CLEAR_MASK;
			DMA1_CHANNEL_FOUR->DMA1_CCR|=MEMORY_SIZE;
			DMA1_CHANNEL_FOUR->DMA1_CCR|=PERIPHERAL_SIZE;

			/*Config  increment */
			DMA1_CHANNEL_FOUR->DMA1_CCR|=ENABLE_MEMORY_INCREMENT;
			DMA1_CHANNEL_FOUR->DMA1_CCR|=DISABLE_PERIPHERAL_INCREMENT;

			/*Enable Data Direction from memory to prei*/
			DMA1_CHANNEL_FOUR->DMA1_CCR|=DMA1_DATA_DIRECTION_MASK_FOR_TX;

			/*Enable Transfer complete interrupt*/
			DMA1_CHANNEL_FOUR->DMA1_CCR|=DMA1_TRANSFER_COMPLETE_INTERRUPT_ENABLE_MASK;


			/*config DMA counter*/
			DMA1_CHANNEL_FOUR->DMA1_CNDTR=len;


			/*config Peripheral Addres */
			DMA1_CHANNEL_FOUR->DMA1_CPAR=USART1->USART_DR;


			/*config memory Addres */
			DMA1_CHANNEL_FOUR->DMA1_CMAR=buffer;


			/*Enable DMA*/
			DMA1_CHANNEL_FOUR->DMA1_CCR|=DMA1_ENABLE_MASK;


			/*USART1->USART_DR=0;*/
			TxBuffer.state=BUSY_STATE;
#endif
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
		if(RxBuffer.state==IDLE_STATE)
		{
#if (USART_DMA==USART_DMA_DISABLE)

			RxBuffer.ptr=buffer;
			RxBuffer.size=len;
			RxBuffer.state=BUSY_STATE;
			RxBuffer.position=0;
			recieve_req=1;

#elif (USART_DMA==USART_DMA_ENABLE)


			/*Configure Channel 5 for RX in DMA*/
			/*Clear transfer complete flag for CH5*/
			DMA1_IFCR|=DMA1_TRANSFER_COMPLETE_FLAG_CH5_MASK;

			/*set priority for channel 4*/
			DMA1_CHANNEL_FIVE->DMA1_CCR&=PRIORITY_CLEAR_MASK;
			DMA1_CHANNEL_FIVE->DMA1_CCR|=(CHANNEL5_PRIORITY_FOR_DMA1);

			/*config ptr Size*/
			DMA1_CHANNEL_FIVE->DMA1_CCR&=BITS_CONFG_CLEAR_MASK;
			DMA1_CHANNEL_FIVE->DMA1_CCR|=MEMORY_SIZE;
			DMA1_CHANNEL_FIVE->DMA1_CCR|=PERIPHERAL_SIZE;

			/*Config  increment */
			DMA1_CHANNEL_FIVE->DMA1_CCR|=ENABLE_MEMORY_INCREMENT;
			DMA1_CHANNEL_FIVE->DMA1_CCR|=DISABLE_PERIPHERAL_INCREMENT;

			/*Enable Data Direction from memory to prei*/
			DMA1_CHANNEL_FIVE->DMA1_CCR|=DMA1_DATA_DIRECTION_MASK_FOR_RX;

			/*Enable Transfer complete interrupt*/
			DMA1_CHANNEL_FIVE->DMA1_CCR|=DMA1_TRANSFER_COMPLETE_INTERRUPT_ENABLE_MASK;


			/*config DMA counter*/
			DMA1_CHANNEL_FIVE->DMA1_CNDTR=len;


			/*config Peripheral Addres */
			DMA1_CHANNEL_FIVE->DMA1_CPAR=USART1->USART_DR;


			/*config memory Addres */
			DMA1_CHANNEL_FIVE->DMA1_CMAR=buffer;


			/*Enable DMA*/
			DMA1_CHANNEL_FIVE->DMA1_CCR|=DMA1_ENABLE_MASK;


			/*USART1->USART_DR=0;*/
			RxBuffer.state=BUSY_STATE;



#endif
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
	if ((USART1->USART_SR & TXE_FLAG_MASK )&& Send_req)
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
			Send_req=0;
			TxBuffer.state=IDLE_STATE;
			appTxNotif();
		}
	}

	if ((USART1->USART_SR & RXEN_FLAG_MASK)&& recieve_req)
	{

		if ((RxBuffer.size != RxBuffer.position) && (RxBuffer.state == BUSY_STATE))
		{
			RxBuffer.ptr [RxBuffer.position]=USART1->USART_DR ;
			RxBuffer.position++;
			if(RxBuffer.size == RxBuffer.position)
				//recieve done
			{RxBuffer.ptr=NULL;
			RxBuffer.position=0;
			RxBuffer.size=0;
			recieve_req=0;

			RxBuffer.state=IDLE_STATE;
			appRxNotif();
			}
		}
	}

}

void DMA1_Channel4_IRQHandler(void)
{
	if(DMA1_ISR & DMA1_TRANSFER_COMPLETE_FLAG_CH4_MASK)
	{
		TxBuffer.state=IDLE_STATE;
		appTxNotif();
	}
}
void DMA1_Channel5_IRQHandler(void)
{
	if(DMA1_ISR & DMA1_TRANSFER_COMPLETE_FLAG_CH5_MASK)
	{
		RxBuffer.state=IDLE_STATE;
		appRxNotif();
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


