/****************************************************************************
 *
 * Module: ADC
 *
 * File name: adc.c
 *
 * Description: Header file for ADC Driver
 *
 * Author: Muhammad Farid
 *
 ****************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include"std_types.h"
#include"micro_config.h"
#include"common_macros.h"

/*****************************************************************************
 *                           Function prototypes                             *
 *****************************************************************************/
/*
 * Function description: Function responsible for initializing ADC driver */
void ADC_init(void);

/* Function description: Function responsible for reading analog data from
 * a certain ADC channel and convert it to digital using the ADC driver */
uint16 ADC_readChannel(uint8 channel_num);

#endif /* ADC_H_ */
