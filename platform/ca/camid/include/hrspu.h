/***********************************************************************************************
File Name        :  hrspu.h

Description      :  scpu  interface for ca

Copyright(C)   :  Haier_IC 2013.7

Project Group  :  HMD_DVBC

Author(s)        :  hanjf

Notes              :  

History            :

Version    Date        	  Author(s)      Description         Referrence

1.0        2013-07-2        hanjf          created              ---

*************************************************************************************************/
#ifndef __HRSPU_H
#define __HRSPU_H

/************************************************************************************************/
/***************************************Includes*************************************************/
/************************************************************************************************/

#include "hrca_config.h"
#include "hrca_display.h"


/************************************End of Includes*********************************************/
#if EMBED_CA != FREEACCESS

#define  HRCA_SC_Printf   HRCA_SerialPrint

#define DSP_COS_DATA_LEN    0x17000  //备份DSP上的数据长度
#define COS_DATA_SIZE       0x9000  // 扩展使用 //EEPROM的size是16K,CA使用15K，从1K开始
#define COS_PARAM_OFFSET_IN_EEPROM       1024
#define COS_DATA_SIZE_WF    0x2000  //wf COS data size
#define COS_DATA_SIZE_ABV   0x3000  //abv COS data size,需要根据不同的COS库调整
#define COS_DATA_SIZE_ABV_UNITY   0x40400  //abv COS data size,需要根据不同的COS库调整
#define COS_DATA_SIZE_XG    0x350
#define COS_DATA_SIZE_DS    0x8200
#define COS_DATA_SIZE_CTI	0x7800//0x8200
#define COS_DATA_SIZE_UTI   0x3c00
#define COS_DATA_SIZE_DVT   0x400//0x00  //为了将chipid发给spu

#if defined(D_ARCH_HI2309)
#define DSP_BASE_MSG           0xba500000
#define DSP_BASE_REG0          0xba580000
#elif defined(D_ARCH_HI2830)
#define DSP_BASE_MSG           0xbd600000
#define DSP_BASE_REG0          0xbd680000
#elif (defined(D_ARCH_HI2610D)|| defined(D_ARCH_HI2610E))
#define DSP_BASE_MSG           0xbd600000
#define DSP_BASE_REG0          0xbd680000
#else
#define DSP_BASE_MSG           0xbd600000
#define DSP_BASE_REG0          0xbd680000
#endif

#define REG32(x)		(*(unsigned long  volatile *)(x))

#define DSP_IRQ_FROM_CPU        REG32(DSP_BASE_REG0 + 0x04*4)

#define DSP_INT_FROM_CPU        REG32(DSP_BASE_MSG + 0x00)
#define DSP_INT_TO_CPU          REG32(DSP_BASE_MSG + 0x04)
#define DSP_PRINT_EN          	REG32(DSP_BASE_MSG + 0x08)

#define DRM_MESSAGE_0           		REG32(DSP_BASE_MSG + 0x10)   //hanjf  
#define DRM_MESSAGE_1           		REG32(DSP_BASE_MSG + 0x14)
#define DRM_MESSAGE_2           		REG32(DSP_BASE_MSG + 0x18)
#define DRM_MESSAGE_3           		REG32(DSP_BASE_MSG + 0x1c)
#define DRM_MESSAGE_4           		REG32(DSP_BASE_MSG + 0x20)
#define DRM_MESSAGE_5           		REG32(DSP_BASE_MSG + 0x24)
#define DRM_MESSAGE_6           		REG32(DSP_BASE_MSG + 0x28)
#define DRM_MESSAGE_7           		REG32(DSP_BASE_MSG + 0x2c)
#define DRM_MESSAGE_8           		REG32(DSP_BASE_MSG + 0x30)
#define DRM_MESSAGE_9           		REG32(DSP_BASE_MSG + 0x34)
#define DRM_MESSAGE_A           		REG32(DSP_BASE_MSG + 0x38)
#define DRM_MESSAGE_B           		REG32(DSP_BASE_MSG + 0x3c)
#define DRM_MESSAGE_C          			REG32(DSP_BASE_MSG + 0x40)
#define DRM_MESSAGE_D           		REG32(DSP_BASE_MSG + 0x44)
#define DRM_MESSAGE_E           		REG32(DSP_BASE_MSG + 0x48)
#define DRM_MESSAGE_F           		REG32(DSP_BASE_MSG + 0x4c)

#define DSP_MESSAGE_18          		REG32(DSP_BASE_MSG + 0xe0)
#define DSP_MESSAGE_19          		REG32(DSP_BASE_MSG + 0xe4)
#define DSP_MESSAGE_1A         			REG32(DSP_BASE_MSG + 0xe8)
#define DSP_MESSAGE_1B       			REG32(DSP_BASE_MSG + 0xec)

/************************************************************************************************/
/*************************************Static  Variable*******************************************/
/************************************************************************************************/

/***********************************End of Static Variables**************************************/

/************************************************************************************************/
/*************************************extern Variables*******************************************/
/************************************************************************************************/
extern unsigned char spu_data[0x400];//[256]
extern unsigned int recvLen; //从SPU接收到的数据长度
extern volatile unsigned char IsChangeProg;
extern volatile unsigned char cosRev; //判断cos是否有返回
extern unsigned char scinsert;
extern unsigned char *ddraddr;

/***********************************End of extern Variables**************************************/

/************************************************************************************************/
/*************************************extern Functions*******************************************/
/************************************************************************************************/

/***********************************End of extern Functions**************************************/

/************************************************************************************************/
/**********************************Function******************************************************/
/************************************************************************************************/

void send_data_to_dsp(unsigned char *dataptr, unsigned int len);
uint8_t HRHash_Data_Check(uint8_t *data, uint8_t *value);
CA_BOOL HRCA_NoneSCGetATR(uint8_t* u8ATR);
void NoneSC_SCPUInit_End(void);
unsigned char NoneSC_GetSPU_Status(void);
hrca_ca2us_state_t NoneSC_GetDES_Status(void);
void NoneSC_RecData_FromSPU(void);
void NoneSC_ReqSPU_BackupData(void);
void NoneSC_SetSPU_DataAddr(void);
void NoneSC_InformSPU_RevertData(void);
uint8_t NoneSC_ReadData(uint32_t Offset, uint8_t *Buffer, uint32_t NumberToRead);
unsigned char NoneSC_WriteData_STATUS(void);
unsigned char NoneSC_WriteData(void);
unsigned char NoneSC_GetSPURevertData_Status(void);
void NoneSC_InitMem(void);
void NoneSC_ReleaseMem(void);
void NoneSC_Init(void);
void NoneSC_Callback(unsigned int p);
void NoneSC_RecInfo_FromSPU(void);

#endif

#endif
