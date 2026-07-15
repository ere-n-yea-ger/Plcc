/*###########################################################################
Project			:	PLCC Supy
Filename		:	MAIN.C
Previous Version	:  	Not Applicable
New Version		:	0.1
Modified  on		:	13-04-1999
Last Modified by	:	G.S.Ubhi
Editor Tab Size  	:	3
Comments		:  	There are three main works which include checking for key
			   	pressed, updating system for alarms and checking switch
			   	status.
############################################################################*/
/*===========================================================================
								Revision History
								================


===========================================================================*/
#include<string.h>
#include<reg51.h>
#define public extern  
#include "declare.h"
#include "database.h"
#include "def.h"

#include "spfunreg.h"

// declaring variables for uart 
extern unsigned char xdata DUART_CSRA_ADDR;
extern unsigned char xdata DUART_THRA_ADDR;

unsigned char key_enter_flag_counter; /*scr_&_agc_bars*/
void main(void)
{
	//declaring variable for receiving 
	unsigned char received_char;  
       
	P1_5  = ~P1_5;
	InitController();      //Delay is introduced for proper init. of LCD
	InitDbase();
	InitDUART(); //uncommented 
	//InitLCD();
	//Delay(100);
	//InitDTMF();
	key_enter_flag_counter=MAXTICKCOUNT; /*scr_&_agc_bars*/	
	
	while(1)
	{
		// 1. Force the chip to transmit a 'U' continuously
		DUART_THRA_ADDR = 'U';
		
		// 2. A dumb delay so we don't flood and crash Tera Term
		{
			unsigned long int delay;
			for(delay = 0; delay < 50000; delay++); 
		}
	}
	
	/*
	while(1)
	{
	   ScreenHandler();
       GetADCInputs();
	   GetAGCInputs();	// added in ver 1.5
	   GetPowerOP();        // added in ver 1.5
       Getalarms();
	   Processloopback();
       Loopbackdisable();	
	   DTMFRxprocess();//added in Ver1.2
	   reset_lcd_display();	//reset_mtu
	}
	*/
}


