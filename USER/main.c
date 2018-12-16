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
 ALIENTEK精英STM32开发板实验15
 RTC实时时钟实验  
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/


 
 int main(void)
 {			    
	int count=256;
	u8 temperature;  	   //温度   
	u8 humidity; 					//湿度
  u8 t_rtc = 0;	 				//时间刷新率
 	u8 t=0;								//温度刷新率
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
	usart3_init(115200);
	LCD_Init();
  LED_Init();		  		//初始化与LED连接的硬件接口	
		 
	ISD_Init();
	ISD1760_config();
	usmart_dev.init(SystemCoreClock/1000000);	//初始化USMART	
	EXTIX_Init();         	//初始化外部中断输入 
	RTC_Init();	  			//RTC初始化
	Remote_Init();
	 
	while(DHT11_Init())	//DHT11初始化	
	{
		LCD_ShowString(30,130,200,16,16,"DHT11 Error");
		delay_ms(200);
		LCD_Fill(30,130,239,130+16,WHITE);
 		delay_ms(200);
	}
	POINT_COLOR=BLUE;//设置字体为蓝色
	while(count--){
		LCD_ShowString(60,148,200,16,16,"Init........");
	}
	LCD_Clear(WHITE);
	POINT_COLOR=BLACK;//设置字体为黑色
	LCD_ShowString(30,80,200,16,16,"Welcome to Our Calendar!");
	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(80,130,200,16,16,"    -  -  ");	   
	LCD_ShowString(80,172,200,16,16,"  :  :  ");		
	//								   
	POINT_COLOR=BLUE;//设置字体为蓝色 
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
		if(t%10==0)			//每100ms读取一次
		{									  
			DHT11_Read_Data(&temperature,&humidity);	//读取温湿度值					    
			LCD_ShowNum(80+40,190,temperature,2,16);	//显示温度	   		   
			LCD_ShowNum(80+40,210,humidity,2,16);		//显示湿度	 	   
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

