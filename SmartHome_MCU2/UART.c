/*
 * UART.c
 *
 *  Created on: Aug 23, 2023
 *      Author: yasmeen
 */

#include"UART.h"


void USART_VIDInit()
{
	u8 Loc_U8UCSRC_VALUE=0b10000000;

	u16 Loc_U16BaudRate=BAUD_RATE;
	//TO SET UP THE BAUD RATE TO 9600 at frequency 16MHz
	UBRRL=(u8)Loc_U16BaudRate;
	UBRRH=(u8)(Loc_U16BaudRate>>8);

	//1-UCSRA REGISTER
	//normal speed NOT DOUBLE
	CLR_BIT(UCSRA,U2X);
	//DISABLE MULTI PROCESSOR MODE
	CLR_BIT(UCSRA,MPCM);
	                    //----------------------------
	//2-UCSRB  register
	//WE USE POLLING SYSTEM NOT INTERRUT (IN case of useage interrupt we need to use the GIA)
	//Rx and TX ENABLE
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);

	//TO SELECT CHAR SIZE (8 BIT)
	CLR_BIT(UCSRB,UCSZ2);
	SET_BIT(Loc_U8UCSRC_VALUE,UCSZ0);
	SET_BIT(Loc_U8UCSRC_VALUE,UCSZ1);
	           //------------------------------
	//3-UCSAC REGISTER VALUE
	//SELECT ASYNCH
	CLR_BIT(Loc_U8UCSRC_VALUE,UMSEL);
	//DISABLE PARITY
	CLR_BIT(Loc_U8UCSRC_VALUE,UPM0);
	CLR_BIT(Loc_U8UCSRC_VALUE,UPM1);
	//TWO STOP BITS
	SET_BIT(Loc_U8UCSRC_VALUE,USBS);

	//UPDATE UCSRC REGISTER
	UCSRC=Loc_U8UCSRC_VALUE;

}

void USART_VIDSendChar(u8 copy_u8char)
{
	//check if the UDR register is ready to send
	while(GET_BIT(UCSRA,UDRE)==0);  //POLLINR waiting for the flag the register is ready
	UDR=copy_u8char; //PUT THE 8BITS in the UDR register

}

u8 USART_U8RECIEVEChar()
{
	u8 Loc_U8character;
	//check if the receive operation is complete (once the end bit reaches )
	while(GET_BIT(UCSRA,RXC)==0);  //POLLINR waiting for tHE receive OPERATION IS COMPLETE
	Loc_U8character=UDR;
	return Loc_U8character;

}
