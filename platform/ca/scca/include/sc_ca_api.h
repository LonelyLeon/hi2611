#ifndef __SC_CA_H__
#define __SC_CA_H__


/****************************************************************/
/****************************************************************/
/*��ʾ��Ϣ*/
#define		MESSAGE_CANCEL_TYPE					0x00
#define		MESSAGE_BADCARD_TYPE				0x01		/*�޷�ʶ�𿨣�����ʹ��*/
#define		MESSAGE_EXPICARD_TYPE				0x02		/*���ܿ��Ѿ����ڣ�������¿�*/
#define		MESSAGE_CARD_INIT_TYPE				0x03		/*���ܿ����ڳ�ʼ��*/
#define		MESSAGE_INSERTCARD_TYPE				0x04		/*���ܽ�Ŀ����������ܿ�*/
#define		MESSAGE_CARD_INIT_ERR_TYPE			0x05		/*���ܿ���ʼ��ʧ��*/
#define		MESSAGE_STB_NO_CARD_TYPE			0x06		/*�������в��������ܿ�*/
#define		MESSAGE_CARD_INIT_OK_TYPE			0x07		/*���ܿ���ʼ�����*/
#define		MESSAGE_NOOPER_TYPE					0x10		/*���в����ڽ�Ŀ��Ӫ��*/
#define		MESSAGE_CARDSTOP_TYPE				0x11		/*���ܿ���ͣ��*/
#define		MESSAGE_OUTWORKTIME_TYPE			0x12		/*���ڹ���ʱ����*/
#define		MESSAGE_WATCHLEVEL_TYPE				0x13		/*��Ŀ��������趨�ۿ�����*/
#define		MESSAGE_PAIRING_TYPE					0x14		/*����û�ж�Ӧ*/
#define		MESSAGE_NOENTITLE_TYPE				0x20		/*��û�й���ý�Ŀ*/
#define		MESSAGE_DECRYPTFAIL_TYPE				0x21		/*��Ŀ����ʧ��*/
#define		MESSAGE_NOMONEY_TYPE				0x22		/*���ڽ���*/
#define		MESSAGE_ERRREGION_TYPE				0x23		/*������ȷ*/
#define		MESSAGE_FINGER_SHOW_TYPE			0x24		/*ָ����ʾ*/
#define		MESSAGE_FINGER_DISAPPEAR_TYPE		0x30		/*ָ������*/
#define		MESSAGE_CARDNOTACTIVE_TYPE			0x31		/*���ܿ�δ����*/
#define		MESSAGE_CARDLOGOUT_TYPE				0x32		/*���ܿ���ע��*/
#define		MESSAGE_CONDITION_CTL_TYPE			0x33		/*�ò�Ʒ���޲�*/
#define		MESSAGE_DESCRA_NOENTITLE_TYPE		0x34		/*��Ȩ�ѵ��ڣ�����ϵ��Ӫ��*/
#define		MESSAGE_ENTITLE_UPDATE_TYPE			0x35		/*��Ȩ�����У����Եȣ�*/
#define		MESSAGE_CARD_UNWONTED_TYPE			0x36		/*���ܿ��ڲ��쳣*/
#define		MESSAGE_CHANGEPRO_TOO_FAST_TYPE			0x37		/*�벻ҪƵ����̨*/

#define    	MESSAGE_MS_PAIR_OK_TYPE				0x40		/* ��ĸ����Գɹ� */
#define    	MESSAGE_MS_PAIR_FAILED_TYPE			0x41		/* ��ĸ�����ʧ��,�����²�����ȷ��ĸ�� */
#define    	MESSAGE_MS_REPAIR_TYPE				0x42		/* �ӿ������º�ĸ����� */
#define		MESSAGE_CARD_MATCH_OK_TYPE			0x43		/*������Գɹ�*/
#define		MESSAGE_CARD_REMATCH_TYPE			0x44		/*���»������*/
#define		MESSAGE_CANCEL_MATCH_TYPE			0x45		/*ȡ���������*/

