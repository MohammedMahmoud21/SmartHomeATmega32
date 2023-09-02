#include "FireSystem_private.h"
#include "FireSystem_interface.h"

static FireModes_Type Mode_Flag = NO_INIT;

void FireSystem_Init(void)
{
	DIO_Init();
	LCD_Init();
	ADC_Init(ADC_VCCREF,DIV_64);
}

void Fire_SafeMode(u16 temp)
{
	if((NO_INIT == Mode_Flag))
	{
		LCD_Clear();
		_delay_ms(2);
		DIO_WritePin(ORANGE_LED,LOW);
		DIO_WritePin(RED_LED,LOW);
		Motor_Stop(M1);
		LCD_GoTo_WriteString(0,0,"Temp:");
		LCD_WriteNumber(temp/10);
		LCD_WriteChar('.');
		LCD_WriteNumber(temp%10);
		LCD_WriteString("      ");
		LCD_GoTo_WriteString(1,0,"Smoke:");
		LCD_GoTo_Clear(1,6,3);
		LCD_GoTo_WriteString(1,10,"Fine");
		LCD_WriteString("      ");
		Mode_Flag=NORMAL;
	}
	else if (NORMAL == Mode_Flag)
	{
		LCD_GoTo_WriteNumber(0,5,temp/10);
		LCD_WriteChar('.');
		LCD_WriteNumber(temp%10);		
	}
	else
	{
		Mode_Flag=NO_INIT;
	}
}

void Fire_HeatMode(u16 smoke,u16 temp)
{
	if((NORMAL == Mode_Flag) || (NO_INIT == Mode_Flag))
	{
		Motor_Stop(M1);
		DIO_WritePin(RED_LED,LOW);
		DIO_WritePin(ORANGE_LED,HIGH);
		LCD_GoTo_WriteString(0,0,"Temp:");
		LCD_GoTo_WriteNumber(0,5,temp/10);
		LCD_WriteChar('.');
		LCD_WriteNumber(temp%10);
		LCD_WriteString("      ");
		LCD_GoTo_WriteString(1,0,"Smoke:");
		LCD_GoTo_WriteNumber(1,6,smoke);
		LCD_WriteString("% ");
		LCD_GoTo_WriteString(1,10,"HEAT");
		LCD_WriteString("      ");
		Mode_Flag = HEAT;
	}
	else if (HEAT == Mode_Flag)
	{
		LCD_GoTo_WriteNumber(0,5,temp/10);
		LCD_WriteChar('.');
		LCD_WriteNumber(temp%10);
		LCD_GoTo_WriteNumber(1,6,smoke);
		LCD_WriteChar('%');
	}
	else
	{
		Mode_Flag=NORMAL;
	}
}

void Fire_FireMode(u16 smoke,u16 temp)
{
	if((HEAT == Mode_Flag) || (NO_INIT == Mode_Flag))
	{
		DIO_WritePin(ORANGE_LED,LOW);
		DIO_WritePin(RED_LED,HIGH);
		Motor_CW(M1);
		LCD_GoTo_WriteString(0,0,"Temp:");
		LCD_GoTo_WriteNumber(0,5,temp/10);
		LCD_WriteChar('.');
		LCD_WriteNumber(temp%10);
		LCD_WriteString("      ");
		LCD_GoTo_WriteString(1,0,"Smoke:");
		LCD_GoTo_WriteNumber(1,6,smoke);
		LCD_WriteString("% ");
		LCD_GoTo_WriteString(1,10,"FIRE");
		LCD_WriteString("      ");
		Mode_Flag=FIRE;	
	}
	else if(FIRE == Mode_Flag)
	{
		LCD_GoTo_WriteNumber(0,5,temp/10);
		LCD_WriteChar('.');
		LCD_WriteNumber(temp%10);
		LCD_GoTo_WriteNumber(1,6,smoke);
		LCD_WriteChar('%');
	}
	else
	{
		if((NO_INIT == Mode_Flag )|| (NORMAL == Mode_Flag))
		{
			Mode_Flag=HEAT;
		}
		else
		{
			Mode_Flag = FIRE;
		}
	}
}

bool_type Fire_GetPassword(void)
{
	bool_type right=TRUE;
	const u8 *const password = "951753";
	u8 count=0;
	u8 key=NO_KEY;
	LCD_Clear();
	_delay_ms(2);
	LCD_GoTo_WriteString(0,0,"Enter Password");
	LCD_GoTo_WriteString(1,0,"To End Fire Mode");
	_delay_ms(1000);
	LCD_Clear();
	_delay_ms(2);
	LCD_GoTo(0,0);
	while('=' != key)
	{
		key = KeyPad_GetKey();
		if(('0' <= key) && ('9' >= key))
		{
			LCD_WriteChar(key);
			if(password[count] != key)
			{
				right = FASLE;
			}
			else
			{
				count = (++count)%(u8)7;
			}
		}
		else if(NO_KEY == key)
		{
			;
		}
		else if ('=' == key)
		{
			if(count < 6 )
			{
				right = FASLE;
			}
			else{;}
			Mode_Flag = NO_INIT;
			
		}
		else 
		{
			if(0 == count)
			{
				right = FASLE;
				key = '=';
			}
			else
			{
				key = '=';
			}
			Mode_Flag = NO_INIT;
		}
		
	}
	return (right);
}
