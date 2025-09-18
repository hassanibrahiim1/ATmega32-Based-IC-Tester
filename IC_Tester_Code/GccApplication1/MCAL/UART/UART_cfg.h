/*
 * UART_cfg.h
 *
 * Created: 2/18/2024 12:53:16 AM
 *  Author: Omar Yasser
 */ 


#ifndef UART_CFG_H_
#define UART_CFG_H_


typedef struct 
{
	Baud_Rate_type    baud_rate ;
	Double_Speed_type speed     ;
	Parity_Mode_type  parity     ;
	Stop_Mode_type    stop      ;
	Data_Size_type    data_size ;
	
}UART_Configration;


// Normal Speed 0
// Double Speed 1
#define NORMAL_SPEED 0
#define DOUBLE_SPEED 1

#define SPEED NORMAL_SPEED

// Disable 0
// Even	   1
// Odd	   2
#define DISABLE_PARITY 0
#define EVEN_PARITY    2
#define ODD_Parity	   3

#define PARITY DISABLE_PARITY

// 1 bit 0
// 2 bit 1
#define _1_bit 0
#define _2_bit 1

#define STOP _1_bit 
 

#endif /* UART_CFG_H_ */