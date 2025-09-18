/*
 * main.h
 *
 * Created: 12/1/2024 8:21:44 PM
 *  Author: Blu-Ray
 */ 


#ifndef MAIN_H_
#define MAIN_H_


#include "MemoryMap.h"
#include "StdTypes.h"
#include "Utilities.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "IC_Tester.h"

#define F_CPU ((u32)(11059200))
#include <util/delay.h>

#define PUSH_BUTTON PIND6


#endif /* MAIN_H_ */