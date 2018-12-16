#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "rtc.h"
#include "lcd.h"
#include "remote.h"
#include "beep.h"
#include "usart3.h"
#include "calendar.h"
#include "delay.h"
#include "Isd.h"
#include<stdlib.h>
//Íâ²¿ÖĞ¶Ï0·şÎñ³ÌĞ
time my_time;
int mymonth[] = {0,32,29,32,31,32,31,32,32,31,32,31,32};
int max[] = {9999,12,0,24,60,60};
void EXTIX_Init(void)
{
 
   	EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;
    KEY_Init();	 //	°´¼ü¶Ë¿Ú³õÊ¼»¯
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//Ê¹ÄÜ¸´ÓÃ¹¦ÄÜÊ±ÖÓ
   //GPIOE.3	  ÖĞ¶ÏÏßÒÔ¼°ÖĞ¶Ï³õÊ¼»¯ÅäÖÃ ÏÂ½µÑØ´¥·¢ //KEY1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);	  	//¸ù¾İEXTI_InitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèEXTI¼Ä´æÆ÷
   //GPIOE.4	  ÖĞ¶ÏÏßÒÔ¼°ÖĞ¶Ï³õÊ¼»¯ÅäÖÃ  ÏÂ½µÑØ´¥·¢	//KEY0
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_Init(&EXTI_InitStructure);	  	//¸ù¾İEXTI_InitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèEXTI¼Ä´æÆ÷
   //GPIOA.0	  ÖĞ¶ÏÏßÒÔ¼°ÖĞ¶Ï³õÊ¼»¯ÅäÖÃ ÉÏÉıÑØ´¥·¢ PA0  WK_UP
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); 
  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_Init(&EXTI_InitStructure);		//¸ù¾İEXTI_InitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèEXTI¼Ä´æÆ÷
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//Ê¹ÄÜ°´¼üWK_UPËùÔÚµÄÍâ²¿ÖĞ¶ÏÍ¨µÀ
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//ÇÀÕ¼ÓÅÏÈ¼¶2£¬ 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//×ÓÓÅÏÈ¼¶3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//Ê¹ÄÜÍâ²¿ÖĞ¶ÏÍ¨µÀ
  	NVIC_Init(&NVIC_InitStructure); 
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//Ê¹ÄÜ°´¼üKEY1ËùÔÚµÄÍâ²¿ÖĞ¶ÏÍ¨µÀ
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//ÇÀÕ¼ÓÅÏÈ¼¶2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//×ÓÓÅÏÈ¼¶1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//Ê¹ÄÜÍâ²¿ÖĞ¶ÏÍ¨µÀ
  	NVIC_Init(&NVIC_InitStructure);  	  //¸ù¾İNVIC_InitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèNVIC¼Ä´æÆ÷
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//Ê¹ÄÜ°´¼üKEY0ËùÔÚµÄÍâ²¿ÖĞ¶ÏÍ¨µÀ
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//ÇÀÕ¼ÓÅÏÈ¼¶2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//×ÓÓÅÏÈ¼¶0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//Ê¹ÄÜÍâ²¿ÖĞ¶ÏÍ¨µÀ
  	NVIC_Init(&NVIC_InitStructure);  	  //¸ù¾İNVIC_InitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèNVIC¼Ä´æÆ÷
 
}

//Íâ²¿ÖĞ¶Ï0·şÎñ³ÌĞò 
void EXTI0_IRQHandler(void)
{

	myusart my1;
	PLAY_NUM(1);
	reSet();//Çå³ı½ÓÊÕµ½ÓĞĞ§°´¼ü±êÊ¶	
	my1.usart = USART1;
	my1.sta = &(USART_RX_STA);
	my1.buf = USART_RX_BUF;
	funcTionMenu(my1);
	EXTI_ClearITPendingBit(EXTI_Line0); //Çå³ıLINE0ÉÏµÄÖĞ¶Ï±êÖ¾Î» 
}
 

