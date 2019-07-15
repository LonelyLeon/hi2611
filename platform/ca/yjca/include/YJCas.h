
/******************************************************************************
 * Copyright (c) 2008, �ɶ�Ӣ�����ӿƼ����޹�˾
 * All rights reserved.
 *
 * �ļ����ƣ� YJCas.h
 * 
 * ��    Ҫ:  ��������ϵͳ��̽ӿڡ�
 *            
 * 
 * ��ǰ�汾�� 	1.0.0
 *
 * ��    �ߣ� 		Nbug
 * �������ڣ� 	2008��7��30��
 *
 * smart card :  T0
 ******************************************************************************/
#ifndef  _YJCAS_H_
#define   _YJCAS_H_ 

#include "YJTypes.h"
#ifdef  __cplusplus
extern "C" {
#endif


typedef struct _YJCAEmailInfo
{
	UINT16 	u16EmailID;     							/*�ʼ���ID�������ֲ�ͬ���ʼ�*/      
	UINT8  	au8MailTime[3];							/*����ʮ�����Ƶ�����08/07/14*/
	UINT8  	au8EmailHead[MAIL_MAX_CAPTIONLEN];		/*�ʼ����⣬�Ϊ20*/
	UINT8  	au8Email[MAIL_MAX_CONTENTLEN]; 			/*Email�����ģ��512������*/
}SYJCAEmailInfo;


typedef enum 
{
	EN_ALLPROG_NO_ROLL,   							/*�й�����Ļ����������̨��������*/
	EN_ALLPRO_ROLL,								/*�й�����Ļ����������̨������*/
	EN_PIDLIST_NO_ROLL,							/*�й�����Ļ������ֻ��PIDLIST�еĽ�Ŀ������*/
	EN_PIDLIST_ROLL,								/*�й�����Ļ������ֻ��PIDLIST�еĽ�Ŀ����*/
}IsRoll_en;


typedef struct _YJCARollPrgSetInfo					/*�����ݽṹ����������Щ̨��Ҫ��������Щ̨����Ҫ����*/
{
	IsRoll_en enIsRoll;								/*���ݸò������й�����Ļ�Ĵ���*/
	UINT8	u8VideoPidNum;							/*�������õĽ�Ŀ�� */
	UINT16 	au16VideoPidList[MAX_VIDEOPID_NUM];		/*Video Pid�б�*/
}SYJCARollPrgSetInfo;


typedef struct _YJCAOsdInfo
{
	UINT8 	u8RollTimes;							/*����������ͬһ��������Ļ���Թ������*/
	UINT8 	u8RollMode;								/*����ģʽ��ֵΪ1��ʾ�Ϲ���Ϊ0��ʾ�¹���Ϊ2��ʾ�����Ϊ3��ʾ�ҹ�*/
	UINT8 	au8RollContent[MAX_ROLLDATA_LEN];		/*������Ļ���ݣ����512��*/
	UINT16 	u16TxtLen;								/*������Ļ��ʵ�ʳ���*/
	UINT16 	u16OsdId;								/*������Ļ��ID�������ֲ�ͬ����Ļ*/
	SYJCARollPrgSetInfo stCaRollPrgSetInfo;
} SYJCAOsdInfo;

typedef enum/*IPPV���û�ѡ���Ƿ���IPPV*/
{
	FOCUSON_YES = 0,
	FOCUSON_NO
}IppvFocus_en;

typedef enum CA_RESULT_T/*CA����״̬*/
{
	CA_SUCCESS,
	CA_SAME_STATE,
	CA_FAILURE
} CA_RESULT_t;

/* ASC Time */
typedef struct
{
    INT32 Year;
    INT8 	Month;
    INT8 	Day;
    INT8 	Hour;
    INT8 	Min;
    INT8 	Second;
}TIME_DATE_YJCA;


typedef struct CA_IPPVDATA_S
{
	UINT8 			ippv;								/*�жϸý�Ŀ�Ƿ�ΪIPPV��Ŀ��1ΪIPPV��Ŀ������Ϊ��IPPV��Ŀ*/
	UINT16 			pid;									/*IPPV��Ŀ��VIDEO PID*/
	TIME_DATE_YJCA 	startDate;							/*IPPV��Ŀ��ʼ����ʱ��*/
	TIME_DATE_YJCA	 time;								/*IPPV��Ŀ�����Ĳ���ʱ�䣬����������������Ч*/
	TIME_DATE_YJCA 	currentDate;							/*��ǰ����ʱ��*/
	UINT16 			money;								/*�տ��ý�Ŀ����Ҫ�ķ��ã���λΪ��*/
}CA_IPPVDATA_T;


typedef struct RADIATE_Fre_INFO_S
{
	UINT32 		u32Frequency;						/*���ݹ㲥���ڵ�Ƶ��*/
#if defined ( DVBC) 
    	UINT8 		u8Modulation;  
 	UINT32 		u32SymbolRate;	
#elif defined (DMBT) /*DMB_T*/
	UINT8		u8BandWidth;
	UINT32 		u32DemodPara;
#elif defined (DVBS)
	/*�ȴ��������*/
	UINT8 		 u8Unuse;  
 	UINT32 		 u32SymbolRate;	
#endif
	UINT16 		u16VideoPid;						/*����Ƶ����VideoPID*/
	UINT16 		u16AudioPid;						/*����Ƶ����AudioPID*/

}RADIATE_Fre_INFO_T;	

typedef struct RADIATE_CHANNEL_INFO_S
{
	UINT8		u8RadiateType;						/*���ݹ㲥�����ֽ����ͣ�0x00��ʾ�����ݹ㲥��0x01��ʾ�������ݹ㲥*/
	UINT8 		u8MenuTableID;						/*�˵�����Table ID*/
	UINT8 		u8TitleTableID;						/*��������Table ID*/
	UINT8 		u8TxtTableID;						/*���ݹ㲥����Table ID*/
	UINT8 		u8LogoTransContralTableID;			/*���洫�����TableID*/
	UINT16 		u16ChannelPid;						/*���ݹ㲥PID*/
	UINT16 		u16LogoChannelPid;					/*���洫��PID*/
	RADIATE_Fre_INFO_T 	stFreInfo;
}RADIATE_CHANNEL_INFO_T;	

/*����Ϊ���Ƶ����Ϣ*/
typedef struct CaFreInfo
{
	UINT16 		u16Frequency;
#if	 defined (DVBC) 	
    	UINT8 		u8Modulation;    
  	UINT32 		u32SymbolRate;
#elif defined (DMBT) 
	UINT8		u8BandWidth;
	UINT32 		u32DemodPara;
#elif defined (DVBS)
	/*�ȴ�����-S�Ĳ���*/
	UINT8 		 u8Unuse;  
 	UINT32 		 u32SymbolRate;	
#endif
	UINT8		u8Resverd;

}CaFreInfo_t;


typedef struct __ServiceTxtAdsInfo
{
	UINT8 m_ucStyleId;
	UINT8 m_ucTxtId;
	UINT16 m_usPid;
	struct __ServiceTxtAdsInfo *pnext;
}ServiceTxtAdsInfo;

typedef struct __TxtStyleInfo
{
	UINT8 m_ucId;
	UINT32 m_usColor;
	UINT8 m_ucFont;
	UINT8 m_ucSize;
	UINT8 m_ucPos;
	UINT8 m_ucStyle;
	UINT32 m_usBgColor;
	struct __TxtStyleInfo* pnext;
}TxtStyleInfo;

typedef struct __AdsCharInfo
{
	UINT8 m_ucId;
	UINT32 m_uiMjd;
	UINT32 m_uiStart;
	UINT32 m_uiDuration;
	UINT8 m_ucTxtLen;
	UINT8* m_pTxt;
	struct __AdsCharInfo *pnext;
}AdsCharInfo;



struct cas_info {	
    UINT8     ecm_pid_num;
    UINT8     emm_pid_num;
    int  ecm_filter;
    int  descramblers[8];
    int  ecm_channels[8]; 
    int  emm_channels[8];	
    int  handle_sc;  
    UINT8     sc_outin; 
    int  gSmcMutexId;	
    int  p_gsemFlash;	
    UINT8 CartAtr;
};

//struct cas_info casfilter ;//haoxw

/*---------------------------���º���ΪCAS�ṩ��STB����-----------------------------*/


/*
 * �����������YJ CA��һЩ��ʼ������������ʼ��ʧ�ܣ���������������YJCA	
-*/
extern bool 	YJCASTB_Init(void);
extern UINT16   YJCASTB_EntitlCountGot(void);
extern bool     YJCASTB_EntitlListGot(UINT8 *pu8Data,UINT8 listNum);
/*
 * ����������������ж��Ƿ���CASYSTEMID�ܹ�����ǰCAʶ��	
-*/
extern bool  YJCASTB_IsYJCa(UINT16 u16CaSystemID);
/*�ú������ڻ�ȡ��ĸ����Ϣ*/
extern bool YJCASTB_GetOperatorChildStatus(bool *pbIsChild,
                UINT8 *pu8DelayTime,UINT8 *pu8LastConfirmTime,UINT8 *pu8MainCardNo);
/*
*�����ĸ�����������ʾ��CA��Ϣ�˵���,�ֱ���:
	1����ID(10B):		*pu8CardId //��ID��ȥ����4��5�ֽڣ�����8���ֽ�����EMM���ݻ�ȡ�ĵ�ַ����
	2���û���(8B):	*pu8UserId
	3���豸��(9B):	*pu8DeviceId//����STB���к�
	4������(9B):	*pu8CardMatch
*/
extern bool YJCASTB_CardIdGot(UINT8 *pu8CardId);
extern bool YJCASTB_UserIdGot(UINT8 *pu8UserId);
extern bool YJCASTB_DeviceIdGot(UINT8 *pu8DeviceId);
extern bool YJCASTB_CardMatch(UINT8 *pu8CardMatch);
/*�ú������ڻ�ȡYJCA�İ汾���Ѿ��������*/
extern void YJCASTB_GetVer(UINT8 *pu8CaVer,UINT8 *pu8CaLibDate);
/*�ú������ڻ�ȡ��С��Ȩ����*/
extern bool YJCASTB_MinAccreditDate(UINT8 *pu8MinAccreditDate);
/*������ECM�Ĺ���������TABLEID�ֱ�Ϊ0x80,0x81*/
/*�ú������ڴ���õ���ECM����,��IPPV����,���ܺ��CW�����ֵ�*/
extern CA_RESULT_t  YJ_ParseEcmData(UINT8 *pu8ReceiveData);
/*EMM����������������ΪTABLEIDΪ0x82*/
/*�����ܿ�ID �����ĸ��ֽ�Ϊ0xff ������㲥���ʱҪƥ��ǰ�ĸ��ֽ�*/
/*�ú������ڴ���õ���EMM����,����Ȩ������Ϣ,�ʼ�\������Ļ,����LOGO��*/
extern CA_RESULT_t YJ_ParseEmmData(UINT8 *pu8ReceiveData);
/*�ú������ڳ�ʼ���Կ������Ĵ���,ÿ�μ�⵽�п������Ӧ�õ��øú���*/
extern bool YJCASTB_CardInsert (void);
/*�ú��������ͷŶԿ�������һЩ��Դ,ÿ�μ�⵽�п��γ���Ӧ�õ��øú����ͷ������Դ*/
extern void YJCASTB_CardRemove(void);
/*�ú������ڴ����û���IPPV��Ŀ�����Ľ����ѡ��Ի����е��ǣ���ʾ�㲥��IPPV
��Ŀ��CA������Ǯ��д����һϵ�в�����ѡ��񣬲����������ţ�������ʾ�öԻ���
�Ի�����ʾ������STB�ṩ��CAS���ã��������˵��*/
extern void YJSTBCA_IppvHandle(IppvFocus_en enIppvFocusStatus);
/*��ȡ��ǰ��Ŀ��ECM PID,��ECM PID��Ϊ0����Ϊ���Ž�Ŀ������Ϊ�Ǽ��Ž�Ŀ*/
extern bool YJSTBCA_SetEcmPid(UINT16 u16EcmPid);
/*�ú������ڵõ���ǰ���Ž�Ŀ������Ȩ����(4B)�����ں�Ƶ����Ϣһ����ʾ*/
extern void YJCASTB_GetCurPrgAccreditEndDate(UINT8* Date);
/*�ú������ڵõ����������Ƶ����Ϣ*/
extern bool YJCASTB_DbFreInfoGet(CaFreInfo_t *pstCaDbFreInfo);
/*----------------------------------���Ͻӿ���CAS�ṩ��STB----------------------------------------*/
/*----------------------------------���½ӿ���STB�ṩ��CAS----------------------------------------*/


/*�ú�������ǰ�߳�*/
extern void YJSTBCA_Sleep(UINT16 u16MilliSeconds);
/*�ú������ڷ����ڴ�*/
extern void* YJSTBCA_Malloc(UINT16 u16BufSize);
/*�ú��������ͷ��ڴ�*/
extern void  YJSTBCA_Free(void *pBuf);
/*�ú������ڶ��������ָ�븳ֵ*/
extern void YJSTBCA_Memset(void *pDestBuf,UINT8 c,UINT16 u16Size);
/*�ú��������ڴ濽��*/
extern void YJSTBCA_Memcpy(void *pDestBuf,void *pSrcBuf,UINT16 u16Size);
/*�ú��������������ָ��Ƚ�*/
extern INT32 YJSTBCA_Memcmp(void *pDestBuf,void *pSrcBuf,UINT16 u16Size);
/*�ú��������ڴ��ƶ�*/
extern void YJSTBCA_Memmove(void *pDestBuf, const void *pSrcBuf, UINT16 u16Size );
/*���ַ������Ⱥ���*/
extern UINT16  YJSTBCA_Strlen(UINT8 *pString);
/*����ʽ���ַ��������ָ����ַ*/
extern int YJSTBCA_Sprintf(char * buf, const char *fmt, ...);
/*��ȡSTB���к�, ����Ϊ�Ÿ��ֽ�*/
extern void 	YJSTBCA_STBSerialNumGot(UINT8 *pu8SerialNum);
/*CW���������ú���*/
extern void YJSTBCA_ScrSetCW(UINT16 ecmpid ,const UINT8 *pu8OddKey,const UINT8 *pu8EvenKey, UINT8 u8CwLen);
/*���ܿ��������к���*/
extern bool YJSTBCA_SMCRun( const UINT8 * pu8Command, UINT16 u16CommandLen,
			          UINT8 *pu8Reply, UINT16 * pu16ReplyLen,UINT8 *pu8StatusWord);
extern CA_RESULT_t YJ_SMCDataDecode(UINT8 *pDataBuf, UINT16 DataLen, UINT8*ResBuf);
/*���ܿ���λ����*/
extern bool YJSTBCA_SMCReset(void);
extern CA_RESULT_t   YJ_SetCardHandshake(void);
extern UINT8  YJ_GetCardHandshakeNum(void);
/*�ʼ�������*/
extern void  YJSTBCA_EmailHandle(SYJCAEmailInfo *pstEmailInfo);
/*�������ݹ㲥���ݲ����Ľӿں���*/
extern void YJSTBCA_RadiateHandle(RADIATE_CHANNEL_INFO_T *pstRadiateChannelInfo);
/*�������洦����������pu8LogoName����ֽ�Ϊ8B����ͬ��Logo����������*/
extern void YJSTBCA_LogoHandle(UINT8 u8SwitchFlag,UINT8 *pu8LogoName,UINT8*pu8LogoData,UINT32 u32LogoLen);
extern void YJSTBCA_FingerPrint(UINT8 showflag,UINT8 *pu8strmessage);
/*������Ļ������*/
extern void YJSTBCA_OsdHandle(SYJCAOsdInfo *pstOsdInfo);

/*��ʾ������Ϣ����*/
extern void YJSTBCA_ShowCAMessage(UINT8 u8MsgType,UINT8 *pu8strMessage,UINT16  u16Timer);

/*��ȡ��ǰ���Ž�Ŀ��Video Pid*/
extern bool YJSTBCA_GetVideoPid(UINT16 *pu16VideoPid);

/*�ú���������ʾIPPV�Ի��򣬲���pstCaIppvInfo��CAS���ݸ�STB*/
extern void YJSTBCA_ShowIppv(CA_IPPVDATA_T *pstCaIppvInfo);

/*�ú����õ�ĿǰSmart Card��״̬������ֵΪ�棬��ʾ�Ѳ���YJ��������Ϊ��Ч������û�п�����*/
extern bool YJSTBCA_GetCardStatus(void);

/*�ú���������ʾIPPVǮ����״̬*/
extern void YJSTBCA_ShowSlotStatus(UINT8 *pu8IppvInfo);

/*�ú������ڵõ�Flash�й�濪��LOGO������*/
extern bool YJSTBCA_LogoGet(UINT8 *pu8LogoNameInFlash);

/*��ӡ�����ӿ�*/
extern INT32 YJCAS_PRINT(const char * fmt,...);

/*�ź�����ʼ������*/
extern void YJSTBCA_SemaphoreInit(YJCA_Semaphore *pSemaphore ,bool bInitVal);

/*�ź����ͷ�*/
extern void YJSTBCA_SemaphoreSignal(YJCA_Semaphore *pSemaphore );
/*�ź����ȴ�*/
extern void YJSTBCA_SemaphoreWait(YJCA_Semaphore *pSemaphore );

/*���񴴽�*/
extern bool YJSTBCA_RegisterTask(const UINT8 *pu8Name, UINT8 u8Priority,void *pTaskFun, void *pParam, UINT16 u16StackSize);

/*pstFreInfo�������������Ƶ��ȥ��ȡNIT Section,��ȡ�ɹ�����CA_SUCCESS��
���ò���*pu8Section���أ���ȡʧ�ܷ���CA_FAILURE
ע��:
	1.�ṹ������е�Ƶ������MΪ��λ
	2.��ȡ��������֤���NIT Buffer,����CA_SUCCESS,���򷵻�CA_FAILURE
	3.����ָ��Ƶ��ʧ��������1-3��,���ݹ󷽰���Ƶ��Ч�ʶ���
*/
extern CA_RESULT_t YJCASTB_AreaSectionGet(CaFreInfo_t *pstFreInfo,UINT8 *pu8Section);

/*��ȡ�ҽ���Ļ��������*/
extern void YJCASTB_AdsInfoGet(ServiceTxtAdsInfo *pstPidInfo,TxtStyleInfo *pstStyleInfo,AdsCharInfo *pstAdsCharInfo);

/*������ʱ�䵽MJDʱ���ת��*/
extern INT32 YJCASTB_TimeYmdToMjd(UINT16 usYear, UINT8 ucMonth, UINT8 ucDay);

/*���µ�ǰ��ϵͳʱ��*/
extern void YJCASTB_TimeUpdateTime(UINT32 usMjd, UINT8 ucHour, UINT8 ucMin, UINT8 ucSec);
/*�ҽ���Ļ����֪ͨ,CA���øú�����STBӦ�ü�ʱ����ϴιҽǵ�����*/
extern void YJCASTB_AdsSwitchNotify(void);
/*----------------------------------���Ͻӿ���STB�ṩ��CAS----------------------------------------*/

#endif

