/*
 * Timer0.C

 *
 *  Created on: Aug 20, 2023
 *      Author: yasmeen
 *       SWC:Timers
 *      Version:1.2
 */

#include "Timer1.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "avr/io.h"
#include "avr/interrupt.h"


void Timers_VidTimer1Init()
{
	                           /*1-Select mode*/

#if Timer1_Mode_Select == Timer1_NORMAL_Mode0

	CLR_BIT(TCCR1A,WGM10);
	CLR_BIT(TCCR1A,WGM11);

	CLR_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);


#elif Timer1_Mode_Select == Timer1_PWM_PHASECORRECT_8BIT_Mode1

	SET_BIT(TCCR1A,WGM10);
	CLR_BIT(TCCR1A,WGM11);

	CLR_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);

#elif Timer1_Mode_Select == Timer1_PWM_PHASECORRECT_9BIT_Mode2

	CLR_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);

	CLR_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);

#elif Timer1_Mode_Select == Timer1_PWM_PHASECORRECT_10BIT_Mode3

	SET_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);

	CLR_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);

#elif Timer1_Mode_Select == Timer1_CTC1_Mode4

	CLR_BIT(TCCR1A,WGM10);
	CLR_BIT(TCCR1A,WGM11);

	SET_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);

#elif Timer1_Mode_Select == Timer1_FASTPWM_8BIT_Mode5

#elif Timer1_Mode_Select == Timer1_FASTPWM_9BIT_Mode6

#elif Timer1_Mode_Select == Timer1_FASTPWM_10BIT_Mode7

#elif Timer1_Mode_Select == Timer1_PWM_PHASEANDFREQUENCYCORRECT1__Mode8

#elif Timer1_Mode_Select == Timer1_PWM_PHASEANDFREQUENCYCORRECT2__Mode9

#elif Timer1_Mode_Select == Timer1_PWM_PHASECORRECT1__Mode10

#elif Timer1_Mode_Select == Timer1_PWM_PHASECORRECT2__Mode11

#elif Timer1_Mode_Select == Timer1_CTC2_Mode12

#elif Timer1_Mode_Select == Timer1_RESERVED13

#elif Timer1_Mode_Select == Timer1_FastPWM1_MODE14

	CLR_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);

	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);

#elif Timer1_Mode_Select == Timer1_FastPWM2_Mode15

	SET_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);

	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
#endif

	//2-SETUP  HARDWARE PIN

	CLR_BIT(TCCR1A,COM1A0);
	SET_BIT(TCCR1A,COM1A1);

	CLR_BIT(TCCR1A,COM1B0);
	SET_BIT(TCCR1A,COM1B1);

	//3-SET UP  ICR1

	//ICR1=19999; (IN 8 MHZ)
	  ICR1=39999;  //(IN 16MHZ)
	//4-SET UP COMPARE MATCH VALUE

	OCR1A=3000;  //90 DEGREE ANGLE WE WILL CHANGE HERE (IN 16MHZ IT IS FROM 1999:3999)
	OCR1B=3000;
	                                           //5-PRESCALE

	                        /* 5-pre_scalar */  //to enable the timer after all the previous steps(LAST STEP)

#if TIMER1_PRESCALE_Select == TIMER1_TIMER_OFF


#elif TIMER1_PRESCALE_Select == TIMER1_NO_PRESCALE


#elif TIMER1_PRESCALE_Select == TIMER1_PRESCALE_8

	CLR_BIT(TCCR1B, CS10);
	SET_BIT(TCCR1B, CS11);
	CLR_BIT(TCCR1B, CS12);

#elif TIMER0_PRESCALE_Select == TIMER1_PRESCALE_64

#elif TIMER0_PRESCALE_Select == TIMER1_PRESCALE_256

#elif TIMER0_PRESCALE_Select == TIMER1_PRESCALE_1024

#endif
}


void Timer1_VidTimer1SetOCR1(u16 Copy_u16Ocr1Value)
{
	OCR1A=Copy_u16Ocr1Value;
}


void Timer1_VidTimer1SetOCR1B(u16 Copy_u16Ocr1Value)
{
	OCR1B=Copy_u16Ocr1Value;
}
