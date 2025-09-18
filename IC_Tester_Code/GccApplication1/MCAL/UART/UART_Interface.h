// /*
//  * UART_Interface.h
//  *
//  * Created: 2/15/2024 11:33:55 PM
//  *  Author: Omar Yasser



#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

/******************************** Include Section ***********************************/
#include "StdTypes.h"


/******************************** Macros Section ************************************/

// USART Control and Status Register A (UCSRA)
#define RXC   7
#define TXC   6
#define UDRE  5
#define FE    4
#define DOR   3
#define PE    2
#define U2X   1
#define MPCM  0

// USART Control and Status Register B (UCSRB)
#define RXCIE  7
#define TXCIE  6
#define UDRIE  5
#define RXEN   4
#define TXEN   3
#define UCSZ2  2
#define RXB8   1
#define TXB8   0

// USART Control and Status Register C (UCSRC)
#define URSEL  7
#define UMSEL  6
#define UPM1   5
#define UPM0   4
#define USBS   3
#define UCSZ1  2
#define UCSZ0  1
#define UCPOL  0

// No data
#define NO_DATA '>'


/******************************** Typedef Section ***********************************/
typedef enum
{
	Baud_rate_2400  = 0,
	Baud_rate_4800  = 1,
	Baud_rate_9600  = 2,
	Baud_rate_14_4k = 3,
	Baud_rate_19_2k = 4,
	Baud_rate_28_8k = 5,
	Baud_rate_38_4k = 6,
}Baud_Rate_type;

typedef enum
{
	Double_Speed_Disable = 0,
	Double_Speed_Enable  = 1
}Double_Speed_type;

typedef enum
{
	Disable_Parity = 0,
	EVEN_Parity    = 2,
	ODD_Parity     = 3
}Parity_Mode_type;

typedef enum
{
	MODE_1_BIT = 0,
	MODE_2_BIT = 1,
}Stop_Mode_type;

typedef enum
{
	_5_bit = 0,
	_6_bit = 1,
	_7_bit = 2,
	_8_bit = 3,
	_9_bit = 7
}Data_Size_type;

typedef enum
{
	NOT_RECEIVE = 0,
	RECEIVED    = 1
}UART_Ret_type;

/***************************** Function Declaration *********************************/

// Inputs:
//		   This function take void 
//
// Output:
//		   This function return void
void UART_INIT(void);

// Inputs:
//		   Data   : the desired transmitted data
//
// Output:
//		   This function return void
// Description:
//			    This function send the data through TX pin using UART protocol
void UART_SEND_DATA(u8 data);
void UART_SEND_STRING(c8 *data);


// Inputs:
//		   This function enter void
//
// Output:
//		   This function return the received data
// Description:
//			    This function receive the data through RX pin using UART protocol
u8 UART_RECEIVE_DATA_BW(void);                  // Using Busy Wait method
UART_Ret_type UART_RECEIVE_DATA_PC(u8 *data);  // Using Periodic check method
u8 UART_RECEIVE_DATA(void);				  // Using Interrupt


void UART_TX_ENABLE(void);
void UART_TX_DISABLE(void);
void UART_RX_ENABLE(void);
void UART_RX_DISABLE(void);


// This functions to control the interrupt
void UART_RXCI_ENABLE(void); // Receive complete Interrupt
void UART_RXCI_DISABLE(void);
void UART_TXCI_ENABLE(void); // Transmit complete Interrupt
void UART_TXCI_DISABLE(void);
void UART_DEI_ENABLE(void);  // Data empty Interrupt
void UART_DEI_DISABLE(void);

// This functions used to set the call back function for ISR
void UART_RXC_CALL_BACK(void (*rxc)(void));
void UART_TXC_CALL_BACK(void (*txc)(void));
void UART_DE_CALL_BACK(void (*de)(void));



#endif /* UART_INTERFACE_H_ */




