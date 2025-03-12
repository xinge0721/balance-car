#include "control.h"

control::control(GPIO_TypeDef* _left_GPIOx, uint16_t _leftPin, 
								GPIO_TypeDef* _right_GPIOx, uint16_t _rightPin)
					:left(_left_GPIOx,_leftPin,GPIO_Mode_Out_PP),
					right(_right_GPIOx,_rightPin,GPIO_Mode_Out_PP)
{
		left.Write(0);
		right.Write(0);		
}

