#ifndef __pivot_H
#define __pivot_H

#include "sys.h"
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "OLED_Font.h"
#include "PWM.h"
void Hardware_Init();
uint32_t GetGpioClock(GPIO_TypeDef* GPIOx);

class GPIO {

public:
    GPIO_TypeDef* GPIOx;
    uint16_t Pin;
		GPIO(GPIO_TypeDef* _GPIOx, uint16_t _Pin,GPIOMode_TypeDef mode);

    // Í¨ÓÃIO²Ù×÷
    void Write(bool state);

    bool Read(void);
};

#endif
