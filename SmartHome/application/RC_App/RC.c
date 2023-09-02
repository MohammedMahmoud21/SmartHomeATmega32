#include "Motor_Interface.h"
#include "StdTypes.h"
#include "RC_interface.h"

void RC_MoveForward(void)
{
	Motor_CW(M1);
	Motor_CW(M2);
	Motor_CW(M3);
	Motor_CW(M4);
}
void RC_MoveBackward(void)
{
	Motor_CCW(M1);
	Motor_CCW(M2);
	Motor_CCW(M3);
	Motor_CCW(M4);
}
void RC_RotateRight(void)
{
	Motor_CCW(M1);
	Motor_CCW(M2);
	Motor_CW(M3);
	Motor_CW(M4);
}
void RC_RotateLeft(void)
{
	Motor_CW(M1);
	Motor_CW(M2);
	Motor_CCW(M3);
	Motor_CCW(M4);
	
}
void RC_Stop(void)
{
	Motor_Stop(M1);
	Motor_Stop(M2);
	Motor_Stop(M3);
	Motor_Stop(M4);
}