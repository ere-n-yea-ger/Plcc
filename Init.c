/*###########################################################################
Project			:	PLCC Supv
Filename		:	init.C
Previous Version	:  Not Applicable
New Version		:	0.1
Modified  on		:	15-04-1999
Last Modified by	:	G.S.Ubhi
Editor Tab Size  	:	3
Comments		:
############################################################################*/


#define public 
#include <string.h>
#include <reg51.h>
#include "def.h"
#include "database.h"
#include "declare.h"
//#include "addr.h"
                                                        
public unsigned char xdata OUTPORT1_ADD   		_at_ 0x9000;
public unsigned char xdata OUTPORT2_ADD   		_at_ 0x9200;
public unsigned char xdata ADC_ADD        	    _at_ 0x9400;
//public unsigned char xdata PHASE_ADD      		_at_ 0x9A00;
//public unsigned char xdata DTMF_TXRX_ADD     		_at_ 0x9C00;
public unsigned char xdata INPORT1_ADD    		_at_ 0x8000;
public unsigned char xdata INPORT2_ADD    		_at_ 0x8200;
public unsigned char xdata INPORT3_ADD    		_at_ 0x8400;
public unsigned char xdata INPORT4_ADD    		_at_ 0x8600;
public unsigned char xdata INPORT5_ADD    		_at_ 0x8800;
public unsigned char xdata INPORT6_ADD    		_at_ 0x8A00;
public unsigned char xdata INPORT7_ADD    		_at_ 0x8C00;
public unsigned char xdata INPORT8_ADD    		_at_ 0x8E00;
public unsigned char xdata NVRAM_START_ADDR		_at_ 0xA000;
public unsigned char xdata NVRAM_END_ADDR	   	_at_ 0xBFFF;
public unsigned char xdata DUART_MRA_WRITE_ADDR	    _at_ 0x9600;
public unsigned char xdata DUART_CSRA_ADDR	       	_at_ 0x9601;
public unsigned char xdata DUART_CRA_ADDR	       	_at_ 0x9602;
public unsigned char xdata DUART_THRA_ADDR	       	_at_ 0x9603;
public unsigned char xdata DUART_ACR_ADDR	       	_at_ 0x9604;
public unsigned char xdata DUART_IMR_ADDR	       	_at_ 0x9605;
public unsigned char xdata DUART_CTU_WRITE_ADDR		_at_ 0x9606;
public unsigned char xdata DUART_CTL_WRITE_ADDR		_at_ 0x9607;
public unsigned char xdata DUART_MRB_WRITE_ADDR		_at_ 0x9608;
public unsigned char xdata DUART_CSRB_ADDR	       	_at_ 0x9609;
public unsigned char xdata DUART_CRB_ADDR	       	_at_ 0x960A;
public unsigned char xdata DUART_THRB_ADDR	       	_at_ 0x960B;
public unsigned char xdata DUART_IVR_WRITE_ADDR		_at_ 0x960C;
public unsigned char xdata DUART_OPCR_ADDR   		_at_ 0x960D;
public unsigned char xdata DUART_SOPBC_ADDR 		_at_ 0x960E;
public unsigned char xdata DUART_COPBC_ADDR	       	_at_ 0x960F;
public unsigned char xdata LCD_CMD_ADDR		       	_at_ 0x9800;
public unsigned char xdata LCD_DATA_ADDR	       	_at_ 0x9802;
//added in Ver1.2
public unsigned char xdata DTMF_CNTL_ADDR	       	_at_ 0x9a02;    //write to ctrl
public unsigned char xdata DTMF_STAT_ADDR 	       	_at_ 0x9a03;    //read status
public unsigned char xdata DTMF_TX_ADDR		       	_at_ 0x9a00;   //write to Tx
public unsigned char xdata DTMF_RX_ADDR 	       	_at_ 0x9a01;   //read from Rx
extern unsigned char	lcd_reset_flag;			//reset_mtu
//ends here



                                                    
sbit E_IN1 	       	=    Alarm1_value^0 ;
sbit E_IN2       	=    Alarm1_value^1 ;
sbit M_OUT1	        =    Alarm1_value^2 ;
sbit M_OUT2	       	=    Alarm1_value^3 ;
sbit OutputLowAlm 	=    Alarm1_value^4 ;
sbit OverloadAlm	=    Alarm1_value^5 ;
sbit FuseAlm		=    Alarm1_value^6 ;
sbit loadline		=    Alarm1_value^7 ;
sbit Ch1AgcAlm		=    Alarm2_value^0 ;
sbit Ch1SNAlm		=    Alarm2_value^1 ;
sbit Ch1Mute		=    Alarm2_value^2 ;
sbit Ch2AgcAlm		=    Alarm2_value^3 ;
sbit Ch2SNAlm		=    Alarm2_value^4 ;
sbit Ch2Mute		=    Alarm2_value^5 ;
sbit PsuFaulty		=    Alarm2_value^6 ;
sbit TCXOAlm		=    Alarm2_value^7 ;
sbit slot1      	=    Alarm3_value^0 ;
sbit slot2      	=    Alarm3_value^1 ;
sbit slot3      	=    Alarm3_value^2 ;
sbit slot4      	=    Alarm3_value^3 ;
sbit slot5      	=    Alarm3_value^4 ;
sbit slot6      	=    Alarm3_value^5 ;
sbit slot7      	=    Alarm3_value^6 ;
sbit slot8      	=    Alarm3_value^7 ;
sbit RTUAlm1      	=    Alarm5_value^0 ;
sbit RTUAlm2      	=    Alarm5_value^1 ;
sbit RTUAlm3      	=    Alarm5_value^2 ;
sbit RTUAlm4      	=    Alarm5_value^3 ;
sbit RTUAlm5      	=    Alarm5_value^4 ;
sbit RTUAlm6      	=    Alarm5_value^5 ;
sbit RTUAlm7      	=    Alarm5_value^6 ;
sbit RTUAlm8      	=    Alarm5_value^7 ;
/*sbit FanAlm       =    Alarm4_value^0 ; now used for 20w or 40w header*/
sbit SystemConfig	=    Alarm4_value^0;/*for 20w or 40w*/
sbit ExtAlm       	=    Alarm4_value^1 ;
sbit DoorOpenAlm  	=    Alarm4_value^2 ;
sbit switchll		=    Alarm4_value^3 ; 
sbit switchrl		=    Alarm4_value^4 ; 
sbit channel1		=    Alarm4_value^5 ; 
sbit channel2		=    Alarm4_value^6 ; 
sbit AdcRdy       	=    Alarm4_value^7 ;
sbit RTUAlm9      	=    Alarm7_value^0 ;
sbit RTUAlm10      	=    Alarm7_value^1 ;
sbit RTUAlm11     	=    Alarm7_value^2 ;
sbit RTUAlm12     	=    Alarm7_value^3 ;
sbit RTUAlm13      	=    Alarm7_value^4 ;
sbit RTUAlm14      	=    Alarm7_value^5 ;
sbit RTUAlm15      	=    Alarm7_value^6 ;
sbit RTUAlm16      	=    Alarm7_value^7 ;



