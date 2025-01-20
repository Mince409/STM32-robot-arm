#include "stm32f10x.h"                  // Device header
#include "stdarg.h"
#include "OLED.h"
uint16_t RxTime[13]; //存储接收的数据 这个数组负责接收所有数据，根据实际情况更改大小
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
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE); //开启DMA时钟
	
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_MemoryBaseAddr=AddrA; //内存地址
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord; //内存数据宽度
	DMA_InitStructure.DMA_PeripheralBaseAddr=AddrB; //外设地址
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord; //外设数据宽度
	DMA_InitStructure.DMA_BufferSize=Size; //传输的数据单位
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralDST; //数据的方向 DST(外设到内存) SRC(内存到外设)
	DMA_InitStructure.DMA_M2M=DMA_M2M_Enable;
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Enable; //外设寄存器是否自增
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable; //内存寄存器是否自增
	DMA_InitStructure.DMA_Mode=DMA_Mode_Circular; //工作模式
	DMA_InitStructure.DMA_Priority=DMA_Priority_High; //传输优先级
	
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1,DISABLE);
}

void MyDMA_FlagStatus(void)
{
	DMA_Cmd(DMA1_Channel1,DISABLE); //关闭DMA
	DMA_SetCurrDataCounter(DMA1_Channel1,MySize); //自动重装
	DMA_Cmd(DMA1_Channel1,ENABLE); //开启DMA
	while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET); //判断是否有数据传输完成
	DMA_ClearFlag(DMA1_FLAG_TC1); //传输完成清除标志位
} 

//判断是否有数据传入
uint8_t Serial_GetAddr(void)
{
	if(RxAddr == 1)
	{
		RxAddr=0;
		return 1;
	}
	return 0;
}

/******封装串口接收触发中断函数******/
void USART2_IRQHandler(void)
{
	//将变量放在内存的静态区
	static uint8_t Rxpack = 0; 
	static uint16_t pRxpack = 0;
	
	if(USART_GetITStatus(USART2,USART_IT_RXNE) == SET)
	{
		RxData = USART_ReceiveData(USART2);
		//判断起始位
		if(Rxpack == 0)
		{
			if(RxData == 0xA5) //校验位,又称包头
			{
				Rxpack = 1;
				pRxpack = 0;
			}
		}
		//数据传入
		else if(Rxpack == 1) //开始数据传入
		{
			RxTime[pRxpack] = RxData; //将数据传到数组
			pRxpack++;
			if(pRxpack >= 11) //传入数据的数量限制,[我这里用的蓝牙调试器需要把校验位算上]
			{
				Rxpack = 2;
			}
		}
		//判断停止位
		else if(Rxpack == 2)
		{
			if(RxData == 0x5A) //校验位,又称包尾
			{
				Rxpack = 0;
				RxAddr = 1;
			}
		}
		//清除标志位
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	}
}
