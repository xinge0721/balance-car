#ifndef __IO_Core_H
#define __IO_Core_H	 

#include "stm32f10x.h"                  // Device header
#include "stddef.h"

class GPIO {

public:
    GPIO_TypeDef* GPIOx;
    uint16_t Pin;
		GPIO(GPIO_TypeDef* _GPIOx, uint16_t _Pin,GPIOMode_TypeDef mode);

    // 通用IO操作
    void Write(bool state);

    bool Read(void);
};

typedef struct {
    GPIO_TypeDef* GPIOx;
    uint16_t Pin;
    TIM_TypeDef* TIMx;
} TIM_GPIO_Mapping;

// PWM引脚与定时器的映射表（根据STM32F103C8T6手册配置）
static const TIM_GPIO_Mapping timMap[] = {
    // TIM1（APB2）
    {GPIOA, GPIO_Pin_8,  TIM1}, // TIM1_CH1
    {GPIOA, GPIO_Pin_9,  TIM1}, // TIM1_CH2
    {GPIOA, GPIO_Pin_10, TIM1}, // TIM1_CH3
    {GPIOA, GPIO_Pin_11, TIM1}, // TIM1_CH4
    
    // TIM2（APB1）
    {GPIOA, GPIO_Pin_0,  TIM2}, // TIM2_CH1
    {GPIOA, GPIO_Pin_1,  TIM2}, // TIM2_CH2
    {GPIOA, GPIO_Pin_2,  TIM2}, // TIM2_CH3
    {GPIOA, GPIO_Pin_3,  TIM2}, // TIM2_CH4
    
    // TIM3（APB1）
    {GPIOA, GPIO_Pin_6,  TIM3}, // TIM3_CH1
    {GPIOA, GPIO_Pin_7,  TIM3}, // TIM3_CH2
    {GPIOB, GPIO_Pin_0,  TIM3}, // TIM3_CH3
    {GPIOB, GPIO_Pin_1,  TIM3}, // TIM3_CH4
    
    // TIM4（APB1）
    {GPIOB, GPIO_Pin_6,  TIM4}, // TIM4_CH1
    {GPIOB, GPIO_Pin_7,  TIM4}, // TIM4_CH2
    {GPIOB, GPIO_Pin_8,  TIM4}, // TIM4_CH3
    {GPIOB, GPIO_Pin_9,  TIM4}, // TIM4_CH4
};
class PWM
{
private:
 GPIO OC2;
 GPIO OC3;


// PWM定时器查询函数
TIM_TypeDef* PWM_GetTimerFromGPIO(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    for(uint8_t i=0; i<sizeof(timMap)/sizeof(timMap[0]); i++)
    {
        if(timMap[i].GPIOx == GPIOx && timMap[i].Pin == GPIO_Pin)
        {
            return timMap[i].TIMx;
        }
    }
    return NULL;
}

public:
	PWM(GPIO_TypeDef* _OC2, u16 _OC2Pin,
			GPIO_TypeDef* _OC3, u16 _OC3Pin,
			u16 arr,u16 psc);
};
#endif











