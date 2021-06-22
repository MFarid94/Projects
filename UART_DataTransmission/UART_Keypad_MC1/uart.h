/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mohamed Farid
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"

/*******************************************************************************
 * 							 Preprocessor Macros							   *
 *******************************************************************************/

/* UART Driver Baud Rate */
#define USART_BAUDRATE 9600

/*******************************************************************************
 * 							 Function Prototypes							   *
 *******************************************************************************/

void UART_init(void);

void UART_sendByte(const uint8 data);

uint8 UART_recieveByte(void);

void UART_sendString(const uint8 *str);

void UART_recieveString(uint8 *str);   // Receive until #

#endif /* UART_H_ */
