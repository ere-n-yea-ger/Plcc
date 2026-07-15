/*###########################################################################
Project				:	PLCC Supy
Filename				:	DECLARE.H
Previous Version	:  Not applicable
New Version			:	0.1
Modified  on		:	19-03-1999
Last Modified by	:	G.S.Ubhi
Editor Tab Size  	:	3
Comments				:
############################################################################*/
/*===========================================================================
								Revision History
								================


===========================================================================*/

/*--------------------------------------------------------------------------
								Function.C
--------------------------------------------------------------------------*/
unsigned char SelectionCursorPosition(unsigned char Row, unsigned char Column);
unsigned char ShowScrollKey(unsigned char Key, unsigned char Row, unsigned char Column);
void GetAlarms(void);
void Delay(unsigned char Count);
void Wait40(void);
void Processloopback(void);
unsigned char Switchstatus(void);
/******************************************/
void GetADCInputs (void);
void GetAGCInputs (void);	// added in ver 1.5
void GetPowerOP (void);         // added in ver 1.5
void ScrBlank(int);		// added in ver 1.5
int GetBars(float);		// added in ver 1.5
void DispCh1AGC(void); //29-11-2k ajay
void DispCh2AGC(void); //29-11-2k ajay

/***************************************************/
void Loopbackdisable (void);
void Getalarms(void);
void Getswitchstatus(void);
void Remoteloop(unsigned char,unsigned char);
void DTMFRxprocess(void);
void DispAGCGraph(int,int,int);
void DispPAMPGraph(int);


/*--------------------------------------------------------------------------
								Mmi.C
--------------------------------------------------------------------------*/
void ScreenHandler(void);
void reset_lcd_display();	//reset_mtu
unsigned char KeyBoardScan(void);
void display(char string[2][20]);
void StringOut(unsigned char *, unsigned char, unsigned int);
unsigned char SelectionCursorPosition(unsigned char , unsigned char );
void Delay(unsigned char);

/*--------------------------------------------------------------------------
								Bios.C
--------------------------------------------------------------------------*/
unsigned char BiosCall(unsigned char *ParamStr, unsigned char *RetParamStr);

/*--------------------------------------------------------------------------
								Initlise.C
--------------------------------------------------------------------------*/
void InitDbase(void);
void InitController(void);
void InitLCD(void);
void InitDUART(void);
void InitDTMF(void);



/*##################### End Of File "DECLARE.H" ###########################*/



