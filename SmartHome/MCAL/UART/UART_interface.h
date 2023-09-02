#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_
#include "MemMap.h"
#include "Utiles.h"
#include "StdTypes.h"

typedef enum
{
	UART_TX,
	UART_RX
}UART_Interrupt_type;

#define BAUD_9600	0
#define BAUD_38400	1
#define BAUD_RATE	BAUD_9600

extern void UART_Init(void);
extern void UART_Send(u8 data);
extern u8   UART_Receive(void);
extern void UART_SendNoBlock(u8 data);
extern u8   UART_ReceiveNoBlock(void);
extern void UART_InterruptEnable(UART_Interrupt_type interrupt);
extern void UART_InterruptDisable(UART_Interrupt_type interrupt);
extern void UART_SetCallBack(UART_Interrupt_type interrupt,void (*p_f)(void));
#endif /* UART_INTERFACE_H_ */