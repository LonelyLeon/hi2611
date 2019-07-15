/***********************************************************************************************
File Name        : 

Description      :  

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  HMD_DVBC

Author(s)        :  hourn

Notes              :  

History            :

Version    Date        	  Author(s)      Description         Referrence

1.0        2012-02-01     hourn          created              ---

*************************************************************************************************/

/*******************************Includes************************************************/
#ifndef _QZCA_FUN_H_
#define _QZCA_FUN_H_

#ifdef GLOBAL_H_
#define QZ_EXTERN
#else
#define QZ_EXTERN extern
#endif

#include "../ca/camid/include/hrca_config.h"
#include "qzca_internal.h"
/**********************************************************************************/

/*****************************CA public function*****************************************/

QZ_EXTERN uint8_t HRQZCASTB_Init(void);
QZ_EXTERN CA_BOOL HRQZCASTB_Exit(void);
QZ_EXTERN CA_BOOL HRQZCASTB_SCInsert(void);
QZ_EXTERN CA_BOOL HRQZCASTB_SCRemove(void);
QZ_EXTERN void HRQZCASTB_ServiceClear(uint8_t flag);
QZ_EXTERN CA_BOOL HRQZCASTB_SysIDCheck(uint16_t u16SysID);
QZ_EXTERN void HRQZCA_Init_PMTData(void);
QZ_EXTERN void HRQZCA_MonitorPMT(void);
QZ_EXTERN void HRQZCASTB_SetEcmpid(uint16_t u16EcmPID, uint16_t u16ServiceID, uint16_t u16PID, uint8_t u8Type);
QZ_EXTERN void HRQZCA_MonitorCAT(void);
QZ_EXTERN void HRQZCASTB_SetEmmpid(uint16_t u16EmmPID, uint8_t u8Type);
QZ_EXTERN void HRQZCASTB_StopEmmpid(uint16_t u16EmmPID);
QZ_EXTERN void HRQZCASTB_CADataGot(uint8_t u8ReqID, CA_BOOL u8Ok, uint16_t u16Pid, uint8_t* u8ReceiveData, uint16_t u16Len);
QZ_EXTERN void HRQZCASTB_MaskFlash(void);
QZ_EXTERN void HRQZCASTB_UpdateFlash(void);
QZ_EXTERN void HRQZCASTB_OsdMsgOver(uint16_t u16Time);
QZ_EXTERN void HRQZCASTB_ServiceChangeState(uint16_t u16SerId, uint8_t u8State);
QZ_EXTERN void HRQZCASTB_DataReadyNotify(int slot, uint8_t *u8Data, uint16_t u16DataLen);
QZ_EXTERN void HRQZCASTB_ShowBuyMessage(uint8_t bMessage);

/*****************************QZ private function****************************************/

QZ_EXTERN uint8_t HRQZCASTB_GetDate(uint8_t *date);
QZ_EXTERN CA_BOOL HRQZCASTB_GetZoneCode(void);
QZ_EXTERN CA_BOOL HRQZCASTB_SetECMFilter(uint8_t *data, uint8_t *mask, uint8_t type);
QZ_EXTERN CA_BOOL HRQZCASTB_SetEMMFilter(uint8_t *data, uint8_t *mask);
QZ_EXTERN uint8_t HRQZCASTB_ProcessEmm(uint8_t *emm_data, uint8_t emm_len);
QZ_EXTERN uint8_t HRQZCASTB_ProcessEcm(const uint8_t *ecm_data, uint8_t ecm_len, uint8_t *cw_mask, uint8_t *cw);
QZ_EXTERN uint8_t HRQZCASTB_Apdu_package_v4(uint8_t *cache, uint8_t cla, uint8_t ins, uint8_t p1, uint8_t p2, uint8_t lc, uint8_t *input_data);
QZ_EXTERN uint8_t HRQZCASTB_Apdu_package_v2( uint8_t *cache, uint8_t cla, uint8_t ins, uint8_t p1, uint8_t p2, uint8_t le );
QZ_EXTERN uint16_t HRQZCASTB_Crc16ccitt(uint8_t *pBuffer, uint32_t uBufSize);
QZ_EXTERN uint8_t HRQZCASTB_pack_data(uint8_t pkg_type, uint8_t *cache, uint8_t data_len, uint8_t *out) ;
QZ_EXTERN CA_BOOL HRQZCASTB_SaveEmail(const emm_email* Emm_Email);

QZ_EXTERN uint8_t HRQZCASTB_Check_Card(uint8_t *STB_sn, uint8_t STB_sn_lenth, uint8_t *super_cas_id, uint8_t *smartcard_id, uint8_t *cw_mask);
QZ_EXTERN void 	  HRQZCASTB_SetCW(uint8_t *cw);

/*****************************QZ menu function****************************************/

//--ÓÊ¼þ
QZ_EXTERN int32_t HRQZCASTB_GetEmailCount(uint16_t *pu16EmailCount, uint16_t *pu16NewEmailCount, uint16_t *pu16EmptyEmailCount);
QZ_EXTERN int32_t HRQZCASTB_GetEmailHeads(uint16_t *pu16EmailCount, hrqzca_emailInfo_t* tEmailInfo);
QZ_EXTERN int32_t HRQZCASTB_GetEmailHead_ByIndex(uint16_t u16EmailHeadIndex, hrqzca_emailInfo_t* tEmailInfo);
QZ_EXTERN int32_t HRQZCASTB_GetEmailContent(uint16_t u16EmailIdIndex, hrqzca_emailContent_t *tEmailContent);
QZ_EXTERN int32_t HRQZCASTB_DelEmail(uint16_t u16EmailIdIndex, uint8_t u8All);
QZ_EXTERN int32_t HRQZCASTB_DelEmailTail(uint16_t u16EmailIdIndex);
QZ_EXTERN int32_t HRQZCASTB_EmailRead(uint16_t u16EmailIndex);


//--¿¨ÐÅÏ¢
QZ_EXTERN uint16_t HRQZCASTB_GetScNo(char *sc);
QZ_EXTERN int32_t HRQZCASTB_GetScBasicInfo(hrqzca_scBasicInfo_t *tPBScInfo);

#endif //end #ifndef _QZCA_FUN_H_
