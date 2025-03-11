#ifndef __PWM_H
#define __PWM_H

#include "pivot.h"
class PWM
{
private:

public:
	PWM(GPIO_TypeDef* _SCL_GPIOx, u16 _sclPin,u16 arr,u16 psc);
};

#endif
