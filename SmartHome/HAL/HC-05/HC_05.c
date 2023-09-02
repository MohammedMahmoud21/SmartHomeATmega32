#include "HC_05_interface.h"


/***************** Global Variables Defination *********************/
/*Tx Queue*/
static char *Queue_Tx_Array[hc_05QUEUE_SIZE];
volatile static u8 In_Tx=0;
volatile static u8 Out_Tx=0;
volatile static u8 Rotate_Tx_Flag=0;
/*Rx Queue*/
static char *Queue_Rx_Array[hc_05QUEUE_SIZE];
volatile static u8 In_Rx=0;
volatile static u8 Out_Rx=0;
volatile static bool_type Rotate_Rx_Flag=FALSE;
volatile static u8 Messages_Counter=0;
/***************** Static APIs Deceleration *********************/

static void BCM_voidTxISR(void);
static void BCM_voidRxISR(void);

/***************** APIs Implementations *********************/

void HC_voidInit(void)
{
	UART_SetCallBack(UART_TX,BCM_voidTxISR);
	UART_SetCallBack(UART_RX,BCM_voidRxISR);
	sei();
	UART_InterruptEnable(UART_TX);
	UART_InterruptEnable(UART_RX);
}

/*Basic Communication Module (BCM) Based on UART*/

Error_t HC_xSendString(char *Copy_charpString)
{
	Error_t Local_xErrorState=OK;
	if(In_Tx >= hc_05QUEUE_SIZE)
	{
		In_Tx=ZERO_INIT;
		Rotate_Tx_Flag=1;
	}
	else
	{
		/*Nothing*/
	}
	if((In_Tx == Out_Tx) && (1 == Rotate_Tx_Flag))
	{
		/*Queue Full*/
		Local_xErrorState = NOK;
	}
	else
	{
		Queue_Tx_Array[In_Tx] = Copy_charpString;
		UART_SendNoBlock(Queue_Tx_Array[In_Tx][ZERO_INIT]);
		In_Tx++;
	}
	
	return (Local_xErrorState);
		
}
Error_t HC_xReceiveString(char *Copy_charpString)
{
	Error_t Local_xErrorState=OK;
	if(In_Rx >= hc_05QUEUE_SIZE)
	{
		/*Queue Full*/
	}
	else
	{
		Queue_Rx_Array[In_Rx] = Copy_charpString;
		In_Rx++;
	}
	return (Local_xErrorState);
}
Error_t HC_xDeQueue(u8 *const Copy_u8pMessagesNumber)
{
	Error_t Local_xErrorState=OK;
	if(NULL_PTR == Copy_u8pMessagesNumber)
	{
		Local_xErrorState = NOK;
	}
	else
	{
		*Copy_u8pMessagesNumber = Messages_Counter;
	}
	return (Local_xErrorState);
}
Error_t HC_xMessageRead(void)
{
	Error_t Local_xErrorState=OK;
	if((ZERO_INIT == Out_Rx) || (ZERO_INIT == Messages_Counter))
	{
		/*Wrong Call for this function*/
		Local_xErrorState = NOK;
	}
	else
	{
		/*Tell Module That all messages have been read and u can start over again*/
		Out_Rx =ZERO_INIT;
		Messages_Counter=ZERO_INIT;	
	}
	return (Local_xErrorState);
	
}

/*Static APIs Implementations*/
static void BCM_voidTxISR(void)
{
	static u16 Local_u16Iterator=1;
	if(Out_Tx >= hc_05QUEUE_SIZE)
	{
		Out_Tx=0;
		Rotate_Tx_Flag=0;
	}
	else
	{
		;
	}
	if((Out_Tx == In_Tx) && (0 == Rotate_Tx_Flag))
	{
		/*Queue Empty*/
	}
	else
	{
		if( '\0' !=Queue_Tx_Array[Out_Tx][Local_u16Iterator])
		{
			UART_SendNoBlock(Queue_Tx_Array[Out_Tx][Local_u16Iterator]);
			Local_u16Iterator++;	
		}
		else
		{
			Local_u16Iterator =1;
			Out_Tx++;
		}
		
	}
}
static void BCM_voidRxISR(void)
{
	static u16 Local_u16Counter=0;
	if((Out_Rx >= hc_05QUEUE_SIZE))
	{
		/*Queue Filled all places*/
	}
	else if(Out_Rx == In_Rx)
	{
		/*Queue Full*/
	}
	else
	{
		Queue_Rx_Array[Out_Rx][Local_u16Counter] = UART_ReceiveNoBlock();
		if(hc_05ENDSTRING != Queue_Rx_Array[Out_Rx][Local_u16Counter])
		{
			Local_u16Counter++;	
		}
		else
		{
			Queue_Rx_Array[Out_Rx][Local_u16Counter] ='\0';
			Local_u16Counter=0;
			Out_Rx++;
			Messages_Counter++; /*To know number of current messages*/
		}
	}
}



