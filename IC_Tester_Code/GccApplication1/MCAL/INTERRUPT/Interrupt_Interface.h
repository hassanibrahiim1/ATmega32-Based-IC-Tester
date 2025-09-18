/*
 * Interrupt_Interface.h
 *
 * Created: 12/30/2023 12:51:40 AM
 *  Author: omarn
 */ 


#ifndef INTERRUPT_INTERFACE_H_
#define INTERRUPT_INTERFACE_H_

/******************************** External Interrupt Sense pins ****************************/
#define ISC00   0
#define ISC01   1
#define ISC10   2
#define ISC11   3
#define ISC2    6

/************************************** Global Interrupt ************************************/
#define CLOSE_GI()		  __asm__("cli"::)
#define ENABLE_GI()       __asm__("sei"::)

/*************************************** Typedef Section *************************************/
typedef enum
{
	INT0=6,
	INT1=7,
	INT2=5
	
}EX_INT_PIN_type;

typedef enum
{
	RISING_EDGE  =0,
	FALLING_EDGE =1
		
}SENSE_INT_type;

typedef enum 
{
	ENABLE,
	DISABLE
	
}INT_Status_type;

/************************************** Function declaration *********************************/

void EXI_INIT(EX_INT_PIN_type INT);

void EXI_CONTROL(EX_INT_PIN_type INT , INT_Status_type status);

void EXI_TRIG_EDGE(EX_INT_PIN_type INT , SENSE_INT_type sense);

void EXI_CALLBACK(EX_INT_PIN_type INT, void (*ptr) (void));






#endif /* INTERRUPT_INTERFACE_H_ */