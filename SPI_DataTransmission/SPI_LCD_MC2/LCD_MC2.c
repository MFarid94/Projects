/******************************************************************************
 *
 * File Name: SPI_LCD_MC2.c
 *
 * Description: Write Embedded c code using ATmega16 uC to control LCD
 * 				display using keypad and SPI.
 * 				Requirements:
 * 				- Configure the uC control with internal 1 Mhz Clock.
 * 				- 4x4 keypad is connected to PORTA in uC1.
 * 				- Use internal pull up Resistors with keypad.
 * 				- LCD connected to uC2.
 * 				- Display the keypad button on LCD.
 *
 * Author: Mohamed Farid
 *
 *******************************************************************************/

#include "lcd.h"
#include "spi.h"

int main(void)
{
	uint8 key;
	LCD_init();
	SPI_slaveInit();

	LCD_clearScreen();

	while(1)
	{
		key = SPI_receiveByte();		/* Receive byte using SPI */
		if((key >= 0) && (key <= 9))
		{
			LCD_IntegerToString(key);
		}
		else
		{
			LCD_displayCharacter(key);
		}

	}
}
