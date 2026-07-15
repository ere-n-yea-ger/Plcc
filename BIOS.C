
/*###########################################################################
Project			:	PLCC Supv
Filename		:	BIOS.C
Previous Version	:  Not Applicable
New Version		:	0.1
Modified  on		:	12-04-1999
Last Modified by	:	G.S.Ubhi
Editor Tab Size  	:	3
Comments		:

############################################################################*/
#define public extern
#include <reg51.h>
#include "def.h"
#include "database.h"
#include "declare.h"
#include "addr.h"
 
extern unsigned char xdata  LCD_CMD_ADDR	;
extern unsigned char xdata  LCD_DATA_ADDR 	;  

unsigned char BiosCall(unsigned char *ParamStr, unsigned char *RetParamStr)
{
	unsigned char i, ErrorCode;
	unsigned char LeftKey, UpKey, RightKey, DownKey, ExecuteKey, KeyPad;
	unsigned char NoOfKeysPressed;
    

	switch(ParamStr[0])
	{


	 case DisplayChar:
		/*------------------------------------------------------------------
			ParamStr[1] = 1 A A A A A A A

			AAAAAAA -> DDRAM Address Corresponds to Cursor Address

			ParamStr[2] = ASCII Character to be displayed.

		------------------------------------------------------------------*/
	        LCD_CMD_ADDR = ParamStr[1];
        	Wait40();
		LCD_DATA_ADDR = ParamStr[2];
		Wait40();
		RetParamStr[0] = 0;
		break;

	case SetCursorPosition:
		/*------------------------------------------------------------------
			ParamStr[1] = 1 A 0 A A A A A
			AAAAAA -> Cursor Address (0x00 - 0x0F) & (0x40 - 0x4F)

		------------------------------------------------------------------*/
		LCD_CMD_ADDR = ParamStr[1];
		Wait40();
		RetParamStr[0] = 0;
		break;

	case ClearDisplay:
		LCD_CMD_ADDR = LCD_CLEAR_DISP;
		Delay(2);
		RetParamStr[0] = 0;
		break;

	case ChangeDisplayMode:
		
  		/*------------------------------------------------------------------
			ParamStr[1] = 0 0 0 1 S/C R/L 0 0

			S/C = 1: Display Shift
			S/C = 0: Cursor Movement
			R/L = 1: Shift to Right
			R/L = 0: Shift to Left
		------------------------------------------------------------------*/
		LCD_CMD_ADDR = ParamStr[1];
		Wait40();				/*Wait for 40 micro sec */
		RetParamStr[0] = 0;
		break;

	case GetKey:

		KeyPad = INPORT6_ADD;
		KeyPad = (0xFF ^ KeyPad) & 0x1F;

		DownKey        	= 	 KeyPad & 0x01;
		RightKey      	= 	(KeyPad >> 1) & 0x01;
		UpKey        	= 	(KeyPad >> 2) & 0x01;
		LeftKey        	= 	(KeyPad >> 3) & 0x01;
		ExecuteKey      = 	(KeyPad >> 4) & 0x01;


		/* Check if any Key is pressed*/
		if(KeyPad)
		{
			/* Check that only one Key is pressed at a time*/
			for(NoOfKeysPressed = 0, i = 0; i < 5; ++i)
			{
				if((KeyPad >> i) & 0x01)
					++NoOfKeysPressed;
			}

			if(NoOfKeysPressed > 1)
			{
				RetParamStr[0] = 1;
				RetParamStr[1] = NO_KEY_PRESSED;
			}
			else
			{
				RetParamStr[0] = 2;
				RetParamStr[1] = KEY_PRESSED;

				if(LeftKey)
					RetParamStr[2] = LEFT_KEY;
				if(UpKey)
					RetParamStr[2] = UP_KEY;
				if(RightKey)
					RetParamStr[2] = RIGHT_KEY;
				if(DownKey)
					RetParamStr[2] = DOWN_KEY;
				if(ExecuteKey)
					RetParamStr[2] = EXECUTE_KEY;
			}
		}
		else
		{
			RetParamStr[0] = 1;
			RetParamStr[1] = NO_KEY_PRESSED;
		}
		break;

	default:
	break;
	}
	ErrorCode = OK;
	return(ErrorCode);
}


/*##################### End Of File "BIOS.C" ###########################*/



