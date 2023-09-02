#ifndef TIMERS_INTERFACE_H_
#define TIMERS_INTERFACE_H_

#include "MemMap.h"
#include "StdTypes.h"
#include "Utiles.h"

/******************** Timer0 *******************************/

/********************User Definded data types*********************************/

typedef enum{
	TIMER0_STOP=0,
	TIMER0_SCALER_1,
	TIMER0_SCALER_8,
	TIMER0_SCALER_64,
	TIMER0_SCALER_256,
	TIMER0_SCALER_1024,
	EXTERNALl_FALLING,
	EXTERNAL_RISING
}Timer0_Scaler_type;

typedef enum
{
	TIMER0_NORMAL_MODE=0,
	TIMER0_PHASECORRECT_MODE,
	TIMER0_CTC_MODE,
	TIMER0_FASTPWM_MODE

}Timer0_Mode_type;

typedef enum
{
	Timer0_Comp,
	Timer0_OV
}Timer0_Interrupt_type;

typedef enum
{
	OCO_DISCONNECTED=0,
	OCO_TOGGLE,
	OCO_NON_INVERTING,
	OCO_INVERTING
}OC0_Mode_type;

/******************* Functions protoypes ***********************************/
extern void Timer0_Init(Timer0_Mode_type mode,Timer0_Scaler_type scaler);
extern void Timer0_OC0_Mode(OC0_Mode_type mode);
extern void Timer0_InterruptEnable(Timer0_Interrupt_type interrupt);
extern void Timer0_InterruptDisable(Timer0_Interrupt_type interrupt);
extern void Timer0_SetCallBack(Timer0_Interrupt_type interrupt,void (*p)(void));


/******************** Timer1 *******************************/

/********************User Definded data types*********************************/

typedef enum{
	TIMER1_STOP=0,
	TIMER1_SCALER_1,
	TIMER1_SCALER_8,
	TIMER1_SCALER_64,
	TIMER1_SCALER_256,
	TIMER1_SCALER_1024,
	EXTERNAL0_FALLING,
	EXTERNAL0_RISING
}Timer1_Scaler_type;

typedef enum
{
	TIMER1_NORMAL_MODE=0,
	TIMER1_CTC_ICR_TOP_MODE,
	TIMER1_CTC_OCRA_TOP_MODE,
	TIMER1_FASTPWM_ICR_TOP_MODE,
	TIMER1_FASTPWM_OCRA_TOP_MODE,
	TIMER1_FASTPWM_8bit
}Timer1_Mode_type;

typedef enum
{
	OCRA_DISCONNECTED=0,
	OCRA_TOGGLE,
	OCRA_NON_INVERTING,
	OCRA_INVERTING

}OC1A_Mode_type;

typedef enum
{
	OCRB_DISCONNECTED=0,
	OCRB_TOGGLE,
	OCRB_NON_INVERTING,
	OCRB_INVERTING

}OC1B_Mode_type;


typedef enum{
	RISING,
	FALLING
}ICU_Edge_type;

typedef enum
{
	TIMER1_OV,
	TIMER1_COMA,
	TIMER1_COMB,
	TIMER1_ICU
}Timer1_Interrupt_type;

/******************* Functions protoypes ***********************************/
extern void Timer1_Init(Timer1_Mode_type mode,Timer1_Scaler_type scaler);
extern void Timer1_OCA_Mode(OC1A_Mode_type mode);
extern void Timer1_OCB_Mode(OC1B_Mode_type mode);
extern void Timer1_ICP_Mode(ICU_Edge_type type);
extern void Timer1_InterruptEnable(Timer1_Interrupt_type interrupt);
extern void Timer1_InterruptDisable(Timer1_Interrupt_type interrupt);
extern void Timer1_SetCallBack(Timer1_Interrupt_type interrupt, void (*p)(void));



/******************** Timer2 *******************************/

/********************User Definded data types*********************************/

typedef enum
{
	T2_NORMAL,
	T2_CTC,
	T2_FAST_PWM,
	T2_PHASE_CORRECT	
}Timer2_Mode_type;

typedef enum
{
	TIMER2_STOP=0,
	TIMER2_SCALER_1,
	TIMER2_SCALER_8,
	TIMER2_SCALER_64,
	TIMER2_SCALER_256,
	TIMER2_SCALER_1024,
	EXTERNAL2_FALLING,
	EXTERNAL2_RISING
}Timer2_Scaler_type;

typedef enum
{
	OCR2_DISCONNECTED=0,
	OCR2_TOGGLE,
	OCR2_NON_INVERTING,
	OCR2_INVERTING

}OC2_Mode_type;

typedef enum
{
	TIMER2_COMP,
	TIMER2_OV
}Timer2_Interrupt_type;;

/******************* Functions protoypes ***********************************/
extern void Timer2_Init(Timer2_Mode_type mode,Timer2_Scaler_type scaler);
extern void Timer2_OCR_Mode(OC2_Mode_type mode);
extern void Timer2_InterruptEnable(Timer2_Interrupt_type interrupt);
extern void Timer2_InterruptDisable(Timer2_Interrupt_type interrupt);
extern void Timer2_SetCallBack(Timer2_Interrupt_type interrupt,void (*p_fnc)(void));
#endif /* TIMERS_INTERFACE_H_ */