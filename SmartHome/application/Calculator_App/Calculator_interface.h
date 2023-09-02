#ifndef CALCULATOR_INTERFACE_H_
#define CALCULATOR_INTERFACE_H_
#include "StdTypes.h"
#include "LCD_interface.h"
#include "KeyPad_interface.h"

typedef enum
{
	ADD='+',
	SUB='-',
	MUL='*',
	DIV='/',
	REM='%',
	CALC='=',
	END ='c',
	NO_OP=0
}Operation_type;


extern void Calculator_Init(void);
extern s32 Calculator_TakeNumber(Operation_type *const operation,bool_type clear);

#endif /* CALCULATOR_INTERFACE_H_ */