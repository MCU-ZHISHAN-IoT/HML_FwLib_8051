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
 * @Prototype:void UART_cmd_multiBaudrate(Action a)
 * @Parameter:(1)a:expected action
 * @Ret-val:
 * @Note:disable or enable multi baud rate mode
 */
void UART_cmd_multiBaudrate(Action a)
{
	PCON = (PCON & 0x7F) | ((unsigned char)a << 0x7);
}

/*
 * @Prototype:void UART_cmd_receive(Action a)
 * @Parameter:(1)a:expected action
 * @Ret-val:
 * @Note:disable or enable receive function of UART module
 */
void UART_cmd_receive(Action a)
{
	REN = a;
}

/*
 * @Prototype:unsigned int UART_getBaudGeneratorInitValue(uint32_t baud)
 * @Parameter:(1)baud:expected baud rate
 * @Ret-val:initial value the baud rate required of timer counter register(if return 0x0000, it means overflow)
 * @Note:calculate timer counter register value
 */
unsigned int UART_getBaudGeneratorInitValue(uint32_t baud)
{
	unsigned char tmp = 0x00;
	
	if(PCON & 0x80)     /* multi baud rate mode */
	{
		if(baud > _FRE_OSC_/12/16)
		{
			/* baud rate over max value */
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
 * @Prototype:void UART_config(UART_configTypeDef *uc)
 * @Parameter:(1)uc:the pointer of configuration struct
 * @Ret-val:
 * @Note:configure UART module
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
	
	/* UART module need TIM1 module as baud rate generator */
	tc.function          = TIM_FUNC_TIM;
	tc.interruptState    = DISABLE;
	tc.interruptPriority = DISABLE;
	tc.mode              = TIM_mode_2;
	tc.value             = UART_getBaudGeneratorInitValue(uc->baudrate);
	TIM_config(PERIPH_TIM_1,&tc);
	TIM_cmd(PERIPH_TIM_1,ENABLE);
	
}

/*
 * @Prototype:FunctionalState UART_isReceived(void)
 * @Parameter:
 * @Ret-val:(1)SET:data have been received;(2)RESET:data haven't been received
 * @Note:
 */
FunctionalState UART_isReceived(void)
{
	return (FunctionalState)RI;
}

/*
 * @Prototype:FunctionalState UART_isTransmitted(void)
 * @Parameter:
 * @Ret-val:(1)SET:data have been transmitted;(2)RESET:data haven't been transmitted
 * @Note:
 */
FunctionalState UART_isTransmitted(void)
{
	return (FunctionalState)TI;
}

/*
 * @Prototype:void UART_sendByte(byte dat)
 * @Parameter:(1)dat:one byte of data user want to send
 * @Ret-val:
 * @Note:send a byte via UART module
 */
void UART_sendByte(byte dat)
{
	SBUF = dat;
	while(!TI);
	TI = RESET;
}

/*
 * @Prototype:void UART_sendString(char *str)
 * @Parameter:(1)str:the point of string user want to send
 * @Ret-val:
 * @Note:send a ASCII string via UART module
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
 * @Prototype:void UART_setMode(UART_mode m)
 * @Parameter:(1)m:expected work mode
 * @Ret-val:
 * @Note:set work mode of UART module
 */
void UART_setMode(UART_mode m)
{
	SCON = (SCON & 0x3F) | ((unsigned char)m << 0x6);
}

/*
 * @Prototype:void UART_INT_cmd(Action a)
 * @Parameter:(1)a:expected action
 * @Ret-val:
 * @Note:disable or enable interrupt function of UART module
 */
void UART_INT_cmd(Action a)
{
	ES = a;
}

/*
 * @Prototype:void UART_INT_setPriority(Action a)
 * @Parameter:(1)a:expected action
 * @Ret-val:
 * @Note:disable or enable interrupt priority state of UART module
 */
void UART_INT_setPriority(Action a)
{
	PS = a;
}

#endif
