#include "ADC_Interface.h"
#include "ADC_cnfg.h"
void ADC_Init(ADC_VoltageRef_Type vref,ADC_PREScaller_Type prescaller)
{
	//set vref
	switch (vref)
	{
	case ADC_VCCREF:
		CLR_BIT(ADMUX,REFS1);
		SET_BIT(ADMUX,REFS0);
		break;
	case ADC_AREF:
		CLR_BIT(ADMUX,REFS1);
		CLR_BIT(ADMUX,REFS0);
		break;
	case ADC_256REF:
		SET_BIT(ADMUX,REFS1);
		SET_BIT(ADMUX,REFS0);
		break;
	default:
		//Nothing
		break;
	}
	//set right adjust
	CLR_BIT(ADMUX,ADLAR);
	//set prescaller
	ADCSRA &= 0xf8;
	ADCSRA |= prescaller;
	//set enable bit.
	SET_BIT(ADCSRA,ADEN);
}


u16	ADC_Read(ADC_Chanels_Type ch)
{
	u16 ADC_R=0;
	//chose chanel
	ADMUX &= 0xE0;
	ADMUX |= ch;
	//start conversion.
	SET_BIT(ADCSRA,ADSC);
	while (READ_BIT(ADCSRA,ADSC));
	//Read ADCL & ADCH.
	//this one based on right adjust.
	ADC_R = ADCL | ((u16)ADCH << 8);
	return (ADC_R);
}

u16 ADC_Read_MiliVolt(ADC_Chanels_Type ch)
{
	u16 volt=0;
	u16 AdcRead=ADC_Read(ch);
	
	volt = ((REF_VOLT* (u32)1000 * AdcRead)/(1024));
	
	return (volt);
}

void ADC_voidStartConversion(ADC_Chanels_Type ch)
{
	//chose chanel
	ADMUX &= 0xE0;
	ADMUX |= ch;
	//start conversion.
	SET_BIT(ADCSRA,ADSC);
}

Error_t ADC_xReadPeriodic(u16 *const Copy_u16Read)
{
	Error_t Local_xErrorState=OK;
	if(NULL_PTR == Copy_u16Read)
	{
		Local_xErrorState = NULL;
	}
	else if(ZERO_INIT == READ_BIT(ADCSRA,ADSC))
	{
		/*U can Read now*/
		*Copy_u16Read =  ADCL | ((u16)ADCH << 8);
		Local_xErrorState=OK;
	}
	else
	{
		Local_xErrorState =NOK;
	}
	
	return (Local_xErrorState);	
}
