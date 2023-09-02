#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_
#include "StdTypes.h"
#include "MemMap.h"
#include "Utiles.h"


extern void EEPROM_Send(u16 address,u8 data);
extern u8	EEPROM_Receive(u16 address,u8 *data);


#endif /* EEPROM_INTERFACE_H_ */