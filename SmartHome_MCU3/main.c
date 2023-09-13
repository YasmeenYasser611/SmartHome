/*
 * main.c

 *
 *  Created on: Aug 24, 2023
 *      Author: yasmeen
 */

#include "avr/io.h"
#include"STD_TYPES.h"
#include "BIT_MATH.h"
#include"DIO.h"
#include"avr/delay.h"
#include"SPI.h"
#include"LCD.h"
#include"ADC.h"
#include"EXT_INT0.h"
#include "Smart_Home_Config.h"
#define F_CPU 16000000 UL

void main(void)
{
    u16 LOC_U16DigitalRes, LOC_U16AnalogRES ,LOC_U16TEMP;
    u8 read;
	DIO_VidSetPinDirection(DIO_PORTD,DIO_PIN4,DIO_OUTPUT); //ROOM1
	DIO_VidSetPinDirection(DIO_PORTD,DIO_PIN5,DIO_OUTPUT); //ROOM2
	DIO_VidSetPinDirection(DIO_PORTD,DIO_PIN6,DIO_OUTPUT); //ROOM3
	DIO_VidSetPinDirection(DIO_PORTD,DIO_PIN7,DIO_OUTPUT); //ROOM4
	DIO_VidSetPinDirection(DIO_PORTD,DIO_PIN0,DIO_OUTPUT); //AIR COND
	DIO_VidSetPinDirection(DIO_PORTD,DIO_PIN1,DIO_OUTPUT); //TVC
	DIO_VidSetPinDirection(DIO_PORTD,DIO_PIN2,DIO_INPUT); //SWITCH FOR AIR COND
	DIO_VidSetPinValue(DIO_PORTD,DIO_PIN2,DIO_HIGH);
	EX_INT0VidInit();
	LCD_VidInit();
	SPT_SlaveInit();
	ADC_VidInit();
	while(1)
	{

		read=SPI_u8SlaveTrancieve(10); // read the value from the master MCU
		if(read=='O')
		{
			//ROOM1 ON
			LCD_SEND_COMMAND(0x01);
			LCD_VidSendStrig(" ROOM1 ON");
			DIO_VidSetPinValue(DIO_PORTD,DIO_PIN4,DIO_HIGH);
		}
		else if(read=='*')
		{
			//CLEAR SCREEN
			LCD_SEND_COMMAND(0x01);

		}
		else if(read=='F')
		{
			//ROOM1 OFF
			LCD_SEND_COMMAND(0x01);
			LCD_VidSendStrig(" ROOM1 Turned ");
			LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
	        LCD_VidSendStrig("OFF");
			DIO_VidSetPinValue(DIO_PORTD,DIO_PIN4,DIO_LOW);
		}
		else if(read=='2')
		{
			//ROOM2 ON
			LCD_SEND_COMMAND(0x01);
			LCD_VidSendStrig(" ROOM2 Turned On");
			DIO_VidSetPinValue(DIO_PORTD,DIO_PIN5,DIO_HIGH);
		}
		else if(read=='3')
		{
			//ROOM2 OFF
			LCD_SEND_COMMAND(0x01);
			LCD_VidSendStrig(" ROOM2 Turned ");
			LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
	        LCD_VidSendStrig("OFF");
			DIO_VidSetPinValue(DIO_PORTD,DIO_PIN5,DIO_LOW);
		}
		else if(read=='4')
		{
			//ROOM3 ON
			LCD_SEND_COMMAND(0x01);
			LCD_VidSendStrig(" ROOM3 Turned On");
			DIO_VidSetPinValue(DIO_PORTD,DIO_PIN6,DIO_HIGH);
		}
		else if(read=='5')
		{
			//ROOM3 OFF
			LCD_SEND_COMMAND(0x01);
			LCD_VidSendStrig(" ROOM3 Turned ");
			LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
	        LCD_VidSendStrig("OFF");
			DIO_VidSetPinValue(DIO_PORTD,DIO_PIN6,DIO_LOW);
		}
		else if(read=='6')
		{
			//ROOM4 ON
			LCD_SEND_COMMAND(0x01);
			LCD_VidSendStrig(" ROOM4 Turned On");
			DIO_VidSetPinValue(DIO_PORTD,DIO_PIN7,DIO_HIGH);
		}
		else if(read=='7')
		{
			//ROOM4 OFF
			LCD_SEND_COMMAND(0x01);
			LCD_VidSendStrig(" ROOM4 Turned ");
			LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
	        LCD_VidSendStrig("OFF");
			DIO_VidSetPinValue(DIO_PORTD,DIO_PIN7,DIO_LOW);
		}
		else if(read=='8')
		{
			//TV ON
			LCD_SEND_COMMAND(0x01);
			LCD_VidSendStrig(" TV Turned On");
			DIO_VidSetPinValue(DIO_PORTD,DIO_PIN1,DIO_HIGH);
		}
		else if(read=='9')
		{
			//TV OFF
			LCD_SEND_COMMAND(0x01);
			LCD_VidSendStrig(" TV Turned off");
			DIO_VidSetPinValue(DIO_PORTD,DIO_PIN1,DIO_LOW);
		}
		else if(read=='t')
		{
			//MASTER WANT TO TURN AIR CONDITION ON
	        LCD_SEND_COMMAND(0x01);
			LCD_VidSendStrig("  check room ");
			LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
	        LCD_VidSendStrig("Temp first");
	        _delay_ms(500);
	        //WE WILL CHECK ROOM TEMPERATURE FIRST
			LOC_U16DigitalRes=ADC_U16GetDigitalValue(ADC_CHANNEL_0);
			LOC_U16AnalogRES= (u16)((LOC_U16DigitalRes * 2560UL/*unsigned long*/)/1024); //(2.56\1024)*1000(scale to mv )
			LOC_U16TEMP=LOC_U16AnalogRES/10; //to be goos with the temp sens
			LCD_SEND_COMMAND(0x01);
			LCD_VidSendStrig(" Room Temp=");
			LCD_VidSendNumber(LOC_U16TEMP);
			LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
	        LCD_VidSendStrig("Desired TEMP=");
	        LCD_VidSendNumber(Desired_Temp);
			_delay_ms(500);
			if(LOC_U16TEMP>Desired_Temp)
			{
				//RURN TEMP ON
				LCD_SEND_COMMAND(0x01);
				LCD_VidSendStrig(" Air condition ");
				LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
		        LCD_VidSendStrig("Turned On ");
		        DIO_VidSetPinValue(DIO_PORTD,DIO_PIN0,DIO_HIGH);
			}
			else
			{
				//HE WILL NOT TURN ON THE CINDITIONER BECAUSE THE ROOM TEMP IS LESS THAN THE DESIRED
				LCD_SEND_COMMAND(0x01);
				LCD_VidSendStrig(" ROOM Temp <=");
				LCD_VidSendNumber(Desired_Temp);
				LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
		        LCD_VidSendStrig("conditioning OFF ");
				DIO_VidSetPinValue(DIO_PORTD,DIO_PIN0,DIO_LOW);

			}
		}
		else if(read=='m')
		{
			//AIE CONDITIONER TURN OFF
			LCD_SEND_COMMAND(0x01);
			LCD_VidSendStrig(" air condition ");
			LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
	        LCD_VidSendStrig(" Turned off ");
			DIO_VidSetPinValue(DIO_PORTD,DIO_PIN0,DIO_LOW);
		}
		else
		{
			//ELSE CLEAR THE SCREEN
			LCD_SEND_COMMAND(0x01);

		}


	}

}

ISR(INT0_vect)
{
	//WHEN THE SWITCH TURN ON OR  OFF (ANY CHANGE IN EXT INTERRUPT0)
	static u8 count=0;
	count++;
	if(count%2==0)
	{
		//IF HE PRESS EVEN NUMBER OF PRESSES
		LCD_SEND_COMMAND(0x01);
		DIO_VidSetPinValue(DIO_PORTD,DIO_PIN0,DIO_LOW);
		LCD_VidSendStrig(" Air condition ");
		LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
        LCD_VidSendStrig(" Turned off ");
        _delay_ms(200);
        LCD_SEND_COMMAND(0x01);
	}
	else
	{
		//IF HE PRESS ODD NUMBER OF PRESSED ------- TURN ON THE AIR CONDITIONER
		LCD_SEND_COMMAND(0x01);
		DIO_VidSetPinValue(DIO_PORTD,DIO_PIN0,DIO_HIGH);
		LCD_VidSendStrig(" Air condition ");
		LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
        LCD_VidSendStrig("Turned On ");
	}


}
