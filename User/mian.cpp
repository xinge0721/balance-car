#include "stm32f10x.h"                  // Device header
#include "pivot.h"


int main()
{
	Hardware_Init();
	OLED oled(GPIOB,8,GPIOB,9);
	
	oled.ShowNum(3,3,100,3);
	while(1);
}
