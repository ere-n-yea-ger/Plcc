/*##########################################################################
:	CC supy
Filename			:	function.C
Previous Version		:  	N/A
New Version			:	0.1
Modified  on			:  	16/04/1999
Last Modified by		:	Gurmeet S Ubhi
Editor Tab Size  		:          3
Comments			:
###########################################################################*/

#define public extern 
#include <reg51.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>		
#include "database.h"
#include"declare.h"
#include "def.h"
#include"screen.h"
#include"addr.h"
#include "spfunreg.h"

extern struct Screen Screens[80]; /*scr_&_agc_bars*/
extern unsigned char xdata  LCD_CMD_ADDR	;
extern unsigned char xdata  LCD_DATA_ADDR 	;  
extern unsigned char key_enter_flag_counter,key_enter_flag_counter1; /*scr_&_agc_bars*/
void GetAlarms( void)

			{
			 Alarm1_value = INPORT1_ADD ^ 0xff;
			 Alarm2_value = INPORT2_ADD ^ 0xff;
			 Alarm3_value = INPORT3_ADD ^ 0xff;
			 Alarm4_value = INPORT4_ADD ^ 0x87;
			 rtu_alm_cfg = 0;						/*To Check Alarms of RTU Data Modem*/
			 Alarm5_value = INPORT5_ADD ^ 0xff;
			 rtu_alm_cfg = 1;
			 Alarm7_value = INPORT5_ADD ^ 0xff;
			} 


unsigned char KeyBoardScan(void)
{

	static unsigned char KeyDebounceCount, LastKey;
	unsigned char  xdata ParamStr[5];
	unsigned char  xdata  RetParamStr[5];

	ParamStr[0] = GetKey;
	BiosCall(ParamStr, RetParamStr);

	if(RetParamStr[1] == KEY_PRESSED)
	{
		if(++KeyDebounceCount > KEY_DEBOUNCE_THRS)
		{
			KeyDebounceCount = 0;

			if(RetParamStr[2] != LastKey)
			{
				LastKey = RetParamStr[2];
				if(AGC1_scr==1)				/*Gurjit2*/ /*scr_&_agc_bars*/
				{
					AGC1_scr=0;
					ch1_agc=0;
				}
				if(AGC2_scr==1)
				{
					AGC2_scr=0;
					ch2_agc=0;
				}
				key_enter_flag_counter=MAXTICKCOUNT;
				key_enter_flag_counter1=0;          /*scr_&_agc_bars*/
				return(RetParamStr[2]);
			}
			else
			{
				return(NO_KEY_PRESSED);
			}
		}
	}
	else
	{
		KeyDebounceCount = 0;
		LastKey = NO_KEY_PRESSED;
	}
	return(NO_KEY_PRESSED);
}                               

void StringOut(unsigned char *DisplayStr, unsigned char Row, unsigned int Col)
{
	unsigned int   xdata DdramAddr;
	unsigned char  xdata ParamStr[5];
	unsigned char  xdata RetParamStr[5];

	if(Row == ROW_2)	Row = 0x04;
	else Row = 0;

	for(DdramAddr = 0; DdramAddr < Col; DdramAddr++)
	{
		ParamStr[0] = DisplayChar;
		ParamStr[1] = 0x80 | ((16 * Row) + DdramAddr);
		ParamStr[2] = DisplayStr[DdramAddr];
		BiosCall(ParamStr, RetParamStr);

		/*------------------------------------------------------------------
		IpVar[1] = 1 A A A A A A A

		AAAAAAA -> DDRAM Address Corresponds to Cursor Address
		IpVar[2] = ASCII Character to be displayed.

		------------------------------------------------------------------*/
	}
}


unsigned char SelectionCursorPosition(unsigned char Row, unsigned char Column)
{
	unsigned char  xdata ParamStr[5];
	unsigned char  xdata RetParamStr[5];

	if(Row == ROW_2)	Row = 0x04;
	else	Row = 0x00;

	ParamStr[0] = SetCursorPosition;
	ParamStr[1] = 0x80 | ((16 * Row) + Column);
	BiosCall(ParamStr, RetParamStr);
	return 0;
}

void Delay(unsigned char Count)
{
	unsigned char i, j;

	for(i = 0; i < Count; ++i)
		for(j = 0; j < 200; ++j);
}

void Wait40(void)
{
	unsigned char i;
	for(i = 0; i < 20; ++i);
}


void GetADCInputs(void)

{
   unsigned char xdata Buffer[20];
   unsigned int xdata i,j,IntValue=0;
   float xdata Value = 0;
   
   ADC_ADD = Read_N12V;    
   Wait40();
   Wait40();
   Wait40();
   N12V_value = ADC_ADD;       
   Value =((int)N12V_value*12)/211.2;/*214.0;*/ /*scr_&_agc_bars*/
   sprintf(Buffer,"%2.2f",Value);
   for(i=0,j=6;i<5;i++,j++)
      Screens[STATUS_SCR+12].string[1][j] = Buffer[i];
    
    				  
   ADC_ADD = Read_P12V;    /* Data to be written = 0x0C*/
   Wait40();
   Wait40();
   Wait40();	
   P12V_value = ADC_ADD;
   Value = ((int)P12V_value*12)/220.0;/*214.0;*/ /*scr_&_agc_bars*/
   sprintf(Buffer,"%2.2f",Value);
   for(i=0,j=6;i<5;i++,j++)
   Screens[STATUS_SCR+12].string[0][j] = Buffer[i];
	/*  if(v12==1)
      display(Screens[STATUS_SCR+12].string);*/
   if(!SystemConfig)/*20w*/
   {
                 
		ADC_ADD = Read_P36V;    
		Wait40();
		Wait40();
		Wait40();	
		P36V_value = ADC_ADD;
		Value = ((int)P36V_value*36)/247.0;/*20V*/	/*Gurjit_36V_supply*/
		/*Value = ((int)P36V_value*50)/247.0;*/			/*voltage display changed to 50V*/ /*inder_plcc*/ /*scr_&_agc_bars*/
		sprintf(Buffer,"P36V: + %2.2f   ",Value);	/*Gurjit_36V_supply*/
		/*sprintf(Buffer,"P50V: + %2.2f   ",Value);*/ 


		/*sprintf(Buffer,"50.03V",Value);*/

		for(i=0,j=0;i<15;i++,j++)
			Screens[STATUS_SCR+13].string[0][j] = Buffer[i];
    
		ADC_ADD = Read_N36V;    
		Wait40();
		Wait40();
		Wait40();	
		N36V_value = ADC_ADD;
		Value = ((int)N36V_value*36)/255.0;/*20V*/	/*Gurjit_36V_supply*/
		/*Value = ((int)N36V_value*50)/247.0;*/			/*voltage display changed to 50V*/ /*inder_plcc*/
		sprintf(Buffer,"N36V: - %2.2f   ",Value);	/*Gurjit_36V_supply*/
		/*sprintf(Buffer,"N50V: - %2.2f   ",Value);*/ 

		/*  sprintf(Buffer,"50.05",Value); */
		for(i=0,j=0;i<15;i++,j++)
			Screens[STATUS_SCR+13].string[1][j] = Buffer[i];
   }
   else/*40 w*/
   {
		ADC_ADD = Read_P36V;    
		Wait40();
		Wait40();
		Wait40();	
		P36V_value = ADC_ADD;
		Value = ((int)P36V_value*36)/247.0;/*20V*/	/*Gurjit_36V_supply*/
		/*Value = ((int)P36V_value*50)/247.0;*//*50V*/
		sprintf(Buffer,"P36V: + %2.2f   ",Value);	/*Gurjit_36V_supply*/
		/*sprintf(Buffer,"P50V: + %2.2f   ",Value); */

		/*sprintf(Buffer,"50.03V",Value);*/

		for(i=0,j=0;i<15;i++,j++)
			Screens[STATUS_SCR+13].string[0][j] = Buffer[i];

		ADC_ADD = Read_N36V;    
		Wait40();
		Wait40();
		Wait40();	
		N36V_value = ADC_ADD;
		Value = ((int)N36V_value*36)/255.0;/*20V*/	/*Gurjit_36V_supply*/
		/*Value = ((int)N36V_value*50)/255.0;*//*50V*/
		sprintf(Buffer,"N36V: - %2.2f   ",Value);	/*Gurjit_36V_supply*/	
		/*sprintf(Buffer,"N50V: - %2.2f   ",Value);*/
		/*  sprintf(Buffer,"50.05",Value); */
		for(i=0,j=0;i<15;i++,j++)
			Screens[STATUS_SCR+13].string[1][j] = Buffer[i];

	}
	
	ADC_ADD = Read_P5V;    
	Wait40();
	Wait40();
	Wait40();
	P5V_value = ADC_ADD;
	Value = ((int)P5V_value*5)/163.0;
	sprintf(Buffer,"%2.2f",Value);
	for(i=0,j=5;i<4;i++,j++)
		Screens[STATUS_SCR+14].string[0][j] = Buffer[i];
}
 

