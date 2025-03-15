#include "IO_Core.h" 
#include "assert.h"

// PWM�����붨ʱ����ӳ�������STM32F103C8T6�ֲ����ã�
const TIM_GPIO_Mapping timMap[] = {
    // TIM1��APB2��
    {GPIOA, GPIO_Pin_8,  TIM1}, // TIM1_CH1
    {GPIOA, GPIO_Pin_9,  TIM1}, // TIM1_CH2
    {GPIOA, GPIO_Pin_10, TIM1}, // TIM1_CH3
    {GPIOA, GPIO_Pin_11, TIM1}, // TIM1_CH4
    
    // TIM2��APB1��
    {GPIOA, GPIO_Pin_0,  TIM2}, // TIM2_CH1
    {GPIOA, GPIO_Pin_1,  TIM2}, // TIM2_CH2
    {GPIOA, GPIO_Pin_2,  TIM2}, // TIM2_CH3
    {GPIOA, GPIO_Pin_3,  TIM2}, // TIM2_CH4
    
    // TIM3��APB1��
    {GPIOA, GPIO_Pin_6,  TIM3}, // TIM3_CH1
    {GPIOA, GPIO_Pin_7,  TIM3}, // TIM3_CH2
    {GPIOB, GPIO_Pin_0,  TIM3}, // TIM3_CH3
    {GPIOB, GPIO_Pin_1,  TIM3}, // TIM3_CH4
    
    // TIM4��APB1��
    {GPIOB, GPIO_Pin_6,  TIM4}, // TIM4_CH1
    {GPIOB, GPIO_Pin_7,  TIM4}, // TIM4_CH2
    {GPIOB, GPIO_Pin_8,  TIM4}, // TIM4_CH3
    {GPIOB, GPIO_Pin_9,  TIM4}, // TIM4_CH4
};

// ��ʱ����ѯ����
TIM_TypeDef* GetTimerFromGPIO(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    for(uint8_t i=0; i<sizeof(timMap)/sizeof(timMap[0]); i++)
    {
        if(timMap[i].GPIOx == GPIOx && timMap[i].Pin == GPIO_Pin)
        {
            return timMap[i].TIMx;
        }
    }
    return NULL;
}


uint32_t GetGpioClock(GPIO_TypeDef* GPIOx) {
	if 			(GPIOx == GPIOA) return RCC_APB2Periph_GPIOA;
	else if (GPIOx == GPIOB) return RCC_APB2Periph_GPIOB;
	else if (GPIOx == GPIOC) return RCC_APB2Periph_GPIOC;
	else if (GPIOx == GPIOD) return RCC_APB2Periph_GPIOD;
	else if (GPIOx == GPIOE) return RCC_APB2Periph_GPIOE;
	else if (GPIOx == GPIOF) return RCC_APB2Periph_GPIOF;
	else if (GPIOx == GPIOG) return RCC_APB2Periph_GPIOG;
	else return 0; // ������
}

uint32_t GetTIMClock(TIM_TypeDef* TIMx) {
	if 			(TIMx == TIM2) return RCC_APB1Periph_TIM2;
	else if (TIMx == TIM3) return RCC_APB1Periph_TIM3;
	else if (TIMx == TIM4) return RCC_APB1Periph_TIM4;
	else if (TIMx == TIM5) return RCC_APB1Periph_TIM5;
	else if (TIMx == TIM6) return RCC_APB1Periph_TIM6;
	else if (TIMx == TIM7) return RCC_APB1Periph_TIM7;
	else if (TIMx == TIM12) return RCC_APB1Periph_TIM12;
	else if (TIMx == TIM13) return RCC_APB1Periph_TIM13;
	else if (TIMx == TIM14) return RCC_APB1Periph_TIM14;
	else return 0; // ������
}
	GPIO::GPIO(GPIO_TypeDef* _GPIOx, uint16_t _Pin, GPIOMode_TypeDef mode)
	: GPIOx(_GPIOx),
	Pin(_Pin) 
{
	RCC_APB2PeriphClockCmd(GetGpioClock(GPIOx), ENABLE);

	GPIO_InitTypeDef init;
	init.GPIO_Pin = Pin;
	init.GPIO_Speed = GPIO_Speed_50MHz;

	init.GPIO_Mode = mode;

	GPIO_Init(GPIOx, &init);
}

	// ͨ��IO����
