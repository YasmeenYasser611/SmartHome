/*
 * main.c

 *
 *  Created on: Sep , 2023
 *      Author: yasmeen yasser mohamed mohamed
 *      smart home system
 *      iti graduation project
 */

#include"LCD.h"
#include"KPD.h"
#include "Timer1.h"
#include "DIO.h"
#include"avr/interrupt.h"
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"UART.h"
#include"Smart_Home_Config.h"

void main(void)
{
	u16 pass=0;
	u8 read=0xFF , Try , counter=0 , flag=1 ,flag2=1, Temp;
	KPD_Init();
	LCD_VidInit();
	Timers_VidTimer1Init();
	USART_VIDInit();
	DIO_VidSetPinDirection(DIO_PORTA,DIO_PIN5 ,DIO_OUTPUT); //block led
	DIO_VidSetPinDirection(DIO_PORTA,DIO_PIN6 ,DIO_OUTPUT);//Guest led
	DIO_VidSetPinDirection(DIO_PORTA,DIO_PIN7 ,DIO_OUTPUT);//admin led
	DIO_VidSetPinDirection(DIO_PORTD, DIO_PIN5, DIO_OUTPUT);//door
	DIO_VidSetPinDirection(DIO_PORTD, DIO_PIN4, DIO_OUTPUT);//GARAG
	DIO_VidSetPinDirection(DIO_PORTA, DIO_PIN4, DIO_OUTPUT);//BUZZER
	DIO_VidSetPinDirection(DIO_PORTD, DIO_PIN3, DIO_OUTPUT);//out led1
	DIO_VidSetPinDirection(DIO_PORTA, DIO_PIN2, DIO_OUTPUT);//out led2
	DIO_VidSetPinDirection(DIO_PORTD,DIO_PIN0,DIO_INPUT); //RX
	DIO_VidSetPinDirection(DIO_PORTD,DIO_PIN1,DIO_OUTPUT); //TX

	//configure ADC IN interrupt
	ADCSRA = 0x8F;
	ADMUX=0x40;
	SET_BIT(SREG,7);
	SET_BIT(ADCSRA,ADSC);

    //start the smart home system
	LCD_VidSendStrig("Welcome To Smart");
	LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
	LCD_VidSendStrig("Home System");
	_delay_ms(100);
	LCD_SEND_COMMAND(0x01);
	//select mode page
	LCD_VidSendStrig(" Select Mode:");
	LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
	LCD_VidSendStrig("0:Admin 1:Guest");
	while(1)
	{
		read= KPD_u8GetPressedKey();
		if(read!=0xFF)
		{
			if(read=='0')
			{
				//he select admin mode , so he should log in first
				LCD_SEND_COMMAND(0x01);
				LCD_VidSendStrig(" Admin Mode:");
			    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
				LCD_VidSendStrig("Enter Pass:");
				while(1)
				{

					while(1)
					{
						read= KPD_u8GetPressedKey();
						 if(read!=0xFF)
						 {
							 if(read!='=')
							 {
								 LCD_SEND_Char('*');
								 //he still writing the password
								 pass = (pass * 10) + read;
								 break;
							 }
							 else if(read=='=')
							 {
								 //he finishing writing the password
								 if(pass==Yasmeen_Pass)
								 {
									 DIO_VidSetPinValue(DIO_PORTA,DIO_PIN7,DIO_HIGH);//admin led will on
									 LCD_SEND_COMMAND(0x01);
									 //admin yasmeen here
									 LCD_VidSendStrig(" Right Password");
									 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
									 LCD_VidSendStrig("welcome yasmeen");
									 _delay_ms(400);
									 LCD_SEND_COMMAND(0x01);
									 LCD_VidSendStrig(" 0:Home");
									 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColTwo);
									 LCD_VidSendStrig("1:Garag");
									 while(1)
									 {
									     read= KPD_u8GetPressedKey();
										 if(read!=0xFF)
										 {
											 if(read=='0')
											 {
												 //home door will open for 1m
												 LCD_SEND_COMMAND(0x01);
												 LCD_VidSendStrig("  Home Door ");
												 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
												 LCD_VidSendStrig("  Will OPEN");
												 Timer1_VidTimer1SetOCR1(3999); //open the door
												 _delay_ms(1000);
												 LCD_SEND_COMMAND(0x01);
												 LCD_VidSendStrig("  Home Door ");
												 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
												 LCD_VidSendStrig("Will close again");
												 Timer1_VidTimer1SetOCR1(3000);//close the door again
												 _delay_ms(100);
												 USART_VIDSendChar(1); //TO TELL HOME that yasmeen is at home
												 DIO_VidSetPinValue(DIO_PORTA,DIO_PIN7 ,DIO_LOW); //admin led off
												 LCD_SEND_COMMAND(0x01);
												 LCD_VidSendStrig(" Select Mode:");
												 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
												 LCD_VidSendStrig("0:Admin 1:Guest");
												 flag=0;
												 flag2=0;
												 counter=0;
												 pass=0;
												 break;
											 }
											 else if(read==1)
											 {
												 //garag door will open for 1min
												 LCD_SEND_COMMAND(0x01);
												 LCD_VidSendStrig(" Garag Door ");
												 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
												 LCD_VidSendStrig(" Will OPEN");
												 Timer1_VidTimer1SetOCR1B(3999); //open the door
												 _delay_ms(1000);
												 LCD_SEND_COMMAND(0x01);
												 LCD_VidSendStrig("  Garag Door ");
												 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
												 LCD_VidSendStrig("Will close again");
												 Timer1_VidTimer1SetOCR1B(3000);//close the GARAG again
												 _delay_ms(100);
												 DIO_VidSetPinValue(DIO_PORTA,DIO_PIN7 ,DIO_LOW); //admin led off
												 LCD_SEND_COMMAND(0x01);
												 LCD_VidSendStrig(" Select Mode:");
												 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
												 LCD_VidSendStrig("0:Admin 1:Guest");
												 flag=0;
												 flag2=0;
												 counter=0;
												 pass=0;
												 break;
											 }
											 else
											 {
													LCD_SEND_COMMAND(0x01);
													LCD_VidSendStrig(" wrong choice");
												    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
													LCD_VidSendStrig("choose again");
													_delay_ms(500);
													LCD_SEND_COMMAND(0x01);
													LCD_VidSendStrig(" 0:Home");
													LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColTwo);
												    LCD_VidSendStrig("1:Garag");

											 }
										 }


									 }

								 }
								 else if (pass==Yousef_Pass)
								 {
									 //admin yousef here
									 DIO_VidSetPinValue(DIO_PORTA,DIO_PIN7,DIO_HIGH);//admin led will on
									 LCD_SEND_COMMAND(0x01);
									 //admin yousef here
									 LCD_VidSendStrig(" Right Password");
									 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
									 LCD_VidSendStrig("Welcome Yousef");
									 _delay_ms(500);
									 LCD_SEND_COMMAND(0x01);
									 LCD_VidSendStrig(" 0:Home");
									 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColTwo);
									 LCD_VidSendStrig("1:Garag");
									 while(1)
									 {
									     read= KPD_u8GetPressedKey();
										 if(read!=0xFF)
										 {
											 if(read=='0')
											 {
												 //open the door
												 LCD_SEND_COMMAND(0x01);
												 LCD_VidSendStrig("  Home Door ");
												 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
												 LCD_VidSendStrig("  Will OPEN");
												 Timer1_VidTimer1SetOCR1(3999); //open the door
												 _delay_ms(1000);
												 LCD_SEND_COMMAND(0x01);
												 LCD_VidSendStrig("  Home Door ");
												 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
												 LCD_VidSendStrig("Will close again");
												 Timer1_VidTimer1SetOCR1(3000);//close the door again
												 _delay_ms(500);
												 USART_VIDSendChar(2);
												 DIO_VidSetPinValue(DIO_PORTA,DIO_PIN7 ,DIO_LOW); //admin led off
												 LCD_SEND_COMMAND(0x01);
												 LCD_VidSendStrig(" Select Mode:");
												 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
												 LCD_VidSendStrig("0:Admin 1:Guest");
												 flag=0;
												 flag2=0;
												 counter=0;
												 pass=0;
												 break;
											 }
											 else if(read==1)
											 {
												 //open the garag
												 LCD_SEND_COMMAND(0x01);
												 LCD_VidSendStrig(" Garag Door ");
												 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
												 LCD_VidSendStrig(" Will OPEN");
												 Timer1_VidTimer1SetOCR1B(3999); //open the door
												 _delay_ms(1000);
												 LCD_SEND_COMMAND(0x01);
												 LCD_VidSendStrig("  Garag Door ");
												 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
												 LCD_VidSendStrig("Will close again");
												 Timer1_VidTimer1SetOCR1B(3000);//close the GARAG again
												 _delay_ms(500);
												 DIO_VidSetPinValue(DIO_PORTA,DIO_PIN7 ,DIO_LOW); //admin led off
												 LCD_SEND_COMMAND(0x01);
												 LCD_VidSendStrig(" Select Mode:");
												 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
												 LCD_VidSendStrig("0:Admin 1:Guest");
												 flag=0;
												 flag2=0;
												 counter=0;
												 pass=0;
												 break;
											 }
											 else
											 {
												    //wrong entry
													LCD_SEND_COMMAND(0x01);
													LCD_VidSendStrig(" wrong choice");
												    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
													LCD_VidSendStrig("choose again");
													_delay_ms(500);
													LCD_SEND_COMMAND(0x01);
													LCD_VidSendStrig(" 0:Home");
													LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColTwo);
												    LCD_VidSendStrig("1:Garag");

											 }
										 }


									 }

								 }
								 else
								 {
									 //wring password he take atemp
									 LCD_SEND_COMMAND(0x01);
									 Try = Attempts;
									 counter++;
									 if(counter<Attempts)
									 {
										 LCD_VidSendStrig(" Wrong Password");
										 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
										 LCD_VidSendStrig("Tries Left:");
										 Temp =(Try-counter);
										 LCD_VidSendNumber(Temp);
										 _delay_ms(500);
										 LCD_SEND_COMMAND(0x01);
										 LCD_VidSendStrig(" Admin Mode:");
										 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
										 LCD_VidSendStrig("Enter Pass:");
										 pass=0;
										 break;


									 }
									 else
									 {
										 //block user
										 DIO_VidSetPinValue(DIO_PORTA,DIO_PIN5 ,DIO_HIGH);
										 LCD_VidSendStrig(" login blocked");
										 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
										 LCD_VidSendStrig("wait 2 minutes");
										 _delay_ms(1000);
										 DIO_VidSetPinValue(DIO_PORTA,DIO_PIN5 ,DIO_LOW);
										 LCD_SEND_COMMAND(0x01);
										 LCD_VidSendStrig(" Select Mode:");
										 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
										 LCD_VidSendStrig("0:Admin 1:Guest");
										 flag=0;
										 counter=0;
										 pass=0;
										 break;
									 }


								 }

							 }


						 }
							if(flag2==0)
							{
								flag2=1;
								break;
							}



					}//end of while 2
					if(flag==0)
					{
						flag=1;
						break;
					}
			      }


			}
		else if(read==1)
			{
				//he select GUEST mode , so he should log in first
				LCD_SEND_COMMAND(0x01);
				LCD_VidSendStrig(" Guest Mode:");
			    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
				LCD_VidSendStrig("Enter Pass:");
				while(1)
				{

					while(1)
					{
						read= KPD_u8GetPressedKey();
						 if(read!=0xFF)
						 {
							 if(read!='=')
							 {
								 LCD_SEND_Char('*');
								 //he still writing the password
								 pass = (pass * 10) + read;
								 break;
							 }
							 else if(read=='=')
							 {
								 //he finishing writing the password
								 if(pass==Yasser_Pass)
								 {
									 DIO_VidSetPinValue(DIO_PORTA,DIO_PIN6,DIO_HIGH);//guest led will on
									 LCD_SEND_COMMAND(0x01);
									 //guest yasser here
									 LCD_VidSendStrig(" Right Password");
									 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
									 LCD_VidSendStrig("welcome yasser");
									 _delay_ms(100);
									 LCD_SEND_COMMAND(0x01);
									 LCD_VidSendStrig(" bell will ring");
									 USART_VIDSendChar(3);
									 DIO_VidSetPinValue(DIO_PORTA, DIO_PIN4,DIO_HIGH);//BUZZER ON
									 _delay_ms(1000);
									 LCD_SEND_COMMAND(0x01);
									 LCD_VidSendStrig(" bell will");
									 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
									 LCD_VidSendStrig(" Turn OFF!!!!");
									 DIO_VidSetPinValue(DIO_PORTA, DIO_PIN4,DIO_LOW);//BUZZER OFF
									 DIO_VidSetPinValue(DIO_PORTA,DIO_PIN6,DIO_LOW);//guest led will OFF
									 _delay_ms(400);
									 LCD_SEND_COMMAND(0x01);
									 LCD_VidSendStrig(" Select Mode:");
									 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
									 LCD_VidSendStrig("0:Admin 1:Guest");
									 flag=0;
									 flag2=0;
									 counter=0;
									 pass=0;

								 }
								 else
								 {
									 //wring password he take atemp
									 LCD_SEND_COMMAND(0x01);
									 Try = Attempts;
									 counter++;
									 if(counter<Attempts)
									 {
										 LCD_VidSendStrig(" Wrong Password");
										 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
										 LCD_VidSendStrig("Tries Left:");
										 Temp =(Try-counter);
										 LCD_VidSendNumber(Temp);
										 _delay_ms(1000);
										 LCD_SEND_COMMAND(0x01);
										 LCD_VidSendStrig(" GUEST Mode:");
										 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
										 LCD_VidSendStrig("Enter Pass:");
										 pass=0;
										 break;


									 }
									 else
									 {
										 //block user
										 DIO_VidSetPinValue(DIO_PORTA,DIO_PIN5 ,DIO_HIGH);
										 LCD_VidSendStrig(" login blocked");
										 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
										 LCD_VidSendStrig("wait 2 minutes");
										 _delay_ms(2000);
										 DIO_VidSetPinValue(DIO_PORTA,DIO_PIN5 ,DIO_LOW);
										 LCD_SEND_COMMAND(0x01);
										 LCD_VidSendStrig(" Select Mode:");
										 LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
										 LCD_VidSendStrig("0:Admin 1:Guest");
										 flag=0;
										 counter=0;
										 pass=0;
										 break;
									 }


								 }

							 }


						 }
							if(flag2==0)
							{
								flag2=1;
								break;
							}



					}//end of while 2
					if(flag==0)
					{
						flag=1;
						break;
					}
			      }


			}
		else
		{
			//wrong entry
			LCD_SEND_COMMAND(0x01);
			LCD_VidSendStrig(" wrong choice");
		    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
			LCD_VidSendStrig("choose again");
			_delay_ms(500);
			LCD_SEND_COMMAND(0x01);
			LCD_VidSendStrig(" Select Mode:");
			LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
			LCD_VidSendStrig("0:Admin 1:Guest");

		}

		}

	}




}



