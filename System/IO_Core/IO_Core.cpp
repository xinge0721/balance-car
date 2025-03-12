#include "IO_Core.h" 

uint32_t GetGpioClock(GPIO_TypeDef* GPIOx) {
	if 			(GPIOx == GPIOA) return RCC_APB2Periph_GPIOA;
	else if (GPIOx == GPIOB) return RCC_APB2Periph_GPIOB;
	else if (GPIOx == GPIOC) return RCC_APB2Periph_GPIOC;
	else if (GPIOx == GPIOD) return RCC_APB2Periph_GPIOD;
	else if (GPIOx == GPIOE) return RCC_APB2Periph_GPIOE;
	else if (GPIOx == GPIOF) return RCC_APB2Periph_GPIOF;
	else if (GPIOx == GPIOG) return RCC_APB2Periph_GPIOG;
	else return 0; // 错误处理
}

uint32_t GetTIMClock(GPIO_TypeDef* GPIOx) {
	if 			(GPIOx == GPIOA) return RCC_APB2Periph_GPIOA;
	else if (GPIOx == GPIOB) return RCC_APB2Periph_GPIOB;
	else if (GPIOx == GPIOC) return RCC_APB2Periph_GPIOC;
	else if (GPIOx == GPIOD) return RCC_APB2Periph_GPIOD;
	else if (GPIOx == GPIOE) return RCC_APB2Periph_GPIOE;
	else if (GPIOx == GPIOF) return RCC_APB2Periph_GPIOF;
	else if (GPIOx == GPIOG) return RCC_APB2Periph_GPIOG;
	else return 0; // 错误处理
}
	GPIO::GPIO(GPIO_TypeDef* _GPIOx, uint16_t _Pin, GPIOMode_TypeDef mode)
	: GPIOx(_GPIOx),
	Pin(_Pin) 
{
	RCC_APB2PeriphClockCmd(GetGpioClock(GPIOx), ENABLE);

	GPIO_InitTypeDef init;
	init.GPIO_Pin = Pin;
	init.GPIO_Speed = GPIO_Speed_50MHz;

	init.GPIO_Mode = mode;

	GPIO_Init(GPIOx, &init);
}

	// 通用IO操作
void GPIO::Write(bool state) {
GPIO_WriteBit(GPIOx, Pin, state ? Bit_SET : Bit_RESET);
}

bool GPIO::Read(void) {
return GPIO_ReadInputDataBit(GPIOx, Pin);
}
	
#include "PWM.h"

PWM::PWM(GPIO_TypeDef* _OC2, u16 _OC2Pin,
					GPIO_TypeDef* _OC3, u16 _OC3Pin,
					
					u16 arr,u16 psc)
					:OC2(_OC2,_OC2Pin,GPIO_Mode_AF_PP),
					OC3(_OC3,_OC2Pin,GPIO_Mode_AF_PP)
{
		
		TIM_TypeDef* pwm_tim = PWM_GetTimerFromGPIO(_OC2, _OC2Pin);
		if(pwm_tim == TIM1){
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    }
    else{
        // TIM2-TIM4,TIM5-TIM7属于APB1
        uint32_t rcc_periph = RCC_APB1Periph_TIM2 * ((uint32_t)pwm_tim - (uint32_t)TIM2)/(0x400);
        RCC_APB1PeriphClockCmd(rcc_periph, ENABLE);
    }

	
}	


