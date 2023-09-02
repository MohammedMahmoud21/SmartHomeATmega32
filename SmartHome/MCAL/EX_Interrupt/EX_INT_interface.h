#ifndef EX_INT_INTERFACE_H_
#define EX_INT_INTERFACE_H_


typedef enum
{
	LOW_LEVEL=0,
	ANY_CHANGE=1,
	FALLING_EDGE,
	RISING_EDGE
}EXINT_SenseControl_type;

typedef enum
{
	EX_INT0,
	EX_INT1
}EXINT_IntNumber_type;

typedef enum
{
	EX_INT0_ENABLE,
	EX_INT1_ENABLE,
	EX_INT2_ENABLE
}EXINT_RequestEnable_type;


extern void EX_INT_SetSenseControl(EXINT_IntNumber_type interrupt,EXINT_SenseControl_type type);
extern void EX_INT_Enable(EXINT_RequestEnable_type interrupt);
extern void EX_INT_Disable(EXINT_RequestEnable_type interrupt);
extern void EX_INT_Set_CallBack(EXINT_RequestEnable_type interrupt, void (*p_func)(void));

#endif /* EX_INT_INTERFACE_H_ */