sbit system_maj_alm  	=	Led_cntl^0;
sbit system_min_alm  	=	Led_cntl^1;
sbit rtu_alm_cfg      	=	Led_cntl^2;
sbit System_health    	=	Led_cntl^3;
sbit System_ok 	      	=	Led_cntl^4;
sbit System_not_ok     	=	Led_cntl^5;
sbit System_test_mode	=	Led_cntl^6;

sbit Ch1_local_loop  	=	loop_status^0;
sbit Ch1_remote_loop  	=	loop_status^1;
sbit Ch1_remrem_loop    =	loop_status^2;
sbit Ch2_local_loop   	=	loop_status^3;
sbit Ch2_remote_loop 	=	loop_status^4;
sbit Ch2_remrem_loop   	=	loop_status^5;
sbit major_alm      	=	loop_status^6;
sbit minor_alm      	=	loop_status^7;
sbit Ch1_test_mode    	= 	Test_mode^1;
sbit Ch2_test_mode    	= 	Test_mode^2;
sbit fault_min_alm    	= 	Test_mode^3;
sbit Ch1_loop_min_alm	= 	Test_mode^4;
sbit Ch2_loop_min_alm	= 	Test_mode^5;




void InitController(void)
{

	TL0  = 0xFF;    		/* For Tick of 15ms -> C5FF; 20ms -> B7FF; 10ms -> DBFF ds-25msec->a5ff for Osc. Freq. of 11.0592 MHz */
	TH0  = 0xA5;
	TL1  = 0x00;    		/* AutoReload Count = E8 for Baud rate = 1200  for Osc. Freq. of 11.0592 MHz */
	TH1  = 0xE8;    		/* AutoReload Count = FD for Baud rate = 9600  for Osc. Freq. of 11.0592 MHz */
			     	/* SCON   (Serial Port Control) */
	REN  = 1;		/* Reception Disabled */
	SM2  = 0; 		/* For Valid Stop Bit */
	SM1  = 1; 		/* Mode 1             */
	SM0  = 0;
	RI   = 0;
	TI   = 0;
				/* Using TImer 1 as a Baud Rate Generator 	*/
	TMOD = 0x21;
				/* Timer 0 = Timer with internal control
				   Timer 0 = Mode 1 (16-Bit Timer)
				   Timer 1 = Timer with internal control
				   Timer 1 = Mode 2 (8-Bit AutoReload Timer)	*/
				/* TCON  (Timer Control)                    	*/
    TR1 = 1;   		/* Timer 1 = ON  */
    TR0 = 1;   		/* Timer 0 = ON  */
    IT0 = 1;		/* edge Triggered External Interrupt0 */
    IT1 = 0;		/* edge Triggered External Interrupt1 */
 	IP  = 0x02; 		/* Interrupt Priority */

   	IE  = 0x82;		/* Check */	
				/* EA - - ES ET1 EX1 ET0 EX0
				   1  0 0  0  0   0   1   0
    				   Interrupt Mask = Disabled 97       
     			           Timer Interrupt = Enable*/
}  

