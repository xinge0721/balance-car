#include "stm32f10x.h"                  // Device header
#include "pivot.h"
//初始化
OLED oled(GPIOB, GPIO_Pin_8, GPIOB, GPIO_Pin_9);
control Controlleft
				(GPIOB,GPIO_Pin_12,GPIOB,GPIO_Pin_13,//左电机
				GPIOB,GPIO_Pin_14,GPIOB,GPIO_Pin_15,//右电机
				GPIOA,GPIO_Pin_8,GPIOA,GPIO_Pin_11,7199,0);//俩个电机的PWM
				
//双边沿计数，脉冲值是单边沿的4倍
encoder End_left(GPIOA, GPIO_Pin_0,
								GPIOA, GPIO_Pin_1,
								65535, 0);
encoder End_right(GPIOA, GPIO_Pin_6,
									GPIOA, GPIO_Pin_7,
									65535, 0);
MPU6050 MPU(GPIOB, GPIO_Pin_3, GPIOB, GPIO_Pin_4);


int main()
{
	Hardware_Init();

	oled.ShowNum(3,3,999,3);
	Controlleft.left.Go();
	Controlleft.right.Go();

	int i = 0;
	while(1)
	{
		Controlleft.pwm.setOc1(3600); // 50%占空比
		Controlleft.pwm.setOc4(3600);
		i += End_left.Right();
		i += End_right.Right();
		oled.ShowNum(3,3,i,3);
	}
}