#define		MESSAGE_NEWEMAIL_TYPE				0x50		/* ��ʾ���ʼ�ͼ�� */
#define		MESSAGE_OVEREMAIL_TYPE				0x51		/* ��ʾ�ʼ����� */
#define		MESSAGE_HIDE_NEWEMAIL_TYPE			0x52		/* �������ʼ�ͼ��*/
#define		MESSAGE_EXIGENT_PROG_TYPE			0x53		/*�����㲥*/
#define		MESSAGE_EXIGENT_PROG_STOP_TYPE		0x54		/*ֹͣ�����㲥*/
#define		MESSAGE_CARD_UNLOCK_OK_TYPE		0x55		/*���ܿ���������ɹ�*/
#define		MESSAGE_PURSER_UPDATE_TYPE			0x56		/*����Ǯ������*/
#define		MESSAGE_NET_ERR_LOCK_TYPE			0x57		/*�����쳣����������*/
#define		MESSAGE_SYSTEM_ERR_LOCK_TYPE		0x58		/*ϵͳ�쳣����������*/
#define		MESSAGE_NET_ERR_UNLOCK_TYPE			0x59		/*�����쳣����*/
#define		MESSAGE_SYSTEM_ERR_UNLOCK_TYPE		0x60		/*ϵͳ�쳣����*/

/*OSD��Ϣ*/
#define		MESSAGE_SHOWOSD_TYPE				0x61		/*��ʾOSD��Ϣ*/
#define		MESSAGE_HIDEOSD_TYPE					0x62		/*����OSD��Ϣ*/


/*��ʾ�Ի���*/
#define		MESSAGE_CARDISDUE_TYPE					0x70		/*���ܿ�����Ƿ�Ѵ߽�*/
#define		MESSAGE_IPPVBUY_TYPE					0x71		/*IPPV������ʾ�� */
#define		MESSAGE_IPPV_OUTTIME_TYPE				0x72		/*IPPV��Ŀ����*/
#define		MESSAGE_HIDE_IPPVBUY_TYPE				0x73		/*���� IPPV������ʾ�� */
#define		MESSAGE_CONDITION_SEARCH_TYPE			0x74		/*����NIT��������Ŀ*/

/****************************************************************/
/****************************************************************/

#define		SCCA_OPERATOR_NAME_LEN				(40)
#define		SCCA_OPERATOR_PHONE_LEN				(40)
#define		SCCA_OPERATOR_ADDRESS_LEN			(80)

#define    IN                         /*��������(��������)*/
#define	   OUT                      /*��������(�ش�����)*/
#define    SCCA_CARD_REGION_DESC   0XA5/*NIT�������ܿ�����ID������*/

#ifndef		NULL
#define		NULL		0
#endif

#ifndef TRUE
#define TRUE				(1)
#endif

#ifndef FALSE
#define FALSE			(0)
#endif

#ifndef BOOL
#define BOOL		unsigned char
#endif

typedef unsigned int os_sem_t;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int  u32;
/* delete by lim 2015.2.27
typedef char				INT8;
typedef unsigned char		UINT8;
typedef short				INT16;
typedef unsigned short		UINT16;
typedef int				INT32;
typedef unsigned int		UINT32;
*/
typedef UINT32			SCCA_Semaphore;
typedef UINT32			SCCA_MsgQueue;

#define IN
#define OUT


#define ECM_TABLE_ID  0x80
#define ECM_TABLE_ID_ODD   0x81
#define EMM_TABLE_ID   		0x82

//ʱ���ʽ
typedef struct _ST_TIME_INFO
{
	UINT8 	ucHour;
	UINT8 	ucMinute;
	UINT8	ucSecond;
}ST_TIME_INFO;

