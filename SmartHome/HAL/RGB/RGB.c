#include "RGB.h"
#include "RGB_private.h"


void RGB_Init(void)
{
	Timer0_Init(TIMER0_FASTPWM_MODE,TIMER0_SCALER_8);
	Timer1_Init(TIMER1_FASTPWM_8bit,TIMER1_SCALER_8);
	//ICR1=256;
	//TODO: set OC pins as non inverting.
	Timer0_OC0_Mode(OCO_NON_INVERTING);
	Timer1_OCA_Mode(OCRA_NON_INVERTING);
	Timer1_OCB_Mode(OCRB_NON_INVERTING);
}

void RGB_SetColour(RGB_Colour_type colour)
{
	//set red value.
	OCR0  = RGB_Array[colour][0];
	//set green value.
	OCR1A = RGB_Array[colour][1];
	//set blue value.
	OCR1B = RGB_Array[colour][2];
}

void RGB_SlideColour(void)
{
	u16 Red=255;
	u16 Green=255;
	u16 Blue=255;
	u8 Counter=0;
	u16 Counter2=0;
	for(;Counter<3;Counter++)
	{
		for(Counter2=0;Counter2<=255;Counter2++)
		{
			switch (Counter)
			{
			case 0:
				Red--;
				break;
			case 1:
				Green--;
				break;
			case 2:
				Blue--;
				break;
			}
			OCR0=Red;
			OCR1A = Green;
			OCR1B = Blue;
			_delay_ms(10);
		}
		/*switch (Counter)
		{
			case 0:
			//Red=255;
			break;
			case 1:
			//Green=255;
			break;
			case 2:
			Blue=255;
			break;
		}*/
		
	}	
}