/*****************************/
// added in ver 1.5
/***************************/

void GetAGCInputs(void)
{
   
	if(ch1_agc==1)
	   	DispCh1AGC();
	if(ch2_agc==1)
		DispCh2AGC();

    
   
}       

/**********************************/  
 //added in ver 1.5
/***********************************/
/**********************************/
//testing code 29-11-2k ajay
/**********************************/

void DispCh2AGC(void)
{
	unsigned int  xdata i,j,Bars;
	unsigned char xdata Buffer[20],buf[5];
	float xdata Value = 0,Value1=0.00,val=0.00;

	if(Twin_ch_system)
    {
	   sprintf(Buffer,"%s","Ch2 AGC Level  ");
	   for(i=0,j=0;i<15;i++,j++)
	   Screens[STATUS_SCR+10].string[0][j] = Buffer[i];

			ADC_ADD = Read_AGC1;                    
			Wait40();
			Wait40();
			Wait40();
			AGC1_value = ADC_ADD;           	 // for channel one
			Value =((int)AGC1_value*(4.7/8))/9.8;  /* because Read_AGC2 we are getting aprox 200
					     and agc input  before divider is aprox. 5V */
		       agc=Value*(1/2.44);
   		       Value1=agc;
		       sprintf(buf,"%1.2f",Value1);
		       val=atof(buf);
   	         if((val >(float)5.59)||(val <(float)4.22))
			{
				sprintf(Buffer,"%s"," Out of Range  ");
				for(i=0,j=0;i<15;i++,j++)
					Screens[STATUS_SCR+10].string[1][j] = Buffer[i];
		    }
			else
				ScrBlank((STATUS_SCR+10));    	       	       
	        Bars=GetBars(agc);	
  			for(i=0;i<Bars;i++)
  	 	    {
  	  			Screens[STATUS_SCR+10].string[1][i] = 0xff;
   		    }
			display(Screens[STATUS_SCR+10].string);
	}
	else
    {

       	strcpy(Buffer,"Channel2   N.A. ");	
       	for(i=0,j=0;i<16;i++,j++)
    		Screens[STATUS_SCR+10].string[0][j] = Buffer[i];
    	strcpy(Buffer,"Single Ch Config");	
		for(i=0,j=0;i<16;i++,j++)
     		Screens[STATUS_SCR+10].string[1][j] = Buffer[i];
	   	if(AGC2_scr)
	        display(Screens[STATUS_SCR+10].string);
 
	}

}

void DispCh1AGC(void)
{
	unsigned int  xdata i,j,Bars;
	unsigned char xdata Buffer[20],buf[5];
	float xdata Value = 0,Value1=0.00,val=0.00;
     	
	sprintf(Buffer,"%s","Ch1 AGC Level  ");
	for(i=0,j=0;i<15;i++,j++)
		Screens[STATUS_SCR+9].string[0][j] = Buffer[i];
 	
	ADC_ADD = Read_AGC2;                    
	Wait40();
	Wait40();
	Wait40();
	AGC2_value = ADC_ADD;           	 // for channel one
	Value =((int)AGC2_value*(4.7/8))/9.8;  /* because Read_AGC2 we are getting aprox 200
			             		               and input agc before divider is aprox. 5V */
	agc=Value*(1/2.44);
   	Value1=agc;
	sprintf(buf,"%1.2f",Value1);
	val=atof(buf);
			
   
	if((val >(float)5.59)||(val <(float)4.22))
	{
		sprintf(Buffer,"%s"," Out of Range  ");
		for(i=0,j=0;i<15;i++,j++)
			Screens[STATUS_SCR+9].string[1][j] = Buffer[i];
	}
    else
	    ScrBlank((STATUS_SCR+9));
  
   	Bars=GetBars(agc);

    for(i=0;i<Bars;i++)
	{
		Screens[STATUS_SCR+9].string[1][i] = 0xff;
	}
    display(Screens[STATUS_SCR+9].string);

  
} 
/***********************/
// end of testing code
/**************************/
		 /*******************************/
		/********added in ver 1.5*******/
	       /*******************************/

		int GetBars(float agc)
			{
			int Bars=0;

			if(agc>=4.22 && agc<4.49)                  // number of bars to be displayed
				Bars=1;	
			if(agc>4.49 && agc<4.65)
				Bars=2;
			if(agc>4.65 && agc<4.78)
				Bars=3;
			if(agc>4.78 && agc<4.87)
			     Bars=4;
			if(agc>4.87 && agc<4.95)
			     Bars=5;
			if(agc>4.95 && agc<5.02)
			     Bars=6;
			if(agc>5.02 && agc<5.10)
			     Bars=7;
			if(agc>5.10 && agc<5.15)
			     Bars=8;
			if(agc>=5.15 && agc<5.21)
			     Bars=9;
			if(agc>5.21 && agc<5.27)
			     Bars=10;
			if(agc>5.27 && agc<5.33)
			     Bars=11;
			if(agc>5.33 && agc<5.38)
			     Bars=12;
			if(agc>5.38 && agc<5.43)
			     Bars=13;
			if(agc>5.43 && agc<5.49)
			     Bars=14;
			if(agc>5.49 && agc<5.54)
			     Bars=15;
			if(agc>5.54 && agc<5.59)
			     Bars=16;
			return Bars;


}
  	

/**************************************/
// added in ver 1.5
/*************************************/

void ScrBlank(int ScreenNo)
{
int i,j;
for(i=0,j=0;i<16;i++,j++)
Screens[ScreenNo].string[1][j] = ' ';
}	             

/**************************************/
// added in ver 1.5
/*************************************/

void GetPowerOP(void)
{	  		
	if(ch_PAMP==1)
		DispPAMPGraph(0);  
}

/***************************/
// added in ver 1.5
/***************************/

