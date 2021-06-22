/******************************************************************************
 *
 * File Name: Keypad_MC1.c
 *
 * Description: Write Embedded c code using ATmega16 uC to control LCD
 * 				display using keypad and UART.
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

#include "keypad.h"
#include "uart.h"

int main(void)
{
	uint8 key;
	UART_init();

	while(1)
	{
		key = keypad_getPressedKey();		/* Get the pressed key */

		/* Send the pressed key to the other MicroController through UART */
		UART_sendByte(key);

		/* Delay to compensate the difference between Hardware and Software speed,
		 * i.e without delay if key pressed the scan cycle will call the keypad_getPressedKey
		 * multiple times while the user only pressed once */
		_delay_ms(500);
	}
}
