/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:a demo which shows how to use HML to toggle P10 state when EXTI is trigged
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
	EXTI_configTypeDef ec;
	
	ec.mode = EXTI_mode_fallEdge;
	ec.priority = DISABLE;
	EXTI_config(PERIPH_EXTI_1,&ec);
	EXTI_cmd(PERIPH_EXTI_1,ENABLE);
	enableAllInterrupts();
	
	GPIO_configPort(PERIPH_GPIO_1,0xFF);
}

void main(void)
{
	sys_init();
	while(true);
}

/*
 * @Protype:void exti1_isr(void)
 * @Parameter:None
 * @Ret-val:None
 * @Note:interrupt service function for EXTI1
 */
void exti1_isr(void) __interrupt IE1_VECTOR
{
	GPIO_toggleBitValue(PERIPH_GPIO_1,PERIPH_GPIO_PIN_2);
}

