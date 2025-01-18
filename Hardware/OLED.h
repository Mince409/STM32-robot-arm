#ifndef __OLED_H
#define __OLED_H

void OLED_Init(void);//初始化
void OLED_Clear(void);//清屏
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);//OLED显示单个字符
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);//OLED显示字符串
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);//OLED显示数字(十进制,正数)
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);//OLED显示数字(十进制,带符号)
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);//OLED显示数字(十六进制,正数)
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);//OLED显示数字(二进制,正数)

#endif