void DispPAMPGraph(int Bars)
{
	unsigned int xdata i,j;
	unsigned char xdata Buffer[20],buf[5];
	float xdata Value = 0,Value1 = 0,val=0.00;
	 
  	             	
	if(!(Twin_ch_system))
	{
	     
		ScrBlank((STATUS_SCR+11));
	    ADC_ADD=Read_Power_level;
		Wait40();
		Wait40();
		Wait40();
	    PAMP_value=ADC_ADD;
             	
		Value =((int)PAMP_value*3*1.017)/66.89; 
       	Value1 =((int)PAMP_value*3*1.017)/66.89;
		sprintf(buf,"%1.1f",Value1);
		val=atof(buf);
      		   
       	   	    
       	   	
		if(val<(float)0.5)
		{
			sprintf(Buffer,"%s","PAMP VERY LOW  v"); /*scr_&_agc_bars*/
		    for(i=0,j=0;i<16;i++,j++)
		    Screens[STATUS_SCR+11].string[1][j] = Buffer[i];
		}
		if(val>(float)8.0)
		{
			sprintf(Buffer,"%s","PAMP VERY HIGH ^"); /*scr_&_agc_bars*/
			for(i=0,j=0;i<16;i++,j++)
				Screens[STATUS_SCR+11].string[1][j] = Buffer[i];
		}
		if(Value<2.1 && Value>0.6)
			Bars=1;
		if(Value<2.6 && Value>2.1)
		    Bars=2;
		if(Value<2.9 && Value>2.6)
		    Bars=3 ;
		if(Value<3.0 && Value>2.9)
		    Bars=4;
		if(Value<3.3 && Value>3.0)
		    Bars=5;
		if(Value<4.7 && Value>3.3)
		    Bars=6;
		if(Value<4.8 && Value>4.7)
		    Bars=7;
		if(Value<5.1 && Value>4.8)
		    Bars=8;
		if(Value<5.5 && Value>5.1)
		    Bars=9;
		if(Value<6.1 && Value>5.5)
		    Bars=10;
		if(Value<6.8 && Value>6.1)
		    Bars=11;
		if(Value<7.4 && Value>6.8)
		    Bars=12;
		if(Value<7.5 && Value>7.4)
		    Bars=13;
		if(Value<8.0 && Value>7.5)
            Bars=14;
                                          
		for(i=0;i<Bars;i++)
		{
			Screens[STATUS_SCR+11].string[1][i] = 0xff;
		}
		     
		display(Screens[STATUS_SCR+11].string);
	    Wait40();

               	
	}
	else
    {
		
      	ScrBlank((STATUS_SCR+11));
             
	    ADC_ADD=Read_Power_level;
	    Wait40();
	    Wait40();
		Wait40();
		PAMP_value=ADC_ADD;
		Value =((int)PAMP_value*3*1.017)/66.89;
		Value1 =((int)PAMP_value*3*1.017)/66.89;	
		sprintf(buf,"%1.1f",Value1);
		val=atof(buf);
   		       
		if(val<(float)0.8)
		{
			sprintf(Buffer,"%s","PAMP VERY LOW  v"); /*scr_&_agc_bars*/
			for(i=0,j=0;i<16;i++,j++)
			 	Screens[STATUS_SCR+11].string[1][j] = Buffer[i];
		}
	
		if(val>(float)4.3)
		{
			sprintf(Buffer,"%s","PAMP VERY HIGH v"); /*scr_&_agc_bars*/
			for(i=0,j=0;i<16;i++,j++)
			   	Screens[STATUS_SCR+11].string[1][j] = Buffer[i];
		}
	    if(Value<1.1 && Value>0.9)
	        Bars=1;
		if(Value<1.2 && Value>1.1)
			Bars=2;
		if(Value<1.4 && Value>1.2)
	        Bars=3;
		if(Value<1.7 && Value>1.4)
			Bars=4;
	    if(Value<2.0 && Value>1.7)
			Bars=5;
		if(Value<2.3 && Value>2.0)
	        Bars=6;
		if(Value<2.6 && Value>2.3)
	        Bars=7;
		if(Value<2.9 && Value>2.6)
	        Bars=8;
		if(Value<3.0 && Value>2.9)
	        Bars=9;
		if(Value<3.4 && Value>3.0)
	        Bars=10;
		if(Value<3.7 && Value>3.4)
	        Bars=11;
		if(Value<4.0 && Value>3.7)
	        Bars=12;
		if(Value<4.3 && Value>4.0)
	        Bars=13;
				
		for(i=0;i<Bars;i++)
		{
			Screens[STATUS_SCR+11].string[1][i] = 0xff;
		}

	  	
		display(Screens[STATUS_SCR+11].string);
		Wait40();
	   
        
	
	}
	
}
   	



void Loopbackdisable(void)
{
 
   unsigned char xdata Buffer[20];
   unsigned int xdata i,j;
   
	if(S_Time10min1 == SET)
     {
     Ch1_local_loop = RESET;
     Ch1_test_mode = RESET;
     System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
     S_Time10min1 = RESET;
     Timer10minen1 = RESET;
     //Ver1.1
     Ch1_loop_min_alm = 1;
     system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
     //ends here
     OUTPORT2_ADD = Led_cntl;
     OUTPORT1_ADD = loop_status;
     strcpy(Buffer,"Normal         ");
     for(i=0,j=0;i<14;i++,j++)
    	Screens[LOCAL_SCR].string[1][j] = Buffer[i];
     }
     	
 if(S_Time10min2 == SET)
     {
     Ch2_local_loop = RESET;
     Ch2_test_mode = RESET;
     System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
     S_Time10min2 = RESET;
     Timer10minen2 = RESET;
     //Ver1.1
	Ch2_loop_min_alm = 1;
     system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
     //ends here
     OUTPORT2_ADD = Led_cntl;
     OUTPORT1_ADD = loop_status;
     strcpy(Buffer,"Normal         ");
     for(i=0,j=0;i<14;i++,j++)
    	Screens[LOCAL_SCR+1].string[1][j] = Buffer[i];
     }

//added in Ver1.2

if(S_Time10min3 == SET  )
     {
     Remoteloop(RL3,ST_CHECK);	
     Ch1_remote_loop = RESET;
     Ch1_remrem_loop = RESET;	
     Ch1_test_mode = RESET;
     System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
     S_Time10min3 = RESET;
     Timer10minen3 = RESET;
     //Ver1.1
     Ch1_loop_min_alm = 1;
     system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
     //ends here
     OUTPORT2_ADD = Led_cntl;
     OUTPORT1_ADD = loop_status;
     strcpy(Buffer,"Normal         ");
/***********************************************/
//added in ver 1.4 to display message in screen
/***********************************************/
   if(ST_CHECK==1)
   	{

          for(i=0,j=0;i<14;i++,j++)
      	Screens[STATION1_SCR].string[1][j] = Buffer[i];
   	}
   if(ST_CHECK==2)
     {

      for(i=0,j=0;i<14;i++,j++)
      Screens[STATION2_SCR].string[1][j] = Buffer[i];
     }
  if(ST_CHECK==3)
    {

     for(i=0,j=0;i<14;i++,j++)
      Screens[STATION3_SCR].string[1][j] = Buffer[i];
    }
  if(ST_CHECK==4)
    {

     for(i=0,j=0;i<14;i++,j++)
     Screens[STATION4_SCR].string[1][j] = Buffer[i];
    }
 if(ST_CHECK==5)
   {

     for(i=0,j=0;i<14;i++,j++)
     Screens[STATION5_SCR].string[1][j] = Buffer[i];
   }
if(ST_CHECK==6)
  {

   for(i=0,j=0;i<14;i++,j++)
   Screens[STATION6_SCR].string[1][j] = Buffer[i];
  }
if(ST_CHECK==7)
{

			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION7_SCR].string[1][j] = Buffer[i];
				}
				if(ST_CHECK==8)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION8_SCR].string[1][j] = Buffer[i];
				}
				if(ST_CHECK==9)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION9_SCR].string[1][j] = Buffer[i];
				}
				if(ST_CHECK==10)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION10_SCR].string[1][j] = Buffer[i];
				}
		 
     }
     	
 if(S_Time10min4 == SET)
     {
     Remoteloop(RL4,ST_CHECK);
     Ch2_remote_loop = RESET;
     Ch2_remrem_loop = RESET;
     Ch2_test_mode  = RESET;
     System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
     S_Time10min4  = RESET;
     Timer10minen4 = RESET;
     //Ver1.1
     Ch2_loop_min_alm = 1;
     system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
     //ends here
     OUTPORT2_ADD = Led_cntl;
     OUTPORT1_ADD = loop_status;
     strcpy(Buffer,"Normal         ");
	/***********************************************/
	//added in ver 1.4 to display message in screen
	/***********************************************/
     if(ST_CHECK==1)
     {
     for(i=0,j=0;i<14;i++,j++)
     Screens[STATION1_SCR+1].string[1][j] = Buffer[i];
     }
     if(ST_CHECK==2)
     {
      for(i=0,j=0;i<14;i++,j++)
           Screens[STATION2_SCR+1].string[1][j] = Buffer[i];
    }
    if(ST_CHECK==3)
    {
      for(i=0,j=0;i<14;i++,j++)
          Screens[STATION3_SCR+1].string[1][j] = Buffer[i];
    }
    if(ST_CHECK==4)
    {
      for(i=0,j=0;i<14;i++,j++)
          Screens[STATION4_SCR+1].string[1][j] = Buffer[i];
   }
   if(ST_CHECK==5)
   {
     for(i=0,j=0;i<14;i++,j++)
          Screens[STATION5_SCR+1].string[1][j] = Buffer[i];
  }
  if(ST_CHECK==6)
   {
     for(i=0,j=0;i<14;i++,j++)
          Screens[STATION6_SCR+1].string[1][j] = Buffer[i];
   }
  if(ST_CHECK==7)
   {
     for(i=0,j=0;i<14;i++,j++)
          Screens[STATION7_SCR+1].string[1][j] = Buffer[i];
   }
 if(ST_CHECK==8)
  {
     for(i=0,j=0;i<14;i++,j++)
         Screens[STATION8_SCR+1].string[1][j] = Buffer[i];
  }
 if(ST_CHECK==9)
  {
     for(i=0,j=0;i<14;i++,j++)
    	Screens[STATION9_SCR+1].string[1][j] = Buffer[i];
  }
if(ST_CHECK==10)
  {
    for(i=0,j=0;i<14;i++,j++)
        Screens[STATION10_SCR+1].string[1][j] = Buffer[i];
  }			
     }
    //ends here

}     	




