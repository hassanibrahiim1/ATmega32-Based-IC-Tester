/*
 * UART_Cfg.c
 *
 * Created: 7/21/2024 1:46:22 AM
 *  Author: Omar Yasser
 */ 

#include "UART_Interface.h"
#include "UART_cfg.h"

UART_Configration config = {
	.baud_rate = Baud_rate_19_2k,
	.speed     = Double_Speed_Disable,
    .parity    = Disable_Parity,
	.stop      = MODE_1_BIT,
	.data_size = _8_bit
};
