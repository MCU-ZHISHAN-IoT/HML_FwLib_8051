/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:operate on-chip UART module
 * @Required-complier:SDCC
 * @Support-mcu:Intel MCS-51 based microprocessors
 * @Version:V0
 */

#include "uart.h"

#ifdef ___COMPILE_UART___

/*
 * @Protype:void UART_cmd_multiBaudrate(Action a)
 * @Parameter:(1)a:expected action
 * @Ret-val:
 * @Note:disable or enable multi baudrate mode
 */
void UART_cmd_multiBaudrate(Action a)
{
	PCON = (PCON & 0x7F) | ((unsigned char)a << 0x7);
}

/*
 * @Protype:void UART_cmd_receive(Action a)
 * @Parameter:(1)a:expected action
 * @Ret-val:
 * @Note:disable or enable receive function of UART module
 */
void UART_cmd_receive(Action a)
{
	REN = a;
}

/*
 * @Protype:unsigned int UART_getTimerInitValue(unsigned int baud)
 * @Parameter:(1)baud:expected baudrate
 * @Ret-val:init value the baudrate required of timer counter register(if return 0x0000,it means overflow)
 * @Note:calculate timer counter register value
 */
unsigned int UART_getTimerInitValue(unsigned int baud)
{
	unsigned char tmp = 0x00;
	
	if(PCON & 0x80)     /* multi baudrate mode */
	{
		if(baud > _FRE_OSC_/12/16)
		{
			/* baudrate over max value */
			return 0x0000;
		}
		else 
		{
			tmp = (256 - _FRE_OSC_/16/12/baud);  
		}
	}
	else
	{
		if(baud > _FRE_OSC_/12/32)
		{
			return 0x0000;
		}
		else
		{
			tmp = (256 - _FRE_OSC_/32/12/baud);
		}
	}
	
	return (tmp << 0x8) | tmp;
}

/*
 * @Protype:void UART_config(UART_configTypeDef *uc)
 * @Parameter:(1)uc:the pointer of config struct
 * @Ret-val:
 * @Note:config UART module
 */
void UART_config(UART_configTypeDef *uc)
{
	TIM_configTypeDef tc;
	
	UART_INT_cmd(uc->interruptState);
	UART_INT_setPriority(uc->interruptPriority);
	UART_cmd_multiBaudrate(uc->multiBaudrate);
	
	//TODO:2018-04-07
	UART_setMode(uc->mode);
	UART_cmd_receive(uc->receiveState);
	
	/* UART module need TIM1 module as baudrate generator */
	tc.function          = TIM_FUNC_TIM;
	tc.interruptState    = DISABLE;
	tc.interruptPriority = DISABLE;
	tc.mode              = TIM_mode_2;
	tc.value             = UART_getTimerInitValue(uc->baudrate);
	TIM_config(PERIPH_TIM_1,&tc);
	TIM_cmd(PERIPH_TIM_1,ENABLE);
	
}

/*
 * @Protype:FunctionalState UART_isReceived(void)
 * @Parameter:
 * @Ret-val:(1)SET:data have been received;(2)RESET:data haven't been received
 * @Note:
 */
FunctionalState UART_isReceived(void)
{
	return (FunctionalState)RI;
}

/*
 * @Protype:FunctionalState UART_isTransmitted(void)
 * @Parameter:
 * @Ret-val:(1)SET:data have been transmitted;(2)RESET:data haven't been transmitted
 * @Note:
 */
FunctionalState UART_isTransmitted(void)
{
	return (FunctionalState)TI;
}

/*
 * @Protype:void UART_sendByte(unsigned char dat)
 * @Parameter:(1)dat:one byte of data user want to send
 * @Ret-val:
 * @Note:send a byte via UART module
 */
void UART_sendByte(unsigned char dat)
{
	SBUF = dat;
	while(!TI);
	TI = RESET;
}

/*
 * @Protype:void UART_sendString(char *str)
 * @Parameter:(1)str:the point of string user want to send
 * @Ret-val:
 * @Note:send a Ascii string via UART module
 */
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

/*
 * @Protype:void UART_setMode(UART_mode m)
 * @Parameter:(1)m:expected work mode
 * @Ret-val:
 * @Note:set work mode of UART module
 */
void UART_setMode(UART_mode m)
{
	SCON = (SCON & 0x3F) | ((unsigned char)m << 0x6);
}

/*
 * @Protype:void UART_INT_cmd(Action a)
 * @Parameter:(1)a:expected action
 * @Ret-val:
 * @Note:disable or enable interupt function of UART module
 */
void UART_INT_cmd(Action a)
{
	ES = a;
}

/*
 * @Protype:void UART_INT_setPriority(Action a)
 * @Parameter:(1)a:expected action
 * @Ret-val:
 * @Note:disable or enable interupt priority state of UART module
 */
void UART_INT_setPriority(Action a)
{
	PS = a;
}

#endif
