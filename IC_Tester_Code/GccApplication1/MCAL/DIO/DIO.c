/*
 * DIO.c
 *
 * Created: 12/8/2023 1:48:23 PM
 *  Author: Omar Yasser
 */ 


/******************************************************* include section ***********************************************************/
#include "DIO_Interface.h"
#include "Utilities.h"
#include "MemoryMap.h"
#include "DIO_Private.h"

/*********************************************************** Function Implementation *****************************************************/
void DIO_InitPin(DIO_Pin_type pin ,DIO_PinStatues_type status)
{
	u8 port = pin/8;
	u8 num_pin = pin%8;
	switch(port)
	{
		// PORT A
		case PA:
			switch(status)
			{
				case OUTPUT:
					SET_BIT(DDRA,num_pin);
					break;
				case INPUT_FREE:
					CLR_BIT(DDRA,num_pin);
					break;
				case INPUT_PULLUP:
					CLR_BIT(DDRA,num_pin);
					SET_BIT(PORTA,num_pin);
					break;
			}
			break;
		
		// PORT B
		case PB:
			switch(status)
			{
				case OUTPUT:
					SET_BIT(DDRB,num_pin);
					break;
				case INPUT_FREE:
					CLR_BIT(DDRB,num_pin);
					break;
				case INPUT_PULLUP:
					CLR_BIT(DDRB,num_pin);
					SET_BIT(PORTB,num_pin);
					break;
			}
			break;
		
		// PORT C
		case PC:
			switch(status)
			{
				case OUTPUT:
					SET_BIT(DDRC,num_pin);
					break;
				case INPUT_FREE:
					CLR_BIT(DDRC,num_pin);
					break;
				case INPUT_PULLUP:
					CLR_BIT(DDRC,num_pin);
					SET_BIT(PORTC,num_pin);
					break;
			}
			break;
		
		// PORTD
		case PD:
			switch(status)
			{
				case OUTPUT:
					SET_BIT(DDRD,num_pin);
					break;
				case INPUT_FREE:
					CLR_BIT(DDRD,num_pin);
					break;
				case INPUT_PULLUP:
					CLR_BIT(DDRD,num_pin);
					SET_BIT(PORTD,num_pin);
					break;
			}
			break;
	}

	
}

void DIO_INIT(void)
{
	for(DIO_Pin_type i = PINA0 ; i < TOTAL_PIN ; ++i)
	{
		DIO_InitPin(i,Pin_Statues[i]);
	}
}
void DIO_WritePin(DIO_Pin_type pin , DIO_PinVolt_type volt)
{
	u8 port = pin/8;
	u8 num_pin = pin%8;
	
	switch(port)
	{
		// PORT A
		case PA:
			switch(volt)
			{
				case HIGH:
					SET_BIT(PORTA,num_pin);
					break;
				case LOW:
					CLR_BIT(PORTA,num_pin);
					break;
			}
			break;
		
		// PORT B
		case PB:
			switch(volt)
			{
				case HIGH:
				SET_BIT(PORTB,num_pin);
				break;
				case LOW:
				CLR_BIT(PORTB,num_pin);
				break;
			}
			break;
			
		// PORT C	
		case PC:
			switch(volt)
			{
				case HIGH:
				SET_BIT(PORTC,num_pin);
				break;
				case LOW:
				CLR_BIT(PORTC,num_pin);
				break;
			}
			break;
			
		// PORTD	
		case PD:
			switch(volt)
			{
				case HIGH:
				SET_BIT(PORTD,num_pin);
				break;
				case LOW:
				CLR_BIT(PORTD,num_pin);
				break;
			}
			break;
	}

}
DIO_PinVolt_type DIO_ReadPin(DIO_Pin_type pin)
{
	u8 port = pin/8;
	u8 num_pin = pin%8;
	DIO_PinVolt_type volt = LOW;
	switch(port)
	{
		// PORT A
		case PA:
			volt = READ_PIN(PINA,num_pin);
			break;
		
		// PORT B
		case PB:
			volt = READ_PIN(PINB,num_pin);
			break;
		
		// PORT C
		case PC:
			volt = READ_PIN(PINC,num_pin);
			break;
		
		// PORTD
		case PD:
			volt = READ_PIN(PIND,num_pin);
			break;
	}
	
	return volt;
	
}
void DIO_WritePort(DIO_Port_type port , u8 value)
{
	switch(port)
	{
		// PORT A
		case PA:
			PORTA = value;		
			break;
		
		// PORT B
		case PB:
			PORTB = value;
			break;
		
		// PORT C
		case PC:
			PORTC = value;
			break;
		
		// PORTD
		case PD:
			PORTD = value;
			break;
	}
	
}
u8 DIO_ReadPort(DIO_Port_type port)
{
	u8 value = 0;
	switch(port)
	{
		// PORT A
		case PA:
			value = PINA;
			break;
		
		// PORT B
		case PB:
			value = PINB;
			break;
		
		// PORT C
		case PC:
			value = PINC;
			break;
		
		// PORTD
		case PD:
			value = PIND;
			break;
	}
	return value;
	
}
void DIO_TogglePin(DIO_Pin_type pin)
{
	u8 port = pin/8;
	u8 num_pin = pin%8;
	
	switch(port)
	{
		// PORT A
		case PA:
			TOGGLE_BIT(PORTA,num_pin);
		break;
		
		// PORT B
		case PB:
			TOGGLE_BIT(PORTB,num_pin);
		break;
		
		// PORT C
		case PC:
			TOGGLE_BIT(PORTC,num_pin);
		break;
		
		// PORTD
		case PD:
			TOGGLE_BIT(PORTD,num_pin);
		break;
	}

}