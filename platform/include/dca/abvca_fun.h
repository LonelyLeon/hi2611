/*************************************************************************************************

File Name      :  abvca_fun.h

Description    :  

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  CA

Author(s)      :  hourn

Notes          :  

History        :

	Version    Date        	Author(s)      Description         Referrence

	1.0        2012-02-01     hourn          created              ---

**************************************************************************************************/

/*******************************Includes************************************************/

#ifndef _ABVCA_FUN_H_
#define _ABVCA_FUN_H_

#include "../ca/camid/include/hrca_config.h"
#include "../ca/camid/include/hrca_flash.h"
#include "abvca_internal.h"
#include "dCA.h"
#include"../../ca/abvca/include/abv_ca_interface.h"

/************************************End of Includes*********************************************/

/************************************************************************************************/
/*************************************extern Variables*******************************************/
/************************************************************************************************/
extern uint32_t  abvTaskIdTable[MAX_TASK_NUMBER_ABVCA];
/***********************************End of extern Variables**************************************/

/*****************************CA public function*****************************************/

extern unsigned char HRABVCASTB_Init(void);
extern unsigned char HRABVCASTB_Exit(void);
extern unsigned char HRABVCASTB_SCInsert(void);
extern unsigned char HRABVCASTB_SCRemove(void);
extern unsigned char HRABVCASTB_SCRemove_NoneCard(void);
extern void HRABVCASTB_ServiceClear(uint8_t flag);
extern unsigned char HRABVCASTB_SysIDCheck(uint16_t u16SysID);
extern void HRABVCA_Init_PMTData(void);
extern void HRABVCA_MonitorPMT(void);
extern void HRABVCA_MonitorCAT(void);
extern void HRABVCASTB_SetEcmpid(uint16_t u16EcmPID, uint16_t u16ServiceID, uint16_t u16PID, uint8_t u8Type);
extern void HRABVCASTB_SetEmmpid(uint16_t u16EmmPID, uint8_t u8Type);
extern void HRABVCASTB_ServiceChangeState(D_CASrvInfo* P_CAInfo, uint8_t u8State, uint8_t u8Start);
extern void HRABVCASTB_DataReadyNotify(uint32_t slot, uint8_t *u8Data, uint16_t u16DataLen);
extern void HRABVCASTB_ShowBuyMessage(uint8_t bMessage);
extern void HRABVCASTB_TimerShowBuyMessage(uint8_t bMessage,uint32_t time);

extern int32_t  HRABVCASTB_GetCustomerID(uint8_t *pCustomerID);
extern void HRABVCA_ShowEMMSuperFinger(uint32_t u32EcmPID, char *CardIDarray, uint8_t ShowOrHide);
extern void HRABVCA_ShowUserSuperFinger(uint32_t u32EcmPID, char *CardIDarray, uint8_t ShowOrHide);
extern void HRABVCA_ShowMaurityProgram(uint8_t ShowOrHide);
extern void HRABVCA_ShowCovertFinger(uint32_t u32EcmPID, char *CardIDarray, uint8_t ShowOrHide);
extern void HRABVCA_ShowOsdMessage(char* u8OsdData, uint32_t bg_clor, uint32_t font_clor, uint8_t font_size, uint8_t transparency, uint32_t u16Time, uint32_t u8JudgeValue);
extern void HRABVCA_GetCurOTAInfo(uint32_t* buffer, uint8_t length);
extern void HRABVCA_SendOTAInfo(char *OtaInfo);
extern void HRABVCA_SendMsgFromCA2OtherSTB(uint8_t* buffer);
extern void HRABVCA_SendSerialStatus(CA_BOOL* bStatus);
extern void HRABVCA_MonitorOSD(void);
extern void HRABVCA_GetSTBInfo(uint8_t* buffer, uint16_t length);
extern unsigned char HRABVCA_PVRInfo(void);
extern void HRABVCA_SendForbidPVR(void);
extern uint32_t HRABVCA_GetRGBInfo(uint8_t colorindex);
extern void HRABVCA_ConvertTransparency(uint8_t transPercent, uint8_t *trans);

