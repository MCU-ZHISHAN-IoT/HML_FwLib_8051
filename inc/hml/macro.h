/*****************************************************************************/
/** 
 * \file        macro.h
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       HML macro define
 * \note        
 * \version     v0.2
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
 *                                macro                                      *
 *****************************************************************************/
#define WORD_MAX      0xFFFF

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
    #error HML run-time check: error: HML need define input clock frequency! (ERROR_CODE-0x01)
#endif

/**
 *\brief: timer-2 selection
 */
#if (__CONF_HAVE_TIM2 == 1)
    #define HAVE_TIM2
#endif
/**
 *\brief: register T2MOD selection
 */
#if (__CONF_HAVE_T2MOD == 1)
    #ifdef HAVE_TIM2
        #define HAVE_T2MOD
    #else
        #error HML run-time check: error: macro __CONF_HAVE_T2MOD based on macro __CONF_HAVE_TIM2 (ERROR_CODE-0x02)
    #endif
#endif

/**
 *\brief: HML compile selection check
 */
#if (defined __CONF_COMPILE_UART)
    #if (!defined __CONF_COMPILE_TIM)
        #error HML run-time check: UART module need extern support, please enable macro __CONF_COMPILE_TIM (ERROR_CODE-0x03)
    #endif
#endif

/**
 *\brief: SDCC version check
 */
#if (__SDCC_VERSION_MAJOR == 3)
    #if (__SDCC_VERSION_MINOR < 6)
        #error HML run-time check: HML requires SDCC v3.6.0 or later versions (ERROR_CODE-0x04)
    #endif
#else
    #if (__SDCC_VERSION_MAJOR < 3)
        #error HML run-time check: HML requires SDCC v3.6.0 or later versions (ERROR_CODE-0x05)
    #endif
#endif
 
#endif