ISR(ADC_vect)
{
	//ISR for ADC IN interrupt mode for the LDR
	u16 LOC_U16DigitalRes, LOC_U16AnalogRES ,LOC_U16Light,LDR;

	LOC_U16DigitalRes=ADC;

	LOC_U16AnalogRES= (u16)((LOC_U16DigitalRes *5000UL)/1024);

	LOC_U16Light=LOC_U16AnalogRES;

	LDR=(1*5000 -LOC_U16Light*1)/LOC_U16Light;
	if(LDR>200) //dark we need 2 leds
	{
	 DIO_VidSetPinValue(DIO_PORTD,DIO_PIN3,DIO_HIGH);
	 DIO_VidSetPinValue(DIO_PORTD,DIO_PIN2,DIO_HIGH);

	}
	else if(LDR>55 && LDR<=200)// one led
	{
		 DIO_VidSetPinValue(DIO_PORTD,DIO_PIN3,DIO_HIGH);
		 DIO_VidSetPinValue(DIO_PORTD,DIO_PIN2,DIO_LOW);
		 _delay_ms(500);

	}
	else if(LDR>=0 && LDR<=55) // no leds on
	{
		 DIO_VidSetPinValue(DIO_PORTD,DIO_PIN3,DIO_LOW);
		 DIO_VidSetPinValue(DIO_PORTD,DIO_PIN2,DIO_LOW);
		 _delay_ms(500);
	}
    //adc start convertion again
	SET_BIT(ADCSRA,ADSC);
}
