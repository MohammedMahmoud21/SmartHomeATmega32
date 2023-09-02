#include "UART_interface.h"



static void (*UART_P_TX)(void)=NULL_PTR;
static void (*UART_P_RX)(void)=NULL_PTR;

//51 for 9600 , 12 for 38400
static const u16 Baud_Array[2] = {51,12};

void UART_Init(void)
{
	// transmission speed
	CLR_BIT(UCSRA,U2X);

	//B- Bit data
	SET_BIT(UCSRC,UCSZ0);
	SET_BIT(UCSRC,UCSZ1);
	CLR_BIT(UCSRB,UCSZ2);

	//Async
	CLR_BIT(UCSRC,UMSEL);
	//NO parity
	CLR_BIT(UCSRC,UPM0);
	CLR_BIT(UCSRC,UPM1);
	// One stop bit
	CLR_BIT(UCSRC,USBS);
	//baud rate.
	UBRRH = (u8)(Baud_Array[BAUD_RATE]>>8);
	UBRRL = (u8)(Baud_Array[BAUD_RATE]);
	
	//enable UART  receiver.
	SET_BIT(UCSRB,RXEN);

	//enable UART  transmitter .
	SET_BIT(UCSRB,TXEN);
}

void UART_Send(u8 data)
{
	while(0 == READ_BIT(UCSRA,UDRE));
	UDR = data;
}
u8   UART_Receive(void)
{
	u8 data=0;
	while(0 == READ_BIT(UCSRA,RXC));//busy wait.
	data = UDR;
	return (data);	
}


/*************************** No Block & ISR****************************/
void UART_SendNoBlock(u8 data)
{
	UDR = data;	
}
u8   UART_ReceiveNoBlock(void)
{
	return UDR;
}

void UART_InterruptEnable(UART_Interrupt_type interrupt)
{
	if(UART_TX == interrupt)
	{
		SET_BIT(UCSRB,TXCIE);
	}	
	else if(UART_RX == interrupt)
	{
		SET_BIT(UCSRB,RXCIE);
	}
	else
	{
		;
	}
}
void UART_InterruptDisable(UART_Interrupt_type interrupt)
{
	if(UART_TX == interrupt)
	{
		CLR_BIT(UCSRB,TXCIE);
	}
	else if(UART_RX == interrupt)
	{
		CLR_BIT(UCSRB,RXCIE);
	}
	else
	{
		;
	}
}
void UART_SetCallBack(UART_Interrupt_type interrupt,void (*p_f)(void))
{
	if(UART_TX == interrupt)
	{
		UART_P_TX = p_f;
	}
	else if(UART_RX == interrupt)
	{
		UART_P_RX = p_f;
	}
	else
	{
		;
	}
}

ISR(USART_TXC_VECT)
{
	if(NULL_PTR != UART_P_TX)
	{
		UART_P_TX();
	}
	else{;}
}

ISR(USART_RXC_VECT)
{
	if(NULL_PTR != UART_P_RX)
	{
		UART_P_RX();
	}
	else{;}
}