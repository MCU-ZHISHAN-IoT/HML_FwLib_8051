/*****************************************************************************/
/** 
 * \file        conf.h
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       HML configurations, this file need to be modified by users
 * \note        
 * \version     v0.1
 * \ingroup     generic
******************************************************************************/

#ifndef ___CONF_H___
#define ___CONF_H___

/*****************************************************************************
 *                                macro                                      *
 *****************************************************************************/

/**
 *\brief: configure clock frequency of MCU
 */
#define __CONF_FRE_CLKIN 11059200L

/**
 *\brief: select HML module which take part in compilation
 */
#define __CONF_COMPILE_EXTI
#define __CONF_COMPILE_GPIO
#define __CONF_COMPILE_TIM
#define __CONF_COMPILE_UART
#define __CONF_COMPILE_UTIL

#endif
