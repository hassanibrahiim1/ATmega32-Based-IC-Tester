/*
 * GccApplication1.c
 *
 * Created: 11/4/2024 6:11:43 PM
 * Author : Blu-Ray
 */ 

#include "main.h"

const c8 *s;
u8 bt_flag;

int main(void)
{
    /* Replace with your application code */
	DIO_INIT();
	LCD_INIT();

	LCD_WRITE_STRING("IC-Tester Ready!");
	_delay_ms(1500);
	LCD_CLR();
	LCD_WRITE_STRING(" Press to Test");
	LCD_SET_CURSOR(2, 1);
	LCD_WRITE_STRING("  IC   _____");
	while (1)
	{
		
		if (DIO_ReadPin(PUSH_BUTTON) == LOW)
		{
			bt_flag = 1;
			while (DIO_ReadPin(PUSH_BUTTON) == LOW);
		}
		
		
		if (bt_flag)
		{
			LCD_SET_CURSOR(2, 8);
			LCD_WRITE_STRING("           ");
			LCD_SET_CURSOR(2, 8);
			s = test_ic();
			LCD_WRITE_STRING(s);
			bt_flag = 0;
		}
    }
	
	return 0; 
}
