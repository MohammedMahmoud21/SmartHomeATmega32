#include "Timers_interface.h"

/********************* Timer 0 ***************************/

static void (*T0_Ov)(void)=NULL_PTR;
static void (*T0_Comp)(void)=NULL_PTR;

/**********************Functions Implementaions*******************************/
void Timer0_Init(Timer0_Mode_type mode,Timer0_Scaler_type scaler)
{
	switch (mode)
	{
	case TIMER0_NORMAL_MODE:
		CLR_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
	case TIMER0_PHASECORRECT_MODE:
		SET_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
	case TIMER0_CTC_MODE:
		CLR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
	case TIMER0_FASTPWM_MODE:
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
	}
	
	TCCR0 &= 0xf8;
	TCCR0 |= scaler;
}
void Timer0_OC0_Mode(OC0_Mode_type mode)
{
	switch (mode)
	{
	case OCO_DISCONNECTED:
		CLR_BIT(TCCR0,COM00);
		CLR_BIT(TCCR0,COM01);
		break;
	case OCO_TOGGLE:
		SET_BIT(TCCR0,COM00);
		CLR_BIT(TCCR0,COM01);
		break;
	case OCO_NON_INVERTING:
		CLR_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
	case OCO_INVERTING:
		SET_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
	}
}
void Timer0_InterruptEnable(Timer0_Interrupt_type interrupt)
{
	if(Timer0_Comp == interrupt)
	{
		SET_BIT(TIMSK,OCIE0);
	}
	else if(Timer0_OV == interrupt)
	{
		SET_BIT(TIMSK,TOIE0);
	}
	else{;}
}
void Timer0_InterruptDisable(Timer0_Interrupt_type interrupt)
{
	if(Timer0_Comp == interrupt)
	{
		CLR_BIT(TIMSK,OCIE0);
	}
	else if(Timer0_OV == interrupt)
	{
		CLR_BIT(TIMSK,TOIE0);
	}
	else{;}
}
void Timer0_SetCallBack(Timer0_Interrupt_type interrupt,void (*p)(void))
{
	if(Timer0_Comp == interrupt)
	{
		T0_Comp = p;
	}
	else if(Timer0_OV == interrupt)
	{
		T0_Ov = p;
	}
	else{;}
}
/****************** Timer0 ISR ***************************/

ISR(TIMER0_OVF_VECT)
{
	if(NULL_PTR == T0_Ov)
	{
		//nothing;
	}
	else
	{
		T0_Ov();
	}
}
ISR(TIMER0_COMP_VECT)
{
	if(NULL_PTR == T0_Comp)
	{
		//Nothing;
	}
	else
	{
		T0_Comp();
	}
}




/********************* Timer 1 ***************************/

static void (*T1_Ov)(void)=NULL_PTR;
static void (*T1_COMA)(void)=NULL_PTR;
static void (*T1_COMB)(void)=NULL_PTR;
static void (*T1_ICU)(void)=NULL_PTR;

/**********************Functions Implementaions*******************************/
void Timer1_Init(Timer1_Mode_type mode,Timer1_Scaler_type scaler)
{
	switch (mode)
	{
	case TIMER1_NORMAL_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;
	case TIMER1_CTC_ICR_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
	case TIMER1_CTC_OCRA_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;
	case TIMER1_FASTPWM_ICR_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
	case TIMER1_FASTPWM_OCRA_TOP_MODE:
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		case TIMER1_FASTPWM_8bit:
		SET_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;
	}
	
	TCCR1B &= 0xF8;
	TCCR1B |= scaler;
}
void Timer1_OCA_Mode(OC1A_Mode_type mode)
{
	switch (mode)
	{
	case OCRA_DISCONNECTED:
		CLR_BIT(TCCR1A,COM1A0);
		CLR_BIT(TCCR1A,COM1A1);
		break;
	case OCRA_TOGGLE:
		SET_BIT(TCCR1A,COM1A0);
		CLR_BIT(TCCR1A,COM1A1);
		break;
	case OCRA_NON_INVERTING:
		CLR_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
	case OCRA_INVERTING:
		SET_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
	}
}
void Timer1_OCB_Mode(OC1B_Mode_type mode)
{
	switch (mode)
	{
	case OCRB_DISCONNECTED:
		CLR_BIT(TCCR1A,COM1B0);
		CLR_BIT(TCCR1A,COM1B1);
		break;
	case OCRB_TOGGLE:
		SET_BIT(TCCR1A,COM1B0);
		CLR_BIT(TCCR1A,COM1B1);
		break;
	case OCRB_NON_INVERTING:
		CLR_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
	case OCRB_INVERTING:
		SET_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
	}
}
void Timer1_ICP_Mode(ICU_Edge_type type)
{
	if(RISING == type)
	{
		SET_BIT(TCCR1B,ICES1);
	}
	else if(FALLING == type)
	{
		CLR_BIT(TCCR1B,ICES1);
	}
	else{;}
}
void Timer1_InterruptEnable(Timer1_Interrupt_type interrupt)
{
	switch (interrupt)
	{
	case TIMER1_OV:
		SET_BIT(TIMSK,TOIE1);
		break;
	case TIMER1_COMA:
		SET_BIT(TIMSK,OCIE1A);
		break;
	case TIMER1_COMB:
		SET_BIT(TIMSK,OCIE1B);
		break;
	case TIMER1_ICU:
		SET_BIT(TIMSK,TICIE1);
		break;
	}
}
void Timer1_InterruptDisable(Timer1_Interrupt_type interrupt)
{
	switch (interrupt)
	{
		case TIMER1_OV:
		CLR_BIT(TIMSK,TOIE1);
		break;
		case TIMER1_COMA:
		CLR_BIT(TIMSK,OCIE1A);
		break;
		case TIMER1_COMB:
		CLR_BIT(TIMSK,OCIE1B);
		break;
		case TIMER1_ICU:
		CLR_BIT(TIMSK,TICIE1);
		break;
	}
}
void Timer1_SetCallBack(Timer1_Interrupt_type interrupt, void (*p)(void))
{
	switch (interrupt)
	{
		case TIMER1_OV:
		T1_Ov=p;
		break;
		case TIMER1_COMA:
		T1_COMA = p;
		break;
		case TIMER1_COMB:
		T1_COMB = p;
		break;
		case TIMER1_ICU:
		T1_ICU = p;
		break;
	}
}
/****************** Timer1 ISR ***************************/
ISR(TIMER1_OVF_VECT)
{
	if(NULL_PTR == T1_Ov)
	{
		//nothing
		;
	}
	else
	{
		T1_Ov();
	}
}


