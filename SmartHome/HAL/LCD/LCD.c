#define F_CPU	(8000000UL)
#include <util/delay.h>
#include "LCD_interface.h"
#include "LCD_cnfg.h"
#include "LCD_private.h"

/************************ LCD static Functions implementations ******************************/

/************* 8 Bit Mode *****************/

#if (LCD_MODE) == (_8_BIT_MODE)

static void LCD_SendCommand(u8 command)
{
	
	DIO_WritePin(RS,LOW);
	DIO_WritePort(LCD_PORT,command);
	DIO_WritePin(E,HIGH);
	_delay_ms(2);
	DIO_WritePin(E,LOW);
	_delay_ms(2);
}

static void LCD_SendData(u8 data)
{
	DIO_WritePin(RS,1);
	DIO_WritePort(LCD_PORT,data);
	DIO_WritePin(E,HIGH);
	_delay_ms(2);
	DIO_WritePin(E,LOW);
	_delay_ms(2);
}

void LCD_Init(void)
{
	_delay_ms(50);
	LCD_SendCommand(FUNCTION_SET);
	LCD_SendCommand(DISP_ON_OFF);
	LCD_SendCommand(DISP_CLEAR);
	_delay_ms(1);
	LCD_SendCommand(ENTRY_MODE);
}

/************* 4 Bit Mode *****************/

#elif (LCD_MODE) == (_4_BIT_MODE)

static void LCD_SendCommand(u8 command)
{
	
	//send most significant nibble.
	DIO_WritePin(RS,LOW);
	DIO_WritePin(D7,READ_BIT(command,7));
	DIO_WritePin(D6,READ_BIT(command,6));
	DIO_WritePin(D5,READ_BIT(command,5));
	DIO_WritePin(D4,READ_BIT(command,4));
	DIO_WritePin(E,HIGH);
	_delay_ms(2);
	DIO_WritePin(E,LOW);
	_delay_ms(2);
	//send least significant nibble.
	DIO_WritePin(D7,READ_BIT(command,3));
	DIO_WritePin(D6,READ_BIT(command,2));
	DIO_WritePin(D5,READ_BIT(command,1));
	DIO_WritePin(D4,READ_BIT(command,0));
	DIO_WritePin(E,HIGH);
	_delay_ms(2);
	DIO_WritePin(E,LOW);
	_delay_ms(2);
}

static void LCD_SendData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	//send most significant nibble.
	DIO_WritePin(D7,READ_BIT(data,7));
	DIO_WritePin(D6,READ_BIT(data,6));
	DIO_WritePin(D5,READ_BIT(data,5));
	DIO_WritePin(D4,READ_BIT(data,4));
	DIO_WritePin(E,HIGH);
	_delay_ms(2);
	DIO_WritePin(E,LOW);
	_delay_ms(2);
	//send least significant nibble.
	DIO_WritePin(D7,READ_BIT(data,3));
	DIO_WritePin(D6,READ_BIT(data,2));
	DIO_WritePin(D5,READ_BIT(data,1));
	DIO_WritePin(D4,READ_BIT(data,0));
	DIO_WritePin(E,HIGH);
	_delay_ms(2);
	DIO_WritePin(E,LOW);
	_delay_ms(2);
}

void LCD_Init(void)
{
	_delay_ms(50);
	LCD_SendCommand(_4_BITCOMMAND);
	_delay_ms(1);
	LCD_SendCommand(FUNCTION_SET);
	_delay_ms(1);
	LCD_SendCommand(DISP_ON_OFF);
	_delay_ms(1);
	LCD_SendCommand(DISP_CLEAR);
	_delay_ms(20);
	LCD_SendCommand(ENTRY_MODE);
}
#endif

/************************ LCD extern Functions implementations ******************************/

void LCD_WriteChar(const u8 ch)
{
	LCD_SendData(ch);
}

void LCD_WriteString(const u8 *const str)
{
	u8 Index=0;
	for(;str[Index];Index++)
	{
		LCD_WriteChar(str[Index]);
	}
}

