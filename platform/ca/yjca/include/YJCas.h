
/******************************************************************************
 * Copyright (c) 2008, 成都英集电子科技有限公司
 * All rights reserved.
 *
 * 文件名称： YJCas.h
 * 
 * 概    要:  条件接受系统编程接口。
 *            
 * 
 * 当前版本： 	1.0.0
 *
 * 作    者： 		Nbug
 * 创建日期： 	2008年7月30日
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
	UINT16 	u16EmailID;     							/*邮件的ID，以区分不同的邮件*/      
	UINT8  	au8MailTime[3];							/*三个十六进制的数据08/07/14*/
	UINT8  	au8EmailHead[MAIL_MAX_CAPTIONLEN];		/*邮件标题，最长为20*/
	UINT8  	au8Email[MAIL_MAX_CONTENTLEN]; 			/*Email的正文，最长512个汉字*/
}SYJCAEmailInfo;


typedef enum 
{
	EN_ALLPROG_NO_ROLL,   							/*有滚动字幕下来，所有台都不滚动*/
	EN_ALLPRO_ROLL,								/*有滚动字幕下来，所有台都滚动*/
	EN_PIDLIST_NO_ROLL,							/*有滚动字幕下来，只有PIDLIST中的节目不滚动*/
	EN_PIDLIST_ROLL,								/*有滚动字幕下来，只有PIDLIST中的节目滚动*/
}IsRoll_en;


typedef struct _YJCARollPrgSetInfo					/*该数据结构用于声明那些台需要滚动，那些台不需要滚动*/
{
	IsRoll_en enIsRoll;								/*根据该参数进行滚动字幕的处理*/
	UINT8	u8VideoPidNum;							/*滚动设置的节目数 */
	UINT16 	au16VideoPidList[MAX_VIDEOPID_NUM];		/*Video Pid列表*/
}SYJCARollPrgSetInfo;


typedef struct _YJCAOsdInfo
{
	UINT8 	u8RollTimes;							/*滚动次数，同一条滚动字幕可以滚动多次*/
	UINT8 	u8RollMode;								/*滚动模式，值为1表示上滚、为0表示下滚、为2表示左滚、为3表示右滚*/
	UINT8 	au8RollContent[MAX_ROLLDATA_LEN];		/*滚动字幕内容，最大512字*/
	UINT16 	u16TxtLen;								/*滚动字幕的实际长度*/
	UINT16 	u16OsdId;								/*滚动字幕的ID，以区分不同的字幕*/
	SYJCARollPrgSetInfo stCaRollPrgSetInfo;
} SYJCAOsdInfo;

typedef enum/*IPPV，用户选择是否购买IPPV*/
{
	FOCUSON_YES = 0,
	FOCUSON_NO
}IppvFocus_en;

typedef enum CA_RESULT_T/*CA返回状态*/
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
	UINT8 			ippv;								/*判断该节目是否为IPPV节目，1为IPPV节目，否则为非IPPV节目*/
	UINT16 			pid;									/*IPPV节目的VIDEO PID*/
	TIME_DATE_YJCA 	startDate;							/*IPPV节目开始播放时间*/
	TIME_DATE_YJCA	 time;								/*IPPV节目持续的播放时间，年月日三个变量无效*/
	TIME_DATE_YJCA 	currentDate;							/*当前日期时间*/
	UINT16 			money;								/*收看该节目所需要的费用，单位为分*/
}CA_IPPVDATA_T;


typedef struct RADIATE_Fre_INFO_S
{
	UINT32 		u32Frequency;						/*数据广播所在的频率*/
#if defined ( DVBC) 
    	UINT8 		u8Modulation;  
 	UINT32 		u32SymbolRate;	
#elif defined (DMBT) /*DMB_T*/
	UINT8		u8BandWidth;
	UINT32 		u32DemodPara;
#elif defined (DVBS)
	/*等待加入参数*/
	UINT8 		 u8Unuse;  
 	UINT32 		 u32SymbolRate;	
#endif
	UINT16 		u16VideoPid;						/*虚拟频道的VideoPID*/
	UINT16 		u16AudioPid;						/*虚拟频道的AudioPID*/

}RADIATE_Fre_INFO_T;	

typedef struct RADIATE_CHANNEL_INFO_S
{
	UINT8		u8RadiateType;						/*数据广播控制字节类型，0x00表示无数据广播，0x01表示正在数据广播*/
	UINT8 		u8MenuTableID;						/*菜单数据Table ID*/
	UINT8 		u8TitleTableID;						/*标题数据Table ID*/
	UINT8 		u8TxtTableID;						/*数据广播内容Table ID*/
	UINT8 		u8LogoTransContralTableID;			/*界面传输控制TableID*/
	UINT16 		u16ChannelPid;						/*数据广播PID*/
	UINT16 		u16LogoChannelPid;					/*界面传输PID*/
	RADIATE_Fre_INFO_T 	stFreInfo;
}RADIATE_CHANNEL_INFO_T;	

/*以下为广告频点信息*/
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
	/*等待加入-S的参数*/
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

/*---------------------------以下函数为CAS提供给STB调用-----------------------------*/


