
/*###########################################################################
Project			:	PLCC Supv
Filename		:	DEF.H
Previous Version	:  	Not Applicable
New Version		:	0.1
Modified  on		:	13-04-1999
Last Modified by	:	G.S.Ubhi
Editor Tab Size  	:	3
Comments		:	
############################################################################*/
/*===========================================================================
								Revision History
								================


===========================================================================*/
#define KEY_DEBOUNCE_THRS			                	4
#define MAXTICKCOUNT        		       	                        150		/*Gurjit2*/ /*scr_&_agc_bars*/
//added in Ver 1.2 for increasing debounce as discussed with Mr. Vimal
//#define SW_DEBOUNCE_THRS			     	                5
#define SW_DEBOUNCE_THRS					     	7
#define No_loop								0
#define Ch1_local			 				1
#define Ch2_local			 				2
#define Ch1_remote			 				3
#define Ch2_remote			 				4

#define RL1			 					7
#define RL2			 					8
#define RL3			 					9
#define RL4			 					10


/*---------------------------------------------------------------------------
				General Definetions
----------------------------------------------------------------------------*/

#define SET    					1
#define RESET                     		0
#define OK             				0x00

/*---------------------------------------------------------------------------
				BIOS Call Nos
----------------------------------------------------------------------------*/

#define GetKey						0x01
#define DisplayChar					0x02
#define SetCursorPosition		       		0x03
#define ClearDisplay					0x04
#define ChangeDisplayMode		       		0x05

/*---------------------------------------------------------------------------
				ADC Channel Selection
----------------------------------------------------------------------------*/

#define Read_N12V 					0x0B
#define Read_P12V 					0x0C
#define Read_P5V     					0x0D
#define Read_N36V 					0x0E
#define Read_P36V 					0x0F
#define Read_Power_level		  		0x0A
#define Read_AGC1       	       			0x09
#define Read_AGC2	                		0x08


/*---------------------------------------------------------------------------
				Dual UART - 68681 Commands
----------------------------------------------------------------------------*/

/* Interrupt Status Register */
#define TX_A_READY 					0x01
#define RX_A_READY 					0x02
#define DELTA_BREAK_A					0x04
#define COUNTER_READY 					0x08
#define TX_B_READY	 				0x10
#define RX_B_READY 					0x20
#define DELTA_BREAK_B			       		0x40
#define IP_PORT_CHANGE					0x80

/* Interrupt Mask Register */
#define ENABLE_TX_A_READY_INT	 			0x01
#define ENABLE_RX_A_READY_INT				0x02
#define ENABLE_DELTA_BREAK_A_INT			0x04
#define ENABLE_COUNTER_READY_INT			0x08
#define ENABLE_TX_B_READY_INT				0x10
#define ENABLE_RX_B_READY_INT				0x20
#define ENABLE_DELTA_BREAK_B_INT			0x40
#define ENABLE_IP_PORT_CHANGE_INT			0x80

#define DISABLE_TX_A_READY_INT	 			0xFE
#define DISABLE_RX_A_READY_INT				0xFD
#define DISABLE_DELTA_BREAK_A_INT			0xFB
#define DISABLE_COUNTER_READY_INT			0xF7
#define DISABLE_TX_B_READY_INT	       			0xEF
#define DISABLE_RX_B_READY_INT				0xDF
#define DISABLE_DELTA_BREAK_B_INT			0xBF
#define DISABLE_IP_PORT_CHANGE_INT			0x7F

/* Mode Register 1 */
#define CHAR_8B_NP_CE_RI_NRR				0x13				/* In Use */
#define CHAR_8B_OP_CE_RI_NRR				0x07
#define CHAR_8B_EP_CE_FI_NRR				0x43
#define CHAR_8B_OP_CE_FI_NRR				0x47

/* Mode Register 2 */
#define MODE_N_NTR_NTC_1SB				0x07				/* In Use */
#define MODE_N_NTR_NTC_2SB				0x0F
#define MODE_L_NTR_NTC_1SB				0x47
#define MODE_R_NTR_NTC_2SB	 			0xCF

