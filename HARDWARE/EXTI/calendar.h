#ifndef __CALENDAR_H
#define __CALENDAR_H	 
#include "sys.h"  
#include "lcd.h"
#include "rtc.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����3��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/3/29
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	  
typedef struct pos{
	int x;
	int y;
}pos;
extern int rili[6][7];
extern pos position[6][7];

int whatTheDay(int y, int m, int d);
int isRunNian(int y);
void generate(int y, int m);
void InitPosition();
void show(int year, int month);
#endif