//����ʱ���ʽ
typedef struct _ST_DATE_TIME_INFO
{
	UINT16	usYear;
	UINT8	ucMonth;
	UINT8	ucDay;
	UINT8 	ucHour;
	UINT8 	ucMinute;
	UINT8	ucSecond;
}ST_DATE_TIME_INFO;

//�ʼ���Ϣ
typedef struct _ST_MAIL_INFO
{
	UINT8				ucMailID;				// Mail ID
	UINT8				ucNewFlag;				// 0 �������ʼ� 1�����ʼ�
	UINT8				aucMailTitle[32 + 1];		// �ʼ����⣬�Ϊ30
	UINT8				aucMailSender[32 + 1];	//�ʼ�������
	ST_DATE_TIME_INFO	stSendTime;				//�ʼ�����ʱ��(����ʱ��)
}ST_MAIL_INFO;

//��Ʒ��Ȩ��Ϣ
#define CAS_PRODUCT_NAME_MAX_LEN (30)
typedef struct  _ST_PRODUCT_ENTITLE
{
	UINT8			ucEnableType;		/*��Ȩģʽ*/
	UINT8          		ucRecoadFlag;		/* ��û���� ��0��������¼�� 1������¼��*/
	UINT16        		usProductID;		/* ��ƷID */
	ST_DATE_TIME_INFO 	stBeginTime;		/* ��Ʒ��ʼʱ��*/
	ST_DATE_TIME_INFO 	stEndTime;		/* ��Ʒ����ʱ��*/
	UINT8			ucProductName[CAS_PRODUCT_NAME_MAX_LEN];
}ST_PRODUCT_ENTITLE;

//�ʼ��б���Ϣ
typedef struct _ST_MAILLIST_INFO
{
	ST_MAIL_INFO	stMailInfo[50];
	UINT8 		ucMailNum;

}ST_MAILLIST_INFO;

//��Ӫ����Ϣ
typedef struct _ST_OPERATOR_INFO
{
	UINT8 aucOperatorName[SCCA_OPERATOR_NAME_LEN];
	UINT8 aucOperatorPhone[SCCA_OPERATOR_PHONE_LEN];
	UINT8 aucOperatorAddress[SCCA_OPERATOR_ADDRESS_LEN];

}ST_OPERATOR_INFO;

//IPPV��Ϣ
typedef struct _ST_IPPV_INFO
{
	UINT8			aucIppvName[33];
	UINT8			aucEventID[4];
	UINT16/*UINT8*/	ucProviderID;
	UINT16			usPrice;
	UINT16			usEcmPid;
	ST_DATE_TIME_INFO	stBeginTime;
	ST_DATE_TIME_INFO	stEndTime;

}ST_IPPV_INFO;

//ָ����ʾλ��
typedef enum _EN_FINGER_SHOW_POS
{
	SHOW_LEFT_TOP = 0,
	SHOW_RIGHT_TOP,
	SHOW_LEFT_BOTTOM,
	SHOW_RIGHT_BOTTOM,
	SHOW_BY_COORDINATE,

}EN_FINGER_SHOW_POS;

//ָ����ʾ��Ϣ
typedef struct _ST_FINGER_SHOW_INFO
{
	EN_FINGER_SHOW_POS enShowPostion;		/*��ʾλ��*/
	UINT8 aucFontShowColor[4];				/*������ʾ��ɫ*/
	UINT8 aucBackShowColor[4];				/*������ʾ��ɫ*/
	UINT16 usShowXPos;						/*��ʾX����*/
	UINT16 usShowYPos;						/*��ʾY����*/
	UINT8 ucShowFont;						/*��ʾ����*/
	UINT8 ucShowFontSize;					/*��ʾ�����С*/
	UINT8 pucShowContent[20];				/*��ʾ����*/

}ST_FINGER_SHOW_INFO;

