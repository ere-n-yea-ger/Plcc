/*###########################################################################
Project			:	PLCC Supy
Filename		:	INTERPT.C
Previous Version	:  	Not Applicable
New Version		:	0.1
Modified  on		:	29-03-1999
Last Modified by	:	G.S.Ubhi
Editor Tab Size  	:	3

Comments		:
############################################################################*/

#define public extern
#include<reg51.h>
#include "def.h"
#include "database.h"
#include "spfunreg.h"
#include "addr.h"

extern unsigned int xdata S_Time12minCnt1;	//reset_mtu
unsigned char lcd_reset_flag;		//reset_mtu
//#include<stdio.h>
//void DispBars(void);

/*>>>>>>>>>>>>>>>>>>>>>>>>>
interrupt TimerInt0(void)
<<<<<<<<<<<<<<<<<<<<<<<<*/
void TimerInt0 (void) interrupt 1			 
{
unsigned char  count=0,ReadDTMF,Temp;
//****************//
//unsigned char buf[20];
//int i;
//******************//	
//	S_Time50msCnt++;
	S_Time100msCnt++;
	S_Time500msCnt++;
        

       	ReadDTMF  = DTMF_STAT_ADDR;

       	if((ReadDTMF)&(0x04))	
	    {	
	    Temp = DTMF_RX_ADDR;
	    
	    DTMFRxByte = ((Temp)&(0x0F));
		
        }

	if(S_Time100msCnt > 3)
	{
	  S_Time100msCnt = 0;
	  S_Time100ms = SET;
	}             
        //added in Ver1.2
	if((Tonedurationen1 == SET)||(Tonedurationen2 == SET)||(Tonedurationen3 == SET)||(Tonedurationen4 == SET))
	  TonedurationCnt++;
	else
	  TonedurationCnt = 0;
       
	 if(TonedurationCnt > 4)
	  {
          Toneduration = SET;
	  TonedurationCnt = 0;
		  }

	if((Tonepauseen1 == SET)||(Tonepauseen2 == SET)||(Tonepauseen3 == SET))
	  TonepauseCnt++;
	else
	  TonepauseCnt = 0;

	 if
	 (TonepauseCnt > 5)
	  {
	  Tonepause = SET;
	  TonepauseCnt = 0;
	  }

	if(Tone1waitflag == SET)
		Tone1waitCnt++;
	else
		Tone1waitCnt = 0;


		if(Tone1waitCnt > 20)
	  Tone1waitflag = RESET;


	if(Tone2waitflag == SET)
		Tone2waitCnt++;
	else
		Tone2waitCnt = 0;
	
	if(Tone3waitflag == SET)  /********************/
		Tone3waitCnt++;
	else
		Tone3waitCnt = 0;

		if(Tone2waitCnt > 20)
	  Tone2waitflag = RESET;
	/****************************/
	//ADDED IN Ver 1.4
    /*****************************/
	if(Tone3waitCnt > 20) /*********************/
	  Tone3waitflag = RESET;

		  //till here
  
	if(S_Time500msCnt > 19)
	{
	
     
	  S_Time500msCnt = 0;
	  S_Time500ms = SET;

	  System_health = ~System_health;   //this is the code for sys. health LED

	   /****************************************************************/
	 // testing code 28-11-2k  ajay
	// for channel1 AGC graph
		if(AGC1_scr==1)
			ch1_agc=1;
		else
			ch1_agc=0;
	// for channel2 AGC graph
		if(AGC2_scr)
			ch2_agc=1;
	    else
	   		ch2_agc=0;
		 // for power output graph
    if(PAMP_scr==1)
		ch_PAMP=1;
		else
		ch_PAMP=0;
      /*********************/

	  if(Timer10minen1)
		S_Time10minCnt1++;
	  else
		 S_Time10minCnt1 = 0;

	  if(Timer10minen2)
		 S_Time10minCnt2++;
	  else
		 S_Time10minCnt2 = 0;

	//added in Ver1.2
	  if(Timer10minen3)
		S_Time10minCnt3++;
	  else
		 S_Time10minCnt3 = 0;

	  if(Timer10minen4)  // added in ver 1.4 
		 S_Time10minCnt4++;
	  else
		 S_Time10minCnt4 = 0;
	  //ends here
	  if(S_Time12minCnt1)	//reset_mtu
		S_Time12minCnt1++;
	}

	  P1_5 = ~P1_5;           // Kick Watchdog

	if(S_Time10minCnt1 > 1199)  //Check 10minute time for loop disable
	{
	  S_Time10minCnt1 = 0;
	  S_Time10min1 = SET;
	}
	if(S_Time10minCnt2 > 1199)
	{
	  S_Time10minCnt2 = 0;
	  S_Time10min2 = SET;
	}

	if(S_Time10minCnt3 > 1199)  //Check 10minute time for loop disable
	{
	  S_Time10minCnt3 = 0;
	  S_Time10min3 = SET;
	}
	if(S_Time10minCnt4 > 1199)  //Check 10minute time for loop disable
	{
	  S_Time10minCnt4 = 0;
	  S_Time10min4 = SET;
	}
/*	if(S_Time12minCnt1 > 50)		//25 seconds	//reset_mtu
	{
		lcd_reset_flag=SET;
		S_Time12minCnt1=0;
	} */
		if(S_Time12minCnt1 > 7200)		//1 hour	//reset_mtu	after 1 hour
	{
		lcd_reset_flag=SET;
		S_Time12minCnt1=0;
	}
	TL0 = 0xFF;    	/* Reload Tick Counter : 25ms -> A5FF; 20ms -> B7FF; 10ms -> DBFF  */
	TH0 = 0xA5;

 }

