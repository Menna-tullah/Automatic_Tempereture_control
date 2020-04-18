/*
 * LCD.h
 *
 *  Created on: Apr 16, 2020
 *      Author: menna
 */

#ifndef LCD_H_
#define LCD_H_

#include"micro_config.h"
#include"std_types.h"
#include"common_macros.h"


#define RS PD5
#define RW PD6
#define E PD7

#define LCD_CTRL_PORT PORTD
#define LCD_CTRL_PORT_DIR DDRD

#define LCD_DATA_PORT PORTB
#define LCD_DATA_PORT_DIR DDRB

/* functions prototypes */
void LCD_init(void);
void LCD_sendCommand(uint8 command);
void LCD_dispalyChar(uint8 ch);
void LCD_displayString(const char* st);
void LCD_clearScreen(void);
void LCD_goToRowColumn(uint8 row,uint8 col);
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *st);
void LCD_integerToString(uint8 num);

/* LCD commands */
#define CLEAR_CMD 0x01
#define TWO_LINE_EIGHT_BIT_MODE 0x38
#define CURSOR_ON 0x0E
#define CURSOR_OFF 0x0C
#define SET_CURSOR_LOCATION 0x80

#endif /* LCD_H_ */
