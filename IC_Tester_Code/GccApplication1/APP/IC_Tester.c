#include "IC_Tester.h"

#ifndef F_CPU
#define F_CPU ((u32)(11059200))
#endif
#include <util/delay.h>

#define TEST_DELAY 10
#define TRIES	3

static void init_ic_pins(const ICMetadata_t *ic);
static void pins_low(const ICMetadata_t *i);

static const c8 *err_message = "Unknown";

const ICMetadata_t ic_metadata[NUM_ICS] = {
	{
		.ic_name = "4081", .pin_count = 5,
		.pins =
		{
			{SOCKET_PIN1, OUTPUT},		{SOCKET_PIN2, OUTPUT},
			{SOCKET_PIN3, INPUT_FREE},	{SOCKET_PIN7, OUTPUT},		
			{SOCKET_PIN24, OUTPUT}
		},
		.truth_table =
		{
			// AND gate truth table
			// Pins: (A1, B1, Q1, Q2, B2, A2, VSS, A3, B3, Q3, Q4, B4, A4, VDD)
			{.pins_logic = {0, 0, 0, 0, 1}},
			{.pins_logic = {0, 1, 0, 0, 1}},
			{.pins_logic = {1, 0, 0, 0, 1}},
			{.pins_logic = {1, 1, 1, 0, 1}}
		},
		.truth_table_rows = 4
	},
	{
		.ic_name = "7486", .pin_count = 5,
		.pins = 
		{
			{SOCKET_PIN1,  OUTPUT},		{SOCKET_PIN2,  OUTPUT},
			{SOCKET_PIN3,  INPUT_FREE}, {SOCKET_PIN7,  OUTPUT},		
			{SOCKET_PIN24, OUTPUT}
		},
		.truth_table = 
		{
			// Exclusive OR Gate truth table
			// Pins: (1A, 1B, 1Y, 2A, 2B, 2Y, GND, 3Y, 3A, 3B, 4Y, 4A, 4B, VCC)
			{.pins_logic = {0, 0, 0, 0, 1}},
			{.pins_logic = {1, 0, 1, 0, 1}},
			{.pins_logic = {0, 1, 1, 0, 1}},
			{.pins_logic = {1, 1, 0, 0, 1}}
		},
		.truth_table_rows = 4
	},
	{
		.ic_name = "74541", .pin_count = 6,
		.pins = 
		{
			{SOCKET_PIN1, OUTPUT},		{SOCKET_PIN7, OUTPUT},
			{SOCKET_PIN10, OUTPUT},		{SOCKET_PIN17, INPUT_FREE},
			{SOCKET_PIN23, OUTPUT},		{SOCKET_PIN24, OUTPUT},
		},
		.truth_table = 
		{
			// Buffer/Line Driver truth table
			// Pins: (OE1, A1, A2, A3, A4, A5, A6, A7, A8, GND, Y8, Y7, Y6, Y5, Y4, Y3, Y2, Y1, OE2, VCC)
			{.pins_logic = {0, 0, 0, 0, 0, 1}},
			{.pins_logic = {0, 1, 0, 1, 0, 1}}
		},
		.truth_table_rows = 2
	},
	{
		.ic_name = "744511", .pin_count = 16,
		.pins = 
		{
			{SOCKET_PIN1, OUTPUT},		{SOCKET_PIN2, OUTPUT},
			{SOCKET_PIN3, OUTPUT},		{SOCKET_PIN4, OUTPUT},
			{SOCKET_PIN5, OUTPUT},		{SOCKET_PIN6, OUTPUT},
			{SOCKET_PIN7, OUTPUT},		{SOCKET_PIN8, OUTPUT},
			{SOCKET_PIN17, INPUT_FREE},	{SOCKET_PIN18, INPUT_FREE},		
			{SOCKET_PIN19, INPUT_FREE},	{SOCKET_PIN20, INPUT_FREE},		
			{SOCKET_PIN21, INPUT_FREE},	{SOCKET_PIN22, INPUT_FREE},
			{SOCKET_PIN23, INPUT_FREE},	{SOCKET_PIN24, OUTPUT}
		},
		.truth_table = 
		{
			// BCD-to-7 Segment Decoder truth table
			// Pins: (B, C, LT, BL, LE, D, A, GND, e, d, c, b, a, g, f, VCC)
			{.pins_logic = {0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1}},
			{.pins_logic = {0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1}},
			{.pins_logic = {1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1}},
			{.pins_logic = {1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1}},
			{.pins_logic = {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1}},
			{.pins_logic = {0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1}},
			{.pins_logic = {1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1}},
			{.pins_logic = {1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1}},
			{.pins_logic = {0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1}},
			{.pins_logic = {0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1}}
		},
		.truth_table_rows = 10
	},
	{
		.ic_name = "74367", .pin_count = 5,
		.pins = 
		{
			{SOCKET_PIN1, OUTPUT},		{SOCKET_PIN8, OUTPUT},
			{SOCKET_PIN17, INPUT_FREE},	{SOCKET_PIN18, OUTPUT},
			{SOCKET_PIN24, OUTPUT}
		},
		.truth_table = 
		{
			// Buffer/Line Driver truth table
			// Pins: (G1, 1A, 1Y, 2A, 2Y, 3A, 3Y, GND, 4Y, 4A, 5Y, 5A, 6Y, 6A, G2, VCC)
			{.pins_logic = {0, 0, 0, 0, 1}},
			{.pins_logic = {0, 0, 1, 1, 1}}
		},
		. truth_table_rows = 2
	},
	{
		.ic_name = "4043", .pin_count = 6,
		.pins = 
		{
			{SOCKET_PIN2, INPUT_FREE},	{SOCKET_PIN3, OUTPUT},		
			{SOCKET_PIN4, OUTPUT},		{SOCKET_PIN5, OUTPUT},
			{SOCKET_PIN8, OUTPUT},		{SOCKET_PIN24, OUTPUT}
		},
		.truth_table =
		{
			// Quad SR Latches truth table
			// Pins: (Q4, Q1, R1, S1, E, S2, R2, VSS, Q2, Q3, R3, S3, NC, S4, R4, VDD)
			{.pins_logic = {1, 0, 1, 1, 0, 1}},
			{.pins_logic = {1, 0, 0, 1, 0, 1}},
			{.pins_logic = {0, 1, 0, 1, 0, 1}},
			{.pins_logic = {1, 1, 1, 1, 0, 1}}
		},
		.truth_table_rows = 4
	},
	{
		.ic_name = "74280", .pin_count = 14,
		.pins =
		{
			{SOCKET_PIN1, OUTPUT},		{SOCKET_PIN2, OUTPUT},
			{SOCKET_PIN3, OUTPUT},		{SOCKET_PIN4, OUTPUT},
			{SOCKET_PIN5, INPUT_FREE},  {SOCKET_PIN6, INPUT_FREE},
			{SOCKET_PIN7, OUTPUT},		{SOCKET_PIN18, OUTPUT},
			{SOCKET_PIN19, OUTPUT},		{SOCKET_PIN20, OUTPUT},
			{SOCKET_PIN21, OUTPUT},		{SOCKET_PIN22, OUTPUT},
			{SOCKET_PIN23, OUTPUT},		{SOCKET_PIN24, OUTPUT}
		},
		.truth_table =
		{
			// Parity Generator/Checker truth table
			// Pins: (D6, D7, NC, D8, P_EVEN, P_ODD, GND, D0, D1, D2, D3, D4, D5, VCC)
			{.pins_logic = {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
			{.pins_logic = {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1}},
			{.pins_logic = {0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1}},
		},
		.truth_table_rows = 3
	},
	{
		.ic_name = "74196", .pin_count = 6,
		.pins =
		{
			{SOCKET_PIN1, OUTPUT},      {SOCKET_PIN4, OUTPUT},
			{SOCKET_PIN5, INPUT_FREE},	{SOCKET_PIN7, OUTPUT},
			{SOCKET_PIN23, OUTPUT},		{SOCKET_PIN24, OUTPUT}
		},
		.truth_table =
		{
			// Example truth table for SN74196N
			// Pins: (LOAD, QC, C, A, QA, CLK2, GND, CLK1, QB, B, D, QD, CLR, VCC)
			{.pins_logic = {0, 0, 0, 0, 1, 1}},
			{.pins_logic = {0, 1, 1, 0, 1, 1}},
			{.pins_logic = {1, 1, 1, 0, 1, 1}},
			{.pins_logic = {1, 0, 0, 0, 0, 1}}
		},
		.truth_table_rows = 3
	}
};

const c8 *test_ic(void) 
{
	u8 ic_counter, cases_counter, pin_counter, tries;
	DIO_PinVolt_type logic;
	u8 flag = 1;

	for (ic_counter = 0; ic_counter < NUM_ICS; ic_counter++) 
	{
		flag = 1;
		init_ic_pins(ic_metadata + ic_counter);
		_delay_ms(TEST_DELAY);
		for (cases_counter = 0; cases_counter < ic_metadata[ic_counter].truth_table_rows; cases_counter++) 
		{
			for (pin_counter = 0; pin_counter < ic_metadata[ic_counter].pin_count; pin_counter++) 
			{
				if (ic_metadata[ic_counter].pins[pin_counter].status == OUTPUT) 
				{
					DIO_WritePin(
					ic_metadata[ic_counter].pins[pin_counter].channel,
					READ_PIN(ic_metadata[ic_counter].truth_table[cases_counter].ic_logic, pin_counter)
					);
				}
			}
			_delay_ms(TEST_DELAY);
			for (pin_counter = 0; pin_counter < ic_metadata[ic_counter].pin_count; pin_counter++) 
			{
				if (ic_metadata[ic_counter].pins[pin_counter].status == INPUT_FREE) 
				{
					tries=0;
					while(tries <= TRIES)
					{
						tries++;
						logic = DIO_ReadPin(ic_metadata[ic_counter].pins[pin_counter].channel);
						if (READ_PIN(ic_metadata[ic_counter].truth_table[cases_counter].ic_logic, pin_counter) != logic)
						{
							flag=0;
						}
						else
						{
							flag=1;
							break;
						}
					}
				}
			}
			if (flag == 0) 
			{
				break;
			}
		}
		pins_low(ic_metadata + ic_counter);
		if (flag) 
		{
			return ic_metadata[ic_counter].ic_name;
		}
	}
	return err_message;
}

static void init_ic_pins(const ICMetadata_t *ic) 
{
	u8 counter;
	for (counter = 0; counter < ic->pin_count; counter++) 
	{
		DIO_InitPin(ic->pins[counter].channel, ic->pins[counter].status);
		if (ic->pins[counter].status == OUTPUT)
		{
			DIO_WritePin(ic->pins[counter].channel, LOW);
		}
	}
}

static void pins_low(const ICMetadata_t *ic)
{
	u8 counter;
	for (counter = 0; counter < ic->pin_count; counter++)
	{
		if (ic->pins[counter].status == OUTPUT)
		{
			DIO_WritePin(ic->pins[counter].channel, LOW);
		}
	}
}