/* Clock Select Register */
#define BAUD_16X_EXTERNAL				0xEE
#define BAUD_1X_EXTERNAL				0xFF
#define BAUD_4800_INT					0x99
#define BAUD_9600_INT					0xBB           /* In Use */

/* Command Register */
#define RESET_MR_PTR 				0x10			/* Causes MRn to point to MR1n */
#define RESET_RECEIVER	 			0x20
#define RESET_TRANSMITTER 			0x30
#define RESET_ERROR_STATUS			0x40
#define RESET_BRK_CNG_INT			0x50
#define START_BREAK					0x60
#define STOP_BREAK 					0x70
#define SET_RX_BRG_BIT				0x80
#define CLEAR_RX_BRG_BIT			0x90
#define SET_TX_BRG_BIT				0xA0
#define CLEAR_TX_BRG_BIT  			0xB0
#define SET_STANDBY_MODE			0xC0
#define SET_ACTIVE_MODE				0xD0

#define EN_TX_RX   	   				0x05
#define DIS_TX_RX  					0x0A

/* Status Register */
#define INVALID_CHAR			  	0x60				/* Parity Error &| Framing Error */
#define TX_EMPTY   					0x08
#define TX_RDY				     	0x04
#define RX_FIFO_FULL				0x02
#define RX_RDY				       	0x01

/* Auxillary Control Register */
#define CLOCK_SET0					0x80

#define KEY_PRESSED					0
#define LEFT_KEY					1
#define UP_KEY						2
#define RIGHT_KEY					3
#define DOWN_KEY					4
#define EXECUTE_KEY					5
#define NO_KEY_PRESSED				6


/*--------------------------------------------------------------------------
				Card Configuration
---------------------------------------------------------------------------*/
#define VFI_CARD					0X01
#define CHM_CARD					0X02
#define PAMP_CARD					0X04
#define DI_CARD						0X08
#define SU_CARD						0X10
#define HF_CARD						0X20
#define PSU_CARD					0X40

/*--------------------------------------------------------------------------
				Screen Number
---------------------------------------------------------------------------*/
#define ROW_1						 0
#define ROW_2						 1
#define COLUMN_1					 0

/*--------------------------------------------------------------------------
				Menu Mode
---------------------------------------------------------------------------*/

#define  OPEN_MENU_MODE   				1
#define  MAIN_MENU_MODE   				2
#define  STATUS_MENU_MODE   			3
#define  TEST_MENU_MODE   				4
#define  ALARM_MENU_MODE   				5
#define  LOCAL_LOOPBACK_MODE   			6
#define  REMOTE_LOOPBACK_MODE   		7
#define  OTHER_MODE   					18
/**************************************/
//ADDED IN Ver 1.4 FOR STATION_ID SCREENS
/*************************************/

#define  STATION1					8
#define  STATION2      				9
#define  STATION3					10
#define  STATION4					11
#define  STATION5					12
#define  STATION6					13
#define  STATION7					14
#define  STATION8					15
#define  STATION9					16
#define  STATION10					17

/*--------------------------------------------------------------------------
				Screen Definitions
---------------------------------------------------------------------------*/

#define  OPENING_SCR		    0							/*0*/
#define  MAIN_SCR		       	OPENING_SCR + 1							/*1*/ /*scr_&_agc_bars*/
#define  MAIN_MAX_SCR           MAIN_SCR + 3				/*4*/
#define  STATUS_SCR		       	MAIN_MAX_SCR + 1			/*5*/
#define  STATUS_MAX_SCR         STATUS_SCR + 14				/*19*/
#define  TEST_SCR		       	STATUS_MAX_SCR + 1			/*20*/
#define  TEST_MAX_SCR           TEST_SCR + 1				/*21*/
#define  LOCAL_SCR		       	TEST_MAX_SCR + 1			/*22*/
#define  LOCAL_MAX_SCR          LOCAL_SCR + 1				/*23*/

//added in Ver1.2                      
#define  REMOTE_SCR		    	LOCAL_MAX_SCR + 1			/*24*/
#define  REMOTE_MAX_SCR	    	REMOTE_SCR + 11  /*******************************/	/*35*/

//ADDED in ver 1.4 FOR STATION_ID SCREENS
  
