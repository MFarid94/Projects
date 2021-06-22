 /******************************************************************************
 *
 * Module: ICU
 *
 * File Name: icu.c
 *
 * Description: Source file for the ICU Driver
 *
 * Author: Muhammad Farid
 *
 *******************************************************************************/

#include "icu.h"

/*******************************************************************************
 * 							 Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 * 							 Interrupt Service Routines 					   *
 *******************************************************************************/

ISR(TIMER1_CAPT_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the call back function in the application after the edge is detected */
		(*g_callBackPtr)();		/* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*******************************************************************************
 * 							 Function Definitions							   *
 *******************************************************************************/

/*
 * Description: Function to initialize the ICU Driver.
 * 	1. Set the required Clock.
 * 	2. Set the required Edge detection.
 * 	3. Enable the input capture interrupt.
 * 	4. Initialize Timer1 registers.
 */
void Icu_init(const Icu_ConfigType *Config_Ptr)
{
	/* Set pin PD6/ICP1 as input pin */
	DDRD &= (~(1<<PD6));

	/* Operate Timer1 in normal mode */
	TCCR1A = (1<<FOC1A) |(1<<FOC1B);

	/*
	 * Insert the required clock values in the first three bits (CS10, CS11 and CS12)
	 * of TCCR1B Register
	 * */
	TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->clock);

	/*
	 * Insert the required edge type in ICES1 bit in register TCCR1B
	 * */
	TCCR1B = (TCCR1B & 0xBF) | ((Config_Ptr->edge)<<6);

	/* Initial value of Timer1 is Zero */
	TCNT1 = 0;

	/* Initial value for the input capture register */
	ICR1 = 0;

	/* Enable the input capture interrupt to generate an interrupt when an edge is detected PD6/ICP1 */
	TIMSK |= (1<<TICIE1);
}

/*
 * Description: Function to set the Call Back function address
 */

void Icu_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the call back function in a global variable */
	g_callBackPtr = a_ptr;
}

/*
 * Description: Function to set the required edge detection
 */

void Icu_setEdgeDetectionType(const Icu_EdgeType a_edgetype)
{
	/*
	 * insert the required edge type in ICES1 bit in TCCR1B Register
	 */
	TCCR1B = (TCCR1B & 0xBF) | (a_edgetype<<6);
}

/*
 * Description: Function to get the Timer1 value when the input is captured
 * 				the value stored at Input Capture Register ICR1
 */

uint16 Icu_getInputCaptureValue(void)
{
	return ICR1;
}

/*
 * Description: Function to clear the Timer1 value to start count from zero
 */

void Icu_clearTimerValue(void)
{
	TCNT1 = 0;
}

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void Icu_DeInit(void)
{
	/* clear  All Timer1 Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/* Disable the Input Capture interrupt */
	TIMSK &= (~(1<<TICIE1));
}
