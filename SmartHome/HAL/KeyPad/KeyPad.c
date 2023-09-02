#include "KeyPad_private.h"
#include "KeyPad_interface.h"

u8 KeyPad_GetKey(void)
{
	u8 key=NO_KEY;
	u8 row=0;
	u8 colm=0;
	u8 iterator=0;
	//initialize all rows with 1, as we enabled pull up resistor.
	for(iterator=0;iterator<ROWS;iterator++)
	{
		DIO_WritePin(KeyPad_Rows[iterator],HIGH);
	}
	/*
		Sequence:
		a. put low on one of rows.
		b. go read all input pins (colms).
		c. if PB was pressed return value (check KeyPAd_Array for reference).
		d. if not put high again on the row and repeate from b.
	*/
	for(;row < ROWS;row++)
	{
		DIO_WritePin(KeyPad_Rows[row],LOW);
		for(colm=0;colm<COLMS;colm++)
		{
			if(LOW == DIO_ReadPin(KeyPad_Colms[colm]))
			{
				key = KeyPad_Array[row][colm];
				while(LOW == DIO_ReadPin(KeyPad_Colms[colm]));
			}
			else{;}
		}
		DIO_WritePin(KeyPad_Rows[row],HIGH);
	}
	
	return (key);
}