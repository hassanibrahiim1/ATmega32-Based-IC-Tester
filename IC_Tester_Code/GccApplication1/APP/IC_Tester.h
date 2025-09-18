/*
 * IC_Tester.h
 *
 * Created: 12/1/2024 8:45:18 PM
 *  Author: Blu-Ray
 */ 

#ifndef IC_TESTER_H_
#define IC_TESTER_H_

/*************************** include section ***************************/
#include "DIO_Interface.h"
#include "Utilities.h"
#include "StdTypes.h"

/*************************** Macro section ***************************/
#define SOCKET_PIN1  PINA0
#define SOCKET_PIN2  PINA1
#define SOCKET_PIN3  PINA2
#define SOCKET_PIN4  PINA3
#define SOCKET_PIN5  PINA4
#define SOCKET_PIN6  PINA5
#define SOCKET_PIN7  PINA6
#define SOCKET_PIN8  PINA7
#define SOCKET_PIN9  PINB0
#define SOCKET_PIN10 PINB1
// #define SOCKET_PIN11 PINB2
// #define SOCKET_PIN12 PINB3
// #define SOCKET_PIN13 PINB4
// #define SOCKET_PIN14 PINB5
#define SOCKET_PIN15 PINB6
#define SOCKET_PIN16 PINB7
#define SOCKET_PIN17 PINC7
#define SOCKET_PIN18 PINC6
#define SOCKET_PIN19 PINC5
#define SOCKET_PIN20 PINC4
#define SOCKET_PIN21 PINC3
#define SOCKET_PIN22 PINC2
#define SOCKET_PIN23 PINC1
#define SOCKET_PIN24 PINC0

#define NUM_ICS			8
#define MAX_PINS		20
#define MAX_TRUTH_TABLE 10

/*************************** Definition section ***************************/
typedef struct {
    DIO_Pin_type channel;
    DIO_PinStatues_type status;
} pinChannel_t;

typedef union {
    struct {
        u8 pin1: 1;
        u8 pin2: 1;
        u8 pin3: 1;
        u8 pin4: 1;
        u8 pin5: 1;
        u8 pin6: 1;
        u8 pin7: 1;
        u8 pin8: 1;
        u8 pin9: 1;
        u8 pin10: 1;
//         u8 pin11: 1;
//         u8 pin12: 1;
//         u8 pin13: 1;
//         u8 pin14: 1;
        u8 pin15: 1;
        u8 pin16: 1;
        u8 pin17: 1;
        u8 pin18: 1;
        u8 pin19: 1;
        u8 pin20: 1;
		u8 pin21: 1;
		u8 pin22: 1;
		u8 pin23: 1;
		u8 pin24: 1;
    } pins_logic;
    u32 ic_logic;
} testCase_t;

typedef struct {
    c8 *ic_name;
    u8 pin_count;
    pinChannel_t pins[MAX_PINS];
    testCase_t truth_table[MAX_TRUTH_TABLE];
    u8 truth_table_rows; 
} ICMetadata_t;
/*************************** Declaration section ***************************/
extern const ICMetadata_t ic_metadata[NUM_ICS];
const const c8 *test_ic(void);

#endif /* IC_TESTER_H_ */
