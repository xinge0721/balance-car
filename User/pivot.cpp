#include "pivot.h"

void Hardware_Init()
{
	LED_Init();
	
}

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
