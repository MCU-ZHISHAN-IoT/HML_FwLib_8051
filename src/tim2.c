/*****************************************************************************/
/** 
 * \file        tim2.c
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       operations for on-chip timer-2
 * \note        
 * \version     v0.3
 * \ingroup     TIM2
******************************************************************************/

#include "hml/tim2.h"

#ifdef HAVE_TIM2

#ifdef COMPILE_TIM2

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        2019/09/22
 * \brief       calculate initial value of counter/timer by specified time length
 * \param[in]   t: expected time length (unit: us)
 * \return      none
 * \ingroup     TIM2
 * \remarks     result is usually written into TH2/TL2
******************************************************************************/
uint16_t TIM2_calculateInitValue(uint16_t t)
{
    if((t*(MCU_FRE_CLK/1000000)/12) >= TIM2_MAXTICK)
    {
        return 0;
    }
    else
    {
        return (TIM2_MAXTICK + 1 - (t*(MCU_FRE_CLK/1000000)/12));
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        2019/09/26
 * \brief       configure timer-2
 * \param[in]   t2c: custom configure structure, look up details in header file
 * \return      none
 * \ingroup     TIM2
 * \remarks     
******************************************************************************/
void TIM2_config(TIM2_configTypeDef *t2c)
{
    TIM2_setFunction(t2c->function);
    TIM2_INT_cmd(t2c->interruptState);
    TIM2_INT_setPriority(t2c->interruptPriority);
    TIM2_setMode(t2c->mode);
    TIM2_setValue(t2c->value);
    TIM2_setReloadValue(t2c->reloadValue);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        2019/09/21
 * \brief       clear interrupt flag of TIM2
 * \param[in]   
 * \return      none
 * \ingroup     TIM2
 * \remarks     timer-2 overflow flag set by a timer-2 overflow and must be cleared
                software. TF2 will not be set when after RCLK=1 or TCLK=1
******************************************************************************/
void TIM2_clearFlag(void)
{
    TF2 = RESET;
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        2019/09/21
 * \brief       enable or disable timer-2
 * \param[in]   a: expected state
 * \return      none
 * \ingroup     TIM2
 * \remarks     
******************************************************************************/
void TIM2_cmd(Action a)
{
    TR2 = a;
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        2019/09/22
 * \brief       get capture result of timer-2
 * \param[in]   
 * \return      16-bit result form RCAP2H/RCAP2L
 * \ingroup     TIM2
 * \remarks     this function only can be called validly under capture mode
******************************************************************************/
uint16_t TIM2_getCaptureValue(void)
{
    return (uint16_t)((RCAP2H << 0x8) | RCAP2L);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        2019/09/22
 * \brief       get external flag from EXF2 which indicte state of pin T2EX
 * \param[in]   
 * \return      external flag
 * \ingroup     TIM2
 * \remarks     
******************************************************************************/
bool TIM2_isExternalEvent(void)
{
    return (bool)EXF2;
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        2019/09/21
 * \brief       configure function(timer or counter) of timer-2
 * \param[in]   f: expected function
 * \return      none
 * \ingroup     TIM2
 * \remarks     
******************************************************************************/
void TIM2_setFunction(TIM2_function f)
{
    C_T2 = (FunctionalState)f;
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        2020/10/13
 * \brief       set work mode of timer-2
 * \param[in]   mode: expected work mode
 * \return      none
 * \ingroup     TIM2
 * \remarks     
******************************************************************************/
void TIM2_setMode(TIM2_mode mode)
{
    T2CON = (T2CON & 0xCE) | mode;
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        2019/09/22
 * \brief       set 16-bit reload value of timer-2
 * \param[in]   val: expected 16-bit value
 * \return      none
 * \ingroup     TIM2
 * \remarks     the parameter value will be written into register RCAP2H/RCAP2L
******************************************************************************/
void TIM2_setReloadValue(uint16_t val)
{
    RCAP2H = (byte)(val >> 0x8);
    RCAP2L = val;
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        2019/09/22
 * \brief       set value of THx/TLx register
 * \param[in]   val: expected value(range: 0x0000~0xFFFF)
 * \return      none
 * \ingroup     TIM2
 * \remarks     
******************************************************************************/
void TIM2_setValue(uint16_t val)
{
    TH2 = (byte)(val >> 0x8);
    TL2 = val;
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        2019/09/21
 * \brief       enable or disable baud clock source
 * \param[in]   t: UART receive or transmit clock
 * \param[in]   a: expected action
 * \return      none
 * \ingroup     TIM2
 * \remarks     this function is usually used to take place baud clock source
                of UART from timer-1
******************************************************************************/
void TIM2_BAUD_cmd(TIM2_baudClock t,Action a)
{
    if (t == TIM2_baudClock_receive)
    {
        RCLK = (FunctionalState)a;
    }
    else if (t == TIM2_baudClock_transmit)
    {
        TCLK = (FunctionalState)a;
    }
    else
    {
        /* nothing to be done */
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        2019/09/26
 * \brief       enable of disable interrupt switch of timer-2
 * \param[in]   a: expected action
 * \return      none
 * \ingroup     TIM2
 * \remarks     
******************************************************************************/
void TIM2_INT_cmd(Action a)
{
    ET2 = (FunctionalState)a;
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        2019/09/26
 * \brief       configure interrupt priority class of timer-2
 * \param[in]   a: expected action(ENABLE: high priority class; DISABLE: low priority class)
 * \return      none
 * \ingroup     TIM2
 * \remarks     
******************************************************************************/
void TIM2_INT_setPriority(Action a)
{
    PT2 = (FunctionalState)a;
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        2019/09/22
 * \brief       enable or disable T2EX function of timer-2
 * \param[in]   a: expected action
 * \return      none
 * \ingroup     TIM2
 * \remarks     when enable, allows a capture or reload to occur as a result of a
 *              negative transition on T2EX if timer-2 is not being used to clock
 *              the serial port. EXEN2 = 0 causes timer-2 to ignore events at 
 *              T2EX
******************************************************************************/
void TIM2_T2EX_cmd(Action a)
{
    EXEN2 = a;
}

#if (defined HAVE_T2MOD)

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        2019/09/23
 * \brief       allow timer-2 to choose up or down counter via pin T2EX
 * \param[in]   a: expected action
 * \return      none
 * \ingroup     TIM2
 * \remarks     (1) this function requires macro HAVE_T2MOD (enabled by macro 
 *              __CONF_HAVE_T2MOD)
 *              (2) only for auto-reload mode
******************************************************************************/
void TIM2_DCOUNT_cmd(Action a)
{
    CONFB(T2MOD, BIT_NUM_DCEN, (FunctionalState)a);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        2019/09/23
 * \brief       ebale or disable clock output from timer-2
 * \param[in]   a: expected action
 * \return      none
 * \ingroup     TIM2
 * \remarks     
******************************************************************************/
void TIM2_OUT_cmd(Action a)
{
    CONFB(T2MOD, BIT_NUM_T2OE, (FunctionalState)a);
}

#endif

#else
    #warning nothing to be done, you can remove the .c file from your project if it does not need to compile.
#endif

#endif
