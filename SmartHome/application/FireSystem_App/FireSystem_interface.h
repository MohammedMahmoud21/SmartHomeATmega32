#ifndef FIRESYSTEM_INTERFACE_H_
#define FIRESYSTEM_INTERFACE_H_
#include "Utiles.h"
#include "MemMap.h"
#include "StdTypes.h"

#define NORMAL_TEMP	(400)
#define HEAT_TEMP	(450)

typedef enum
{
	NORMAL,
	HEAT,
	FIRE,
	NO_INIT
}FireModes_Type;

extern void FireSystem_Init(void);
extern void Fire_SafeMode(u16 temp);
extern void Fire_HeatMode(u16 smoke,u16 temp);
extern void Fire_FireMode(u16 smoke,u16 temp);
extern bool_type Fire_GetPassword(void);
#endif /* FIRESYSTEM_INTERFACE_H_ */