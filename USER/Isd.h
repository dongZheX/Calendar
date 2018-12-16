#ifndef __ISD1760_H__
#define __ISD1760_H__

#include "stm32f10x_gpio.h"
												
extern uint8_t SR0_L;			
extern uint8_t SR0_H; 			
extern uint8_t SR1; 		
extern uint8_t ID;
extern uint8_t APCL;
extern uint8_t APCH;			

#define RCC_GPIO_ISD1760          RCC_APB2Periph_GPIOE
#define MISO	GPIO_Pin_0		//CPU	 	(IN)
#define MOSI	GPIO_Pin_1		//ISD1760	(OUT)
#define SCLK	GPIO_Pin_2 		
#define nSS		GPIO_Pin_3		//??????
//????SS????,SCLK????,MOSI????

#define SCLK_1		GPIO_SetBits(GPIO_ISD1760, SCLK)	
#define SCLK_0		GPIO_ResetBits(GPIO_ISD1760, SCLK)
#define nSS_1		GPIO_SetBits(GPIO_ISD1760, nSS)
#define nSS_0		GPIO_ResetBits(GPIO_ISD1760, nSS)
#define MOSI_1		GPIO_SetBits(GPIO_ISD1760, MOSI)	
#define MOSI_0		GPIO_ResetBits(GPIO_ISD1760, MOSI)

//?????
#define PU 0x01           	//Power up ????
#define STOP 0x02 			//??????
#define RESET 0x03 			//??
#define CLI_INT 0x04 		//?????EOM?
#define RD_STATUS 0x05 		//???????????
#define RD_PLAY_PTR 0x06 	//????????????????
#define PD 0x07 			//Power down ??
#define RD_REC_PTR 0x08 	//????????????????
#define DEVID 0x09 			//????ID
#define PLAY 0x40 			//??????
#define REC 0x41 			//?????????
#define ERASE 0x42 			//??????
#define G_ERASE 0x43 		//???????????
#define RD_APC 0x44 		//????????????APC???;APC--?????????
#define WR_APC1 0x45 		//?<D11:D0>?????APC1???,??VOL?????
#define WR_APC2 0x65 		//?<D11:D0>?????APC2???,??<D2:D0>?????
#define WR_NVCFG 0x46 		//?APC?????NVCFG;???????
#define LD_NVCFG 0x47 		//?NVCFG?????APC
#define FWD 0x48 			//???
#define CHK_MEM 0x49 		//???????????
#define EXTCLK 0x4A 		//????????
#define SET_PLAY 0x80 		//?<S10:S0>????,??<E10:E0>?EOM
#define SET_REC 0x81 		//?<S10:S0>????,??<E10:E0>
#define SET_ERASE 0x82 		//??<S10:S0>?<E10:E0>???
#define NOP _nop_() 

void delayus(void);							//15us ???
void Delay(uint16_t z );					//??:??MS????,Z????MS? 
uint8_t SPISendData(uint8_t BUF_ISD);		//??: SPI????(????)???
void RdStatus(void);			//??: ????
void ClrInt(void);				//??: ????
void ISD_WR_NVCFG(void);		//??: ???????
void ISD_WR_APC2(void);			//??: ??APC2
void RdAPC(void);				//??: ??APC
void ISD_Init(void);			//??: ??? 
void ISD_CHK_MEM(void);			//??: ????
void ISD_Reset(void);			//??: ??
void ISD_Stop(void);			//??: ??
void ISD_PU(void);				//??: ??
void ISD_PD(void);				//??: ??
uint8_t RD_DevID(void);			//??: ??ID
//void GetToneAdd(uint8_t cNum,uint16_t * ipStartAdd,uint16_t * ipEndAdd);//??: ???????????
void ISD_PLAY(void);		//??: ????
void ISD_FWD(void);
void SetREC(uint8_t cNum);		//??: ????
void Erase_All(void);			//??: ????		
void ISD1760_config(void);
void PLAY_NUM(u8 i);
#endif