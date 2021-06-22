/******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.h
 *
 * Description: Header file for the Keypad driver
 *
 * Author: Mohamed Farid
 *
 *******************************************************************************/


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/*******************************************************************************
 * 							 Preprocessor Macros							   *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define N_col 4
#define N_row 4

/* keypad Port Configurations */
#define KEYPAD_PORT_OUT		PORTA
#define KEYPAD_PORT_IN		PINA
#define KEYPAD_PORT_DIR		DDRA

/*******************************************************************************
 * 							 Function Prototypes							   *
 *******************************************************************************/

/*
 * Function responsible for getting the pressed keypad key
 */
uint8 keypad_getPressedKey(void);

#endif /* KEYPAD_H_ */
