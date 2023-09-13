#include"LCD.h"
void LCD_SEND_COMMAND(u8 Copy_U8LcdCommand)
{
	DIO_VidSetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_LOW);
	DIO_VidSetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_LOW);
	DIO_VidSetPortValue(LCD_DATA_PORT,Copy_U8LcdCommand);
	DIO_VidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_HIGH);
	_delay_us(1);
	DIO_VidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_LOW);
	//_delay_us(1);

}
void LCD_SEND_Char(u8 Copy_U8LcdData) //to send character
{
	DIO_VidSetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_HIGH);
	DIO_VidSetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_LOW);
	DIO_VidSetPortValue(LCD_DATA_PORT,Copy_U8LcdData);
	DIO_VidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_HIGH);
	_delay_us(1);
	DIO_VidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_LOW);
	//_delay_us(1);

}
void LCD_VidInit(void)
{
	DIO_VidSetPortDirection(LCD_DATA_PORT,DIO_ALL_OUTPUT);
	DIO_VidSetPinDirection(LCD_EN_PORT,LCD_EN_PIN,DIO_OUTPUT);
	DIO_VidSetPinDirection(LCD_RW_PORT,LCD_RW_PIN,DIO_OUTPUT);
	DIO_VidSetPinDirection(LCD_RS_PORT,LCD_RS_PIN,DIO_OUTPUT);
	//DELAY MORE THAN 30 MS
	_delay_ms(35);

	LCD_SEND_COMMAND(0b00111000); //0011NFXX ,    N=HOW MANY LINES YOU WANT TO USE(1)  ,   F= FONT SIZE(0=5*7)
	_delay_us(50); // DELAY MORE THAN 39 MICRO SEC
	LCD_SEND_COMMAND(0b00001100);  //00001DCB , C = LIKE FLAF WHEN TO STOP(OFF) , B= BLANKING , D= DISPLAY
	_delay_us(50);
	LCD_SEND_COMMAND(0b00000001);
	_delay_ms(2); // delay more than 1.5 ms
	LCD_SEND_COMMAND(0b00000110); //write from left to right

}

void LCD_VidSendStrig(u8 * Copy_Pu8String)
{

	while(*Copy_Pu8String != '\0' ) // \0 is the last element in the arrray
	{
		LCD_SEND_Char(*Copy_Pu8String);
		Copy_Pu8String++;

	}
}

void LCD_VidGoTOLocation(u8 Copy_U8RowNumber  , u8 Copy_U8ColNumber)
{
	_delay_ms(2);
	switch(Copy_U8RowNumber)
		{

		    case LCD_RowOne: LCD_SEND_COMMAND(LCD_RowOneStart+ Copy_U8ColNumber);
		                     break;
		    case LCD_RowTwo: LCD_SEND_COMMAND(LCD_RowTwoStart + Copy_U8ColNumber);
		                     break;
		}

}

void LCD_VidSendNumber(u32 Copy_U32Number)
{
	u8 nums[32];
	itoa(Copy_U32Number, nums , 10);  //convert integer data type to string datatype ,10 (base-DEC)
	LCD_VidSendStrig(nums);

}
