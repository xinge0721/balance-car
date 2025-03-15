#ifndef IO_CORE_H  // 推荐使用普通名称
#define IO_CORE_H

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

extern const TIM_GPIO_Mapping timMap[];  


class PWM
{
private:
 GPIO OC2;
 GPIO OC3;
TIM_TypeDef* pwm_tim;


public:
	PWM(GPIO_TypeDef* _OC2, u16 _OC2Pin,
			GPIO_TypeDef* _OC3, u16 _OC3Pin,
			u16 arr,u16 psc);
	void oc2(u16 value = 0);
	void oc3(u16 value = 0);
};


#endif











