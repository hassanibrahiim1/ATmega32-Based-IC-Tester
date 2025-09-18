/*
 * MemoryMap.h
 *
 * Created: 12/5/2023 9:32:04 PM
 *  Author: Omar Yasser
 */ 


#ifndef MEMORYMAP_H_
#define MEMORYMAP_H_

/*********************************** DIO Register ************************************/
// address of PORTA
#define DDRC (*((volatile unsigned char*) 0x34) )
#define PORTC (*((volatile unsigned char*) 0x35) )
#define PINC (*((volatile unsigned char*)0X33))

// address of PORTA
#define DDRB (*((volatile unsigned char*) 0x37) )
#define PORTB (*((volatile unsigned char*) 0x38) )
#define PINB (*((volatile unsigned char*)0X36))

// address of PORTA
#define DDRA (*((volatile unsigned char*) 0x3A) )
#define PORTA (*((volatile unsigned char*) 0x3B) )
#define PINA (*((volatile unsigned char*)0X39))

// address of PORTD
#define DDRD (*((volatile unsigned char*) 0x31) )
#define PORTD (*((volatile unsigned char*) 0x32) )
#define PIND (*((volatile unsigned char*)0X30))

/*********************************** ADC Register **********************************/

// ADMUX Register
#define ADMUX  (*((volatile unsigned char*)0X27))

// ADCSRA Register
#define ADCSRA (*((volatile unsigned char*)0X26))

// ADDATA Register
#define ADCH   (*((volatile unsigned char*)0X25))
#define ADCL   (*((volatile unsigned char*)0X24))


/***************************** External Interrupt Register ***************************/

#define MCUCSR (*((volatile unsigned char*)0X54))
#define MCUCR  (*((volatile unsigned char*)0X55))
#define GICR   (*((volatile unsigned char*)0X5B))



/********************************** ISR defination *********************************/

// Interrupt services routine function
#define ISR(vector) void vector (void)__attribute__((signal));\
					void vector (void)
					
// vector table

/* External Interrupt */ 
#define INT0_vect			__vector_1
#define INT1_vect			__vector_2
#define INT2_vect			__vector_3

/* Timer/counter2 compare match */
#define TIMER2_COMP_vect	__vector_4

/* Timer/counter2 overflow */
#define TIMER2_OVF_vect		__vector_5

/* Timer/Counter1 Capture Event */
#define TIMER1_CAPT_vect	__vector_6

/* Timer/Counter1 Compare Match A */
#define TIMER1_COMPA_vect   __vector_7

/* Timer/Counter1 Compare Match B */
#define TIMER1_COMPB_vect   __vector_8

/* Timer/counter1 overflow */
#define TIMER1_OVF_vect		__vector_9

/* Timer/counter0 compare match */
#define TIMER0_COMP_vect	__vector_10

/* Timer/counter0 overflow */
#define TIMER0_OVF_vect		__vector_11

/* Serial transfer complete */
#define SPI_STC_vect		__vector_12

/* USART Rx Complete */
#define USART_RXC_vect		__vector_13

/* USART Data Register Empty */
#define USART_UDRE_vect		__vector_14

/* USART Tx Complete */
#define USART_TXC_vect		__vector_15

/* ADC Conversion Complete */
#define ADC_vect			__vector_16


/************************************ NVM Register ***********************************/

/* Address Register */
#define EEAR (*((volatile unsigned short*)0X3E))

/* Data Register */
#define EEDR (*((volatile unsigned char*)0X3D))

/* Control Register */
#define EECR (*((volatile unsigned char*)0X3C))

/*********************************** Timer resgister **********************************/

//------------------------------------- Timer0 -------------------------------------// 
/* Timer0 Control Register */
#define TCCR0 (*((volatile unsigned char*)0X53))

/* Timer0 Counter Register */
#define TCNT0 (*((volatile unsigned char*)0X52))

/* Timer0 OCR0  */
#define OCR0  (*((volatile unsigned char*)0X5C))

//------------------------------------- Timer2 -------------------------------------//
/* Timer2 Control Register */
#define TCCR2 (*((volatile unsigned char*)0X45))

/* Timer2 Counter Register */
#define TCNT2 (*((volatile unsigned char*)0X44))

/* Timer2 OCR2  */
#define OCR2  (*((volatile unsigned char*)0X43))

//------------------------------------- Timer1 -------------------------------------//
/* Timer1 Control Register */ 
#define TCCR1B (*((volatile unsigned char*)0X4E))
#define TCCR1A (*((volatile unsigned char*)0X4F))

/* Timer1 Counter Register */
#define TCNT1  (*((volatile unsigned short*)0X4C))

/* Timer1 OCR1  */
#define OCR1A  (*((volatile unsigned short*)0X4A))
#define OCR1B  (*((volatile unsigned short*)0X48))

/* Timer1 Input Capture Unit  */
#define ICR1   (*((volatile unsigned short*)0X46))

//--------------------------------- Timer Interrupt ----------------------------------//
/* Timer Interrupt Enable  */
#define TIMSK (*((volatile unsigned char*)0X59))

/* Timer Interrupt Flag Register  */
#define TIFR (*((volatile unsigned char*)0X58))


/*********************************** UART resgister **********************************/

/* UART Data Register */
#define UDR   (*((volatile unsigned char *)0X2C))

/* USART Control and Status Register A */
#define UCSRA (*((volatile unsigned char *)0X2B))

/* USART Control and Status Register B */
#define UCSRB (*((volatile unsigned char *)0X2A))

/* USART Control and Status Register C */
#define UCSRC (*((volatile unsigned char *)0X40))

/* USART Baud Rate Register */
#define UBRRL (*((volatile unsigned char *)0X29))
#define UBRRH (*((volatile unsigned char *)0X40))

/*********************************** SPI resgister ************************************/

/* SPI Data Register */
#define SPDR (*((volatile char *)0X2F))

/* SPI Control Register */
#define SPCR (*((volatile char *)0X2D))

/* SPI Status Register */
#define SPSR (*((volatile char *)0X2E))

/*********************************** I2C resgister ************************************/
#define TWBR (*((volatile unsigned char*)0X20))
#define TWBR0 0
#define TWBR1 1
#define TWBR2 2
#define TWBR3 3
#define TWBR4 4
#define TWBR5 5
#define TWBR6 6
#define TWBR7 7


#define TWCR  (*((volatile unsigned char*)0X56))
#define TWIE  0
#define TWEN  2
#define TWWC  3
#define TWSTO 4
#define TWSTA 5
#define TWEA  6
#define TWINT 7

#define TWSR (*((volatile unsigned char*)0X21))
#define TWPS0 0
#define TWPS1 1
#define TWS3  3
#define TWS4  4
#define TWS5  5
#define TWS6  6
#define TWS7  7

#define TWDR (*((volatile unsigned char*)0X23))
#define TWD0 0
#define TWD1 1
#define TWD2 2
#define TWD3 3
#define TWD4 4
#define TWD5 5
#define TWD6 6
#define TWD7 7

#define TWAR (*((volatile unsigned char*)0X22))
#define TWGCE 0
#define TWA0  1
#define TWA1  2
#define TWA2  3
#define TWA3  4
#define TWA4  5
#define TWA5  6
#define TWA6  7
#endif /* MEMORYMAP_H_ */

