#ifndef __SERTAL_H
#define __SERTAL_H
void Serial_Init(void);
void Serial_SendData(uint8_t Data);//基础串口发送
void Serial_SendAddr(uint8_t *Addr,uint8_t Nean);//数组型串口发送
void MyDMA_Init(uint32_t AddrA,uint32_t AddrB,uint16_t Size); //DMA数据转运初始化
void MyDMA_FlagStatus(void);
uint8_t Serial_GetAddr(void);
extern uint16_t RxTime[];
#endif
