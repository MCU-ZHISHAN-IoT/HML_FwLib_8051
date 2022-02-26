/*****************************************************************************/
/** 
 * \file        util.h
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       public operations
 * \note        
 * \version     v0.3
 * \ingroup     UTIL
******************************************************************************/

#ifndef ___HML_UTIL_H___
#define ___HML_UTIL_H___

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml/macro.h"
#include "hml/types.h"
#include <8052.h>

/*****************************************************************************
 *                          function declare                                 *
 *****************************************************************************/
void disableAllInterrupts(void);
void enableAllInterrupts(void);
void sleep(uint16_t t);

#endif
