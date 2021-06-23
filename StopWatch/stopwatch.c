/*
 * stopwatch.c
 * Created on: May 29, 2021
 * Author: Muhammad Farid
 *
 * Description: It is a stop watch project (Hours : Minutes : Seconds), using timers and external interrupts.
 * INT0: Reset the stop watch
 * INT1: Pause the stop watch
 * INT2: Resume the stop watch
 * Timer 1: In compare mode , Fcpu = 1Mhz , prescaler = 1024
 * Stop watch based on ATMEGA16 microcontroller and multiplexed 7-segments connected to microcontroller,
 * using 3 buttons for stop, resume and reset options. Drivers Designed and Implemented for project: Timer,External Interrupts
 */

#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

/* Clock variables and their subsets */
volatile unsigned char g_Hours = 0;
unsigned char g_HoursUnits = 0;
unsigned char g_HoursTens = 0;
volatile unsigned char g_Minutes = 0;
unsigned char g_MinutesUnits = 0;
unsigned char g_MinutesTens = 0;
volatile unsigned char g_Seconds = 0;
unsigned char g_SecondsUnits = 0;
unsigned char g_SecondsTens = 0;

/* Code of Timer1 on CTC mode that increments the clock variables */
ISR(TIMER1_COMPA_vect){
	g_Seconds++;
	if(59 == g_Seconds){
		g_Minutes++;
		if(59 == g_Minutes){
			g_Hours++;
			g_Minutes = 0;
		}
		g_Seconds = 0;
	}
}

/* Code of INT0 ISR used to reset stop watch by re-setting
 * TIMER1 initial count to zero and clearing all timing variables */
ISR(INT0_vect){
	TCNT1 = 0;
	g_Seconds = 0;
	g_SecondsUnits = 0;
	g_SecondsTens = 0;
	g_Minutes = 0;
	g_MinutesUnits = 0;
	g_MinutesTens = 0;
	g_Hours = 0;
	g_HoursUnits = 0;
	g_HoursTens = 0;
}

/* Code of INT1 ISR used to pause stop watch by clearing all
 * prescaler, i.e. No clock source(Timer/Counter stopped)*/
ISR(INT1_vect){
	TCCR1B &= (~(1<<CS10)) & (~(1<<CS11)) & (~(1<<CS12));
}

/* Code of INT2 ISR used to resume stop watch by re-setting prescaler */
ISR(INT2_vect){
	TCCR1B |= (1<<CS12) | (1<<CS10);
}

/* Timer1 is used to cause an interrupt each second using Fcpu 1 MHZ
 * and a prescaler of 1024 then each clock tick is 1 ms we set compare
 * register to clear on 1000 clocks i.e. 1 second */
void TIMER1_compare_mode_init(void){
	TCNT1 = 0;					/* Timer Initially 0 */
	OCR1A = 1000;				/* Compare on clock 1000 , clock = 1ms*/
	TIMSK |= (1<<OCIE1A);		/* Output compare A match interrupt enable */
	/* Configure timer control register TCCR1A
	 * 1. Disconnected OC1A COM1A1=0 COM1A0=0
	 * 2. Disconnect OC1B  COM1B0=0 COM1B1=0
	 * 3. NON PWM mode FOC1A=1 FOC1B=0.
	 */
	TCCR1A = (1<<FOC1A);
	/* Configure timer control register TCCR1B
	 * 1. CTC mode WGM10=0 WGM11=0 WGM12=1 WGM13=0
	 * 2. Fcpu =1 MHZ, Prescaler = Fcpu/1024 CS10=1 CS11=0 CS12=1
	 * */
	TCCR1B = (1<<WGM12) | (1<<CS10) | (1<<CS12);
}

/* INT0 parameter configuration */
void INT0_init(void){
	GICR |= (1<<INT0);   				/* Enable Interrupt 0 */
	MCUCR |= (1<<ISC00) | (1<<ISC01);	/* Interrupt 0 is generated on rising edge */
	DDRD &= (~(1<<PD2));				/* Configure INT0/PD2 as input pin */
	PORTD |= (1<<PD2);					/* Activate internal pull up resistor */
}

