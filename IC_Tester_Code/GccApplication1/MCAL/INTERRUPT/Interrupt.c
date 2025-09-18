/*
 * Interrupt.c
 *
 * Created: 12/30/2023 12:51:20 AM
 *  Author: omarn
 */ 

/********************************** Include Section ********************************/
#include "Utilities.h"
#include "MemoryMap.h"
#include "StdTypes.h"
#include "Interrupt_Interface.h"

/********************************** Global Variable ********************************/
static void (*ptr_INT0) (void) = NULL_PTR;
static void (*ptr_INT1) (void) = NULL_PTR;
static void (*ptr_INT2) (void) = NULL_PTR;

/******************************* Function Implementation ***************************/
void EXI_INIT(EX_INT_PIN_type INT)
{
	ENABLE_GI();
	switch(INT)
	{
		case INT0:
			EXI_CONTROL(INT0,ENABLE);
			break;
		
		case INT1:
			EXI_CONTROL(INT1,ENABLE);
			break;
		
		case INT2:
			EXI_CONTROL(INT2,ENABLE);
			break;
	}
}

void EXI_CONTROL(EX_INT_PIN_type INT , INT_Status_type status)
{
	switch (INT)
	{
		case INT0:
			switch (status)
			{
				case ENABLE:
					SET_BIT(GICR,INT0);
					break;
					
				case DISABLE:
					CLR_BIT(GICR,INT0);
					break;
			}
			break;
			
		case INT1:
			switch (status)
			{
				case ENABLE:
				SET_BIT(GICR,INT1);
				break;
			
				case DISABLE:
				CLR_BIT(GICR,INT1);
				break;
			}
			break;
		
		case INT2:
			switch (status)
			{
				case ENABLE:
				SET_BIT(GICR,INT2);
				break;
				
				case DISABLE:
				CLR_BIT(GICR,INT2);
				break;
			}
			break;
	}
}

void EXI_TRIG_EDGE(EX_INT_PIN_type INT , SENSE_INT_type sense)
{
	switch(INT)
	{
		case INT0:
		switch(sense)
		{
			case RISING_EDGE:
			SET_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
			
			case FALLING_EDGE:
			CLR_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
		}
		break;
		
		case INT1:
		switch(sense)
		{
			case RISING_EDGE:
			SET_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
			
			case FALLING_EDGE:
			CLR_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;

		}
		break;
		
		case INT2:
		switch(sense)
		{
			case RISING_EDGE:
			SET_BIT(MCUCSR,ISC2);
			break;
			
			case FALLING_EDGE:
			CLR_BIT(MCUCSR,ISC2);
			break;
		}
		break;
	}
}

void EXI_CALLBACK(EX_INT_PIN_type INT, void (*ptr) (void))
{
	switch (INT)
	{
		case INT0:
			ptr_INT0 = ptr;
		break;
		
		case INT1:
			ptr_INT1 = ptr;
		break;
		
		case INT2:
			ptr_INT2 = ptr;
		break;
	}
}

/***************************************** ISR **************************************/
ISR(INT0_vect)
{
	if(ptr_INT0 == NULL_PTR)
	{
		return;
	}
	ptr_INT0();
}

ISR(INT1_vect)
{
	if(ptr_INT1 == NULL_PTR)
	{
		return;
	}
	ptr_INT1();
}

ISR(INT2_vect)
{
	if(ptr_INT2 == NULL_PTR)
	{
		return;
	}
	ptr_INT2();
}