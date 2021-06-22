/****************************************************************************
 *
 * File name: adc.c
 *
 * Description: Write Embedded C code using ATmega16 uC to update 2x16 LCD
 * 				Display by ADC Value using Potentiometer
 *
 * 				Requirements:
 * 				- Configure the uC control with internal 1Mhz Clock
 * 				- Connect the LCD Data Path to PORTC
 * 				- Connect the "RS" LCD pin to PD4
 * 				- Connect the "R/W" LCD pin to PD5
 * 				- Connect the "E" LCD pin to PD6
 * 				- Potentiometer connected to ADC Channel 0
 * 				- This message always exist on LCD:
 * 				  "ADC Value = x", x is the ADC value got after convert
 * 				  the analog input to digital
 *
 *
 * Author: Muhammad Farid
 *
 ****************************************************************************/

#include"adc.h"
#include"lcd.h"


int main(void){
	uint16 res_value;
	LCD_init();				/* Initialize LCD Module */
	ADC_init();				/* Initialize ADC Module */
	LCD_clearScreen();		/* Clear Screen at beginning */

	/* Display this string "ADC Value = " only once on LCD Screen */
	LCD_displayString("ADC Value = ");

	while(1){
		LCD_gotoRowColumn(0,12);			/* display the number every time at this position  */
		res_value = ADC_readChannel(0);		/* read channel zero when the potentiometer is connected */
		LCD_IntegerToString(res_value);		/* display the ADC value on LCD screen */
	}

}