//Íâ²¿ÖĞ¶Ï3·şÎñ³ÌĞò
void EXTI3_IRQHandler(void)
{
	myusart my1;
	reSet();//Çå³ı½ÓÊÕµ½ÓĞĞ§°´¼ü±êÊ¶

	my1.usart = USART3;
	my1.sta = &(USART3_RX_STA);
	my1.buf = USART3_RX_BUF;
	funcTionMenu(my1);
	EXTI_ClearITPendingBit(EXTI_Line3); //Çå³ıLINE0ÉÏµÄÖĞ¶Ï±êÖ¾Î
}

void EXTI4_IRQHandler(void)
{
	u8 key;
	int flag = 0;
	myusart my;
	int y = calendar.w_year, m = calendar.w_month;
	LCD_Clear(WHITE);
	InitPosition();
 	my.usart = USART3;
	my.sta = &(USART3_RX_STA);
	my.buf = USART3_RX_BUF;
	show(y, m);
	while(1){
		key=Remote_Scan();
		switch(key)
			{	  
				case 194:{
					m ++;
					if(m == 13){
						y ++;
						m = 1;
					}
					LCD_Clear(WHITE);
					delay_ms(500);
					show(y, m);
				};
				break;	   
				case 34:{
					m --;
					if(m == 0){
						y --;
						m = 12;
					}
					LCD_Clear(WHITE);
					delay_ms(100);
					show(y, m);
				};
				break;	
				case 2:setPresent(my,&y,&m);show(y,m);break;
				case 82:backToMain(); flag = 1;break;		
				case 226:{
					RTC_Get();
					LCD_Clear(WHITE);
					show(calendar.w_year,calendar.w_month);
				}
			}
			delay_ms(1000);
			if(flag) break;
	}
	EXTI_ClearITPendingBit(EXTI_Line4);
}
 //×Ö·û×ª»¯ÎªÊı×Ö
void funcTionMenu(myusart m){
	u8 key;
	int flag = 0;
	//printf("ÇëÊäÈëÊ±¼ä,ÒÔ»Ø³µ¼ü½áÊø\n");
	LCD_Clear(WHITE);
	POINT_COLOR=BLUE;//ÉèÖÃ×ÖÌåÎªÀ¶É«
	LCD_ShowString(30,80,200,16,12, "1: date");
	LCD_ShowString(30,100,200,16,12, "2: time");
	LCD_ShowString(30,120,200,16,12, "3: alarm");
	LCD_ShowString(30,140,200,16,12, "4: setTime");
	delay_ms(10);   
	while(1)
	{
		
		key=Remote_Scan();	
		if(key)
		{	 	  
			switch(key)
			{
				case 104:flag=alterDate(m); break;		  
				case 152:flag=alterTime(m);break;	   
				case 176:flag=setAlarm(m);break;
				case 48: flag=setTime();break;
				case 82:flag = 1;break;		 
			}
	  }
		if(flag == 1)
			break;
	}
	backToMain();
}
int str2int(char* str)
{
    int temp = 0;
    const char* p = str;
    if(str == NULL) return 0;
    if(*str == '-' || *str == '+')
    {
        str ++;
    }
    while( *str != 0)
    {
        if( *str < '0' || *str > '9')
        {
            break;
        }
        temp = temp*10 +(*str -'0');
        str ++;
    }
    if(*p == '-')
    {
       temp = -temp;

    }
    return temp;
}

