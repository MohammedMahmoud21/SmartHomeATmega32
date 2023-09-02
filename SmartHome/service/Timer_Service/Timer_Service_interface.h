#ifndef TIMER_SERVICE_INTERFACE_H_
#define TIMER_SERVICE_INTERFACE_H_

#include "Timers_interface.h"


extern void Timer_Service_voidSetInterruptTime_ms(u16 Copy_u16Time,void (*p_func)(void));

#endif /* TIMER_SERVICE_INTERFACE_H_ */