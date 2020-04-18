/*
 * adc.c
 *
 *  Created on: Apr 16, 2020
 *      Author: menna
 */

#include"ADC.h"

void ADC_init(void)
{
	ADMUX = 0;
	/* set ADEN :for ADC Enable
	 * set ADPS0 & ADPS1 : for 8 prescaler
	 */
	ADCSRA |= (1<<ADEN) | (1<<ADPS0) | (1<<ADPS1);
}

uint16 ADC_readChannel(uint8 channel_num)
{
	channel_num &= 0x07;
	ADMUX &= 0xE0; /* clear first 5 bits before set the required channel */
	ADMUX |= channel_num;
	ADCSRA |= (1<<ADSC); /* start conversion */
	while(BIT_IS_CLEAR(ADCSRA,ADIF));
	SET_BIT(ADCSRA,ADIF);
	return ADC;
}
