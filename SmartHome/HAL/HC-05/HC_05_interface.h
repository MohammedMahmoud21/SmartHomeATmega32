#ifndef HC_05_INTERFACE_H_
#define HC_05_INTERFACE_H_
#include "UART_interface.h"
#include "StdTypes.h"

#define hc_05QUEUE_SIZE	(5)
#define hc_05ENDSTRING	(13)


extern void HC_voidInit(void);
extern Error_t HC_xSendString(char *Copy_charpString);
extern Error_t HC_xReceiveString(char *Copy_charpString);
extern Error_t HC_xDeQueue(u8 *const Copy_u8pMessagesNumber);
extern Error_t HC_xMessageRead(void);
#endif /* HC_05_INTERFACE_H_ */