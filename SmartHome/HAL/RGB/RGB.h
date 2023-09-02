#ifndef RGB_H_
#define RGB_H_

#include "Timers_interface.h"
#define F_CPU	(8000000UL)
#include <util/delay.h>

#define RGB_VOLTS_COUNT		(3)

typedef enum
{
	RED=0,
	BLUE,
	GREEN,
	BLACK,
	DARK_BLUE,
	VIOLET,
	ORANGE,
	WHITE,
	DARK_ORANGE,
	SKY,
	PINK,
	GRAY,
	COLOURS_COUNT
}RGB_Colour_type;

extern void RGB_Init(void);
extern void RGB_SetColour(RGB_Colour_type colour);
extern void RGB_SlideColour(void);

#endif /* RGB_H_ */