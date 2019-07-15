/***********************************************************************************************
File Name        : 

Description      :  

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  HMD_DVBC

Author(s)        :  lim

Notes              :  

History            :

Version    Date        	  Author(s)      Description         Referrence

1.0        2012-11-02      lim            created              ---
1.1		   2013-03-06	   lim			  modify               ---

*************************************************************************************************/

/*******************************Includes************************************************/
#ifndef FUNCTION_H_
#define FUNCTION_H_

#ifdef GLOBAL_H_
#define XG_EXTERN
#else
#define XG_EXTERN extern
#endif

#include "xgca_internal.h"
#include "xgca_type.h"
/********************************extern*******************************************/

//XG_EXTERN char gMatchList[64][9];			   //��ʱ���ã������Ҫ��Ҫ����flash�У�
//XG_EXTERN uint16_t gListCnt;				   //
XG_EXTERN struct xgca_global
{
	struct SysId
	{
		systemId gpSysId;						   //ϵͳid
		uint8_t gSysIdCnt;						   //ϵͳid������ĿǰΪ1
	}SysId_t;

	struct EcmResponse
	{
		uint8_t stopCommand;					   //����ʾppvʱ�������򿨷������ֱ���û�����ѡ��
		uint8_t show_feed;						   //��ǰ�Ƿ������Զ�ι��
		uint8_t gNearDay;						   	   //ppc��Ȩ��������
		uint8_t gNearHour;						   //������Сʱ��
		char isKinescope;						   //�Ƿ�����¼��
		uint8_t gLevel; 							   //��Ŀ����
	}EcmResponse_t;
	
	struct Zone
	{
		hrxgca_zoneRestrict_t gZoneRestrict;	 	  //�������ƽṹ��
		uint8_t gNeedNIT;						 	  //�Ƿ���ҪNIT
		uint8_t NITtable[200];						  //NIT��
	}Zone_t;

	struct Email
	{
		hrxgca_email_t *gpEmail;					   //�ʼ�ָ��
	}Email_t;

	struct Other
	{
		uint8_t xgca_isFree;						   //��Ŀ�Ƿ���ѡ�0-free,	1-not free
		uint8_t gCardState; 						   //��״̬: CA_FALSE:���γ�CA_TRUE:����ʼ���ɹ�
		uint8_t gLevelLimit;                            //�Ƿ��м������
        uint8_t gLevelSet;                              //�Ƿ�������ȷ�˼�������
    }Other_t;
}xgca_global_t;

extern uint32_t MainSdramHandle;    				  //
extern uint8_t  gLevel;
/*****************************CA public function*****************************************/

XG_EXTERN uint8_t HRXGCASTB_Init(void);
XG_EXTERN char HRXGCASTB_Exit(void);
XG_EXTERN char HRXGCASTB_SCInsert(void);
XG_EXTERN char HRXGCASTB_SCRemove(void);
XG_EXTERN void HRXGCASTB_ServiceClear(uint8_t flag);
XG_EXTERN char HRXGCASTB_SysIDCheck(uint16_t u16SysID);
XG_EXTERN void HRXGCA_Init_PMTData(void);
XG_EXTERN void HRXGCA_MonitorPMT(void);
XG_EXTERN void HRXGCASTB_SetEcmpid(uint16_t u16EcmPID, uint16_t u16ServiceID, uint16_t u16PID, uint8_t u8Type);
XG_EXTERN void HRXGCASTB_StopEcmpid(uint16_t u16EcmPID);
XG_EXTERN void HRXGCA_MonitorCAT(void);
XG_EXTERN void HRXGCASTB_SetEmmpid(uint16_t u16EmmPID, uint8_t u8Type);
XG_EXTERN void HRXGCASTB_StopEmmpid(uint16_t u16EmmPID);
XG_EXTERN void HRXGCASTB_CADataGot(uint8_t u8ReqID, char u8Ok, uint16_t u16Pid, uint8_t* u8ReceiveData, uint16_t u16Len);
XG_EXTERN void HRXGCASTB_MaskFlash(void);
XG_EXTERN void HRXGCASTB_UpdateFlash(void);
XG_EXTERN void HRXGCASTB_OsdMsgOver(uint16_t u16Time);
XG_EXTERN void HRXGCASTB_ServiceChangeState(uint16_t u16SerId, uint8_t u8State);
XG_EXTERN void HRXGCASTB_DataReadyNotify(int slot, uint8_t *u8Data, uint16_t u16DataLen);
XG_EXTERN void HRXGCASTB_ShowBuyMessage(uint8_t bMessage);
XG_EXTERN void HRXGCASTB_TimerShowBuyMessage(uint8_t bMessage, uint32_t time);
XG_EXTERN void HRXGCASTB_FlashShowBuyMessage(uint8_t bMessage, uint32_t time, uint32_t show_time, uint32_t hide_time);
XG_EXTERN uint8_t HRXGCASTB_GetDES_Status(void);
XG_EXTERN void  HRXGCASTB_PurseSPUData(void);
XG_EXTERN void HRXGCASTB_SCPUInit_End(void);
XG_EXTERN void HRXGCASTB_ClearTip(void);
XG_EXTERN void HRXGCASTB_ShowCOSMessage(void);
XG_EXTERN void HRXGCASTB_BackCOSFlashData(uint8_t type, uint8_t *buffer, uint8_t lenth);
XG_EXTERN uint8_t HRXGCASTB_GetSCNetID(uint8_t *pu8NetId);

