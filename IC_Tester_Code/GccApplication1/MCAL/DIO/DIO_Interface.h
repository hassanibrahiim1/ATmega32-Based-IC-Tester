/*
 * DIO_Interface.h
 *
 * Created: 12/8/2023 1:48:45 PM
 *  Author: Omar Yasser
 */ 




#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_


/************************************************** include section **********************************************************/

#include "StdTypes.h"

/*************************************************** typedef section ********************************************************/
typedef enum
{
	// ALL PIN IN REGISTER A
	PINA0 = 0,
	PINA1 = 1,
	PINA2,
	PINA3,
	PINA4,
	PINA5,
	PINA6,
	PINA7,
	
	// ALL PIN IN REGISTER B
	PINB0,
	PINB1,
	PINB2,
	PINB3,
	PINB4,
	PINB5,
	PINB6,
	PINB7,
	
	// ALL PIN IN REGISTER C
	PINC0,
	PINC1,
	PINC2,
	PINC3,
	PINC4,
	PINC5,
	PINC6,
	PINC7,
	
	// ALL PIN IN REGISTER D
	PIND0,
	PIND1,
	PIND2,
	PIND3,
	PIND4,
	PIND5,
	PIND6,
	PIND7,
	
	// NUMBER OF TOTAL PIN IN MC
	TOTAL_PIN
}DIO_Pin_type;

typedef enum
{
	PA,
	PB,
	PC,
	PD
}DIO_Port_type;

	
typedef enum 
{
	OUTPUT,
	INPUT_FREE,
	INPUT_PULLUP
}DIO_PinStatues_type;

typedef enum
{
	LOW  = 0,
	HIGH = 1
}DIO_PinVolt_type;	

/******************************************************* Function declaration *****************************************************/

extern void DIO_INIT(void);  // initialization for all pin as we config 
extern void DIO_InitPin(DIO_Pin_type pin ,DIO_PinStatues_type status);
extern void DIO_WritePin(DIO_Pin_type pin , DIO_PinVolt_type volt); // write on a specific pin
extern DIO_PinVolt_type DIO_ReadPin(DIO_Pin_type pin); // read from specific pin
extern void DIO_WritePort(DIO_Port_type port , u8 value); // write a certain value on a specific port
extern u8 DIO_ReadPort(DIO_Port_type port); // read the value from specific port
extern void DIO_TogglePin(DIO_Pin_type pin); // toggle pin



	
	
	
	
	



#endif /* DIO_INTERFACE_H_ */