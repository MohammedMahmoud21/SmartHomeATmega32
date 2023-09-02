#include "SmartHome_interface.h"
/************************************************************************/
/****************** Global Variables Defenation *************************/
/************************************************************************/

static char Paswword[smarthomePASSWORD_LENGTH] = "Elsayaad";
volatile static u8 MyTimer_Flag=ZERO_INIT;

/************************************************************************/
/******************static Functions Decleration *************************/
/************************************************************************/

static Error_t SmartHome_xSplitString(char *const Copy_charpMainString,char *const Copy_charpSplitString,u32 *const Copy_u32pNumber);
static Error_t SmartHome_DetecOperation(char **Copy_charppOperationsArray,const u8 Copy_u8Size,char *Copy_charpString,System_States_type *const Copy_xpStateFlag);
static void	SmartHome_Perform_LDEOn(u32 number);
static void	SmartHome_Perform_LDEOff(u32 number);
static void	SmartHome_Perform_MoveServo(u32 number);
static void	SmartHome_Perform_Set_RGBColour(u32 number);
static void SmartHome_Perform_FanOn(u32 number);
static void SmartHome_Perform_FanOff(u32 number);
static void SmartHome_Perform_LightAdjust(u32 number);
static void SmartHome_voidTimerISR(void);


/************************************************************************/
/******************Functions Implementation *****************************/
/************************************************************************/

