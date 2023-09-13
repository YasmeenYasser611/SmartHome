#ifndef LCD_H
#define LCD_H

#include"avr/io.h"
#include"stdlib.h"
#include"STD_TYPES.h"
#include"DIO.h"
#include"avr/delay.h"

#define LCD_RS_PIN  DIO_PIN2
#define LCD_RS_PORT DIO_PORTA

#define LCD_RW_PIN  DIO_PIN3
#define LCD_RW_PORT DIO_PORTA

#define LCD_EN_PIN DIO_PIN4
#define LCD_EN_PORT DIO_PORTA

#define LCD_DATA_PORT DIO_PORTC

#define LCD_RowOne 1
#define LCD_RowTwo 2

#define LCD_ColOne 0x00
#define LCD_ColTwo 0x01
#define LCD_ColThree 0x02
#define LCD_ColFour 0x03
#define LCD_ColFive 0x04
#define LCD_ColSix 0x05
#define LCD_ColSeven 0x06
#define LCD_ColEight 0x07
#define LCD_ColNine 0x08
#define LCD_ColTen 0x09
#define LCD_ColEleven 0x0A
#define LCD_ColTwelve 0x0B
#define LCD_ColThirteen 0x0C
#define LCD_ColFourteen 0x0D
#define LCD_ColFiveteen 0x0E
#define LCD_ColSixteen 0x0F


#define LCD_RowOneStart 0x80
#define LCD_RowTwoStart 0xc0


void LCD_SEND_COMMAND(u8 Copy_U8LcdCommand);
void LCD_SEND_Char(u8 Copy_U8LcdData);
void LCD_VidInit(void);
void LCD_VidSendStrig(u8 * Copy_Pu8String);
void LCD_VidGoTOLocation(u8 Copy_U8RowNumber  , u8 Copy_U8ColNumber);
void LCD_VidSendNumber(u32 Copy_U32Number);


#endif