//OSD��ʾλ��
typedef enum _EN_OSD_SHOW_POS
{
	SHOW_TOP = 0,					//�ڶ�����ʾ
	SHOW_BOTTOM,					//�ڵײ���ʾ
	SHOW_TOP_BOTTOM,				//�ڶ����͵ײ�ͬʱ��ʾ
	SHOW_LEFT,						//�������ʾ
	SHOW_RIGHT,					//���ұ���ʾ
	SHOW_LEFT_RIGHT,				//����ߺ��ұ�ͬʱ��ʾ
}EN_OSD_SHOW_POS;

//OSD��ʾ��Ϣ
typedef struct _ST_OSD_SHOW_INFO
{
	EN_OSD_SHOW_POS	ucDisplayPos;
	UINT8	ucFontType;
	UINT8	ucFontSize;
	UINT8	aucBackgroundColor[4];
	UINT8	aucDisplayColor[4];
	UINT16	usContentSize;
	UINT16	usGetBufferSize;
	UINT8* 	pucDisplayBuffer;

}ST_OSD_SHOW_INFO;

//����ʱ����Ϣ
typedef struct _ST_WORKTIME_INFO
{
	ST_TIME_INFO stBeginTime;
	ST_TIME_INFO stEndTime;
}ST_WORKTIME_INFO;

typedef enum _EN_CA_LANGUAGE
{
	CA_LANGUAGE_CHINESE,
	CA_LANGUAGE_ENGLISH,
	CA_LANGUAGE_TOTAL,
}EN_CA_LANGUAGE;

typedef struct _ST_CA_EXIGENT_PROGRAM
{
	UINT16 usNetWorkID;
	UINT16 usTransportStreamID;
	UINT16 usServiceID;
}ST_CA_EXIGENT_PROGRAM;

typedef struct _ST_CA_MSG_QUEUE
{
	UINT32 uiFirstPara;
	UINT32 uiSecondPara;
	UINT32 uiThirdPara;
	UINT32 uiFourthPara;
}ST_CA_MSG_QUEUE;

typedef enum _EN_CAS_SHOW_MSG_TYPE
{
	CAS_MSG_TYPE_PICTURE,//��ʾͼƬ
	CAS_MSG_TYPE_FINGER_SHOW,//��ʾָ��
	CAS_MSG_TYPE_OSD,//��ʾosd
	CAS_MSG_TYPE_NOTE_LONG_TIME,//������ʾ����Ϣ
	CAS_MSG_TYPE_NOTE_SHORT_TIME,//��ʾʱ��̵ܶ���Ϣ
	CAS_MSG_TYPE_DIALOG,//�Ի���
	CAS_MSG_TYPE_PROGRESS,//������
	CAS_MSG_TYPE_NOT_SHOW,//ֻ�ǽ���ĳ�ֲ��������漰����ʾ
	CAS_MSG_TYPE_TOTAL,
}EN_CAS_SHOW_MSG_TYPE;

