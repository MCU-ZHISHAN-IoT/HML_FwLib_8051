/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:operate on-chip TIM module
 * @Required-complier:SDCC
 * @Support-mcu:Intel MCS-51 based microprocessors
 * @Version:V0
 */

#include "tim.h"

#ifdef ___COMPILE_TIM___

/*
 * @Protype:void TIM_cmd(PERIPH_TIM tim,Action a)
 * @Parameter:
 *  (1)tim:target timer module
 *  (2)a:expected action
 * @Ret-val:
 * @Note:lanuch or stop timer
 */
void TIM_cmd(PERIPH_TIM tim,Action a)
{
	switch(tim)
	{
		case PERIPH_TIM_0:TR0 = a;break;
		case PERIPH_TIM_1:TR1 = a;break;
		default:break;
	}
}

/*
 * @Protype:void TIM_config(PERIPH_TIM tim,TIM_configTypeDef *tc)
 * @Parameter:
 *  (1)tim:target timer module
 *  (2)tc:custom config reference info.,look up details in header file
 * @Ret-val:
 * @Note:config target timer
 */
void TIM_config(PERIPH_TIM tim,TIM_configTypeDef *tc)
{
	TIM_setFunction(tim,tc->function);
	TIM_setMode(tim,tc->mode);
	TIM_setValue(tim,tc->value);
	TIM_INT_cmd(tim,tc->interruptState);
	TIM_INT_setPriority(tim,tc->interruptPriority);
}

/*
 * @Protype:unsigned int TIM_getValue(PERIPH_TIM tim)
 * @Parameter:(1)tim:target timer module
 * @Ret-val:value(if return 0,means user call this function with error ways)
 * @Note:get timer's value
 */
unsigned int TIM_getValue(PERIPH_TIM tim)
{
	switch(tim)
	{
		case PERIPH_TIM_0:return ((TH0 << 0x08) | TL0);
		case PERIPH_TIM_1:return ((TH1 << 0x08) | TL1);
		default:return 0;
	}
}

/*
 * @Protype:bool TIM_isOverflow(PERIPH_TIM tim)
 * @Parameter:(1)tim:target timer module
 * @Ret-val:(1)false:not overflow;(2)true:overflow;
 * @Note:check value register timer if is overflow
 */
bool TIM_isOverflow(PERIPH_TIM tim)
{
	switch(tim)
	{
		case PERIPH_TIM_0:return (bool)TF0;
		case PERIPH_TIM_1:return (bool)TF1;
		default:return false;
	}
}

/*
 * @Protype:void TIM_setFunction(PERIPH_TIM tim,TIM_function f)
 * @Parameter:
 * (1)tim:target timer module
 * (2)f:expected function
 * @Ret-val:
 * @Note:config the module as counter mode or timer mode
 */
void TIM_setFunction(PERIPH_TIM tim,TIM_function f)
{
	switch(tim)
	{
		case PERIPH_TIM_0:TMOD = (TMOD & 0xFB) | (f << 0x02);break;
		case PERIPH_TIM_1:TMOD = (TMOD & 0xBF) | (f << 0x06);break;
		default:break;
	}
}

/*
 * @Protype:void TIM_setMode(PERIPH_TIM tim,TIM_mode m)
 * @Parameter:
 * (1)tim:target timer module
 * (2)m:work mode(refer to header file)
 * @Ret-val:
 * @Note:set work mode of timer
 */
void TIM_setMode(PERIPH_TIM tim,TIM_mode m)
{
	switch(tim)
	{
		case PERIPH_TIM_0:TMOD = (TMOD & 0xFC) | m;break;
		case PERIPH_TIM_1:TMOD = (TMOD & 0xCF) | (m << 0x04);break;
		default:break;
	}
}

/*
 * @Protype:void TIM_setValue(PERIPH_TIM tim,word val)
 * @Parameter:
 * (1)tim:target timer module
 * (2)val:expected value
 * @Ret-val:
 * @Note:set value in value register of specified timer module
 */
void TIM_setValue(PERIPH_TIM tim,word val)
{
	switch(tim)
	{
		case PERIPH_TIM_0:
		{
			TH0 = (u8)((val >> 0x8) & 0x00FF);
			TL0 = (u8)(val & 0x00FF);
		} break;
		case PERIPH_TIM_1:
		{
			TH1 = (u8)((val >> 0x8) & 0x00FF);
			TL1 = (u8)(val & 0x00FF);
		} break;
		default:break;
	}
}

/*
 * @Protype:void TIM_INT_cmd(PERIPH_TIM tim,Action a)
 * @Parameter:
 * (1)tim:target timer module
 * (2)a:expected action,decide disable or enable timer intterupt
 * @Ret-val:
 * @Note:disable or enable timer intterupt
 */
void TIM_INT_cmd(PERIPH_TIM tim,Action a)
{
	switch(tim)
	{
		case PERIPH_TIM_0:ET0 = (FunctionalState)a;break;
		case PERIPH_TIM_1:ET1 = (FunctionalState)a;break;
		default:break;
	}
}

/*
 * @Protype:void TIM_INT_setPriority(PERIPH_TIM tim,Action a)
 * @Parameter:
 * (1)tim:target timer module
 * (2)a:expected action,decide disable or enable the timer has higher priority
 * @Ret-val:
 * @Note:disable or enable the timer has higher priority
 */
void TIM_INT_setPriority(PERIPH_TIM tim,Action a)
{
	switch(tim)
	{
		case PERIPH_TIM_0:PT0 = (FunctionalState)a;break;
		case PERIPH_TIM_1:PT1 = (FunctionalState)a;break;
		default:break;
	}
}

#endif
