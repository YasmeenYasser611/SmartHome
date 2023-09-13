/*
 * UART.h
 *
 *  Created on: Aug 23, 2023
 *      Author: yasmeen
 */

#ifndef UART_H_
#define UART_H_

#include"DIO.h"
#include"BIT_MATH.h"
#include"STD_TYPES.h"
#include"avr/io.h"

#define BAUD_RATE 103

void USART_VIDInit();
void USART_VIDSendChar(u8 copy_u8char);
u8 USART_U8RECIEVEChar();

#endif /* UART_H_ */
