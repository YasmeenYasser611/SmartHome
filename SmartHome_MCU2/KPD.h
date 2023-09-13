#ifndef KPD_H_
#define KPD_H_

#include"avr/io.h"
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO.h"
#include"avr/delay.h"

#define KPD_ROW_NUM 4
#define KPD_COL_NUM 4

#define ROW1 DIO_PIN0
#define ROW2 DIO_PIN1
#define ROW3 DIO_PIN2
#define ROW4 DIO_PIN3

#define COL1 DIO_PIN4
#define COL2 DIO_PIN5
#define COL3 DIO_PIN6
#define COL4 DIO_PIN7
#define KPD_PORT            DIO_PORTC
#define KPD_PORT_DIRECTION   0xF0   //0b 1111 0000

#define KPD_ARR  {{7,8,9,'/'},{4,5,6,'*'},{1,2,3,'-'},{'C','0','=','+'}};

void KPD_Init(void);
//u8 KPD_U8GETPressedKey(void);
u8 KPD_u8GetPressedKey(void);
#endif /* KPD_H_ */
