#ifndef ULTRASONIC_INTERFACE_H_
#define ULTRASONIC_INTERFACE_H_
#include "Timers_interface.h"
#include "DIO_interface.h"
#include "Ultrasonic_cnfig.h"
#define F_CPU	(8000000UL)
#include <util/delay.h>



extern u16 Get_Distance(Ultrasonic_Number_type u);



#endif /* ULTRASONIC_INTERFACE_H_ */