/*
 * 这个函数将对YJ CA做一些初始化操作，若初始化失败，将不能正常启动YJCA	
-*/
extern bool 	YJCASTB_Init(void);
extern UINT16   YJCASTB_EntitlCountGot(void);
extern bool     YJCASTB_EntitlListGot(UINT8 *pu8Data,UINT8 listNum);
/*
 * 这个函数将被用来判断是否是CASYSTEMID能够被当前CA识别	
-*/
extern bool  YJCASTB_IsYJCa(UINT16 u16CaSystemID);
/*该函数用于获取子母卡信息*/
extern bool YJCASTB_GetOperatorChildStatus(bool *pbIsChild,
                UINT8 *pu8DelayTime,UINT8 *pu8LastConfirmTime,UINT8 *pu8MainCardNo);
/*
*以下四个函数用于显示在CA信息菜单中,分别是:
	1、卡ID(10B):		*pu8CardId //该ID号去掉第4、5字节，其余8个字节用做EMM数据获取的地址过滤
	2、用户号(8B):	*pu8UserId
	3、设备号(9B):	*pu8DeviceId//就是STB序列号
	4、卡绑定(9B):	*pu8CardMatch
*/
extern bool YJCASTB_CardIdGot(UINT8 *pu8CardId);
extern bool YJCASTB_UserIdGot(UINT8 *pu8UserId);
extern bool YJCASTB_DeviceIdGot(UINT8 *pu8DeviceId);
extern bool YJCASTB_CardMatch(UINT8 *pu8CardMatch);
/*该函数用于获取YJCA的版本号已经库的日期*/
extern void YJCASTB_GetVer(UINT8 *pu8CaVer,UINT8 *pu8CaLibDate);
/*该函数用于获取最小授权期限*/
extern bool YJCASTB_MinAccreditDate(UINT8 *pu8MinAccreditDate);
/*有两个ECM的过滤条件：TABLEID分别为0x80,0x81*/
/*该函数用于处理得到的ECM数据,如IPPV数据,加密后的CW控制字等*/
extern CA_RESULT_t  YJ_ParseEcmData(UINT8 *pu8ReceiveData);
/*EMM过滤条件：两个均为TABLEID为0x82*/
/*当智能卡ID 后面四个字节为0xff 是区域广播码此时要匹配前四个字节*/
/*该函数用于处理得到的EMM数据,如授权控制信息,邮件\滚动字幕,开机LOGO等*/
extern CA_RESULT_t YJ_ParseEmmData(UINT8 *pu8ReceiveData);
/*该函数用于初始化对卡操作的处理,每次检测到有卡插入后都应该调用该函数*/
extern bool YJCASTB_CardInsert (void);
/*该函数用于释放对卡操作的一些资源,每次检测到有卡拔出后都应该调用该函数释放相关资源*/
extern void YJCASTB_CardRemove(void);
/*该函数用于处理用户对IPPV节目操作的结果，选择对话框中的是，表示点播该IPPV
节目，CA会做扣钱、写卡等一系列操作，选择否，不能正常播放，反复提示该对话框，
对话框显示函数由STB提供，CAS调用，详见以下说明*/
extern void YJSTBCA_IppvHandle(IppvFocus_en enIppvFocusStatus);
/*获取当前节目的ECM PID,若ECM PID不为0，则为加扰节目，否则为非加扰节目*/
extern bool YJSTBCA_SetEcmPid(UINT16 u16EcmPid);
/*该函数用于得到当前加扰节目最终授权日期(4B)，用于和频道信息一起显示*/
extern void YJCASTB_GetCurPrgAccreditEndDate(UINT8* Date);
/*该函数用于得到各类广告的主频点信息*/
extern bool YJCASTB_DbFreInfoGet(CaFreInfo_t *pstCaDbFreInfo);
/*----------------------------------以上接口是CAS提供给STB----------------------------------------*/
/*----------------------------------以下接口是STB提供给CAS----------------------------------------*/


/*该函数挂起当前线程*/
extern void YJSTBCA_Sleep(UINT16 u16MilliSeconds);
/*该函数用于分配内存*/
extern void* YJSTBCA_Malloc(UINT16 u16BufSize);
/*该函数用于释放内存*/
extern void  YJSTBCA_Free(void *pBuf);
/*该函数用于对数组或者指针赋值*/
extern void YJSTBCA_Memset(void *pDestBuf,UINT8 c,UINT16 u16Size);
/*该函数用于内存拷贝*/
extern void YJSTBCA_Memcpy(void *pDestBuf,void *pSrcBuf,UINT16 u16Size);
/*该函数用于数组或者指针比较*/
extern INT32 YJSTBCA_Memcmp(void *pDestBuf,void *pSrcBuf,UINT16 u16Size);
/*该函数用于内存移动*/
extern void YJSTBCA_Memmove(void *pDestBuf, const void *pSrcBuf, UINT16 u16Size );
/*求字符串长度函数*/
extern UINT16  YJSTBCA_Strlen(UINT8 *pString);
/*将格式化字符串输出到指定地址*/
extern int YJSTBCA_Sprintf(char * buf, const char *fmt, ...);
/*获取STB序列号, 长度为九个字节*/
extern void 	YJSTBCA_STBSerialNumGot(UINT8 *pu8SerialNum);
/*CW控制字设置函数*/
extern void YJSTBCA_ScrSetCW(UINT16 ecmpid ,const UINT8 *pu8OddKey,const UINT8 *pu8EvenKey, UINT8 u8CwLen);
/*智能卡命令运行函数*/
extern bool YJSTBCA_SMCRun( const UINT8 * pu8Command, UINT16 u16CommandLen,
			          UINT8 *pu8Reply, UINT16 * pu16ReplyLen,UINT8 *pu8StatusWord);
