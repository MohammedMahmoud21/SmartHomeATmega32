#ifndef SMARTHOME_INTERFACE_H_
#define SMARTHOME_INTERFACE_H_
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "EEPROM_interface.h"
#include "ADC_Interface.h"
#include "UART_interface.h"
#include "EEPROM_Service_interface.h"
#include "HC_05_interface.h"
#include "Servo.h"
#include "RGB.h"
#include "Motor_Interface.h"
#include "Sensors_interface.h"
#include "Strings.h"
#define F_CPU	(8000000UL)
#include <util/delay.h>


#define smarthomeMESSAGES_SIZE		(5)
#define smarthomeMESSAGES_LENGTH	(20)
#define smarthomeREPLAY_SIZE		(8)
#define smarthomeREPLAY_LENGTH		(20)
#define  smarthomeOperationsCount	(8)	
#define smarthomePASSWORD_LENGTH	(20)


typedef enum
{
	CHANGE=0,
	LEDON_OPERATION,
	LEDOFF_OPERATION,
	Door_OPERATION,
	RGB_OPERATION,
	FANON_OPERATION,
	FANOFF_OPERATION,
	LIGHTING_OPERATION,
	CLOSED,
	OPENED,
	IDLE,
	WRONG_OPERATION
}System_States_type;


extern void SmartHome_voidInit(void);
extern void SmartHome_voidStart(void);



#endif /* SMARTHOME_INTERFACE_H_ */