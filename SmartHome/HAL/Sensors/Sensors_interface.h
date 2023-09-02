#ifndef SENSORS_INTERFACE_H_
#define SENSORS_INTERFACE_H_
#include "ADC_Interface.h"



extern u16 LM35_GetTemp(void); 
extern u8  POT_GetPerc(void);
extern u16 MPX_GetPressure(void);
extern Error_t LDR_GetValue(u16 *Copy_u16pData);
#endif /* SENSORS_INTERFACE_H_ */