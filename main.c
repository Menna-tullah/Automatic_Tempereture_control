/*
 * main.c
 *
 *  Created on: Apr 16, 2020
 *      Author: menna
 */

#include"micro_config.h"
#include"std_types.h"
#include"common_macros.h"
#include"LCD.h"
#include"ADC.h"
#include"keypad.h"

#define FAN PD0
#define HEATER PD1

/* function prototyoes*/
uint32 get_desired_temp(void);
void turn_device(void);

uint32 room_temp = 0;
uint32 desired_temp = 0;
uint32 temp = 0;
int main(void)
{
	LCD_init();
	ADC_init();
	LCD_clearScreen();
	LCD_displayString("Room Temp:");
	LCD_displayStringRowColumn(1,0 , "desired temp:");

	DDRD |= (1<<FAN)|(1<<HEATER); /* set heater and fan pins as output */


	while(1)
	{
		/* display the room temp */
		LCD_goToRowColumn(0,11);
		room_temp = ADC_readChannel(1);
		room_temp = (ADC_readChannel(1)*150*5)/(1023*1.5);
		LCD_integerToString(room_temp);


		/* Enter the desired temp then enter using '*' */

		if(keypad_getPressedKey() == '#') /* start enter the desired temp */
		{
			LCD_integerToString(get_desired_temp());
		}
		/* test whether it is needed to turn on the heater or fan */
			if(keypad_getPressedKey() == '*')
			{
				turn_device();
			}


	}
}

uint32 get_desired_temp()
{
	uint8 i;
	temp = 0;
	desired_temp = 0;
	_delay_ms(500);
	for(i = 0; i < 2; i++)
	{
		LCD_goToRowColumn(1,13+i);
		temp = keypad_getPressedKey();
		desired_temp = desired_temp*10+temp;
		_delay_ms(150);
	}
	LCD_goToRowColumn(1,13);
	return desired_temp;
}
void turn_device()
{
	if (desired_temp > room_temp)
	{
		PORTD &= ~(1 << FAN); /* Fan is off */
		PORTD |= (1 << HEATER); /* heater is on */
	}
	else if (desired_temp < room_temp)
	{
		PORTD &= ~(1 << HEATER); /* heater off*/
		PORTD |= (1 << FAN); /* fan ON */

	}
	else if (desired_temp == room_temp)
	{
		PORTD &= ~(1 << HEATER); /* Heater is off */
		PORTD &= ~(1 << FAN); /* fan is off */
	}
}
