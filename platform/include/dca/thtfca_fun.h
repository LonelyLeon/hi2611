/*************************************************************************************************

File Name      :  thtfca_fun.h

Description    :  

Copyright(C)   :  

Project Group  :  CA

Author(s)      :  

Notes          :  

History        :

	Version    Date        	Author(s)      Description         Referrence

	1.0                                    created              ---

**************************************************************************************************/

/************************************************************************************************/
/***************************************Includes*************************************************/
/************************************************************************************************/

#ifndef _THTFCA_FUN_H_
#define _THTFCA_FUN_H_

#include "../ca/camid/include/hrca_config.h"
#include "../ca/camid/include/hrca_api.h"
#include "../ca/camid/include/hrca_flash.h"
#include "../../ca/thtfca/include/p4vLibConfigs.h"
#include "../../ca/thtfca/include/p4vLib.h"
#include "dCA.h"
#include "thtfca_internal.h"

/************************************End of Includes*********************************************/

/*****************************CA public function*****************************************/

extern CA_BOOL HRTHTFCASTB_Init(void);
extern CA_BOOL HRTHTFCASTB_Exit(void);
extern CA_BOOL HRTHTFCASTB_SCInsert(void);
extern CA_BOOL HRTHTFCASTB_SCRemove(void);
extern void HRTHTFCASTB_ServiceClear(uint8_t flag);
extern CA_BOOL HRTHTFCASTB_SysIDCheck(uint16_t u16SysID);
extern void HRTHTFCA_Init_PMTData(void);
extern void HRTHTFCA_MonitorPMT(void);
extern void HRTHTFCASTB_SetEcmpid(uint16_t u16EcmPID, uint16_t u16ServiceID, uint16_t u16PID, uint8_t u8Type);
extern void HRTHTFCASTB_StopEcmpid(uint16_t u16EcmPID);
extern void HRTHTFCA_MonitorCAT(void);
extern void HRTHTFCASTB_SetEmmpid(uint16_t u16EmmPID, uint8_t u8Type);
extern void HRTHTFCASTB_StopEmmpid(uint16_t u16EmmPID);
extern void HRTHTFCASTB_CADataGot(uint8_t u8ReqID, CA_BOOL u8Ok, uint16_t u16Pid, uint8_t* u8ReceiveData, uint16_t u16Len);
extern void HRTHTFCASTB_MaskFlash(void);
extern void HRTHTFCASTB_UpdateFlash(void);
extern void HRTHTFCASTB_OsdMsgOver(uint16_t u16Time);
extern void HRTHTFCASTB_ServiceChangeState(D_CASrvInfo* P_CAInfo, uint8_t u8State, uint8_t u8Start);
extern void HRTHTFCASTB_DataReadyNotify(int32_t slot, uint8_t *u8Data, uint16_t u16DataLen);
extern CA_BOOL HRTHTFCASTB_SaveEmail(info_mail_t *emailInfo);
extern void HRTHTFCASTB_ShowBuyMessage(uint8_t bMessage);
extern void HRTHTFCASTB_TimerShowBuyMessage(uint8_t bMessage,uint32_t time);
extern void HRTHTFCA_ShowMaurityProgram(uint8_t ShowOrHide);
extern void HRTHTFCA_SaveOsdInit(uint8_t OSDMaxNum);
extern CA_BOOL HRTHTFCA_SaveOsdMessage(info_popup_message_t* u8OsdData);
extern CA_BOOL HRTHTFCA_GetOsdMessage(info_popup_message_t* u8OsdData);
extern void HRTHTFCA_MonitorOSD(void);
extern void HRTHTFCASTB_GetECMPID(uint8_t *pmtbuff, uint16_t u16len, uint16_t* pid);
extern void HRTHTFCASTB_GetEMMPIDList(uint8_t *catbuff, uint16_t u16len, emm_pid_list_t* pidlist);
extern void HRTHTFCASTB_GetUserID(uint8_t *Buffer, uint32_t NumberToRead);
extern void HRTHTFCASTB_SetUserID(uint8_t *Buffer, uint32_t NumberToWrite);
extern void HRTHTFCA_MonitorEntitle(uint8_t state);
extern CA_BOOL HRTHTFCASTB_EntitleState(void);

