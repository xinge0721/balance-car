#include "key.h"
#include "delay.h"
int Keyflag;
/**
  * 函    数：按键初始化
  * 参    数：无
  * 返 回 值：无
  */
void Key_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_Key_InitStructure;
	GPIO_Key_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Key_InitStructure.GPIO_Pin=GPIO_Pin_15;
	GPIO_Key_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_Key_InitStructure);
	
}
uint8_t Get_Key1Num()
{
	uint8_t KeyNum=0;
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)==0)
	{
		delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)==0);
		delay_ms(20);
		KeyNum=1;
	}
	return KeyNum;
}
