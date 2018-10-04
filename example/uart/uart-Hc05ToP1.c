/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:send byte data which from HC-05 module(via UART) to GPIO1
 * @Required-compiler:SDCC
 * @Support-mcu:8051 and its compitable MCUs
 * @Version:V0
 */

#include "conf.h"

void sys_init(void)
{
	UART_configTypeDef uc;
	
	uc.baudrate = 9600;
	uc.interruptState = ENABLE;
	uc.interruptPriority = DISABLE;
	uc.mode = UART_mode_1;
	uc.multiBaudrate = DISABLE;
	uc.receiveState  = ENABLE;

	UART_config(&uc);
	enableAllInterrupts();
}

void main(void)
{
	sys_init();
	while(true);
}

void uart_isr(void) __interrupt SI0_VECTOR
{
	P1 = SBUF;
	RI = 0;
}

