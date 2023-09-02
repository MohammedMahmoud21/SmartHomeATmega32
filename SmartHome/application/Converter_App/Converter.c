#define F_CPU	(8000000UL)
#include <util/delay.h>
#include "Converter_interface.h"
#include "Converter_private.h"




void Converter_Init(void)
{
	DIO_Init();
	LCD_Init();
	LCD_GoTo_WriteString(0,0,"Hello To Numbers");
	LCD_GoTo_WriteString(1,0,"   Converter   ");
	_delay_ms(1000);
	LCD_Clear();
	_delay_ms(2);
	LCD_GoTo_WriteString(0,0,"    Made By   ");
	LCD_GoTo_WriteString(1,0,"Mohamed Elsayaad");
	_delay_ms(3000);
	LCD_Clear();
}
Number_Format_type Converter_UserOption(Number_Format_type option)
{
	Number_Format_type option2=DECIMAL;
	u8 key=NO_KEY;
	u8 flag=0;
	
	while(NO_KEY == key)
	{
		if(0 == flag)
		{
			LCD_Clear();
			if((HEX == option) || (DECIMAL == option) || (BIN == option))
			{
				
				LCD_GoTo_WriteString(0,0,"Convert ");
				LCD_WriteChar(option);
				LCD_WriteString(" to:");
				LCD_GoTo_WriteString(1,0,"1-D 2-H 3-B");
			}
			else if (START == option)
			{
				LCD_WriteString("Convert From:");
				LCD_GoTo_WriteString(1,0,"1-D 2-H 3-B");
			}
			else
			{
				;
			}
			
			flag=1;
		}
		else{;}
		key = KeyPad_GetKey();
		if('1' == key)
		{
			option2 = DECIMAL;
		}
		else if('2' == key)
		{
			option2 = HEX;
		}
		else if('3' == key)
		{
			option2 = BIN;
		}
		else
		{
			if(NO_KEY == key)
			{
				;
			}
			else
			{
				key = NO_KEY;
				flag =0;
				LCD_Clear();
				LCD_GoTo_WriteString(0,0,"Invalid");
				_delay_ms(1000);
			}
			
		}
	}
	LCD_Clear();
	return (option2);
}
s32 Converter_Take_User_DecimalNumber(bool_type *const exit)
{
	s32 number=0;
	u32 key = NO_KEY;
	u8 flag=0;
	*exit = FASLE;
	while('=' != key)
	{
		key = KeyPad_GetKey();
		if(('0' <= key) && ('9' >= key))
		{
			if(0 == flag)
			{
				LCD_GoTo_Clear(0,2,10);
				flag=1;	
				LCD_GoTo(0,2);
			}
			else{;}
			LCD_WriteChar(key);
			number = (number*10) + (key-'0');
		}
		else
		{
			if('c' == key)
			{
				*exit = TRUE;
				key = '=';
			}
		}
	}
	return (number);	
}
s32 Converter_Take_User_BinaryNumber(bool_type *const exit)
{
	s32 number=0;
	u32 counter=0;
	u32 key=NO_KEY;
	u8 flag=0;
	*exit = FASLE;
	while ('=' != key)
	{
		key = KeyPad_GetKey();
		if('0' == key)
		{
			
			if(0 == flag)
			{
				LCD_GoTo_Clear(0,2,15);
				flag=1;
				LCD_GoTo(0,15);
			}
			else{;}
			LCD_GoTo_WriteChar(0,15-counter,key);
			counter++;
			
		}
		else if('1' == key)
		{
			if(0 == flag)
			{
				LCD_GoTo_Clear(0,2,15);
				flag=1;
				LCD_GoTo(0,15);
			}
			else{;}
			LCD_GoTo_WriteChar(0,15-counter,key);
			number |= (1<<counter);
			counter++;
			
		}
		else
		{
			if('c' == key)
			{
				*exit = TRUE;
				key = '=';
			}
		}
	}
	
	return (number);	
}
s32 Converter_Take_User_HEXNumber(bool_type *const exit)
{
	s32 number=0;
	u32 key = NO_KEY;
	u8 counter=0;
	u8 hex_count=0;
	u8 flag=0;
	*exit = FASLE;
	while('=' != key)
	{
		key = KeyPad_GetKey();
		if(('0' <= key) && ('9' >= key))
		{
			if(0 == flag)
			{
				LCD_GoTo_Clear(0,2,15);
				flag=1;
				LCD_GoTo(0,15);
			}
			else{;}
			LCD_GoTo_WriteChar(0,15-counter,key);
			number |= ((key-'0')<<hex_count);
			hex_count+=4;
			counter++;
		}
		else if(('A'<= key) && ('F' >= key))
		{
			if(0 == flag)
			{
				LCD_GoTo_Clear(0,2,15);
				flag=1;
				LCD_GoTo(0,15);
			}
			else{;}
			LCD_GoTo_WriteChar(0,15-counter,key);
			number |= ((((key-'A')+10))<<hex_count);
			hex_count +=4;
			counter++;
		}
		else
		{
			if('c' == key)
			{
				*exit = TRUE;
				key = '=';
			}
		}
		
	}
	return (number);	
}