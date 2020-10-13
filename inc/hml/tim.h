/*****************************************************************************/
/** 
 * \file        tim.h
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       operations for on-chip timer
 * \note        
 * \version     v0.3
 * \ingroup     TIM
******************************************************************************/

#ifndef ___HML_TIM_H___
#define ___HML_TIM_H___

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include <8052.h>
/*****************************************************************************/
#include "hml/bit.h"
#include "hml/macro.h"
#include "hml/types.h"

/*****************************************************************************
 *                                macro                                      *
 *****************************************************************************/

/**
 * \brief mark TMOD bits for bit operation
 */
#define BIT_NUM_T0_M0     0
#define BIT_NUM_T0_M1     1
#define BIT_NUM_T0_CT     2
#define BIT_NUM_T0_GATE   3
#define BIT_NUM_T1_M0     4
#define BIT_NUM_T1_M1     5
#define BIT_NUM_T1_CT     6
#define BIT_NUM_T1_GATE   7

/*****************************************************************************
 *                           enumeration type                                *
 *****************************************************************************/

/**
 * \brief mark timer
 */
typedef enum
{
    PERIPH_TIM_0 = 0x0,
    PERIPH_TIM_1 = 0x1
} PERIPH_TIM;

/**
 * \brief mark work mode
 */
typedef enum
{
    TIM_mode_0 = 0x0,   /* 13-bit timer/counter */
    TIM_mode_1 = 0x1,   /* 16-bit timer/counter */
    TIM_mode_2 = 0x2,   /* 8-bit auto reload */
    TIM_mode_3 = 0x3    /* only for timer-0 */
} TIM_mode;

/**
 * \brief mark counter mode and timer mode
 */
typedef enum
{
    TIM_function_cnt = 0x1, /* counter mode */
    TIM_function_tim = 0x0  /* timer mode */
} TIM_function;

/*****************************************************************************
 *                           structure define                                *
 *****************************************************************************/

/**
 * \brief structure for congratulating TIM module
 */
typedef struct
{
    TIM_function function;
    Action       interruptState;
    Action       interruptPriority;
    TIM_mode     mode;
    uint16_t     value;
} TIM_configTypeDef;

/*****************************************************************************
 *                          function declare                                 *
 *****************************************************************************/
void TIM_cmd(PERIPH_TIM tim, Action a);
void TIM_config(PERIPH_TIM tim, TIM_configTypeDef *tc);
uint16_t TIM_getValue(PERIPH_TIM tim);
bool TIM_isOverflow(PERIPH_TIM tim);
void TIM_setFunction(PERIPH_TIM tim, TIM_function f);
void TIM_setMode(PERIPH_TIM tim, TIM_mode mode);
void TIM_setValue(PERIPH_TIM tim, uint16_t val);
void TIM_INT_cmd(PERIPH_TIM tim, Action a);
void TIM_INT_setPriority(PERIPH_TIM tim, Action a);

#endif