/*****************************XG private function****************************************/

XG_EXTERN char HRXGCASTB_BoundCard(void);
XG_EXTERN char HRXGCASTB_VerifyMatch(void);
XG_EXTERN char HRXGCASTB_GetResponse(uint16_t *lc, uint8_t *response, uint16_t *errorCode);
XG_EXTERN uint8_t HRXGCASTB_Package(uint8_t *cache, uint8_t cla, uint8_t ins, uint8_t p1, uint8_t p2, uint16_t lc, uint8_t *input_data);
XG_EXTERN char HRXGCASTB_UpdateList(uint8_t *response);
XG_EXTERN char HRXGCASTB_CheckList(uint8_t *response);
XG_EXTERN char HRXGCASTB_GetCASList(uint8_t len);
XG_EXTERN char HRXGCASTB_GetEcmFilter(const uint16_t SysId, const uint16_t SubSysId);
XG_EXTERN char HRXGCASTB_GetEmmFilter(const uint16_t SysId, const uint16_t SubSysId);
XG_EXTERN void HRXGCASTB_SetCW(uint8_t *oddcw, uint8_t type);
XG_EXTERN void HRXGCASTB_MJD2YMD(hrxgca_Date_t *date, uint8_t *utc);
XG_EXTERN void HRXGCASTB_BCD2HMS(hrxgca_Time_t *time, uint8_t *bcd);
XG_EXTERN char HRXGCASTB_SaveEmail(hrxgca_email_t* newemail);
XG_EXTERN uint8_t HRXGCASTB_GetZoneRestrict(void);
XG_EXTERN char HRXGCASTB_SendCommand(uint8_t *pCommand, uint8_t CommandLen, uint8_t *pResponse, uint16_t *ResLen, uint16_t *errorCode);
XG_EXTERN void HRXGCASTB_ShowMessage(uint16_t errorCode);
XG_EXTERN void HRXGCASTB_ClearOSD(void);

/*****************************XG private function****************************************/
//--�ʼ�7
XG_EXTERN int32_t HRXGCASTB_GetEmailCount(uint16_t *pu16EmailCount, uint16_t *pu16NewEmailCount, uint16_t *pu16EmptyEmailCount);
XG_EXTERN int32_t HRXGCASTB_GetEmailHeads(uint16_t *pu16EmailCount, hrxgca_emailInfo_t* tEmailInfo);
XG_EXTERN int32_t HRXGCASTB_GetEmailHead_ByIndex(uint16_t u16EmailHeadIndex, hrxgca_emailInfo_t* tEmailInfo);
XG_EXTERN int32_t HRXGCASTB_GetEmailContent(uint16_t u16EmailIdIndex, hrxgca_emailContent_t *tEmailContent);
XG_EXTERN int32_t HRXGCASTB_DelEmail(uint16_t u16EmailIdIndex, uint8_t u8All);
XG_EXTERN int32_t HRXGCASTB_DelEmailTail(uint16_t u16EmailIdIndex);
XG_EXTERN int32_t HRXGCASTB_EmailRead(uint16_t u16EmailIndex);

//--��Ȩ��Ϣ10
XG_EXTERN int32_t HRXGCASTB_GetOperatorIds(uint16_t *pu16TVSId);
XG_EXTERN int32_t HRXGCASTB_GetOperatorInfo(uint16_t* pu16TVSId, uint8_t* pu8Count, hrxgca_operatorInfo_t* tOperatorInfo);
XG_EXTERN int32_t HRXGCASTB_GetOperatorInfo_ByIndex(uint16_t u16TVSIdIndex,hrxgca_operatorInfo_t *tOperatorInfo);
XG_EXTERN int32_t HRXGCASTB_GetEntitlesIds(uint16_t u16TVSIdIndex, uint32_t *u32EntitleIds);
XG_EXTERN int32_t HRXGCASTB_GetServiceEntitles(uint16_t u16TVSIdIndex, uint8_t *pu8Count, hrxgca_serviceEntitles_t *tServiceEntitles);
XG_EXTERN int32_t HRXGCASTB_GetServiceEntitle_ByIndex(uint16_t u16TVSIdIndex,hrxgca_serviceEntitles_t *tServiceEntitles);
XG_EXTERN int32_t HRXGCASTB_GetDetitle(uint16_t u16TVSIdIndex, uint8_t *pu8Count, hrxgca_detitleInfo_t *tDetitle);
XG_EXTERN int32_t HRXGCASTB_GetDetitle_ByIndex(uint16_t u16TVSIdIndex, hrxgca_detitleInfo_t *tDetitle);
XG_EXTERN int32_t HRXGCASTB_GetDetitleReaded(uint16_t u16TVSIdIndex);
XG_EXTERN int32_t HRXGCASTB_DelDetitle(uint16_t u16TVSIdIndex, uint32_t u32Detitle);

