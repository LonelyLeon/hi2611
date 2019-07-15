/*************************************************************************************************

File Name      :  hrca_catask.h

Description    :  External dmux definitions for ca module

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  CA

Author(s)      :  hourn

Notes          :  

History        :

	Version    Date        	Author(s)      Description         Referrence

	1.0        2012-02-02     hourn          created              ---

**************************************************************************************************/
#ifndef _HRCA_CATASK_H_
#define _HRCA_CATASK_H_

#include <stdint.h>
#include "dCA.h"
#if ((EMBED_CA & CTICA) == CTICA) 
#include "../../ctica/include/ctiapi.h"
#endif


/*---------- ECM_PID设置的操作类型 ---------*/
#define ECMPID_SET_INI          0x00 //初始化
#define ECMPID_SET_ADD       	0x01 //添加一路ECMPID
#define ECMPID_SET_END         	0x02 //设置完成

/*---------- EMM_PID设置的操作类型 ---------*/
#define EMMPID_SET          0x00 //设置EMMPID
#define EMMPID_STOP       	0x01 //停止EMM接收

#if (((EMBED_CA & CTICA) == CTICA) || ((EMBED_CA & TRCA) == TRCA))
#define MAX_ES_NUM		      10 //max ES number
#define MAX_CA_DESC_LENGTH	  20 //max descrypt length
#define MAX_AUDIO_COPY_COUNT  2

typedef struct PmtEsInfo
{
	//uint8_t 	StreamType;
    uint16_t 	StreamPid;
	uint16_t	InfoLength; 
	int8_t		StreamInfo[MAX_CA_DESC_LENGTH];
} PmtEsInfo_t;
#endif


typedef struct {
    uint8_t *data;
    int16_t length;
} hrca_msg_t;


extern CA_BOOL ECM2FILTER;

//----------------------------------
extern uint16_t pidCurAudio;
extern uint16_t pidCurVideo;
	


extern void *BmailAccess; 	//Bmail备份信号量
extern void *OsdAccess;  	//Osd信号量
extern void *CASlot0Access; //PMT\CAT数据保护
extern void *CADataAccess;  //ECM\EMM数据保护
extern void *CADmuxAccess;  //CA 使用dmux保护
extern void *CAMainFlashAccess; //CA MainFlash 保护
extern void *FlashAlternateAccess; //CA 交替备份flash的保护
extern void *CAFlashBakFlagAccess; //CA FlashBakFlag保护


extern uint16_t  IDtoPid[10];
extern uint8_t	 Mask[10][16];
extern uint8_t   MaskFilter[10][16];

extern CA_BOOL CAModuleInit; //CA模块是否已经初始化
extern uint16_t NewscrambleLevel;//加扰级别：0:免费,1:TS层,2:PES层

/******************************** api**********************************************/
extern void HRCA_ParseCAT(uint8_t* catBuffer);
extern void HRCA_ParsePMT(uint8_t* pu8PmtBuffer);
extern void HRCA_ParseNIT(uint8_t* NitBuffer);
extern CA_BOOL HRCA_Init(void);
extern CA_BOOL HRCA_TaskExit(uint32_t CASDEF);
extern uint16_t Got_CAFilterId(uint16_t wPid, uint8_t *buffer);

#endif


