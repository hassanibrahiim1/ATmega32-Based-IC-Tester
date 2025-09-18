/*
 * UART.c
 *
 * Created: 2/15/2024 11:34:17 PM
 *  Author: Omar Yasser
 */ 


/******************************** Include Section ***********************************/
#include <MemoryMap.h>
#include <Utilities.h>
#include <UART_Interface.h>
#include "StdTypes.h"
#include "UART_cfg.h"
#include "LCD_Interface.h"
#define F_CPU ((u32)(11059200))
#include <util/delay.h>

/********************************* Variable Section *********************************/
void (*RXC_VAR) (void) = NULL_PTR;
void (*TXC_VAR) (void) = NULL_PTR;
void (*DE_VAR)  (void) = NULL_PTR;

volatile static u8 Data = 0;
volatile static u8 Flag_Data = 0;

extern UART_Configration config;


static const u16 baud_rate[2][7] =
{
	{207,103,51,34,25,16,12},
	
	{416,207,103,68,51,34,25},
	
};

/************************************************************************************/
static void RXC_FUNC(void)
{
	Flag_Data = 1;
	Data = UDR;
}

/***************************** Function Implementation ******************************/

void UART_INIT(void)
{
	// Enable the TX and RX
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);

	// Select the UCSRC register	
	SET_BIT(UCSRC,URSEL);
	
	// Set the data size
	switch(config.data_size)
	{
		case _5_bit:
			CLR_BIT(UCSRC,UCSZ0);
			CLR_BIT(UCSRC,UCSZ1);
			CLR_BIT(UCSRB,UCSZ2);
			break;
		
		case _6_bit:
			SET_BIT(UCSRC,UCSZ0);
			CLR_BIT(UCSRC,UCSZ1);
			CLR_BIT(UCSRB,UCSZ2);
			break;
		
		case _7_bit:
			CLR_BIT(UCSRC,UCSZ0);
			SET_BIT(UCSRC,UCSZ1);
			CLR_BIT(UCSRB,UCSZ2);
			break;
		
		case _8_bit:
			SET_BIT(UCSRC,UCSZ0);
			SET_BIT(UCSRC,UCSZ1);
			CLR_BIT(UCSRB,UCSZ2);
			break;
		
		case _9_bit:
			SET_BIT(UCSRC,UCSZ0);
			SET_BIT(UCSRC,UCSZ1);
			SET_BIT(UCSRB,UCSZ2);
			break;
		
		default:
			break;
		
	}
	
	// Set the parity mode
	switch(config.parity)
	{
		case Disable_Parity:
			CLR_BIT(UCSRC,UPM0);
			CLR_BIT(UCSRC,UPM1);
			break;
			
		case EVEN_PARITY:
			CLR_BIT(UCSRC,UPM0);
			SET_BIT(UCSRC,UPM1);
			break;
					
		case ODD_Parity:
			SET_BIT(UCSRC,UPM0);
			SET_BIT(UCSRC,UPM1);
			break;
			
		default:
			break;
	}
	
	// Set the stop bit
	if(config.stop)
	{
		SET_BIT(UCSRC,USBS);
	}
	else
	{
		CLR_BIT(UCSRC,USBS);
	}
	
	// Set the speed
	if (config.speed)
	{
		SET_BIT(UCSRA,U2X);
	}
	else
	{
		CLR_BIT(UCSRA,U2X);
	}
	
	// Set the baud rate
	SET_BIT(UBRRH,URSEL);
	u16 UBRR = baud_rate[config.speed][config.baud_rate];
	UBRRL = (u8) UBRR;
	UBRRH = (u8)((u16)UBRR>>8 & (0<<URSEL));
	
	
	//------------------------------------- Set RX Call Back -------------------------------------------//
	UART_RXC_CALL_BACK(RXC_FUNC);
	//--------------------------------------------------------------------------------------------------//

}


//----------------------- Transmit Data Function -----------------------//
void UART_SEND_DATA(u8 data)
{
	while(!READ_PIN(UCSRA,UDRE));
	UDR = data;
}

void UART_SEND_STRING(c8 *data)
{
	for (int i = 0 ; data[i]!= 0 ; i++)
	{
		while(!READ_PIN(UCSRA,UDRE));
		UDR = data[i];
	}
	
}

//----------------------- Receive Data Function -----------------------//
u8 UART_RECEIVE_DATA_BW(void)
{
	while(!READ_PIN(UCSRA,RXC));
	return UDR;
	
}  
               
UART_Ret_type UART_RECEIVE_DATA_PC(u8 *data)
{
	if(READ_PIN(UCSRA,RXC))
	{
		return NOT_RECEIVE;
	}
	
	*data  = UDR;
	return RECEIVED;
}  

u8 UART_RECEIVE_DATA(void)
{
	if(Flag_Data == 1)
	{
		Flag_Data = 0;
		return Data;
	}
	return NO_DATA;
}


//-----------------------  TX & RX Control -----------------------//
void UART_TX_ENABLE(void)
{
	SET_BIT(UCSRB,TXEN);
}

void UART_TX_DISABLE(void)
{
	CLR_BIT(UCSRB,TXEN);
}

void UART_RX_ENABLE(void)
{
	SET_BIT(UCSRB,RXEN);
}

void UART_RX_DISABLE(void)
{
	CLR_BIT(UCSRB,RXEN);
}


//-----------------------  Interrupt Control -----------------------//
void UART_RXCI_ENABLE(void)
{
	SET_BIT(UCSRB,RXCIE);
}

void UART_RXCI_DISABLE(void)
{
	CLR_BIT(UCSRB,RXCIE);
}

void UART_TXCI_ENABLE(void)
{
	SET_BIT(UCSRB,TXCIE);
} 

void UART_TXCI_DISABLE(void)
{
	CLR_BIT(UCSRB,TXCIE);
}

void UART_DEI_ENABLE(void)
{
	SET_BIT(UCSRB,UDRIE);
} 

void UART_DEI_DISABLE(void)
{
	CLR_BIT(UCSRB,UDRIE);
}

//-------------------------  Set Call Back  ------------------------//
void UART_RXC_CALL_BACK(void (*rxc)(void))
{
	if(rxc == NULL_PTR)
	{
		return;
	}
	RXC_VAR = rxc;
	
}

void UART_TXC_CALL_BACK(void (*txc)(void))
{
	if(txc == NULL_PTR)
	{
		return;
	}
	TXC_VAR = txc;
}

void UART_DE_CALL_BACK(void (*de)(void))
{
	if(de == NULL_PTR)
	{
		return;
	}
	DE_VAR = de;
}

//---------------------------------------------------- ISR Function ----------------------------------------------------------//

ISR(USART_RXC_vect)
{
	if(RXC_VAR == NULL_PTR)
	{
		return;
	}
	RXC_VAR();
}

ISR(USART_TXC_vect)
{
	if(TXC_VAR == NULL_PTR)
	{
		return;
	}
	TXC_VAR();
}

ISR(USART_UDRE_vect)
{
	if(DE_VAR == NULL_PTR)
	{
		return;
	}
	DE_VAR();
}