void SmartHome_voidInit(void)
{
	DIO_Init();
	LCD_Init();
	ADC_Init(ADC_VCCREF,DIV_64);
	RGB_Init();
	Servo_Init();
	UART_Init();
	HC_voidInit();
	Timer0_SetCallBack(Timer0_OV,SmartHome_voidTimerISR);
}
void SmartHome_voidStart(void)
{
	u8 Local_u8MessagesNumber=ZERO_INIT;
	System_States_type Local_u8PrevStateFlag=CLOSED;
	System_States_type Local_u8StateFlag=CLOSED;
	u8 Local_u8EEPROMFlag=ZERO_INIT;
	u8 Local_u8Counter=ZERO_INIT;
	u32 Local_u32Number=ZERO_INIT;
	u8 Local_u8DefaultRet=ZERO_INIT;
	u8 Local_u8DisplayFlag=ZERO_INIT;
	u8 Local_u8Flag=ZERO_INIT;
	Error_t Local_xErrorState=OK;
	/*String to save operated user string on it*/
	char Local_charOperatedString[smarthomeMESSAGES_LENGTH]={ZERO_INIT};
	/*Array of Arrays contain received messages*/
	char Mesaages[smarthomeMESSAGES_SIZE][smarthomeMESSAGES_LENGTH]={ZERO_INIT};
	/*Array of Arrays contain Sent messages to user*/
	char RepliedArray[smarthomeREPLAY_SIZE][smarthomeREPLAY_LENGTH]={"PASSWORD SAVED\n","LED ON\n","LED OFF\n","Door\n","RGB\n","Fan On","Fan Off","LIGHTControl"};
	/*Array of pointers contain system features*/
	char *Operations_Array[smarthomeOperationsCount] = {"ChangePassword","LEDON","LEDOFF","Door","RGB","FanOn","FanOff","LIGHTControl"};
	/*Array of pointers contain system features APIs*/
	void (*Local_voidFeaturesArray[smarthomeOperationsCount])(u32) ={NULL_PTR,&SmartHome_Perform_LDEOn,&SmartHome_Perform_LDEOff,&SmartHome_Perform_MoveServo,&SmartHome_Perform_Set_RGBColour,&SmartHome_Perform_FanOn,&SmartHome_Perform_FanOff,&SmartHome_Perform_LightAdjust};
		
		
	EEPROM_Receive(8,&Local_u8EEPROMFlag);
	if('2' == Local_u8EEPROMFlag)
	{
		EEPROM_Serivce_ReceiveString(10,Paswword,smarthomePASSWORD_LENGTH);
	}
	else
	{
		;
	}
	/*Send Locations to receive messages To BCM*/
	HC_xReceiveString(Mesaages[0]);
	HC_xReceiveString(Mesaages[1]);
	HC_xReceiveString(Mesaages[2]);
	HC_xReceiveString(Mesaages[3]);
	HC_xReceiveString(Mesaages[4]);
	LCD_GoTo(0,0);
	LCD_WriteString("System Locked");
	LCD_GoTo(1,0);
	LCD_WriteString("Enter Password");
	while(1)
	{
		/*System locked need password*/
		while((CLOSED == Local_u8StateFlag) || (CHANGE == Local_u8StateFlag))
		{
			if((CHANGE == Local_u8StateFlag) && (ZERO_INIT == Local_u8DisplayFlag))
			{
				LCD_Clear();
				_delay_ms(2);
				LCD_GoTo_WriteString(0,0,"Enter New Pass    ");
				Local_u8DisplayFlag=1;
				Local_u8Flag=ZERO_INIT;
			}
			else
			{
				/*Nothing*/
			}
			
			HC_xDeQueue(&Local_u8MessagesNumber);
			if(ZERO_INIT < Local_u8MessagesNumber)
			{
				Local_u8DefaultRet = String_Compare(Paswword,Mesaages[0]);
				HC_xMessageRead();
				
				if((EQUAL == Local_u8DefaultRet) && (CLOSED == Local_u8StateFlag))
				{
					Local_u8StateFlag= OPENED;
					Local_u8PrevStateFlag = CLOSED;
					LCD_Clear();
					_delay_ms(2);
					Servo_SetAngle(180);
					LCD_GoTo_WriteString(0,0,"System Unlocked");
					LCD_GoTo_WriteString(1,0,"Door Opened");
					LCD_Clear();
					LCD_GoTo_WriteString(0,0,"System Ready");
				}
				else if((NOT_EQUAL == Local_u8DefaultRet) && (CHANGE == Local_u8StateFlag))
				{
					EEPROM_Service_SendString(10,Mesaages[0]);
					EEPROM_Send(8,'2');
					EEPROM_Serivce_ReceiveString(10,Paswword,smarthomePASSWORD_LENGTH);
					/*HC_xSendString("Changed Successfully");*/
					LCD_GoTo_WriteString(0,0,"Enter New Pass");
					/*HC_xSendString("Enter New Password");*/
					Local_u8StateFlag = CLOSED;
				}
				else
				{
					LCD_GoTo_WriteString(1,0,"Wrong Password              ");
					/*HC_xSendString("Wrong Password");*/
				}
			}
			else
			{
				/*Nothing*/
			}
		}
		/*System working*/
		HC_xDeQueue(&Local_u8MessagesNumber);
		if(ZERO_INIT < Local_u8MessagesNumber)
		{
			Local_xErrorState = SmartHome_xSplitString(Mesaages[Local_u8Counter],Local_charOperatedString,&Local_u32Number);
			Local_u8Counter++;
			if(Local_u8Counter >= Local_u8MessagesNumber)
			{
				HC_xMessageRead();
				Local_u8Counter=0;
				
			}
			else
			{
				;
			}
			
			Local_xErrorState = SmartHome_DetecOperation(Operations_Array,smarthomeOperationsCount,Local_charOperatedString,&Local_u8StateFlag);
			if((OK == Local_xErrorState) && (CHANGE != Local_u8StateFlag ))
			{
				Local_voidFeaturesArray[Local_u8StateFlag](Local_u32Number);
				Local_u32Number=0;
				/*HC_xSendString(RepliedArray[Local_u8StateFlag]);*/
			}
			else if(CHANGE == Local_u8StateFlag)
			{
				;
			}
			else
			{
				
				LCD_GoTo_WriteString(0,0,"Wrong Operation");
				/*HC_xSendString("Wrong Option\n");*/
			}
		}
		else
		{
			/*Nothing*/
		}
		if(LIGHTING_OPERATION == Local_u8StateFlag)
		{
			/*Switch on my timer*/
			Local_u8PrevStateFlag = Local_u8StateFlag;
			if(ZERO_INIT == Local_u8Flag)
			{
				Timer0_InterruptEnable(Timer0_OV);
				Local_u8Flag =1;
			}
			else
			{
				/*Nothing*/
			}
			
		}
		else if(CLOSED == Local_u8StateFlag)
		{	
			if(ZERO_INIT == Local_u8Flag)
			{
				Local_u8PrevStateFlag = Local_u8StateFlag;
				Timer0_InterruptDisable(Timer0_OV);
				Local_u8Flag =1;
			}
			else
			{
				/*Nothing*/
			}
		}
		else
		{
			;
		}
		if((LIGHTING_OPERATION == Local_u8PrevStateFlag) && (1 == MyTimer_Flag))
		{
			SmartHome_Perform_LightAdjust(Local_u32Number);
			MyTimer_Flag=ZERO_INIT;
		}
		else
		{
			;
		}
		
		
	}
}

/************************************************************************/
/******************static Functions Implementation **********************/
/************************************************************************/

static Error_t SmartHome_xSplitString(char *const Copy_charpMainString,char *const Copy_charpSplitString,u32 *const Copy_u32pNumber)
{
	Error_t Local_xErrorState=OK;
	if((NULL_PTR == Copy_charpMainString) || (NULL_PTR == Copy_charpSplitString) || (NULL_PTR == Copy_u32pNumber))
	{
		Local_xErrorState =NULL;
	}
	else
	{
		Local_xErrorState = String_Split(Copy_charpMainString,Copy_charpSplitString,Copy_u32pNumber);
		if(OK != Local_xErrorState)
		{
			Local_xErrorState = NOK;
		}
		else
		{
			//NOTHING
		}
	}
	
	return (Local_xErrorState);
}

