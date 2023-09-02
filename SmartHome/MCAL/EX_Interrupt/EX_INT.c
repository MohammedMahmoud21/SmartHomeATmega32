#include "EX_INT_interface.h"
#include "EX_INT_private.h"

/*********************** static Global variables defination **************/

//define global pointers to function for callback.
static void (*P_Int0)(void) = NULL_PTR;
static void (*P_Int1)(void) = NULL_PTR;
static void (*P_Int2)(void) = NULL_PTR;

/************************************************************************/
/* External interrupt enable, disable and sense control functions.      */
/************************************************************************/

void EX_INT_SetSenseControl(EXINT_IntNumber_type interrupt,EXINT_SenseControl_type type)
{
	switch (interrupt)
	{
	case EX_INT0:
		switch(type)
		{
		case LOW_LEVEL:
			CLR_BIT(MCUCR,ISC00);
			CLR_BIT(MCUCR,ISC01);
			break;
		case ANY_CHANGE:
			SET_BIT(MCUCR,ISC00);
			CLR_BIT(MCUCR,ISC01);
			break;
		case FALLING_EDGE:
			CLR_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
		case RISING_EDGE:
		SET_BIT(MCUCR,ISC00);
		SET_BIT(MCUCR,ISC01);
			break;
		default:
			break;
		}
		break;
	case EX_INT1:
		switch(type)
		{
			case LOW_LEVEL:
			CLR_BIT(MCUCR,ISC10);
			CLR_BIT(MCUCR,ISC11);
			break;
			case ANY_CHANGE:
			SET_BIT(MCUCR,ISC10);
			CLR_BIT(MCUCR,ISC11);
			break;
			case FALLING_EDGE:
			CLR_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
			default:
			break;
		}
		break;
	default:
		break;
	}
}
void EX_INT_Enable(EXINT_RequestEnable_type interrupt)
{
	switch (interrupt)
	{
	case EX_INT0_ENABLE:
		SET_BIT(GICR,INT0_ENABLE);
		break;
	case EX_INT1_ENABLE:
		SET_BIT(GICR,INT1_ENABLE);
		break;
	case EX_INT2_ENABLE:
		SET_BIT(GICR,INT2_ENABLE);
		break;
	default:
		break;
	}	
}
void EX_INT_Disable(EXINT_RequestEnable_type interrupt)
{
	switch (interrupt)
	{
		case EX_INT0_ENABLE:
		CLR_BIT(GICR,INT0_ENABLE);
		break;
		case EX_INT1_ENABLE:
		CLR_BIT(GICR,INT1_ENABLE);
		break;
		case EX_INT2_ENABLE:
		CLR_BIT(GICR,INT2_ENABLE);
		break;
		default:
		break;
	}
}

/************************************************************************/
/*                   Call back function			                        */
/************************************************************************/

void EX_INT_Set_CallBack(EXINT_RequestEnable_type interrupt, void (*p_func)(void))
{
	switch (interrupt)
	{
	case EX_INT0_ENABLE:
		P_Int0 = p_func;
		break;
	case EX_INT1_ENABLE:
		P_Int1 = p_func;
		break;
	case EX_INT2_ENABLE:
		P_Int2 = p_func;
		break;
	default:
		break;	
	}
}

/************************************************************************/
/*                   ISR (interrupt service routine) functions			*/
/************************************************************************/

ISR(INT0_VECT)
{
	if(NULL_PTR == P_Int0)
	{
		//Nothing;
	}
	else
	{
		P_Int0();
	}
}

ISR(INT1_VECT)
{
	if(NULL_PTR == P_Int1)
	{
		//Nothing;
	}
	else
	{
		P_Int1();
	}
}

ISR(INT2_VECT)
{
	if(NULL_PTR == P_Int2)
	{
		//Nothing;
	}
	else
	{
		P_Int2();
	}
}
