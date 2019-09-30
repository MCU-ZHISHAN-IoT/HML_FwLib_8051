/*****************************************************************************/
/** 
 * \file        uart.h
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       operation for on-chip UART module
 * \note        
 * \version     v0.2
 * \ingroup     UART
******************************************************************************/

#ifndef ___UART_H___
#define ___UART_H___

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include <stdint.h>
#include "tim.h"

#ifdef HAVE_TIM2
    #include "tim2.h"
#endif

/*****************************************************************************
 *                                macro                                      *
 *****************************************************************************/

/**
 *\brief: mark bits for bit operation
 */
#define BIT_NUM_SMOD 7

/*****************************************************************************
 *                           enumeration type                                *
 *****************************************************************************/

/**
 *\brief: mark work mode
 */
typedef enum
{
    UART_mode_0 = 0x0,  /* 8-bit shift register */
    UART_mode_1 = 0x1,  /* 8-bit UART,variable baud rate */
    UART_mode_2 = 0x2,  /* 9-bit UART,baud rate = fosc/64 or fosc/32 */
    UART_mode_3 = 0x3   /* 9-bit UART,variable baud rate */
} UART_mode;

/**
 *\brief: mark baud rate generator
 */
typedef enum
{
    UART_baudGenerator_tim1 = 0x0,
    UART_baudGenerator_tim2 = 0x1      /* require macro HAVE_TIM2 */
} UART_baudGenerator;

/*****************************************************************************
 *                           structure define                                *
 *****************************************************************************/

/**
 *\brief: structure for configure UART module
 */
typedef struct
{
    uint32_t  baudrate;
    Action    interruptState;
    Action    interruptPriority;
    UART_mode mode;
    Action    multiBaudrate;
    Action    receiveState;

#ifdef HAVE_TIM2
    UART_baudGenerator baudGenertor;
#endif

} UART_configTypeDef;

/*****************************************************************************
 *                          function declare                                 *
 *****************************************************************************/
void UART_cmd_multiBaudrate(Action a);
void UART_cmd_receive(Action a);
void UART_config(UART_configTypeDef *uc);
unsigned int UART_getBaudGeneratorInitValue(uint32_t baud, UART_baudGenerator g);
FunctionalState UART_isReceived(void);
FunctionalState UART_isTransmitted(void);
void UART_sendByte(byte dat);
void UART_sendString(char *str);
void UART_setMode(UART_mode m);
void UART_INT_cmd(Action a);
void UART_INT_setPriority(Action a);

#endif
