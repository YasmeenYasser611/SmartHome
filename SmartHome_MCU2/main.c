/*
 * main.c

 *
 *  Created on: Sep 3, 2023
 *      Author: yasmeen
 */

#include"LCD.h"
#include"KPD.h"
#include"DIO.h"
#include"UART.h"
#include"SPI.h"
void main(void)
{
	u8 masterR;
	u8 x=0 , FLAG=1,FLAG2=1,FLAG3=1 ,FLAG4=1,FLAG5=1;
	u8 read=0xFF , read2=0xFF,read3=0xFF;
	USART_VIDInit();
	KPD_Init();
	LCD_VidInit();
	SPI_MasterInit();
	DIO_VidSetPinDirection(DIO_PORTD,DIO_PIN0,DIO_INPUT); //UART RX
	DIO_VidSetPinDirection(DIO_PORTD,DIO_PIN1,DIO_OUTPUT); //UART  TX
	while(1)
	{
		//RECIVING SIGNAL FROM DOOR MCU
		_delay_ms(505);
		x=USART_U8RECIEVEChar();
        //WHEN ADMIN YASMEEN GET IN FROM THE DOOR TO THE HOME
		if(x==1)
		{
			   LCD_SEND_COMMAND(0x01);
	           LCD_VidSendStrig(" Welcome Home");
	           LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
		       LCD_VidSendStrig("Admin Yasmeen ");

		}
		else if(x==2) //WHEN ADMIN YOUSEF GET IN FROM THE DOOR TO THE HOME
		{
			LCD_SEND_COMMAND(0x01);
			LCD_VidSendStrig(" Welcome Home");
		    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
		    LCD_VidSendStrig("Admin Yousef ");


		}
		else if(x==3)//WHEN GUEST YASSER GET IN FROM THE DOOR TO THE HOME
		{
	     LCD_SEND_COMMAND(0x01);
         LCD_VidSendStrig(" Guest Yasser  ");
         LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
	     LCD_VidSendStrig(" outside!!!");

		}
		else
		{
			LCD_SEND_COMMAND(0x01); //clear screen
		}
		//WAIT FOR THE USRT TO PRESS = TO SHOW HIM THE OPTIONS
		read=0xFF;
		while(read==0xFF)
		{
		 read= KPD_u8GetPressedKey();
		}
		if(read!=0xFF)
		{
			//IF HE PRESSED = SO HE WANT TO CONTROL SOME THING
			if(read=='=')
			{
				//FIREST HE SHOULD SELECT THE MODE
				LCD_SEND_COMMAND(0x01);
			    LCD_VidSendStrig(" SELECT MODE");
			    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
				LCD_VidSendStrig("0:Admin 1:Guest ");
				while(1)
				{
					read=0xFF;
					while(read==0xFF)
					{
						read= KPD_u8GetPressedKey();
					}

					if(read!=0xFF)
					{
						if(read=='0')
						{
							//admin mode
							LCD_SEND_COMMAND(0x01);
						    LCD_VidSendStrig(" 1:Room1 2:Room2");
						    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
							LCD_VidSendStrig("3:Room3 4:+ 0RET");
							while(1)
							{
								read2=0xFF;
								while(read2==0xFF)
								{
									read2= KPD_u8GetPressedKey();
								}
								if(read2!=0xFF)
								{
									switch(read2)
									{
									case 1 : // IF HE CHOOSE ROOM1
										    LCD_SEND_COMMAND(0x01);
								            LCD_VidSendStrig(" Room1 S:OFF");
								            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
								           	LCD_VidSendStrig("1:on 2:off 3:RET ");
								           	while(1)
								           	{
									           	read3=0xFF;
												while(read3==0xFF)
												{
													read3= KPD_u8GetPressedKey();
												}
									           	if(read3!=0xFF)
									           	{
									           		switch(read3)
									           		{
									           		case 1: //IF HE CHOOSE ON
									           			    LCD_SEND_COMMAND(0x01);
							           			            masterR=SPI_u8MasterTrancieve('O'); //room1 will turn on
									           			    LCD_VidSendStrig(" Room1 S:ON");
									                        LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
									           	            LCD_VidSendStrig("1:on 2:off 3:RET ");
									           	            //_delay_ms(400);
									           			   break;
									           		case 2: //IF HE CHOOSE OFF
									           			    LCD_SEND_COMMAND(0x01);
							           			            masterR=SPI_u8MasterTrancieve('F'); //room1 will turn OFF
									           			    LCD_VidSendStrig(" Room1 S:OFF");
									                        LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
									           	            LCD_VidSendStrig("1:on 2:off 3:RET ");
									           	            //_delay_ms(400);
									           			   break;
									           		case 3: //IF HE WANT TO RETURN TO THE PRIVIOUS PAGE
									           			    LCD_SEND_COMMAND(0x01);
												            LCD_VidSendStrig(" 1:Room1 2:Room2");
												            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
												            LCD_VidSendStrig("3:Room3 4:+ 0RET");
												        	masterR=SPI_u8MasterTrancieve('F');
												        	_delay_ms(100);
												        	masterR=SPI_u8MasterTrancieve('*');
												        	FLAG=0;
									           			   break;
													default://WRONG ENTERY
														LCD_SEND_COMMAND(0x01);
														LCD_VidSendStrig(" wrong choice");
													    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
														LCD_VidSendStrig("choose again");
														_delay_ms(500);
														LCD_SEND_COMMAND(0x01);
														masterR=SPI_u8MasterTrancieve('F');
											        	_delay_ms(100);
											        	masterR=SPI_u8MasterTrancieve('*');
											            LCD_VidSendStrig(" Room1 S:OFF");
											            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
											           	LCD_VidSendStrig("1:on 2:off 3:RET ");
														break;



									           		}
									           		if(FLAG==0)
									           		{
									           			//FLAG TO RETURN TO PRIVIOUSE PAGE AND CHOOSE ANOTHER OPTION
									           			FLAG=1;
									           			break;
									           		}
									           	}

								           	}
								           	break;
									case 2 ://IF USER CHOOSE ROOM2
										    LCD_SEND_COMMAND(0x01);
								            LCD_VidSendStrig(" Room2 S:OFF");
								            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
								           	LCD_VidSendStrig("1:on 2:off 3:RET ");
								           	while(1)
								           	{
									           	read3=0xFF;
												while(read3==0xFF)
												{
													read3= KPD_u8GetPressedKey();
												}
									           	if(read3!=0xFF)
									           	{
									           		switch(read3)
									           		{
									           		case 1: //IF USER CHOOSE ON
									           			    LCD_SEND_COMMAND(0x01);
							           			            masterR=SPI_u8MasterTrancieve('2'); //room2 will turn on
									           			    LCD_VidSendStrig(" Room2 S:ON");
									                        LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
									           	            LCD_VidSendStrig("1:on 2:off 3:RET ");
									           	            //_delay_ms(400);
									           			   break;
									           		case 2://IF HE CHOOSE OFF
									           			    LCD_SEND_COMMAND(0x01);
							           			            masterR=SPI_u8MasterTrancieve('3'); //room2 will turn off
									           			    LCD_VidSendStrig(" Room2 S:OFF");
									                        LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
									           	            LCD_VidSendStrig("1:on 2:off 3:RET ");
									           	            //_delay_ms(400);
									           			   break;
									           		case 3: //IF HE CHOOSE TO RETURN TO THE PRIVIOSE PAGE
									           			    LCD_SEND_COMMAND(0x01);
												            LCD_VidSendStrig(" 1:Room1 2:Room2");
												            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
												            LCD_VidSendStrig("3:Room3 4:+ 0RET");
												        	masterR=SPI_u8MasterTrancieve('3');
												        	_delay_ms(100);
												        	masterR=SPI_u8MasterTrancieve('*');
												        	FLAG=0;
									           			   break;
													default: //WRONG ENTERY
														LCD_SEND_COMMAND(0x01);
														LCD_VidSendStrig(" wrong choice");
													    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
														LCD_VidSendStrig("choose again");
														_delay_ms(500);
														LCD_SEND_COMMAND(0x01);
														masterR=SPI_u8MasterTrancieve('3');
											        	_delay_ms(100);
											        	masterR=SPI_u8MasterTrancieve('*');
											            LCD_VidSendStrig(" Room2 S:OFF");
											            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
											           	LCD_VidSendStrig("1:on 2:off 3:RET ");
														break;




									           		}
									           		if(FLAG==0)
									           		{
									           			//FLAG TO RETURN
									           			FLAG=1;
									           			break;
									           		}
									           	}

								           	}
								           	break;
									case 3 ://I USER CHOOSE ROOM3
										    LCD_SEND_COMMAND(0x01);
								            LCD_VidSendStrig(" Room3 S:OFF");
								            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
								           	LCD_VidSendStrig("1:on 2:off 3:RET ");
								           	while(1)
								           	{
									           	read3=0xFF;
												while(read3==0xFF)
												{
													read3= KPD_u8GetPressedKey();
												}
									           	if(read3!=0xFF)
									           	{
									           		switch(read3)
									           		{
									           		case 1: //IF HE WANT TO TURN ROOM3 ON
									           			    LCD_SEND_COMMAND(0x01);
							           			            masterR=SPI_u8MasterTrancieve('4'); //room3 will turn on
									           			    LCD_VidSendStrig(" Room3 S:ON");
									                        LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
									           	            LCD_VidSendStrig("1:on 2:off 3:RET ");
									           	            //_delay_ms(400);
									           			   break;
									           		case 2: //IF HE CHOOSE TO TURN ROOM3 OFF
									           			    LCD_SEND_COMMAND(0x01);
							           			            masterR=SPI_u8MasterTrancieve('5'); //room3 will turn off
									           			    LCD_VidSendStrig(" Room3 S:OFF");
									                        LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
									           	            LCD_VidSendStrig("1:on 2:off 3:RET ");
									           	           // _delay_ms(400);
									           			   break;
									           		case 3: //IF HE WANT TO RETURN TO PRIVIOUSE PAGE
									           			    LCD_SEND_COMMAND(0x01);
												            LCD_VidSendStrig(" 1:Room1 2:Room2");
												            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
												            LCD_VidSendStrig("3:Room3 4:+ 0RET");
												        	masterR=SPI_u8MasterTrancieve('5');
												        	masterR=SPI_u8MasterTrancieve('*');
												        	FLAG=0;
									           			   break;
													default: //WRONG ENTERY
														LCD_SEND_COMMAND(0x01);
														LCD_VidSendStrig(" wrong choice");
													    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
														LCD_VidSendStrig("choose again");
														_delay_ms(500);
														LCD_SEND_COMMAND(0x01);
														masterR=SPI_u8MasterTrancieve('5');
											        	//_delay_ms(100);
											        	masterR=SPI_u8MasterTrancieve('*');
											            LCD_VidSendStrig(" Room3 S:OFF");
											            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
											           	LCD_VidSendStrig("1:on 2:off 3:RET ");
														break;




									           		}
									           		if(FLAG==0)
									           		{
									           			//FLAG TO RETURN TO PRAVIOUSE PAGE
									           			FLAG=1;
									           			break;
									           		}
									           	}

								           	}
								           	break;
									case 4 :// IF HE CHOOSE + FOR MORE OPTIONS
										    LCD_SEND_COMMAND(0x01);
								            LCD_VidSendStrig(" 1:Room4 2:TV");
								            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
								           	LCD_VidSendStrig("3:Air_COND 4:RET");
											while(1)
											{
												read2=0xFF;
												while(read2==0xFF)
												{
													read2= KPD_u8GetPressedKey();
												}
												if(read2!=0xFF)
												{
													switch(read2)
													{
													case 1 ://ROOM4
														    LCD_SEND_COMMAND(0x01);
												            LCD_VidSendStrig(" Room4 S:OFF");
												            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
												           	LCD_VidSendStrig("1:on 2:off 3:RET ");
												           	while(1)
												           	{
													           	read3=0xFF;
																while(read3==0xFF)
																{
																	read3= KPD_u8GetPressedKey();
																}
													           	if(read3!=0xFF)
													           	{
													           		switch(read3)
													           		{
													           		case 1: //TURN IT ON
													           			    LCD_SEND_COMMAND(0x01);
											           			            masterR=SPI_u8MasterTrancieve('6'); //room4 will turn on
													           			    LCD_VidSendStrig(" Room4 S:ON");
													                        LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
													           	            LCD_VidSendStrig("1:on 2:off 3:RET ");
													           	            //_delay_ms(400);
													           			   break;
													           		case 2://TURN IT OFF
													           			    LCD_SEND_COMMAND(0x01);
											           			            masterR=SPI_u8MasterTrancieve('7'); //room4 will turn oFF
											           		                //_delay_ms(1000);
													           			    LCD_VidSendStrig(" Room4 S:OFF");
													                        LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
													           	            LCD_VidSendStrig("1:on 2:off 3:RET ");
													           	           // _delay_ms(400);
													           			   break;
													           		case 3: //TO RETURN TO THE PRIVIOUS PAGE
													           			    LCD_SEND_COMMAND(0x01);
													           			    masterR=SPI_u8MasterTrancieve('7');
														                    LCD_VidSendStrig(" 1:Room4 2:TV");
														                    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
														                	LCD_VidSendStrig("3:Air_COND 4:RET");
																        	masterR=SPI_u8MasterTrancieve('*');
																        	FLAG2=0;
													           			   break;
																	default: // WRONG ENTERY
																		LCD_SEND_COMMAND(0x01);
																		masterR=SPI_u8MasterTrancieve('7');
																		LCD_VidSendStrig(" wrong choice");
																	    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
																		LCD_VidSendStrig("choose again");
																		_delay_ms(500);
																		LCD_SEND_COMMAND(0x01);
															        	masterR=SPI_u8MasterTrancieve('*');
															            LCD_VidSendStrig(" Room4 S:OFF");
															            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
															           	LCD_VidSendStrig("1:on 2:off 3:RET ");
																		break;
													           		}
													           		if(FLAG2==0)
													           		{
													           			//FLAG TO RETURN TO PRIVIOSE PAGE
													           			FLAG2=1;
													           			break;
													           		}
													           	}

												           	}
												           	break;
													case 2 ://TV
														    LCD_SEND_COMMAND(0x01);
												            LCD_VidSendStrig(" TV S:OFF");
												            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
												           	LCD_VidSendStrig("1:on 2:off 3:RET ");
												           	while(1)
												           	{
													           	read3=0xFF;
																while(read3==0xFF)
																{
																	read3= KPD_u8GetPressedKey();
																}
													           	if(read3!=0xFF)
													           	{
													           		switch(read3)
													           		{
													           		case 1://TURN TV ON
													           			    LCD_SEND_COMMAND(0x01);
											           			            masterR=SPI_u8MasterTrancieve('8'); //TV will turn on
													           			    LCD_VidSendStrig(" TV S:ON");
													                        LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
													           	            LCD_VidSendStrig("1:on 2:off 3:RET ");
													           	           // _delay_ms(400);
													           			   break;
													           		case 2:  //TURN TV OFF
													           			    LCD_SEND_COMMAND(0x01);
											           			            masterR=SPI_u8MasterTrancieve('9'); //TV will turn oFF
													           			    LCD_VidSendStrig(" TV S:OFF");
													                        LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
													           	            LCD_VidSendStrig("1:on 2:off 3:RET ");
													           	            //_delay_ms(400);
													           			   break;
													           		case 3: //TO RETURN TO PRIVIOS PAGE
													           			    LCD_SEND_COMMAND(0x01);
													           		        masterR=SPI_u8MasterTrancieve('9');
														                    LCD_VidSendStrig(" 1:Room4 2:TV");
														                    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
														                	LCD_VidSendStrig("3:Air_COND 4:RET");
																        	masterR=SPI_u8MasterTrancieve('*');
																        	FLAG2=0;
													           			   break;
																	default: //WRONG ENTERY
																		LCD_SEND_COMMAND(0x01);
																		LCD_VidSendStrig(" wrong choice");
																	    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
																		LCD_VidSendStrig("choose again");
																		_delay_ms(500);
																		LCD_SEND_COMMAND(0x01);
																		masterR=SPI_u8MasterTrancieve('9');
															            LCD_VidSendStrig(" TV S:OFF");
															            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
															           	LCD_VidSendStrig("1:on 2:off 3:RET ");
															        	//_delay_ms(100);
															        	masterR=SPI_u8MasterTrancieve('*');
																		break;
													           		}
													           		if(FLAG2==0)
													           		{
													           			//FLAG TO RETURN TO PREVIOSE PAGE
													           			FLAG2=1;

													           			break;
													           		}
													           	}

												           	}
												           	break;
													case 3: //AIR COND
								           		         LCD_SEND_COMMAND(0x01);
								           		         LCD_VidSendStrig(" Air cond S:ON");
								           		         LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
								           		         LCD_VidSendStrig("1:on 2:off 3:RET ");
												           	while(1)
												           	{
													           	read3=0xFF;
																while(read3==0xFF)
																{
																	read3= KPD_u8GetPressedKey();
																}
													           	if(read3!=0xFF)
													           	{
													           		switch(read3)
													           		{
													           		case 1: //TURN IT ON
													           			    LCD_SEND_COMMAND(0x01);
											           			            masterR=SPI_u8MasterTrancieve('t'); //CONDITIONER will turn on
													           			    LCD_VidSendStrig(" Air cond S:ON");
													                        LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
													           	            LCD_VidSendStrig("1:on 2:off 3:RET ");
													           	          //  _delay_ms(400);
													           			   break;
													           		case 2: //TURN IT OFF
													           			    LCD_SEND_COMMAND(0x01);
											           			            masterR=SPI_u8MasterTrancieve('m'); //CONDITIONER will turn oFF
											           			            LCD_VidSendStrig(" Air cond S:OFF");
													                        LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
													           	            LCD_VidSendStrig("1:on 2:off 3:RET ");
													           	            //_delay_ms(400);
													           			   break;
													           		case 3: //RETURN TO PRIVIOSE PAGE
													           			    LCD_SEND_COMMAND(0x01);
													           	          	masterR=SPI_u8MasterTrancieve('m');
														                    LCD_VidSendStrig(" 1:Room4 2:TV");
														                    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
														                	LCD_VidSendStrig("3:Air_COND 4:RET");
																        	masterR=SPI_u8MasterTrancieve('*');
																        	FLAG2=0;
													           			   break;
																	default://WRONG ENTRY
																		LCD_SEND_COMMAND(0x01);
																		LCD_VidSendStrig(" wrong choice");
																	    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
																		LCD_VidSendStrig("choose again");
																		_delay_ms(500);
																		LCD_SEND_COMMAND(0x01);
																		masterR=SPI_u8MasterTrancieve('m');
															            LCD_VidSendStrig(" Air cond S:OFF");
															            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
															           	LCD_VidSendStrig("1:on 2:off 3:RET ");
															           	masterR=SPI_u8MasterTrancieve('*');
																		break;
													           		}
													           		if(FLAG2==0)
													           		{
													           			//FLAG TO RETURN
													           			FLAG2=1;

													           			break;
													           		}
													           	}

												           	}
														 break;
													case 4 ://RET
									           		        LCD_SEND_COMMAND(0x01);
													        LCD_VidSendStrig(" 1:Room1 2:Room2");
													        LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
													        LCD_VidSendStrig("3:Room3 4:+ 0RET");
									           		    	masterR=SPI_u8MasterTrancieve('*');
												        	FLAG3=0;
												           	break;
													default://WRONG ENTERY
														LCD_SEND_COMMAND(0x01);
														LCD_VidSendStrig(" wrong choice");
													    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
														LCD_VidSendStrig("choose again");
														_delay_ms(500);
														LCD_SEND_COMMAND(0x01);
														masterR=SPI_u8MasterTrancieve('*');
											            LCD_VidSendStrig(" 1:Room4 2:TV");
											            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
											           	LCD_VidSendStrig("3:Air_COND 4:RET");
														break;


													}
									           		if(FLAG3==0)
									           		{
									           			//FLAG TO RETURN
									           			FLAG3=1;
									           			break;
									           		}
												}

											}


								           	break;
									case'0': //IF HE WANT TO RETURN TO MODE SELECT PAGE
										    LCD_SEND_COMMAND(0x01);
										    LCD_VidSendStrig(" SELECT MODE");
								            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
									        LCD_VidSendStrig("0:Admin 1:Guest ");
									        masterR=SPI_u8MasterTrancieve('*');
										    FLAG4=0;
									        break;
									default: //WRONG ENTERY
										LCD_SEND_COMMAND(0x01);
										LCD_VidSendStrig(" wrong choice");
									    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
										LCD_VidSendStrig("choose again");
										_delay_ms(500);
										LCD_SEND_COMMAND(0x01);
									    LCD_VidSendStrig(" 1:Room1 2:Room2");
									    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
									    LCD_VidSendStrig("3:Room3 4:+ 0RET");
										break;

									}
								}
						  		if(FLAG4==0)
						       		{
						  			    //FLAG TO RETURN TO PRIVIOSE PAGE
						       			FLAG4=1;
						       			break;
						       		}

							}

						}
						else if(read==1)
						{
							//*************************************GUEST MODE**************************************
							LCD_SEND_COMMAND(0x01);
						    LCD_VidSendStrig(" 1:Room1 2:Room2");
						    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
							LCD_VidSendStrig("3:Room3 4:ROOM4 0 ");
							while(1)
							{
								read2=0xFF;
								while(read2==0xFF)
								{
									read2= KPD_u8GetPressedKey();
								}
								if(read2!=0xFF)
								{
									switch(read2)
									{
									case 1 ://ROOM1
										    LCD_SEND_COMMAND(0x01);
								            LCD_VidSendStrig(" Room1 S:OFF");
								            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
								           	LCD_VidSendStrig("1:on 2:off 3:RET ");
								           	while(1)
								           	{
									           	read3=0xFF;
												while(read3==0xFF)
												{
													read3= KPD_u8GetPressedKey();
												}
									           	if(read3!=0xFF)
									           	{
									           		switch(read3)
									           		{
									           		case 1: //TURN IT ON
									           			    LCD_SEND_COMMAND(0x01);
							           			            masterR=SPI_u8MasterTrancieve('O'); //room1 will turn on
									           			    LCD_VidSendStrig(" Room1 S:ON");
									                        LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
									           	            LCD_VidSendStrig("1:on 2:off 3:RET ");

									           			   break;
									           		case 2://TURN IT OFF
									           			    LCD_SEND_COMMAND(0x01);
							           			            masterR=SPI_u8MasterTrancieve('F'); //room1 will turn oFF
									           			    LCD_VidSendStrig(" Room1 S:OFF");
									                        LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
									                        LCD_VidSendStrig("1:on 2:off 3:RET ");

									           			   break;
									           		case 3: //RETURN
									           			    LCD_SEND_COMMAND(0x01);
									           		    	masterR=SPI_u8MasterTrancieve('F');
												            LCD_VidSendStrig(" 1:Room1 2:Room2");
												            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
												            LCD_VidSendStrig("3:Room3 4:ROOM4");
												        	masterR=SPI_u8MasterTrancieve('*');
												        	FLAG=0;
									           			   break;
													default: //WRONG ENTERY
														LCD_SEND_COMMAND(0x01);
														LCD_VidSendStrig(" wrong choice");
													    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
														LCD_VidSendStrig("choose again");
														_delay_ms(500);
														LCD_SEND_COMMAND(0x01);
														masterR=SPI_u8MasterTrancieve('F');
											        	//_delay_ms(100);
											        	masterR=SPI_u8MasterTrancieve('*');
											            LCD_VidSendStrig(" Room1 S:OFF");
											            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
											           	LCD_VidSendStrig("1:on 2:off 3:RET ");
														break;



									           		}
									           		if(FLAG==0)
									           		{
									           			//FLAG TO RETURN
									           			FLAG=1;
									           			break;
									           		}
									           	}

								           	}
								           	break;
									case 2 ://ROOM2
										    LCD_SEND_COMMAND(0x01);
								            LCD_VidSendStrig(" Room2 S:OFF");
								            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
								           	LCD_VidSendStrig("1:on 2:off 3:RET ");
								           	while(1)
								           	{
									           	read3=0xFF;
												while(read3==0xFF)
												{
													read3= KPD_u8GetPressedKey();
												}
									           	if(read3!=0xFF)
									           	{
									           		switch(read3)
									           		{
									           		case 1: //TURN IT ON
									           			    LCD_SEND_COMMAND(0x01);
							           			            masterR=SPI_u8MasterTrancieve('2'); //room2 will turn on
									           			    LCD_VidSendStrig(" Room2 S:ON");
									                        LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
									           	            LCD_VidSendStrig("1:on 2:off 3:RET ");
									           	            //_delay_ms(400);
									           			   break;
									           		case 2://TURN IT OFF
									           			   LCD_SEND_COMMAND(0x01);
							           			            masterR=SPI_u8MasterTrancieve('3'); //room1 will turn off
									           			    LCD_VidSendStrig(" Room2 S:OFF");
									                        LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
									           	            LCD_VidSendStrig("1:on 2:off 3:RET ");
									           	            //_delay_ms(400);
									           			   break;
									           		case 3: //RETURN
									           			    LCD_SEND_COMMAND(0x01);
									           			    masterR=SPI_u8MasterTrancieve('3');
												            LCD_VidSendStrig(" 1:Room1 2:Room2");
												            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
												            LCD_VidSendStrig("3:Room3 4:Room4 ");
												        	masterR=SPI_u8MasterTrancieve('*');
												        	FLAG=0;
									           			   break;
													default://WRONG ENTERY
														LCD_SEND_COMMAND(0x01);
														LCD_VidSendStrig(" wrong choice");
													    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
														LCD_VidSendStrig("choose again");
														_delay_ms(500);
														LCD_SEND_COMMAND(0x01);
														masterR=SPI_u8MasterTrancieve('3');
											        	//_delay_ms(100);
											        	masterR=SPI_u8MasterTrancieve('*');
											            LCD_VidSendStrig(" Room2 S:OFF");
											            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
											           	LCD_VidSendStrig("1:on 2:off 3:RET ");
														break;



									           		}
									           		if(FLAG==0)
									           		{
									           			//FLAG TO RETURN TO PRIVIOSE PAGE
									           			FLAG=1;
									           			break;
									           		}
									           	}

								           	}
								           	break;
									case 3 ://ROOM3
										    LCD_SEND_COMMAND(0x01);
								            LCD_VidSendStrig(" Room3 S:OFF");
								            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
								           	LCD_VidSendStrig("1:on 2:off 3:RET ");
								           	while(1)
								           	{
									           	read3=0xFF;
												while(read3==0xFF)
												{
													read3= KPD_u8GetPressedKey();
												}
									           	if(read3!=0xFF)
									           	{
									           		switch(read3)
									           		{
									           		case 1://TURN ON
									           			   LCD_SEND_COMMAND(0x01);
							           			            masterR=SPI_u8MasterTrancieve('4'); //room3 will turn on
									           			    LCD_VidSendStrig(" Room3 S:ON");
									                        LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
									           	            LCD_VidSendStrig("1:on 2:off 3:RET ");
									           	           // _delay_ms(400);
									           			   break;
									           		case 2: //TURN OFF
									           			    LCD_SEND_COMMAND(0x01);
							           			            masterR=SPI_u8MasterTrancieve('5'); //room3 will turn off
									           			    LCD_VidSendStrig(" Room3 S:OFF");
									                        LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
									           	            LCD_VidSendStrig("1:on 2:off 3:RET ");
									           	           // _delay_ms(400);
									           			   break;
									           		case 3: //RETURN TO PRIVIOSE PAGE
									           			    LCD_SEND_COMMAND(0x01);
									           			    masterR=SPI_u8MasterTrancieve('5');
												            LCD_VidSendStrig(" 1:Room1 2:Room2");
												            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
												            LCD_VidSendStrig("3:Room3 4:Room4 ");
												        	masterR=SPI_u8MasterTrancieve('*');
												        	FLAG=0;
									           			   break;
													default://WRONG ENTERY
														LCD_SEND_COMMAND(0x01);
														LCD_VidSendStrig(" wrong choice");
													    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
														LCD_VidSendStrig("choose again");
														_delay_ms(500);
														LCD_SEND_COMMAND(0x01);
														masterR=SPI_u8MasterTrancieve('5');

											        	masterR=SPI_u8MasterTrancieve('*');
											            LCD_VidSendStrig(" Room3 S:OFF");
											            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
											           	LCD_VidSendStrig("1:on 2:off 3:RET ");
														break;
									           		}
									           		if(FLAG==0)
									           		{
									           			//FLAG TO RETURN
									           			FLAG=1;
									           			break;
									           		}
									           	}

								           	}
								           	break;
									case 4 ://ROOM4
										    LCD_SEND_COMMAND(0x01);
								            LCD_VidSendStrig(" Room4 S:OFF");
								            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
								           	LCD_VidSendStrig("1:on 2:off 3:RET ");
								           	while(1)
								           	{
									           	read3=0xFF;
												while(read3==0xFF)
												{
													read3= KPD_u8GetPressedKey();
												}
									           	if(read3!=0xFF)
									           	{
									           		switch(read3)
									           		{
									           		case 1: //TURN IT ON
									           			    LCD_SEND_COMMAND(0x01);
							           			            masterR=SPI_u8MasterTrancieve('6'); //room4 will turn on
									           			    LCD_VidSendStrig(" Room4 S:ON");
									                        LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
									           	            LCD_VidSendStrig("1:on 2:off 3:RET ");
									           	            //_delay_ms(400);
									           			   break;
									           		case 2: //TURN IT OFF
									           			    LCD_SEND_COMMAND(0x01);
							           			            masterR=SPI_u8MasterTrancieve('7'); //room4 will turn off
									           			    LCD_VidSendStrig(" Room4 S:OFF");
									                        LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
									           	            LCD_VidSendStrig("1:on 2:off 3:RET ");
									           	            //_delay_ms(400);
									           			   break;
									           		case 3: //RETURN
									           			    LCD_SEND_COMMAND(0x01);
									           		        masterR=SPI_u8MasterTrancieve('7');
												            LCD_VidSendStrig(" 1:Room1 2:Room2");
												            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
												        	LCD_VidSendStrig("3:Room3 4:Room4 ");
												        	masterR=SPI_u8MasterTrancieve('*');

												        	FLAG=0;
									           			   break;
													default: //WRONG ENTERY
															LCD_SEND_COMMAND(0x01);
															masterR=SPI_u8MasterTrancieve('7');
															LCD_VidSendStrig(" wrong choice");
														    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
															LCD_VidSendStrig("choose again");
															_delay_ms(500);
															LCD_SEND_COMMAND(0x01);
												        	masterR=SPI_u8MasterTrancieve('*');
												            LCD_VidSendStrig(" Room4 S:OFF");
												            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
												           	LCD_VidSendStrig("1:on 2:off 3:RET ");
															break;



									           		}
									           		if(FLAG==0)
									           		{
									           			//FLAG TO RETURN
									           			FLAG=1;
									           			break;
									           		}
									           	}

								           	}
								           	break;
									case'0'://IF USER WANT TO RETURN TO THE MODE SELECT PAGE
										    LCD_SEND_COMMAND(0x01);
										    LCD_VidSendStrig(" SELECT MODE");
								            LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
									        LCD_VidSendStrig("0:Admin 1:Guest ");
									        masterR=SPI_u8MasterTrancieve('*');
										    FLAG4=0;
									        break;
									default: //WRONG ENTERY
										LCD_SEND_COMMAND(0x01);
										LCD_VidSendStrig(" wrong choice");
									    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
										LCD_VidSendStrig("choose again");
										_delay_ms(500);
										LCD_SEND_COMMAND(0x01);
									    LCD_VidSendStrig(" 1:Room1 2:Room2");
									    LCD_VidGoTOLocation(LCD_RowTwo,LCD_ColOne);
										LCD_VidSendStrig("3:Room3 4:Room4 ");
										break;
									}
								}
						  		if(FLAG4==0)
						       		{
						  			    //FLAG TO RETURN TO PREVIOSE PAGE
						       			FLAG4=1;
						       			break;
						       		}

							}

						}
						else if(read=='=')
						{
							//IF HE FINISH END WANT TO ENTER THE WAITING MODE
							LCD_SEND_COMMAND(0x01);
							LCD_VidSendStrig(" WAITING UPDATES");
							FLAG5=0;
							read=0xFF;
							break;

						}
						else
						{ //WRONG ENTERY
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

					if(FLAG5==0)
					{
						//FLAG TO RETURN
						FLAG5=1;
						break;
					}

				}

			} //IF HE DID NOT PRESS = THE SYSTEM WILL LOOP WAITING HIM TO PRESS = TO START SHOWING HIM THE OPTIONS


		}//END OF THE CHECK IF HE PRESSED ANY KEY


	} //END OF THE FIREST BIG WHILE LOOP

} //END OF MAIN
