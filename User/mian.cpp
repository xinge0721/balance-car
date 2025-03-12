#include "stm32f10x.h"                  // Device header
#include "pivot.h"

OLED oled(GPIOB, GPIO_Pin_8, GPIOB, GPIO_Pin_9);

int main()
{
	Hardware_Init();

	oled.ShowNum(3,3,999,3);
	while(1);
}
