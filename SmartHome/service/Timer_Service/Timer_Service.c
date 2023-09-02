#include "Timer_Service_interface.h"





void Timer_Service_voidSetInterruptTime_ms(u16 Copy_u16Time,void (*p_func)(void))
{
	//set timer1 to ctc OCRA top.
	Timer1_Init(TIMER1_CTC_OCRA_TOP_MODE,TIMER1_SCALER_8);
	//calc time us.
	OCR1A = (Copy_u16Time *(u32)1000);
	//set callback
	Timer1_SetCallBack(TIMER1_COMA,p_func);
	//enable interrupt.
	Timer1_InterruptEnable(TIMER1_COMA);
}