unsigned char Switchstatus (void)
 {
  static unsigned char SW1DebounceCount, Lastswitch,SW2DebounceCount, Lastswitch1;
  Alarm4_value = INPORT4_ADD ^ 0xff; 	
  if(switchll)
    {
    if(++SW1DebounceCount > SW_DEBOUNCE_THRS)
      {
       SW1DebounceCount = 0;
       if(switchll!= Lastswitch)
	 {
	  Lastswitch = switchll;
    	  if(channel1)
	    return(Ch2_local);/*interchanged ch1_local and ch2_local for hardware compatibility*/
        	
          else 
	    return(Ch1_local);
          }
       else
	  return(No_loop);
       }
    }
  else
    {  //ver1.2
    if(switchrl)
      {
      if(++SW2DebounceCount > SW_DEBOUNCE_THRS)
	{
	 SW2DebounceCount = 0;
         if(switchrl!= Lastswitch1)
	   {
	    Lastswitch1 = switchrl;
    	    if(channel1)
	      return(Ch2_remote);/*interchanged ch1_remote and ch2_remote for hardware compatibility*/
        	
            else 
	      return(Ch1_remote);
           }
 	 else
	   return(No_loop);
	  }
      }        //ends here
     else
	{
		SW2DebounceCount = 0;
		SW1DebounceCount = 0;
		Lastswitch = No_loop;
		Lastswitch1 = No_loop;
	}
	return(No_loop);
      }


}

void Processloopback( void )
{

   unsigned char xdata Buffer[20];
   unsigned int xdata i,j;

	loopbacktype = Switchstatus();
	SELF_ADD=((INPORT7_ADD)&(0x0F)); // added in ver 1.4
	OUTPORT1_ADD = loop_status;
	//added in Ver 1.2
	switch(loopbacktype)
	{	
		case Ch1_local:
		if(loadline)
		{
			if(Ch1_local_loop)
			{
				Ch1_local_loop = RESET;
				Timer10minen1  = RESET;
				Ch1_test_mode  = RESET;
				System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
				//Ver1.1
				Ch1_loop_min_alm = 1;
			        system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
				//ends here


				OUTPORT2_ADD = Led_cntl;
				OUTPORT1_ADD = loop_status;
 			        strcpy(Buffer,"Normal         ");
			        for(i=0,j=0;i<14;i++,j++)
                                Screens[LOCAL_SCR].string[1][j] = Buffer[i];
    		}
			else
			{
				Ch1_local_loop = SET;
				Timer10minen1  = SET;
				Ch1_test_mode  = SET;
		            	System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
				//Ver1.1
				Ch1_loop_min_alm = 0;
				system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
				//ends here
				OUTPORT2_ADD = Led_cntl;
				OUTPORT1_ADD = loop_status;
				strcpy(Buffer,"Local test mode");
				for(i=0,j=0;i<14;i++,j++)
    			        Screens[LOCAL_SCR].string[1][j] = Buffer[i];
			}
		}
		break;
  
  case Ch2_local:
    if(Twin_ch_system) /* Added by saravjit to prevent local loopack of ch2 in single configuration */	
	{
	  if(loadline)
		{
		if(Ch2_local_loop)
		      {
		      Ch2_local_loop = RESET;
		      Timer10minen2  = RESET;
		      Ch2_test_mode  = RESET;
		      System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
		      //Ver1.1
		      Ch2_loop_min_alm = 1;
		      system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
		      //ends here
		      OUTPORT2_ADD = Led_cntl;
 		      OUTPORT1_ADD = loop_status;
		      strcpy(Buffer,"Normal         ");
		      for(i=0,j=0;i<14;i++,j++)
    		      Screens[LOCAL_SCR+1].string[1][j] = Buffer[i];
		      }
		   else
		      {
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
			strcpy(Buffer,"Local test mode");
			for(i=0,j=0;i<14;i++,j++)
    		        Screens[LOCAL_SCR+1].string[1][j] = Buffer[i];
     	   		}
        }
	}  /* Added by saravjit to prevent local loopack of ch2 in single configuration */
	break;

  case Ch1_remote:
     if((SELF_ADD>=1)&&(SELF_ADD<=10))
	{                   
		/* if(!(loadline)) */
		/* Code modified for no remote loopback in case of AGC alarm-saravjit */
		if((!loadline) && (!Ch1AgcAlm)) 
		{
			if(Ch1_remote_loop)
			{
				
				Remoteloop(RL3,SW_ST_ID);	// resets remote loopback for channel 1
				Ch1_remote_loop = RESET;
				Timer10minen3 = RESET;
				Ch1_test_mode = RESET;
				System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
				//Ver1.1
				Ch1_loop_min_alm = 1;
				system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
				//ends here
				OUTPORT2_ADD = Led_cntl;
 				OUTPORT1_ADD = loop_status;
				strcpy(Buffer,"Normal         ");
				/***********************************************/
				//added in ver 1.4 to display message in screen
				/***********************************************/
				if(SW_ST_ID==1)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION1_SCR].string[1][j] = Buffer[i];
				}
				if(SW_ST_ID==2)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION2_SCR].string[1][j] = Buffer[i];
				}
				if(SW_ST_ID==3)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION3_SCR].string[1][j] = Buffer[i];
				}
				if(SW_ST_ID==4)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION4_SCR].string[1][j] = Buffer[i];
				}
				if(SW_ST_ID==5)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION5_SCR].string[1][j] = Buffer[i];
				}
				if(SW_ST_ID==6)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION6_SCR].string[1][j] = Buffer[i];
				}
				if(SW_ST_ID==7)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION7_SCR].string[1][j] = Buffer[i];
				}
				if(SW_ST_ID==8)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION8_SCR].string[1][j] = Buffer[i];
				}
				if(SW_ST_ID==9)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION9_SCR].string[1][j] = Buffer[i];
				}
				if(SW_ST_ID==10)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION10_SCR].string[1][j] = Buffer[i];
				}
		    	}
		    	else
		    	{
			/************************************************/
			// to set remote loop through dip switch in n+1 or n-1 station
			/**************************************************/ 
				if((SELF_ADD%2)==0)
				{
				Remoteloop(RL1,SELF_ADD-1); // sets remote loopback for channel 1
				SW_ST_ID=SELF_ADD-1;
				}
				else
				{	
				Remoteloop(RL1,SELF_ADD+1);
				SW_ST_ID=SELF_ADD+1;
				}
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
				strcpy(Buffer,"In Remote Loop");
				if(SELF_ADD==0x01)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION1_SCR].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==0x02)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION2_SCR].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==0x03)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION3_SCR].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==0x04)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION4_SCR].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==0x05)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION5_SCR].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==0x06)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION6_SCR].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==0x07)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION7_SCR].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==0x08)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION8_SCR].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==0x09)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION9_SCR].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==0x0A)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION10_SCR].string[1][j] = Buffer[i];
				}
                               
			}
        }
      }
