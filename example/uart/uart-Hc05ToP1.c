/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:send byte data which from HC-05 module(via UART) to GPIO1
 * @Required-compiler:SDCC
 * @Support-mcu:Intel MCS-51 based microprocessors
 * @Version:V0
 */

#include "conf.h"

/*
 * @Prototype:void sys_init(void)
 * @Parameter:
 * @Ret-val:
 * @Note:init MCU
 */
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

/* ----- @main ----- */
void main(void)
{
	sys_init();
	while(true);
}

/*
 * @Prototype:void uart_isr(void) __interrupt SI0_VECTOR
 * @Parameter:
 * @Ret-val:
 * @Note:interrupt handle function for UART
 */
void uart_isr(void) __interrupt SI0_VECTOR
{
	P1 = SBUF;
	RI = RESET;
}

