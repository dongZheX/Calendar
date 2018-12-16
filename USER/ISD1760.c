#include "ISD1760.h"
#include "sys.h"
#define GPIO_ISD1760                   GPIOA    /*???GPIO??*/
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
//SPI?????1700??,nSS=1; SCLK=1; MOSI=0;
#define RCC_GPIO_ISD1760                    RCC_APB2Periph_GPIOD 													
uint8_t SR0_L;				//?????0????
uint8_t SR0_H; 				//?????0????
uint8_t SR1; 				//?????1????
uint8_t ID;
uint8_t APCL;
uint8_t APCH;		//??ID?APC????APC??? 

//------------------------------------------------------------ 
uint16_t caToneA[8]={0x0010,0x0028,  0x0029,0x0042,  0x0043,0x0059,  0x0060,0x0074};	//0x0010?????
//---------------------------------------------------------------

//---------------------------------------------------------------
void delayus(void)
{
   //while(k--);//??15us \
   while(2--);
}

void Delay(uint16_t z)
{
	uint16_t x,y;
	for(x=z;x>0;x--) //7us
		for(y=185;y>0;y--);	//990us,????? 1ms ?
}
//---------------------------------------------------------------// 
//??? : SPISendData( ) 
//????:SPI????(????)???---???? ???? 
//---------------------------------------------------------------
uint8_t SPISendData(uint8_t BUF_ISD) 
{ 
	uint8_t i,dat;
	
	dat  = BUF_ISD;				//???ISD1760??? 
	SCLK_1;			
	nSS_0;	//????????,???SPI

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
		if(GPIO_ReadInputDataBit(GPIO_ISD1760, MISO))		//??CPU????ISD1760??? 
		{ 
			dat|=0x80; 	//1700 ??,????? ,????
		} 				//?????????0,??CPU???1,?????1,??????????
		SCLK_1;; 		//?????
		delayus();; 
	} 
	MOSI_0;				//??????,IO????? ? ?? 
	// nSS=1; 
	return(dat); 
}
/************************************************************************** 
* ????: void RdStatus(void); 
* ??: ???? 
**************************************************************************/ 
void RdStatus(void) 
{ 
	nSS_0;
	SPISendData(RD_STATUS);				//??????????? 
	SPISendData(0x00);					//??????????????????????						 
	SPISendData(0x00); 
	nSS_1; 
	Delay(10); 							//??10ms
	nSS_0;						 
	SR0_L 	=SPISendData(RD_STATUS); 
	SR0_H 	=SPISendData(0x00); 
	SR1 	=SPISendData(0x00); 
	nSS_1; 
	Delay(10); 
} 

/************************************************************************** 
* ????: void ClrInt(void); 
* ??: ???? 
**************************************************************************/ 
void ClrInt(void) 
{ 
	nSS_0;
	SPISendData(CLI_INT);				//?????EOM? 
	SPISendData(0x00); 
	nSS_1;
	Delay(10); 
} 

/************************************************************************** 
* ????: void ISD_WR_NVCFG(void); 
* ??: ??????? 
**************************************************************************/ 
void ISD_WR_NVCFG(void) 
{ 
	nSS_0;
	SPISendData(WR_NVCFG);				//?APC?????NVCFG;??????? 
	SPISendData(0x00); 
	nSS_1; 
	Delay(10); 
} 

/************************************************************************** 
* ????: void ISD_WR_APC2(uchar voiceValue); 
* ??: ??APC2 
**************************************************************************/ 
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

/************************************************************************** 
* ????: void RD_APC(void); 
* ??: ??APC 
**************************************************************************/ 
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

/************************************************************************** 
* ????: void ISD_Init(void); 
* ??: ??? 
**************************************************************************/ 
void ISD_Init(void) 
{ 
	ISD_Reset();	//??: ?? 
	do 
	{ 
		ISD_PU();	//??: ?? 
		RdStatus();	//??: ???? 
	}
	while((SR0_L&0x01)||(!(SR1&0x01))); //if(SR0_L^0==1){system Err}<CMD_Err==1> 
	
	ClrInt();		//??: ???? 
	ISD_WR_APC2();	//??: ??APC2 
	RdAPC(); 		//??: ??APC
} 

/************************************************************************** 
* ????: void ISD_CHK_MEM(void); 
* ??: ???? 
**************************************************************************/ 
void ISD_CHK_MEM(void) 
{ 
	nSS_0;
	SPISendData(CHK_MEM);	//??????????? 
	SPISendData(0x00); 
	nSS_1;
	Delay(10); 
} 

/************************************************************************** 
* ????: void ISD_Reset(void); 
* ??: ?? 
**************************************************************************/ 
void ISD_Reset(void) 
{ 
	nSS_0;
	SPISendData(RESET);		//?? 
	SPISendData(0x00); 
	nSS_1; 
	Delay(50); 
} 

/************************************************************************** 
* ????: void ISD_Stop(void); 
* ??: ?? 
**************************************************************************/ 
void ISD_Stop(void) 
{ 
	nSS_0;
	SPISendData(STOP);	//?????? 
	SPISendData(0x00); 
	nSS_1; 
	Delay(50); 
} 

