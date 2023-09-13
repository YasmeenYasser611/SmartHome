/*
 * Timer0.h
 *
 *  Created on: Aug 20, 2023
 *      Author: yasmeen
 *       SWC:Timers
 *      Version:1.2
 */
#ifndef TIMERS_H
#define TIMERS_H

#include "STD_TYPES.h"
//to select the timer mode

void Timers_VidTimer1Init();
void Timer1_VidTimer1SetOCR1(u16 Copy_u16Ocr1Value);
void Timer1_VidTimer1SetOCR1B(u16 Copy_u16Ocr1Value);

#define Timer1_NORMAL_Mode0                                                0
#define Timer1_PWM_PHASECORRECT_8BIT_Mode1                                 1
#define Timer1_PWM_PHASECORRECT_9BIT_Mode2                                 2
#define Timer1_PWM_PHASECORRECT_10BIT_Mode3                                3
#define Timer1_CTC1_Mode4                                                  4
#define Timer1_FASTPWM_8BIT_Mode5                                          5
#define Timer1_FASTPWM_9BIT_Mode6                                          6
#define Timer1_FASTPWM_10BIT_Mode7                                         7
#define Timer1_PWM_PHASEANDFREQUENCYCORRECT1__Mode8                        8
#define Timer1_PWM_PHASEANDFREQUENCYCORRECT2__Mode9                        9
#define Timer1_PWM_PHASECORRECT1__Mode10                                   10
#define Timer1_PWM_PHASECORRECT2__Mode11                                   11
#define Timer1_CTC2_Mode12                                                 12
#define Timer1_RESERVED13                                                  13
#define Timer1_FastPWM1_MODE14                                             14
#define Timer1_FastPWM2_Mode15                                             15

//we could select which mode
#define Timer1_Mode_Select  Timer1_FastPWM1_MODE14
//-----------------------------------------------------------------------

//FOR PRESCALE SELECT

#define TIMER1_TIMER_OFF         0
#define TIMER1_NO_PRESCALE       1
#define TIMER1_PRESCALE_8        2
#define TIMER1_PRESCALE_64       3
#define TIMER1_PRESCALE_256      4
#define TIMER1_PRESCALE_1024     5

#define TIMER1_PRESCALE_Select  TIMER1_PRESCALE_8
//------------------------------------------------------------------------------------




#endif