void backToMain(){
	LCD_Clear(WHITE);
	LCD_ShowString(30,80,200,16,16,"Welcome to Our Calendar!");
	LCD_ShowString(80,130,200,16,16,"    -  -  ");	   
	LCD_ShowString(80,172,200,16,16,"  :  :  ");		
	LCD_ShowString(80,190,200,16,16,"Temp:  C");	 
	LCD_ShowString(80,210,200,16,16,"Humi:  %");	
}
//ĞŞ¸Äµ±Ç°ÈÕÆÚ
int alterDate(myusart my){
	u16 t;
	u16 len;	
	u16 times=0;
	u32 h,m,s;
	u8 key;
	int count=100;
	char** result;
	printf("ÇëÊäÈëÈÕÆÚ£¬ÒÔ»Ø³µ¼ü½áÊø\n");
	LCD_Clear(WHITE);
	LCD_ShowString(30,80,200,16,12,"Please Input the date:");
	LCD_ShowString(30,100,200,16,12,"like 2018,10,21");
	while(1)
	{
		if(*my.sta&0x8000)
		{					   
			len=*my.sta&0x3fff;//µÃµ½´Ë´Î½ÓÊÕµ½µÄÊı¾İ³¤¶È
			printf("\r\nÄú·¢ËÍµÄÏûÏ¢Îª:\r\n\r\n");
			for(t=0;t<len;t++)
			{
				USART_SendData(my.usart, my.buf[t]);//Ïò´®¿Ú1·¢ËÍÊı¾İ
				while(USART_GetFlagStatus(my.usart,USART_FLAG_TC)!=SET);//µÈ´ı·¢ËÍ½áÊø
			}
			result = split((char*)my.buf,",");
			h = calendar.hour;
			m = calendar.min;
			s = calendar.sec;
			RTC_Set(str2int(result[0]),str2int(result[1]),str2int(result[2]),h,m,s);
			printf("\r\n\r\n");//²åÈë»»ĞĞ
			*my.sta=0;
			LCD_Clear(WHITE);
			clear(len,my.buf);
			while(count--){	
				LCD_ShowString(60,148,200,16,16,"Setting........");
			}
			return 1;
		}else
		{
			times++;  
			if(times%30==0)LED0=!LED0;//ÉÁË¸LED,ÌáÊ¾ÏµÍ³ÕıÔÚÔËĞĞ.
			delay_ms(10);   
		}
		key=Remote_Scan();	
		if(key)
		{	 	  
			switch(key)
			{
				case 82:reSet();return 0;		 
			}
	  }
	}
}

