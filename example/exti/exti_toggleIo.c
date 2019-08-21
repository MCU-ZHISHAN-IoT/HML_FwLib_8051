/*****************************************************************************/
/** 
 * \file        exti_toggleIo.c
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       a example which shows how to use HML_FwLib_8051 to toggle P10 state when EXTI1 is trigged
 * \note        
 * \test-board  TS51-V2.0
 * \test-mcu    STC89C52RC
 * \version     v0.1
 * \ingroup     example
******************************************************************************/

#include "hml.h"

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       initial MCU
 * \param[in]   
 * \return      none
 * \ingroup     
 * \remarks     
******************************************************************************/
void sys_init(void)
{
    EXTI_configTypeDef ec;

    ec.mode     = EXTI_mode_fallEdge;
    ec.priority = DISABLE;
    EXTI_config(PERIPH_EXTI_1,&ec);
    EXTI_cmd(PERIPH_EXTI_1,ENABLE);
    enableAllInterrupts();

    GPIO_configPortValue(PERIPH_GPIO_1,0xFF);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
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
 * \date        
 * \brief       interrupt service function for EXTI1
 * \param[in]   
 * \return      none
 * \ingroup     
 * \remarks     
******************************************************************************/
void exti1_isr(void) __interrupt IE1_VECTOR
{
    GPIO_toggleBitValue(PERIPH_GPIO_1,PERIPH_GPIO_PIN_2);
}

