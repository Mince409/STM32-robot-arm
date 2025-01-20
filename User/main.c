#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "PWM.h"

//uint16_t Addr[9]; //��������
uint16_t Data; //���ݳ��ر���
uint8_t speed = 25; //�ٶ�ֵ
int i=84,z=117,k=78,w=54; //����ֵ
int Tempi=84,Tempz=117,Tempk=78,Tempw=54; //ֵֹͣ

int main(void)
{
	//ZS���ټ���ֵ,FS��������ֵ
//	int ZS=159,FS=199;
	
	//���ܳ�ʼ��
//	MyDMA_Init((uint32_t)Addr,(uint32_t)RxTime,8); //����DMA��ʼ��Ū�귢��û��
	OLED_Init(); //OLED��ʾ��ʼ��
	Serial_Init(); //����ͨ�ų�ʼ��
	PWM_Init(); //PWM�������ʼ��
	
	while(1)
	{
//		MyDMA_FlagStatus(); //DMA����ת��
		Data = RxTime[10]; //���ݻ���ת�˸�����  �����ȡ���ݵ����ݸ����ʵ���������
		
		//���������ݴ�ӡ��OLED��Ļ��
//		if(Serial_GetAddr() == 1)
//		{
//			OLED_ShowHexNum(1,1,Data,1);
//		}	

	//һ��ȫ���������͵��ֽ����ж�if������ж�������ʵ���������

		//ֹͣ���ж���
		if(Data == 0){
			//ת��
			PWM_A8(Tempk);
			//���
			PWM_A9(Tempi);
			//С��
			PWM_A10(Tempz);
			//צ��
			PWM_A11(Tempw);
		}
		//ת��
		if(Data == 9){
			if(k<=180){
				k+=1;
				PWM_A8(k);
				Tempk=k;
				Delay_ms(speed);
			}
			else continue;
		}
		//
		else if(Data == 2){
			if(k>=-16){
				k-=1;
				PWM_A8(k);
				Tempk=k;
				Delay_ms(speed);
			}
			else continue;
			
			//PWM_A8(FS);
		}
		//���
		else if(Data == 3){
			if(i<=180){
				i+=1;
				PWM_A9(i);
				Tempi=i;
				Delay_ms(speed);
			}
			else continue;
		}
		//
		else if(Data == 4){	
			if(i>=-16){
				i-=1;
				PWM_A9(i);
				Tempi=i;
				Delay_ms(speed);
			}
			else continue;
		}
		//С��
		else if(Data == 5){
			if(z<=180){
				z+=1;
				PWM_A10(z);
				Tempz=z;
				Delay_ms(speed);
			}
			else continue;
		}
		//
		else if(Data == 6){
			if(z>=-16){
				z-=1;
				PWM_A10(z);
				Tempz=z;
				Delay_ms(speed);
			}
			else continue;
		}
		//צ��
		else if(Data == 7){
			if(w>=-16){
				w-=1;
				PWM_A11(w);
				Tempw=w;
				Delay_ms(20);
			}
			else continue;
			
			//PWM_A11(260);
		}
		//
		else if(Data == 8){
			if(w<=180){
				w+=1;
				PWM_A11(w);
				Tempw=w;
				Delay_ms(20);
			}
			else continue;
			
			//PWM_A11(80);
		}			
	}
}