/* INT1 parameter configuration */
void INT1_init(void){
	GICR |= (1<<INT1);					/* Enable interrupt 1 */
	MCUCR |= (1<<ISC10) | (1<<ISC11);	/* Interrupt 1 is generated on rising edge */
	DDRD &= (~(1<<PD3));				/* Configure INT1/PD3 as input pin */
}

/* INT2 parameter configuration */
void INT2_init(void){
	GICR |= (1<<INT2);					/* Enable interrupt 2 */
	MCUCSR |= (1<<ISC2);				/* Interrupt 2 is generated on rising edge */
	DDRB &= (~(1<<PB2));				/* Configure INT2/PB2 as input pin */
	PORTB |= (1<<PB2);					/* Activate internal pull up */
}

int main(void){
	DDRA |= 0x3F;						/* Configure first 6 pins in PORTA as output */
	PORTA &= 0xC0;						/* Initialize first 6 pins in PORTA to zero */

	DDRC |= 0x0F;						/* Configure first 4 pins in PORTC as output */
	PORTC &= 0xF0;						/* Initialize first 4 pins in PORTC to Zero */

	SREG |= (1<<7);
	TIMER1_compare_mode_init();
	INT0_init();
	INT1_init();
	INT2_init();

	while(1){
		g_SecondsUnits = g_Seconds % 10;		/* Obtain units of seconds by remainder to 10 */
		g_SecondsTens = g_Seconds / 10;			/* Obtain tens of seconds by division to 10 */
		g_MinutesUnits = g_Minutes % 10;
		g_MinutesTens = g_Minutes / 10;
		g_HoursUnits = g_Hours % 10;
		g_HoursTens = g_Hours / 10;


		/* By clearing and setting PORTA registers we allow multiplexed output on 7 segment
		 * reducing decoders and pins used in our setup, a delay of 3ms allows human eye to
		 * see 7 segments as if they are always on, then writing on PORTC the need to be displayed
		 * values, bit masking is used as not to corrupt other pin status of PORTC in case of
		 * generic application ( Not specifically to this application ) */

		PORTA &= 0xC0;											/* Set Sixth pin in PORTA, enabling Sixth 7 segment */
		PORTA |= (1<<PA5);
		PORTC = (PORTC & 0xF0) | (g_SecondsUnits & 0x0F);       /* Display units of seconds on first 7 segment */
		_delay_ms(3);

		PORTA &= 0xC0;											/* Set Fifth pin in PORTA, enabling Fifth 7 segment */
		PORTA |= (1<<PA4);
		PORTC = (PORTC & 0xF0) | (g_SecondsTens & 0x0F);		/* Displaying Tens of seconds on second 7 segment */
		_delay_ms(3);

		PORTA &= 0xC0;											/* Set Fourth pin in PORTA, enabling Fourth 7 segment */
		PORTA |= (1<<PA3);
		PORTC = (PORTC & 0xF0) | (g_MinutesUnits & 0x0F);		/* Displaying Units of Minutes on Third 7 segment */
		_delay_ms(3);

		PORTA &= 0xC0;											/* Set Third pin in PORTA, enabling Third 7 segment */
		PORTA |= (1<<PA2);
		PORTC = (PORTC & 0xF0) | (g_MinutesTens & 0x0F);		/* Displaying Tens of Minutes on Fourth 7 segment */
		_delay_ms(3);

		PORTA &= 0xC0;											/* Set Second pin in PORTA, enabling Second 7 segment */
		PORTA |= (1<<PA1);
		PORTC = (PORTC & 0xF0) | (g_HoursUnits & 0x0F);			/* Displaying Units of Hours on Fifth 7 segment */
		_delay_ms(3);

		PORTA &= 0xC0;											/* Set First pin in PORTA, enabling first 7 segment */
		PORTA |= (1<<PA0);
		PORTC = (PORTC & 0xF0) | (g_HoursTens & 0x0F);			/* Displaying Tens of Hours on Sixth 7 segment */
		_delay_ms(3);
	}
}

