#include "EEPROM_Service_interface.h"


void EEPROM_Service_SendString(u16 address,u8*str)
{
	u16 index=0;
	for(;str[index];index++,address++)
	{
		EEPROM_Send(address,str[index]);
	}
	EEPROM_Send(address,0);
}
u8	EEPROM_Serivce_ReceiveString(u16 address,u8*str,u16 size)
{
	u8 error =0;
	u16 index=0;
	if(NULL_PTR == str)
	{
		error =1;
	}
	else
	{
		EEPROM_Receive(address,str);
		for(index=0;(str[index]) && (index < size-1);)
		{
			index++;
			address++;
			EEPROM_Receive(address,str+index);
		}
		str[index]=0;
	}
	return (error);
}