//ĞŞ¸Äµ±Ç°Ê±¼ä
int alterTime(myusart my){
//ÉèÖÃÄÖÖÓ
	u16 t;
	u16 len;	
	u16 times=0;
	u32 h,m,s;
	u8 key;
	int count = 100;
	char** result;
	printf("ÇëÊäÈëÊ±¼ä£¬ÒÔ»Ø³µ½áÊø:");
	LCD_Clear(WHITE);
	LCD_ShowString(30,80,200,16,12,"Please Input the time:");
	LCD_ShowString(30,100,200,16,12,"like 15,12,12");
	while(1)
	{
		if(*my.sta&0x8000)
		{					   
			len=*my.sta&0x3fff;//µÃµ½´Ë´Î½ÓÊÕµ½µÄÊı¾İ³¤¶È
			printf("\r\nÄú·¢ËÍµÄÏûÏ¢Îª:\r\n\r\n");
			for(t=0;t<len;t++)
			{
				USART_SendData(my.usart, my.buf[t]);//Ïò´®¿Ú1·¢ËÍÊı¾İ
				while(USART_GetFlagStatus(my.usart,USART_FLAG_TC)!=SET);//µÈ´ı·¢ËÍ½áÊø
			}
			result = split((char*)my.buf,",");
			h = calendar.w_year;
			m = calendar.w_month;
			s = calendar.w_date;
			RTC_Set(h,m,s,str2int(result[0]),str2int(result[1]),str2int(result[2]));
			clear(len,my.buf);
			printf("\r\n\r\n");//²åÈë»»ĞĞ
			*my.sta=0;
			LCD_Clear(WHITE);
			while(count--){	
				LCD_ShowString(60,148,200,16,16,"Setting........");
			}
			return 1;
		}else
		{
			times++;  
			if(times%30==0)LED0=!LED0;//ÉÁË¸LED,ÌáÊ¾ÏµÍ³ÕıÔÚÔËĞĞ.
			delay_ms(10);   
		}
		key=Remote_Scan();	
		if(key)
		{	 	  
			switch(key)
			{
				case 82:reSet();return 0;	 
			}
	  }
	}
}
int setAlarm(myusart my){
	u16 t;  
	u16 len;	
	u16 times=0;
	u8 key;
	int count=100;
	char** result;
	delay_ms(10);//Ïû¶¶
	printf("ÇëÊäÈëÊµÊ±¼äÒÔÉèÖÃÄÖÖÓ,ÒÔ»Ø³µ¼ü½áÊø\n");
	LCD_Clear(WHITE);
	POINT_COLOR=BLUE;//ÉèÖÃ×ÖÌåÎªÀ¶É«
	LCD_ShowString(20,80,200,16,12,"Please Input the time to set alarm:");
	LCD_ShowString(20,100,250,16,12,"like 2018,10,21,15,12,1");
	delay_ms(10);   
	while(1)
	{
		if(*my.sta&0x8000)
		{					   
			len=*my.sta&0x3fff;//µÃµ½´Ë´Î½ÓÊÕµ½µÄÊı¾İ³¤¶È
			printf("\r\nÄú·¢ËÍµÄÏûÏ¢Îª:\r\n\r\n");
			for(t=0;t<len;t++)
			{
				USART_SendData(my.usart, my.buf[t]);//Ïò´®¿Ú1·¢ËÍÊı¾İ
				while(USART_GetFlagStatus(my.usart,USART_FLAG_TC)!=SET);//µÈ´ı·¢ËÍ½áÊø
			}
			result = split((char*)my.buf,",");
			RTC_Alarm_Set(str2int(result[0]),str2int(result[1]),str2int(result[2]),str2int(result[3]),str2int(result[4]),str2int(result[5]));
			printf("\r\n\r\n");//²åÈë»»ĞĞ
			*my.sta=0;
			clear(len,my.buf);
			LCD_Clear(WHITE);
			while(count--){	
				LCD_ShowString(60,148,200,16,16,"Setting........");
			}
			return 1;
		}else
		{
			times++;  
			if(times%30==0)LED0=!LED0;//ÉÁË¸LED,ÌáÊ¾ÏµÍ³ÕıÔÚÔËĞĞ.
			delay_ms(10);   
		}		
		key=Remote_Scan();	
		if(key)
		{	 	  
			switch(key)
			{
				case 82:reSet();return 0;		 
			}
	  }	 
	}
}
void setPresent(myusart my,int *y, int *m){
	u16 t;
	u16 len;	
	u16 times=0;
	u8 key;
	int count=100;
	char** result;
	printf("ÇëÊäÈëÈÕÆÚ£¬ÒÔ»Ø³µ¼ü½áÊø\n");
	LCD_Clear(WHITE);
	LCD_ShowString(30,80,200,16,12,"Please Input the date:");
	LCD_ShowString(30,100,200,16,12,"like 2018,10Q");
	while(1)
	{
		if(*my.sta&0x8000)
		{					   
			len=*my.sta&0x3fff;//µÃµ½´Ë´Î½ÓÊÕµ½µÄÊı¾İ³¤¶È
			printf("\r\nÄú·¢ËÍµÄÏûÏ¢Îª:\r\n\r\n");
			for(t=0;t<len;t++)
			{
				USART_SendData(my.usart, my.buf[t]);//Ïò´®¿Ú1·¢ËÍÊı¾İ
				while(USART_GetFlagStatus(my.usart,USART_FLAG_TC)!=SET);//µÈ´ı·¢ËÍ½áÊø
			}
			result = split((char*)my.buf,",");
			*y = str2int(result[0]);
			*m = str2int(result[1]);
			printf("\r\n\r\n");//²åÈë»»ĞĞ
			*my.sta=0;
			clear(len,my.buf);
			LCD_Clear(WHITE);
			while(count--){	
				LCD_ShowString(60,148,200,16,16,"Setting........");		
			}
			LCD_Clear(WHITE);
			break;
		}else
		{
			times++;  
			if(times%30==0)LED0=!LED0;//ÉÁË¸LED,ÌáÊ¾ÏµÍ³ÕıÔÚÔËĞĞ.
			delay_ms(10);   
		}
		key=Remote_Scan();	
		if(key)
		{	 	  
			switch(key)
			{
				case 82:reSet();break;		 
			}
	  }
	}
}
void clear(int len, u8* buf){
	int i;
	for(i=0;i<len;i++)
		buf[i] = '\0';
}

