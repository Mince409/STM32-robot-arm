#ifndef __OLED_H
#define __OLED_H

void OLED_Init(void);//��ʼ��
void OLED_Clear(void);//����
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);//OLED��ʾ�����ַ�
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);//OLED��ʾ�ַ���
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);//OLED��ʾ����(ʮ����,����)
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);//OLED��ʾ����(ʮ����,������)
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);//OLED��ʾ����(ʮ������,����)
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);//OLED��ʾ����(������,����)

#endif
