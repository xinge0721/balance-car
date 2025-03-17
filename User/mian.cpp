#include "stm32f10x.h"                  // Device header
#include "pivot.h"
//初始化
OLED oled(GPIOB, GPIO_Pin_8, GPIOB, GPIO_Pin_9);
control Contro
				(GPIOB,GPIO_Pin_12,GPIOB,GPIO_Pin_13,//左电机
				GPIOB,GPIO_Pin_14,GPIOB,GPIO_Pin_15,//右电机
				GPIOA,GPIO_Pin_8,GPIOA,GPIO_Pin_11,7199,0);//俩个电机的PWM
				
//双边沿计数，脉冲值是单边沿的4倍
//encoder End_left(GPIOA, GPIO_Pin_1,
//								GPIOA, GPIO_Pin_0,
//								65535, 0);
								
encoder End_right(GPIOA, GPIO_Pin_6,
									GPIOA, GPIO_Pin_7,
									65535, 0);
									
MPU6050 MPU(GPIOB, GPIO_Pin_3,
						GPIOB, GPIO_Pin_4
						GPIOB, GPIO_Pin_B);//PB5


int main()
{
	Hardware_Init();
GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;//初始化GPIO--PA0、PA1
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0 |GPIO_Pin_1;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);//初始化定时器。
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=65535;
	TIM_TimeBaseInitStruct.TIM_Prescaler=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//配置编码器模式
	
	TIM_ICStructInit(&TIM_ICInitStruct);//初始化输入捕获
	TIM_ICInitStruct.TIM_ICFilter=10;
	TIM_ICInit(TIM2,&TIM_ICInitStruct);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//配置溢出更新中断标志位
	
	TIM_SetCounter(TIM2,0);//清零定时器计数值
	
	TIM_Cmd(TIM2,ENABLE);//开启定时器
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
		
		seepdleft += TIM_GetCounter(TIM2);TIM_SetCounter(TIM2,0);
		
		oled.ShowNum(2,1,seepdleft,5);
		seepdRight += End_right.Right();

		oled.ShowNum(3,1,seepdRight,5);

	}
}
