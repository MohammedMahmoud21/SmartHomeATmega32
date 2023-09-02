#ifndef STRINGS_H_
#define STRINGS_H_
#include "StdTypes.h"

#define EQUAL		(1)
#define NOT_EQUAL	(0)
#define DIFF		('a' - 'A')
//Calc abs value of any number
#define ABS(number)		((number) * (((2*number)+1)%2))

extern u8 String_Compare(u8 *str1,u8 *str2);
/************************************************************************/
/* @brief: function split string compined of string and number like this LEDON 1, splited1 = LEDON and splited2=1,
			String must have one space and doesn't matter if its upper or lower or mix.
*/
/************************************************************************/
extern Error_t String_Split(u8 *main_str,u8 *splited_str1,u32 *splited_number);

#endif /* STRINGS_H_ */