/*****************************function in menu***************************************/
//--用户信息
extern uint16_t HRTHTFCASTB_GetScNo(char *sc);
extern int32_t HRTHTFCASTB_GetUserBasicInfo(hrthtfca_userBasicInfo_t * tPBScInfo);

//--授权信息
extern int32_t HRTHTFCASTB_GetOperatorInfo(uint8_t* pu8Count, hrthtfca_operatorInfo_t* tOperatorInfo);
extern int32_t HRTHTFCASTB_GetOperatorInfo_ByIndex(uint16_t u16TVSIdIndex, hrthtfca_operatorInfo_t *tOperatorInfo);
extern int32_t HRTHTFCASTB_GetServiceEntitles(uint16_t u16TVSIdIndex, uint16_t *pu8Count, hrthtfca_serviceEntitles_t *tServiceEntitles);
extern int32_t HRTHTFCASTB_GetServiceEntitle_ByIndex(uint16_t u16TVSIdIndex, hrthtfca_serviceEntitles_t *tServiceEntitles);
extern void HRTHTFCASTB_GetCurProgramEntitle(char *tServiceEntitle);
//--密码
extern int32_t HRTHTFCASTB_ChangePin(uint8_t *pu8OldPin, uint8_t *pu8NewPin, uint8_t u8Len);
extern int32_t HRTHTFCASTB_SetPinAvailability(uint8_t *pu8Pin, uint8_t enbaleOrNot);
extern int32_t HRTHTFCASTB_GetPinState(uint8_t *state);

//--等级
extern int32_t HRTHTFCASTB_GetRating(uint8_t *pu8Rating);
extern int32_t HRTHTFCASTB_SetRating(uint8_t u8Rating, uint8_t *pu8Pin);

//--成人级
extern int32_t HRTHTFCASTB_MaurityProg(uint8_t *pu8Pin);

//--工作时间
extern int32_t HRTHTFCASTB_GetWorkTime(uint8_t* pu8StartHour, uint8_t* pu8StartMin, uint8_t* pu8StartSec, uint8_t* pu8EndHour, uint8_t* pu8EndMin, uint8_t* pu8EndSec, uint8_t* pu8State);
extern int32_t HRTHTFCASTB_SetWorkTime(uint8_t u8StartHour, uint8_t u8StartMin, uint8_t u8StartSec, uint8_t u8EndHour, uint8_t u8EndMin, uint8_t u8EndSec, uint8_t* pu8Pin);
extern int32_t HRTHTFCASTB_FreeWorkTime(uint8_t* pu8Pin);

//--邮件
extern int32_t HRTHTFCASTB_GetEmailCount(uint16_t* pu16EmailCount, uint16_t* pu16NewEmailCount, uint16_t* pu16EmptyEmailCount);
extern int32_t HRTHTFCASTB_GetEmailHeads(uint16_t* pu16EmailCount, hrthtfca_emailInfo_t* tEmailInfo);
extern int32_t HRTHTFCASTB_GetEmailHead_ByIndex(uint16_t u16EmailHeadIndex, hrthtfca_emailInfo_t* tEmailInfo);
extern int32_t HRTHTFCASTB_GetEmailContent(uint16_t u16EmailIdIndex, hrthtfca_emailContent_t* tEmailContent);
extern int32_t HRTHTFCASTB_DelEmail(uint16_t u16EmailIdIndex, uint8_t u8All);

//--续费自动通知
extern int32_t HRTHTFCASTB_GetOverdueInfo(uint8_t *pu8Day, uint8_t *pu8State);
extern int32_t HRTHTFCASTB_SetOverdueInfo(uint8_t pu8Day, uint8_t pu8State);



#endif


