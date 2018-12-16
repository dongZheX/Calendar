#include "isd.h"
#include "delay.h"
#include "lcd.h"
#define GPIO_ISD1760     GPIOE   
													
uint8_t SR0_L;				
uint8_t SR0_H; 				
uint8_t SR1; 				
uint8_t ID;
uint8_t APCL;
uint8_t APCH;		

void delayus(void)
{
  u8 i=2; 
	while(i--);
}

void Delay(uint16_t z)
{
	uint16_t x,y;
	for(x=z;x>0;x--) //7us
		for(y=185;y>0;y--);	
}
uint8_t SPISendData(uint8_t BUF_ISD) 
{
	uint8_t i;
	uint8_t dat = BUF_ISD;
	
	SCLK_1;			
	nSS_0;	

	for(i=0;i<8;i++)	//8???? 
	{ 
		SCLK_0;; 		//0--1,?(CPU)--?(ISD)
		delayus();		//SPI???? 
		if(dat&0x01)	//???? 
		{ 
			MOSI_1; 	//???1700 ?????
		} 
		else 
		{ 
			MOSI_0; 
		} 
		dat>>=1;		 
		if(GPIO_ReadInputDataBit(GPIO_ISD1760, MISO))	
		{ 
			dat|=0x80; 
		} 			
		SCLK_1;; 		//?????
		delayus();; 
	} 
	MOSI_0;				
	// nSS=1; 
	return(dat); 
}

void RdStatus(void) 
{ 
	nSS_0;
	SPISendData(RD_STATUS); 
	SPISendData(0x00); 
	SPISendData(0x00); 
	nSS_1;  
	delay_ms(10);               //ясЁы10ms 
	SR0_L =SPISendData(RD_STATUS); 
	SR0_H =SPISendData(0x00); 
	SR1 =SPISendData(0x00); 
	nSS_1; 
	delay_ms(10);
	/*nSS_0;
	SPISendData(RD_STATUS);				
	SPISendData(0x00);											 
	SPISendData(0x00); 
	nSS_1; 
	Delay(10); 							//??10ms
	nSS_0;						 
	SR0_L 	=SPISendData(RD_STATUS); 
	SR0_H 	=SPISendData(0x00); 
	SR1 	=SPISendData(0x00); 
	nSS_1; 
	Delay(10); */
} 

void ClrInt(void) 
{ 
	nSS_0;
	SPISendData(CLI_INT);				//?????EOM? 
	SPISendData(0x00); 
	nSS_1;
	Delay(10); 
} 

void ISD_WR_NVCFG(void) 
{ 
	nSS_0;
	SPISendData(WR_NVCFG);				//?APC?????NVCFG;??????? 
	SPISendData(0x00); 
	nSS_1; 
	Delay(10); 
} 


void ISD_WR_APC2(void)
{ 
	nSS_0;
	SPISendData(WR_APC2);	//?<D11:D0>?????APC2???,??<D2:D0>????? 
	SPISendData(0x70); 		//0xa8????,0xaf????,0xa0????????? 
	SPISendData(0x0c);	//0c 		
											//D11=1,?SETPLAY???,???EOM????????????SET_PLAY???,??????EOM????????? 
	nSS_1; 
	Delay(10); 
	ISD_WR_NVCFG(); 		//??????? 
} 

void RdAPC(void) 
{ 
	nSS_0;
	SPISendData(RD_APC);	//????????????APC??? 
	SPISendData(0x00); 
	SPISendData(0x00); 
	SPISendData(0x00); 
	nSS_1; 
	Delay(10); //??10ms 
	SR0_L = SPISendData(RD_APC); 
	SR0_H = SPISendData(0x00); 
	APCL  = SPISendData(0x00); 
	APCH  = SPISendData(0x00); 
	nSS_1; 
	Delay(10); 
} 


void ISD_Init(void) 
{ 
	ISD_Reset();	//??: ?? 
	LCD_Clear(WHITE);
	do 
	{ 
		ISD_PU();	//??: ?? 
		RdStatus();	//??: ???? 
		LCD_ShowString(80,190,200,16,16,"ISD_Init");
	}
	while((SR0_L&0x01)||(!(SR1&0x01))); //if(SR0_L^0==1){system Err}<CMD_Err==1> 
	LCD_Clear(WHITE);
	ClrInt();		//??: ???? 
	ISD_WR_APC2();	//??: ??APC2 
	RdAPC(); 		//??: ??APC
} 

