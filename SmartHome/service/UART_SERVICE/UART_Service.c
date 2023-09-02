#include "UART_Service_interface.h"
#include "LCD_interface.h"

/****************************Global Variables**********************************/
/*TX variables*/
static u8 *TX_Arr[QUEUE_SIZE]={0};
static u8 TX_Out=0;
static u8 TX_IN=0;
static u8 Rotate_Flag=0; 
/*Rx variables*/
static u8 *RX_Arr[QUEUE_SIZE]={0};
static u8 RX_Out=0;
static u8 RX_IN=0;
static u8 RX_Rotate_Flag=0;
static u8 RX_Counter=0;
/********************* static Functions prototype *************************/
static void TX_Func(void);
static void RX_Func(void);
/********************* Functions Implementations *************************/

void UART_Service_SendString(u8 *str)
{
	u8 index=0;
	while('\0' != str[index])
	{
		UART_Send(str[index]);
		index++;
	}
}
void UART_Service_ReceiveString(u8 *str,const u8 size)
{
	u16 index=0;
	str[index] = UART_Receive();
	if(10 == str[index])
	{
		str[index]=UART_Receive();
	}
	else{;}
	for(;(str[index]!=ENTER) && (index < size-1);)
	{
		index++;
		str[index]=UART_Receive();
	}
	str[index]=0;
}

void UART_Service_SendNumber(u32 number)
{
	u8 iterator=0;
	for(;(iterator<4) && (0 < number);iterator++)
	{
		UART_Send((u8)(number&PORT_MASK));
		number >>=8;
	}
}

u32 UART_Service_ReceiveNumber(void)
{
	u32 number=0;
	u8 *data=&number;
	
	data[0]=(UART_Receive());
	data[1]=(UART_Receive());
	data[2]=(UART_Receive());
	data[3]=(UART_Receive());
	
	return (number);	
}

void UART_Service_Send_String_CheckSum(u8 *str)
{
	u8 length=0;
	u16 index=0;
	u16 sum=0;
	while(str[length])
	{
		length++;
	}	
	//First send length.
	UART_Send(length);
	//send data and calc sum.
	for(;index<length;index++)
	{
		UART_Send(str[index]);
		sum += str[index];
	}
	//send sum.
	UART_Send((u8)sum);
	UART_Send((u8)(sum>>8));
}

u8	UART_Service_Receive_String_CheckSum(u8 *str)
{
	u8 Ret_Val=0; //0 => bad data.
	u8 length=0;
	u16 index=0;
	u16 Calc_Sum=0;
	u16 Received_Sum=0;
	u8 Byte_One=0;
	u8 Byte_Two=0;
	length = UART_Receive();
	//receive data and calc sum.
	for(;index < length;index++)
	{
		str[index]=UART_Receive();
		Calc_Sum += str[index];
	}
	str[index]=0;
	/*******************************************/

	//receive sum.
	Byte_One = UART_Receive();
	Byte_Two = UART_Receive();
	Received_Sum = (u32)Byte_One | ((u32)Byte_Two<<8);
	if(Received_Sum == Calc_Sum)
	{
		Ret_Val=1;
	}
	else
	{
		Ret_Val=0;
	}
	
	return (Ret_Val);
}

/******************** Basic Communication APIs ******************************/


void UART_Service_BCM_Tx_Init(void)
{
	sei();
	UART_Init();
	UART_SetCallBack(UART_TX,TX_Func);
	UART_InterruptEnable(UART_TX);
}
void UART_Service_BCM_Rx_Init(void)
{
	sei();
	UART_Init();
	UART_SetCallBack(UART_RX,RX_Func);
	UART_InterruptEnable(UART_RX);
}
void UART_Service_BCM_SendStringAsynch(u8 *str)
{
	if(TX_IN >= QUEUE_SIZE)
	{
		TX_IN =0;
		Rotate_Flag=1;
	}
	else if ((TX_IN == TX_Out) && (1 == Rotate_Flag))
	{
		;
	}
	else
	{
		UART_SendNoBlock(str[0]);
		TX_Arr[TX_IN]=str;
		TX_IN++;
	}
}
void UART_Service_BCM_ReceiveStringAsynch(u8 *str)
{
	RX_Arr[RX_IN] = str;
	RX_IN++;
}
u8	UART_Service_BCM_DataArrived(void)
{
	u8 ret_val=RX_Counter;
	if(RX_Counter > 0)
	{
		RX_Counter--;	
	}
	else
	{
		;
	}
	return ret_val;
}
static void RX_Func(void)
{
	static u8 iterator=0;
	RX_Arr[RX_Out][iterator]=UART_ReceiveNoBlock();
	if(13 != RX_Arr[RX_Out][iterator])
	{
		iterator++;
		
	}
	else
	{
		RX_Arr[RX_Out][iterator]=0;
		RX_Out++;
		iterator=0;
		RX_Counter++;
	}
	
}

static void TX_Func(void)
{
	static u16 index=1;
	if(TX_Out >= QUEUE_SIZE)
	{
		TX_Out=0;
		Rotate_Flag=0;
	}
	else
	{
		if((TX_Out==TX_IN) &&(0==Rotate_Flag))
		{
			TX_IN=0;
			TX_Out=0;
		}
		else
		{
			if('\0' != TX_Arr[TX_Out][index])
			{
				UART_SendNoBlock(TX_Arr[TX_Out][index]);
				index++;
			}
			else
			{
				index=1;
				TX_Out++;
				if(TX_Out<TX_IN)
				{
					UART_SendNoBlock(TX_Arr[TX_Out][0]);	
				}
				else{;}
				
				
			}	
		}
		
	}
	
	
}