void LCD_WriteNumber(s32 number)
{
	u8 str[20]={0};
	s8 index=0;
	if(0 == number)
	{
		LCD_WriteChar('0');	
	}
	else
	{
		if(0 > number)
		{
			LCD_WriteChar('-');
			number = 0 - number;
		}
		else{;}
		
		while(number)
		{
			str[index] = (number%(u8)10)+'0';
			number = (number / (u8)10);
			index++;
		}
		for(--index;index >=0 ; index--)
		{
			LCD_WriteChar(str[index]);
		}
	}
	
}

void LCD_WriteNumber_4Digites(s16 number)
{
	if(0 > number)
	{
		LCD_WriteChar('-');
		number = 0 - number;
	}
	else{;}
	LCD_WriteChar(((number%10000)/1000)+'0');
	LCD_WriteChar(((number%1000)/100)+'0');
	LCD_WriteChar(((number%100)/10)+'0');
	LCD_WriteChar(((number%10)/1)+'0');
}

void LCD_WriteNumber_Hex(u32 number)
{
	u8 hex[9]={0};
	s8 index=0;
	u8 digit=0;
	while(number)
	{
		digit = number %16;
		if(10 > digit)
		{
			hex[index] = digit + '0';
		}
		else
		{
			digit = digit -10;
			hex[index]= digit +'A';
		}
		index++;
		number /= 16;
	}
	for(--index;index >=0;index--)
	{
		LCD_WriteChar(hex[index]);
	}
}

void LCD_WriteNumber_Binary(u16 number)
{
	u8 flag=0;
	s16 iterator=0;
	for(iterator=15;iterator>=0;iterator--)
	{
		if(READ_BIT((number>>iterator),0))
		{
			LCD_WriteChar('1');
			flag=1;
		}
		else
		{
			if(1 == flag)
			{
				LCD_WriteChar('0');
			}
			else{;}
		}
	}
}

void LCD_GoTo(u8 line,u8 cell)
{
	if(0 == line)
	{
		LCD_SendCommand((0x80 | cell));
	}
	else if(1 == line)
	{
		LCD_SendCommand(0x80|(0x40+cell));
	}
	else{;}
}

void LCD_Clear(void)
{
	LCD_SendCommand(0x01);
}


void LCD_GoTo_Clear(u8 line,u8 cell, u8 number_of_cells)
{
	u8 iterator=0;
	LCD_GoTo(line,cell);
	for(;iterator < number_of_cells;iterator++)
	{
		LCD_WriteChar(' ');
	}
	
}


void LCD_GoTo_WriteString(u8 line,u8 cell,u8 *const str)
{
	LCD_GoTo(line,cell);
	LCD_WriteString(str);
}

void LCD_GoTo_WriteChar(u8 line,u8 cell,u8 ch)
{
	LCD_GoTo(line,cell);
	LCD_WriteChar(ch);
}
void LCD_GoTo_WriteNumber(u8 line,u8 cell,s32 number)
{
	LCD_GoTo(line,cell);
	LCD_WriteNumber(number);
}
void LCD_GoTo_WriteNumber_4Digt(u8 line,u8 cell,s16 number)
{
	LCD_GoTo(line,cell);
	LCD_WriteNumber_4Digites(number);
}
void LCD_GoTo_WriteBinary(u8 line,u8 cell,u16 number)
{
	LCD_GoTo(line,cell);
	LCD_WriteNumber_Binary(number);
}
void LCD_GoTo_WriteHex(u8 line,u8 cell,u32 number)
{
	LCD_GoTo(line,cell);
	LCD_WriteNumber_Hex(number);
}

void LCD_ShiftRight_Display_On(void)
{
	LCD_SendCommand(0x1c);
}
void LCD_ShiftLeft_Display_On(void)
{
	LCD_SendCommand(0x18);
}


void LCD_CreateChar(const u8 *const pattern,u8 address)
{
	u8 index=0;
	LCD_SendCommand(0x40 | (8*address));
	for(;index <8;index++)
	{
		LCD_SendData(pattern[index]);
	}
	LCD_GoTo(0,0);
}
