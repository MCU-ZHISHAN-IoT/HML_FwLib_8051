/*****************************************************************************/
/** 
 * \file        test.c
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       a example which shows how to use HML_FwLib_8051 to send string
 *              via UART module
 * \note        
 * \test-board  TS51-V2.0
 * \test-mcu    STC89C52RC
 * \version     v0.2
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
    UART_configTypeDef uc;

    uc.baudrate          = 9600;
    uc.interruptState    = ENABLE;
    uc.interruptPriority = DISABLE;
    uc.mode              = UART_mode_1;
    uc.multiBaudrate     = DISABLE;
    uc.receiveState      = ENABLE;
    uc.baudGenertor      = UART_baudGenerator_tim1;

    UART_config(&uc);
    enableAllInterrupts();
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
    while(true)
    {
        sleep(500);
        UART_sendString("Hello,world!\r\n");
    }
}
