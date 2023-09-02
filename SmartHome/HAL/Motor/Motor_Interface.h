#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_

typedef enum
{
	M1=0,
	M2,
	M3,
	M4,
	M5,
	TOTAL_MOTORS
}Motor_type;


extern void Motor_Stop(Motor_type motor);
extern void Motor_CW(Motor_type motor);
extern void Motor_CCW(Motor_type motor);



#endif /* MOTOR_INTERFACE_H_ */