else
display(Screens[STATUS_SCR+3].string);

	break;

  case Ch2_remote:
if((SELF_ADD>=1)&&(SELF_ADD<=10)) 
{
	  if(Twin_ch_system)	
    		{
	 /* if(!(loadline)) */
	 /* Code modified for no remote loopback in case of AGC alarm-saravjit */
		 if((!loadline) && (!Ch2AgcAlm))
		{
			if(Ch2_remote_loop)
			 {
				Remoteloop(RL4,SW_ST_ID);  // resets remote loopback for channel 2 
				Ch2_remote_loop = RESET;
				Timer10minen4 = RESET;
				Ch2_test_mode = RESET;
				System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
				//Ver1.1
				Ch2_loop_min_alm = 1;
    		    		system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
				//ends here
				OUTPORT2_ADD = Led_cntl;
 				OUTPORT1_ADD = loop_status;
				strcpy(Buffer,"Normal         ");
			/***********************************************/
			//added in ver 1.4 to display message in screen
			/***********************************************/
				if(SW_ST_ID==1)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION1_SCR+1].string[1][j] = Buffer[i];
				}
				if(SW_ST_ID==2)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION2_SCR+1].string[1][j] = Buffer[i];
				}
				if(SW_ST_ID==3)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION3_SCR+1].string[1][j] = Buffer[i];
				}
				if(SW_ST_ID==4)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION4_SCR+1].string[1][j] = Buffer[i];
				}
				if(SW_ST_ID==5)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION5_SCR+1].string[1][j] = Buffer[i];
				}
				if(SW_ST_ID==6)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION6_SCR+1].string[1][j] = Buffer[i];
				}
				if(SW_ST_ID==7)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION7_SCR+1].string[1][j] = Buffer[i];
				}
				if(SW_ST_ID==8)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION8_SCR+1].string[1][j] = Buffer[i];
				}
				if(SW_ST_ID==9)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION9_SCR+1].string[1][j] = Buffer[i];
				}
				if(SW_ST_ID==10)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION10_SCR+1].string[1][j] = Buffer[i];
				}			
                                                                                             
			}
			else
			 {  
		  	/************************************************/
			// to set remote loop through dip switch in n+1 or n-1 station
			/**************************************************/ 
		   
			        if((SELF_ADD%2)==0)
				{
				Remoteloop(RL2,SELF_ADD-1); // sets remote loopback for channel 2
				SW_ST_ID=SELF_ADD-1;
				}
				else
				{	
				Remoteloop(RL2,SELF_ADD+1);
				SW_ST_ID=SELF_ADD+1;
				}
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
				strcpy(Buffer,"In Remote Loop");
			/***********************************************/
			//added in ver 1.4 to display message in screen
			/***********************************************/
			   	if(SELF_ADD==0x01)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION1_SCR+1].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==0x02)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION2_SCR+1].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==0x03)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION3_SCR+1].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==0x04)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION4_SCR+1].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==0x05)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION5_SCR+1].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==0x06)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION6_SCR+1].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==0x07)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION7_SCR+1].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==0x08)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION8_SCR+1].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==0x09)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION9_SCR+1].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==0x0A)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION10_SCR+1].string[1][j] = Buffer[i];
				}
                             			
     			
			 }
        }
    }/*********************/
 }/********************/
else
display(Screens[STATUS_SCR+3].string);
	break;
	
       default:
	break;
    }
 }
 	       

 //ends here


/*******************************************************/    
// modified this function in ver 1.4 
/******************************************************/   

