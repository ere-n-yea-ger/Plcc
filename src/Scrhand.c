/*##########################################################################
Project				:	PLCC Supy
Filename			:	scrhand.C                 
Previous Version	: 	Not Applicable
New Version			:	00.1
Modified  on		:	15-04-1999
Last Modified by	:	Ajay
Editor Tab Size  	:
Comments		:  In this program UP and DOWN Keys are used to scroll the
			   menu and ESC Key to go back to screen no 2 within the menu.
			   The ENTER Key is used to go in its sub menus.
###########################################################################*/

#define public extern
#include<stdio.h>
#include<string.h>
#include"def.h"
#include"declare.h"
#include"database.h"
#include"addr.h"
#include"screen.h" 

extern unsigned char key_enter_flag_counter; /*scr_&_agc_bars*/
extern unsigned char lcd_reset_flag;	//reset_mtu
unsigned char key_enter_flag_counter1=0; /*scr_&_agc_bars*/
struct Screen Screens[]
  =   {
		  { OPEN_MENU_MODE,OPENING_SCR,{" PUNCOM PL9500  ", " PLCC EQUIPMENT " }},
   		  { MAIN_MENU_MODE,MAIN_SCR,{"MAIN MENU       ", "               v" }},
		  { MAIN_MENU_MODE,MAIN_SCR+1,{"ALARMS         ^", " <Enter>       v" }},
		  { MAIN_MENU_MODE,MAIN_SCR+2,{"STATUS         ^", " <Enter>       v" }},
		  { MAIN_MENU_MODE,MAIN_SCR+3,{"TEST           ^", " <Enter>        " }},
	  		  
		  { STATUS_MENU_MODE,STATUS_SCR,  {"Software Ver.   ", "1.3            v" }},
		  { STATUS_MENU_MODE,STATUS_SCR+1,{"System Config. ^", "               v" }},/*new screen to display 20w or 40 w*/ /*scr_&_agc_bars*/
		  { STATUS_MENU_MODE,STATUS_SCR+2,{"               ^", "               v" }},	     	  
		  { STATUS_MENU_MODE,STATUS_SCR+3,{"               ^", "               v" }},	     	  
		  { STATUS_MENU_MODE,STATUS_SCR+4,{"Slot1:VFI1     ^", "Slot2:CHM1     v" }},
		  { STATUS_MENU_MODE,STATUS_SCR+5,{"Slot3:VFI2     ^", "Slot4:CHM2     v" }},
		  { STATUS_MENU_MODE,STATUS_SCR+6,{"Slot5:PAMP     ^", "Slot6:DIU1     v" }},
		  { STATUS_MENU_MODE,STATUS_SCR+7,{"Slot7:DIU2     ^", "Slot8:SUP      v" }},
		  { STATUS_MENU_MODE,STATUS_SCR+8,{"HF Hybrid      ^", "               v" }},
		  { STATUS_MENU_MODE,STATUS_SCR+9,{"               ^", "               v" }},
		  { STATUS_MENU_MODE,STATUS_SCR+10,{"               ^", "               v" }},
		  { STATUS_MENU_MODE,STATUS_SCR+11,{"   PAMP O/P:   ^", "               v" }},
		  { STATUS_MENU_MODE,STATUS_SCR+12,{"P12V:+         ^", "N12V:-         v" }},
		  { STATUS_MENU_MODE,STATUS_SCR+13,{"               ^", "               v" }},
		  { STATUS_MENU_MODE,STATUS_SCR+14,{"P5V:+          ^", "                " }},
		  

		  { TEST_MENU_MODE,TEST_SCR,{"LOCAL LOOPBACK  ", "                " }},	  
   		  { TEST_MENU_MODE,TEST_SCR+1,{"REMOTE LOOPBACK ", "                " }},

   		 
		  { LOCAL_LOOPBACK_MODE,LOCAL_SCR,  {"Channel1       ^", "Normal         v" }},
		  { LOCAL_LOOPBACK_MODE,LOCAL_SCR+1,{"Channel2       ^", "Normal         v"}},
		   		
		  //screens added for implementing remote loop
		 
         
		/**********************************************************/
		  //screens added for implementing remote loop  in Ver 1.4                   
		/*********************************************************/
		  
		 { REMOTE_LOOPBACK_MODE,REMOTE_SCR,{"                ", "               v" }},          
		 { REMOTE_LOOPBACK_MODE,REMOTE_SCR+1,{"Select Terml.? ^", "               v" }},          // to ask from user /*scr_&_agc_bars*/

		 { REMOTE_LOOPBACK_MODE,REMOTE_SCR+2,{"Terml. ID:One  ^", "               v" }},
		 { REMOTE_LOOPBACK_MODE,REMOTE_SCR+3,{"Terml. ID:Two  ^", "               v" }},
		  
		  { REMOTE_LOOPBACK_MODE,REMOTE_SCR+4,{"Terml. ID:Three^", "               v" }},
		  { REMOTE_LOOPBACK_MODE,REMOTE_SCR+5,{"Terml. ID:Four ^", "               v" }},

		  { REMOTE_LOOPBACK_MODE,REMOTE_SCR+6,{"Terml. ID:Five ^", "               v" }},
		  { REMOTE_LOOPBACK_MODE,REMOTE_SCR+7,{"Terml. ID:Six  ^", "               v" }},
 
		  { REMOTE_LOOPBACK_MODE,REMOTE_SCR+8,{"Terml. ID:Seven^", "               v" }},
		  { REMOTE_LOOPBACK_MODE,REMOTE_SCR+9,{"Terml. ID:Eight^", "               v" }},
       
		  { REMOTE_LOOPBACK_MODE,REMOTE_SCR+10,{"Terml. ID:Nine ^", "               v" }},
		  { REMOTE_LOOPBACK_MODE,REMOTE_SCR+11,{"Terml. ID:Ten  ^", "               v" }},

		  { STATION1, STATION1_SCR,  {"Channel1       ^", "Normal         v"}},
		  { STATION1, STATION1_SCR+1,{"               ^", "               v"}},
			  
		  { STATION2, STATION2_SCR,  {"Channel1       ^", "Normal         v"}},
		  { STATION2, STATION2_SCR+1,{"               ^", "               v"}},

		  { STATION3, STATION3_SCR,  {"Channel1       ^", "Normal         v"}},
		  { STATION3, STATION3_SCR+1,{"               ^", "               v"}},
		  
		  { STATION4, STATION4_SCR,{"Channel1       ^", "Normal         v"}},
		  { STATION4, STATION4_SCR+1,{"               ^", "               v"}},			

		  { STATION5, STATION5_SCR,{"Channel1       ^", "Normal         v"}},
		  { STATION5, STATION5_SCR+1,{"               ^", "               v"}},	

		  { STATION6, STATION6_SCR,{"Channel1       ^", "Normal         v"}},
		  { STATION6, STATION6_SCR+1,{"               ^", "               v"}},	

		  { STATION7, STATION7_SCR,{"Channel1       ^", "Normal         v"}},
		  { STATION7, STATION7_SCR+1,{"               ^", "               v"}},

		  { STATION8, STATION8_SCR,{"Channel1       ^", "Normal         v"}},
		  { STATION8, STATION8_SCR+1,{"               ^", "               v"}},

		  { STATION9, STATION9_SCR,{"Channel1       ^", "Normal         v"}},
		  { STATION9, STATION9_SCR+1,{"               ^", "               v"}},

		  { STATION10, STATION10_SCR,{"Channel1       ^", "Normal         v"}},
		  { STATION10, STATION10_SCR+1,{"               ^", "               v"}},	
   		   
		//screens added in Ver 1.4  ends here
	/**********************************/	
	   			
		  { OTHER_MODE,OTHER_SCR,  {"Set            ^", "               v" }},
		  { OTHER_MODE,OTHER_SCR+1,{"Remove         ^", "               v" }},
		  { OTHER_MODE,OTHER_SCR+2,{"Already in Test ", "Mode            " }},
   		  { OTHER_MODE,OTHER_SCR+3,{"Can't Execute   ", "loopback        " }},	
       		  
		  { ALARM_MENU_MODE,ALARM_SCR,  {"                ", "               v" }},
		  { ALARM_MENU_MODE,ALARM_SCR+1,{"               ^", "               v" }},
		  { ALARM_MENU_MODE,ALARM_SCR+2,{"               ^", "               v" }},
		  { ALARM_MENU_MODE,ALARM_SCR+3,{"               ^", "               v" }},
		  { ALARM_MENU_MODE,ALARM_SCR+4,{"               ^", "               v" }},
		  { ALARM_MENU_MODE,ALARM_SCR+5,{"               ^", "               v" }},
		  { ALARM_MENU_MODE,ALARM_SCR+6,{"               ^", "               v" }},
		  { ALARM_MENU_MODE,ALARM_SCR+7,{"               ^", "               v" }},
		  { ALARM_MENU_MODE,ALARM_SCR+8,{"               ^", "               v" }},
		  { ALARM_MENU_MODE,ALARM_SCR+9,{"               ^", "               v" }},
		  { ALARM_MENU_MODE,ALARM_SCR+10,{"               ^","               v" }},
		  { ALARM_MENU_MODE,ALARM_SCR+11,{"               ^","               v" }},
		  { ALARM_MENU_MODE,ALARM_SCR+12,{"               ^","               v" }},
		  { ALARM_MENU_MODE,ALARM_SCR+13,{"               ^","               v" }},
		  { ALARM_MENU_MODE,ALARM_SCR+14,{"               ^","               v" }},
		  { ALARM_MENU_MODE,ALARM_SCR+15,{"               ^","               v" }},
		

    };
