 /******************************************************************************
 *
 * Module: Micro - Configuration
 *
 * File Name: Micro_Config.h
 *
 * Description: File include all Microcontroller libraries
 *
 * Author: Mohamed Farid
 *
 *******************************************************************************/

#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_

#ifndef F_CPU
#define F_CPU 1000000UL // 1 Mhz Clock Frequency
#endif


#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

#endif /* MICRO_CONFIG_H_ */
