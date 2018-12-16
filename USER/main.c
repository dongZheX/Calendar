#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	
#include "usmart.h"	 
#include "rtc.h" 
#include "dht11.h"
#include "exti.h"
#include "usart3.h"
#include "remote.h"
#include "Isd.h"
#include "calendar.h"
#include<stdio.h>
 
/************************************************
 ALIENTEK��ӢSTM32������ʵ��15
 RTCʵʱʱ��ʵ��  
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


 
 int main(void)
 {			    
	int count=256;
	u8 temperature;  	   //�¶�   
	u8 humidity; 					//ʪ��
  u8 t_rtc = 0;	 				//ʱ��ˢ����
 	u8 t=0;								//�¶�ˢ����
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	usart3_init(115200);
	LCD_Init();
  LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�	
		 
	ISD_Init();
	ISD1760_config();
	usmart_dev.init(SystemCoreClock/1000000);	//��ʼ��USMART	
	EXTIX_Init();         	//��ʼ���ⲿ�ж����� 
	RTC_Init();	  			//RTC��ʼ��
	Remote_Init();
	 
	while(DHT11_Init())	//DHT11��ʼ��	
	{
		LCD_ShowString(30,130,200,16,16,"DHT11 Error");
		delay_ms(200);
		LCD_Fill(30,130,239,130+16,WHITE);
 		delay_ms(200);
	}
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	while(count--){
		LCD_ShowString(60,148,200,16,16,"Init........");
	}
	LCD_Clear(WHITE);
	POINT_COLOR=BLACK;//��������Ϊ��ɫ
	LCD_ShowString(30,80,200,16,16,"Welcome to Our Calendar!");
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	LCD_ShowString(80,130,200,16,16,"    -  -  ");	   
	LCD_ShowString(80,172,200,16,16,"  :  :  ");		
	//								   
	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
 	LCD_ShowString(80,190,200,16,16,"Temp:  C");	 
 	LCD_ShowString(80,210,200,16,16,"Humi:  %");	
	
	//
	while(1)
	{					
		
		if(t_rtc!=calendar.sec)
		{
			t_rtc=calendar.sec;
			LCD_ShowNum(80,130,calendar.w_year,4,16);									  
			LCD_ShowNum(120,130,calendar.w_month,2,16);									  
			LCD_ShowNum(144,130,calendar.w_date,2,16);	 
			switch(calendar.week)
			{
				case 0:
					LCD_ShowString(80,148,200,16,16,"Sunday   ");
					break;
				case 1:
					LCD_ShowString(80,148,200,16,16,"Monday   ");
					break;
				case 2:
					LCD_ShowString(80,148,200,16,16,"Tuesday  ");
					break;
				case 3:
					LCD_ShowString(80,148,200,16,16,"Wednesday");
					break;
				case 4:
					LCD_ShowString(80,148,200,16,16,"Thursday ");
					break;
				case 5:
					LCD_ShowString(80,148,200,16,16,"Friday   ");
					break;
				case 6:
					LCD_ShowString(80,148,200,16,16,"Saturday ");
					break;  
			}
			LCD_ShowNum(80,172,calendar.hour,2,16);									  
			LCD_ShowNum(104,172,calendar.min,2,16);									  
			LCD_ShowNum(128,172,calendar.sec,2,16);
			LED0=!LED0;
		}	
		if(t%10==0)			//ÿ100ms��ȡһ��
		{									  
			DHT11_Read_Data(&temperature,&humidity);	//��ȡ��ʪ��ֵ					    
			LCD_ShowNum(80+40,190,temperature,2,16);	//��ʾ�¶�	   		   
			LCD_ShowNum(80+40,210,humidity,2,16);		//��ʾʪ��	 	   
		}				   
	 	delay_ms(10);
		t++;
		if(t==20)
		{
			t=0;
			LED0=!LED0;
		}
		delay_ms(10);								  
	};  
 }

