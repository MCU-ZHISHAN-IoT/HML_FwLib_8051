/*****************************************************************************/
/** 
 * \file      tim2_bleekLed.c
 * \author    Weilun Fong | wlf@zhishan-iot.tk
 * \date      2019/09/28
 * \brief     a example which shows bleek LED per one second by timer-2
 * \note      
 * \version   v0.3
 * \ingroup   example
 * \remarks   test-board: TS51-V2.0; test-MCU: STC89C52RC
******************************************************************************/

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml/hml.h"

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        2019/09/28
 * \brief       initial MCU
 * \param[in]   
 * \return      none
 * \ingroup     
 * \remarks     
******************************************************************************/
void sys_init(void)
{
    TIM2_configTypeDef t2c;

    t2c.function          = TIM2_function_tim;
    t2c.interruptState    = ENABLE;
    t2c.interruptPriority = DISABLE;
    t2c.mode              = TIM2_mode_0;
    t2c.value             = 0x0000;
    t2c.reloadValue       = TIM2_calculateInitValue(50000);

    TIM2_config(&t2c);
    TIM2_cmd(ENABLE);
    enableAllInterrupts();
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        2019/09/28
 * \brief       main function
 * \param[in]   
 * \return      none
 * \ingroup     
 * \remarks     
******************************************************************************/
void main(void)
{    
    sys_init();
    while(true);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        2019/09/28
 * \brief       main function
 * \param[in]   
 * \return      none
 * \ingroup     
 * \remarks     toggle state of target LED
******************************************************************************/
void tim2_isr(void) __interrupt TF2_VECTOR
{
    static unsigned char i = 0;

    TIM2_INT_cmd(DISABLE);

    i++;
    TIM2_clearFlag();

    if (i == 20)
    {
        i = 0;
        P1 = ~P1;  /* a 8-bit LED group is connected to P1 on board */
    }

    TIM2_INT_cmd(ENABLE);
}
