/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:provides some public functions
 * @Required-complier:SDCC
 * @Support-mcu:Intel MCS-51 based microprocessors
 * @Version:V0
 */


#include "util.h"

#ifdef ___COMPILE_UTIL___

/*
 * @Protype:void disableAllInterrupts(void)
 * @Parameter:
 * @Ret-val:
 * @Note:disable all interrupts
 */
void disableAllInterrupts(void)
{
	EA = RESET;
}

/*
 * @Protype:void enableAllInterrupts(void)
 * @Parameter:
 * @Ret-val:
 * @Note:enable total switch of intterupts
 */
void enableAllInterrupts(void)
{
	EA = SET;
}

/*
 * @Protype:void sleep(u16 t)
 * @Parameter:(1)how many ms users expected
 * @Ret-val:
 * @Note:software delay according to frequency of crystal oscillator
 */
void sleep(u16 t)
{
	u8 i = 0x00;
	
	#if ( _FRE_OSC_ == 11059200L )

		while(t--)
		{
			i = 110;
			while(i--);
		}
		
	#elif ( _FRE_OSC_ == 12000000L )

		while(t--)
		{
			i = 120;
			while(i--);
		}
		
	#else
		
	/* users can add other situations here */
	
	#endif
}

#endif