void GPIO::Write(bool state) {
GPIO_WriteBit(GPIOx, Pin, state ? Bit_SET : Bit_RESET);
}

bool GPIO::Read(void) {
return GPIO_ReadInputDataBit(GPIOx, Pin);
}
	
#include "PWM.h"

PWM::PWM(GPIO_TypeDef* _OC2, u16 _OC2Pin,
					GPIO_TypeDef* _OC3, u16 _OC3Pin,
					
					u16 arr,u16 psc)
					:OC2(_OC2,_OC2Pin,GPIO_Mode_AF_PP),
					OC3(_OC3,_OC3Pin,GPIO_Mode_AF_PP)
{
		
		TIM_TypeDef* OC2_tim = GetTimerFromGPIO(_OC2, _OC2Pin);
		TIM_TypeDef* OC3_tim = GetTimerFromGPIO(_OC3, _OC3Pin);

		// ��������Ƿ�ӳ�䵽��Ч�Ķ�ʱ��
		if (OC2_tim == NULL || OC3_tim == NULL) {
				assert(0 && "Invalid PWM pin mapping!"); // ��ȷ����ԭ��
				return;
		}

		// ����Ƿ�ʹ��ͬһ��ʱ��
		if (OC2_tim != OC3_tim) {
				assert(0 && "OC2 and OC3 must use the same timer!");
				return;
		}

		this->pwm_tim = OC2_tim; // ֱ��ʹ��OC2_tim����ȷ��OC2_tim == OC3_tim��

		// ���ݶ�ʱ������ʹ��ʱ��
		if (pwm_tim == TIM1) {
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
		} else {
				RCC_APB1PeriphClockCmd(GetTIMClock(pwm_tim), ENABLE);
		}

		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  // ���嶨ʱ��ʱ���׼��ʼ���ṹ�����

		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseStructure.TIM_Period = arr;
		TIM_TimeBaseStructure.TIM_Prescaler = psc;
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
		
		TIM_TimeBaseInit(pwm_tim, &TIM_TimeBaseStructure);  // ��ʼ��TIM
		
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure); // ��ʼ��TIM_OCInitStruct�ṹ������г�Ա
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; // ����ΪPWMģʽ1
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; // ������Ը�
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // �Ƚ����ʹ��
    TIM_OCInitStructure.TIM_Pulse = 0; // ��ʼռ�ձ�����Ϊ0
		
		TIM_OC2Init(pwm_tim, &TIM_OCInitStructure); // ��ʼ��ͨ��2������Ƚϲ���
    TIM_OC3Init(pwm_tim, &TIM_OCInitStructure); // ��ʼ��ͨ��3������Ƚϲ���
		
		
    TIM_OC2PreloadConfig(pwm_tim, TIM_OCPreload_Enable); // ʹ��ͨ��2������Ƚ�Ԥװ�ؼĴ���
    TIM_OC3PreloadConfig(pwm_tim, TIM_OCPreload_Enable); // ʹ��ͨ��3������Ƚ�Ԥװ�ؼĴ���

    // ʹ��TIM5
    TIM_Cmd(pwm_tim, ENABLE);
		if (pwm_tim == TIM1) 
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
}	

void PWM::oc2(u16 value) 
{
		 TIM_SetCompare2(pwm_tim, value);
}

void PWM::oc3(u16 value) 
{
		 TIM_SetCompare3(pwm_tim, value);
}




