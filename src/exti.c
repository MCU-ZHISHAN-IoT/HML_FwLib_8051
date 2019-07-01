/*****************************************************************************/
/** 
 * \file        exti.c
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       operation for on-chip EXTI module
 * \note        
 * \version     v0.1
 * \ingroup     EXTI
******************************************************************************/

#include "exti.h"

#ifdef __CONF_COMPILE_EXTI

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       configure function for EXTI module
 * \param[in]   exti: target EXTI module
 * \return      ec  : the pointer of configuration structure which includes all configuration information
 * \ingroup     EXTI
 * \remarks     
******************************************************************************/
void EXTI_config(PERIPH_EXTI exti,EXTI_configTypeDef *ec)
{
    EXTI_setMode(exti,ec->mode);
    EXTI_setPriority(exti,ec->priority);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       disable or enable target EXTI module
 * \param[in]   exti: target EXTI module
 * \return      a   : expected status
 * \ingroup     EXTI
 * \remarks     
******************************************************************************/
void EXTI_cmd(PERIPH_EXTI exti,Action a)
{
    switch(exti)
    {
        case PERIPH_EXTI_0: EX0 = a; break;
        case PERIPH_EXTI_1: EX1 = a; break;
        default: break;
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       configure work mode of target EXTI module
 * \param[in]   exti: target EXTI module
 * \return      mod : expected work mode
 * \ingroup     EXTI
 * \remarks     
******************************************************************************/
void EXTI_setMode(PERIPH_EXTI exti,EXTI_mode mod)
{
    switch(exti)
    {
        case PERIPH_EXTI_0: IT0 = mod; break;
        case PERIPH_EXTI_1: IT1 = mod; break;
        default: break;
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       configure priority class of target EXTI module
 * \param[in]   exti: target EXTI module
 * \return      a   : ENABLE(high priority class) or DISABLE(low priority class)
 * \ingroup     EXTI
 * \remarks     
******************************************************************************/
void EXTI_setPriority(PERIPH_EXTI exti,Action a)
{
    switch(exti)
    {
        case PERIPH_EXTI_0: PX0 = a; break;
        case PERIPH_EXTI_1: PX1 = a; break;
        default: break;
    }
}

#endif
