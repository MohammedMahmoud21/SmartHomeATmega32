#include "DIO_interface.h"
#include "StdTypes.h"
#include "Motor_Interface.h"
#include "Motor_cnfig.h"

static const u8 Motor_Number_Array[TOTAL_MOTORS][3] =
{
	{M1_IN1,M1_IN2,M1_EN},
	{M2_IN1,M2_IN2,M2_EN},
	{M3_IN1,M3_IN2,M3_EN},
	{M4_IN1,M4_IN2,M4_EN},
	{M5_IN1,M5_IN2,M5_EN}
};

void Motor_Stop(Motor_type motor)
{
	if((motor%5) < NUMBER_OF_MOTORS)
	{
		DIO_WritePin(Motor_Number_Array[motor%5][0],LOW);
		DIO_WritePin(Motor_Number_Array[motor%5][1],LOW);
		DIO_WritePin(Motor_Number_Array[motor%5][2],LOW);	
	}
	else
	{
		;
	}
	
}

extern void Motor_CW(Motor_type motor)
{
	if((motor%5) < NUMBER_OF_MOTORS)
	{
		DIO_WritePin(Motor_Number_Array[motor%5][0],HIGH);
		DIO_WritePin(Motor_Number_Array[motor%5][1],LOW);
		DIO_WritePin(Motor_Number_Array[motor%5][2],HIGH);
	}
	else
	{
		;
	}
}

extern void Motor_CCW(Motor_type motor)
{
	if((motor%5) < NUMBER_OF_MOTORS)
	{
		DIO_WritePin(Motor_Number_Array[motor%5][0],LOW);
		DIO_WritePin(Motor_Number_Array[motor%5][1],HIGH);
		DIO_WritePin(Motor_Number_Array[motor%5][2],HIGH);
	}
	else
	{
		;
	}
}