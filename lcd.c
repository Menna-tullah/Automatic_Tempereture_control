/*
 * lcd.c
 *
 *  Created on: Apr 16, 2020
 *      Author: menna
 */
#include"LCD.h"

void LCD_init(void)
{
	LCD_DATA_PORT_DIR = 0xFF; /* set the pins as output for the LCD data */
	LCD_CTRL_PORT_DIR |= (1<<E) | (1<<RW) | (1<<RS);

	LCD_sendCommand(TWO_LINE_EIGHT_BIT_MODE);
	LCD_sendCommand(CLEAR_CMD);
	LCD_sendCommand(CURSOR_ON);
}

void LCD_sendCommand(uint8 command)
{
	CLEAR_BIT(LCD_CTRL_PORT,RS); /* instruction mode */
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
	LCD_DATA_PORT = command;
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
}

void LCD_displayChar(uint8 ch)
{
	SET_BIT(LCD_CTRL_PORT,RS); /* data mode */
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
	LCD_DATA_PORT = ch;
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
}

void LCD_displayString(const char* str)
{
	while((*str) != '\0')
	{
		LCD_displayChar(*str);
		str++;
	}
}

void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_CMD);
}

/* to go to the required location on LCD */
void LCD_goToRowColumn(uint8 row,uint8 col)
{
	uint8 address;

	/* first of all calculate the required address */
	switch(row)
	{
		case 0:
				address=col;
				break;
		case 1:
				address=col+0x40;
				break;
		case 2:
				address=col+0x10;
				break;
		case 3:
				address=col+0x50;
				break;
	}
	/* to write to a specific address in the LCD
	 * we need to apply the corresponding command(0x80) --> 0b10000000+Address */
	LCD_sendCommand(address | SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *st)
{
	LCD_goToRowColumn(row,col);
	LCD_displayString(st);
}

void LCD_integerToString(uint8 num)
{
	 char buff[16]; /* String to hold the ASCII result */
	 itoa(num,buff,10); /* 10 for decimal */
     LCD_displayString(buff);
}
