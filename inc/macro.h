/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:includes some important macro definitions
 * @Required-compiler:SDCC
 * @Support-mcu:Intel MCS-51 based microprocessors
 * @Version:V0
 */

#ifndef ___MACRO_H___
#define ___MACRO_H___

/* --- @type define --- */
typedef unsigned char byte;
typedef unsigned char u8;
typedef unsigned int  u16;
typedef unsigned int  word;

/* --- @enum type --- */
/* mark user action */
typedef enum
{
	DISABLE = 0x0,
	ENABLE  = !DISABLE
} Action;

/* mark bit value/state */
typedef enum
{
	RESET = 0x0,
	SET   = !RESET
} FunctionalState;

/* ---------- NEED TO CONFIG MANUALLY !!! ---------- */

/* specify the frequency of crystal oscillator */
#define _FRE_OSC_ 11059200L
// #define _FRE_OSC_ 12000000L

/* select the part you need */
#define ___COMPILE_EXTI___
#define ___COMPILE_GPIO___
#define ___COMPILE_TIM___
#define ___COMPILE_UART___
#define ___COMPILE_UTIL___

/* ---------- END OF MANUAL CONFIGURATON PART --------- */

/* --------- @run-time check ------- */

#ifndef _FRE_OSC_
	#error HML run-time check:the firmware library need define extern clcok frequency!(ERROR_CODE-0x01)
#endif

#if (defined ___COMPILE_UART___) && (!defined ___COMPILE_TIM___)
	#error HML run-time check: UART part need extern support, please enable macro ___COMPILE_TIM___ (ERROR_CODE-0x02)
#endif

#endif
