#include"KPD.h"





void KPD_Init(void)
{
	DIO_VidSetPortDirection(KPD_PORT, KPD_PORT_DIRECTION);
	DIO_VidSetPortValue(KPD_PORT,DIO_ALL_HIGH);  //0b 1111   1111
	                                             //   high + pull up res
}


u8 KPD_u8GetPressedKey(void){
	u8 Loc_u8PressedKey= 0xFF	, PinVal;
	u8 Loc_u8KPDArr[KPD_ROW_NUM][KPD_COL_NUM]= KPD_ARR;
    u8 Loc_u8KPDCOLArr[KPD_COL_NUM]={COL1, COL2, COL3, COL4};
	u8 Loc_u8KPDROWArr[KPD_ROW_NUM]={ROW1, ROW2, ROW3, ROW4};
	for(u8 i=0; i < KPD_COL_NUM; i++)
	{ //loop for col
			/* ACTIVATE CURRENT COLUMN */
		DIO_VidSetPinValue(KPD_PORT, Loc_u8KPDCOLArr[i], DIO_LOW);
			/* SEARCH IF A ROW IS LOW THUS A KEY IS PRESSED */
		for(u8 j=0; j < KPD_ROW_NUM; j++ )
		{//loop for rows
			PinVal=DIO_U8Get_PinValue(KPD_PORT, Loc_u8KPDROWArr[j]);
				/* CHECK IF SWITCH IS PRESSED */
			if( DIO_LOW == PinVal)
			{
				Loc_u8PressedKey = Loc_u8KPDArr[j][i];
					/* Polling ( wait till button is released ) */
				while( DIO_LOW == PinVal	)
				{
					PinVal=DIO_U8Get_PinValue(KPD_PORT, Loc_u8KPDROWArr[j]);
				}
				_delay_ms(10);
			}
		}
			/* DEACTIVATE CURRENT COLUMN */
		DIO_VidSetPinValue(KPD_PORT, Loc_u8KPDCOLArr[i], DIO_HIGH);
	}
	return Loc_u8PressedKey;
}
