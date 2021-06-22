 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the LCD Driver
 *
 * Author: Muhammad Farid
 *
 *******************************************************************************/

#include "lcd.h"

void LCD_init(void)
{
	LCD_CTRL_PORT_DIR |= (1<<E) | (1<<RS) | (1<<RW);	/* Set Control pins as output pins */
	LCD_DATA_PORT_DIR = 0xFF;								/* Set Data pins as output pins */

	LCD_sendCommand(TWO_LINE_LCD_EIGHT_BIT_MODE);			/* use 2-line LCD + 8-bit data mode + 5*7 dot display mode */

	LCD_sendCommand(CURSOR_OFF);							/* cursor off */

	LCD_sendCommand(CLEAR_COMMAND);							/* clear LCD at the beginning */
}

void LCD_sendCommand(uint8 command)
{
	CLEAR_BIT(LCD_CTRL_PORT,RW);                /* Write data to LCD, RW = 0  */
	CLEAR_BIT(LCD_CTRL_PORT,RS);				/* Instruction mode, RS = 0 */

	_delay_ms(1);								/* Delay for processing tas = 50 ns */
	SET_BIT(LCD_CTRL_PORT,E);					/* Enable LCD E=1 */
	_delay_ms(1);								/* Delay for processing tpw - tdsw = 290-100 = 190 ns */
	LCD_DATA_PORT = command;					/* output the required command to the data bus D0 -> D7 */
	_delay_ms(1);								/* Delay for processing tdsw = 100 ns */
	CLEAR_BIT(LCD_CTRL_PORT,E);					/* Disable LCD E=0 */
	_delay_ms(1);								/* Delay for processing th = 13 ns*/
}

void LCD_displayCharacter(uint8 data)
{
	CLEAR_BIT(LCD_CTRL_PORT,RW);				/* Write data to LCD, RW=0 */
	SET_BIT(LCD_CTRL_PORT,RS);					/* Data mode, RS=1 */

	_delay_ms(1);								/* Delay for processing tas=50 ns */
	SET_BIT(LCD_CTRL_PORT,E);					/* Enable LCD E=1 */
	_delay_ms(1);								/* Delay for processing tpw - tdsw = 290-100 =190 ns */
	LCD_DATA_PORT = data;						/* output the required Data to the data bus D0 - D7 */
	_delay_ms(1);								/* Delay for processing tdsw = 100 ns */
	CLEAR_BIT(LCD_CTRL_PORT,E);					/* Disable LCD E=0 */
	_delay_ms(1);								/* Delay for processing th =13 ns */

}

void LCD_displayString(const char *str)
{
	uint8 i = 0;

	while(str[i] != '\0'){
		LCD_displayCharacter(str[i]);
		i++;
	}
}

void LCD_goToRowColumn(uint8 row, uint8 column)
{
	uint8 Address;

	/* Calculate the required address */
	switch(row){

				case 0: Address = column;
				break;

				case 1: Address = 0x40 + column;
				break;

				case 2: Address = 0x10 + column;
				break;

				case 3: Address = 0x50 + column;
				break;

	}
	/* To write a specific address in the LCD
	 * we need to apply the corresponding command 0b10000000 + Address */
	LCD_sendCommand(Address | SET_CURSOR_LOCATION);
}

void LCD_diplayStringRowColumn(uint8 row, uint8 column, const char *str)
{
	LCD_goToRowColumn(row,column);				/* Go to the LCD required Position */
	LCD_displayString(str);						/* display the string */
}

void LCD_integerToString(int data)
{
	char buff[16];								/* Buffer to store incoming integer */
	itoa(data,buff,10);							/* 10 for decimal */
	LCD_displayString(buff);
}

void clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND);             // Clear display
}
