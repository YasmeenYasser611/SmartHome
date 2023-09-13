/*
 * SPI.C
 *
 *  Created on: Aug 24, 2023
 *      Author: yasmeen
 */

#include"avr/io.h"

#include"BIT_MATH.h"
#include"STD_TYPES.h"
#include"DIO.h"
#include"SPI.h"

void SPI_MasterInit(void)
{
DIO_VidSetPinDirection(DIO_PORTB,DIO_PIN5,DIO_OUTPUT); //MOSI
DIO_VidSetPinDirection(DIO_PORTB,DIO_PIN6,DIO_INPUT); //MISO

DIO_VidSetPinDirection(DIO_PORTB,DIO_PIN7,DIO_OUTPUT);//CLOCK
DIO_VidSetPinDirection(DIO_PORTB,DIO_PIN4,DIO_OUTPUT); //CS
DIO_VidSetPinValue(DIO_PORTB,DIO_PIN4,DIO_HIGH);

SPCR=0b01011110;
/*
 * pin7---------interrupt disable
 * pin6    === enable spi
 * pin5    === to send lsb first
 * pin4    ===  master  =1
 * pin3 -----cpol
 * pin2-------cphase
 * pin1,pin0  -------  prescale  64
 * */


}
u8 SPI_u8MasterTrancieve(u8 Data)
{
	DIO_VidSetPinValue(DIO_PORTB,DIO_PIN4,DIO_LOW);
	SPDR= Data;
	while(GET_BIT(SPSR,SPIF)==0);
	DIO_VidSetPinValue(DIO_PORTB,DIO_PIN4,DIO_HIGH);
	return SPDR;
}
void SPT_SlaveInit(void)
{
	DIO_VidSetPinDirection(DIO_PORTB,DIO_PIN5,DIO_INPUT);
	DIO_VidSetPinDirection(DIO_PORTB,DIO_PIN6,DIO_OUTPUT);

	DIO_VidSetPinDirection(DIO_PORTB,DIO_PIN7,DIO_INPUT);
	DIO_VidSetPinDirection(DIO_PORTB,DIO_PIN4,DIO_INPUT);
	SPCR=0b01001110;
	/*
	 * pin7---------interrupt disable
	 * pin6    === enable spi
	 * pin5    === to send lsb first
	 * pin4    ===  slave  =0
	 * pin3 -----cpol
	 * pin2-------cphase
	 * pin1,pin0  -------  prescale  64
	 * */
}

u8 SPI_u8SlaveTrancieve(u8 Data)
{

	SPDR= Data;
	while(GET_BIT(SPSR,SPIF)==0);
	return SPDR;
}