static Error_t SmartHome_DetecOperation(char **Copy_charppOperationsArray,const u8 Copy_u8Size,char *Copy_charpString,System_States_type *const Copy_xpStateFlag)
{
	Error_t Local_xErrorState=OK;
	System_States_type Local_xIndex=CHANGE;
	u8 flag=1;
	if((NULL_PTR == Copy_charppOperationsArray) || (NULL_PTR == Copy_charpString) || (NULL_PTR == Copy_xpStateFlag))
	{
		Local_xErrorState = NULL;
	}
	else
	{
		for(;(Local_xIndex<Copy_u8Size) && (1 == flag);Local_xIndex++)
		{
			if(EQUAL == String_Compare(Copy_charpString,Copy_charppOperationsArray[Local_xIndex]))
			{
				flag=ZERO_INIT;
				*Copy_xpStateFlag = Local_xIndex;
			}
			else{;}
		}
		if(1 == flag)
		{
			Local_xErrorState = NOK;
			*Copy_xpStateFlag =WRONG_OPERATION;
		}
		else
		{
			Local_xErrorState = OK;
		}
	}
	
	return (Local_xErrorState);
}

static void	SmartHome_Perform_LDEOn(u32 number)
{
	DIO_Pin_type pin=PC0;
	if(number > 3)
	{
		LCD_GoTo_WriteString(1,0,"InvalidOption");
	}
	else
	{
		LCD_GoTo_Clear(1,0,15);
		pin = (pin+number)-1;
		LCD_GoTo_WriteString(1,0,"LEDON");
		DIO_WritePin(pin,HIGH);
	}
	
}
static void	SmartHome_Perform_LDEOff(u32 number)
{
	DIO_Pin_type pin=PC0;
	if(number > 3)
	{
		LCD_GoTo_WriteString(1,0,"InvalidOption");
	}
	else
	{
		LCD_GoTo_Clear(1,0,15);
		LCD_GoTo_WriteString(1,0,"LEDOFF");
		pin = (pin+number)-1;
		DIO_WritePin(pin,LOW);
	}
}
static void	SmartHome_Perform_MoveServo(u32 number)
{
	if(number > 180)
	{
		LCD_GoTo_WriteString(1,0,"InvalidOption");
	}
	else
	{
		LCD_GoTo_Clear(1,0,15);
		LCD_GoTo_WriteString(1,0,"Servo:");
		LCD_GoTo_WriteNumber(1,6,number);
		Servo_SetAngle(number);
	}
}
static void	SmartHome_Perform_Set_RGBColour(u32 number)
{
	if(number > 12)
	{
		LCD_GoTo_WriteString(1,0,"InvalidOption");
	}
	else
	{
		LCD_GoTo_Clear(1,0,15);
		RGB_SetColour((RED+number)-1);
	}
}
static void SmartHome_Perform_FanOn(u32 number)
{
	Motor_CCW(M1);
}
static void SmartHome_Perform_FanOff(u32 number)
{
	Motor_Stop(M1);
}
static void SmartHome_Perform_LightAdjust(u32 number)
{
	Error_t Local_xErrorState=OK;
	u16 Local_u16Read=ZERO_INIT;
	Local_xErrorState = LDR_GetValue(&Local_u16Read);
	if(OK == Local_xErrorState)
	{
		if((0<=Local_u16Read) && (20 >= Local_u16Read))
		{
			/*Very Dark*/
			DIO_WritePin(PC3,HIGH);
			DIO_WritePin(PC4,HIGH);
			DIO_WritePin(PC5,HIGH);
			DIO_WritePin(PC6,HIGH);
			DIO_WritePin(PC7,HIGH);
			DIO_WritePin(PB5,HIGH);
			DIO_WritePin(PB6,HIGH);
			DIO_WritePin(PB7,HIGH);
		}
		else if((22<=Local_u16Read) && (40 >=Local_u16Read))
		{
			DIO_WritePin(PC3,HIGH);
			DIO_WritePin(PC4,HIGH);
			DIO_WritePin(PC5,HIGH);
			DIO_WritePin(PC6,HIGH);
			DIO_WritePin(PC7,HIGH);
			DIO_WritePin(PB5,HIGH);
			DIO_WritePin(PB6,LOW);
			DIO_WritePin(PB7,LOW);
		}
		else if((42 <=Local_u16Read) && (58 >= Local_u16Read))
		{
			DIO_WritePin(PC3,HIGH);
			DIO_WritePin(PC4,HIGH);
			DIO_WritePin(PC5,HIGH);
			DIO_WritePin(PC6,LOW);
			DIO_WritePin(PC7,LOW);
			DIO_WritePin(PB5,LOW);
			DIO_WritePin(PB6,LOW);
			DIO_WritePin(PB7,LOW);
		}
		else
		{
			/*Light High*/
			DIO_WritePin(PC3,HIGH);
			DIO_WritePin(PC4,LOW);
			DIO_WritePin(PC5,LOW);
			DIO_WritePin(PC6,LOW);
			DIO_WritePin(PC7,LOW);
			DIO_WritePin(PB5,LOW);
			DIO_WritePin(PB6,LOW);
			DIO_WritePin(PB7,LOW);
		}
	}
	else
	{
		/*Nothing*/
	}
	
}
static void SmartHome_voidTimerISR(void)
{
	static u16 Local_u16Counter=ZERO_INIT;
	Local_u16Counter++;
	/*Generate alarm every 500ms*/
	if(Local_u16Counter == 1961)
	{
		
		MyTimer_Flag=1;
		Local_u16Counter =ZERO_INIT;
	}
	else
	{
		;
	}
	
}