void ISD_CHK_MEM(void) 
{ 
	nSS_0;
	SPISendData(CHK_MEM);	//??????????? 
	SPISendData(0x00); 
	nSS_1;
	Delay(10); 
} 
 
void ISD_Reset(void) 
{ 
	nSS_0;
	SPISendData(RESET);		//?? 
	SPISendData(0x00); 
	nSS_1; 
	Delay(50); 
} 

void ISD_Stop(void) 
{ 
	nSS_0;
	SPISendData(STOP);	//?????? 
	SPISendData(0x00); 
	nSS_1; 
	Delay(50); 
} 

void ISD_PU(void) 
{ 
	nSS_0;
	SPISendData(PU);	//Power up ???? 
	SPISendData(0x00); 
	nSS_1; 
	Delay(50); 
} 

void ISD_PD(void) 
{ 
	nSS_0;
	SPISendData(PD);	//Power down ?? 
	SPISendData(0x00); 
	nSS_1;
	Delay(10); 
}

uint8_t RD_DevID(void) 
{ 
	nSS_0;
	SPISendData(DEVID);				//????ID 
	SPISendData(0x00); 
	SPISendData(0x00); 
	nSS_1;
	Delay(10);            //??10ms 
	SR0_L   = SPISendData(DEVID); 
	SR0_H   = SPISendData(0x00); 
	ID      = SPISendData(0x00); 
	nSS_1; 
	Delay(10); 
	return(ID); 
} 

void ISD_PLAY(void) 
{ 
 	LCD_Clear(WHITE);
	do 
	{ 
			
		RdStatus();		//??: ???? 
		LCD_ShowString(30,130,200,16,16,"DHT11 Error");
	}
	while((SR0_L&0x01)||(!(SR1&0x01))); 	//if(SR0_L^0==1){system Err}<CMD_Err==1> 
	LCD_Clear(WHITE);
	ClrInt();  			//??: ????

	nSS_0;
	SPISendData(PLAY);		//??????? 
	SPISendData(0x00); 
	nSS_1; 

	Delay(10);             		//??10ms 
	
	do 
	{ 
		RdStatus();				//??: ???? 
	}
	while((SR0_L&0x01)||((SR1&0x04))); // 0x04? if(SR0_L^0==1){system Err}<CMD_Err==1> 
} 

void ISD_FWD(void)
{
	LCD_Clear(WHITE);
   do 
	{ 
		ISD_PU();
		RdStatus();		//??: ???? 
		LCD_ShowString(80,190,200,16,16,"Temp:  C");	 
	}
	while((SR0_L&0x01)||(!(SR1&0x01)));  	//if(SR0_L^0==1){system Err}<CMD_Err==1> 
	LCD_Clear(WHITE);
	ClrInt();  			//??: ????

	nSS_0;
	SPISendData(FWD);		//??????? 
	SPISendData(0x00); 
	nSS_1; 

	Delay(10);             		//??10ms 
	
	do 
	{ 
		RdStatus();				//??: ???? 
	}
	while((SR0_L&0x01)||((SR1&0x04)));
}

void Erase_All(void) 
{ 
	nSS_0;
	SPISendData(G_ERASE);	//??????????? 
	SPISendData(0x00);	 
	nSS_1;
	Delay(10); 			//??10ms 
}
void ISD1760_config(void)					//??IO????
{
  GPIO_InitTypeDef GPIO_InitStructure;		//?????,????(????????)

  RCC_APB2PeriphClockCmd(RCC_GPIO_ISD1760,ENABLE);				//??GPIO??		  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;	//??		
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
  RCC_APB2PeriphClockCmd(RCC_GPIO_ISD1760,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;								//??		
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;					//??
  GPIO_Init(GPIOE, &GPIO_InitStructure);								/*???GPIO????*/			
}


void PLAY_NUM(u8 i)
{
  i = i+2;
//	 ISD_PLAY();		
//	  delay_ms(100);	
	while(i)
	{	ISD_FWD();      //??????
		delay_ms(100);
		i--;
	}
	ISD_PLAY();		  //????????
	 delay_ms(100);	
	ISD_Reset();    //??,?????,????????????
	
	delay_ms(100);            	
	do 
	{ 
		ISD_PU();   //??
    delay_ms(50);
		RdStatus();				 
	}
	while((SR0_L&0x01)||((SR1&0x04)));////////?????,???,??????????????,????????
}