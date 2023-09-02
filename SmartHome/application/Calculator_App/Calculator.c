#include "Calculator_interface.h" 


void Calculator_Init(void)
{
	DIO_Init();
	LCD_Init();
	LCD_GoTo_WriteString(0,0,"    Welcome To   :");
	LCD_GoTo_WriteString(1,0,"Calculator App");
	_delay_ms(2000);
	LCD_Clear();
	_delay_ms(2);
	LCD_GoTo_WriteString(0,0,"    Made By   ");
	LCD_GoTo_WriteString(1,0,"Mohamed Elsayaad");
	_delay_ms(3000);
	LCD_Clear();
}

s32 Calculator_TakeNumber(Operation_type *const operation,bool_type clear)
{
	s32 number=0;
	u8 loop_flag=1;
	u8 start_flag=0;
	u8 clear_flag=0;
	u8 negative_flag=0;
	u32 key =NO_KEY;
	u8 temp=0;
	while(loop_flag)
	{
		key = KeyPad_GetKey();
		temp = ((ADD == key) || (SUB == key) || (MUL == key) || (DIV == key) || (REM == key) || (CALC == key) || (END == key));
		if(('0' <= key) && ('9'>= key))	
		{
			if((TRUE == clear) && (0==clear_flag))
			{
				LCD_GoTo_Clear(0,0,15);
				LCD_GoTo(0,0);
				clear_flag=1;
			}
			else{;}
			LCD_WriteChar(key);
			number = (number*10)+(key-'0');
		}
		else if(1 == temp)
		{
			if((TRUE == clear) && (0==clear_flag))
			{
				LCD_GoTo_Clear(0,0,15);
				LCD_GoTo(0,0);
				clear_flag=1;
			}
			else{;}
			*operation = key;
			LCD_WriteChar(key);
			loop_flag=0;
		}
		else
		{
			
			if((0 == start_flag) && ('n' == key))
			{
				negative_flag=1;
				LCD_WriteChar('-');
				start_flag=1;
			}
		}
		temp=0;
	}
	if(1 == negative_flag)
	{
		number = 0 - number;
	}
	else{;}
	return (number);	
}