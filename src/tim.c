/*****************************************************************************/
/** 
 * \file        tim.c
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       operations for on-chip timer
 * \note        
 * \version     v0.2
 * \ingroup     TIM
******************************************************************************/

#include "tim.h"

#ifdef __CONF_COMPILE_TIM

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       enable or disable target timer
 * \param[in]   tim: target timer
 * \param[in]   a  : expected action
 * \return      none
 * \ingroup     TIM
 * \remarks     
******************************************************************************/
void TIM_cmd(PERIPH_TIM tim,Action a)
{
    switch(tim)
    {
        case PERIPH_TIM_0: TR0 = a; break;
        case PERIPH_TIM_1: TR1 = a; break;
        default: break;
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       configure target timer
 * \param[in]   tim: target timer
 * \param[in]   tc : custom configure structure, look up details in header file
 * \return      none
 * \ingroup     TIM
 * \remarks     
******************************************************************************/
void TIM_config(PERIPH_TIM tim,TIM_configTypeDef *tc)
{
    TIM_setFunction(tim,tc->function);
    TIM_setMode(tim,tc->mode);
    TIM_setValue(tim,tc->value);
    TIM_INT_cmd(tim,tc->interruptState);
    TIM_INT_setPriority(tim,tc->interruptPriority);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       get value of counter inside target timer
 * \param[in]   tim: target timer
 * \return      value which stored in counter
 * \ingroup     TIM
 * \remarks     
******************************************************************************/
unsigned int TIM_getValue(PERIPH_TIM tim)
{
    switch(tim)
    {
        case PERIPH_TIM_0: return ((TH0 << 0x08) | TL0);
        case PERIPH_TIM_1: return ((TH1 << 0x08) | TL1);
        default: return 0;
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       check target timer is whether in overflow state or not
 * \param[in]   tim: target timer
 * \return      true(be in overflow state) or false
 * \ingroup     TIM
 * \remarks     
******************************************************************************/
bool TIM_isOverflow(PERIPH_TIM tim)
{
    switch(tim)
    {
        case PERIPH_TIM_0: return (bool)TF0;
        case PERIPH_TIM_1: return (bool)TF1;
        default: return false;
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       configure target timer module as counter mode or timer mode
 * \param[in]   tim: target timer
 * \param[in]   f  : expected function
 * \return      none
 * \ingroup     TIM
 * \remarks     
******************************************************************************/
void TIM_setFunction(PERIPH_TIM tim,TIM_function f)
{
    switch(tim)
    {
        case PERIPH_TIM_0:CONFB(TMOD,BIT_NUM_T0_CT,f); break;
        case PERIPH_TIM_1:CONFB(TMOD,BIT_NUM_T1_CT,f); break;
        default: break;
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       configure work mode of target timer
 * \param[in]   tim: target timer
 * \param[in]   m  : expected work mode
 * \return      none
 * \ingroup     TIM
 * \remarks     
******************************************************************************/
void TIM_setMode(PERIPH_TIM tim,TIM_mode m)
{
    switch(tim)
    {
        case PERIPH_TIM_0: TMOD = (TMOD & 0xFC) | m; break;
        case PERIPH_TIM_1: TMOD = (TMOD & 0xCF) | (m << 0x04); break;
        default: break;
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       set value of counter register of target timer
 * \param[in]   tim: target timer
 * \param[in]   val: the range of value is 0x0000~0xFFFF
 * \return      none
 * \ingroup     TIM
 * \remarks     
******************************************************************************/
void TIM_setValue(PERIPH_TIM tim,word val)
{
    switch(tim)
    {
        case PERIPH_TIM_0:
        {
            TH0 = (u8)((val >> 0x8) & 0x00FF);
            TL0 = (u8)(val & 0x00FF);
        } break;
        case PERIPH_TIM_1:
        {
            TH1 = (u8)((val >> 0x8) & 0x00FF);
            TL1 = (u8)(val & 0x00FF);
        } break;
        default: break;
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       enable of disable interrupt switch of target timer
 * \param[in]   tim: target timer
 * \param[in]   a  : expected action
 * \return      none
 * \ingroup     TIM
 * \remarks     
******************************************************************************/
void TIM_INT_cmd(PERIPH_TIM tim,Action a)
{
    switch(tim)
    {
        case PERIPH_TIM_0: ET0 = (FunctionalState)a; break;
        case PERIPH_TIM_1: ET1 = (FunctionalState)a; break;
        default: break;
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       configure interrupt priority class of target timer
 * \param[in]   tim: target timer
 * \param[in]   a  : expected action(ENABLE: high priority class; DISABLE: low priority class)
 * \return      none
 * \ingroup     TIM
 * \remarks     
******************************************************************************/
void TIM_INT_setPriority(PERIPH_TIM tim,Action a)
{
    switch(tim)
    {
        case PERIPH_TIM_0: PT0 = (FunctionalState)a; break;
        case PERIPH_TIM_1: PT1 = (FunctionalState)a; break;
        default: break;
    }
}

#else
    #warning Nothing to be done... User should remove .c file which is disabled by compile control macro from current directory.
#endif
