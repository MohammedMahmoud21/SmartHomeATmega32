#include "Sensors_interface.h"
#include "Sensors_cnfg.h"



u16 LM35_GetTemp(void)
{
	u16 Temp=0;
	u16 volt=ADC_Read_MiliVolt(LM35_CH);
	Temp = volt;
	return (Temp);	
}

u8  POT_GetPerc(void)
{
	u8 perc=0;
	u16 adc = ADC_Read(POT_CH);
	perc = ((u32)100*adc)/1023;
	return (perc);
}

u16 MPX_GetPressure(void)
{
	u16 pressure=0;
	u16 adc = ADC_Read(MPX4115);
	if(adc > 980)
	{
		adc = 976;
	}
	else if(adc < 50)
	{
		adc = 55;
	}
	else{;}
	pressure = ((((adc*(u32)10)-550)*(u32)100)/921)+150;
	return (pressure);	
}

Error_t LDR_GetValue(u16 *Copy_u16pData)
{
	static u8 Local_u8ConversionFlag=ZERO_INIT;
	Error_t Local_xErrorState=OK;
	u16 read=0;
	u16 ldr=0;
	if(ZERO_INIT == Local_u8ConversionFlag)
	{
		ADC_voidStartConversion(LDR_CH);
		Local_u8ConversionFlag=1;
		Local_xErrorState = NOK;
	}
	else
	{
		Local_xErrorState = ADC_xReadPeriodic(&read);
		if(OK == Local_xErrorState)
		{
			*Copy_u16pData = ((u32)100*(read-360))/1003;
			Local_u8ConversionFlag=ZERO_INIT;
		}
		else
		{
			Local_xErrorState = NOK;
		}
	}
	return (Local_xErrorState);
}