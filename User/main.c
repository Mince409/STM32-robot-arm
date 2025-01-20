#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "PWM.h"

//uint16_t Addr[9]; //数据数组
uint16_t Data; //数据承载变量
uint8_t speed = 25; //速度值
int i=84,z=117,k=78,w=54; //操作值
int Tempi=84,Tempz=117,Tempk=78,Tempw=54; //停止值

int main(void)
{
	//ZS加速减数值,FS加速增数值
//	int ZS=159,FS=199;
	
	//功能初始化
//	MyDMA_Init((uint32_t)Addr,(uint32_t)RxTime,8); //这是DMA初始化弄完发现没用
	OLED_Init(); //OLED显示初始化
	Serial_Init(); //串口通信初始化
	PWM_Init(); //PWM波输出初始化
	
	while(1)
	{
//		MyDMA_FlagStatus(); //DMA数据转运
		Data = RxTime[10]; //数据缓存转运给变量  数组存取数据的数据格根据实际情况更改
		
		//将串口数据打印在OLED屏幕上
//		if(Serial_GetAddr() == 1)
//		{
//			OLED_ShowHexNum(1,1,Data,1);
//		}	

	//一下全是蓝牙发送的字节数判断if里面的判读数根据实际情况更改

		//停止所有动作
		if(Data == 0){
			//转轴
			PWM_A8(Tempk);
			//大臂
			PWM_A9(Tempi);
			//小臂
			PWM_A10(Tempz);
			//爪子
			PWM_A11(Tempw);
		}
		//转轴
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
		//大臂
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
		//小臂
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
		//爪子
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