extern CA_RESULT_t YJ_SMCDataDecode(UINT8 *pDataBuf, UINT16 DataLen, UINT8*ResBuf);
/*智能卡复位函数*/
extern bool YJSTBCA_SMCReset(void);
extern CA_RESULT_t   YJ_SetCardHandshake(void);
extern UINT8  YJ_GetCardHandshakeNum(void);
/*邮件处理函数*/
extern void  YJSTBCA_EmailHandle(SYJCAEmailInfo *pstEmailInfo);
/*传送数据广播数据参数的接口函数*/
extern void YJSTBCA_RadiateHandle(RADIATE_CHANNEL_INFO_T *pstRadiateChannelInfo);
/*开机画面处理函数，参数pu8LogoName最大字节为8B，相同的Logo不在做更换*/
extern void YJSTBCA_LogoHandle(UINT8 u8SwitchFlag,UINT8 *pu8LogoName,UINT8*pu8LogoData,UINT32 u32LogoLen);
extern void YJSTBCA_FingerPrint(UINT8 showflag,UINT8 *pu8strmessage);
/*滚动字幕处理函数*/
extern void YJSTBCA_OsdHandle(SYJCAOsdInfo *pstOsdInfo);

/*显示警告信息函数*/
extern void YJSTBCA_ShowCAMessage(UINT8 u8MsgType,UINT8 *pu8strMessage,UINT16  u16Timer);

/*获取当前加扰节目的Video Pid*/
extern bool YJSTBCA_GetVideoPid(UINT16 *pu16VideoPid);

/*该函数用于显示IPPV对话框，参数pstCaIppvInfo由CAS传递给STB*/
extern void YJSTBCA_ShowIppv(CA_IPPVDATA_T *pstCaIppvInfo);

/*该函数得到目前Smart Card的状态，返回值为真，表示已插入YJ卡，否则为无效卡或者没有卡插入*/
extern bool YJSTBCA_GetCardStatus(void);

/*该函数用于显示IPPV钱包的状态*/
extern void YJSTBCA_ShowSlotStatus(UINT8 *pu8IppvInfo);

/*该函数用于得到Flash中广告开机LOGO的名字*/
extern bool YJSTBCA_LogoGet(UINT8 *pu8LogoNameInFlash);

/*打印函数接口*/
extern INT32 YJCAS_PRINT(const char * fmt,...);

/*信号量初始化函数*/
extern void YJSTBCA_SemaphoreInit(YJCA_Semaphore *pSemaphore ,bool bInitVal);

/*信号量释放*/
extern void YJSTBCA_SemaphoreSignal(YJCA_Semaphore *pSemaphore );
/*信号量等待*/
extern void YJSTBCA_SemaphoreWait(YJCA_Semaphore *pSemaphore );

/*任务创建*/
extern bool YJSTBCA_RegisterTask(const UINT8 *pu8Name, UINT8 u8Priority,void *pTaskFun, void *pParam, UINT16 u16StackSize);

/*pstFreInfo输入参数，到该频点去获取NIT Section,获取成功返回CA_SUCCESS，
并用参数*pu8Section传回，获取失败返回CA_FAILURE
注意:
	1.结构体参数中的频率是以M为单位
	2.获取到区域验证码的NIT Buffer,返回CA_SUCCESS,否则返回CA_FAILURE
	3.锁定指定频点失败请重试1-3次,根据贵方案锁频的效率而定
*/
extern CA_RESULT_t YJCASTB_AreaSectionGet(CaFreInfo_t *pstFreInfo,UINT8 *pu8Section);

/*获取挂角字幕各项数据*/
extern void YJCASTB_AdsInfoGet(ServiceTxtAdsInfo *pstPidInfo,TxtStyleInfo *pstStyleInfo,AdsCharInfo *pstAdsCharInfo);

/*年月日时间到MJD时间的转换*/
extern INT32 YJCASTB_TimeYmdToMjd(UINT16 usYear, UINT8 ucMonth, UINT8 ucDay);

/*更新当前的系统时间*/
extern void YJCASTB_TimeUpdateTime(UINT32 usMjd, UINT8 ucHour, UINT8 ucMin, UINT8 ucSec);
/*挂角字幕更换通知,CA调用该函数后，STB应该及时清除上次挂角的数据*/
extern void YJCASTB_AdsSwitchNotify(void);
/*----------------------------------以上接口是STB提供给CAS----------------------------------------*/

#endif

