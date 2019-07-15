
/*���淶Ӧ�ýӿ�����������Ӳ�CAS21*/



#ifndef  _LXDTCA_USR_H_
#define 	_LXDTCA_USR_H_

#ifdef  __cplusplus
extern "C" {
#endif


#if 1
/*---------------------------CAS��Ϣ��غ궨��--------------------------*/
/*��ʾ��Ϣ����*/
#define	MESSAGE_CANCEL_TYPE_LXDTCA				0x00		/*���CAMESSAGE��ʾ*/
#define	MESSAGE_BADCARD_TYPE_LXDTCA			    0x01		/*�޷�ʶ��*/
#define	MESSAGE_EXPICARD_TYPE_LXDTCA			0x02		/*���ܿ��Ѿ����ڣ�������¿�*/
#define	MESSAGE_INSERTCARD_TYPE_LXDTCA	        0x03		/*���Ž�Ŀ����������ܿ�*/
#define	MESSAGE_NOOPER_TYPE_LXDTCA				0x04		/*���в����ڽ�Ŀ��Ӫ��*/
#define	MESSAGE_BLACKOUT_TYPE_LXDTCA			0x05		/*��������*/
#define	MESSAGE_WATCHLEVEL_TYPE_LXDTCA			0x07		/*��Ŀ��������趨�ۿ�����*/
#define	MESSAGE_PAIRING_TYPE_LXDTCA				0x08		/*��ĿҪ�������Ӧ*/
#define	MESSAGE_NOENTITLE_TYPE_LXDTCA			0x09		/*û����Ȩ*/
#define	MESSAGE_NOMONEY_TYPE_LXDTCA			    0x0B		/*���ڽ���*/
#define MESSAGE_ERRREGION_TYPE_LXDTCA         	0x0C		/*������ȷ*/
#define	MESSAGE_STOP_SERVICE_LXDTCA				0x0D		/*�û���ͣ��*/
#define	MESSAGE_STB_CARD_NOMARCH_LXDTCA		    0x0E		/*������ƥ��*/
#define	MESSAGE_INSERT_PARENTCARD_LXDTCA		0x0F		/*�����ĸ����֤*/
#define	MSSAGE_CARDINIT_FAIL_LXDTCA				0x10		/*����ʼ��ʧ��*/
#define	MSSAGE_CHILDCARD_AUTHE_FAIL_LXDTCA		0x11		/*�ӿ���֤ʧ��*/
#define	MSSAGE_CHILDCARD_AUTHE_SUCCE_LXDTCA 	0x12		/*�ӿ���֤�ɹ�*/
#define	MSSAGE_CHILDCARD_INSERT_LXDTCA			0x13		/*�������֤�ӿ�*/
#define	MSSAGE_CHILDCARD_CANCELOK_LXDTCA		0x14		/*�ӿ�ȡ���ɹ�*/
#define	MSSAGE_CHILDCARD_SETUPOK_LXDTCA		    0x15		/*�ӿ����óɹ�*/
#define	MSSAGE_PARENT_CONFIRM_FAIL_LXDTCA		0x16		/*ĸ��ȷ��ʧ��*/
#define	MSSAGE_PARENT_CONFIRM_SUCCE_LXDTCA	    0x17		/*ĸ��ȷ�ϳɹ�*/
#define	MSSAGE_STRING_LXDTCA					0xFF		/*��ʾCA�ַ���*/

#define	Email_IconHide						    0x00		/*�����ʼ�֪ͨͼ��*/
#define	Email_New							    0x01		/*���ʼ�֪ͨ����ʾ���ʼ�ͼ��*/
#define	Email_SpaceExhaust					    0x02		/*���̿ռ�������ͼ����˸*/

/*���ܷ���ֵ����*/
#define	LXDTCA_OK							    0x00
#define	LXDTCA_FAIL						        0x01		/*δ֪����*/
#define	LXDTCA_POINTER_INVALID			        0x02		/*ָ����Ч*/
#define	LXDTCA_CARD_INVALID				        0x03		/*���ܿ���Ч*/
#define	LXDTCA_PIN_INVALID				        0x04		/* PIN����Ч*/
#define	LXDTCA_DATASPACE_SMALL			        0x06		/*�����Ŀռ䲻��*/
#define	LXDTCA_PIN_LOCK					        0x05		/*PIN������*/
#define	LXDTCA_CARD_PAIROTHER_			        0x07		/*���ܿ��Ѿ���Ӧ��Ļ�����*/
#define	LXDTCA_DATA_NOT_FIND				    0x08		/*û���ҵ���Ҫ������*/
#define	LXDTCA_PROG_STATUS_INVALID		        0x09		/*Ҫ����Ľ�Ŀ״̬��Ч*/
#define	LXDTCA_CARD_NO_ROOM				        0x0A		/*���ܿ�û�пռ��Ź���Ľ�Ŀ*/
#define	LXDTCA_WORKTIME_INVALID			        0x0B		/* �趨�Ĺ���ʱ����Ч*/
#define	LXDTCA_IPPV_CANNTDEL				    0x0C		/*IPPV��Ŀ���ܱ�ɾ��*/
#define	LXDTCA_CARD_NOPAIR				        0x0D		/*���ܿ�û�ж�Ӧ�κεĻ�����*/
#define	LXDTCA_WATCHRATING_INVALID		        0x0E		/*�趨�Ĺۿ�������Ч*/
#define	LXDTCA_CARD_NOTSUPPORT		   	        0x0F		/* ��ǰ���ܿ���֧�ִ˹���*/
#define	LXDTCA_DATA_ERROR				        0x10		/* ���ݴ������ܿ��ܾ�*/
#define	LXDTCA_FEEDTIME_NOT_ARRIVE		        0x11		/* ι��ʱ��δ�����ӿ����ܱ�ι��*/
#define	LXDTCA_CARD_TYPEERROR			        0x12		/*��ĸ��ι��ʧ�ܣ��������ܿ����ʹ���*/
#define LXDTCA_IPPV_BUYDLG				        0x13		/*IPPV��Ŀ������ʾ*/
#define LXDTCA_EMAIL_REFRESH				    0x14		/*EMAIL ����ˢ��*/
#define LXDTCA_EMAIL_NOT_EXIST			        0x15		/*û���ҵ���Ӧ���ʼ�*/
#define LXDTCA_EMAIL_EXIST				        0x16		/*�ʼ��Ѿ�����*/
#define	LXDTCA_EMAIL_FULL					    0x17		/*������*/
#define LXDTCA_IPPV_NOMONEY				        0x18		/*Ǯ������*/

#define LXDTCA_MAXLEN_SLOT				        1			/*Ŀǰ֧��1��Ǯ��*/
#define LXDTCA_MAXLEN_OPERATOR			        1			/*Ŀǰ֧��1����Ӫ��*/
#define	LXDTCA_MAXLEN_ENTITL				    240         /*Ŀǰ֧�ֵ������Ȩ��*/
#define	LXDTCA_MAXLEN_IPPVP				        80

#define LXDTCA_MAXLEN_TVSPRIINFO			    14			/*��Ӫ����Ϣ���֧��14���ֽ�*/
#define	LXDTCA_MAXLEN_EMAIL_TITLE		        30			/*�ʼ�����ĳ���*/
#define	LXDTCA_MAXLEN_EMAIL				        30			/*����ʼ�����*/
#define	LXDTCA_MAXLEN_EMAIL_CONTENT		        200			/*�ʼ����ݵĳ���*/
#define	LXDTCA_MAXLEN_OSD				        200			/*OSD���ݵ���󳤶�*/
#define	OSD_TOP							        0x01		/*OSD�����ʾ����Ļ�Ϸ�*/
#define	OSD_BOTTOM						        0x02		/*OSD�����ʾ����Ļ�·�*/



#ifndef true
#define true           1                                          
#endif

#ifndef false
#define false          0   
#endif

#ifndef	NULL
#define	NULL		   0
#endif

#ifndef bool 
#define bool           unsigned char
#endif

#ifndef DWORD
#define DWORD          unsigned long
#endif

/*---------------------------CAS������ݽṹ--------------------------*/
typedef D_U64 				U64;
typedef D_S64 				I64;
typedef int   				I32;
typedef short 			    I16;
typedef signed char		    I8;
typedef unsigned int   		LXDTCA_Semaphore ;
#define	LXDTCA_DATE		    U16	//LXDTCA����������ʱ��:��2000-1-1Ϊ0��ʼ���㣬ÿһ���һ�����磺2000-1-8��7



typedef struct _LXDTCAServiceInfo
{
	U16	u16EcmPid;								
	U16	u16ServiceID;
}SLXDTCAServiceInfo;


typedef struct _LXDTCAOperatorInfo
{
	U16	u16OperatorID;
	U8	u8TVSPriInfo[LXDTCA_MAXLEN_TVSPRIINFO+1];
}SLXDTCAOperatorInfo;



typedef struct _LXDTCAEntitle
{
	U16 u16ProductID;
	LXDTCA_DATE		    u16ExpriData;//LXDTCA����������ʱ������ֵ
}SLXDTCAEntitle;

typedef struct _LXDTCAEntitles
{
	U16	u16ProductCount;
	SLXDTCAEntitle		StEntitles[LXDTCA_MAXLEN_ENTITL];
}SLXDTCAEntitles;


typedef struct _LXDTCAIppvfo
{
	U16 u16ProductID;   //��Ŀ��ID
	U16	u16Price;       //��Ŀ�۸�
	U16	u16ExpiredDate;	//��Ŀ����ʱ��
}SLXDTCAIppvInfo;


typedef struct _LXDTCATVSSlotInfo
{
	U8	u8SlotID;	
	U8 	u8Ver;          //��ֵ�汾
	U16	u16CreditLimit; //���ö�
	U16	u16Balance;     //�ѻ��ĵ���
}SLXDTCATVSSlotInfo;


typedef struct _AREA_INFO_S
{
	U8 u8CheckFlag;
	U8 u8AreaID;
   	U16 u16Frequency;
}AREA_INFO_t;


typedef struct _LXDTCAEmailHead
{
	
	U8	u8EmailFlag;    //0��ɾ���ʼ�,1 ���Ѷ��ʼ�, 3�����ʼ�
	U8	u8CreatTime[2]; //EMAIL������ʱ��
	U8  u8EmailHead[LXDTCA_MAXLEN_EMAIL_TITLE+1];//�ʼ����⣬�Ϊ30
	U16	u16ActionID;    //Email ID  
	U16 u16Importance;  //��Ҫ��, 0����ͨ��1����Ҫ
	
}SLXDTCAEmailHead;

typedef struct _LXDTCAEmailContent
{
	U8	u8Email[LXDTCA_MAXLEN_EMAIL_CONTENT+1];
}SLXDTCAEmailContent;


typedef struct _LXDTCAIppvBuyInfo
{
	U8			u8SlotID;
	U16			u16TVSID;            //��Ӫ��ID
	SLXDTCAIppvInfo	stLxDtCaIppvInfo;//IPPV��Ŀ��Ϣ
}SLXDTCAIppvBuyInfo;


#endif

/*---------------------------CAS��غ����ṹ--------------------------*/

/*��������Ҫʵ�ֵĵĽӿ�*/
extern void LXDTSTB2CA_GetBuffer(  U32* pu32StartAddr, U32* pu32Size);
extern void LXDTSTB2CA_ReadBuffer(U32 pu32StartAddr, U8* pu8Data, U32 u32Len);
extern void LXDTSTB2CA_WriteBuffer(U32 pu32StartAddr,U8* pu8Data,U32 u32Len);
extern void LXDTSTB2CA_Sleep(U16 u16MilliSeconds );
extern void* LXDTSTB2CA_Malloc(U16 u16BufSize);
extern void LXDTSTB2CA_Free(void* pBuf);
extern void LXDTSTB2CA_Memset(void* pDestBuf,U8 c,U16 u16Size);
extern void LXDTSTB2CA_Memcpy(void* pDestBuf,void* pSrcBuf,U16 u16Size);
extern void LXDTSTB2CA_Memmove(void *pDestBuf, const void *pSrcBuf, U16 u16Size );
extern I32  LXDTSTB2CA_Memcmp(void *pDestBuf,void *pSrcBuf,U16 u16Size);
extern U16 LXDTSTB2CA_Strlen(char* pString);
extern void LXDTSTB2CA_SemaphoreInit(  LXDTCA_Semaphore* pSemaphore ,bool bInitVal);
extern void LXDTSTB2CA_SemaphoreSignal( LXDTCA_Semaphore* pSemaphore );
extern void LXDTSTB2CA_SemaphoreWait(  LXDTCA_Semaphore* pSemaphore );
extern bool LXDTSTB2CA_CardReset(void);
extern bool LXDTSTB2CA_RegisterTask( const char * pu8Name, U8 u8Priority, void* pTaskFun,void* pParam, U16 nStackSize);
/*�ú�����������EMM,ECM������*/
extern bool LXDTSTB2CA_GetPrivateData(U8 u8ReqID, const U8* pu8Filter, const U8* pu8Mask,U8 u8Len, U16 u16Pid, U8 u8WaitSeconds);
extern void LXDTSTB2CA_ScrSetCW(U16 u16EcmPID, const U8* pu8OddKey, const U8* pu8EvenKey,U8 u8KeyLen);
extern bool LXDTSTB2CA_SCPBRun( const U8 * pu8Command, U16 u16CommandLen,U8 *pu8Reply, U16 * pu16ReplyLen,U8 *pu8StatusWord);
extern void LXDTSTB2CA_ShowBuyMessage(U16 u16EcmPID,U8 u8MessageType);
/*���������к���ʱ��Ϊ9���ֽ�*/
extern void LXDTSTB2CA_GetSTBID(U8 *pu8StbId);
extern void LXDTSTB2CA_Printf(const char * fmt,...);
extern I32  LXDTSTB2CA_Sprintf(char * buf, const char *fmt, ...);
extern void LXDTSTB2CA_ShowOSDMessage(U8 u8Style, U8 *pu8Mesage);
extern void LXDTSTB2CA_HideOSDMessage(U8 u8Style);
extern U8   LXDTSTB2CA_GetRollOSDTimes(U8 u8Style);
extern void LXDTSTB2CA_EmailNotifyIcon(U8 u8Show,U32 u32EmailID);
extern void LXDTSTB2CA_HideIppvDlg(U16 u16EcmPid);
extern void LXDTSTB2CA_StartIppvBuyDlg(U16 u16EcmPid, SLXDTCAIppvBuyInfo *pIppvProgram);
extern I32  LXDTSTB2CA_EarseBuffer(U32 uiStartAdd, U32 iLen);




/*CA�ں���Ҫʵ�ֵĽӿ�:*/

extern bool  LXDTCA2STB_Init(U8 u8Prior);
extern bool  LXDTCA2STB_IsLx(U16 u16CaId);
extern  void LXDTCA2STB_VersionGet(U8 *pu8CaVersion);//��ȡ��ǰ��CA�汾��,������12���ַ�
extern bool  LXDTCA2STB_CardIn(void);
extern void  LXDTCA2STB_CardOut(void);
extern U16  LXDTCA2STB_AreaCheck(U8 u8IsCheckArea,U8 *pu8Sec);
extern void  LXDTCA2STB_SetEcmPid(SLXDTCAServiceInfo* pServiceInfo);
extern void  LXDTCA2STB_SetEmmPid(U16 u16EmmPid);
extern void  LXDTCA2STB_EmmDataGet(U8 u8ReqID,bool bOK, U16 u16EmmPid, U8* pu8Rec, U16 u16Length);
/*
extern void  LXDTCA2STB_EmmDataGet(U8 u8ReqID,bool bOK, U16 u16Pid, U8* pu8ReceiveData, U16 u16Len);
8ReqID��		��ǰ������ȡ˽�б������ţ���LXDTSTB2CA_GetPrivateData���Ӧ
bOK��     		ȷ�� ��ȡ�����Ƿ�ɹ�
pu8ReceiveData����ȡ��˽������
u16Len��		��ȡ����˽�����ݵĳ���
ע��:
1�����������LXDTSTB2CA_GetPrivateData���Ӧ����һ��LXDTSTB2CA_GetPrivateData���þͱ�����һ��LXDTCA2STB_EmmDataGet
2��CA���ں˻ᱣ������������ã����û�е���LXDTCA2STB_EmmDataGet,��ôCA�ں���Ϊ������������ڹ������ݣ���ʱ�����������ù�����
*/
extern void LXDTCA2STB_EcmDataGet(U8 u8ReqID,bool bOK, U16 u16EcmPid, U8* pu8Rec, U16 u16Length);//ͬ��
extern U16 LXDTCA2STB_ModifyPin(U8* pu8OldPinCode, U8* pu8NewPinCode);
extern U16 LXDTCA2STB_GetRating( U8* pu8Rating);
extern U16 LXDTCA2STB_SetRating(U8* pu8PinCode,U8 u8Rating);
extern U16 LXDTCA2STB_GetOperatorIds(U16* p16TSID);
extern U16 LXDTCA2STB_GetOperatorInfo(U16 u16TSID,SLXDTCAOperatorInfo* pOperatorInfo);
extern U16 LXDTCA2STB_GetAreaInfo(U16 u16TSID, U16 *pu16AreaCode,U16 *pu16NitAreaCode);
extern U16 LXDTCA2STB_PaireInfo(U8* pu8SmcCardId, U8* pu8MatchStbId,U8 *pu8CurrentStbId);
extern U16 LXDTCA2STB_GetEntitlesInfo(U16 u16TSID, SLXDTCAEntitles* pServiceEntitles);
extern void LXDTCA2STB_RefreshUI(void);
extern U16 LXDTCA2STB_GetIPPVProgram(U16 u16TSID,U8 u8SlotID, SLXDTCAIppvInfo * pIppv, U16* p16Number);
extern U16 LXDTCA2STB_GetSlotIDs(U16 u16TSID ,U8* pu8SlotID);
extern U16 LXDTCA2STB_GetSlotInfo(U16 u16TSID ,U8 u8SlotID, SLXDTCATVSSlotInfo* pSlotInfo);
extern U16 LXDTCA2STB_StopIPPVBuyDlg(bool bBuyProgram, U16 u16EcmPid, U8* pu8PinCode);
/*
extern U16 LXDTCA2STB_StopIPPVBuyDlg(bool bBuyProgram, U16 u16EcmPid, U8* pu8PinCode);
	if(����)��������
	{
		�û�����PIN;
		u16Ret = LXDTCA2STB_StopIPPVBuyDlg(TRUE, u16EcmPid,u8Pin);
		switch(u16Ret)
		{
			case LXDTCA_OK;
				printf("����ɹ�");
				break;
			case other:
				printf("����ʧ��");
				break;
			default:
				break;
		}
	}	
	else�������������
	{
		LXDTCA2STB_StopIPPVBuyDlg(FLASE,u16EcmPid,NULL,NULL);
	}

*/
extern U16 LXDTCA2STB_GetEmailHeads( SLXDTCAEmailHead* pEmailHead,U8*  pu8Count,U8*  pu8FromIndex);
/*
extern U16 LXDTCA2STB_GetEmailHeads( SLXDTCAEmailHead* pEmailHead,U8*  pu8Count,U8*  pu8FromIndex);
˵��:
1����ǰ����ѯ�ʼ�ͷ��Ϣ
2��pEmailHead :ָ�򷵻ص�EMAIL��Ϣ������
3��pu8Count   :��������ĳ��ȣ�����ʵ�ʻ�õ��ʼ�����
4��pu8FromIndex:������Ǵӵڼ���EMAIL�ռ俪ʼȡ,�����´�ȡ��λ��;�������ȫ��EAMIL��Ϣ��
	��ô��һ�ε��õ�ʱ�����������0,�Ժ�ÿ�ε��ö������ϴη��ص�ֵ
*/
extern U16 LXDTCA2STB_GetEmailHead(U16 u16EmailID, SLXDTCAEmailHead* pEmailHead);
extern U16 LXDTCA2STB_GetEmailContent(U16 u16EmailID, SLXDTCAEmailContent* pEmailContent);
extern void LXDTCA2STB_DelEmail(U16 u16EmailID);
extern U16 LXDTCA2STB_GetEmailSpaceInfo( U8*  pu8EmailNum, U8* pu8EmptyNum);
extern void LXDTCA2STB_FormatMailBox(void);
extern U16 LXDTCA2STB_GetCardStatus(U16 u16TSID,bool *pbIsSubCard,U16 *pu16FeedCircle,U16 *pu16LastFeedDate,U8 *pu8MunCardNo);

#endif
