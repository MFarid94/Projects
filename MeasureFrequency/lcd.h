 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD Driver
 *
 * Author: Muhammad Farid
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/*******************************************************************************
 *                   		 Preprocessor Macros                               *
 *******************************************************************************/

/* LCD Hardware Pins*/
#define RS PD4
#define RW PD5
#define E PD7
#define LCD_CTRL_PORT 		PORTD
#define LCD_CTRL_PORT_DIR 	DDRD
#define LCD_DATA_PORT		PORTC
#define LCD_DATA_PORT_DIR	DDRC

/* LCD Commands */
#define TWO_LINE_LCD_EIGHT_BIT_MODE		0x38
#define CLEAR_COMMAND					0x01
#define CURSOR_OFF						0x0C
#define CURSOR_ON						0x0E
#define SET_CURSOR_LOCATION				0x80

/*******************************************************************************
 * 							 Function Prototypes							   *
 *******************************************************************************/

/* Function to initialize LCD */
void LCD_init(void);

/* Function to send command */
void LCD_sendCommand(uint8 command);

/* Function to display a certain character */
void LCD_displayCharacter(uint8 data);

/* Function to display a certain string */
void LCD_displayString(const char *str);

/* Function to goto a certain position on LCD display */
void LCD_goToRowColumn(uint8 row, uint8 column);

/* Function to display a string in a certain position on LCD display */
void LCD_displayStringRowColumn(uint8 row, uint8 column, const char *str);

/* Function to clear screen */
void LCD_clearScreen(void);

/* Function to display an integer on screen */
void LCD_integerToString(int data);

#endif /* LCD_H_ */
