#ifndef __SERTAL_H
#define __SERTAL_H
void Serial_Init(void);
void Serial_SendData(uint8_t Data);//�������ڷ���
void Serial_SendAddr(uint8_t *Addr,uint8_t Nean);//�����ʹ��ڷ���
void MyDMA_Init(uint32_t AddrA,uint32_t AddrB,uint16_t Size); //DMA����ת�˳�ʼ��
void MyDMA_FlagStatus(void);
uint8_t Serial_GetAddr(void);
extern uint16_t RxTime[];
#endif
