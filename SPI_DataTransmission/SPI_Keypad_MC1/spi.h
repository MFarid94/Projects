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

#ifndef SPI_H_
#define SPI_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/*******************************************************************************
 * 							 Function Prototypes							   *
 *******************************************************************************/

void SPI_masterInit(void);
void SPI_slaveInit(void);
void SPI_sendByte(uint8 data);
uint8 SPI_receiveByte(void);
void SPI_sendString(const uint8 *str);
void SPI_receiveString(char *str);

#endif /* SPI_H_ */