//��������ֵ����
typedef enum _EN_ERR_CAS
{
	/*�������Ͷ���*/
	CA_ERROR_OK = 0x00,
	CA_CARD_FAILURE,                           /*��ͨѶʧ��*/
	CA_CARD_SUCCESS,                             /*��ͨѶ�ɹ�*/
	CA_CARD_NOMONEY,                            /*���ڽ���*/
	CA_CARD_WRITEPURSER_ERROR,          /*дǮ��ʧ��*/
	CA_CARD_ERROR_REGION,		     /*������ȷ*/
	CA_CARD_CHECK_PIN_OK,                   /*��֤PIN��ɹ�*/
	CA_CARD_CHECK_PIN_ERROR,		     /*��֤PIN��ʧ��*/
	CA_CARD_CHANGE_PIN_FAILED,        /*�޸�PINʧ��*/
	CA_CARD_CHECK_PIN_LOCK,               /*��֤PIN������Ѵ�����ļ�����*/
	CA_CARD_UNLOCK_PIN_FAILED,	     /*����PINʧ��*/
	CA_ERROR_IC_INVALID ,                     /* ���������޿�����Ч��         */
	CA_ERROR_CARD_PAIROTHER,            /* ���ܿ��Ѿ���Ӧ��Ļ�����     */
	CA_ERROR_CARD_STOP,        			/* ����ͣ��    */
	CA_ERROR_CARD_CANCELED,        		/* ����ע��  */
	CA_ERROR_CARD_OUTTIME,			/* ���ѹ��� */
	CA_ERROR_CARD_PENDING,        			/* ��δ����    */
	CA_ERROR_CARD_NOPAIR,                  /* ��Ҫ��������*/
	CA_ERROR_PARAMETER,                      /*��������*/
	CA_ERROR_FLASHADDR,                      /*FLASH��ַ����ΪNULL��*/
	CA_ERROR_UNKOWNDATA,                  /*δ֪���ݣ�����CA����Ҫ������*/
	CA_ERROR_REPEATINGDATA,             /*�ظ�������*/
	CA_ERROR_PAIRED_OK,                      /*��ĸ����Գɹ�*/
	CA_ERROR_WORKTIME,                         /*���ڹ���ʱ��*/
	CA_ERROR_WATCH_LEVLE,                 /*��ǰ��Ŀ�ۿ�����������ü���*/
	CA_ERROR_PAIRED_FAILED,              /*��ĸ�����ʧ��*/
	CA_ERROR_PAIRED_REPAIRED,          /*��ĸ����Ҫ�������*/
	CA_ERROR_NOENTITLE,                      /*û����Ȩ*/
	CA_ERROR_IPPV_NOBUY,                    /*IPPVδ����*/
	CA_ERROR_NETTEST,                         /*��������*/
	CA_ERROR_CRC,                                 /*CRC����*/
	CA_ERROR_WORKTIME_FORMAT,		/*����ʱ�θ�ʽ����*/
	CA_ERROR_MALLOC_ERR,			/*�ڴ����ʧ��*/
	CA_ERROR_CONDITION_CTL,			/*�ò�Ʒ�޲�*/
	CA_ERROR_NET_ERR,			/*�����쳣��STB������*/
	CA_ERROR_SYS_ERR,			/*ϵͳ�쳣��STB������*/
	CA_ERROR_STATE_ERR,			/*״̬������*/
	CA_ERROR_CARD_UNWONTED,			/*���������쳣*/
	CA_ERROR_OPT_TOO_FAST,		/*����̫Ƶ��*/
	CA_ERROR_UNKNOWN,                       /* δ֪����*/
}EN_ERR_CAS;

typedef enum _EN_CA_MSG_QUEUE_MODE
{
	CA_MSG_QUEUE_WAIT,
	CA_MSG_QUEUE_NOWAIT,
	CA_MSG_QUEUE_UNKNOW,
}EN_CA_MSG_QUEUE_MODE;

typedef enum _EN_CA_DATA_ID
{
	ECM_DATA_ID_ODD = 1,//ECM_DATA_ID
	//ECM_DATA_ID_EVEN = 2,
	EMM_DATA_ID_USER  = 2,//EMM_DATA_ID
	EMM_DATA_ID_BD = 3,

}EN_CA_DATA_ID;

typedef enum _EN_CA_CARD_STATE
{
	CA_CARD_STATE_NO_CARD = 0,
	CA_CARD_STATE_INITIALIZING,	
	CA_CARD_STATE_OK,	
	CA_CARD_STATE_FAIL,
}EN_CA_CARD_STATE;

/***********************************�������ṩ��CA�ĺ���**************************************/

