#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

#include "StdTypes.h"
#include "DIO_interface.h"

#define NO_KEY	((u8)0)


u8 KeyPad_GetKey(void);

#endif /* KEYPAD_INTERFACE_H_ */