/**************************** Author : Mohammed Elsayaad *******************************/
/**************************** Date : 9 March,2023         *******************************/
/**************************** Description: Smart Home main c file  *******************************/
/*
This smart home project uses an ATmega32 microcontroller to control the lights, door, fan, and RGB LED in a home. The microcontroller is connected to a variety of sensors and actuators, including:

A light sensor to detect the ambient light level and adjust the brightness of the lights accordingly.
A door sensor to detect whether the door is open or closed.
A servo motor to control the door.
A DC motor to control the fan.
An RGB LED to create custom light colors.
A keypad to enter the door password.
An LCD display to show the system state, such as the current light level and the door status.
The microcontroller is programmed to perform the following tasks:

Read the light sensor and adjust the brightness of the lights accordingly.
Read the door sensor and open or close the door as needed.
Control the DC motor to turn the fan on or off and to change the fan speed.
Change the color of the RGB LED.
Read the keypad and check the door password.
Display the system state on the LCD display.
The door password is saved in EEPROM, which is a type of memory that can be used to store data even when the power is turned off. This allows the door password to be changed easily without having to reprogram the microcontroller.
*/ 
/***************************************************************************************/
/***************************************************************************************/

#include "SmartHome_interface.h"


int main(void)
{
	SmartHome_voidInit();
	SmartHome_voidStart();
}


