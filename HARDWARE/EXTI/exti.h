#ifndef __EXTI_H
#define __EXTI_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK精英STM32开发板
//外部中断 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 
typedef struct myusart{
	USART_TypeDef * usart;
	vu16* sta;
	u8* buf;
}myusart;
typedef struct time{
	int year;
	int month;
	int date;
	int hour;
	int min;
	int sec;
}time;
void EXTIX_Init(void);//外部中断初始化	
int str2int(char* str);
void backToMain(void);
int alterDate(myusart);
int alterTime(myusart);
int setAlarm(myusart);
int setTime();
void set(int x, int y, int index);
void funcTionMenu(myusart);
void setPresent(myusart,int *y, int *m);
void clear(int len, u8* buf);
void modify(int flag, int index);
#endif

