/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:includes some definitions for operating timer resource
 * @Required-complier:SDCC
 * @Support-mcu:Intel MCS-51 based microprocessors
 * @Version:V0
 */

#ifndef ___TIM_H___
#define ___TIM_H___

/* ----- @header file ----- */
#include <8051.h>
#include <stdbool.h>
#include "macro.h"

/* ----- @enumeration type ----- */
/* mark timer */
typedef enum
{
    PERIPH_TIM_0 = 0x0,
    PERIPH_TIM_1 = 0x1
} PERIPH_TIM;

/* mark work mode */
typedef enum
{
    TIM_mode_0 = 0x0,   /* 13-bit timer/counter */
    TIM_mode_1 = 0x1,   /* 16-bit timer/counter */
    TIM_mode_2 = 0x2,   /* 8-bit auto reload */
    TIM_mode_3 = 0x3    /* only for timer-0 */
} TIM_mode;

/* mark counter mode and timer mode */
typedef enum
{
    TIM_function_cnt = 0x1, /* counter mode */
    TIM_function_tim = 0x0  /* timer mode */
} TIM_function;

/* ----- @structure define ----- */
/* special structure for congratulating TIM module */
typedef struct
{
    TIM_function function;
    Action       interruptState;
    Action       interruptPriority;
    TIM_mode     mode;
    unsigned int value;
} TIM_configTypeDef;

/* ----- @function ----- */
void TIM_cmd(PERIPH_TIM tim,Action a);
void TIM_config(PERIPH_TIM tim,TIM_configTypeDef *tc);
unsigned int TIM_getValue(PERIPH_TIM tim);
bool TIM_isOverflow(PERIPH_TIM tim);
void TIM_setFunction(PERIPH_TIM tim,TIM_function f);
void TIM_setMode(PERIPH_TIM tim,TIM_mode m);
void TIM_setValue(PERIPH_TIM tim,word val);
void TIM_INT_cmd(PERIPH_TIM tim,Action a);
void TIM_INT_setPriority(PERIPH_TIM tim,Action a);

#endif
