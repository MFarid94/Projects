 /******************************************************************************
 *
 * File Name: measure.c
 *
 * Description: Write Embedded C code using ATmega16 uC to calculate the
 * 				frequency of an input signal.
 * 				Requirements:
 * 				 - Configure the uC control with internal 1Mhz Clock.
 * 				 - The input signal frequency is 500 hz and it is connected to
 * 				 	ICP1/PD6 pin.
 * 				 - Configure the timer1 clock to equals to F_CPU without
 * 				 	prescaling.
 * 				 - Timing should be count using Timer1 in normal mode.
 * 				 - Display the frequency of the input signal on LCD.
 *
 * Author: Muhammad Farid
 *
 *******************************************************************************/

#include "icu.h"
#include "lcd.h"

uint8  g_edgeCount = 0;
uint16 g_timeHigh = 0;
uint16 g_timePeriod = 0;
uint16 g_timePeriodPlusHigh = 0;

void APP_edgeProcessing(void)
{
	g_edgeCount++;
	if(1 == g_edgeCount)
	{
		/* Clear the timer counter register to start measurements
		 * from the first detected rising edge */
		Icu_clearTimerValue();
		/* Detect falling edge */
		Icu_setEdgeDetectionType(FALLING);
	}
	else if(2 == g_edgeCount)
	{
		/* Store the high time value */
		g_timeHigh = Icu_getInputCaptureValue();
		/* Detect rising edge */
		Icu_setEdgeDetectionType(RISING);
	}
	else if(3 == g_edgeCount)
	{
		/* Store the period time value */
		g_timePeriod = Icu_getInputCaptureValue();
		/* Detect falling edge */
		Icu_setEdgeDetectionType(FALLING);
	}
	else if(4 == g_edgeCount)
	{
		/* Store the period time value + High time value */
		g_timePeriodPlusHigh = Icu_getInputCaptureValue();
		/* Clear the timer counter register to start measurements again */
		Icu_clearTimerValue();
		/* Detect Rising edge */
		Icu_setEdgeDetectionType(RISING);
	}
}


int main(void)
{
	uint32 frequency = 0;

	/* Create configuration structure for ICU Driver */
	Icu_ConfigType Icu_Config = {F_CPU_CLOCK,RISING};

	/* Enable Global interrupt I-Bit */
	SREG |= (1<<7);

	/* Set the Call back function pointer in the ICU Driver */
	Icu_setCallBack(APP_edgeProcessing);

	/* Initialize both the LCD and ICU Driver */
	LCD_init();
	Icu_init(&Icu_Config);

	while(1)
	{
		if(4 == g_edgeCount)
		{
			Icu_DeInit();		/* Disable ICU Driver */
			g_edgeCount = 0;
			LCD_displayString("Frequency= ");
			/* Calculate the frequency */
			frequency = (1000000/(g_timePeriodPlusHigh - g_timeHigh));
			/* Display the frequency on the LCD screen */
			LCD_integerToString(frequency);
			LCD_displayString("Hz");
		}
	}
}