#define  STATION1_SCR			REMOTE_MAX_SCR+1			/*36*/
#define  STATION1_MAX_SCR		REMOTE_MAX_SCR+2			/*37*/
#define  STATION2_SCR		    REMOTE_MAX_SCR+3
#define  STATION2_MAX_SCR		REMOTE_MAX_SCR+4
#define  STATION3_SCR		    REMOTE_MAX_SCR+5
#define  STATION3_MAX_SCR		REMOTE_MAX_SCR+6
#define  STATION4_SCR		    REMOTE_MAX_SCR+7
#define  STATION4_MAX_SCR		REMOTE_MAX_SCR+8
#define  STATION5_SCR		    REMOTE_MAX_SCR+9
#define  STATION5_MAX_SCR		REMOTE_MAX_SCR+10			/*45*/
#define  STATION6_SCR		    REMOTE_MAX_SCR+11
#define  STATION6_MAX_SCR		REMOTE_MAX_SCR+12
#define  STATION7_SCR		    REMOTE_MAX_SCR+13
#define  STATION7_MAX_SCR		REMOTE_MAX_SCR+14
#define  STATION8_SCR		    REMOTE_MAX_SCR+15
#define  STATION8_MAX_SCR		REMOTE_MAX_SCR+16
#define  STATION9_SCR		    REMOTE_MAX_SCR+17
#define  STATION9_MAX_SCR		REMOTE_MAX_SCR+18
#define  STATION10_SCR		    REMOTE_MAX_SCR+19
#define  STATION10_MAX_SCR		REMOTE_MAX_SCR+20			/*55*/

#define  OTHER_SCR		    	STATION10_MAX_SCR+1			/*56*/

//ends here
#define  OTHER_MAX_SCR          OTHER_SCR + 3				/*59*/
#define  CHECK_SCR		 		OTHER_MAX_SCR+1				/*60*/
#define  CHECK_MAX_SCR		 	CHECK_SCR+1					/*61*/
#define  ALARM_SCR              CHECK_MAX_SCR+1				/*62*/	
#define  ALARM_MAX_SCR          ALARM_SCR + 15				/*77*/

			
#define LCD_INIT_BYTE 					0x30
#define LCD_MODE_DEC 					0x05
#define LCD_MODE_INC 				 	0x06
#define LCD_MODE_INC_DISP_SHIFT	      	0x07
#define LCD_CLEAR_DISP 		       		0x01		
#define LCD_DISP_SHIFT					0x18		
#define LCD_8B_2L_10D					0x3C		
#define LCD_8B_2L_7D					0x38		
#define LCD_SET_DDRAM_START  				0x80		
#define LCD_CURSOR_ON_ROW1				0x80
#define LCD_CURSOR_ON_ROW2      	    		0xC0
//#define LCD_BUSY_FLAG_SET				0x80		
//#define LCD_OFF					0x08		
#define LCD_DISP_ON					0x0E		
#define LCD_DISP_ON_CRSR_BLINK				0x0F

//To be defined for generation of tones Ver1.2 
                                                
#define DTMF_INIT_BYTE 			    0x00	
#define DTMF_INIT1_BYTE	       		0x08	
#define DTMF_IRQ_DTMF	       		0x0C	
#define DTMF_NON_BURST				0x01	
#define DTMF_TONE_DIS				0x04
#define DTMF_TONE_ENA				0x05


#define DTMF_TX1_BYTE		0x00 //sending 0
#define DTMF_TX2_BYTE		0x0D //sending A
#define DTMF_TX3_BYTE		0x0E //sending B
#define DTMF_TX4_BYTE		0x0F ////sending c
#define DTMF_TX_BYTE1		0x0B //sending *
#define DTMF_TX_BYTE2		0x0C  //sending #


/**********************************************/
// added in Ver 1.4 for station id
/**********************************************/

#define DTMF_ST1_ID		0x01 //sending D
#define DTMF_ST2_ID		0x02
#define DTMF_ST3_ID		0x03
#define DTMF_ST4_ID		0x04
#define DTMF_ST5_ID		0x05
#define DTMF_ST6_ID		0x06
#define DTMF_ST7_ID		0x07
#define DTMF_ST8_ID		0x08
#define DTMF_ST9_ID		0x09
#define DTMF_ST10_ID		0x0A