extern void SCCA_printf(IN const INT8 *string,...);
extern void SCCA_GetBuffer(OUT UINT32 * puiStartAddr,  OUT UINT32 * puiSize);
extern void SCCA_FlashRead(UINT32 uiStartAddr,  OUT UINT8 * pucData,  IN UINT32 * puiLen);
extern void SCCA_FlashWrite(UINT32 uiStartAddr, IN UINT8* pucData, IN UINT32 uiLen);
extern void SCCA_FlashErase(void);
extern void* SCCA_Malloc(UINT16 usBufferSize);
extern void SCCA_Memset(IN void* pucBuffer, UINT8 ucValue, UINT32 uiSize);
extern void SCCA_Memcpy(IN void* pucDestBuffer, IN void* pucSourceBuffer, UINT32 uiSize);
extern INT32 SCCA_Memcmp(IN void* pucDestBuffer, IN void* pucSourceBuffer, UINT32 uiSize);
extern INT32 SCCA_Sprintf(IN UINT8* pucDestBuffer, IN const UINT8* pucFormatBuffer, ...);
extern INT32 SCCA_StrLen(IN const UINT8* pucFormatBuffer);
extern void SCCA_Free(IN void* pucBuffer);
extern void SCCA_Sleep(UINT16 usMilliSeconds);
extern void SCCA_SemaphoreInit(IN SCCA_Semaphore* puiSemaphore , UINT8 ucInitVal);
extern void SCCA_ReleaseSemaphore(IN SCCA_Semaphore* puiSemaphore);
extern void SCCA_WaitSemaphore(IN SCCA_Semaphore* puiSemaphore);
extern void SCCA_ShowMessage(UINT8 ucMessageType, EN_CAS_SHOW_MSG_TYPE  enShowType, IN UINT8 * pucMessage);
extern void SCCA_SetCW(UINT16 usEcmPID, IN UINT8* pucOddKey, IN UINT8* pucEvenKey, IN UINT8* pucKeyLen);
extern void SCCA_StopCurrentProgram(void);
extern void SCCA_PlayCurrentProgram(void);
extern void SCCA_SendDataToSmartCard(IN UINT8* pucSend, IN UINT8 *pucSendLen, OUT UINT8* pucReceive,
											OUT UINT8 *pucReceiveLen, UINT32 uiTimeout, OUT UINT8* pucStatusWord );
extern BOOL SCCA_RegisterTask (IN INT8* pucName, UINT8 ucPriority, IN void* pTaskFun );
extern BOOL SCCA_SCReset(UINT8 *pucAtr, UINT8 *pucLen);
extern BOOL SCCA_SetFilter(EN_CA_DATA_ID enDataID, IN UINT8* pucFilter, IN UINT8* pucMask,
							UINT8 ucFilterLen, UINT16 usPID, UINT8 ucWaitSeconds);
extern BOOL SCCA_StopFilter(EN_CA_DATA_ID enDataID, UINT16 usPID);
extern BOOL SCCA_QueryProgram(UINT16 usNetWorkID, UINT16 usTransportStreamID, UINT16 usServiceID);
extern BOOL SCCA_MsgQueueInit(IN INT8* pucName, UINT32* uiMsgQueueHandle, UINT32 uiMaxMsgLen, EN_CA_MSG_QUEUE_MODE enMode);
extern BOOL SCCA_MsgQueueGetMsg(UINT32 uiMsgHandle, ST_CA_MSG_QUEUE* pstMsg, EN_CA_MSG_QUEUE_MODE enMode, UINT32 uiWaitMilliSecond);
extern BOOL SCCA_MsgQueueSendMsg(UINT32 uiMsgHandle, ST_CA_MSG_QUEUE* pstMsg);
extern UINT32 SCCA_GetSystemTime();
extern void SCCA_SetSystemTime(IN INT32 uiTime);
/*****************************************************************************************************/

