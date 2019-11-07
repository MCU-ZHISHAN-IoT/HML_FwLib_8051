/*****************************************************************************/
/** 
 * \file        conf.h
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       HML configurations, this file need to be modified by users
 * \note        
 * \version     v0.3
 * \ingroup     generic
******************************************************************************/

#ifndef ___HML_CONF_H___
#define ___HML_CONF_H___

/*****************************************************************************
 *                                macro                                      *
 *****************************************************************************/

/**
 *\brief: configure clock frequency of MCU
 */
#define __CONF_FRE_CLKIN     11059200L

/**
 *\brief: timer-2 function selection
 */
#define __CONF_HAVE_TIM2     1
#define __CONF_HAVE_T2MOD    1    /* register T2MOD is not a standard register for all 8052 MCUs */

/**
 *\brief: select HML module which take part in compilation
 */
#define __CONF_COMPILE_EXTI
#define __CONF_COMPILE_GPIO
#define __CONF_COMPILE_TIM
#define __CONF_COMPILE_TIM2
#define __CONF_COMPILE_UART
#define __CONF_COMPILE_UTIL

#endif
