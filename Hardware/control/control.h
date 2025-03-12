#ifndef __control_H
#define __control_H

#include "sys.h"

//class Motor
//{


//};


class control
{

public:
	control(GPIO_TypeDef* _left_GPIOx, u16 _leftPin,
					GPIO_TypeDef* _right_GPIOx, u16 _rightPin);
private:
		IO_Core left;
		IO_Core right;
};

#endif
