/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the UART AVR driver
 *
 * Author: Mohamed Farid
 *
 *******************************************************************************/

#include "uart.h"

#define BAUD_PRESCALE ((F_CPU/(USART_BAUDRATE*8UL))-1)

/*******************************************************************************
 * 							 Function Prototypes							   *
 *******************************************************************************/

void UART_init(void)
{
	/*
	 * U2X = 1 for double transmission speed
	 */
	UCSRA = (1<<U2X);
	/************************ UCSRB Description ********************************
	 * RXCIE = 0 Disable USART Rx complete interrupt enable
	 * TXCIE = 0 Disable USART Tx complete interrupt enable
	 * UDRIE = 0 Disable USART Data register empty interrupt enable
	 * RXEN = 1 Receiver enable
	 * TXEN = 1 Transmitter enable
	 * UCSZ2 = 0 8-bit mode
	 * RXB8 & TXB8 not used to 8-bit data mode
	 ***************************************************************************/
	UCSRB = (1<<RXEN) | (1<<TXEN);
	/************************ UCSRC Description ********************************
	 * URSEL = 1 Enable in order to write in UCSRC register
	 * UMSEL = 0 for Asynchronous operation
	 * UPM1:0 = 00 Disable parity bit checking
	 * USBS = 0 1-bit Stop bit select
	 * UCPOL = 0 	Used with the Synchronous operation only
	 * UCSZ1:0 = 11  For 8-bit data mode
	 ***************************************************************************/
	UCSRC = (1<<UCSZ0) | (1<<UCSZ1);
	/* First 8-bits from the BAUD_PRESCALE inside UBRRL and last 4-bits in UBRRH */
	UBRRL = BAUD_PRESCALE;
	UBRRH = BAUD_PRESCALE >> 8;
}

void UART_sendByte(const uint8 data)
{
	/*
	 * UDRE flag is set when Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){};
	UDR = data;
	/************************ Another solution *********************************
	 * Write data to buffer then wait until transmission complete flag is set
	 * UDR = data
	 * while(BIT_IS_CLEAR(UCSRA,TXC)){}
	 * SET_BIT(UCSRA,TXC) //Clear transmission flag by setting it to one
	 ***************************************************************************/
}

uint8 UART_receiveByte(void)
{
	/*
	 * RXC Flag is set when Rx buffer (UDR) is full and ready for receiving
	 * a byte so wait until this flag is set to one
	 */
	while(BIT_IS_CLEAR(UCSRA,RXC)){};
	/* Read the received data from buffer (UDR) , Rx flag will be cleared
	 * once data is returned (read) */
	return UDR;
}

void UART_sendString(const uint8 *str)
{
	uint8 i;
	while(str[i] != '\0')
	{
		UART_sendByte(str[i]);
		i++;
	}
}

void UART_receiveString(uint8 *str)
{
	uint8 i = 0;
	str[i] = UART_receiveByte();
	while(str[i] != '#')
	{
		i++;
		str[i] = UART_receiveByte();
	}
	str[i] = '\0';
}
