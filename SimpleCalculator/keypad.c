/******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.c
 *
 * Description: Source file for the Keypad driver
 *
 * Author: Mohamed Farid
 *
 *******************************************************************************/

#include "keypad.h"

/*******************************************************************************
 * 							 Function Prototypes(private)					   *
 *******************************************************************************/

#if (3 == N_col)
/*
 * Function responsible for mapping the switch number in the keypad to it's
 * corresponding functional number in the proteus for 4x3 keypad
 */
static uint8 keypad_4x3_adjustKeyNumber(uint8 button_number);
#elif (4 == N_col)
/*
 * Function responsible for mapping the switch number in the keypad to it's
 * corresponding functional number in the proteus for 4x3 keypad
 */
static uint8 keypad_4x4_adjustKeyNumber(uint8 button_number);
#endif
/*******************************************************************************
 * 							 Function Definitions                              *
 *******************************************************************************/
uint8 keypad_getPressedKey(void)
{
	uint8 row, col;

	while(1)
	{
		for(col = 0; col < 4 ; col++ )
		{
			/*
			 * each time only one of the column pins will be
			 * output while the rest will be input including row pins
			 */
			KEYPAD_PORT_DIR = (0b00010000<<col);

			/* only one of the column pins will output zero while
			 * row pins are internal pull up activated
			 */
			KEYPAD_PORT_OUT = (~(0b00010000<<col));
			for(row = 0 ; row <4 ; row ++)	/* Loop for row */
			{
				if(BIT_IS_CLEAR(KEYPAD_PORT_IN,row)) /* If the switch is pressed in this row */
				{
					#if (3 == N_col)
							return keypad_4x3_adjuctKeyNumber((row*N_col)+col+1);
					#elif (4 == N_col)
							return keypad_4x4_adjustKeyNumber((row*N_col)+col+1);
					#endif
				}
			}
		}
	}
}

#if (3 == N_col)

static uint8 keypad_4x3_adjustKeyNumber(uint8 button_number)
{
	switch(button_number)
	{
			case 10: return '*';		/* ASCII code for ' = ' */
			         break;

			case 11: return 0;
					 break;

			case 12: return '#';		/* ASCII code for ' + ' */
			         break;

			default: return button_number;
					 break;
	}
}

#elif (4 == N_col)

static uint8 keypad_4x4_adjustKeyNumber(uint8 button_number)
{
	switch(button_number)
	{
			case 1: return 7;
					break;

			case 2: return 8;
					break;

			case 3: return 9;
					break;

			case 4: return '%';			/* ASCII for % */
					break;

			case 5: return 4;
					break;

			case 6: return 5;
					break;

			case 7: return 6;
					break;

			case 8: return '*';			/* ASCII for '*' */
					break;

			case 9: return 1;
					break;

			case 10: return 2;
					 break;

			case 11: return 3;
					 break;

			case 12: return '-';
					 break;

			case 13: return 13;			/* ASCII for Enter */
					 break;

			case 14: return 0;
					 break;

			case 15: return '=';		/* ASCII for ' = ' */
					 break;

			case 16: return '+';		/* ASCII for ' + ' */
					 break;

			default: return button_number;
	}
}

#endif
