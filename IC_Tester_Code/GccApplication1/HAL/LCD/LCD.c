/********************************** include section *****************************/
#include "LCD_cfg.h"
#include "LCD_Interface.h"
#include "Utilities.h"
#include <string.h>
#ifndef F_CPU  // delay include with guard
#define F_CPU ((u32)(11059200))
#include <util/delay.h>
#endif


/********************************* Function Implementation ************************************/

#if MODE == 1
/***************** 8_bit *******************/
static void write_instruction(u8 ins)
{
	DIO_WritePin(LCD_RS,LOW);
	DIO_WritePort(LCD_DATA,ins);
	DIO_WritePin(LCD_EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(LCD_EN,LOW);
	_delay_ms(1);	
}

static void write_data(u8 data)
{
	DIO_WritePin(LCD_RS,HIGH);
	DIO_WritePort(LCD_DATA,data);
	DIO_WritePin(LCD_EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(LCD_EN,LOW);
	_delay_ms(1);
}

void LCD_INIT(void)
{
	_delay_ms(50);
	write_instruction(FUNC_SET_VALUE);
	write_instruction(DIS_ON_OFF_VALUE);
	write_instruction(DIS_CLR_VALUE);
	_delay_ms(1);
	write_instruction(ENTRY_MODE_VALUE);
}

#elif MODE == 0
/***************** 4_bit *******************/
static void write_instruction(u8 ins)
{
	DIO_WritePin(LCD_RS,LOW);
	DIO_WritePin(LCD_D7,READ_PIN(ins,7));
	DIO_WritePin(LCD_D6,READ_PIN(ins,6));
	DIO_WritePin(LCD_D5,READ_PIN(ins,5));
	DIO_WritePin(LCD_D4,READ_PIN(ins,4));
	DIO_WritePin(LCD_EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(LCD_EN,LOW);
	_delay_ms(1);
	
	DIO_WritePin(LCD_D7,READ_PIN(ins,3));
	DIO_WritePin(LCD_D6,READ_PIN(ins,2));
	DIO_WritePin(LCD_D5,READ_PIN(ins,1));
	DIO_WritePin(LCD_D4,READ_PIN(ins,0));
	DIO_WritePin(LCD_EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(LCD_EN,LOW);
	_delay_ms(1);
}

static void write_data(u8 data)
{
	DIO_WritePin(LCD_RS,HIGH);
	DIO_WritePin(LCD_D7,READ_PIN(data,7));
	DIO_WritePin(LCD_D6,READ_PIN(data,6));
	DIO_WritePin(LCD_D5,READ_PIN(data,5));
	DIO_WritePin(LCD_D4,READ_PIN(data,4));
	DIO_WritePin(LCD_EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(LCD_EN,LOW);
	_delay_ms(1);
	
	DIO_WritePin(LCD_D7,READ_PIN(data,3));
	DIO_WritePin(LCD_D6,READ_PIN(data,2));
	DIO_WritePin(LCD_D5,READ_PIN(data,1));
	DIO_WritePin(LCD_D4,READ_PIN(data,0));
	DIO_WritePin(LCD_EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(LCD_EN,LOW);
	_delay_ms(1);
}

void LCD_INIT(void)
{
	_delay_ms(50);
	write_instruction(0x02);
	write_instruction(FUNC_SET_VALUE);
	write_instruction(DIS_ON_OFF_VALUE);
	write_instruction(DIS_CLR_VALUE);
	_delay_ms(1);
	write_instruction(ENTRY_MODE_VALUE);
}

#endif


void LCD_CLR(void)
{
	write_instruction(DIS_CLR_VALUE);
	_delay_ms(1);
}

void LCD_WRITE_CHAR(u8 character)
{
	write_data(character);
}

void LCD_WRITE_NUM(s32 num)
{
	u8 str[11],i=0;
	if(num == 0)
	{
		write_data('0');
	}
	if(num < 0)
	{
		write_data('-');
		num *= -1;
	}
	while(num)
	{
		str[i] = (num%10) + '0';
		num/=10;
		i++;
	}
	for (s8 j = i-1 ; j>=0 ; j--)
	{
		write_data(str[j]);
	}
	
}

void LCD_WRITE_BINARY(u32 num)
{
	u8 flag = 0;
	
	for (s8 i =31 ; i>=0 ; i--)
	{
		if(num & (1<<i))
		{
			write_data('1');
			flag=1;
		}
		else if(flag == 1)
		{
			write_data('0');
		}
	}
	
	
}

void LCD_WRITE_HEX(u32 num)
{
	u8 temp=0,jump = 4*7,flag=0;
	for (s8 i = 7 ; i>=0 ;i--)
	{
		temp = (num>>jump) & 15;
		if(temp > 9)
		{
			temp = (temp -10) + 'A';
			write_data(temp);
			flag=1;

		}
		else if (temp > 0)
		{
			temp = temp + '0';
			write_data(temp);
			flag=1;
		}
		else if(flag ==1)
		{
			write_data('0');
		}
		jump-=4; 
		
	}
}

void LCD_WRITE_STRING(const c8 *string)
{
	for(u8 i = 0 ; string[i] ; ++i)
	{
		write_data(string[i]);
	}
}

void LCD_SET_CURSOR(u8 line , u8 cell)
{
	if((line-1) == 0)
	{
		write_instruction(0x80 | (cell-1));
	}
	if((line-1) == 1)
	{
		write_instruction(0x80 | 0x40 | (cell-1));
	}
}

void LCD_REMOVE_CHAR(void)
{
	write_instruction(CURSOR_LEFT);
	write_data(' ');
	write_instruction(CURSOR_LEFT);
}

void LCD_DRAW(u8 los  ,u8* img)
{
	write_instruction(0x40 + (los*8));
	for (u8 i = 0; i <8 ;++i)
	{
		write_data(img[i]);
	}
	LCD_SET_CURSOR(1,1);
}

void LCD_MOVING_STRING(c8* string)
{
	u8 len = strlen(string);
	u8 line = 1 ,count =1;
	u8 stop=0;
	for(s8 i = 1 ; stop!=2  ; i++)
	{
		count =1;
		if(i > ((16-len)+1) )
		{
			if(line == 1)
			{
				for (s8 j = len-(i-((16-len)+1) ) ; j<len ; j++)
				{
					LCD_SET_CURSOR(2,count);
					LCD_WRITE_CHAR(string[j]);
					LCD_SET_CURSOR(line,i);
					count++;
				}
				
			}
			if(line == 2)
			{
				for (s8 j = len-(i-((16-len)+1) ) ; j<len ; j++)
				{
					LCD_SET_CURSOR(1,count);
					LCD_WRITE_CHAR(string[j]);
					LCD_SET_CURSOR(line,i);
					count++;
				}
				
			}
			

		}
		LCD_SET_CURSOR(line,i);
		LCD_WRITE_STRING(string);
		_delay_ms(500);
		LCD_CLR();
		if(i==16)
		{
			i=0;
			line = line==1? 2:1;
			stop++;
		}
		
	}
	
}




