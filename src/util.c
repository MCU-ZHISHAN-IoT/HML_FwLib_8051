/*****************************************************************************/
/** 
 * \file        util.c
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       public operations
 * \note        
 * \version     v0.0
 * \ingroup     UTIL
******************************************************************************/

#include "util.h"

#ifdef __CONF_COMPILE_UTIL

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       disable MCU interrupt switch
 * \param[in]   
 * \return      none
 * \ingroup     UTIL
 * \remarks     
******************************************************************************/
void disableAllInterrupts(void)
{
    EA = RESET;
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       enable MCU interrupt switch
 * \param[in]   
 * \return      none
 * \ingroup     UTIL
 * \remarks     
******************************************************************************/
void enableAllInterrupts(void)
{
    EA = SET;
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       software delay according to frequency of crystal oscillator
 * \param[in]   t: how many one ms you want to delay
 * \return      none
 * \ingroup     UTIL
 * \remarks     
******************************************************************************/
void sleep(u16 t)
{
    u8 i = 0x00;
    
    #if ( MCU_FRE_CLK == 11059200L )

    while(t--)
    {
        i = 110;
        while(i--);
    }
        
    #elif ( MCU_FRE_CLK == 12000000L )

    while(t--)
    {
        i = 120;
        while(i--);
    }

    #else

    /* users can add other situations here */

    #endif
}

#endif
