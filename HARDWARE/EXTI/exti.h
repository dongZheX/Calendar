#ifndef __EXTI_H
#define __EXTI_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK��ӢSTM32������
//�ⲿ�ж� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
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
void EXTIX_Init(void);//�ⲿ�жϳ�ʼ��	
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

