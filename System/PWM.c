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
	TIM_TimeBaselnitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//时钟分频
	TIM_TimeBaselnitStructure.TIM_CounterMode=TIM_CounterMode_Down;//计数器模式
	TIM_TimeBaselnitStructure.TIM_Period=20000-1;//计数周期 即ARR的值
	TIM_TimeBaselnitStructure.TIM_Prescaler=72-1;//预分频器 即PSC的值
	TIM_TimeBaselnitStructure.TIM_RepetitionCounter=0;//重复计时器
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaselnitStructure);

	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//PWM1模式
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//输出高电平有效
	TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCNPolarity_High;//输出互补高电平有效
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//输出通道有效
	TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Enable;//输出互补通道有效
	TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Set;//空闲状态输出通道呈高电平
	TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;//空闲状态输出通道呈低电平
	TIM_OCInitStructure.TIM_Pulse=0;//CCR 占空比
	
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);//初始化CH1
	TIM_OC2Init(TIM1,&TIM_OCInitStructure);//初始化CH2
	TIM_OC3Init(TIM1,&TIM_OCInitStructure);//初始化CH3
	TIM_OC4Init(TIM1,&TIM_OCInitStructure);//初始化CH4
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);//允许CH1自动重装
	TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);//允许CH2自动重装
	TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable);//允许CH3自动重装
	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable);//允许CH4自动重装
	
	TIM_Cmd(TIM1,ENABLE);//使能TM1
	TIM_CtrlPWMOutputs(TIM1,ENABLE);//主模式使能
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