void Remoteloop (unsigned char remoteloop,unsigned char ST_CHECK )
{      
	unsigned char xdata Initial= 0,Loop=0;
       switch(remoteloop)
       {                                 
        
	case RL1:
	 //added in Ver1.4 for selecting channel for transmission 
	 Ch_sel  = SET; //changed
	 DTMF_en = RESET;		
	//ends here    
  
	    while(!(Loop))
	     {			
 	     if(Initial == 0)
	         {	
	          Tonedurationen1 = SET;
	    	  Initial  	  = SET;	
	          DTMF_TX_ADDR 	  = DTMF_TX_BYTE1;    //changed for testing
	    	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;    //Enable tone genr.
	         }		
	    if((Toneduration)&&(Tonedurationen1))  		
		 {
		  Tonedurationen1 = RESET;
	       	  Toneduration    = RESET;
	       	  Tonepauseen1    = SET;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_DIS;    //Disable tone genr.
	         }
	   if((Tonepause)&&(Tonepauseen1))
		 {	              
	          Tonedurationen2 = SET;
	       	  Tonepauseen1    = RESET;
	       	  Tonepause       = RESET;
	       	  DTMF_TX_ADDR 	  = DTMF_TX_BYTE2;    
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;    //Enable tone genr.
		 }	
           if((Toneduration)&&(Tonedurationen2))  		
 		 {
		  Tonedurationen2 = RESET;
	       	  Toneduration    = RESET;
	       	  Tonepauseen2    = SET;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_DIS;    //Disable tone genr.
	         }
               
	   if((Tonepause)&&(Tonepauseen2))
		 {	              
	          Tonedurationen3 = SET;
	       	  Tonepauseen2    = RESET;
	       	  Tonepause       = RESET;
	       	    
/************************************/
// added in ver 1.4 to send station id for ch1 
/**********************************/
	       	
		  switch(ST_CHECK)
			{
			case 1:
    		       		DTMF_TX_ADDR    = DTMF_ST1_ID;
	       			DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
				SW_ST_ID=1;
			break;
			case 2:
    				DTMF_TX_ADDR 	  = DTMF_ST2_ID;
	       			DTMF_CNTL_ADDR    = DTMF_TONE_ENA;
				SW_ST_ID=2;
			break;		
			case 3:
		
				DTMF_TX_ADDR 	  = DTMF_ST3_ID;
	       	  		DTMF_CNTL_ADDR    = DTMF_TONE_ENA;
				SW_ST_ID=3;
			break;
			case 4:
		
				DTMF_TX_ADDR 	  = DTMF_ST4_ID;
		       		DTMF_CNTL_ADDR    = DTMF_TONE_ENA;
				SW_ST_ID=4;
			break;
			case 5:
				DTMF_TX_ADDR 	  = DTMF_ST5_ID;
		       		DTMF_CNTL_ADDR    = DTMF_TONE_ENA;
				SW_ST_ID=5;
			break;
			case 6:
				DTMF_TX_ADDR 	  = DTMF_ST6_ID;
	       			DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
				SW_ST_ID=6;
			break;
			case 7:
				DTMF_TX_ADDR 	  = DTMF_ST7_ID;
	       			DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
				SW_ST_ID=7;
			break;
			case 8:
				DTMF_TX_ADDR 	  = DTMF_ST8_ID;
	       			DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
				SW_ST_ID=8;
			break;
			case 9:
				DTMF_TX_ADDR 	  = DTMF_ST9_ID;
	       	 		DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
				SW_ST_ID=9;
			break;
			case 10:
				DTMF_TX_ADDR 	  = DTMF_ST10_ID;
		       		DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
				SW_ST_ID=10;
			break;
			default:
			break;
			}
		  }
	   if((Toneduration)&&(Tonedurationen3))  		
 		 {
		  Tonedurationen3 = RESET;
	       	  Toneduration    = RESET;
	       	  Tonepauseen3    = SET;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_DIS;    //Disable tone genr.
	         }
		
		if((Tonepause)&&(Tonepauseen3))
		  {	
   		  Tonedurationen4 = SET;
	       	  Tonepauseen3    = RESET;
	       	  Tonepause       = RESET;
	       	  DTMF_TX_ADDR 	  = DTMF_TX1_BYTE;    
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;    //Enable tone genr.
		 }
		if((Toneduration)&&(Tonedurationen4))
		 {	
		  Tonedurationen4 = RESET;
	       	  Toneduration    = RESET;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_DIS;
		  Loop = SET;			
		 }
	
            }	
	       DTMF_en = SET;			//added in Ver1.4
	      	break;

	case RL2:
	 //added in Ver1.4 for selecting channel for transmission 
	 Ch_sel	= RESET;//changed
	 DTMF_en = RESET;		
	//ends here    

	    while(!(Loop))
	     {			
 	       if(Initial == 0)
	         {	
	          Tonedurationen1   = SET;
		  Initial 	    = SET;	
	          DTMF_TX_ADDR 	    = DTMF_TX_BYTE1;    //changed for testing
		  DTMF_CNTL_ADDR    = DTMF_TONE_ENA;    //Enable tone genr.
	          }		
	       if((Toneduration)&&(Tonedurationen1))  		
 		  {
		  Tonedurationen1 = RESET;
	       	  Toneduration    = RESET;
	       	  Tonepauseen1    = SET;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_DIS;    //Disable tone genr.
	         }
		if((Tonepause)&&(Tonepauseen1))
		 {	              
		  Tonedurationen2 = SET;
	       	  Tonepauseen1    = RESET;
	       	  Tonepause       = RESET;
	       	  DTMF_TX_ADDR 	  = DTMF_TX_BYTE2;    
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;    //Enable tone genr.
	         }	
        if((Toneduration)&&(Tonedurationen2))  		
		 {
		  Tonedurationen2 = RESET;
	       	  Toneduration    = RESET;
	       	  Tonepauseen2    = SET;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_DIS;    //Disable tone genr.
	         }
	 if((Tonepause)&&(Tonepauseen2))
		 {	              
	          Tonedurationen3 = SET;
	       	  Tonepauseen2    = RESET;
	       	  Tonepause       = RESET;
	
	/************************************/
	// added in ver 1.4 to send station id for ch2
	/**********************************/

	 
	
		 switch(ST_CHECK)
			{
			case 1:
		  DTMF_TX_ADDR 	  = DTMF_ST1_ID;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;
			case 2:
		  DTMF_TX_ADDR 	  = DTMF_ST2_ID;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;		
			case 3:
		  DTMF_TX_ADDR 	  = DTMF_ST3_ID;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;
			case 4:
		  DTMF_TX_ADDR 	  = DTMF_ST4_ID;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;
			case 5:
		  DTMF_TX_ADDR 	  = DTMF_ST5_ID;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;
			case 6:
		  DTMF_TX_ADDR 	  = DTMF_ST6_ID;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;
			case 7:
		  DTMF_TX_ADDR 	  = DTMF_ST7_ID;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;
			case 8:
		  DTMF_TX_ADDR 	  = DTMF_ST8_ID;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;
			case 9:
		  DTMF_TX_ADDR 	  = DTMF_ST9_ID;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;
			case 10:
		  DTMF_TX_ADDR 	  = DTMF_ST10_ID;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;
			default:
			break;
			}
		}
	    if((Toneduration)&&(Tonedurationen3))  		
 		 {
		  Tonedurationen3 = RESET;
	       	  Toneduration    = RESET;
	       	  Tonepauseen3    = SET;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_DIS;    //Disable tone genr.
	         }
		
	   if((Tonepause)&&(Tonepauseen3))
			{	
		  Tonedurationen4 = SET;
	       	  Tonepauseen3    = RESET;
	       	  Tonepause       = RESET;
	       	  DTMF_TX_ADDR 	  = DTMF_TX2_BYTE;    
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;    //Enable tone genr.
			}
	   if((Toneduration)&&(Tonedurationen4))
			{	
		  Tonedurationen4  = RESET;
	       	  Toneduration	   = RESET;
	       	  DTMF_CNTL_ADDR   = DTMF_TONE_DIS;
		      Loop = SET;			
			}
	
                 }	
	       	DTMF_en = SET;			//added in Ver1.4		
	    	break;

	case RL3:
	 
  	//added in Ver1.4 for selecting channel for transmission 
	 Ch_sel = SET;//changed
	 DTMF_en = RESET;		
	//ends here    
	    
	    while(!(Loop))
	     {			
 	       if(Initial == 0)
	         {	
	          Tonedurationen1   = SET;
		  Initial           = SET;	
	          DTMF_TX_ADDR 	    = DTMF_TX_BYTE1;    //changed for testing
		  DTMF_CNTL_ADDR    = DTMF_TONE_ENA;    //Enable tone genr.
	          }		
	       if((Toneduration)&&(Tonedurationen1))  		
 			{
		  Tonedurationen1 = RESET;
	       	  Toneduration    = RESET;
	       	  Tonepauseen1    = SET;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_DIS;    //Disable tone genr.
	         }
		if((Tonepause)&&(Tonepauseen1))
			{	              
		      Tonedurationen2 = SET;
	       	  Tonepauseen1    = RESET;
	       	  Tonepause       = RESET;
	       	  DTMF_TX_ADDR 	  = DTMF_TX_BYTE2;    
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;    //Enable tone genr.
	         }	
        if((Toneduration)&&(Tonedurationen2))  		
 	       	{
		  Tonedurationen2 = RESET;
	       	  Toneduration    = RESET;
	       	  Tonepauseen2    = SET;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_DIS;    //Disable tone genr.
	         }
	 if((Tonepause)&&(Tonepauseen2))
		 {	              
	          Tonedurationen3 = SET;
	       	  Tonepauseen2    = RESET;
	       	  Tonepause       = RESET;
	/************************************/
	// added in ver 1.4 to send station id for ch1 to reset remote loop	 
	/**********************************/
        
		 switch(ST_CHECK)
		 {
		 case 1:
  		 DTMF_TX_ADDR 	  = DTMF_ST1_ID;
	         DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
		 break;
		 case 2:
		    
		 DTMF_TX_ADDR 	  = DTMF_ST2_ID;
	         DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
		 break;		
			case 3:
			  DTMF_TX_ADDR 	  = DTMF_ST3_ID;
	        	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;
			case 4:
			  DTMF_TX_ADDR 	  = DTMF_ST4_ID;
	        	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;
			case 5:
			  DTMF_TX_ADDR 	  = DTMF_ST5_ID;
		       	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;
			case 6:
			  DTMF_TX_ADDR 	  = DTMF_ST6_ID;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;
			case 7:
			  DTMF_TX_ADDR 	  = DTMF_ST7_ID;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;
			case 8:
			  DTMF_TX_ADDR 	  = DTMF_ST8_ID;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;
			case 9:
			  DTMF_TX_ADDR 	  = DTMF_ST9_ID;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;
			case 10:
			  DTMF_TX_ADDR 	  = DTMF_ST10_ID;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;
			default:
			break;
			}
			}
	    if((Toneduration)&&(Tonedurationen3))  		
 		 {
		  Tonedurationen3 = RESET;
	       	  Toneduration    = RESET;
	       	  Tonepauseen3    = SET;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_DIS;    //Disable tone genr.
	         }		
		 
		if((Tonepause)&&(Tonepauseen3))
		  {	
		  Tonedurationen4 = SET;
	       	  Tonepauseen3    = RESET;
	       	  Tonepause       = RESET;
	       	  DTMF_TX_ADDR 	  = DTMF_TX3_BYTE;    
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;    //Enable tone genr.
			}
		if((Toneduration)&&(Tonedurationen4))
			{	
		  Tonedurationen4     = RESET;
	       	  Toneduration        = RESET;
	       	  DTMF_CNTL_ADDR      = DTMF_TONE_DIS;
		      Loop = SET;			
			}
	
             }	
	           DTMF_en = SET;			//added in Ver1.4	    	
       	
	    	
       		break;

	case RL4:
    //added in Ver1.4 for selecting channel for transmission 
	 Ch_sel = RESET;
	 DTMF_en = RESET;		
	//ends here    
	
	    while(!(Loop))
	     {			
 	       if(Initial == 0)
	         {	
	          Tonedurationen1   = SET;
		  Initial 	    = SET;	
	          DTMF_TX_ADDR 	    = DTMF_TX_BYTE1;    //changed for testing
		  DTMF_CNTL_ADDR    = DTMF_TONE_ENA;    //Enable tone genr.
	          }		
        if((Toneduration)&&(Tonedurationen1))  		
 		 {
	       	  Tonedurationen1 = RESET;
	       	  Toneduration    = RESET;
	       	  Tonepauseen1    = SET;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_DIS;    //Disable tone genr.
	         }
       	if((Tonepause)&&(Tonepauseen1))
		{	              
	       	  Tonedurationen2 = SET;
	       	  Tonepauseen1    = RESET;
	       	  Tonepause       = RESET;
	       	  DTMF_TX_ADDR 	  = DTMF_TX_BYTE2;    
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;    //Enable tone genr.
	         }	
        if((Toneduration)&&(Tonedurationen2))  		
 		 {
	       	  Tonedurationen2 = RESET;
	       	  Toneduration    = RESET;
	       	  Tonepauseen2    = SET;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_DIS;    //Disable tone genr.
	         }
       if((Tonepause)&&(Tonepauseen2))
		 {	              
	          Tonedurationen3 = SET;
	       	  Tonepauseen2    = RESET;
	       	  Tonepause       = RESET;
	/************************************/
	// added in ver 1.4 to send station id for ch2 to reset remote loop	 
	/**********************************/
        
	     switch(ST_CHECK)
			{
		case 1:
			DTMF_TX_ADDR     = DTMF_ST1_ID;
	       	  	DTMF_CNTL_ADDR   = DTMF_TONE_ENA;
			break;
		case 2:
			  DTMF_TX_ADDR 	  = DTMF_ST2_ID;
	 	      	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;		
		case 3:
			  DTMF_TX_ADDR 	  = DTMF_ST3_ID;
	       		  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;
		case 4:
			  DTMF_TX_ADDR 	  = DTMF_ST4_ID;
	       		  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;
		case 5:
			  DTMF_TX_ADDR 	  = DTMF_ST5_ID;
	       		  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;
		case 6:
			  DTMF_TX_ADDR 	  = DTMF_ST6_ID;
	       		  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;
		case 7:
			  DTMF_TX_ADDR 	  = DTMF_ST7_ID;
	       		  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;
		case 8:
			  DTMF_TX_ADDR 	  = DTMF_ST8_ID;
	       		  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;
		case 9:
			  DTMF_TX_ADDR 	  = DTMF_ST9_ID;
	       		  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;
		case 10:
			  DTMF_TX_ADDR 	  = DTMF_ST10_ID;
	       		  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;
			break;
			default:
			break;
			}
			}
		if((Toneduration)&&(Tonedurationen3))  		
 			{
			  Tonedurationen3 = RESET;
		       	  Toneduration    = RESET;
	       		  Tonepauseen3    = SET;
	       	  	  DTMF_CNTL_ADDR  = DTMF_TONE_DIS;    //Disable tone genr.
	         	}


		if((Tonepause)&&(Tonepauseen3))
			{	
	  	  Tonedurationen4 = SET;
	       	  Tonepauseen3    = RESET;
	       	  Tonepause       = RESET;
	       	  DTMF_TX_ADDR 	  = DTMF_TX4_BYTE;    
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_ENA;    //Enable tone genr.
			}
		if((Toneduration)&&(Tonedurationen4))
			{	
	       	  Tonedurationen4  = RESET;
	       	  Toneduration    = RESET;
	       	  DTMF_CNTL_ADDR  = DTMF_TONE_DIS;
		      Loop = SET;			
			}
	
               }	
	       DTMF_en = SET;			//added in Ver1.4	    	
              	    	
       		break;
	
		default:
		break;	
	}
   }
                                                                                                 
