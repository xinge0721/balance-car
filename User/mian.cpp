#include "stm32f10x.h"                  // Device header
#include "pivot.h"
//初始化
OLED oled(GPIOB, GPIO_Pin_8, GPIOB, GPIO_Pin_9);
control Contro
				(GPIOB,GPIO_Pin_12,GPIOB,GPIO_Pin_13,//左电机
				GPIOB,GPIO_Pin_14,GPIOB,GPIO_Pin_15,//右电机
				GPIOA,GPIO_Pin_8,GPIOA,GPIO_Pin_11,7199,0);//俩个电机的PWM
				
//双边沿计数，脉冲值是单边沿的4倍
encoder End_left(GPIOB, GPIO_Pin_6,
								GPIOB, GPIO_Pin_7,
								65535, 0);
encoder End_right(GPIOA, GPIO_Pin_6,
									GPIOA, GPIO_Pin_7,
									65535, 0);
MPU6050 MPU(GPIOB, GPIO_Pin_3, GPIOB, GPIO_Pin_4);


int main()
{
	Hardware_Init();

//	oled.ShowNum(3,3,999,3);
	Contro.left.Go();
	Contro.right.Go();

	int16_t seepdleft = 0;
	int16_t seepdRight = 0;
	while(1)
	{

		Delay_ms(50);
		Contro.pwm.setOc1(3600); // 50%占空比
		Contro.pwm.setOc4(3600);
		
		seepdleft += End_left.Right();
		
		oled.ShowNum(2,1,seepdleft,5);
		seepdRight += End_right.Right();

		oled.ShowNum(3,1,seepdRight,5);

	}
}
