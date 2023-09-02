#ifndef LCD_CNFG_H_
#define LCD_CNFG_H_
#include "DIO_interface.h"
#include "StdTypes.h"

#define _4_BIT_MODE	(1)
#define _8_BIT_MODE	(2)

#define LCD_MODE	_4_BIT_MODE

#define RS			PA1
#define E			PA2

#if LCD_MODE == _8_BIT_MODE

#define LCD_PORT	PA

#elif LCD_MODE == _4_BIT_MODE

#define D7	PA6
#define D6	PA5
#define D5	PA4
#define D4	PA3

#endif

#endif /* LCD_CNFG_H_ */