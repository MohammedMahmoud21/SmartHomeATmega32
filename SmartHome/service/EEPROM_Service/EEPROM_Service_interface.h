#ifndef EEPROM_SERVICE_INTERFACE_H_
#define EEPROM_SERVICE_INTERFACE_H_
#include "EEPROM_interface.h"


extern void EEPROM_Service_SendString(u16 address,u8*str);
extern u8	EEPROM_Serivce_ReceiveString(u16 address,u8*str,u16 size);
#endif /* EEPROM_SERVICE_INTERFACE_H_ */