void reset_lcd_display()		//reset_mtu
{
	if(lcd_reset_flag)
	{
		InitLCD();
		lcd_reset_flag=RESET;
		S_Time12minCnt1=1;
	}
}
void ScreenHandler(void)
{	
	static char xdata CurrentScreenNo=0;
    static unsigned char xdata Firsttime=0,Screenflag =0,ch=0;

	unsigned int xdata value=0;
	unsigned char xdata Key=0;

	unsigned char xdata pos=0;
	unsigned char xdata Majorflag = 0;
	unsigned char xdata Minorflag = 0;
	unsigned char xdata MaxAlarms = 0;
	unsigned char xdata Buffer[20];
	unsigned char xdata Buffer1[20];
	unsigned char xdata Buf[20];	
   	unsigned int xdata i,j,cnt=0;
   	unsigned int ScreenNo = 0;
  	unsigned int ch_st=0;
	unsigned char xdata MaxAlarmScreens=0;
	/**************************************************/          
	 //added in ver 1.4 TO SHOW SCREEN ID
	/*************************************************/
	/*************************/ 
	ScreenNo=STATUS_SCR+1;
	if(!SystemConfig)
		sprintf(Buffer1,"%s","  20W System   v"); /*scr_&_agc_bars*/
	else
		sprintf(Buffer1,"%s","  40W System   v"); /*scr_&_agc_bars*/
	 
	i=0;
	while(i<16)
	{
		Screens[ScreenNo].string[1][i] = Buffer1[i];
		i++;
	}
	/******************************/	
	
	SELF_ADD=((INPORT7_ADD)&(0x0F));
    ScreenNo=STATUS_SCR+3;
	if((SELF_ADD>=1)&&(SELF_ADD<=10))
	{
		sprintf(Buffer1,"%s","Local Terminal ^"); /*scr_&_agc_bars*/
	    if(SELF_ADD==0x01)
	 		sprintf(Buf,"%s","ID : One       v");
	    if(SELF_ADD==0x02)
 			sprintf(Buf,"%s","ID : Two       v");
		if(SELF_ADD==0x03)
 			sprintf(Buf,"%s","ID : Three     v");                
		if(SELF_ADD==0x04)
 			sprintf(Buf,"%s","ID : Four      v");               
		if(SELF_ADD==0x05)
 			sprintf(Buf,"%s","ID : Five      v");                
		if(SELF_ADD==0x06)
 			sprintf(Buf,"%s","ID : Six       v");
		if(SELF_ADD==0x07)
 			sprintf(Buf,"%s","ID : Seven     v");                
		if(SELF_ADD==0x08)
 			sprintf(Buf,"%s","ID : Eight     v");               
		if(SELF_ADD==0x09)
 			sprintf(Buf,"%s","ID : Nine      v");                
		if(SELF_ADD==0x0A)
 			sprintf(Buf,"%s","ID : Ten       v");                                
		i=0;		
	  	while(i<16)
		{
	    	Screens[ScreenNo].string[1][i] = Buf[i];
			i++;
	    }	
		                 
		i=0;		
		while(i<16)
		{
	    	Screens[ScreenNo].string[0][i] = Buffer1[i];
			i++;
	    }
	   				
	    ScreenNo=REMOTE_SCR;
		i=0;		
		while(i<16)
		{
	    	Screens[ScreenNo].string[0][i] = Buffer1[i];
			i++;
	    }
		i=0;		
		while(i<16)
		{
	    	Screens[ScreenNo].string[1][i] = Buf[i];
			i++;
	    }  
	}
	else
   	{	       

		sprintf(Buffer1,"%s","Invalid ID      ");
		sprintf(Buf,"%s","    Settings    ");
    	i=0;		
	  	while(i<16)
		{
	    	Screens[ScreenNo].string[1][i] = Buf[i];
			i++;
	    }	
		                 
		i=0;		
		while(i<16)
		{
	    	Screens[ScreenNo].string[0][i] = Buffer1[i];
			i++;
	    }
	   					
	    ScreenNo=REMOTE_SCR;
		i=0;		
		while(i<16)
		{
	    	Screens[ScreenNo].string[0][i] = Buffer1[i];
			i++;
	    }
		i=0;		
		while(i<16)
		{
	    	Screens[ScreenNo].string[1][i] = Buf[i];
			i++;
	    }  
	}

    /*******************************************/		 	                          
	//END
                
	       
	ScreenNo = ALARM_SCR;
	if(OutputLowAlm)//Ver1.2
	{
		strcpy(Buffer,"O/P LOW ALM    ");
		for(i=0,j=0;i<14;i++,j++)
			Screens[ScreenNo].string[0][j] = Buffer[i];

		ScreenNo++;
		Majorflag = 1;
		MaxAlarms++;
	}
	if(!(OverloadAlm))      
	{
		if(slot5)//added in Ver1.1
    	{
			strcpy(Buffer,"OVERLOAD ALM   ");
			for(i=0,j=0;i<14;i++,j++)
				Screens[ScreenNo].string[0][j] = Buffer[i];
			ScreenNo++;
			Majorflag = 1;
			MaxAlarms++;
        } 
	}
	if(!(FuseAlm))
	{
		if(slot5)  //added in ver1.1
		{	    	   	
			strcpy(Buffer,"PAMP FUSE ALM  ");
			for(i=0,j=0;i<14;i++,j++)
				Screens[ScreenNo].string[0][j] = Buffer[i];
			ScreenNo++;
			Majorflag = 1;
			MaxAlarms++;
		}
    }	
	if(Ch1AgcAlm)
	{
		strcpy(Buffer,"CH1 AGC LOW    ");
		for(i=0,j=0;i<14;i++,j++)
			Screens[ScreenNo].string[0][j] = Buffer[i];
			ScreenNo++;
			Majorflag = 1;
			MaxAlarms++;
	}
	if(Ch2AgcAlm)
	{
		strcpy(Buffer,"CH2 AGC LOW    ");
		for(i=0,j=0;i<14;i++,j++)
			Screens[ScreenNo].string[0][j] = Buffer[i];
		ScreenNo++;
		Majorflag = 1;
		MaxAlarms++;
	}
	if(Ch1SNAlm)
	{
		strcpy(Buffer,"CH1 S/N LOW    ");
		for(i=0,j=0;i<14;i++,j++)
			Screens[ScreenNo].string[0][j] = Buffer[i];
		ScreenNo++;
		Majorflag = 1;
		MaxAlarms++;
	}
	if(Ch2SNAlm)
	{
		strcpy(Buffer,"CH2 S/N LOW    ");
		for(i=0,j=0;i<14;i++,j++)
			Screens[ScreenNo].string[0][j] = Buffer[i];
		ScreenNo++;
		Majorflag = 1;
		MaxAlarms++;
	}
	if(Ch1Mute)
	{
		strcpy(Buffer,"CH1 MUTE       ");
		for(i=0,j=0;i<14;i++,j++)
			Screens[ScreenNo].string[0][j] = Buffer[i];
		ScreenNo++;
		Majorflag = 1;
		MaxAlarms++;
	}
	if(Ch2Mute)
	{
		strcpy(Buffer,"CH2 MUTE       ");
		for(i=0,j=0;i<14;i++,j++)
			Screens[ScreenNo].string[0][j] = Buffer[i];
		ScreenNo++;
		Majorflag = 1;
		MaxAlarms++;
	}
	if(PsuFaulty)
	{
		strcpy(Buffer,"PSU FAULTY     ");
		for(i=0,j=0;i<14;i++,j++)
			Screens[ScreenNo].string[0][j] = Buffer[i];
		ScreenNo++;
		Majorflag = 1;
		MaxAlarms++;
	}
	if(TCXOAlm)
	{
		strcpy(Buffer,"TCXO ALM       ");
		for(i=0,j=0;i<14;i++,j++)
			Screens[ScreenNo].string[0][j] = Buffer[i];
		ScreenNo++;
		Minorflag = 1;
		MaxAlarms++;
	}
	     /*	if(FanAlm)
		  {
			strcpy(Buffer,"FAN ALM        ");
			for(i=0,j=0;i<14;i++,j++)
			Screens[ScreenNo].string[0][j] = Buffer[i];
			ScreenNo++;
			Minorflag = 1;
			MaxAlarms++;
		  }*/
    if(ExtAlm)
	{
		strcpy(Buffer,"EXT ALM        ");
		for(i=0,j=0;i<14;i++,j++)
			Screens[ScreenNo].string[0][j] = Buffer[i];
		ScreenNo++;
		Minorflag = 1;
		MaxAlarms++;
	}
	       
		//Added in Ver1.3 for indicating loopback alarm on screens
	if((Ch1_local_loop)||(Ch2_local_loop)||(Ch1_remote_loop)||(Ch2_remote_loop)||(Ch1_remrem_loop)||(Ch1_remrem_loop))
	{
		strcpy(Buffer,"SYS. IN LOOP   ");
		for(i=0,j=0;i<14;i++,j++)
			Screens[ScreenNo].string[0][j] = Buffer[i];
		ScreenNo++;
		Minorflag = 1;
		MaxAlarms++;
	}
		//ends here	

	if(!(slot1))
	{
		strcpy(Buffer,"VFI1 ABSENT    ");
		for(i=0,j=0;i<14;i++,j++)
	    	Screens[ScreenNo].string[0][j] = Buffer[i];
		ScreenNo++;
    	strcpy(Buffer,"Empty    ^");				/*Gurjit2*/ /*scr_&_agc_bars*/
		for(i=0,j=6;i<14;i++,j++)
	    	Screens[STATUS_SCR+4].string[0][j] = Buffer[i];
		Majorflag = 1;
		MaxAlarms++;
	}
    else
	{
    	strcpy(Buffer,"VFI1     ^");				/*Gurjit2*/ /*scr_&_agc_bars*/
		for(i=0,j=6;i<14;i++,j++)
	    	Screens[STATUS_SCR+4].string[0][j] = Buffer[i];
	}	     		
    		
	if(!(slot2))
	{
		strcpy(Buffer,"CHM1 ABSENT    ");
		for(i=0,j=0;i<14;i++,j++)
			Screens[ScreenNo].string[0][j] = Buffer[i];
		ScreenNo++;
		strcpy(Buffer,"Empty    v");				/*Gurjit2*/ /*scr_&_agc_bars*/
		for(i=0,j=6;i<14;i++,j++)
		   	Screens[STATUS_SCR+4].string[1][j] = Buffer[i];
		Majorflag = 1;
		MaxAlarms++;
	}
	else
 	{
        strcpy(Buffer,"CHM1     v");				/*Gurjit2*/ /*scr_&_agc_bars*/
		for(i=0,j=6;i<14;i++,j++)
			Screens[STATUS_SCR+4].string[1][j] = Buffer[i];
	}
 		
  	if(!(slot5))
	{
		strcpy(Buffer,"PAMP ABSENT    ");
		for(i=0,j=0;i<14;i++,j++)
			Screens[ScreenNo].string[0][j] = Buffer[i];
		ScreenNo++;
		strcpy(Buffer,"Empty    ^");				/*Gurjit2*/ /*scr_&_agc_bars*/
		for(i=0,j=6;i<14;i++,j++)
			Screens[STATUS_SCR+6].string[0][j] = Buffer[i];
		Majorflag = 1;
		MaxAlarms++;
	}
	else
 	{
    	strcpy(Buffer,"PAMP     ^");			/*Gurjit2*/ /*scr_&_agc_bars*/
		for(i=0,j=6;i<14;i++,j++)
	    	Screens[STATUS_SCR+6].string[0][j] = Buffer[i];
	}
 		
   	if(!(slot6))
	{
		strcpy(Buffer,"DIU1 ABSENT    ");
		for(i=0,j=0;i<14;i++,j++)
	    	Screens[ScreenNo].string[0][j] = Buffer[i];
		ScreenNo++;
		strcpy(Buffer,"Empty    v"); /*scr_&_agc_bars*/
		for(i=0,j=6;i<14;i++,j++)
			Screens[STATUS_SCR+6].string[1][j] = Buffer[i];
		Majorflag = 1;
		MaxAlarms++;
	}
	else
 	{
    	strcpy(Buffer,"DIU1     v");			/*Gurjit2*/ /*scr_&_agc_bars*/
		for(i=0,j=6;i<14;i++,j++)
	    	Screens[STATUS_SCR+6].string[1][j] = Buffer[i];
	}
 		
      				
  	if(Twin_ch_system)
	{
		if(!(slot3))
		{
			strcpy(Buffer,"VFI2 ABSENT   ")  ;
			for(i=0,j=0;i<14;i++,j++)
				Screens[ScreenNo].string[0][j] = Buffer[i];
			ScreenNo++;
			strcpy(Buffer,"Empty    ^");				/*Gurjit2*/ /*scr_&_agc_bars*/
		  	for(i=0,j=6;i<14;i++,j++)
				Screens[STATUS_SCR+5].string[0][j] = Buffer[i];
		  	Majorflag = 1;
			MaxAlarms++;
		}
		else
  		{
    		strcpy(Buffer,"VFI2     ^");			/*Gurjit2*/ /*scr_&_agc_bars*/
		  	for(i=0,j=6;i<14;i++,j++)
		    	Screens[STATUS_SCR+5].string[0][j] = Buffer[i];
		}
  		if(!(slot4))
		{
			strcpy(Buffer,"CHM2 ABSENT   ");
			for(i=0,j=0;i<14;i++,j++)
				Screens[ScreenNo].string[0][j] = Buffer[i];
			ScreenNo++;
			strcpy(Buffer,"Empty    v");			/*Gurjit2*/ /*scr_&_agc_bars*/
			for(i=0,j=6;i<14;i++,j++)
		   		Screens[STATUS_SCR+5].string[1][j] = Buffer[i];
			Majorflag = 1;
			MaxAlarms++;
		}
		else
  		{
    		strcpy(Buffer,"CHM2     v");			/*Gurjit2*/ /*scr_&_agc_bars*/
			for(i=0,j=6;i<14;i++,j++)
				Screens[STATUS_SCR+5].string[1][j] = Buffer[i];
		}
  		if(!(slot7))
		{
			strcpy(Buffer,"DIU2 ABSENT   ");
			for(i=0,j=0;i<14;i++,j++)
				Screens[ScreenNo].string[0][j] = Buffer[i];
			ScreenNo++;
			strcpy(Buffer,"Empty    ^");				/*Gurjit2*/ /*scr_&_agc_bars*/
		  	for(i=0,j=6;i<14;i++,j++)
			  	Screens[STATUS_SCR+7].string[0][j] = Buffer[i];
		  	Majorflag = 1;
			MaxAlarms++;
		}
  		else
    	{
      		strcpy(Buffer,"DIU2     ^");		/*Gurjit2*/ /*scr_&_agc_bars*/
		  	for(i=0,j=6;i<14;i++,j++)
		    	Screens[STATUS_SCR+7].string[0][j] = Buffer[i];
		}
    }	
    else
    {
		strcpy(Buffer,"Empty    ^");			/*Gurjit2*/ /*scr_&_agc_bars*/
		for(i=0,j=6;i<14;i++,j++)
		{
    		Screens[STATUS_SCR+5].string[0][j] = Buffer[i];
		  			/*Screens[STATUS_SCR+5].string[1][j] = Buffer[i];*/ /*scr_&_agc_bars*/
 			Screens[STATUS_SCR+7].string[0][j] = Buffer[i];
		}
		strcpy(Buffer,"Empty    v");			/*Gurjit2*/ /*scr_&_agc_bars*/
		for(i=0,j=6;i<14;i++,j++)
			Screens[STATUS_SCR+5].string[1][j] = Buffer[i];
 				
		  		
    }
		
	if(slot8)
	{
		if(loadline)
  		{  
			strcpy(Buffer,"on load        v");		/*Gurjit2*/ /*scr_&_agc_bars*/
			for(i=0,j=0;i<16;i++,j++)
				Screens[STATUS_SCR+8].string[1][j] = Buffer[i];
    		        //added in Ver1.3 as required by Namit 
			strcpy(Buffer,"HF HY. on load");
			for(i=0,j=0;i<14;i++,j++)
				Screens[ScreenNo].string[0][j] = Buffer[i];
			ScreenNo++;
			Majorflag = 1;
			MaxAlarms++;		
		}//ends here 
		else
		{
		   	strcpy(Buffer,"on line        v");
			for(i=0,j=0;i<16;i++,j++)
				Screens[STATUS_SCR+8].string[1][j] = Buffer[i];
    	}
	}
	else
	{
		strcpy(Buffer,"absent         v");			/*Gurjit1*/ /*scr_&_agc_bars*/
		for(i=0,j=0;i<16;i++,j++)
			Screens[STATUS_SCR+8].string[1][j] = Buffer[i];
		strcpy(Buffer,"HF HYB. ABSENT");
		for(i=0,j=0;i<14;i++,j++)
			Screens[ScreenNo].string[0][j] = Buffer[i];	
		ScreenNo++;
		Majorflag = 1;
		MaxAlarms++;		
    }  				
	   //ends here	  

               //added in Ver1.1           
		strcpy(Buffer,"No More Alarms");
		for(i=0,j=0;i<14;i++,j++)
		Screens[ScreenNo].string[0][j] = Buffer[i];
	//ScreenNo++;
	
       if(!(Twin_ch_system))
       {
	   strcpy(Buffer,"Single Ch System");
	   /***************************************************/
	   // MODIFIED SCREENS FOR SINGLE CHANNEL SYSTEM
	   /**************************************************/
	   
	     for(i=0,j=0;i<16;i++,j++)
	    Screens[STATUS_SCR+2].string[0][j] = Buffer[i];
	    strcpy(Buf,"Channel2  N.A. ^");	
	    strcpy(Buffer,"Single Ch Config");	

	        for(i=0,j=0;i<16;i++,j++)
	       	Screens[STATION1_SCR+1].string[0][j] = Buf[i];
			
	    	for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION2_SCR+1].string[0][j] = Buf[i];
		
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION3_SCR+1].string[0][j] = Buf[i];		
		
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION4_SCR+1].string[0][j] = Buf[i];
			
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION5_SCR+1].string[0][j] = Buf[i];
			
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION6_SCR+1].string[0][j] = Buf[i];	
		
		for(i=0,j=0;i<16;i++,j++)
		Screens[STATION7_SCR+1].string[0][j] = Buf[i];
			
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION8_SCR+1].string[0][j] = Buf[i];
			
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION9_SCR+1].string[0][j] = Buf[i];			
		
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION10_SCR+1].string[0][j] = Buf[i];
		
		 for(i=0,j=0;i<16;i++,j++)
	       	Screens[STATION1_SCR+1].string[1][j] = Buffer[i];
			
	    	for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION2_SCR+1].string[1][j] = Buffer[i];
		
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION3_SCR+1].string[1][j] = Buffer[i];		
		
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION4_SCR+1].string[1][j] = Buffer[i];
			
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION5_SCR+1].string[1][j] = Buffer[i];
			
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION6_SCR+1].string[1][j] = Buffer[i];	
		
		for(i=0,j=0;i<16;i++,j++)
		Screens[STATION7_SCR+1].string[1][j] = Buffer[i];
			
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION8_SCR+1].string[1][j] = Buffer[i];
			
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION9_SCR+1].string[1][j] = Buffer[i];			
		
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION10_SCR+1].string[1][j] = Buffer[i];

		/*******************************************************/
			
      }
      else	
      {
	   strcpy(Buffer,"Twin Ch System  ");
	   for(i=0,j=0;i<16;i++,j++)
	   Screens[STATUS_SCR+2].string[0][j] = Buffer[i];
	   /**************************************************/
	   // ADDED IN Ver 1.4
	   /**************************************************/
	       strcpy(Buffer1,"Normal         v");	
	       strcpy(Buf,"Channel2       v");				
		for(i=0,j=0;i<16;i++,j++)
	       	Screens[STATION1_SCR+1].string[0][j] = Buf[i];
			
	    	for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION2_SCR+1].string[0][j] = Buf[i];
		
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION3_SCR+1].string[0][j] = Buf[i];		
		
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION4_SCR+1].string[0][j] = Buf[i];
			
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION5_SCR+1].string[0][j] = Buf[i];
			
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION6_SCR+1].string[0][j] = Buf[i];	
		
		for(i=0,j=0;i<16;i++,j++)
			Screens[STATION7_SCR+1].string[0][j] = Buf[i];
			
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION8_SCR+1].string[0][j] = Buf[i];
			
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION9_SCR+1].string[0][j] = Buf[i];			
		
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION10_SCR+1].string[0][j] = Buf[i];
	
                 for(i=0,j=0;i<16;i++,j++)
	       	Screens[STATION1_SCR+1].string[1][j] = Buffer1[i];
			
	    	for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION2_SCR+1].string[1][j] = Buffer1[i];
		
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION3_SCR+1].string[1][j] = Buffer1[i];		
		
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION4_SCR+1].string[1][j] = Buffer1[i];
			
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION5_SCR+1].string[1][j] = Buffer1[i];
			
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION6_SCR+1].string[1][j] = Buffer1[i];	
		
		for(i=0,j=0;i<16;i++,j++)
		Screens[STATION7_SCR+1].string[1][j] = Buffer1[i];
			
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION8_SCR+1].string[1][j] = Buffer1[i];
			
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION9_SCR+1].string[1][j] = Buffer1[i];			
		
		for(i=0,j=0;i<16;i++,j++)
	        Screens[STATION10_SCR+1].string[1][j] = Buffer1[i];
			
		/*****************************************************/
      }    
      
 	if(MaxAlarms == 0)
	 {
	  ScreenNo = ALARM_SCR;
	  strcpy(Buffer,"NO ALARMS     ");
	  for(i=0,j=0;i<14;i++,j++)
	  Screens[ScreenNo].string[0][j] = Buffer[i];
	 }

 	if(Firsttime == 0)
  	{
   	  CurrentScreenNo = OPENING_SCR;
  	  display(Screens[CurrentScreenNo].string);
	  Firsttime=1;
 	}

	//added in Ver1.1  		
 	if(Majorflag)
	  system_maj_alm = 0;
 	else
	    system_maj_alm = 1;
  	if(Minorflag)	    		
  	   fault_min_alm = 0;
     else 
        fault_min_alm = 1;
        	 	
 	//system_min_alm = 0;  Changed to implement minor alm in case of 
     //else 
      //   system_min_alm = 1;	
    		system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
    OUTPORT2_ADD = Led_cntl;
    //Ends here

	if(key_enter_flag_counter)					/*Gurjit2*/ /*scr_&_agc_bars*/
	{
		key_enter_flag_counter--;
		if(key_enter_flag_counter==0)
		{			
			if((PAMP_scr==1) || (AGC1_scr==1) || (AGC2_scr==1))
			{
				PAMP_scr=0;
				ch_PAMP=0;
				AGC1_scr=0;
				ch1_agc=0;
				AGC2_scr=0;
				ch2_agc=0;
			}			
			AGC1_scr=1;
			key_enter_flag_counter1=MAXTICKCOUNT-50;
		}
	}
	if(key_enter_flag_counter1)
	{
		key_enter_flag_counter1--;
		if(key_enter_flag_counter1==0)
		{
			if(AGC1_scr==1)
			{
				AGC1_scr=0;
				ch1_agc=0;
				AGC2_scr=1;
				key_enter_flag_counter1=MAXTICKCOUNT-50;
			}
			else
			{				
				AGC2_scr=0;
				ch2_agc=0;
				AGC1_scr=1;
				key_enter_flag_counter1=MAXTICKCOUNT-50;
			}
		}

	}											/*Gurjit2*/ /*scr_&_agc_bars*/
   
     	
  Key = KeyBoardScan();

  if(Key != NO_KEY_PRESSED)
   {
    switch(Key)
     {
		case EXECUTE_KEY:

			switch(Screens[CurrentScreenNo].Mode)    //first switch starts
			{//1s
	 
  				case OPEN_MENU_MODE:
 					CurrentScreenNo = MAIN_SCR;
					display(Screens[CurrentScreenNo].string);
					break;
			
    		 
				case MAIN_MENU_MODE:	
					switch(CurrentScreenNo)   
					{ 
						case MAIN_SCR:	// Opening Screen
							CurrentScreenNo = MAIN_SCR;
							display(Screens[CurrentScreenNo].string);
							break;
	
						case MAIN_SCR+1:	// Alarms Screen
							CurrentScreenNo = ALARM_SCR;
							display(Screens[CurrentScreenNo].string);
							break;
	
						case MAIN_SCR+2:	//Status Screen
							CurrentScreenNo = STATUS_SCR;
							display(Screens[CurrentScreenNo].string);
							break;
	       
   						case MAIN_SCR+3:	//Test Screen
							CurrentScreenNo = TEST_SCR;
							display(Screens[CurrentScreenNo].string);
							break;
              
           				default:
             				break;
					} 
					break;
                
				case TEST_MENU_MODE:
					switch(CurrentScreenNo)
					{
						case TEST_SCR:
							CurrentScreenNo = LOCAL_SCR;
							display(Screens[CurrentScreenNo].string);
							break;
						//added in Ver1.3
						case TEST_SCR+1:
							CurrentScreenNo = REMOTE_SCR;
							display(Screens[CurrentScreenNo].string);
							break;
						//ends here
						default:
							break;
					}  
					break;
               
				case LOCAL_LOOPBACK_MODE:
					switch(CurrentScreenNo)
					{
						case LOCAL_SCR:
							Screenflag = 1;
							CurrentScreenNo = OTHER_SCR;
							display(Screens[CurrentScreenNo].string);
							break;

						case LOCAL_SCR+1:
							Screenflag = 2;
							CurrentScreenNo = OTHER_SCR;
							display(Screens[CurrentScreenNo].string);
							break;
				
						default:
							break;
				
					}
   					break;
				/**********************************************************/    
				//added in Ver 1.4 for activating remote loop menu 
				/***********************************************************/ 
				case REMOTE_LOOPBACK_MODE:
                      
					switch(CurrentScreenNo)
	   				{
						case REMOTE_SCR+2:
							if(SELF_ADD==1)
							{
								strcpy(Buf,"Local Station  ");
								for(i=0;i<16;i++)
									Screens[REMOTE_SCR+2].string[1][i]=Buf[i];
								display(Screens[REMOTE_SCR+2].string);
							}
							else
							{
								CurrentScreenNo = STATION1_SCR;
								display(Screens[CurrentScreenNo].string);
								ch_st=1;
							}
							break;
						case REMOTE_SCR+3:
							if(SELF_ADD==2)
							{
                                strcpy(Buf,"Local Station  ");
								for(i=0;i<16;i++)
									Screens[REMOTE_SCR+3].string[1][i]=Buf[i];
								display(Screens[REMOTE_SCR+3].string);
							}
							else
							{
								CurrentScreenNo = STATION2_SCR;
								display(Screens[CurrentScreenNo].string);
								ch_st=1;
							}
	        				break;
						case REMOTE_SCR+4:
							if(SELF_ADD==3)
							{
								strcpy(Buf,"Local Station  ");
								for(i=0;i<16;i++)
									Screens[REMOTE_SCR+4].string[1][i]=Buf[i];
								display(Screens[REMOTE_SCR+4].string);
							}
							else
							{
								CurrentScreenNo = STATION3_SCR;
								display(Screens[CurrentScreenNo].string);
								ch_st=1;
							}
        					break;
						case REMOTE_SCR+5:
							if(SELF_ADD==4)
							{
                                strcpy(Buf,"Local Station  ");
								for(i=0;i<16;i++)
									Screens[REMOTE_SCR+5].string[1][i]=Buf[i];
								display(Screens[REMOTE_SCR+5].string);
							}
							else
							{
								CurrentScreenNo = STATION4_SCR;
								display(Screens[CurrentScreenNo].string);
								ch_st=1;
							}
	        				break;
						case REMOTE_SCR+6:
							if(SELF_ADD==5)
							{
								strcpy(Buf,"Local Station  ");
								for(i=0;i<16;i++)
									Screens[REMOTE_SCR+6].string[1][i]=Buf[i];
								display(Screens[REMOTE_SCR+6].string);
							}
							else
							{
			
								CurrentScreenNo = STATION5_SCR;
								display(Screens[CurrentScreenNo].string);
								ch_st=1;
							}
	        				break;
						case REMOTE_SCR+7:
							if(SELF_ADD==6)
							{
                                strcpy(Buf,"Local Station  ");
								for(i=0;i<16;i++)
									Screens[REMOTE_SCR+7].string[1][i]=Buf[i];
								display(Screens[REMOTE_SCR+7].string);
							}
							else
							{
								CurrentScreenNo = STATION6_SCR;
								display(Screens[CurrentScreenNo].string);
								ch_st=1;
							}
	        				break;
						case REMOTE_SCR+8:
							if(SELF_ADD==7)
							{
                                strcpy(Buf,"Local Station  ");
								for(i=0;i<16;i++)
									Screens[REMOTE_SCR+8].string[1][i]=Buf[i];
								display(Screens[REMOTE_SCR+8].string);
							}
							else
							{
				
								CurrentScreenNo = STATION7_SCR;
								display(Screens[CurrentScreenNo].string);
								ch_st=1;
							}
	        				break;
						case REMOTE_SCR+9:
							if(SELF_ADD==8)
							{
                                strcpy(Buf,"Local Station  ");
								for(i=0;i<16;i++)
									Screens[REMOTE_SCR+9].string[1][i]=Buf[i];
								display(Screens[REMOTE_SCR+9].string);
							}
							else
							{
								CurrentScreenNo = STATION8_SCR;
								display(Screens[CurrentScreenNo].string);
								ch_st=1;
							}
	        				break;
						case REMOTE_SCR+10:
							if(SELF_ADD==9)
							{
								strcpy(Buf,"Local Station  ");
								for(i=0;i<16;i++)
									Screens[REMOTE_SCR+10].string[1][i]=Buf[i];
								display(Screens[REMOTE_SCR+10].string);
							}
							else
							{
			  					CurrentScreenNo = STATION9_SCR;
								display(Screens[CurrentScreenNo].string);
								ch_st=1;
							}
	        				break;
			case REMOTE_SCR+11:
				if(SELF_ADD==10)
				{
                                strcpy(Buf,"Local Station  ");
				for(i=0;i<16;i++)
				Screens[REMOTE_SCR+11].string[1][i]=Buf[i];
				display(Screens[REMOTE_SCR+11].string);
				}
				else
				{
			  	CurrentScreenNo = STATION10_SCR;
				display(Screens[CurrentScreenNo].string);
				ch_st=1;
				}
	        		break;
			default:
			break;
		}break;
/************************************************************                  
//screens added in ver 1.4 to activate station & ch screens  
 *************************************************************/
         case STATION1:
	
           
 	 	switch(CurrentScreenNo)
	   	{
 			case STATION1_SCR:
				Screenflag = 3;
				ST_CHECK=1; 
				ch=1;
				ch_st=0;
				CurrentScreenNo = OTHER_SCR;
				display(Screens[CurrentScreenNo].string);
	        		break;

			case STATION1_MAX_SCR:
				Screenflag = 4;
		    		ST_CHECK=1;		
				ch=2;
				ch_st=0;
				CurrentScreenNo = OTHER_SCR;
				display(Screens[CurrentScreenNo].string);
				break;
			default:
		 	break;
		}
                break;
    	      //************/	
         case STATION2:
	 	switch(CurrentScreenNo)
	   	{
			case STATION2_SCR:
				 Screenflag = 5;
		         	 ST_CHECK=2;
				 ch=1;
				 CurrentScreenNo = OTHER_SCR;
				 display(Screens[CurrentScreenNo].string);
				break;

			case STATION2_MAX_SCR:
				 Screenflag = 6;
				 ST_CHECK=2;
			         ch=2;
				 CurrentScreenNo = OTHER_SCR;
				 display(Screens[CurrentScreenNo].string);
				break;	 
			default:
  			break;
		}break;
    			
         case STATION3:	
	 	switch(CurrentScreenNo)
	   	{
			case STATION3_SCR:
				Screenflag = 7;
		    	 	ST_CHECK=3;
				ch=1;
				CurrentScreenNo = OTHER_SCR;
				display(Screens[CurrentScreenNo].string);
				break;

			case STATION3_MAX_SCR:
				Screenflag = 8;
		    	 	ST_CHECK=3;
				ch=2;
				CurrentScreenNo = OTHER_SCR;
				display(Screens[CurrentScreenNo].string);
	        		break;
			default:
  			break;
		}break;
    			
         case STATION4:
	 	switch(CurrentScreenNo)
	   	{
	       		case STATION4_SCR:
				Screenflag = 9;
		     		ST_CHECK=4;
				ch=1;
				CurrentScreenNo = OTHER_SCR;
				display(Screens[CurrentScreenNo].string);
		   		break;

		       case STATION4_MAX_SCR:
			   	Screenflag = 10;
		       		ST_CHECK=4;
				ch=2;
			   	CurrentScreenNo = OTHER_SCR;
			   	display(Screens[CurrentScreenNo].string);
		   		break;	
			default:
  			break;
		}break;
    			
         case STATION5:    			
	 	switch(CurrentScreenNo)
	   	{
	       		case STATION5_SCR:
				Screenflag = 11;
		    	 	ST_CHECK=5;
				ch=1;
				CurrentScreenNo = OTHER_SCR;
				display(Screens[CurrentScreenNo].string);
	       			break;

	       		case STATION5_SCR+1:
				Screenflag = 12;
		 		ST_CHECK=5;
				ch=2;
				CurrentScreenNo = OTHER_SCR;
				display(Screens[CurrentScreenNo].string);
	       			break;
			default:
  			break;
		}break;
    			
         case STATION6:
	 	switch(CurrentScreenNo)
	   	{
	       		case STATION6_SCR:
				Screenflag = 13;
		 		ST_CHECK=6;
				ch=1;
				CurrentScreenNo = OTHER_SCR;
				display(Screens[CurrentScreenNo].string);
	       			break;

	       		case STATION6_SCR+1:
				Screenflag = 14;
		 		ST_CHECK=6;
				ch=2;
				CurrentScreenNo = OTHER_SCR;
				display(Screens[CurrentScreenNo].string);
	       			break;	
			default:
  			break;
		}break;
    			
         case STATION7:
	 	switch(CurrentScreenNo)
	   	{
	       		case STATION7_SCR:
				Screenflag = 15;
		 		ST_CHECK=7;
				ch=1;
				CurrentScreenNo = OTHER_SCR;
				display(Screens[CurrentScreenNo].string);
	       			break;		
	
	       		case STATION7_SCR+1:
				Screenflag = 16;
		 		ST_CHECK=7;
				ch=2;	
				CurrentScreenNo = OTHER_SCR;
				display(Screens[CurrentScreenNo].string);		
		   		break;	      
			default:
  			break;
		}break;
    			
         case STATION8:	   
	 	switch(CurrentScreenNo)
	   	{
		   	case STATION8_SCR:
				Screenflag = 17;
		 		ST_CHECK=8;
				ch=1;
				CurrentScreenNo = OTHER_SCR;
				display(Screens[CurrentScreenNo].string);	
		   		break;

		   	case STATION8_SCR+1:
				Screenflag = 18;
		 		ST_CHECK=8;
				ch=2;
				CurrentScreenNo = OTHER_SCR;
				display(Screens[CurrentScreenNo].string);	
		   		break;
			default:
  			break;
		}break;
    			
         case STATION9:
	 	switch(CurrentScreenNo)
	   	{
         	       case STATION9_SCR:
				Screenflag = 19;
		 		ST_CHECK=9;
				ch=1;
				CurrentScreenNo = OTHER_SCR;
				display(Screens[CurrentScreenNo].string);	
		   		break;	

	       		case STATION9_SCR+1:
				Screenflag = 20;
		 		ST_CHECK=9;
				ch=2;
				CurrentScreenNo = OTHER_SCR;
				display(Screens[CurrentScreenNo].string);	
		   		break;
			default:
  			break;
		}break;
    			
         case STATION10:
	 	switch(CurrentScreenNo)
	   	{
         		case STATION10_SCR:
				Screenflag = 21;
		 		ST_CHECK=10;
				ch=1;
				CurrentScreenNo = OTHER_SCR;
				display(Screens[CurrentScreenNo].string);	
		   		break;	

		   	case STATION10_SCR+1:
				Screenflag = 22;
		 		ST_CHECK=10;
				ch=2;
				CurrentScreenNo = OTHER_SCR;
				display(Screens[CurrentScreenNo].string);	
		   		break;
		   	default:
	       		break;
		}break;
	  //2e
	 break;
     //till here
	
 case OTHER_MODE:
     switch(CurrentScreenNo)
       {//2s
	 case OTHER_SCR:
	     switch(Screenflag)
	       	{//3s
		  case 1:
		     if(loadline)
			{			 
 			     if(!(Ch1_local_loop))
			  	{ 
			 	CurrentScreenNo = LOCAL_SCR;
				strcpy(Buffer,"Local test mode");
	        		for(i=0,j=0;i<14;i++,j++)
				Screens[CurrentScreenNo].string[1][j] = Buffer[i];
		 		Ch1_local_loop = SET;
			      	Timer10minen1 = SET;
			      	Ch1_test_mode = SET;
		     		System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
		           	//Ver1.1
				 Ch1_loop_min_alm = 0;
		        	 system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
	     		       //ends here
	            		OUTPORT2_ADD = Led_cntl;
		     		OUTPORT1_ADD = loop_status;
	       	    		} 
	       	   else
			  CurrentScreenNo = OTHER_SCR+2;
		        }
      		       	else
       	   	        CurrentScreenNo = OTHER_SCR+3;			
		       	display(Screens[CurrentScreenNo].string);
		      
		break;

	  case 2:
		    if(loadline)
  		      {
       		   	if(!(Ch2_local_loop))
			   {
			   CurrentScreenNo = LOCAL_SCR+1;
			   strcpy(Buffer,"Local test mode");
			   for(i=0,j=0;i<14;i++,j++)
			   Screens[CurrentScreenNo].string[1][j] = Buffer[i];
			   Ch2_local_loop = SET;
	      		   Timer10minen2 = SET;
	      		   Ch2_test_mode = SET;
     		     	   System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	      		  //Ver1.1
			   Ch2_loop_min_alm = 0;
               	    	   system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                          //ends here
                          OUTPORT2_ADD = Led_cntl;
	      		  OUTPORT1_ADD = loop_status;
       	               	  } 
			  else
			  CurrentScreenNo = OTHER_SCR+2;
		     } 
       		     else
		     CurrentScreenNo = OTHER_SCR+3;
		     display(Screens[CurrentScreenNo].string);
		     break;
                     //Ver1.2 added for remote loop
	  case 3:
	       if(!(loadline))
  		 {
       		   if(!(Ch1_remote_loop))
		      {
		      ST_CHECK=1;
		      Remoteloop(RL1,ST_CHECK);   //modified in ver 1.4 to set the remote loop for ch1 of station 1
		      CurrentScreenNo = STATION1_SCR;
	              strcpy(Buffer,"In Remote Loop");
		      for(i=0,j=0;i<14;i++,j++)
		      Screens[CurrentScreenNo].string[1][j] = Buffer[i];
		      Ch1_remote_loop = SET;
	      	      Timer10minen3 = SET;
	      	      Ch1_test_mode = SET;
     		      System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	      	      //Ver1.1
		      Ch1_loop_min_alm = 0;
              	      system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
              	      //ends here
                      OUTPORT2_ADD = Led_cntl;
	      	      OUTPORT1_ADD = loop_status;
       	              } 
		      else
		      CurrentScreenNo = OTHER_SCR+2;
			} 
       		else
			CurrentScreenNo = OTHER_SCR+3;
			display(Screens[CurrentScreenNo].string);
		
		break;

	case 4:
if(Twin_ch_system)	
     {
        if(!(loadline))
  		 {
       		   if(!(Ch2_remote_loop))
		      {
                      ST_CHECK=1;
		      Remoteloop(RL2,ST_CHECK); //modified in ver 1.4 to set the remote loop for ch2 of station 2
                      CurrentScreenNo = STATION1_SCR+1;
		      strcpy(Buffer,"In Remote Loop");
		      for(i=0,j=0;i<14;i++,j++)
		      Screens[CurrentScreenNo].string[1][j] = Buffer[i];
		      Ch2_remote_loop = SET;
	      	  Timer10minen4 = SET;
	      	  Ch2_test_mode = SET;
     		  System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	      	  //Ver1.1
		      Ch2_loop_min_alm = 0;
              system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
              //ends here
              OUTPORT2_ADD = Led_cntl;
	      	  OUTPORT1_ADD = loop_status;
       	      } 
		      else
		      CurrentScreenNo = OTHER_SCR+2;
		   } 
       		  else
		   CurrentScreenNo = OTHER_SCR+3;
		   display(Screens[CurrentScreenNo].string);
     }		   
		break;
                      
	case 5:
 		  	
	    if(!(loadline))
  	       {
       		  if(!(Ch1_remote_loop))
		     {
		     ST_CHECK=2;
		     Remoteloop(RL1,ST_CHECK); //modified in ver 1.4 to set the remote loop for ch1 of station 2
		     CurrentScreenNo = STATION2_SCR;
		     strcpy(Buffer,"In Remote Loop");
		     for(i=0,j=0;i<14;i++,j++)
		     Screens[CurrentScreenNo].string[1][j] = Buffer[i];
		     Ch1_remote_loop = SET;
	      	     Timer10minen3 = SET;
	      	     Ch1_test_mode = SET;
     		     System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	      	     //Ver1.1
		     Ch1_loop_min_alm = 0;
        	     system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
      	       //ends here
     	             OUTPORT2_ADD = Led_cntl;
	      	     OUTPORT1_ADD = loop_status;
       	     } 
		   else	
		    CurrentScreenNo = OTHER_SCR+2;
 	       } 
       	      else
	       CurrentScreenNo = OTHER_SCR+3;
	       display(Screens[CurrentScreenNo].string);
	       break;

	case 6:
    if(Twin_ch_system)	
      {
            if(!(loadline))
  		{
       		   if(!(Ch2_remote_loop))
		      {

				 ST_CHECK=2;
				 Remoteloop(RL2,ST_CHECK); //modified in ver 1.4 to set the remote loop for ch2 of station 2

			     CurrentScreenNo = STATION2_SCR+1;
			     strcpy(Buffer,"In Remote Loop");
			     for(i=0,j=0;i<14;i++,j++)
			     Screens[CurrentScreenNo].string[1][j] = Buffer[i];
			     Ch2_remote_loop = SET;
	      		 Timer10minen4 = SET;
	      		 Ch2_test_mode = SET;
     		     System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	      		     //Ver1.1
		         Ch2_loop_min_alm = 0;
               	 system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                 //ends here
                 OUTPORT2_ADD = Led_cntl;
	      		 OUTPORT1_ADD = loop_status;
       	     } 
			    else
			     CurrentScreenNo = OTHER_SCR+2;
 			  } 
       		  	  else
			   CurrentScreenNo = OTHER_SCR+3;
		           display(Screens[CurrentScreenNo].string);
	        }
		   break;



		   	 case 7:
			if(!(loadline))
  			  {
       		       if(!(Ch1_remote_loop))
			    {
			     
				ST_CHECK=3;
		        Remoteloop(RL1,ST_CHECK);//modified in ver 1.4 to set the remote loop for ch1 of station 3	
			
			     CurrentScreenNo = STATION3_SCR;
			     strcpy(Buffer,"In Remote Loop");
			     for(i=0,j=0;i<14;i++,j++)
			     Screens[CurrentScreenNo].string[1][j] = Buffer[i];
			     Ch1_remote_loop = SET;
	      		 Timer10minen3 = SET;
	      		 Ch1_test_mode = SET;
     		     System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	      		     //Ver1.1
		         Ch1_loop_min_alm = 0;
               	 system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                 //ends here
                 OUTPORT2_ADD = Led_cntl;
	      		 OUTPORT1_ADD = loop_status;
       	        } 
			    else
			     CurrentScreenNo = OTHER_SCR+2;
 			  } 
       		  	  else
			   CurrentScreenNo = OTHER_SCR+3;
		           display(Screens[CurrentScreenNo].string);
			   break;

			case 8:
	if(Twin_ch_system)	
      	      {
                  	if(!(loadline))
  			  {
       		   	   if(!(Ch2_remote_loop))
			    {
			     
			    ST_CHECK=3;
		      	    Remoteloop(RL2,ST_CHECK);  //modified in ver 1.4 to set the remote loop for ch2 of station 3
		            CurrentScreenNo = STATION3_SCR+1;
			     strcpy(Buffer,"In Remote Loop");
			     for(i=0,j=0;i<14;i++,j++)
			     Screens[CurrentScreenNo].string[1][j] = Buffer[i];
			     Ch2_remote_loop = SET;
	      		 Timer10minen4 = SET;
	      		 Ch2_test_mode = SET;
     		     System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	      		 //Ver1.1
		         Ch2_loop_min_alm = 0;
               	 system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                 //ends here
                OUTPORT2_ADD = Led_cntl;
	      		OUTPORT1_ADD = loop_status;
       	               	     } 
			    else
			     CurrentScreenNo = OTHER_SCR+2;
 			  } 
       		  	  else
			   CurrentScreenNo = OTHER_SCR+3;
		           display(Screens[CurrentScreenNo].string);
		}	
		   break;

			case 9:
			if(!(loadline))
  			  {
       		   	   if(!(Ch1_remote_loop))
			    {
			     
				ST_CHECK=4;
		     	 Remoteloop(RL1,ST_CHECK);  //modified in ver 1.4 to set the remote loop for ch1 of station 4	
		          CurrentScreenNo = STATION4_SCR;
			     strcpy(Buffer,"In Remote Loop");
			     for(i=0,j=0;i<14;i++,j++)
			     Screens[CurrentScreenNo].string[1][j] = Buffer[i];
			     Ch1_remote_loop = SET;
	      		     Timer10minen3 = SET;
	      		     Ch1_test_mode = SET;
     		     	     System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	      		     //Ver1.1
		             Ch1_loop_min_alm = 0;
               	    	     system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                             //ends here
                             OUTPORT2_ADD = Led_cntl;
	      		     OUTPORT1_ADD = loop_status;
       	               	     } 
			    else
			     CurrentScreenNo = OTHER_SCR+2;
 			  } 
       		  	  else
			   CurrentScreenNo = OTHER_SCR+3;
		           display(Screens[CurrentScreenNo].string);
			   break;

			case 10:
	if(Twin_ch_system)	
      	     {

			if(!(loadline))
  			  {
       		   	   if(!(Ch2_remote_loop))
			    {
			     
			      ST_CHECK=4;
		     	       Remoteloop(RL2,ST_CHECK);    //modified in ver 1.4 to set the remote loop for ch2 of station 4

		     	          CurrentScreenNo = STATION4_SCR+1;
			     strcpy(Buffer,"In Remote Loop");
			     for(i=0,j=0;i<14;i++,j++)
			     Screens[CurrentScreenNo].string[1][j] = Buffer[i];
			     Ch2_remote_loop = SET;
	      		     Timer10minen4 = SET;
	      		     Ch2_test_mode = SET;
     		     	     System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	      		     //Ver1.1
		             Ch2_loop_min_alm = 0;
               	    	     system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                             //ends here
                             OUTPORT2_ADD = Led_cntl;
	      		     OUTPORT1_ADD = loop_status;
       	               	     } 
			    else
			     CurrentScreenNo = OTHER_SCR+2;
 			  } 
       		  	  else
			   CurrentScreenNo = OTHER_SCR+3;
		           display(Screens[CurrentScreenNo].string);
		}	   
		break;


			case 11:
			if(!(loadline))
  			  {
       		   	   if(!(Ch1_remote_loop))
			    {
			     
			ST_CHECK=5;
		      Remoteloop(RL1,ST_CHECK);	//modified in ver 1.4 to set the remote loop for ch1 of station 5
		      
			     CurrentScreenNo = STATION5_SCR;
			     strcpy(Buffer,"In Remote Loop");
			     for(i=0,j=0;i<14;i++,j++)
			     Screens[CurrentScreenNo].string[1][j] = Buffer[i];
			     Ch1_remote_loop = SET;
	      		 Timer10minen3 = SET;
	      		     Ch1_test_mode = SET;
     		     	     System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	      		     //Ver1.1
		             Ch1_loop_min_alm = 0;
               	    	     system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                             //ends here
                             OUTPORT2_ADD = Led_cntl;
	      		     OUTPORT1_ADD = loop_status;
       	               	     } 
			    else
			     CurrentScreenNo = OTHER_SCR+2;
 			  } 
       		  	  else
			   CurrentScreenNo = OTHER_SCR+3;
		           display(Screens[CurrentScreenNo].string);
			   break;


		case 12:
	if(Twin_ch_system)	
      	     {
			if(!(loadline))
  			  {
       		   	   if(!(Ch2_remote_loop))
			    {
			    
			ST_CHECK=5;
		     Remoteloop(RL2,ST_CHECK);//modified in ver 1.4 to set the remote loop for ch2 of station 5	
		     
			     CurrentScreenNo = STATION5_SCR+1;
			     strcpy(Buffer,"In Remote Loop");
			     for(i=0,j=0;i<14;i++,j++)
			     Screens[CurrentScreenNo].string[1][j] = Buffer[i];
			     Ch2_remote_loop = SET;
	      		     Timer10minen4 = SET;
	      		     Ch2_test_mode = SET;
     		     	     System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	      		     //Ver1.1
		             Ch2_loop_min_alm = 0;
               	    	     system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                             //ends here
                             OUTPORT2_ADD = Led_cntl;
	      		     OUTPORT1_ADD = loop_status;
       	               	     } 
			    else
			     CurrentScreenNo = OTHER_SCR+2;
 			  } 
       		  	  else
			   CurrentScreenNo = OTHER_SCR+3;
		           display(Screens[CurrentScreenNo].string);
		}
			   break;

	        	case 13:
			if(!(loadline))
  			  {
       		   	   if(!(Ch1_remote_loop))
			    {
			    
			ST_CHECK=6;
		     Remoteloop(RL1,ST_CHECK);	//modified in ver 1.4 to set the remote loop for ch1 of station 6
		    
			     CurrentScreenNo = STATION6_SCR;
			     strcpy(Buffer,"In Remote Loop");
			     for(i=0,j=0;i<14;i++,j++)
			     Screens[CurrentScreenNo].string[1][j] = Buffer[i];
			     Ch1_remote_loop = SET;
	      		     Timer10minen3 = SET;
	      		     Ch1_test_mode = SET;
     		     	     System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	      		     //Ver1.1
		             Ch1_loop_min_alm = 0;
               	    	     system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                             //ends here
                             OUTPORT2_ADD = Led_cntl;
	      		     OUTPORT1_ADD = loop_status;
       	               	     } 
			    else
			     CurrentScreenNo = OTHER_SCR+2;
 			  } 
       		  	  else
			   CurrentScreenNo = OTHER_SCR+3;
		           display(Screens[CurrentScreenNo].string);
			   break;

		
			case 14:
	if(Twin_ch_system)	
      	     {
			if(!(loadline))
  			  {
       		   	   if(!(Ch2_remote_loop))
			    {
			     
			ST_CHECK=6;
		      Remoteloop(RL2,ST_CHECK);	//modified in ver 1.4 to set the remote loop for ch2 of station 6
		      
			     CurrentScreenNo = STATION6_SCR+1;
			     strcpy(Buffer,"In Remote Loop");
			     for(i=0,j=0;i<14;i++,j++)
			     Screens[CurrentScreenNo].string[1][j] = Buffer[i];
			     Ch2_remote_loop = SET;
	      		     Timer10minen4 = SET;
	      		     Ch2_test_mode = SET;
     		     	     System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	      		     //Ver1.1
		             Ch2_loop_min_alm = 0;
               	    	     system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                             //ends here
                             OUTPORT2_ADD = Led_cntl;
	      		     OUTPORT1_ADD = loop_status;
       	               	     } 
			    else
			     CurrentScreenNo = OTHER_SCR+2;
 			  } 
       		  	  else
			   CurrentScreenNo = OTHER_SCR+3;
		           display(Screens[CurrentScreenNo].string);
		   }
			   break;

			case 15:
			if(!(loadline))
  			  {
       		   	   if(!(Ch1_remote_loop))
			    {
			     
			ST_CHECK=7;
		      Remoteloop(RL1,ST_CHECK);	//modified in ver 1.4 to set the remote loop for ch1 of station 7
		      
			     CurrentScreenNo = STATION7_SCR;
			     strcpy(Buffer,"In Remote Loop");
			     for(i=0,j=0;i<14;i++,j++)
			     Screens[CurrentScreenNo].string[1][j] = Buffer[i];
			     Ch1_remote_loop = SET;
	      		     Timer10minen3 = SET;
	      		     Ch1_test_mode = SET;
     		     	     System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	      		     //Ver1.1
		             Ch1_loop_min_alm = 0;
               	    	     system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                             //ends here
                             OUTPORT2_ADD = Led_cntl;
	      		     OUTPORT1_ADD = loop_status;
       	               	     } 
			    else
			     CurrentScreenNo = OTHER_SCR+2;
 			  } 
       		  	  else
			   CurrentScreenNo = OTHER_SCR+3;
		           display(Screens[CurrentScreenNo].string);
			   break;


			case 16:
	if(Twin_ch_system)	
      	     {
			if(!(loadline))
  			  {
       		   	   if(!(Ch2_remote_loop))
			    {
			    
				ST_CHECK=7;
			     	 Remoteloop(RL2,ST_CHECK); //modified in ver 1.4 to set the remote loop for ch2 of station 7	
		     
			     CurrentScreenNo = STATION7_SCR+1;
			     strcpy(Buffer,"In Remote Loop");
			     for(i=0,j=0;i<14;i++,j++)
			     Screens[CurrentScreenNo].string[1][j] = Buffer[i];
			     Ch2_remote_loop = SET;
	      		     Timer10minen4 = SET;
	      		     Ch2_test_mode = SET;
     		     	     System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	      		     //Ver1.1
		             Ch2_loop_min_alm = 0;
               	    	     system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                             //ends here
                             OUTPORT2_ADD = Led_cntl;
	      		     OUTPORT1_ADD = loop_status;
       	               	     } 
			    else
			     CurrentScreenNo = OTHER_SCR+2;
 			  } 
       		  	  else
			   CurrentScreenNo = OTHER_SCR+3;
		           display(Screens[CurrentScreenNo].string);
			}
			   break;

			case 17:
			if(!(loadline))
  			  {
       		   	   if(!(Ch1_remote_loop))
			    {
			     
			ST_CHECK=8;
		      Remoteloop(RL1,ST_CHECK);	//modified in ver 1.4 to set the remote loop for ch1 of station 8
		     
			     CurrentScreenNo = STATION8_SCR;
			     strcpy(Buffer,"In Remote Loop");
			     for(i=0,j=0;i<14;i++,j++)
			     Screens[CurrentScreenNo].string[1][j] = Buffer[i];
			     Ch1_remote_loop = SET;
	      		     Timer10minen3 = SET;
	      		     Ch1_test_mode = SET;
     		     	     System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	      		     //Ver1.1
		             Ch1_loop_min_alm = 0;
               	    	     system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                             //ends here
                             OUTPORT2_ADD = Led_cntl;
	      		     OUTPORT1_ADD = loop_status;
       	               	     } 
			    else
			     CurrentScreenNo = OTHER_SCR+2;
 			  } 
       		  	  else
			   CurrentScreenNo = OTHER_SCR+3;
		           display(Screens[CurrentScreenNo].string);
			   break;

                    case 18:
	if(Twin_ch_system)	
      	     {
			if(!(loadline))
  			  {
       		   	   if(!(Ch2_remote_loop))
			    {
			    ST_CHECK=8;
			      Remoteloop(RL2,ST_CHECK);	//modified in ver 1.4 to set the remote loop for ch2 of station 8
		     
			     CurrentScreenNo = STATION8_SCR+1;
			     strcpy(Buffer,"In Remote Loop");
			     for(i=0,j=0;i<14;i++,j++)
			     Screens[CurrentScreenNo].string[1][j] = Buffer[i];
			     Ch2_remote_loop = SET;
	      		     Timer10minen4 = SET;
	      		     Ch2_test_mode = SET;
     		     	     System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	      		     //Ver1.1
		             Ch2_loop_min_alm = 0;
               	    	     system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                             //ends here
                             OUTPORT2_ADD = Led_cntl;
	      		     OUTPORT1_ADD = loop_status;
       	               	     } 
			    else
			     CurrentScreenNo = OTHER_SCR+2;
 			  } 
       		  	  else
			   CurrentScreenNo = OTHER_SCR+3;
		           display(Screens[CurrentScreenNo].string);
		}
			   break;

			case 19:
			if(!(loadline))
  			  {
       		   	   if(!(Ch1_remote_loop))
			    {
			     ST_CHECK=9;
		             Remoteloop(RL1,ST_CHECK);	//modified in ver 1.4 to set the remote loop for ch1 of station 9
		     
			     CurrentScreenNo = STATION9_SCR;
			     strcpy(Buffer,"In Remote Loop");
			     for(i=0,j=0;i<14;i++,j++)
			     Screens[CurrentScreenNo].string[1][j] = Buffer[i];
			     Ch1_remote_loop = SET;
	      		     Timer10minen3 = SET;
	      		     Ch1_test_mode = SET;
     		     	     System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	      		     //Ver1.1
		             Ch1_loop_min_alm = 0;
               	    	     system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                             //ends here
                             OUTPORT2_ADD = Led_cntl;
	      		     OUTPORT1_ADD = loop_status;
       	               	     } 
			    else
			     CurrentScreenNo = OTHER_SCR+2;
 			  } 
       		  	  else
			   CurrentScreenNo = OTHER_SCR+3;
		           display(Screens[CurrentScreenNo].string);
			   break;

                           case 20:
	if(Twin_ch_system)	
      	     {
			if(!(loadline))
  			  {
       		   	   if(!(Ch2_remote_loop))
			    {
			     
			ST_CHECK=9;
		      Remoteloop(RL2,ST_CHECK);	//modified in ver 1.4 to set the remote loop for ch2 of station 9
		     
			     CurrentScreenNo = STATION9_SCR+1;
			     strcpy(Buffer,"In Remote Loop");
			     for(i=0,j=0;i<14;i++,j++)
			     Screens[CurrentScreenNo].string[1][j] = Buffer[i];
			     Ch2_remote_loop = SET;
	      		     Timer10minen4 = SET;
	      		     Ch2_test_mode = SET;
     		     	     System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	      		     //Ver1.1
		             Ch2_loop_min_alm = 0;
               	    	     system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                             //ends here
                             OUTPORT2_ADD = Led_cntl;
	      		     OUTPORT1_ADD = loop_status;
       	               	     } 
			    else
			     CurrentScreenNo = OTHER_SCR+2;
 			  } 
       		  	  else
			   CurrentScreenNo = OTHER_SCR+3;
		           display(Screens[CurrentScreenNo].string);
		}
			   break;

				
            case 21:
			if(!(loadline))
  			  {
       		   	   if(!(Ch1_remote_loop))
			    {
			    
			     ST_CHECK=10;
		      	    Remoteloop(RL1,ST_CHECK);  //modified in ver 1.4 to set the remote loop for ch1 of station 10	
		     
			     CurrentScreenNo = STATION10_SCR;
			     strcpy(Buffer,"In Remote Loop");
			     for(i=0,j=0;i<14;i++,j++)
			     Screens[CurrentScreenNo].string[1][j] = Buffer[i];
			     Ch1_remote_loop = SET;
	      		     Timer10minen3 = SET;
	      		     Ch1_test_mode = SET;
     		    	     System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	      		     //Ver1.1
		             Ch1_loop_min_alm = 0;
               	 	     system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                             //ends here
                     	     OUTPORT2_ADD = Led_cntl;
	      		     OUTPORT1_ADD = loop_status;
       	               	     } 
			    else
			     CurrentScreenNo = OTHER_SCR+2;
 			  } 
       		  	  else
			   CurrentScreenNo = OTHER_SCR+3;
		           display(Screens[CurrentScreenNo].string);
			   break;

			case 22:
	if(Twin_ch_system)	
      	     {
			if(!(loadline))
  			  {
       		   	   if(!(Ch2_remote_loop))
			    {
			     
			ST_CHECK=10;
		      Remoteloop(RL2,ST_CHECK);	//modified in ver 1.4 to set the remote loop for ch2 of station 10
		     
			     CurrentScreenNo = STATION10_SCR+1;
			     strcpy(Buffer,"In Remote Loop");
			     for(i=0,j=0;i<14;i++,j++)
			     Screens[CurrentScreenNo].string[1][j] = Buffer[i];
			     Ch2_remote_loop = SET;
	      		     Timer10minen4 = SET;
	      		     Ch2_test_mode = SET;
     		     	     System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	      		     //Ver1.1
		             Ch2_loop_min_alm = 0;
               	    	     system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                             //ends here
                             OUTPORT2_ADD = Led_cntl;
	      		     OUTPORT1_ADD = loop_status;
       	               	     } 
			    else
			     CurrentScreenNo = OTHER_SCR+2;
 			  } 
       		  	  else
			   CurrentScreenNo = OTHER_SCR+3;
		           display(Screens[CurrentScreenNo].string);
		}
			   break;


			//till here
			default:
			break;
			}//3e
			break;
			
   		 case OTHER_SCR+1:
		   switch(Screenflag)
		    {//3s
		     case 1:
		       CurrentScreenNo = LOCAL_SCR;
		       strcpy(Buffer,"Normal         ");
		       for(i=0,j=0;i<14;i++,j++)
		       Screens[CurrentScreenNo].string[1][j] = Buffer[i];
		       display(Screens[CurrentScreenNo].string);
          	       Ch1_local_loop = RESET;
	       	       Timer10minen1 = RESET;
	       	       Ch1_test_mode = RESET;
     	       	       System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	       	       //Ver1.1
		       Ch1_loop_min_alm = 1;
               	       system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                       //ends here
                       OUTPORT2_ADD = Led_cntl;
               	       OUTPORT1_ADD = loop_status;	
		      break;
		      
		       case 2:
		       CurrentScreenNo = LOCAL_SCR+1;
		       strcpy(Buffer,"Normal         ");
		       for(i=0,j=0;i<14;i++,j++)
		       Screens[CurrentScreenNo].string[1][j] = Buffer[i];
		       display(Screens[CurrentScreenNo].string);
 		       Ch2_local_loop = RESET;
	       	       Timer10minen2 = RESET;
	       	       Ch2_test_mode = RESET;
     	       	       //Ver1.1
		       Ch2_loop_min_alm = 1;
               	       system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                       //ends here
                       System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	       	       OUTPORT2_ADD = Led_cntl;
               	       OUTPORT1_ADD = loop_status;			      
         	       break;
			/***********************************************/
			//added in Ver1.4 for to reset the remote loop 	
			/************************************************/	      
		       case 3:
		       Remoteloop(RL3,ST_CHECK);	
		       CurrentScreenNo = STATION1_SCR;
		       strcpy(Buffer,"Normal         ");
		       for(i=0,j=0;i<14;i++,j++)
		       Screens[CurrentScreenNo].string[1][j] = Buffer[i];
		       display(Screens[CurrentScreenNo].string);
 		       Ch1_remote_loop = RESET;
	       	       Timer10minen3 = RESET;
	       	       Ch1_test_mode = RESET;
     	      	       //Ver1.1
		       Ch1_loop_min_alm = 1;
               	       system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                       //ends here
                       System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	       	       OUTPORT2_ADD = Led_cntl;
               	       OUTPORT1_ADD = loop_status;			      
         	       break;
		      
		       case 4:
	if(Twin_ch_system)	
      	     {
		       Remoteloop(RL4,ST_CHECK);
		       CurrentScreenNo = STATION1_SCR+1;
		       strcpy(Buffer,"Normal         ");
		       for(i=0,j=0;i<14;i++,j++)
		       Screens[CurrentScreenNo].string[1][j] = Buffer[i];
		       display(Screens[CurrentScreenNo].string);
 		       Ch2_remote_loop = RESET;
	       	       Timer10minen4 = RESET;
	       	       Ch2_test_mode = RESET;
     	       	       //Ver1.1
		       Ch2_loop_min_alm = 1;
               	       system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                       //ends here
              		 System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	       	   	OUTPORT2_ADD = Led_cntl;
	               OUTPORT1_ADD = loop_status;			      
	      }	
         	   break;
		       
		       case 5:
		       Remoteloop(RL3,ST_CHECK);
		       CurrentScreenNo = STATION2_SCR;
		       strcpy(Buffer,"Normal         ");
		       for(i=0,j=0;i<14;i++,j++)
		       Screens[CurrentScreenNo].string[1][j] = Buffer[i];
		       display(Screens[CurrentScreenNo].string);
 		       Ch1_remote_loop = RESET;
	       	       Timer10minen3 = RESET;
	       	       Ch1_test_mode = RESET;
     	      	       //Ver1.1
		       Ch1_loop_min_alm = 1;
               	       system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                       //ends here
                       System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	       	       OUTPORT2_ADD = Led_cntl;
               	       OUTPORT1_ADD = loop_status;			      
		
         	       break;
		      
		       case 6:
	if(Twin_ch_system)	
      	     	{
		       Remoteloop(RL4,ST_CHECK);
		       CurrentScreenNo = STATION2_SCR+1;
		       strcpy(Buffer,"Normal         ");
		       for(i=0,j=0;i<14;i++,j++)
		       Screens[CurrentScreenNo].string[1][j] = Buffer[i];
		       display(Screens[CurrentScreenNo].string);
 		       Ch2_remote_loop = RESET;
	       	      Timer10minen4 = RESET;
	       	      Ch2_test_mode = RESET;
     	       	       //Ver1.1
		       Ch2_loop_min_alm = 1;
	               system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                       //ends here
	               System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
		       OUTPORT2_ADD = Led_cntl;
	               OUTPORT1_ADD = loop_status;			      
		}
         	   break;
					   
		       	case 7:
		       Remoteloop(RL3,ST_CHECK);
		       CurrentScreenNo = STATION3_SCR;
		       strcpy(Buffer,"Normal         ");
		       for(i=0,j=0;i<14;i++,j++)
		       Screens[CurrentScreenNo].string[1][j] = Buffer[i];
		       display(Screens[CurrentScreenNo].string);
 		       Ch1_remote_loop = RESET;
	       	       Timer10minen3 = RESET;
	       	       Ch1_test_mode = RESET;
     	      	       //Ver1.1
		       Ch1_loop_min_alm = 1;
               	       system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                       //ends here
                       System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	       	       OUTPORT2_ADD = Led_cntl;
               	       OUTPORT1_ADD = loop_status;			      
         	       break;
		      
		       case 8:
	if(Twin_ch_system)	
      	     {
		       Remoteloop(RL4,ST_CHECK);
		       CurrentScreenNo = STATION3_SCR+1;
		       strcpy(Buffer,"Normal         ");
		       for(i=0,j=0;i<14;i++,j++)
		       Screens[CurrentScreenNo].string[1][j] = Buffer[i];
		       display(Screens[CurrentScreenNo].string);
 		       Ch2_remote_loop = RESET;
	       	       Timer10minen4 = RESET;
	       	       Ch2_test_mode = RESET;
     	       	       //Ver1.1
			   Ch2_loop_min_alm = 1;
	               system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                       //ends here
               System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	       	   OUTPORT2_ADD = Led_cntl;
               OUTPORT1_ADD = loop_status;			      
	}
         	   break;
   
				   
				case 9:
		       Remoteloop(RL3,ST_CHECK);
		       CurrentScreenNo = STATION4_SCR;
		       strcpy(Buffer,"Normal         ");
		       for(i=0,j=0;i<14;i++,j++)
		       Screens[CurrentScreenNo].string[1][j] = Buffer[i];
		       display(Screens[CurrentScreenNo].string);
 		       Ch1_remote_loop = RESET;
	       	       Timer10minen3 = RESET;
	       	       Ch1_test_mode = RESET;
     	      	       //Ver1.1
		       Ch1_loop_min_alm = 1;
               	       system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                       //ends here
                       System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	       	       OUTPORT2_ADD = Led_cntl;
               	       OUTPORT1_ADD = loop_status;			      
         	       break;
		      
		       case 10:
	if(Twin_ch_system)	
      	     {
		       Remoteloop(RL4,ST_CHECK);
		       CurrentScreenNo = STATION4_SCR+1;
		       strcpy(Buffer,"Normal         ");
		       for(i=0,j=0;i<14;i++,j++)
		       Screens[CurrentScreenNo].string[1][j] = Buffer[i];
		       display(Screens[CurrentScreenNo].string);
 		       Ch2_remote_loop = RESET;
		       Timer10minen4 = RESET;
	       	       Ch2_test_mode = RESET;
     	       	       //Ver1.1
		       Ch2_loop_min_alm = 1;
              	       system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                       //ends here
                      System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	       	      OUTPORT2_ADD = Led_cntl;
                      OUTPORT1_ADD = loop_status;			      
		}
         	   break;
   
				case 11:
		       Remoteloop(RL3,ST_CHECK);
		       CurrentScreenNo = STATION5_SCR;
		       strcpy(Buffer,"Normal         ");
		       for(i=0,j=0;i<14;i++,j++)
		       Screens[CurrentScreenNo].string[1][j] = Buffer[i];
		       display(Screens[CurrentScreenNo].string);
 		       Ch1_remote_loop = RESET;
	       	       Timer10minen3 = RESET;
	       	       Ch1_test_mode = RESET;
     	      	       //Ver1.1
		       Ch1_loop_min_alm = 1;
               	       system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                       //ends here
                       System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	       	       OUTPORT2_ADD = Led_cntl;
               	       OUTPORT1_ADD = loop_status;			      
         	       break;
		      
		       case 12:
	if(Twin_ch_system)	
      	     {
		       Remoteloop(RL4,ST_CHECK);
		       CurrentScreenNo = STATION5_SCR+1;
		       strcpy(Buffer,"Normal         ");
		       for(i=0,j=0;i<14;i++,j++)
		       Screens[CurrentScreenNo].string[1][j] = Buffer[i];
		       display(Screens[CurrentScreenNo].string);
 		       Ch2_remote_loop = RESET;
	       	   Timer10minen4 = RESET;
	       	   Ch2_test_mode = RESET;
     	       	       //Ver1.1
			   Ch2_loop_min_alm = 1;
               		system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                       //ends here
               		System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	       	   OUTPORT2_ADD = Led_cntl;
        	       OUTPORT1_ADD = loop_status;			      
		}
         	   break;
   
				case 13:
		       Remoteloop(RL3,ST_CHECK);
		       CurrentScreenNo = STATION6_SCR;
		       strcpy(Buffer,"Normal         ");
		       for(i=0,j=0;i<14;i++,j++)
		       Screens[CurrentScreenNo].string[1][j] = Buffer[i];
		       display(Screens[CurrentScreenNo].string);
 		       Ch1_remote_loop = RESET;
	       	       Timer10minen3 = RESET;
	       	       Ch1_test_mode = RESET;
     	      	       //Ver1.1
		       Ch1_loop_min_alm = 1;
               	       system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                       //ends here
                       System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	       	       OUTPORT2_ADD = Led_cntl;
               	       OUTPORT1_ADD = loop_status;			      
         	       break;
		      
		       case 14:
	if(Twin_ch_system)	
      	     {
		       Remoteloop(RL4,ST_CHECK);
		       CurrentScreenNo = STATION6_SCR+1;
		       strcpy(Buffer,"Normal         ");
		       for(i=0,j=0;i<14;i++,j++)
		       Screens[CurrentScreenNo].string[1][j] = Buffer[i];
		       display(Screens[CurrentScreenNo].string);
 		       Ch2_remote_loop = RESET;
	       	       Timer10minen4 = RESET;
	       	       Ch2_test_mode = RESET;
     	       	       //Ver1.1
		       Ch2_loop_min_alm = 1;
                       system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                       //ends here
                       System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	       	       OUTPORT2_ADD = Led_cntl;
                       OUTPORT1_ADD = loop_status;			      
		}
         	   break;
   
				case 15:
		       Remoteloop(RL3,ST_CHECK);
		       CurrentScreenNo = STATION7_SCR;
		       strcpy(Buffer,"Normal         ");
		       for(i=0,j=0;i<14;i++,j++)
		       Screens[CurrentScreenNo].string[1][j] = Buffer[i];
		       display(Screens[CurrentScreenNo].string);
 		       Ch1_remote_loop = RESET;
	       	       Timer10minen3 = RESET;
	       	       Ch1_test_mode = RESET;
     	      	       //Ver1.1
		       Ch1_loop_min_alm = 1;
               	       system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                       //ends here
                       System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	       	       OUTPORT2_ADD = Led_cntl;
               	       OUTPORT1_ADD = loop_status;			      
         	       break;
		      
		       case 16:
	if(Twin_ch_system)	
      	     {
		       Remoteloop(RL4,ST_CHECK);
		       CurrentScreenNo = STATION7_SCR+1;
		       strcpy(Buffer,"Normal         ");
		       for(i=0,j=0;i<14;i++,j++)
		       Screens[CurrentScreenNo].string[1][j] = Buffer[i];
		       display(Screens[CurrentScreenNo].string);
 		       Ch2_remote_loop = RESET;
	       	   Timer10minen4 = RESET;
	       	   Ch2_test_mode = RESET;
     	       	       //Ver1.1
			   Ch2_loop_min_alm = 1;
               system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                       //ends here
               System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	       	   OUTPORT2_ADD = Led_cntl;
               OUTPORT1_ADD = loop_status;			      
		}
         	   break;
				
			   case 17:
		       Remoteloop(RL3,ST_CHECK);
		       CurrentScreenNo = STATION8_SCR;
		       strcpy(Buffer,"Normal         ");
		       for(i=0,j=0;i<14;i++,j++)
		       Screens[CurrentScreenNo].string[1][j] = Buffer[i];
		       display(Screens[CurrentScreenNo].string);
 		       Ch1_remote_loop = RESET;
	       	       Timer10minen3 = RESET;
	       	       Ch1_test_mode = RESET;
     	      	       //Ver1.1
		       Ch1_loop_min_alm = 1;
               	       system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                       //ends here
                       System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	       	       OUTPORT2_ADD = Led_cntl;
               	       OUTPORT1_ADD = loop_status;			      
         	       break;
		      
		       case 18:
	if(Twin_ch_system)	
      	     {
		       Remoteloop(RL4,ST_CHECK);
		       CurrentScreenNo = STATION8_SCR+1;
		       strcpy(Buffer,"Normal         ");
		       for(i=0,j=0;i<14;i++,j++)
		       Screens[CurrentScreenNo].string[1][j] = Buffer[i];
		       display(Screens[CurrentScreenNo].string);
 		       Ch2_remote_loop = RESET;
	       	   Timer10minen4 = RESET;
	       	   Ch2_test_mode = RESET;
     	       	       //Ver1.1
			   Ch2_loop_min_alm = 1;
               system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                       //ends here
               System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	       	   OUTPORT2_ADD = Led_cntl;
               OUTPORT1_ADD = loop_status;			      
		}
         	   break;

			   case 19:
			Remoteloop(RL3,ST_CHECK);
		       CurrentScreenNo = STATION9_SCR;
		       strcpy(Buffer,"Normal         ");
		       for(i=0,j=0;i<14;i++,j++)
		       Screens[CurrentScreenNo].string[1][j] = Buffer[i];
		       display(Screens[CurrentScreenNo].string);
 		       Ch1_remote_loop = RESET;
	       	       Timer10minen3 = RESET;
	       	       Ch1_test_mode = RESET;
     	      	       //Ver1.1
		       Ch1_loop_min_alm = 1;
               	       system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                       //ends here
                       System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	       	       OUTPORT2_ADD = Led_cntl;
               	       OUTPORT1_ADD = loop_status;			      
         	       break;
		      
		    case 20:
	if(Twin_ch_system)	
      	     {		       
			Remoteloop(RL4,ST_CHECK);
		       CurrentScreenNo = STATION9_SCR+1;
		       strcpy(Buffer,"Normal         ");
		       for(i=0,j=0;i<14;i++,j++)
		       Screens[CurrentScreenNo].string[1][j] = Buffer[i];
		       display(Screens[CurrentScreenNo].string);
 		       Ch2_remote_loop = RESET;
	       	      Timer10minen4 = RESET;
	       	      Ch2_test_mode = RESET;
     	       	       //Ver1.1
		      Ch2_loop_min_alm = 1;
	               system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                       //ends here
        	       System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	       	       OUTPORT2_ADD = Led_cntl;
               	       OUTPORT1_ADD = loop_status;			      
		}
         	   break;

		    case 21:
		       Remoteloop(RL3,ST_CHECK);	
		       CurrentScreenNo = STATION10_SCR;
		       strcpy(Buffer,"Normal         ");
		       for(i=0,j=0;i<14;i++,j++)
		       Screens[CurrentScreenNo].string[1][j] = Buffer[i];
		       display(Screens[CurrentScreenNo].string);
 		       Ch1_remote_loop = RESET;
	       	       Timer10minen3 = RESET;
	       	       Ch1_test_mode = RESET;
     	      	       //Ver1.1
		       Ch1_loop_min_alm = 1;
               	       system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                       //ends here
                       System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	       	       OUTPORT2_ADD = Led_cntl;
               	       OUTPORT1_ADD = loop_status;			      
         	       break;
		      
		    case 22:
	if(Twin_ch_system)	
      	     {		      
	        	Remoteloop(RL4,ST_CHECK);
		       CurrentScreenNo = STATION10_SCR+1;
		       strcpy(Buffer,"Normal         ");
		       for(i=0,j=0;i<14;i++,j++)
		       Screens[CurrentScreenNo].string[1][j] = Buffer[i];
		       display(Screens[CurrentScreenNo].string);
 		       Ch2_remote_loop = RESET;
	       	       Timer10minen4 = RESET;
	       	       Ch2_test_mode = RESET;
     	       	       //Ver1.1
		       Ch2_loop_min_alm = 1;
                       system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
                       //ends here
                       System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
	       	       OUTPORT2_ADD = Led_cntl;
                       OUTPORT1_ADD = loop_status;			      
		}
         	   break;

			//ends here
		      default:
		      break;
		      }//3e
		   break;
		   
		  	   
		   case OTHER_SCR+2:
		      CurrentScreenNo = OTHER_SCR;
		      display(Screens[CurrentScreenNo].string);
                   break;
                   
		   case OTHER_SCR+3:
		      CurrentScreenNo = OTHER_SCR;
		      display(Screens[CurrentScreenNo].string);

  		   break;
       			
     	         default:
		   break;
		 } //2e
		break;
	
               default:
	       break;
	     }       //1e , second switch ends
	     break;
    /**************************************************************
                      CASE UP_KEY
     **************************************************************/	
			
      case UP_KEY:
	
   	switch(Screens[CurrentScreenNo].Mode)    //first switch starts
	 {//1s
	  
   	 case OPEN_MENU_MODE:
 	    CurrentScreenNo = MAIN_SCR;
	    display(Screens[CurrentScreenNo].string);
	 break;
     	
       case MAIN_MENU_MODE:
	   
	  if(CurrentScreenNo == MAIN_SCR)
	    CurrentScreenNo = MAIN_SCR;
	  else
	    CurrentScreenNo--;
	  display(Screens[CurrentScreenNo].string);
	  break;
	  
   	 case STATUS_MENU_MODE:
	
		if(CurrentScreenNo == STATUS_SCR)
			CurrentScreenNo = STATUS_SCR;
		else
			CurrentScreenNo--;
		if(CurrentScreenNo==(STATUS_SCR+9))
			AGC1_scr=1;
		else
		{
			AGC1_scr=0;
			ch1_agc=0;
		}
		if(CurrentScreenNo==(STATUS_SCR+10))
			AGC2_scr=1;
		else
		{
			AGC2_scr=0;
			ch2_agc=0;
		}
		if(CurrentScreenNo==(STATUS_SCR+11))
		{
			AGC2_scr=0;
			PAMP_scr=1;
		}
		else
		{
			PAMP_scr=0;
			ch_PAMP=0;
		}
		if(CurrentScreenNo==(STATUS_SCR+12))
			v12=1;
		else
			v12=0;
	   	display(Screens[CurrentScreenNo].string);
		break;		
				 
 	 case ALARM_MENU_MODE: 
 	
	 if(CurrentScreenNo == ALARM_SCR)
	    CurrentScreenNo = ALARM_SCR;
	 else
	    CurrentScreenNo--;
	 display(Screens[CurrentScreenNo].string);
	 break;
	 
  	 case TEST_MENU_MODE:
	 
  	 if(CurrentScreenNo == TEST_SCR)
	    CurrentScreenNo = MAIN_SCR;
	 else
	    CurrentScreenNo--;
	 display(Screens[CurrentScreenNo].string);
	 break; 
   	 
      case LOCAL_LOOPBACK_MODE:
	 
 	 if(CurrentScreenNo == LOCAL_SCR)
	      CurrentScreenNo = TEST_SCR;
	 else
	      CurrentScreenNo--;
	 display(Screens[CurrentScreenNo].string);
	 break;

      case REMOTE_LOOPBACK_MODE:
       
 	 if(CurrentScreenNo == REMOTE_SCR)
	      CurrentScreenNo = TEST_SCR;
	 else
	      CurrentScreenNo--;
	 	display(Screens[CurrentScreenNo].string);
	 break;
/******************************************************/
// added in ver 1.4 for remote screen handling
/******************************************************/
    case STATION1:
	 if(CurrentScreenNo == STATION1_SCR)
	      CurrentScreenNo = REMOTE_SCR+2;
	 else
	      CurrentScreenNo--;
	 	display(Screens[CurrentScreenNo].string);
	 break;
case STATION2:
	 if(CurrentScreenNo == STATION2_SCR)
	      CurrentScreenNo = REMOTE_SCR+3;
	 else
	      CurrentScreenNo--;
	 	display(Screens[CurrentScreenNo].string);
	 break;
case STATION3:
	 if(CurrentScreenNo == STATION3_SCR)
	      CurrentScreenNo = REMOTE_SCR+4;
	 else
	      CurrentScreenNo--;
	 	display(Screens[CurrentScreenNo].string);
	 break;
case STATION4:
	 if(CurrentScreenNo == STATION4_SCR)
	      CurrentScreenNo = REMOTE_SCR+5;
	 else
	      CurrentScreenNo--;
	 	display(Screens[CurrentScreenNo].string);
	 break;
case STATION5:
	 if(CurrentScreenNo == STATION5_SCR)
	      CurrentScreenNo = REMOTE_SCR+6;
	 else
	      CurrentScreenNo--;
	 	display(Screens[CurrentScreenNo].string);
	 break;
case STATION6:
	 if(CurrentScreenNo == STATION6_SCR)
	      CurrentScreenNo = REMOTE_SCR+7;
	 else
	      CurrentScreenNo--;
	 	display(Screens[CurrentScreenNo].string);
	 break;
case STATION7:
	 if(CurrentScreenNo == STATION7_SCR)
	      CurrentScreenNo = REMOTE_SCR+8;
	 else
	      CurrentScreenNo--;
	 	display(Screens[CurrentScreenNo].string);
	 break;
case STATION8:
	 if(CurrentScreenNo == STATION8_SCR)
	      CurrentScreenNo = REMOTE_SCR+9;
	 else
	      CurrentScreenNo--;
	 	display(Screens[CurrentScreenNo].string);
	 break;
case STATION9:
	 if(CurrentScreenNo == STATION9_SCR)
	      CurrentScreenNo = REMOTE_SCR+10;
	 else
	      CurrentScreenNo--;
	 	display(Screens[CurrentScreenNo].string);
	 break;
case STATION10:
	 if(CurrentScreenNo == STATION10_SCR)
	      CurrentScreenNo = REMOTE_SCR+11;
	 else
	      CurrentScreenNo--;
	 	display(Screens[CurrentScreenNo].string);
	 break;
	 
  	 case OTHER_MODE:
	   if(CurrentScreenNo == OTHER_SCR)
	      CurrentScreenNo = OTHER_SCR+1;
	   else
	      CurrentScreenNo--;
	  display(Screens[CurrentScreenNo].string);
	 break;
   	  
       default:
   	  break;
      }//1e ends
	  break;
   	
  case DOWN_KEY:
	
	   switch(Screens[CurrentScreenNo].Mode)
	   {
	     
          case OPEN_MENU_MODE:
 	       CurrentScreenNo = MAIN_SCR;
	       display(Screens[CurrentScreenNo].string);
	    break;
      	
         case MAIN_MENU_MODE:
	     if(CurrentScreenNo < MAIN_MAX_SCR)
               CurrentScreenNo++;
             else
  	       CurrentScreenNo = MAIN_SCR;
	     display(Screens[CurrentScreenNo].string);
	     break;
      	
	    case STATUS_MENU_MODE:
	   if(CurrentScreenNo < STATUS_MAX_SCR)	       
			 CurrentScreenNo++;
 	    else
  	      CurrentScreenNo = STATUS_MAX_SCR;
       if(CurrentScreenNo==(STATUS_SCR+9))
			AGC1_scr=1;
	   else
		{
		AGC1_scr=0;
		ch1_agc=0;
		}
	   if(CurrentScreenNo==(STATUS_SCR+10))
			AGC2_scr=1;
		else
		{
				AGC2_scr=0;
				ch2_agc=0;
		}
	   if(CurrentScreenNo==(STATUS_SCR+11))
			PAMP_scr=1;
		else
			{
		PAMP_scr=0;
		ch_PAMP=0;
		}
		if(CurrentScreenNo==(STATUS_SCR+12))
			v12=1;
		else
			v12=0;
		display(Screens[CurrentScreenNo].string);
	    break;
   	
	    case TEST_MENU_MODE:
	    if(CurrentScreenNo < TEST_MAX_SCR)	       
              CurrentScreenNo++;
 	    else
  	      CurrentScreenNo = TEST_MAX_SCR;
              display(Screens[CurrentScreenNo].string);
	    break;
   	
	    case ALARM_MENU_MODE:
           MaxAlarmScreens = MaxAlarms+ALARM_SCR;
            if(CurrentScreenNo < MaxAlarmScreens)
  	         CurrentScreenNo++;
	       else 
             CurrentScreenNo = MaxAlarmScreens;
          display(Screens[CurrentScreenNo].string);
  	    break;
	    
    	   case LOCAL_LOOPBACK_MODE:
		if(CurrentScreenNo < LOCAL_MAX_SCR)	       
              CurrentScreenNo++;
 	      else
  	      CurrentScreenNo = MAIN_SCR;
          display(Screens[CurrentScreenNo].string);
	    break;
            //added in Ver1.2
    	    case REMOTE_LOOPBACK_MODE:
	    if(CurrentScreenNo < REMOTE_MAX_SCR)
                {cnt++;
		CurrentScreenNo++;
		}
 	    else
  	      CurrentScreenNo = MAIN_SCR;
		if(SELF_ADD!=cnt-2)
          display(Screens[CurrentScreenNo].string);
	    break;
   		//ends here	
	 /******************************************************/
	// added in ver 1.4 for remote screen handling
	/******************************************************/
    	    case STATION1:
           	if(CurrentScreenNo < STATION1_MAX_SCR)
              		CurrentScreenNo++;
 	    	else
  	      		CurrentScreenNo = REMOTE_SCR+2;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION2:
           	if(CurrentScreenNo < STATION2_MAX_SCR)
              		CurrentScreenNo++;
 	    	else
  	      		CurrentScreenNo = REMOTE_SCR+3;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION3:
           	if(CurrentScreenNo < STATION3_MAX_SCR)
              		CurrentScreenNo++;
 	    	else
  	      		CurrentScreenNo = REMOTE_SCR+4;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION4:
           	if(CurrentScreenNo < STATION4_MAX_SCR)
              		CurrentScreenNo++;
 	    	else
  	      		CurrentScreenNo = REMOTE_SCR+5;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION5:
           	if(CurrentScreenNo < STATION5_MAX_SCR)
              		CurrentScreenNo++;
 	    	else
  	      		CurrentScreenNo = REMOTE_SCR+6;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION6:
           	if(CurrentScreenNo < STATION6_MAX_SCR)
              		CurrentScreenNo++;
 	    	else
  	      		CurrentScreenNo = REMOTE_SCR+7;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION7:
           	if(CurrentScreenNo < STATION7_MAX_SCR)
              		CurrentScreenNo++;
 	    	else
  	      		CurrentScreenNo = REMOTE_SCR+8;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION8:
           	if(CurrentScreenNo < STATION8_MAX_SCR)
              		CurrentScreenNo++;
 	    	else
  	      		CurrentScreenNo = REMOTE_SCR+9;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION9:
           	if(CurrentScreenNo < STATION9_MAX_SCR)
              		CurrentScreenNo++;
 	    	else
  	      		CurrentScreenNo = REMOTE_SCR+10;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION10:
           	if(CurrentScreenNo < STATION10_MAX_SCR)
              		CurrentScreenNo++;
 	    	else
  	      		CurrentScreenNo = REMOTE_SCR+11;
          	display(Screens[CurrentScreenNo].string);
	    break;                                            	
            
            
		case OTHER_MODE:
	    if(CurrentScreenNo == OTHER_SCR)	       
              CurrentScreenNo++;
 	    else
  	      CurrentScreenNo = OTHER_SCR;
              display(Screens[CurrentScreenNo].string);
	    break;
	
	    default:
	    break;
	    }
	    break;
     	
        case LEFT_KEY:
	
	   switch(Screens[CurrentScreenNo].Mode)
	    {
		case OPEN_MENU_MODE:
 	    CurrentScreenNo = MAIN_SCR;
	    display(Screens[CurrentScreenNo].string);
	 break;
          case MAIN_MENU_MODE:
	       CurrentScreenNo = OPENING_SCR;
	       display(Screens[CurrentScreenNo].string);
	    break;
      	
	    case STATUS_MENU_MODE:
		CurrentScreenNo = MAIN_SCR;
		if(CurrentScreenNo==(STATUS_SCR+9))
		AGC1_scr=1;
		else
		AGC1_scr=0;
	        if(CurrentScreenNo==(STATUS_SCR+10))
		AGC2_scr=1;
		else
		AGC2_scr=0;
		if(CurrentScreenNo==(STATUS_SCR+11))
		PAMP_scr=1;
		else
			PAMP_scr=0;
		if(CurrentScreenNo==(STATUS_SCR+12))
			v12=1;
		else
			v12=0;

	   	display(Screens[CurrentScreenNo].string);
	    break;
   	
	    case ALARM_MENU_MODE:
      	CurrentScreenNo = MAIN_SCR;
       	display(Screens[CurrentScreenNo].string);
  		
	    break;
	    
         case TEST_MENU_MODE:
         	CurrentScreenNo = MAIN_SCR;
         	display(Screens[CurrentScreenNo].string);
  		
	    break;
	    
         case LOCAL_LOOPBACK_MODE:
         	CurrentScreenNo = TEST_SCR;
         	display(Screens[CurrentScreenNo].string);
  	    break;
	                    //Ver1.2
	case REMOTE_LOOPBACK_MODE:
         	CurrentScreenNo = TEST_SCR;
         	display(Screens[CurrentScreenNo].string);
  	    break;
	 
	    /******************************************************/
		// added in ver 1.4 for remote screen handling
	    /******************************************************/
    	    case STATION1:
               	CurrentScreenNo = TEST_SCR+1;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION2:
               	CurrentScreenNo = TEST_SCR+1;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION3:
               	CurrentScreenNo = TEST_SCR+1;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION4:
               	CurrentScreenNo = TEST_SCR+1;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION5:
               	CurrentScreenNo = TEST_SCR+1;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION6:
               	CurrentScreenNo = TEST_SCR+1;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION7:
               	CurrentScreenNo = TEST_SCR+1;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION8:
               	CurrentScreenNo = TEST_SCR+1;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION9:
               	CurrentScreenNo = TEST_SCR+1;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION10:
               	CurrentScreenNo = TEST_SCR+1;
          	display(Screens[CurrentScreenNo].string);
	    break;                                            	

                         //ends here
         case OTHER_MODE:
         	CurrentScreenNo = TEST_SCR;
         	display(Screens[CurrentScreenNo].string);
  	    break;
	    
         default:
	    break;		
           }
         break;
           
        case RIGHT_KEY:
	
	   switch(Screens[CurrentScreenNo].Mode)
	    {
			case OPEN_MENU_MODE:
 	    CurrentScreenNo = MAIN_SCR;
	    display(Screens[CurrentScreenNo].string);
	 break;
         case MAIN_MENU_MODE:
	       CurrentScreenNo = OPENING_SCR;
	       display(Screens[CurrentScreenNo].string);
	    break;
      	
	    case STATUS_MENU_MODE:
		CurrentScreenNo = MAIN_SCR;
		if(CurrentScreenNo==(STATUS_SCR+9))
			AGC1_scr=1;
		else
			AGC1_scr=0;
	    if(CurrentScreenNo==(STATUS_SCR+10))
			AGC2_scr=1;
		else
			AGC2_scr=0;
		if(CurrentScreenNo==(STATUS_SCR+11))
			PAMP_scr=1;
		else
			PAMP_scr=0;
		if(CurrentScreenNo==(STATUS_SCR+12))
			v12=1;
		else
			v12=0;

	   	display(Screens[CurrentScreenNo].string);
	    break;
   	
	    case ALARM_MENU_MODE:
         	CurrentScreenNo = MAIN_SCR;
         	display(Screens[CurrentScreenNo].string);
  		
	    break;
	    
         case TEST_MENU_MODE:
         	CurrentScreenNo = MAIN_SCR;
         	display(Screens[CurrentScreenNo].string);
  		
	    break;
	    
         case LOCAL_LOOPBACK_MODE:
         	CurrentScreenNo = TEST_SCR;
         	display(Screens[CurrentScreenNo].string);
  	    break;
	          //added in Ver1.2
	case REMOTE_LOOPBACK_MODE:
         	CurrentScreenNo = TEST_SCR;
         	display(Screens[CurrentScreenNo].string);
  	    break;
	   /******************************************************/
		// added in ver 1.4 for remote screen handling
	   /******************************************************/
    	    case STATION1:
               	CurrentScreenNo = TEST_SCR+1;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION2:
               	CurrentScreenNo = TEST_SCR+1;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION3:
               	CurrentScreenNo = TEST_SCR+1;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION4:
               	CurrentScreenNo = TEST_SCR+1;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION5:
               	CurrentScreenNo = TEST_SCR+1;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION6:
               	CurrentScreenNo = TEST_SCR+1;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION7:
               	CurrentScreenNo = TEST_SCR+1;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION8:
               	CurrentScreenNo = TEST_SCR+1;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION9:
               	CurrentScreenNo = TEST_SCR+1;
          	display(Screens[CurrentScreenNo].string);
	    break;
    	    case STATION10:
               	CurrentScreenNo = TEST_SCR+1;
          	display(Screens[CurrentScreenNo].string);
	    break;                                            	
 

            //ends here
         case OTHER_MODE:
         	CurrentScreenNo = TEST_SCR;
         	display(Screens[CurrentScreenNo].string);
  	    break;
	    
         default:
	    break;		
           }
        } 
   }   
}


	/* The following function is used to display the screen which comprises of
	2x16 characters. Initially command is given to clear the display and after
	displaying the screen the cursor is placed at the end of second row before
	returning. */

void display(char string[2][20])
{
	
	SelectionCursorPosition(ROW_1,0);
	StringOut(string[0], ROW_1,16);
	SelectionCursorPosition(ROW_2,0);
	StringOut(string[1], ROW_2,16);
	SelectionCursorPosition(ROW_2,15);
}



