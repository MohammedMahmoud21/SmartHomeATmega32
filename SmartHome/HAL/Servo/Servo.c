#include "Servo.h"
#include "Servo_cnfg.h"


static volatile u16 angle_count=0;
static void servo_timer2_control(void);

void Servo_Init(void)
{
	#if TIMER_USED == Timer1_USED
	
	Timer1_Init(TIMER1_FASTPWM_OCRA_TOP_MODE,TIMER1_SCALER_8);
	Timer1_OCB_Mode(OCRB_NON_INVERTING);
	OCR1A = 19999;
	#elif TIMER_USED == Timer2_USED
	sei();
	Timer2_Init(T2_FAST_PWM,TIMER2_SCALER_8);
	//Timer2_OCR_Mode(OCR2_NON_INVERTING);
	Timer2_SetCallBack(TIMER2_OV,servo_timer2_control);
	Timer2_InterruptEnable(TIMER2_OV);
	TCNT2 = 6;
	#endif
}

void Servo_SetAngle(u16 angle)
{
	u16 value=0;
	#if TIMER_USED == Timer1_USED
	value = (((u32)2000*angle)/180)+499;
	OCR1B = value;
	#elif TIMER_USED == Timer2_USED
	value = (((u32)2000*angle)/180)+500;
	angle_count = 80 - value/250;
	#endif
	
}

static void servo_timer2_control(void)
{
	static u8 count=0;
	count++;
	TCNT2=6;
	if(count == angle_count)
	{
		DIO_WritePin(SERVO_PIN,HIGH);
	}
	else if(count == 80)
	{
		DIO_WritePin(SERVO_PIN,LOW);
		count=0;
	}
	else
	{
		;
	}
}