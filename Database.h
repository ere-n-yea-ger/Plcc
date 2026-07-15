/*###########################################################################
Project				:	PLCC Supy
Filename				:	Database.H
Previous Version	:  not applicable
New Version			:	0.1
Modified  on		:	19-03-1999
Last Modified by	:	G.S.Ubhi
Editor Tab Size  	:	3
Comments				:
###########################################################################*/

public unsigned char bdata Led_cntl;
public unsigned char bdata Alarm1_value;
public unsigned char bdata Alarm2_value; 
public unsigned char bdata Alarm3_value;
public unsigned char bdata Alarm4_value;
public unsigned char bdata Alarm5_value;
public unsigned char bdata Alarm7_value;
public unsigned char bdata Test_mode;
/*****************************************/
//ADDED IN Ver 1.4 TO KEEP STATION ID
/****************************************/
public unsigned char xdata STATION_ID; 
public unsigned char xdata SELF_ADD; 
/***************************************/
public unsigned char bdata loop_status;                             
public unsigned char xdata Agc_voltage;
public unsigned char xdata PAMP_value;
public unsigned char xdata AGC1_value;
public unsigned char xdata AGC2_value;
public unsigned char xdata P12V_value;
public unsigned char xdata N12V_value;   
public unsigned char xdata P36V_value;
public unsigned char xdata N36V_value;
public unsigned char xdata P5V_value;
public unsigned char xdata Twin_ch_system;
public unsigned char xdata loopbacktype;
public unsigned char bdata Switch_status;
public unsigned char xdata Timer10minen1;
public unsigned char xdata Timer10minen2;
public unsigned char xdata Timer10minen3;
public unsigned char xdata Timer10minen4;
public unsigned char xdata Flashledflag;
public unsigned char xdata none;
//public unsigned char xdata S_Time50msCnt;
public unsigned char xdata S_Time100msCnt;
public unsigned char xdata S_Time500msCnt;
//public unsigned char xdata S_Time50ms;
public unsigned char xdata S_Time100ms;
public unsigned char xdata S_Time500ms; 

public unsigned int xdata S_Time12minCnt1;	//reset_mtu
public unsigned int xdata S_Time10minCnt1;
public unsigned char xdata S_Time10min1;
public unsigned int xdata S_Time10minCnt2;
public unsigned char xdata S_Time10min2;

public unsigned int xdata S_Time10minCnt3;
public unsigned char xdata S_Time10min3;
public unsigned int xdata S_Time10minCnt4;
public unsigned char xdata S_Time10min4;

public unsigned char xdata S_Time2sCnt;
public unsigned char xdata Tonedurationen1;
public unsigned char xdata Tonepauseen1;
public unsigned char xdata Tonedurationen2;
public unsigned char xdata Tonepauseen2;
public unsigned char xdata Tonepauseen3;
public unsigned char xdata Tonedurationen3;
/****************************************/
// added in ver 1.4
/******************************************/
public unsigned char xdata Tonedurationen4; 
public unsigned char xdata Toneduration;
public unsigned char xdata Tonepause;
public unsigned char xdata TonedurationCnt;
public unsigned char xdata TonepauseCnt;
public unsigned char xdata Tone1waitflag;
public unsigned char xdata Tone2waitflag;
public unsigned char xdata Tone3waitflag;
public unsigned char xdata Tone1waitCnt;
public unsigned char xdata Tone2waitCnt;
public unsigned char xdata Tone3waitCnt;
public unsigned char xdata DTMFRxflag;
public unsigned char xdata DTMFTxflag;
public unsigned char xdata DTMFRxByte;
public unsigned char xdata DTMFRx_ID;
public unsigned char xdata InterruptMask; 
/*************************************/
// added in ver 1.4
/***************************************/
public unsigned char xdata ST_CHECK;  
public unsigned char xdata RX_ST_CH;  
public unsigned char xdata SW_ST_ID;  
/***************************************/
/*************************************/
// added in ver 1.5
/***************************************/
public int xdata  k,AGC1_scr,AGC2_scr,PAMP_scr,ch1_agc,ch2_agc,ch_PAMP,v12; 
public  float xdata agc;
public  float xdata agc1;
public unsigned char xdata agc2;
/****************************************/


extern bit E_IN1,E_IN2,M_OUT1,M_OUT2,OutputLowAlm,OverloadAlm,FuseAlm,
     	loadline,Ch1AgcAlm,Ch1SNAlm,Ch1Mute,Ch2AgcAlm,Ch2SNAlm,Ch2Mute ,
     	PsuFaulty,TCXOAlm ,RTUAlm1 ,RTUAlm2 ,RTUAlm3,RTUAlm4 ,RTUAlm5 ,     
     	RTUAlm6 , RTUAlm7 , RTUAlm8 , SystemConfig  , ExtAlm  ,DoorOpenAlm , 
     	AdcRdy  , system_maj_alm , system_min_alm  , rtu_alm_cfg    ,
     	System_health , System_not_ok , System_ok , System_test_mode,
     	Ch1_local_loop , Ch1_remote_loop, Ch1_remrem_loop,Ch2_local_loop,
     	Ch2_remote_loop,Ch2_remrem_loop,major_alm,minor_alm,local,	                  
        slot1, slot2,slot3,slot4,slot5, slot6, slot7, slot8,Ch1_test_mode,
        Ch2_test_mode,switchll,switchrl,channel1,fault_min_alm,Ch1_loop_min_alm,Ch2_loop_min_alm;

	



