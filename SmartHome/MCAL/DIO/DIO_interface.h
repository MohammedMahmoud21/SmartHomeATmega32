#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_
#include "StdTypes.h"

/************************************************************************/
/********************* User Defined data types **************************/
/************************************************************************/

typedef enum
{
	OUTPUT,
	INFREE,
	INPULL	
}DIO_PinStatus_type;

typedef enum
{
	LOW=0,
	HIGH
}DIO_PinVolatage_type;

typedef enum
{
	PA,
	PB,
	PC,
	PD	
}DIO_Port_type;

typedef enum
{
	PA0=0,
	PA1,
	PA2,
	PA3,
	PA4,
	PA5,
	PA6,
	PA7,
	PB0,
	PB1,
	PB2,
	PB3,
	PB4,
	PB5,
	PB6,
	PB7,
	PC0,
	PC1,
	PC2,
	PC3,
	PC4,
	PC5,
	PC6,
	PC7,
	PD0,
	PD1,
	PD2,
	PD3,
	PD4,
	PD5,
	PD6,
	PD7,
	TOTALPINS
}DIO_Pin_type;

/************************************************************************/
/********************* Functions declerations ***************************/
/************************************************************************/
extern void DIO_Init(void);
extern void DIO_WritePin(DIO_Pin_type pin,DIO_PinVolatage_type voltage);
extern DIO_PinVolatage_type DIO_ReadPin(DIO_Pin_type pin);
extern void DIO_TogglePin(DIO_Pin_type pin);
extern void DIO_WritePort(DIO_Port_type port, u8 number);
extern u8 DIO_ReadPort(DIO_Port_type port);
#endif /* DIO_INTERFACE_H_ */