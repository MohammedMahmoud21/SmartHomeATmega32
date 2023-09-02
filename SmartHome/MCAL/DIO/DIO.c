#include "StdTypes.h"
#include "MemMap.h"
#include "Utiles.h"
#include "DIO_interface.h"
#include "DIO_private.h"

void DIO_Init(void)
{
	DIO_Pin_type Pin=0;
	for(;Pin < TOTALPINS;Pin++)
	{
		DIO_InitPin(Pin,Pin_Status_Array[Pin]);
	}
}

static void DIO_InitPin(DIO_Pin_type pin,DIO_PinStatus_type status)
{
	u8 Pin  = ((pin)%((u8)8));
	DIO_Port_type Port = ((pin) /((u8)8));
	switch (status)
	{
		case OUTPUT:
		switch(Port)
		{
			case PA:
			SET_BIT(DDRA,Pin);
			CLR_BIT(PORTA,Pin);
			break;
			case PB:
			SET_BIT(DDRB,Pin);
			CLR_BIT(PORTB,Pin);
			break;
			case PC:
			SET_BIT(DDRC,Pin);
			CLR_BIT(PORTC,Pin);
			break;
			case PD:
			SET_BIT(DDRD,Pin);
			CLR_BIT(PORTD,Pin);
			break;
		}
		break;
		case INFREE:
		switch(Port)
		{
			case PA:
			CLR_BIT(DDRA,Pin);
			CLR_BIT(PORTA,Pin);
			break;
			case PB:
			CLR_BIT(DDRB,Pin);
			CLR_BIT(PORTB,Pin);
			break;
			case PC:
			CLR_BIT(DDRC,Pin);
			CLR_BIT(PORTC,Pin);
			break;
			case PD:
			CLR_BIT(DDRD,Pin);
			CLR_BIT(PORTD,Pin);
			break;
		}
		break;
		case INPULL:
		switch(Port)
		{
			case PA:
			CLR_BIT(DDRA,Pin);
			SET_BIT(PORTA,Pin);
			break;
			case PB:
			CLR_BIT(DDRB,Pin);
			SET_BIT(PORTB,Pin);
			break;
			case PC:
			CLR_BIT(DDRC,Pin);
			SET_BIT(PORTC,Pin);
			break;
			case PD:
			CLR_BIT(DDRD,Pin);
			SET_BIT(PORTD,Pin);
			break;
		}
		break;
	}
}

void DIO_WritePin(DIO_Pin_type pin,DIO_PinVolatage_type voltage)
{
	DIO_Port_type port= ((pin)/((u8)8));
	pin = (pin%8);
	if(LOW == voltage)
	{
		switch (port)
		{
			case PA:
			CLR_BIT(PORTA,pin);
			break;
			case PB:
			CLR_BIT(PORTB,pin);
			break;
			case PC:
			CLR_BIT(PORTC,pin);
			break;
			case PD:
			CLR_BIT(PORTD,pin);
			break;
		}
	}
	else if(HIGH == voltage)
	{
		switch (port)
		{
			case PA:
			SET_BIT(PORTA,pin);
			break;
			case PB:
			SET_BIT(PORTB,pin);
			break;
			case PC:
			SET_BIT(PORTC,pin);
			break;
			case PD:
			SET_BIT(PORTD,pin);
			break;
		}
	}
	else
	{
		;
	}
}

DIO_PinVolatage_type DIO_ReadPin(DIO_Pin_type pin)
{
	DIO_PinVolatage_type volt=LOW;
	DIO_Port_type port = (pin / ((u8)8));
	pin = (pin)%((u8)8);
	switch (port)
	{
		case PA:
		volt = READ_BIT(PINA,pin);
		break;
		case PB:
		volt = READ_BIT(PINB,pin);
		break;
		case PC:
		volt = READ_BIT(PINC,pin);
		break;
		case PD:
		volt = READ_BIT(PIND,pin);
		break;
	}
	
	return (volt);
}

void DIO_TogglePin(DIO_Pin_type pin)
{
	DIO_Port_type port = ((pin)/(u8)8);
	pin = ((pin)%(u8)8);
	switch (port)
	{
		case PA:
		TOGGLE_BIT(PORTA,pin);
		break;
		case PB:
		TOGGLE_BIT(PORTB,pin);
		break;
		case PC:
		TOGGLE_BIT(PORTC,pin);
		break;
		case PD:
		TOGGLE_BIT(PORTD,pin);
		break;
	}
}

void DIO_WritePort(DIO_Port_type port, u8 number)
{
	switch (port)
	{
		case PA:
		PORTA = number;
		break;
		case PB:
		PORTB = number;
		break;
		case PC:
		PORTC = number;
		break;
		case PD:
		PORTD = number;
		break;
	}
}

u8 DIO_ReadPort(DIO_Port_type port)
{
	u8 volt = 0;
	switch (port)
	{
		case PA:
		volt = (PINA & PORT_MASK);
		break;
		case PB:
		volt = (PINB & PORT_MASK);
		break;
		case PC:
		volt = (PINC & PORT_MASK);
		break;
		case PD:
		volt = (PIND & PORT_MASK);
		break;
	}
	return (volt);
}