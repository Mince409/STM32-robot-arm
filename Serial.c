#include "stm32f10x.h"                  // Device header
#include "stdarg.h"
#include "OLED.h"
uint16_t RxTime[13]; //�洢���յ����� ����ʵ��������� [������鸺��������е�����]
uint8_t RxAddr;
uint16_t MySize;
uint8_t RxData;
void Serial_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_IntStructure;
	GPIO_IntStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_IntStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_IntStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_IntStructure);
	
	GPIO_IntStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_IntStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_IntStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_IntStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate=9600;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART2,&USART_InitStructure);
	USART_Cmd(USART2,ENABLE);
	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	


}

void MyDMA_Init(uint32_t AddrA,uint32_t AddrB,uint16_t Size)
{
	MySize = Size;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE); //����DMAʱ��
	
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_MemoryBaseAddr=AddrA; //�ڴ��ַ
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord; //�ڴ����ݿ��
	DMA_InitStructure.DMA_PeripheralBaseAddr=AddrB; //�����ַ
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord; //�������ݿ��
	DMA_InitStructure.DMA_BufferSize=Size; //��������ݵ�λ
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralDST; //���ݵķ��� DST(���赽�ڴ�) SRC(�ڴ浽����)
	DMA_InitStructure.DMA_M2M=DMA_M2M_Enable;
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Enable; //����Ĵ����Ƿ�����
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable; //�ڴ�Ĵ����Ƿ�����
	DMA_InitStructure.DMA_Mode=DMA_Mode_Circular; //����ģʽ
	DMA_InitStructure.DMA_Priority=DMA_Priority_High; //�������ȼ�
	
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1,DISABLE);
}

void MyDMA_FlagStatus(void)
{
	DMA_Cmd(DMA1_Channel1,DISABLE); //�ر�DMA
	DMA_SetCurrDataCounter(DMA1_Channel1,MySize); //�Զ���װ
	DMA_Cmd(DMA1_Channel1,ENABLE); //����DMA
	while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET); //�ж��Ƿ������ݴ������
	DMA_ClearFlag(DMA1_FLAG_TC1); //������������־λ
} 

//�ж��Ƿ������ݴ���
uint8_t Serial_GetAddr(void)
{
	if(RxAddr == 1)
	{
		RxAddr=0;
		return 1;
	}
	return 0;
}

/******��װ���ڽ��մ����жϺ���******/
void USART2_IRQHandler(void)
{
	//�����������ڴ�ľ�̬��
	static uint8_t Rxpack = 0; 
	static uint16_t pRxpack = 0;
	
	if(USART_GetITStatus(USART2,USART_IT_RXNE) == SET)
	{
		RxData = USART_ReceiveData(USART2);
		//�ж���ʼλ
		if(Rxpack == 0)
		{
			if(RxData == 0xA5) //����У��,�ֳư�ͷ
			{
				Rxpack = 1;
				pRxpack = 0;
			}
		}
		//���ݴ���
		else if(Rxpack == 1) //��ʽ���봫������
		{
			RxTime[pRxpack] = RxData;
			pRxpack++;
			if(pRxpack >= 11) //�ܹ��ж�������11�͸ĳɶ���[����������������ǵð�У��λҲ����,�����Ŀ������Ͳ�֪����]
			{
				Rxpack = 2;
			}
		}
		//�ж�ֹͣλ
		else if(Rxpack == 2)
		{
			if(RxData == 0x5A) // ����У��,�ֳư�β
			{
				Rxpack = 0;
				RxAddr = 1;
			}
		}
		//�����־λ
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	}
}
