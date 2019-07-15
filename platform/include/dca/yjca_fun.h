/*************************************************************************************************

File Name      :  yjca_fun.h

Description    :  

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  CA

Author(s)      :  haoxw

Notes          :  

History        :

	Version    Date        	Author(s)      Description         Referrence

	1.0        2014-08-21     haoxw         created              ---

**************************************************************************************************/

/*******************************Includes************************************************/

#ifndef _YJCA_FUN_H_
#define _YJCA_FUN_H_

#include "../ca/camid/include/hrca_config.h"
#include "yjca_internal.h"
#include "dCA.h"

/************************************End of Includes*********************************************/

/************************************************************************************************/
/*************************************extern Variables*******************************************/
/************************************************************************************************/

/***********************************End of extern Variables**************************************/

/*****************************CA public function*****************************************/

extern unsigned char HRYJCASTB_Init(void);
extern unsigned char HRYJCASTB_Exit(void);
extern unsigned char HRYJCASTB_SCInsert(void);
extern unsigned char HRYJCASTB_SCRemove(void);
extern void HRYJCASTB_ServiceClear(uint8_t flag);
extern unsigned char HRYJCASTB_SysIDCheck(uint16_t u16SysID);
extern void HRYJCA_Init_PMTData(void);
extern void HRYJCA_MonitorPMT(void);
extern void HRYJCA_MonitorCAT(void);
extern void HRYJCASTB_SetEcmpid(uint16_t u16EcmPID, uint16_t u16ServiceID, uint16_t u16PID, uint8_t u8Type);
extern void HRYJCASTB_SetEmmpid(uint16_t u16EmmPID, uint8_t u8Type);
extern void HRYJCASTB_StopEmmpid(uint16_t u16EmmPID);
extern void HRYJCASTB_ServiceChangeState(D_CASrvInfo* P_CAInfo, uint8_t u8State, uint8_t u8Start);
extern void HRYJCASTB_DataReadyNotify(int32_t slot, uint8_t *u8Data, uint16_t u16DataLen);
extern CA_BOOL HRYJCASTB_SaveEmail(YJemail* EmailInfo);
extern void HRYJCASTB_ShowBuyMessage(uint8_t bMessage);
extern void HRYJCA_SaveOsdInit(uint8_t OSDMaxNum);
extern void HRYJCA_MonitorOSD(void);

/*****************************function in menu******************************************/
//--邮件
extern int32_t HRYJCASTB_GetEmailCount(uint16_t *pu16EmailCount, uint16_t *pu16NewEmailCount, uint16_t *pu16EmptyEmailCount);
extern int32_t HRYJCASTB_GetEmailHeads(uint16_t *pu16EmailCount, hryjca_emailInfo_t* tEmailInfo);
extern int32_t HRYJCASTB_GetEmailHead_ByIndex(uint16_t u16EmailHeadIndex, hryjca_emailInfo_t* tEmailInfo);
extern int32_t HRYJCASTB_GetEmailContent(uint16_t u16EmailIdIndex, hryjca_emailContent_t *tEmailContent);
extern int32_t HRYJCASTB_DelEmail(uint16_t u16EmailIdIndex, uint8_t u8All);
extern int32_t HRYJCASTB_DelEmailTail(uint16_t u16EmailIdIndex);
extern int32_t HRYJCASTB_EmailRead(uint16_t u16EmailIndex);

//授权信息
extern int32_t HRYJCASTB_GetServiceEntitles(uint8_t* pu8Count, hryjca_serviceEntitles_t *tServiceEntitles);

//--卡信息
extern uint16_t HRYJCASTB_GetScNo(char *sc);
extern int32_t HRYJCASTB_GetScBasicInfo(hryjca_scBasicInfo_t *tPBScInfo);
extern int32_t HRYJCASTB_GetSCChildParentAttribute(hryjca_scAddedInfo_t* tPAScInfo);

//IPPV
extern void HRYJCASTB_BuyIPPV(uint8_t buyinfo);


#endif


