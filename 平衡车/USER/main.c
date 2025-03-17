#include "stm32f10x.h"
#include "sys.h" 

float Pitch,Roll,Yaw;						//角度
short gyrox,gyroy,gyroz;				//陀螺仪--角速度
short aacx,aacy,aacz;						//加速度
int now_Rspeed,now_Lspeed;	//编码器数据（速度）

int PWM_MAX=3600,PWM_MIN=-3600;	//PWM限幅变量
int MOTO1,MOTO2;								//电机装载变量

extern int Vertical_out,Velocity_out,Turn_out;


unsigned char i;          //计数变量
unsigned char Send_Count; //串口需要发送的数据个数
int main(void)	
{
	delay_init();
	NVIC_Config();
//	u3_Init();           //初始化串口3 PB10 PB11
	
	OLED_Init();//PB8 PB9
	OLED_Clear();
	Key_Init();   //PC15
	MPU_Init();//PB3 PB4
	while(mpu_dmp_init());
	MPU6050_EXTI_Init();//PB5
//	
	Encoder_TIM2_Init();//PA0 PA1 PA2 PA3
	Encoder_TIM3_Init();//PA6 PA7 PB0 PB1
	Motor_Init();//PB12 13 14 15
	PWM_Init_TIM1(0,3599);//PA8 PA9 PA10 PA11
  while(1)	
	{
		OLED_Float(100,0,now_Rspeed,2);//横滚角
		OLED_Float(100,50,now_Lspeed,2);//偏航角
		
		//加载到电机上
		left(3599);
		right(3599);
	} 	
}



