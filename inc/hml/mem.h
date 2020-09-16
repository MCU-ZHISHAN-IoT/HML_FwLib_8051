/*****************************************************************************/
/** 
 * \file        mem.h
 * \author      Weillun Fong | wlf@zhishan-iot.tk
 * \brief       operations for memory zone of MCU
 * \note        allow you to directly access the different memory areas of the 8051.
 * \version     v0.3
 * \ingroup     MEM
******************************************************************************/

#ifndef ___HML_MEM_H___
#define ___HML_MEM_H___

/*****************************************************************************
 *                                macro                                      *
 *****************************************************************************/

/**
 * \brief for direct access
 */
#define __CBYTE ((unsigned char volatile __code  *) 0)
#define __DBYTE ((unsigned char volatile __data  *) 0)
#define __PBYTE ((unsigned char volatile __pdata *) 0)
#define __XBYTE ((unsigned char volatile __xdata *) 0)

#define __CWORD ((unsigned int volatile __code  *) 0)
#define __DWORD ((unsigned int volatile __data  *) 0)
#define __PWORD ((unsigned int volatile __pdata *) 0)
#define __XWORD ((unsigned int volatile __xdata *) 0)

#endif
