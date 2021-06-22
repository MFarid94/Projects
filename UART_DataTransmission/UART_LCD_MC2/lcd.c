/****************************************************************************
 *
 * Module: LCD
 *
 * File name: LCD.c
 *
 * Description: Source file for LCD Driver
 *
 * Author: Muhammad Farid
 *
 ****************************************************************************/

#include "lcd.h"

/****************************************************************************
 *                           Function Definitions                           *
 ****************************************************************************/

void LCD_init(void){
	LCD_DATA_PORT_DIR = 0xFF;							/* Configure the data port as output port */
	LCD_CTRL_PORT_DIR |= (1<<RS) | (1<<RW) | (1<<E);	/* Configure the control pins(E,RW,RS) as output pins */

	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE);		/* use 2-line LCD + 8-bit Data mode + 5*7 dot display mode */

	LCD_sendCommand(CURSOR_OFF);						/* Cursor off */

	LCD_sendCommand(CLEAR_COMMAND);						/* clear LCD at the beginning */
}

void LCD_sendCommand(uint8 command){
	CLEAR_BIT(LCD_CTRL_PORT,RS);						/* Instruction mode RS = 0 */
	CLEAR_BIT(LCD_CTRL_PORT,RW);						/* Write data to LCD RW= 0 */
	_delay_ms(1);										/* delay for processing  tas= 50 ns, 1 ms is delayed due to hardware lagging */
	SET_BIT(LCD_CTRL_PORT,E);							/* Enable LCD E=1 */
	_delay_ms(1);										/* delay for processing tpw - tdsw = 290-100=190 ns */
	LCD_DATA_PORT = command;						 	/* output the required commands to the data bus D0 -> D7 */
	_delay_ms(1);										/* delay for processing tdsw = 100 ns */
	CLEAR_BIT(LCD_CTRL_PORT,E);							/* disable LCD E=0 */
	_delay_ms(1);										/* delay for processing th = 19 ns */
}

void LCD_displayCharacter(uint8 data){
	SET_BIT(LCD_CTRL_PORT,RS);							/* Data mode RS = 1         */
	CLEAR_BIT(LCD_CTRL_PORT,RW);						/* Write data to LCD RW = 0 */
	_delay_ms(1);										/* delay for processing tas = 50ns */
	SET_BIT(LCD_CTRL_PORT,E);							/* Enable LCD E=1 */
	_delay_ms(1);										/* delay for processing tpw - tdsw = 290 - 100 = 190ns */
	LCD_DATA_PORT = data;								/* output the required data char to the data bus D0 -> D7 */
	_delay_ms(1);										/* delay for processing tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E);							/* disable LCD E=0 */
	_delay_ms(1);										/* delay for processing th = 19ns */
}

void LCD_displayString(const char* str){
	uint8 i = 0;

	while(str[i] != '\0'){
		LCD_displayCharacter(str[i]);
		i++;
	}
}

void LCD_gotoRowColumn(uint8 row, uint8 column){

	uint8 Address;

	/* Calculate the required address via following switch case */
	switch(row){
		case 0:
				Address = column;
				break;

		case 1:
				Address = column + 0x40;
				break;

		case 2:
				Address = column + 0x10;
				break;

		case 3:
				Address = column + 0x50;
				break;
	}
	/* to write a specific address in the LCD
	 * we need to apply the corresponding command 0b10000000 + address */
	LCD_sendCommand(Address | SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(uint8 row, uint8 column, const char *str){
	LCD_gotoRowColumn(row,column);		/* Go to required position */
	LCD_displayString(str);				/* Display string at required postion */
}


void LCD_IntegerToString(int data){
	char buff[16];			   /* String to hold the ascii result */
	itoa(data,buff,10);	       /* 10 for decimal */
	LCD_displayString(buff);
}

void LCD_clearScreen(void){
	LCD_sendCommand(CLEAR_COMMAND);		// Clear display
}
