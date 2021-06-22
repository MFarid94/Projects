/****************************************************************************
 *
 * Module: Micro-Configuration
 *
 * File name: micro_config.h
 *
 * Description: File include all Micro-controller libraries
 *
 * Author: Muhammad Farid
 *
 ****************************************************************************/

#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_

#ifndef F_CPU
#define F_CPU 1000000UL // 1MHZ Clock Frequency
#endif

#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

#endif /* MICRO_CONFIG_H_ */
