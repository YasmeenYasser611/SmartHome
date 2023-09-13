/*
 * ADC.h
 *
 *  Created on: Aug 17, 2023
 *      Author: yasmeen
 */

#ifndef ADC_H_
#define ADC_H_

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"avr/io.h"

#define ADC_CHANNEL_0  0
#define ADC_CHANNEL_1  1
#define ADC_CHANNEL_2  2
#define ADC_CHANNEL_3  3
#define ADC_CHANNEL_4  4
#define ADC_CHANNEL_5  5
#define ADC_CHANNEL_6  6
#define ADC_CHANNEL_7  7

void ADC_VidInit(void);

u16 ADC_U16GetDigitalValue(u8 Copy_U8ChannelNumber);


#endif /* ADC_H_ */
