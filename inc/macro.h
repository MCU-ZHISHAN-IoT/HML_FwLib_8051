/*****************************************************************************/
/** 
 * \file        macro.h
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       HML macro define
 * \note        
 * \version     v0.1
 * \ingroup     generic
******************************************************************************/

#ifndef ___MACRO_H___
#define ___MACRO_H___

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "conf.h"

/*****************************************************************************
 *                             type define                                   *
 *****************************************************************************/
typedef unsigned char byte;
typedef unsigned char u8;
typedef unsigned int  u16;
typedef unsigned int  word;

/*****************************************************************************
 *                           enumeration type                                *
 *****************************************************************************/

/**
 *\brief: mark user action
 */
typedef enum
{
    DISABLE = 0x0,
    ENABLE  = !DISABLE
} Action;

/**
 *\brief: mark bit value/state
 */
typedef enum
{
    RESET = 0x0,
    SET   = !RESET
} FunctionalState;

/*****************************************************************************
 *                           run-time check                                  *
 *****************************************************************************/

/**
 *\brief: MCU clock configuration check
 */
#if (defined __CONF_FRE_CLKIN)
    #define MCU_FRE_CLK __CONF_FRE_CLKIN
#else
    #error HML run-time check: error: HML need define input clcok frequency! (ERROR_CODE-0x01)
#endif

/**
 *\brief: HML compile selection check
 */
#if (defined __CONF_COMPILE_UART) && (!defined __CONF_COMPILE_TIM)
    #error HML run-time check: UART module need extern support, please enable macro __CONF_COMPILE_TIM (ERROR_CODE-0x02)
#endif

/**
 *\brief: SDCC version check
 */
#if (__SDCC_VERSION_MAJOR == 3)
    #if (__SDCC_VERSION_MINOR < 6)
        #error HML run-time check: HML requires SDCC v3.6.0 or later versions (ERROR_CODE-0x03)
    #endif
#else
    #if (__SDCC_VERSION_MAJOR < 3)
        #error HML run-time check: HML requires SDCC v3.6.0 or later versions (ERROR_CODE-0x03)
    #endif
#endif
 
#endif
