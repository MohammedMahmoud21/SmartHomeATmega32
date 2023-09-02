#ifndef UART_SERVICE_INTERFACE_H_
#define UART_SERVICE_INTERFACE_H_
#include "UART_interface.h"

#define ENTER		(13)
#define QUEUE_SIZE	(20)



extern void UART_Service_SendString(u8 *str);
extern void UART_Service_ReceiveString(u8 *str,const u8 size);
extern void UART_Service_SendNumber(u32 number);
extern u32  UART_Service_ReceiveNumber(void);
extern void UART_Service_Send_String_CheckSum(u8 *str);
extern u8	UART_Service_Receive_String_CheckSum(u8 *str);
/******************** Basic Communication APIs ******************************/
extern void UART_Service_BCM_Tx_Init(void);
extern void UART_Service_BCM_Rx_Init(void);
extern void UART_Service_BCM_SendStringAsynch(u8 *str);
extern void UART_Service_BCM_ReceiveStringAsynch(u8 *str);
extern u8	UART_Service_BCM_DataArrived(void);
#endif /* UART_SERVICE_INTERFACE_H_ */