void InitDUART(void)
{
	DUART_MRA_WRITE_ADDR 	= CHAR_8B_NP_CE_RI_NRR;
	DUART_MRA_WRITE_ADDR 	= MODE_N_NTR_NTC_1SB ;
	DUART_ACR_ADDR			= CLOCK_SET0 ;
	DUART_CRA_ADDR 			= CLEAR_RX_BRG_BIT ;
	DUART_CRA_ADDR 			= CLEAR_TX_BRG_BIT ;
	DUART_CSRA_ADDR 		= BAUD_9600_INT ;
	DUART_CRA_ADDR 			= RESET_MR_PTR;
	DUART_CRA_ADDR	 		= RESET_RECEIVER;
	DUART_CRA_ADDR 			= RESET_TRANSMITTER;
	DUART_CRA_ADDR 			= RESET_ERROR_STATUS;
	DUART_CRA_ADDR 			= RESET_BRK_CNG_INT;

	// Enable Transmitter and Receiver for Channel A 
	DUART_CRA_ADDR 			= 0x05; 

	DUART_MRB_WRITE_ADDR 	= CHAR_8B_NP_CE_RI_NRR;
	DUART_MRB_WRITE_ADDR 	= MODE_N_NTR_NTC_1SB;
	DUART_CRB_ADDR 			= CLEAR_RX_BRG_BIT;
	DUART_CRB_ADDR 			= CLEAR_TX_BRG_BIT;
	DUART_CSRB_ADDR 		= BAUD_4800_INT;
	DUART_CRB_ADDR 			= RESET_MR_PTR;
	DUART_CRB_ADDR 			= RESET_RECEIVER;
	DUART_CRB_ADDR 			= RESET_TRANSMITTER;
	DUART_CRB_ADDR 			= RESET_ERROR_STATUS;
	DUART_CRB_ADDR 			= RESET_BRK_CNG_INT;

	InterruptMask 			= 0x00;
	DUART_IMR_ADDR 			= InterruptMask;
}
  
void InitLCD(void)
{
    
  	Delay(100);
  	 LCD_CMD_ADDR = LCD_INIT_BYTE;
	Delay(50);										
	 LCD_CMD_ADDR = LCD_INIT_BYTE;
	Delay(50);										
	 LCD_CMD_ADDR = LCD_INIT_BYTE;
	Wait40();
	 LCD_CMD_ADDR = LCD_8B_2L_7D;
	Wait40();
	 LCD_CMD_ADDR = LCD_DISP_ON_CRSR_BLINK;
	Wait40();
	LCD_CMD_ADDR = LCD_MODE_INC;
	Wait40();
	 LCD_CMD_ADDR = LCD_CLEAR_DISP;
     Delay(1000);     
    if(!S_Time12minCnt1)		//reset_mtu
		S_Time12minCnt1=1;
}
  