void DTMFRxprocess(void)
{  
  unsigned char xdata Buffer[20];
  unsigned char xdata i,j;
  int ScreenNo=0;
		                  
SELF_ADD=((INPORT7_ADD)&(0x0F));    // added in ver 1.4
	
  switch(DTMFRxByte)
   {	
   case DTMF_TX_BYTE1:
        Tone1waitflag = SET;
        Tone2waitflag = RESET;
	Tone3waitflag = RESET;
       	break;
    	
   case DTMF_TX_BYTE2:
        
	 if(Tone1waitflag)	
 	    {
	    Tone1waitflag = RESET;
	    Tone2waitflag = SET;
	    }
 	break;
	
   case DTMF_ST1_ID:
		if(Tone2waitflag)
	    	{
	    	Tone2waitflag=RESET;
                RX_ST_CH=1;             // to keep the station number
	        if(SELF_ADD==DTMFRxByte)
		{ 
		Tone3waitflag=SET;
		}

	    }  
		
	   break;
/****************************************/
//added in ver 1.4  to receive the station id
/****************************************/

   case DTMF_ST2_ID:
	   if(Tone2waitflag)
	    {
	    Tone2waitflag=RESET;
	        RX_ST_CH=2;
		if(SELF_ADD==DTMFRxByte)
		{ 
		Tone3waitflag=SET;
		}
	    }            
	 break;
  case DTMF_ST3_ID:
	  if(Tone2waitflag)
	    {
	    Tone2waitflag=RESET;
	        RX_ST_CH=3;
		if(SELF_ADD==DTMFRxByte)
		{ 
		Tone3waitflag=SET;
		}
	    }            
	       break;
  case DTMF_ST4_ID:
	    if(Tone2waitflag)
	    {
	    Tone2waitflag=RESET;
	    RX_ST_CH=4;
		if(SELF_ADD==DTMFRxByte)
		{ 
		Tone3waitflag=SET;
		}
	    }            
	    break;
  case DTMF_ST5_ID:
	    if(Tone2waitflag)
	    {
	    Tone2waitflag=RESET;
	        RX_ST_CH=5;
		if(SELF_ADD==DTMFRxByte)
		{ 
		Tone3waitflag=SET;
		}
	    }            
		break;
 case DTMF_ST6_ID:
		if(Tone2waitflag)
	    {
	    Tone2waitflag=RESET;
	     RX_ST_CH=6;
		if(SELF_ADD==DTMFRxByte)
		{ 
		Tone3waitflag=SET;
		}
	    }            
		break;
 case DTMF_ST7_ID:
		if(Tone2waitflag)
	    {
	    Tone2waitflag=RESET;
	        RX_ST_CH=7;
		if(SELF_ADD==DTMFRxByte)
		{ 
		Tone3waitflag=SET;
		}
	    }            
		break;
 case DTMF_ST8_ID:
	    if(Tone2waitflag)
	    {
	    Tone2waitflag=RESET;
	        RX_ST_CH=8;
		if(SELF_ADD==DTMFRxByte)
		{ 
		Tone3waitflag=SET;
		}
	    }            
		break;
 case DTMF_ST9_ID:
	    if(Tone2waitflag)
	    {
	    Tone2waitflag=RESET;
	        RX_ST_CH=9;
		if(SELF_ADD==DTMFRxByte)
		{ 
		Tone3waitflag=SET;
		}
	    }            
		break;
 case DTMF_ST10_ID:
	        if(Tone2waitflag)
	    {
	    Tone2waitflag=RESET;
	        RX_ST_CH=10;
		if(SELF_ADD==DTMFRxByte)
		{ 
		Tone3waitflag=SET;
		}
	    }            
		break;


    case DTMF_TX1_BYTE:  // sets remote-remote  loopback for channel 1
/**********************************************/
//add in ver 1.4 Screens added to display the loop status 
/********************************************/
       	                
	 if(Tone3waitflag)	
			{
			Tone3waitflag = RESET;
			Ch1_test_mode = SET;
			Timer10minen3 = SET; // added by taranjit to run 10 min timer when remote loopback tone for channel 1 received 
			//Ver1.1
			Ch1_loop_min_alm = 0;
			system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
			//ends here
			System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
			OUTPORT2_ADD = Led_cntl;
			Ch1_remrem_loop = SET;
			OUTPORT1_ADD = loop_status;
			strcpy(Buffer,"In Remote Loop");
		      	 	if(SELF_ADD==1)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION1_SCR].string[1][j] = Buffer[i];
				}
			     	if(SELF_ADD==2)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION2_SCR].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==3)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION3_SCR].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==4)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION4_SCR].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==5)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION5_SCR].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==6)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION6_SCR].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==7)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION7_SCR].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==8)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION8_SCR].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==9)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION9_SCR].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==10)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION10_SCR].string[1][j] = Buffer[i];
				}			
			}	
	break;

    case DTMF_TX2_BYTE:  // sets remote-remote loopback for channel 2
	/****************************************************/
	// added in ver 1.4 Screens added to display the loop status in all stations
	/****************************************************/
	strcpy(Buffer,"In Remote Loop");
	if(Twin_ch_system)	
      	     {                  
		      	       
			       	
        
	  if(Tone3waitflag)
			{
			Tone3waitflag = RESET;
			Ch2_test_mode = SET;
			Timer10minen4 = SET; // added by taranjit to run 10 min timer when remote loopback tone for channel 2 received 
			//Ver1.1
			Ch2_loop_min_alm = 0;
			system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
			//ends here
			System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
			OUTPORT2_ADD = Led_cntl;
			Ch2_remrem_loop = SET;
			OUTPORT1_ADD = loop_status;
                        	if(SELF_ADD==1)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION1_SCR+1].string[1][j] = Buffer[i];
				}
			     	if(SELF_ADD==2)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION2_SCR+1].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==3)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION3_SCR+1].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==4)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION4_SCR+1].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==5)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION5_SCR+1].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==6)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION6_SCR+1].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==7)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION7_SCR+1].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==8)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION8_SCR+1].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==9)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION9_SCR+1].string[1][j] = Buffer[i];
				}
				if(SELF_ADD==10)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION10_SCR+1].string[1][j] = Buffer[i];
				}


			}	
	}
	break;

   case DTMF_TX3_BYTE:  // resets remote-remote loopback for channel 1
	/*************************************************/
	 //added in ver 1.4 Screens added to display the loop status in all stations
	/************************************************/
                             strcpy(Buffer,"Normal         ");
			     if(RX_ST_CH==1)
			 	{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION1_SCR].string[1][j] = Buffer[i];
				}
				if(RX_ST_CH==2)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION2_SCR].string[1][j] = Buffer[i];
				}
				if(RX_ST_CH==3)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION3_SCR].string[1][j] = Buffer[i];
				}
				if(RX_ST_CH==4)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION4_SCR].string[1][j] = Buffer[i];
				}
				if(RX_ST_CH==5)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION5_SCR].string[1][j] = Buffer[i];
				}
				if(RX_ST_CH==6)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION6_SCR].string[1][j] = Buffer[i];
				}
				if(RX_ST_CH==7)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION7_SCR].string[1][j] = Buffer[i];
				}
				if(RX_ST_CH==8)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION8_SCR].string[1][j] = Buffer[i];
				}
				if(RX_ST_CH==9)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION9_SCR].string[1][j] = Buffer[i];
				}
				if(RX_ST_CH==10)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION10_SCR].string[1][j] = Buffer[i];
				}

      if(Tone3waitflag)
			{
			Tone3waitflag = RESET;	
			Ch1_test_mode = RESET;
			Timer10minen3 = RESET; //added by taranjit to reset  timer for channel 1 remote loopback
			//Ver1.1
			Ch1_loop_min_alm = 1;
			system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);
			//ends here
			System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);
			OUTPORT2_ADD = Led_cntl;
			Ch1_remrem_loop = RESET;
			OUTPORT1_ADD = loop_status;
			}	
	break;

  case DTMF_TX4_BYTE:  // resets remote-remote loopback for channel 2
	/**********************************/
	//added in Screens added to display the loop status in all stations
	/**************************************/
	       strcpy(Buffer,"Normal         ");
	if(Twin_ch_system)	
      	     {
				if(RX_ST_CH==1)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION1_SCR+1].string[1][j] = Buffer[i];
				}
				if(RX_ST_CH==2)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION2_SCR+1].string[1][j] = Buffer[i];
				}
				if(RX_ST_CH==3)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION3_SCR+1].string[1][j] = Buffer[i];
				}
				if(RX_ST_CH==4)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION4_SCR+1].string[1][j] = Buffer[i];
				}
				if(RX_ST_CH==5)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION5_SCR+1].string[1][j] = Buffer[i];
				}
				if(RX_ST_CH==6)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION6_SCR+1].string[1][j] = Buffer[i];
				}
				if(RX_ST_CH==7)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION7_SCR+1].string[1][j] = Buffer[i];
				}
				if(RX_ST_CH==8)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION8_SCR+1].string[1][j] = Buffer[i];
				}
				if(RX_ST_CH==9)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION9_SCR+1].string[1][j] = Buffer[i];
				}
				if(RX_ST_CH==10)
				{
			       for(i=0,j=0;i<14;i++,j++)
    			       Screens[STATION10_SCR+1].string[1][j] = Buffer[i];
				}	

	  if(Tone3waitflag)
			{
			Tone3waitflag = RESET;												   
			Ch2_test_mode = RESET;													
			Timer10minen4 = RESET; //added by taranjit to reset  timer for channel 2 remote loopback
			//Ver1.1																	
			Ch2_loop_min_alm = 1;														
			system_min_alm = (fault_min_alm )&(Ch1_loop_min_alm)&(Ch2_loop_min_alm);	
			//ends here																	
			System_test_mode = (Ch1_test_mode)|(Ch2_test_mode);							
			OUTPORT2_ADD = Led_cntl;													
			Ch2_remrem_loop = RESET;													
			OUTPORT1_ADD = loop_status;													
			}	
	}
	    break;
	//}   
  default:

        break;
  	
     	
}

}	


     	   
   
   
                                                   





