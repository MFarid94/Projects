/******************************************************************************
 *
 * Module: SPI
 *
 * File Name: spi.h
 *
 * Description: Source file for the SPI driver
 *
 * Author: Mohamed Farid
 *
 *******************************************************************************/

#include "spi.h"

/*******************************************************************************
 * 							 Function Definitions							   *
 *******************************************************************************/

void SPI_masterInit(void)
{
	/********* Configure SPI Master pins *********
	 * SS(PD4) 		--> output
	 * MOSI(PD5)	--> output
	 * MISO(PD6)	--> input
	 * SCK(PD7)		--> output
	 *********************************************/
	DDRB |= (1<<PD4) | (1<<PD5) | (1<<PD7);
	DDRB &= (~(1<<PD6));

	/* SPE=1 	Enable SPI
	 * MSTR=1 	Enable MC as Master
	 * Fosc/4,  SPR1:0 = 00 */
	SPCR = (1<<SPE) | (1<<MSTR);
}

void SPI_slaveInit(void)
{
	/********* Configure SPI Slave pins *********
	 * SS(PD4)		--> input
	 * MOSI(PD5)	--> input
	 * MISO(PD6)	--> ouput
	 * SCK(PD7)		--> input
	 ********************************************/
	DDRB &= (~(1<<PD4)) & (~(1<<PD5)) & (~(1<<PD7));
	DDRB |= (1<<PD6);

	/* SPE=1 	Enable SPI
	 * MSTR=0	Enable MC as Slave
	 * Fosc/4,  SPR1:0 = 00 */
	SPCR = (1<<SPE);
}

void SPI_sendByte(uint8 data)
{
	SPDR = data;		/* Send data by SPI */
	while(BIT_IS_CLEAR(SPSR,SPIF)){};	/* Wait until SPI interrupt flag=1, transmission complete */
}

uint8 SPI_receiveByte(void)
{
	while(BIT_IS_CLEAR(SPSR,SPIF)){};	/* Wait until SPI interrupt flag=1, transmission complete */
	return SPDR;			/* return the received byte from SPI data register */
}

void SPI_sendString(const uint8 *str)
{
	uint8 i=0;
	while(str[i] != '\0')
	{
		SPI_sendByte(str[i]);
		i++;
	}
}

void SPI_receiveString(char *str)
{
	uint8 i=0;
	str[i] = SPI_receiveByte();
	while(str[i] != '#')
	{
		i++;
		str[i] = SPI_receiveByte();
	}
	str[i] = '\0';
}
