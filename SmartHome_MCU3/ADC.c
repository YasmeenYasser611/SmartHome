/*
 * ADC.c
 *
 *  Created on: Aug 17, 2023
 *      Author: yasmeen
 */


#include"ADC.h"


void ADC_VidInit(void)
{
	//1-ADMUX
	//select ref  2.56v at Vref
	SET_BIT(ADMUX,REFS0);
	SET_BIT(ADMUX,REFS1);


	//RIRHT ADJUST (ALL 10 BIT )
	CLR_BIT(ADMUX, ADLAR);

	//NO aoto trigger (stop)
	CLR_BIT(ADCSRA,ADATE);

	//PRESCALE from 50khz to 200khz       in my case 125khz with f=16mhz and prescale 128
	SET_BIT(ADCSRA,ADPS0);
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);

	//2-ADCSRA
	//ADC ENABLE the last thing
	SET_BIT(ADCSRA,ADEN);
}

u16 ADC_U16GetDigitalValue(u8 Copy_U8ChannelNumber)
{
	u16 Loc_U16DiditalValue; // WE WILL STORE THE DIGITAL VALUE IN IT
	//CHANNEL SELECTION (SINGLE ENDED)
	ADMUX &= 0b11100000;  //TO SAVE the state of the last 3 bits and other bits is 0
	ADMUX |= Copy_U8ChannelNumber;

	//ADC start convertion in the single convertion mode
	SET_BIT(ADCSRA,ADSC);

	//TO CHECK IF IT FINISH THE CONVERSION  (WAIT_FLAG) ADIF
	while((GET_BIT(ADCSRA,ADIF))==0);     //polling (I CHECK THE flag )

	// we should clear the flag after the conversion
	SET_BIT(ADCSRA,ADIF);

	//OUTPUT REGISTER IS 3- ADC because we use righr adjust

	Loc_U16DiditalValue=ADC;
	return Loc_U16DiditalValue;
}

//4-SFIOR if we use auto trigger ----- but we will not use it now

