#ifndef DIO_H
#define DIO_H

#include"avr/io.h"
#include"STD_TYPES.h"
#include"BIT_MATH.h"


#define DIO_OUTPUT 1
#define DIO_INPUT 0

#define DIO_ALL_OUTPUT 0xFF
#define DIO_ALL_INPUT 0x00

#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3

#define DIO_PIN0 0
#define DIO_PIN1 1
#define DIO_PIN2 2
#define DIO_PIN3 3
#define DIO_PIN4 4
#define DIO_PIN5 5
#define DIO_PIN6 6
#define DIO_PIN7 7

#define DIO_LOW 0
#define DIO_ALL_LOW 0x00

#define DIO_HIGH 1
#define DIO_ALL_HIGH 0xFF

void DIO_VidSetPinDirection( u8 Copy_U8Port , u8 Copy_U8Pin , u8 Copy_U8Direction);
void DIO_VidSetPinValue( u8 Copy_U8Port , u8 Copy_U8Pin , u8 Copy_U8Value);
void DIO_VidSetPortDirection(u8 Copy_U8Port , u8 Copy_U8Direction);
void DIO_VidSetPortValue(u8 Copy_U8Port , u8 Copy_U8Value);
void DIO_VidTogglePinValue(u8 Copy_U8Port , u8 Copy_U8Pin);
u8 DIO_U8Get_PinValue(u8 Copy_U8Port , u8 Copy_U8Pin);

#endif
