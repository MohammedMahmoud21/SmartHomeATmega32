#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_
#include "DIO_interface.h"
#include "StdTypes.h"
#include "Utiles.h"



void LCD_Init(void);
void LCD_WriteString(const u8 *const str);
void LCD_WriteChar(const u8 ch);
void LCD_WriteNumber(s32 number);
void LCD_WriteNumber_4Digites(s16 number);
void LCD_WriteNumber_Hex(u32 number);
void LCD_WriteNumber_Binary(u16 number);
void LCD_GoTo(u8 line,u8 cell);
void LCD_Clear(void);
void LCD_GoTo_Clear(u8 line,u8 cell, u8 number_of_cells);
void LCD_GoTo_WriteString(u8 line,u8 cell,u8 *const str);
void LCD_GoTo_WriteChar(u8 line,u8 cell,u8 ch);
void LCD_GoTo_WriteNumber(u8 line,u8 cell,s32 number);
void LCD_GoTo_WriteNumber_4Digt(u8 line,u8 cell,s16 number);
void LCD_GoTo_WriteBinary(u8 line,u8 cell,u16 number);
void LCD_GoTo_WriteHex(u8 line,u8 cell,u32 number);
void LCD_ShiftRight_Display_On(void);
void LCD_ShiftLeft_Display_On(void);
void LCD_CreateChar(const u8 *const pattern,u8 address);

#endif /* LCD_INTERFACE_H_ */