/*****************************function in menu******************************************/
//--邮件7
extern int32_t HRABVCASTB_GetEmailCount(uint16_t *pu16EmailCount, uint16_t *pu16NewEmailCount, uint16_t *pu16EmptyEmailCount);
extern int32_t HRABVCASTB_GetEmailHeads(uint16_t* pu16EmailCount, hrabvca_emailInfo_t* tEmailInfo);
extern int32_t HRABVCASTB_GetEmailHead_ByIndex(uint16_t u16EmailHeadIndex, hrabvca_emailInfo_t *tEmailInfo);
extern int32_t HRABVCASTB_GetEmailContent(uint16_t u16EmailIdIndex, hrabvca_emailContent_t *tEmailContent);
extern int32_t HRABVCASTB_DelEmail(uint16_t u16EmailIndex, uint8_t u8All);
extern int32_t HRABVCASTB_DelEmailTail(uint16_t u16EmailIdIndex);
extern int32_t HRABVCASTB_EmailRead(uint16_t u16EmailIdIndex);
//--授权信息10
extern int32_t HRABVCASTB_GetOperatorInfo(uint8_t *pu8Count, hrabvca_operatorInfo_t *tOperatorInfo);
extern int32_t HRABVCASTB_GetOperatorInfo_ByIndex(uint16_t u16TVSIdIndex,hrabvca_operatorInfo_t *tOperatorInfo);
extern int32_t HRABVCASTB_GetEntitlesIds(uint16_t u16TVSIdIndex, uint32_t *pu32EntitleIds);
extern int32_t HRABVCASTB_GetFreeEntitles(uint16_t u16TVSIdIndex, uint16_t *pu8Count, hrabvca_freeEntitles_t *tServiceEntitles);
extern int32_t HRABVCASTB_GetFreeEntitle_ByIndex(uint16_t u16TVSIdIndex,hrabvca_freeEntitles_t *tServiceEntitles); 
extern int32_t HRABVCASTB_GetPPCEntitles(uint16_t u16TVSIdIndex, uint16_t pagenum, uint16_t *pu8Count, hrabvca_ppcEntitles_t *tServiceEntitles);
extern int32_t HRABVCASTB_GetPPCEntitle_ByIndex(uint16_t u16TVSIdIndex,hrabvca_ppcEntitles_t *tServiceEntitles);
extern int32_t HRABVCASTB_GetPPVEntitles(uint16_t u16TVSIdIndex, uint16_t *pu8Count, hrabvca_ppvEntitles_t *tServiceEntitles);
extern int32_t HRABVCASTB_GetPPVEntitle_ByIndex(uint16_t u16TVSIdIndex,hrabvca_ppvEntitles_t *tServiceEntitles);

//IPPV
extern int32_t HRABVCASTB_BuyIPPV(uint8_t *pu8PinCode, uint8_t buyIppType, uint8_t programID);

//Maurity Program
extern int32_t HRABVCASTB_MaurityProg(uint8_t *pu8Pin, uint8_t *resetnum);

//--密码4
extern int32_t HRABVCASTB_ChangePin(uint8_t *pu8OldPin, uint8_t *pu8NewPin, uint8_t u8Len, uint8_t *resetnum);
//--等级2
extern int32_t HRABVCASTB_GetRating(uint8_t *pu8Rating);
extern int32_t HRABVCASTB_SetRating(uint8_t u8Rating, uint8_t *pu8Pin, uint8_t *resetnum);
//--卡信息6
extern uint16_t HRABVCASTB_GetScNo(char *sc);
extern int32_t HRABVCASTB_GetScBasicInfo(hrabvca_scBasicInfo_t *tPBScInfo);
extern int32_t  HRABVCASTB_GetCALIBVerInfo(uint8_t *verInfo);

//--工作时间2
extern int32_t HRABVCASTB_GetWorkTime(uint8_t* pu8StartHour, uint8_t* pu8StartMin, uint8_t* pu8StartSec, uint8_t* pu8EndHour, uint8_t* pu8EndMin, uint8_t* pu8EndSec, uint8_t* pu8Pin);
extern int32_t HRABVCASTB_SetWorkTime(uint8_t u8StartHour, uint8_t u8StartMin, uint8_t u8StartSec, uint8_t u8EndHour, uint8_t u8EndMin, uint8_t u8EndSec, uint8_t* pu8Pin, uint8_t *resetnum);

//--消费或充值历史信息
extern int32_t HRABVCASTB_GetConsumeInfo(uint16_t u16TVSIdIndex, uint16_t* pu16ConsumeCount, hrabvca_consumeInfo_t* tConsumeInfo);
extern int32_t HRABVCASTB_PrintScNoAndSTBID(void);

#endif


