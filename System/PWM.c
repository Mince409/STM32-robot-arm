#include "stm32f10x.h"                  // Device header
#include "Delay.h"

#define Serve360 360
#define Serve180 180

void PWM_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitTypeDef GPIO_IntStructure;
	GPIO_IntStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_IntStructure.GPIO_Pin=GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_IntStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_IntStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	TIM_InternalClockConfig(TIM1);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaselnitStructure;
	TIM_TimeBaselnitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//ʱ�ӷ�Ƶ
	TIM_TimeBaselnitStructure.TIM_CounterMode=TIM_CounterMode_Down;//������ģʽ
	TIM_TimeBaselnitStructure.TIM_Period=20000-1;//�������� ��ARR��ֵ
	TIM_TimeBaselnitStructure.TIM_Prescaler=72-1;//Ԥ��Ƶ�� ��PSC��ֵ
	TIM_TimeBaselnitStructure.TIM_RepetitionCounter=0;//�ظ���ʱ��
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaselnitStructure);

	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//PWM1ģʽ
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//����ߵ�ƽ��Ч
	TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCNPolarity_High;//��������ߵ�ƽ��Ч
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//���ͨ����Ч
	TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Enable;//�������ͨ����Ч
	TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Set;//����״̬���ͨ���ʸߵ�ƽ
	TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;//����״̬���ͨ���ʵ͵�ƽ
	TIM_OCInitStructure.TIM_Pulse=0;//CCR ռ�ձ�
	
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);//��ʼ��CH1
	TIM_OC2Init(TIM1,&TIM_OCInitStructure);//��ʼ��CH2
	TIM_OC3Init(TIM1,&TIM_OCInitStructure);//��ʼ��CH3
	TIM_OC4Init(TIM1,&TIM_OCInitStructure);//��ʼ��CH4
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);//����CH1�Զ���װ
	TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);//����CH2�Զ���װ
	TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable);//����CH3�Զ���װ
	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable);//����CH4�Զ���װ
	
	TIM_Cmd(TIM1,ENABLE);//ʹ��TM1
	TIM_CtrlPWMOutputs(TIM1,ENABLE);//��ģʽʹ��
}

void PWM_A8(float PWM)
{
	TIM_SetCompare1(TIM1,PWM / Serve180 * 2000 + 500);
}

void PWM_A9(float PWM )
{
	TIM_SetCompare2(TIM1,PWM / Serve180 * 2000 + 500);
}

void PWM_A10(float PWM )
{
	TIM_SetCompare3(TIM1,PWM / Serve180 * 2000 + 500);
}

void PWM_A11(float PWM)
{
	TIM_SetCompare4(TIM1,PWM / Serve180 * 2000 + 500);
}