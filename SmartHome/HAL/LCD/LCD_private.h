#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_
#include "LCD_cnfg.h"

/*make lcd on and display cursor*/
#define DISP_ON_OFF		0x0c
/*Clear Display*/
#define DISP_CLEAR		0x01
/*make address of ddram increase by one and don't shift*/
#define ENTRY_MODE		0x06


#if LCD_MODE == _8_BIT_MODE

/*for 8 bit mode initialization and 5*7 cell*/
#define FUNCTION_SET	0x38

#elif LCD_MODE == _4_BIT_MODE
/*Additional command needed to initialize 4 bit mode in lcd*/
#define _4_BITCOMMAND	0x02
/*for 4 bit mode initialization and 5*7 cell*/
#define FUNCTION_SET	0x28

#endif





static void LCD_SendCommand(u8 command);
static void LCD_SendData(u8 data);

#endif /* LCD_PRIVATE_H_ */