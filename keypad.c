/*
 * keypad.c
 *
 *  Created on: Apr 16, 2020
 *      Author: menna
 */

#include"keypad.h"

/* function prototype */
static uint8 keypad_4x3_adjusKey(uint8 key_num);

uint8 keypad_getPressedKey(void)
{
	uint8 col, row;
	while(1)
	{
		for(col = 0; col < num_col; col++)
		{
			KEYPAD_PORT_DIR = (0b00010000<<col); /* only one of col pins is output and the rest is input*/
			KEYPAD_PORT_OUT = (~(0b00010000<<col)); /* activate the pull up resistors for row pins */

			for(row = 0; row < num_row; row++)
			{
				if(BIT_IS_CLEAR(KEYPAD_PORT_IN, row))
				{
					return keypad_4x3_adjusKey((row*num_col)+col+1);
				}
			}
		}
	}
}

static uint8 keypad_4x3_adjusKey(uint8 key_num)
{
	switch(key_num)
	{
	case 10: return '*';
			break;
	case 11: return 0;
			break;
	case 12: return '#';
			break;
	default: return key_num;
	}
}
