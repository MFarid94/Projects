 /******************************************************************************
 *
 * File Name: Calculator.c
 *
 * Description: It is a simple calculator, that makes addition, subtraction,
 * 				multiplication and reminder calculations on numbers more than one digit.
 *				After entering the first number, we press enter to enter the second number.
 *				While after entering the second number, we press equal to view the result.
 *				If any other operator is pressed rather than the correct 4,
 *				it will print a message that the operator is wrong and will start again from begining.
 *				Simple calculator on ATMEGA16 microcontroller, 4x4 Keypad and 2x16 LCD, that makes addition,
 *				subtraction, multiplication and reminder calculations on numbers more than one digit.
 *
 * Author: Muhammad Farid
 *
 *******************************************************************************/

/*
 * The user should press enter after entering the first number, to be able to enter the second one
 * And should press enter after the second number, to be able to view the result
 */

/*******************************************************************************
 * 							 INCLUDES										   *
 *******************************************************************************/
#include "lcd.h"
#include "keypad.h"

/*******************************************************************************
 * 							 GLOBAL VARIABLES								   *
 *******************************************************************************/
/*Global variable at which when it is set to 1 a wrong message is
 *printed and begin from the beginning
 */
unsigned char begin_flag=0;

/*******************************************************************************
 * 							 FUNCTIONS DEFINITIONS							   *
 *******************************************************************************/
/*
 * Function display the digits entered for the same number return it
 */

sint32 enter_number(void)
{
	sint32 whole_number = 0; 		/*Variable at which the number is saved in it*/
	uint8 num = 0; 					/*Variable save the key that is pressed*/

	/*The goal of this variable to see if it is the first time in the loop or not*/
	uint8 num_size = 0;

	/*As long as enter or equal or the operators are not pressed, enter the loop*/
	while((num != 13) && (num != '=') && (num != '%') && (num != '*') && (num != '-') && (num != '+'))
	{
		num = KeyPad_getPressedKey();
		if((num == '%') || (num == '*') || (num == '-') || (num == '+') || (num == '='))
		{
			LCD_displayCharacter(num);
			begin_flag = 1;
		}
		
		/*If enter key is pressed for the first time in the loop*/
		else if((num == 13) && (num_size == 0))
		{
			begin_flag = 1;
		}
		
		/*If enter key is pressed after more than one loop return the number entered
		 *and complete the code whether by entering the second number or viewing the result
		 */
		else if(num == 13)
		{
			return whole_number;
		}
		
		else
		{
			LCD_intgerToString(num);
			/*Here we save the number entered to return it in num1 and num2*/
			
			whole_number= whole_number*10 + num;
			/*Increase the number size which declare how many times we entered the loop*/
			
			num_size ++;
			_delay_ms(500);
		}
	}
	return whole_number;
}

int main(void)
{
	uint8 operator;
	sint32 num1, num2;
	sint64 result;
	while(1)
	{
		LCD_init();
		LCD_displayStringRowColumn(0,0,"Operator:");
		operator = KeyPad_getPressedKey();
		if ((operator !='+') && (operator !='-') && (operator !='*') && (operator !='%'))
		{
			if(operator == '=')
			{
				LCD_displayCharacter(operator); /*Here it display (=)*/
			}
			else if((operator >= 0) && (operator <=9))
			{
				LCD_intgerToString(operator); /*Here it display the numbers from 0 to 9*/
			}
			
			/*If enter is pressed,nothing will appear*/
			/*Display this message if wrong operator is entered*/
			LCD_displayStringRowColumn(1,0,"Wrong operator");
			_delay_ms(500);
			continue;
		}
		else
		{
			LCD_displayCharacter(operator); /*Here it display (+,-,*,%)*/
			_delay_ms(500);
		}
		LCD_displayStringRowColumn(1,0,"Num1:");
		num1 = enter_number(); /*Press enter to enter num2*/
		if(begin_flag==1)
		{
			/*Here we print a wrong message and begin again*/
			LCD_displayStringRowColumn(2,0,"Wrong number");
			begin_flag = 0; /*Return the flag to 0 for new operations*/
			_delay_ms(500);
			continue;
		}
		_delay_ms(500);

		LCD_displayStringRowColumn(2,0,"Num2:");
		num2 = enter_number(); /*Press enter to view the result*/
		if(begin_flag==1)
		{
			/*Here we print a wrong message and begin again*/
			LCD_displayStringRowColumn(3,0,"Wrong number");
			begin_flag = 0; /*Return the flag to 0 for new operations*/
			_delay_ms(500);
			continue;
		}
		_delay_ms(500);

		switch(operator)
		{
			case '+':
				result = num1 + num2;
				LCD_displayStringRowColumn(3,0,"Result:");
				LCD_intgerToString(result);
				break;

			case '-':
				result = num1 - num2;
				LCD_displayStringRowColumn(3,0,"Result:");
				LCD_intgerToString(result);
				break;

			case '*':
				result = num1 * num2;
				LCD_displayStringRowColumn(3,0,"Result:");
				LCD_intgerToString(result);
				break;

			case '%':
				result = num1 % num2;
				LCD_displayStringRowColumn(3,0,"Result:");
				LCD_intgerToString(result);
				break;
		}
		_delay_ms(500);
	}
}
