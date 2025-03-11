#include "stm32f10x.h"                  // Device header
#include "pivot.h"


int main()
{
	Hardware_Init();
//	GPIO gpio(GPIOB, GPIO_Pin_8,GPIO_Mode_Out_PP);
	OLED oled(GPIOB, GPIO_Pin_8, GPIOB, GPIO_Pin_9);


	oled.ShowNum(3,3,100,3);
	while(1);
}
