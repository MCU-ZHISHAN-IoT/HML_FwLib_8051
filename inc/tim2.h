/*****************************************************************************/
/** 
 * \file        tim2.h
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       operations for on-chip timer-2
 * \note        
 * \version     v0.2
 * \ingroup     TIM2
******************************************************************************/

#ifndef ___TIM2_H___
#define ___TIM2_H___

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include <8052.h>
#include <stdbool.h>
/*****************************************************************************/
#include "bit.h"
#include "util.h"

/*****************************************************************************
 *                                macro                                      *
 *****************************************************************************/

/**
 *\brief: mark max value of counter
 */
#define TIM2_MAXTICK    WORD_MAX

/**
 *\brief: define register T2MOD and bits inside
 */
#if (defined HAVE_T2MOD)

__sfr __at (0xC9) T2MOD;

#define BIT_NUM_DCEN    0    /* down counter enable */
#define BIT_NUM_T2OE    1    /* timer-2 output enable */

#define DCEN            BIT_MASK(BIT_NUM_DCEN)
#define T2OE            BIT_MASK(BIT_NUM_T2OE)

#endif

/**
 *\brief: interrupt vector
 */
#define TF2_VECTOR      5    /* 0x2B timer-2 */

/*****************************************************************************
 *                           enumeration type                                *
 *****************************************************************************/

/**
 *\brief: mark baud clock type
 */
typedef enum
{
    TIM2_baudClock_receive  = 0x0,   /* receive clock */
    TIM2_baudClock_transmit = 0x1    /* transmit clock */
} TIM2_baudClock;

/**
 *\brief: mark work function(role) of timer-2
 */
typedef enum
{
    TIM2_function_cnt = 0x1, /* counter mode */
    TIM2_function_tim = 0x0  /* timer mode */
} TIM2_function;

/**
 *\brief: mark work mode
 */
typedef enum
{
    TIM2_mode_0 = 0x00,      /* 16-bit auto-reload */
    TIM2_mode_1 = 0x01,      /* 16-bit capture */
    TIM2_mode_2 = 0x30       /* baud rate generator */
} TIM2_mode;

/*****************************************************************************
 *                           structure define                                *
 *****************************************************************************/

/**
 *\brief: structure for congratulating TIM2 module
 */
typedef struct
{
    TIM2_function function;
    Action        interruptState;
    Action        interruptPriority;
    TIM2_mode     mode;
    unsigned int  value;
    unsigned int  reloadValue;    /* only for auto-reload mode */
} TIM2_configTypeDef;

/*****************************************************************************
 *                          function declare                                 *
 *****************************************************************************/
unsigned int TIM2_calculateInitValue(unsigned int t);
void TIM2_config(TIM2_configTypeDef *t2c);
void TIM2_clearFlag(void);
void TIM2_cmd(Action a);
unsigned int TIM2_getCaptureValue(void);
bool TIM2_isExternalEvent(void);
void TIM2_setFunction(TIM2_function f);
void TIM2_setMode(TIM2_mode m);
void TIM2_setReloadValue(unsigned int val);
void TIM2_setValue(unsigned int val);
void TIM2_BAUD_cmd(TIM2_baudClock t,Action a);
void TIM2_INT_cmd(Action a);
void TIM2_INT_setPriority(Action a);
void TIM2_T2EX_cmd(Action a);

#if (defined HAVE_T2MOD)
void TIM2_DCOUNT_cmd(Action a);
void TIM2_OUT_cmd(Action a);
#endif

#endif
