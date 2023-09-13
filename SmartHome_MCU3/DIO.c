#include"DIO.h"

//function for direction
void DIO_VidSetPinDirection( u8 Copy_U8Port , u8 Copy_U8Pin , u8 Copy_U8Direction)    //preph name_returntype_funcName
{
	switch(Copy_U8Direction)
	{
	    case DIO_INPUT:
	      switch(Copy_U8Port)
	      {
	    	case DIO_PORTA:
	    		CLR_BIT( DDRA , Copy_U8Pin);
	    		break;
	    	case DIO_PORTB:
	    		CLR_BIT( DDRB , Copy_U8Pin);
	    		break;
	    	case DIO_PORTC:
	    		CLR_BIT( DDRC , Copy_U8Pin);
	    	    break;
	    	case DIO_PORTD:
	    		CLR_BIT( DDRD , Copy_U8Pin);
	    	    break;

	      }
	      break;
	    case DIO_OUTPUT:
	    	switch(Copy_U8Port)
	    		    {
	    		    	case DIO_PORTA:
	    		    		SET_BIT( DDRA , Copy_U8Pin);
	    		    		break;
	    		    	case DIO_PORTB:
	    		    		SET_BIT( DDRB , Copy_U8Pin);
	    		    		break;
	    		    	case DIO_PORTC:
	    		    		SET_BIT( DDRC , Copy_U8Pin);
	    		    	    break;
	    		    	case DIO_PORTD:
	    		    		SET_BIT( DDRD , Copy_U8Pin);
	    		    	    break;
	    		    }
	    	break;
	}
}
//function for value
void DIO_VidSetPinValue( u8 Copy_U8Port , u8 Copy_U8Pin , u8 Copy_U8Value)
{

	switch(Copy_U8Value)
	{
	    case DIO_LOW:
	      switch(Copy_U8Port)
	      {
	    	case DIO_PORTA:
	    		CLR_BIT( PORTA , Copy_U8Pin);
	    		break;
	    	case DIO_PORTB:
	    		CLR_BIT( PORTB , Copy_U8Pin);
	    		break;
	    	case DIO_PORTC:
	    		CLR_BIT( PORTC , Copy_U8Pin);
	    	    break;
	    	case DIO_PORTD:
	    		CLR_BIT( PORTD , Copy_U8Pin);
	    	    break;

	      }
	      break;
	    case DIO_HIGH:
	    	switch(Copy_U8Port)
	    		    {
	    		    	case DIO_PORTA:
	    		    		SET_BIT( PORTA , Copy_U8Pin);
	    		    		break;
	    		    	case DIO_PORTB:
	    		    		SET_BIT( PORTB , Copy_U8Pin);
	    		    		break;
	    		    	case DIO_PORTC:
	    		    		SET_BIT( PORTC , Copy_U8Pin);
	    		    	    break;
	    		    	case DIO_PORTD:
	    		    		SET_BIT( PORTD , Copy_U8Pin);
	    		    	    break;
	    		    }
	    	        break;
	}

}


 //function to set port direction
void DIO_VidSetPortDirection(u8 Copy_U8Port , u8 Copy_U8Direction)
{
	switch(Copy_U8Port)
		    {
		    	case DIO_PORTA:
		    		DDRA= Copy_U8Direction;
		    		break;
		    	case DIO_PORTB:
		    		DDRB= Copy_U8Direction;
		    		break;
		    	case DIO_PORTC:
		    		DDRC= Copy_U8Direction;
		    	    break;
		    	case DIO_PORTD:
		    		DDRD= Copy_U8Direction;
		    	    break;
		    }

}
//functio to set the port value
void DIO_VidSetPortValue(u8 Copy_U8Port , u8 Copy_U8Value)
{
	switch(Copy_U8Port)
		    {
		    	case DIO_PORTA:
		    		PORTA= Copy_U8Value;
		    		break;
		    	case DIO_PORTB:
		    		PORTB= Copy_U8Value;
		    		break;
		    	case DIO_PORTC:
		    		PORTC= Copy_U8Value;
		    	    break;
		    	case DIO_PORTD:
		    		PORTD= Copy_U8Value;
		    	    break;
		    }

}
//function to toggle the pin
void DIO_VidTogglePinValue(u8 Copy_U8Port , u8 Copy_U8Pin)
{
	switch(Copy_U8Port)
		    {
		    	case DIO_PORTA:
		    		TOGGLE_BIT(PORTA , Copy_U8Pin);
		    		break;
		    	case DIO_PORTB:
		    		TOGGLE_BIT(PORTB , Copy_U8Pin);
		    		break;
		    	case DIO_PORTC:
		    		TOGGLE_BIT(PORTC , Copy_U8Pin);
		    	    break;
		    	case DIO_PORTD:
		    		TOGGLE_BIT(PORTD , Copy_U8Pin);
		    	    break;
		    }

}

u8 DIO_U8Get_PinValue(u8 Copy_U8Port , u8 Copy_U8Pin)
{
	u8 read;
	switch(Copy_U8Port)
			    {
			    	case DIO_PORTA:
			    		read =GET_BIT(PINA , Copy_U8Pin);
			    		break;
			    	case DIO_PORTB:
			    		read=GET_BIT(PINB , Copy_U8Pin);
			    		break;
			    	case DIO_PORTC:
			    		read=GET_BIT(PINC , Copy_U8Pin);
			    	    break;
			    	case DIO_PORTD:
			    		read=GET_BIT(PIND , Copy_U8Pin);
			    	    break;
			    }
	return read;
}