/************************************************************************** 
* ????: void ISD_PU(void); 
* ??: ?? 
**************************************************************************/ 
void ISD_PU(void) 
{ 
	nSS_0;
	SPISendData(PU);	//Power up ???? 
	SPISendData(0x00); 
	nSS_1; 
	Delay(50); 
} 
/************************************************************************** 
* ????: void ISD_PD(void); 
* ??: ?? 
**************************************************************************/ 
void ISD_PD(void) 
{ 
	nSS_0;
	SPISendData(PD);	//Power down ?? 
	SPISendData(0x00); 
	nSS_1;
	Delay(10); 
} 
/************************************************************************** 
* ????: void RdStatus(void); 
* ??: ??ID 
**************************************************************************/ 
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

/************************************************************************** 
* ????: void GetToneAdd(uchar cNum, Uint * ipStartAdd, Uint * ipEndAdd); 
* ??: ???????????					(????) 
**************************************************************************/ 
void GetToneAdd(uint8_t cNum, uint16_t *ipStartAdd, uint16_t *ipEndAdd) 
{ 
	*ipStartAdd=caToneA[cNum*2];	//???????? =  ????????????
	*ipEndAdd=caToneA[cNum*2+1]; 
} 

/************************************************************************** 
* ????: void SetPLAY(uchar cNum) 
* ??: ????								(????) 
**************************************************************************/ 
void SetPLAY(uint8_t cNum) 
{ 
	uint16_t Add_ST, Add_ED;	//????,???? 
	uint8_t Add_ST_H, Add_ST_L, Add_ED_H, Add_ED_L;
//?????8?,?????8?,?????8?,?????8?	 
	do 
	{ 
		RdStatus();		//??: ???? 
	}
	while((SR0_L&0x01)||(!(SR1&0x01))); 	//if(SR0_L^0==1){system Err}<CMD_Err==1> 
	
	ClrInt();  			//??: ????
	GetToneAdd(cNum, &Add_ST, &Add_ED);		//??: ??????????? 
	Add_ST_L=(uint8_t)(Add_ST&0x00ff); 		//?????8?
	Add_ST_H=(uint8_t)((Add_ST>>8)&0x00ff); 	//?????8?
	Add_ED_L=(uint8_t)(Add_ED&0x00ff); 		//?????8?
	Add_ED_H=(uint8_t)((Add_ED>>8)&0x00ff); 	//?????8?

	nSS_0;
	SPISendData(SET_PLAY);		//?<S10:S0>????,??<E10:E0>?EOM 
	SPISendData(0x00); 
	SPISendData(Add_ST_L); 		//S7:S0 ???? 
	SPISendData(Add_ST_H); 		//S10:S8 
	SPISendData(Add_ED_L); 		//E7:E0 ???? 
	SPISendData(Add_ED_H); 		//E10:E8 
	SPISendData(0x00); 
	nSS_1; 

	Delay(10);             		//??10ms 
	
	do 
	{ 
		RdStatus();				//??: ???? 
	}
	while((SR0_L&0x01)||((SR1&0x04))); // 0x04? if(SR0_L^0==1){system Err}<CMD_Err==1> 
} 

/************************************************************************** 
* ????: void SetREC(uchar cNum); 
* ??: ???? 
**************************************************************************/ 
void SetREC(uint8_t cNum) 
{ 
	uint16_t Add_ST, Add_ED; 
	uint8_t Add_ST_H, Add_ST_L, Add_ED_H, Add_ED_L; 
	
	do 
	{ 
		RdStatus();			//??: ???? 
	}
	while((SR0_L&0x01)|(!(SR1&0x01))); //if(SR0_L^0==1){system Err}<CMD_Err==1> 

	ClrInt(); 				//??: ????
	GetToneAdd(cNum, &Add_ST, &Add_ED);		//??: ??????????? 
	Add_ST_L=(uint8_t)(Add_ST&0x00ff); 
	Add_ST_H=(uint8_t)((Add_ST>>8)&0x00ff); 
	Add_ED_L=(uint8_t)(Add_ED&0x00ff); 
	Add_ED_H=(uint8_t)((Add_ST>>8)&0x00ff); 

	nSS_0;
	SPISendData(SET_REC);	//?<S10:S0>????,??<E10:E0> 
	SPISendData(0x00); 
	SPISendData(Add_ST_L); 	//S7:S0 ???? 
	SPISendData(Add_ST_H); 	//S10:S8 
	SPISendData(Add_ED_L); 	//E7:E0 ???? 
	SPISendData(Add_ED_H); 	//E10:E8 
	SPISendData(0x00); 
	
	nSS_1;
	Delay(10); 				//??10ms 
	do 
	{ 
		RdStatus();			//??: ???? 
	}
	while((SR0_L&0x01)||(!(SR1&0x01))); //if(SR0_L^0==1){system Err}<CMD_Err==1> 
} 

/************************************************************************** 
* ????: void Erase_All(void); 
* ??: ???? 
**************************************************************************/ 
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

  RCC_APB2PeriphClockCmd(RCC_GPIO_ISD1760,ENABLE);				  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4;	
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  RCC_APB2PeriphClockCmd(RCC_GPIO_ISD1760,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;									
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;				
  GPIO_Init(GPIOA, &GPIO_InitStructure);					

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;										
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;					
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOF, &GPIO_InitStructure);							
}

















