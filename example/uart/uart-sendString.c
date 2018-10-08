/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:a example which shows how to use HML_FwLib_8051 to send string via UART module
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
	while(true)
	{
		sleep(500);
		UART_sendString("Hello,world!\r\n");
	}
}
