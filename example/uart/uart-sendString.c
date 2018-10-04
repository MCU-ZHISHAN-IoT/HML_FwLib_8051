/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:a demo which shows how to use HML_FwLib_8051 to send string via UART module
 * @Required-compiler:SDCC
 * @Support-mcu:8051 and its compitable MCUs
 * @Version:V0
 */
#include "conf.h"

/*
 * @Protype:void sys_init(void)
 * @Parameter:None
 * @Ret-val:None
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

void main(void)
{	
    sys_init();
	while(true)
	{
		sleep(500);
		UART_sendString("Hello,world!\r\n");
	}
}