void InitDbase(void)

{
       
	
 	Led_cntl        = 0x00	;
 	loop_status   	= 0x00	;
 	Alarm1_value	= 0x00	;
 	Alarm2_value	= 0x00	; 
 	Alarm3_value	= 0xff	;
 	Alarm4_value	= 0x00	;
 	Alarm5_value	= 0x00	;
 	loop_status   	= 0x00	;
 	Agc_voltage   	= 0x00	;
 	AGC1_value     	= 0x00	;
 	AGC2_value     	= 0x00	;
 	P12V_value     	= 0x00	;
 	N12V_value     	= 0x00	;
 	P36V_value     	= 0x00	;
 	N36V_value     	= 0x00	;
 	P5V_value      	= 0x00	;
 	Twin_ch_system	= 0x00	;
	loopbacktype	= 0x00	;
 	Switch_status	= 0x00	;
 	Timer10minen1	= 0x00	;
 	Timer10minen2	= 0x00	;
 	Flashledflag	= 0x00	;
	lcd_reset_flag	= 0x00  ;	//reset_mtu
   	// S_Time50msCnt= 0x00	;
 	S_Time100msCnt	= 0x00	;
 	S_Time500msCnt	= 0x00	;
	S_Time2sCnt 	= 0x00	;
	Tonedurationen1	= RESET	;
 	Tonepauseen1	= RESET	;
	Tonedurationen2	= RESET	;
 	Tonepauseen2	= RESET	;
 	Tonedurationen3	= RESET	;
	Toneduration	= RESET	;
 	Tonepause    	= RESET	;
 	TonedurationCnt	= 0x00	;
 	TonepauseCnt	= 0x00	;
	Tone1waitCnt	= 0x00	;
	Tone2waitCnt	= 0x00	;
	//S_Time50ms  	= 0x00	;
    S_Time100ms    	= 0x00	;
    S_Time500ms    	= 0x00	; 
 	S_Time10minCnt1 = 0x00	;
	S_Time12minCnt1	= 0x00  ;		//reset_mtu
 	S_Time10min1    = 0x00	;
 	S_Time10minCnt2 = 0x00	;
 	S_Time10min2    = 0x00	;
    InterruptMask  	= 0x00	; 
 	Twin_ch_system 	= (INPORT6_ADD>>6) & 0x01 ;
 	fault_min_alm  	=  SET	;
 	Ch1_loop_min_alm =  SET	;
 	Ch2_loop_min_alm =  SET	;
 	DTMFRxflag	=  RESET;
   	DTMFRxByte	=  0x00	;
	DTMFRx_ID	=  0x00;
	DTMFTxflag	=  SET	;
/************************************/
	agc	    	= 0x00  ;
	agc2		= 0x00  ;	 
	agc1		= 0x00  ;
   	AGC1_scr	= 0	;
   	AGC2_scr	= 0	;
	PAMP_scr	= 0	;
/*************************************/	 
        
	
	
	}

//Added in Ver1.2 to implement remoteloopback function


void InitDTMF(void)

 {
        unsigned int xdata Initial; 
	Initial	    	= DTMF_STAT_ADDR; 	 
	Delay (20);
	DTMF_CNTL_ADDR 	= DTMF_INIT_BYTE;
	Delay (20);
	DTMF_CNTL_ADDR 	= DTMF_INIT_BYTE;
	Delay (20);
	DTMF_CNTL_ADDR 	= DTMF_INIT1_BYTE;	       
	Delay (20);
	DTMF_CNTL_ADDR 	= DTMF_INIT_BYTE;
	Delay (20);
	Initial	    	= DTMF_STAT_ADDR;
   	Delay (20);
	DTMF_CNTL_ADDR 	= DTMF_IRQ_DTMF;     
	Delay (20);
	DTMF_CNTL_ADDR 	= DTMF_NON_BURST;
	Delay (20);
	
 } 




