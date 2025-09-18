/*
 * LCD_cfg.h
 *
 * Created: 12/11/2023 11:43:00 PM
 *  Author: omarn
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_


/********************************************* Marco section *******************************************/
#define _8_bit			  1
#define _4_bit			  0


/******************************************** Mode config *********************************************/
#define MODE _4_bit


/********************************************* Pin Config *********************************************/

#if MODE == _8_bit
/************ 8_bit_initialization *************/
#define LCD_DATA		  PA
#define LCD_EN			  PINB0
#define LCD_RS			  PINB1


#elif MODE== _4_bit
/************ 4_bit_initialization ************/
#define LCD_RS			  PIND5
#define LCD_EN 			  PIND4

#define LCD_D7            PIND3
#define LCD_D6			  PIND2
#define LCD_D5			  PIND1			
#define LCD_D4			  PIND0


#endif


/********************************************* Initialization Config *******************************/


/*************** FUNCTION SET  ****************/                                  
//	 For 8_bit initialization			  (0x38) 
//	 For 4_bit initialization			  (0x28) 

#define FUNC_SET_VALUE    0x28      

/*************** DISPLAY ON/OFF ***************/ 
//   For cursor OFF						  (0x0C)  
//   For cursor OFF and Blinking		  (0x0D)   
//   For cursor ON						  (0x0E)   
//   For cursor ON and Blinking			  (0x0F)

#define DIS_ON_OFF_VALUE  0x0C       

/*************** DISPLAY CLEAR ****************/
#define DIS_CLR_VALUE     0x01

/***************** ENTRY MODE *****************/
//   For shifting cursor to left          (0x04)
//   For shifting cursor to right		  (0x06)
//	 For shifting all characters to left  (0x07)
//	 For shifting all characters to right (0x05)

#define ENTRY_MODE_VALUE  0x06

/********************************************* Cursor set *******************************************/
#define CURSOR_LEFT       0X10  
#define CURSOR_RIGHT      0x14
/*****************************************************************************************************/


#endif /* LCD_CFG_H_ */