int setTime(){
	int index = 0;
	int flag = 0;
	int count = 100;
	u8 key;
	my_time.year = calendar.w_year;
	my_time.month = calendar.w_month;
	my_time.date = calendar.w_date;
	my_time.hour = calendar.hour;
	my_time.min = calendar.min;
	my_time.sec = calendar.sec;
	LCD_Clear(WHITE);
	LCD_ShowString(80,130,200,16,16,"    -  -  ");	   
	LCD_ShowString(80,172,200,16,16,"  :  :  ");
	LCD_ShowNum(80,130,my_time.year,4,16);									  
	LCD_ShowNum(120,130,my_time.month,2,16);									  
	LCD_ShowNum(144,130,my_time.date,2,16);
	LCD_ShowNum(80,172,my_time.hour,2,16);									  
	LCD_ShowNum(104,172,my_time.min,2,16);									  
	LCD_ShowNum(128,172,my_time.sec,2,16);
	
	while(1){
		switch(index){
		case 0: set(80, 130, index);break;
		case 1: set(120, 130, index);break;
		case 2: set(144, 130, index);break;
		case 3: set(80, 172, index);break;
		case 4: set(104, 172, index);break;
		case 5: set(128, 172, index);break;
		}
		key = Remote_Scan();
		switch(key)
		{	  
				case 194:index=(index+1)%6;break;	   
				case 34: if(--index == -1) index = 5;break;	
				case 98: modify(1,index);break;
				case 168:modify(0,index);break;
				case 2:RTC_Set(my_time.year, my_time.month, my_time.date, my_time.hour, my_time.min, my_time.sec);flag=1; break;
				case 82:backToMain();flag=1;break;			
		}
		delay_ms(10);
		reSet();
		if(flag){
			LCD_Clear(WHITE);
			while(count--){	
				LCD_ShowString(60,148,200,16,16,"Setting........");
			}
			return 1;
		}
	}
}

void set(int x, int y, int index){
	int change = index==0?30:16;
	LCD_Fill(x,y,x+change,y+16,WHITE);
	delay_ms(500);
	LCD_Fill(x,y,x+change,y+16,WHITE);
	switch(index){
		case 0: LCD_ShowNum(x,y,my_time.year,4,16);break;
		case 1: LCD_ShowNum(x,y,my_time.month,2,16);break;
		case 2: LCD_ShowNum(x,y,my_time.date,2,16);break;
		case 3: LCD_ShowNum(x,y,my_time.hour,2,16);break;
		case 4: LCD_ShowNum(x,y,my_time.min,2,16);break;
		case 5: LCD_ShowNum(x,y,my_time.sec,2,16);break;
	}
	delay_ms(300);
}

void modify(int flag, int index){
	if(isRunNian(my_time.year))mymonth[2] = 30;
	else mymonth[2] = 29;
	max[2] = mymonth[my_time.month];
	if(flag){
		switch(index){
			case 0: my_time.year = (my_time.year+1)%max[index];break;
			case 1: my_time.month = (my_time.month+1)%max[index];break;
			case 2: my_time.date = (my_time.date+1)%max[index]; if(my_time.date == 0) my_time.date = 1;break;
			case 3: my_time.hour = (my_time.hour+1)%max[index];break;
			case 4: my_time.min = (my_time.min+1)%max[index];break;
			case 5: my_time.sec = (my_time.sec+1)%max[index];break;
		}
	}
	else{
		switch(index){
			case 0: my_time.year = (my_time.year-1)<0?0:(my_time.year-1);break;
			case 1: my_time.month = (my_time.month-1)<1?12:(my_time.month-1);break;
			case 2: my_time.date = (my_time.date-1)<1?mymonth[my_time.month]:(my_time.date-1);break;
			case 3: my_time.hour = (my_time.hour-1)<0?23:(my_time.hour-1);break;
			case 4: my_time.min = (my_time.min-1)<0?59:(my_time.min-1);break;
			case 5: my_time.sec = (my_time.sec-1)<0?59:(my_time.sec-1);break;
		}	
	}
}