/*******************************CA �ṩ�������е��õĺ���********************************/
void SCCA_PlayChanged();
void SCCA_NitChanged(UINT16 nNit);
void SCCA_SetEcmPid(UINT16 usPid);
void SCCA_SetEmmPid(UINT16 usPid);
void SCCA_SetCardState(UINT8  ucInOrOut);
void SCCA_SetSysLanguage(EN_CA_LANGUAGE enLanguage);
void SCCA_OsdOneTimeOk(void);
void SCCA_GetPrivateData(UINT16 usPid, EN_CA_DATA_ID enDataID, IN UINT8* pucReceiveData, UINT16 usDataLen);
BOOL SCCA_IsSCCa(UINT16 usCaSystemID);
BOOL SCCA_QueryBroadcastEntitle(void);
EN_ERR_CAS SCCA_SC_UnlockPin(void);
EN_ERR_CAS SCCA_DelEmail(UINT8 ucMailID);
EN_ERR_CAS SCCA_DelAllEmail(void);
EN_ERR_CAS SCCA_GetCardRegion(OUT UINT8 * pucCardRegion);
EN_ERR_CAS SCCA_GetOperatorID(OUT UINT8 * pucOperator);
EN_ERR_CAS SCCA_GetOperatorInfo(ST_OPERATOR_INFO* pstOperatorInfo );
EN_ERR_CAS SCCA_SetWatchLevelState(UINT8 ucOpenOrClose);
EN_ERR_CAS SCCA_SetWorkTimeState(UINT8 ucOpenOrClose);
EN_ERR_CAS SCCA_IppvBuy(UINT8 ucBuy,UINT8 ucProvideID) ;
EN_ERR_CAS SCCA_Init(UINT8 ucPriority, EN_CA_LANGUAGE enLanguage);
EN_ERR_CAS SCCA_GetProductNumber(UINT32 uiOperatorID, OUT UINT32 *puiNumber);
EN_ERR_CAS SCCA_GetProductInfo (UINT32 uiOperatorID,  UINT32 uiStartNo,  UINT32 uiReadNum, OUT ST_PRODUCT_ENTITLE *pstProductEntitles);
EN_ERR_CAS SCCA_GetCardNo(OUT UINT8 * pucCardNO, OUT UINT8* pucCardType);
EN_ERR_CAS SCCA_GetMasterCard(UINT8 * pucMasterCardNO);
EN_ERR_CAS SCCA_GetCAVer(OUT UINT8 * pucCAVersion);
EN_ERR_CAS SCCA_GetLCO(OUT UINT8 aucLco[8]);
EN_ERR_CAS SCCA_GetGroupId(OUT UINT8 aucGroupId[16]);
EN_ERR_CAS SCCA_GetCardVersion(OUT UINT8 aucCardVer[32]);
EN_ERR_CAS SCCA_GetPurserInfo(UINT8 ucNo, OUT UINT8 * pucPurser);
EN_ERR_CAS SCCA_GetEmailNumber(OUT UINT8 *pstEmailNo);
EN_ERR_CAS SCCA_GetEmailInfoList(OUT ST_MAILLIST_INFO *pstEmailInfoList);
EN_ERR_CAS SCCA_GetEmailContent(UINT32 uiEmailID, OUT UINT8* pucContentBuf, OUT UINT16 *pusContentLen);
EN_ERR_CAS SCCA_GetCardState(void);
EN_ERR_CAS SCCA_ChangePin(IN UINT8* pucOldPin, IN UINT8* pucNewPin, OUT UINT8* ucOddTimes);
EN_ERR_CAS SCCA_PurseCheckPin(UINT8* pucPin, UINT8* pucOddTimes);
EN_ERR_CAS SCCA_SetWorkTime(IN UINT8* pucPin, OUT UINT8* pucOddTimes, IN ST_WORKTIME_INFO* pstWorkTime);
EN_ERR_CAS SCCA_SetWatchLevel(IN UINT8* pucPin, OUT UINT8* pucOddTimes, IN UINT8* pucWorkLevel);
EN_ERR_CAS SCCA_GetWorkTime(OUT ST_WORKTIME_INFO* pstWorkTime);
EN_ERR_CAS SCCA_GetWorkLevel(OUT UINT8* pucWorkLevel);
BOOL SCCA_ConvertTime(IN INT32 uiTime,OUT ST_DATE_TIME_INFO *pstTmInfo);
UINT32 SCCA_MakeTime(ST_DATE_TIME_INFO *pstTmInfo);
#endif