ISR(TIMER1_COMPB_VECT)
{
	if(NULL_PTR == T1_COMB)
	{
		//nothing
		;
	}
	else
	{
		T1_COMB();
	}
}


ISR(TIMER1_COMPA_VECT)
{
	if(NULL_PTR == T1_COMA)
	{
		//nothing
		;
	}
	else
	{
		T1_COMA();
	}
}

ISR(TIMER1_CAPT_VECT)
{
	if(NULL_PTR == T1_ICU)
	{
		//nothing
		;
	}
	else
	{
		T1_ICU();
	}
}


/********************* Timer 2 ***************************/
static void (*Timer2_OV)(void)=NULL_PTR;
static void (*Timer2_COMP)(void)=NULL_PTR;
/**********************Functions Implementaions*******************************/

void Timer2_Init(Timer2_Mode_type mode,Timer2_Scaler_type scaler)
{
	switch (mode)
	{
	case T2_NORMAL:
		CLR_BIT(TCCR2,WGM20);
		CLR_BIT(TCCR2,WGM21);
		break;
	case T2_CTC:
		SET_BIT(TCCR2,WGM20);
		CLR_BIT(TCCR2,WGM21);
		break;
	case T2_FAST_PWM:
		CLR_BIT(TCCR2,WGM20);
		SET_BIT(TCCR2,WGM21);
		break;
	case T2_PHASE_CORRECT:
		SET_BIT(TCCR2,WGM20);
		SET_BIT(TCCR2,WGM21);
		break;
	}
	
	TCCR2 &= 0xf8;
	TCCR2 |= scaler;
	//CLR_BIT(ASSR,AS2);
}
void Timer2_OCR_Mode(OC2_Mode_type mode)
{
	switch (mode)
	{
	case OCR2_DISCONNECTED:
		CLR_BIT(TCCR2,COM20);
		CLR_BIT(TCCR2,COM21);
		break;
	case OCR2_TOGGLE:
		SET_BIT(TCCR2,COM20);
		CLR_BIT(TCCR2,COM21);
		break;
	case OCR2_NON_INVERTING:
		CLR_BIT(TCCR2,COM20);
		SET_BIT(TCCR2,COM21);
		break;
	case OCR2_INVERTING:	
		SET_BIT(TCCR2,COM20);
		SET_BIT(TCCR2,COM21);
		break;
	}
}

void Timer2_InterruptEnable(Timer2_Interrupt_type interrupt)
{
	if(TIMER2_COMP == interrupt)
	{
		SET_BIT(TIMSK,OCIE2);
	}
	else if(TIMER2_OV == interrupt)
	{
		SET_BIT(TIMSK,TOIE2);
	}
	else{;}
}
void Timer2_InterruptDisable(Timer2_Interrupt_type interrupt)
{
	if(TIMER2_COMP == interrupt)
	{
		CLR_BIT(TIMSK,OCIE2);
	}
	else if(TIMER2_OV == interrupt)
	{
		CLR_BIT(TIMSK,TOIE2);
	}
	else{;}
}
extern void Timer2_SetCallBack(Timer2_Interrupt_type interrupt,void (*p_fnc)(void))
{
	if(TIMER2_COMP == interrupt)
	{
		Timer2_COMP=p_fnc;
	}
	else if(TIMER2_OV == interrupt)
	{
		Timer2_OV=p_fnc;
	}
	else{;}
}

/****************** Timer2 ISR ***************************/

ISR(TIMER2_COMP_VECT)
{
	if(NULL_PTR != Timer2_COMP)
	{
		Timer2_COMP();
	}
	else{;}
}

ISR(TIMER2_OVF_VECT)
{
	if(NULL_PTR != Timer2_OV)
	{
		Timer2_OV();
	}
	else{;}
}