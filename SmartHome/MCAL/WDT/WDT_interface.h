#ifndef WDT_INTERFACE_H_
#define WDT_INTERFACE_H_
#include "MemMap.h"
#include "StdTypes.h"
#include "Utiles.h"

typedef enum
{
	SET_16ms=0,
	SET_32ms,
	SET_65ms,
	SET_130ms,
	SET_260ms,
	SET_520ms,
	SET_1000ms,
	SET_2100ms
	
}TimeOut_type;

extern void WDT_SetTime(TimeOut_type time);
extern void WDT_Stop(void);


#endif /* WDT_INTERFACE_H_ */