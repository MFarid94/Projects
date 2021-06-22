/****************************************************************************
 *
 * Module: ADC
 *
 * File name: adc.c
 *
 * Description: Source file for ADC Driver
 *
 * Author: Muhammad Farid
 *
 ****************************************************************************/

#include"adc.h"

/*****************************************************************************
 *                           Function Definition                             *
 *****************************************************************************/

void ADC_init(void){
	/* ADMUX register bits description:
	 * REFS1:0 = 00 choose to connect external reference voltage by input this voltage through AREF pin
	 * ADLAR = 0 no adjusting of bits
	 * MUX4:0 = 00000 initializing ADC channel to channel zero
	 */
	ADMUX = 0;

	/* ADCSRA register bits description:
	 * ADEN = 1 Enable ADC feature
	 * ADIE = 0 Disable ADC Interrupt
	 * ADPS2:0 = 011 to choose ADC_Clock = F_CPU/8 = 1MHz/8 = 125 KHz --> ADC must operate in range 50-200 KHz,
	 * */
	ADCSRA |= (1<<ADEN) | (1<<ADPS0) | (1<<ADPS1);
}

uint16 ADC_readChannel(uint8 channel_num){
	ADMUX = (ADMUX & 0xE0) | (channel_num & 0x07);		/* clear MUX4:0 bits & mask least 3 bits of channel number then write
	 	 	 	 	 	 	 	 	 	 	 	 	 	   required channel to be used to ADMUX register                      */
	SET_BIT(ADCSRA,ADSC);								/* Start converting the analog readings */
	while(BIT_IS_CLEAR(ADCSRA,ADIF));					/* Poll on ADC flag, if set to 1 then converting is finished */
	SET_BIT(ADCSRA,ADIF);								/* Clear ADC Flag by setting it to 1 */
	return(ADC);										/* Return Data after conversion */
}
