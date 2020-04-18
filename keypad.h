/*
 * keypad.h
 *
 *  Created on: Apr 16, 2020
 *      Author: menna
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include"common_macros.h"
#include"micro_config.h"
#include"std_types.h"

#define num_col 3
#define num_row 4

/* keypad pins configuration */
#define KEYPAD_PORT_OUT PORTC
#define KEYPAD_PORT_IN PINC
#define KEYPAD_PORT_DIR DDRC

/* functions prototypes */
uint8 keypad_getPressedKey(void);

#endif /* KEYPAD_H_ */
