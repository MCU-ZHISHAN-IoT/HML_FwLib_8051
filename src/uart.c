/*****************************************************************************/
/** 
 * \file        uart.c
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       operation for on-chip UART module
 * \note        
 * \version     v0.1
 * \ingroup     UART
******************************************************************************/

#include "uart.h"

#ifdef __CONF_COMPILE_UART

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       disable or enable multi baud rate mode
 * \param[in]   a: expected action
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART_cmd_multiBaudrate(Action a)
{
    CONFB(PCON,BIT_NUM_SMOD,a);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       disable or enable receive function of UART module
 * \param[in]   a: expected action
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART_cmd_receive(Action a)
{
    REN = a;
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       calculate value needed by timer counter register
 * \param[in]   baud: expected baud rate
 * \return      initial value the baud rate required of timer counter register(if return 0x0000, it means overflow)
 * \ingroup     UART
 * \remarks     
******************************************************************************/
unsigned int UART_getBaudGeneratorInitValue(uint32_t baud)
{
    unsigned char tmp = 0x00;
    
    if(PCON & 0x80)     /* multi baud rate mode */
    {
        if(baud > MCU_FRE_CLK/12/16)
        {
            /* baud rate over max value */
            return 0x0000;
        }
        else 
        {
            tmp = (256 - MCU_FRE_CLK/16/12/baud);  
        }
    }
    else
    {
        if(baud > MCU_FRE_CLK/12/32)
        {
            return 0x0000;
        }
        else
        {
            tmp = (256 - MCU_FRE_CLK/32/12/baud);
        }
    }
    
    return (tmp << 0x8) | tmp;
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       configure UART module
 * \param[in]   uc: the pointer of configuration structure
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART_config(UART_configTypeDef *uc)
{
    TIM_configTypeDef tc;
    
    UART_INT_cmd(uc->interruptState);
    UART_INT_setPriority(uc->interruptPriority);
    UART_cmd_multiBaudrate(uc->multiBaudrate);
    
    //TODO:2018-04-07
    UART_setMode(uc->mode);
    UART_cmd_receive(uc->receiveState);
    
    /* UART module need TIM1 module as baud rate generator */
    tc.function          = TIM_function_tim;
    tc.interruptState    = DISABLE;
    tc.interruptPriority = DISABLE;
    tc.mode              = TIM_mode_2;
    tc.value             = UART_getBaudGeneratorInitValue(uc->baudrate);
    TIM_config(PERIPH_TIM_1,&tc);
    TIM_cmd(PERIPH_TIM_1,ENABLE);
    
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       check receive state of UART module
 * \param[in]   
 * \return      SET(data have been received) or RESET(data haven't been received)
 * \ingroup     UART
 * \remarks     
******************************************************************************/
FunctionalState UART_isReceived(void)
{
    return (FunctionalState)RI;
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       check transmit state of UART module
 * \param[in]   
 * \return      SET(data have been transmitted) or RESET(data haven't been transmitted)
 * \ingroup     UART
 * \remarks     
******************************************************************************/
FunctionalState UART_isTransmitted(void)
{
    return (FunctionalState)TI;
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       send one byte of data via UART module
 * \param[in]   dat: the data you want to send(range: 0x00~0xFF)
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART_sendByte(byte dat)
{
    SBUF = dat;
    while(!TI);
    TI = RESET;
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       send one byte of date via UART module
 * \param[in]   str: the point of string user want to send
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART_sendString(char *str)
{
    while(*str != '\0')
    {
        SBUF = *str;
        while(!TI);
        TI = RESET;     /* clear */
        str++;
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       set work mode of UART module
 * \param[in]   m: expected work mode
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART_setMode(UART_mode m)
{
    SCON = (SCON & 0x3F) | ((unsigned char)m << 0x6);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       disable or enable interrupt switch of UART module
 * \param[in]   a: expected action
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART_INT_cmd(Action a)
{
    ES = a;
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       configure interrupt priority class of UART module
 * \param[in]   a: expected action(ENABLE: high priority class; DISABLE: low priority class)
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART_INT_setPriority(Action a)
{
    PS = a;
}

#endif
