/*
 * LCD_Interface.h
 *
 * Created: 12/11/2023 11:38:10 PM
 *  Author: omarn
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

/*********************************************** Include Section *****************************************/
#include "DIO_Interface.h"


/*********************************************** Function declaration ************************************/
void LCD_INIT(void);
void LCD_CLR(void);
void LCD_WRITE_NUM(s32 num);
void LCD_WRITE_BINARY(u32 num);
void LCD_WRITE_HEX(u32 num);
void LCD_WRITE_CHAR(u8 character);
void LCD_WRITE_STRING(const c8 *string);
void LCD_SET_CURSOR(u8 line , u8 cell);  // line 1:2  , cell 1:16
void LCD_REMOVE_CHAR(void);
void LCD_DRAW(u8 los,u8* draw);
void LCD_MOVING_STRING(c8* string);





#endif /* LCD_INTERFACE_H_ */