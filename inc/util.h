/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:provides some public functions
 * @Required-complier:SDCC
 * @Support-mcu:Intel MCS-51 based microprocessors
 * @Version:V0
 */

#ifndef ___UTIL_H___
#define ___UTIL_H___

/* --- @header file --- */
#include <8051.h>
#include "intrasm.h"
#include "macro.h"

/* ---------- @function --------- */
void disableAllInterrupts(void);
void enableAllInterrupts(void);
void sleep(u16 t);

#endif