//--PPV 7
XG_EXTERN int32_t HRXGCASTB_BuyIPPV(uint8_t *pu8PinCode, uint8_t buyIppType, hrxgca_ippBuyInfo_t *tIppvBuyInfo);
XG_EXTERN int32_t HRXGCASTB_GetIPPV(uint16_t u16TVSIdIndex, uint16_t* pu16Count, hrxgca_viewedIpp_t* tViewedIpp);
XG_EXTERN int32_t HRXGCASTB_GetBookedIpps(uint8_t * pu8Ippcount, hrxgca_ippBuyInfo_t * tIppvBoughtInfo);
XG_EXTERN int32_t HRXGCASTB_GetBookedIpps_ByIndex(uint16_t u16IppvIndex, hrxgca_ippBuyInfo_t *tIppvBoughtInfo);
XG_EXTERN int32_t HRXGCASTB_GetIPPV_ByIndex(uint16_t u16TVSIdIndex, hrxgca_viewedIpp_t *tViewedIpp);
XG_EXTERN int32_t HRXGCASTB_InquireBookIppOver(uint16_t ecmPid);
XG_EXTERN int32_t HRXGCASTB_SetIpptPeriod(hrxgca_ippBuyInfo_t *tIppvBuyInfo, uint16_t u16Period);

//--����4
XG_EXTERN int32_t HRXGCASTB_VerifyPin(uint8_t* pu8Pin, uint8_t u8Len);
XG_EXTERN int32_t HRXGCASTB_ChangePin(uint8_t* pu8OldPin, uint8_t* pu8NewPin, uint8_t u8Len);
XG_EXTERN int32_t HRXGCASTB_GetIsPinPass(uint8_t* pu8IsPinPassed);
XG_EXTERN int32_t HRXGCASTB_GetIsPinLocked(uint8_t *pu8IsLock);

//--�ȼ�2
XG_EXTERN int32_t HRXGCASTB_GetRating(uint8_t *pu8Rating);
XG_EXTERN int32_t HRXGCASTB_SetRating(uint8_t u8Rating, uint8_t* pu8Pin);

//--����Ϣ10
XG_EXTERN uint16_t HRXGCASTB_GetScNo(char *sc);
XG_EXTERN int32_t HRXGCASTB_GetScBasicInfo(hrxgca_scBasicInfo_t *tPBScInfo);
XG_EXTERN int32_t HRXGCASTB_GetSCChildParentAttribute(hrxgca_scAddedInfo_t* tPAScInfo);
XG_EXTERN int32_t HRXGCASTB_GetScUpdateInfo(uint8_t* u8Time, uint8_t* u8Stat);
XG_EXTERN int32_t HRXGCASTB_STBScPaired(uint8_t* pNumber, uint8_t* pSTBIdList);	//�������
XG_EXTERN int32_t HRXGCASTB_STBScReadFeedData(uint16_t tvSid, uint8_t* pbyFeedData, uint8_t* pbyLen );
XG_EXTERN int32_t HRXGCASTB_STBScWriteFeedData(uint16_t tvSid, uint8_t* pbyFeedData, uint8_t pbyLen );
XG_EXTERN int32_t HRXGCASTB_GetScInfo(hrxgca_scBasicInfo_t * scInfo);
XG_EXTERN int32_t HRXGCASTB_GetScCosVer(uint32_t *pScCosVer);
XG_EXTERN int32_t HRXGCASTB_GetCAVer(uint8_t *pCAVer);
XG_EXTERN int32_t HRXGCASTB_GetCAManuName(int8_t *pCAMaunNameVer);
XG_EXTERN uint8_t HRXGCASTB_CompareLevelCode(uint16_t code);
//--Ǯ��3
XG_EXTERN int32_t HRXGCASTB_SlotId(uint16_t u16TVSIDIndex, uint8_t *pu8Count, uint8_t *slotId);
XG_EXTERN int32_t HRXGCASTB_SlotInfo(uint16_t u16TVSIDIndex, uint8_t* u8SlotId, hrxgca_slotInfo_t *slotInfo);
XG_EXTERN int32_t HRXGCASTB_SlotInfo_ByIndex(uint16_t u16SlotIndex, hrxgca_slotInfo_t *slotInfo);

//--����ʱ��2
XG_EXTERN int32_t HRXGCASTB_GetWorkTime(uint8_t* pu8StartHour, uint8_t* pu8StartMin, uint8_t* pu8StartSec, uint8_t* pu8EndHour, uint8_t* pu8EndMin, uint8_t* pu8EndSec);
XG_EXTERN int32_t HRXGCASTB_SetWorkTime(uint8_t u8StartHour, uint8_t u8StartMin, uint8_t u8StartSec, uint8_t u8EndHour, uint8_t u8EndMin, uint8_t u8EndSec, uint8_t* pu8Pin);

#endif //end #ifndef FUNCTION_H_
