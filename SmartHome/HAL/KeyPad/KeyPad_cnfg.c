#include "KeyPad_cnfg.h"

/*To change values of ROWS and COLMS check (KeyPad_cnfg.h)*/
/*This array hold the values printed on keypad (changeable)*/
const u8 KeyPad_Array[ROWS][COLMS] = {{'7','8','9','A'},
									  {'4','5','6','B'},
									  {'1','2','3','C'},
									  {'c','0','=','E'}
									 };
/*const u8 KeyPad_Array[ROWS][COLMS] = {{'c','7','8','9','*','/'},
									  {'n','4','5','6','-','D'},
									  {'%','1','2','3','+','E'},
									  {'%','0','.','=','+','F'}
									  };*/

/*These two arrays contain values of pins connecting keypad with MC (changeable)*/
/*note Rows are output from MC so don't forget to init them in DIO*/
const DIO_Pin_type KeyPad_Rows[ROWS]  =  {PC0,PC1,PC2,PC3};
/*note COLMS are INPUT from MC so don't forget to init them in DIO*/
const DIO_Pin_type KeyPad_Colms[COLMS] =  {PC4,PC5,PC6,PC7};