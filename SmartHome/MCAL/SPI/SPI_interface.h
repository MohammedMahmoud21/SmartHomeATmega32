#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_
#include "MemMap.h"
#include "StdTypes.h"
#include "Utiles.h"

#define MASTER			(1)
#define SLAVE			(0)
#define BIG_ENDIAN		(1)
#define LITEL_ENDIAN	(0)

#define SPI_STATE	MASTER
#define DATA_ORDER	LITEL_ENDIAN

extern void SPI_Init(void);
extern u8   SPI_SendReceive_Master(u8 data);
extern void SPI_InterruptEnable(void);
extern void SPI_SetCallBack(void (*p_func)(void));
#if SPI_STATE == SLAVE
extern u8	SPI_ReceivePeriodic(u8 *data);
extern u8	SPI_ReceiveNoBlock(void);
extern void SPI_SendNoBlock(u8 data);
#endif

#endif /* SPI_INTERFACE_H_ */