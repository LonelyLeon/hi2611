
/*本规范应用接口请参照永新视博CAS21*/



#ifndef  _LXDTCA_USR_H_
#define 	_LXDTCA_USR_H_

#ifdef  __cplusplus
extern "C" {
#endif


#if 1
/*---------------------------CAS信息相关宏定义--------------------------*/
/*提示消息定义*/
#define	MESSAGE_CANCEL_TYPE_LXDTCA				0x00		/*清除CAMESSAGE显示*/
#define	MESSAGE_BADCARD_TYPE_LXDTCA			    0x01		/*无法识别卡*/
#define	MESSAGE_EXPICARD_TYPE_LXDTCA			0x02		/*智能卡已经过期，请更换新卡*/
#define	MESSAGE_INSERTCARD_TYPE_LXDTCA	        0x03		/*加扰节目，请插入智能卡*/
#define	MESSAGE_NOOPER_TYPE_LXDTCA				0x04		/*卡中不存在节目运营商*/
#define	MESSAGE_BLACKOUT_TYPE_LXDTCA			0x05		/*条件禁播*/
#define	MESSAGE_WATCHLEVEL_TYPE_LXDTCA			0x07		/*节目级别高于设定观看级别*/
#define	MESSAGE_PAIRING_TYPE_LXDTCA				0x08		/*节目要求机卡对应*/
#define	MESSAGE_NOENTITLE_TYPE_LXDTCA			0x09		/*没有授权*/
#define	MESSAGE_NOMONEY_TYPE_LXDTCA			    0x0B		/*卡内金额不足*/
#define MESSAGE_ERRREGION_TYPE_LXDTCA         	0x0C		/*区域不正确*/
#define	MESSAGE_STOP_SERVICE_LXDTCA				0x0D		/*用户已停机*/
#define	MESSAGE_STB_CARD_NOMARCH_LXDTCA		    0x0E		/*机卡不匹配*/
#define	MESSAGE_INSERT_PARENTCARD_LXDTCA		0x0F		/*请插入母卡认证*/
#define	MSSAGE_CARDINIT_FAIL_LXDTCA				0x10		/*卡初始化失败*/
#define	MSSAGE_CHILDCARD_AUTHE_FAIL_LXDTCA		0x11		/*子卡认证失败*/
#define	MSSAGE_CHILDCARD_AUTHE_SUCCE_LXDTCA 	0x12		/*子卡认证成功*/
#define	MSSAGE_CHILDCARD_INSERT_LXDTCA			0x13		/*请插入认证子卡*/
#define	MSSAGE_CHILDCARD_CANCELOK_LXDTCA		0x14		/*子卡取消成功*/
#define	MSSAGE_CHILDCARD_SETUPOK_LXDTCA		    0x15		/*子卡设置成功*/
#define	MSSAGE_PARENT_CONFIRM_FAIL_LXDTCA		0x16		/*母卡确认失败*/
#define	MSSAGE_PARENT_CONFIRM_SUCCE_LXDTCA	    0x17		/*母卡确认成功*/
#define	MSSAGE_STRING_LXDTCA					0xFF		/*显示CA字符串*/

#define	Email_IconHide						    0x00		/*隐藏邮件通知图标*/
#define	Email_New							    0x01		/*新邮件通知，显示新邮件图标*/
#define	Email_SpaceExhaust					    0x02		/*磁盘空间以满，图标闪烁*/

/*功能返回值定义*/
#define	LXDTCA_OK							    0x00
#define	LXDTCA_FAIL						        0x01		/*未知错误*/
#define	LXDTCA_POINTER_INVALID			        0x02		/*指针无效*/
#define	LXDTCA_CARD_INVALID				        0x03		/*智能卡无效*/
#define	LXDTCA_PIN_INVALID				        0x04		/* PIN码无效*/
#define	LXDTCA_DATASPACE_SMALL			        0x06		/*所给的空间不足*/
#define	LXDTCA_PIN_LOCK					        0x05		/*PIN码锁定*/
#define	LXDTCA_CARD_PAIROTHER_			        0x07		/*智能卡已经对应别的机顶盒*/
#define	LXDTCA_DATA_NOT_FIND				    0x08		/*没有找到所要的数据*/
#define	LXDTCA_PROG_STATUS_INVALID		        0x09		/*要购买的节目状态无效*/
#define	LXDTCA_CARD_NO_ROOM				        0x0A		/*智能卡没有空间存放购买的节目*/
#define	LXDTCA_WORKTIME_INVALID			        0x0B		/* 设定的工作时段无效*/
#define	LXDTCA_IPPV_CANNTDEL				    0x0C		/*IPPV节目不能被删除*/
#define	LXDTCA_CARD_NOPAIR				        0x0D		/*智能卡没有对应任何的机顶盒*/
#define	LXDTCA_WATCHRATING_INVALID		        0x0E		/*设定的观看级别无效*/
#define	LXDTCA_CARD_NOTSUPPORT		   	        0x0F		/* 当前智能卡不支持此功能*/
#define	LXDTCA_DATA_ERROR				        0x10		/* 数据错误，智能卡拒绝*/
#define	LXDTCA_FEEDTIME_NOT_ARRIVE		        0x11		/* 喂养时间未到，子卡不能被喂养*/
#define	LXDTCA_CARD_TYPEERROR			        0x12		/*子母卡喂养失败，插入智能卡类型错误*/
#define LXDTCA_IPPV_BUYDLG				        0x13		/*IPPV节目购买提示*/
#define LXDTCA_EMAIL_REFRESH				    0x14		/*EMAIL 重新刷新*/
#define LXDTCA_EMAIL_NOT_EXIST			        0x15		/*没有找到对应的邮件*/
#define LXDTCA_EMAIL_EXIST				        0x16		/*邮件已经存在*/
#define	LXDTCA_EMAIL_FULL					    0x17		/*邮箱满*/
#define LXDTCA_IPPV_NOMONEY				        0x18		/*钱包余额不足*/

#define LXDTCA_MAXLEN_SLOT				        1			/*目前支持1个钱包*/
#define LXDTCA_MAXLEN_OPERATOR			        1			/*目前支持1个运营商*/
#define	LXDTCA_MAXLEN_ENTITL				    240         /*目前支持的最大授权数*/
#define	LXDTCA_MAXLEN_IPPVP				        80

#define LXDTCA_MAXLEN_TVSPRIINFO			    14			/*运营商信息最大支持14个字节*/
#define	LXDTCA_MAXLEN_EMAIL_TITLE		        30			/*邮件标题的长度*/
#define	LXDTCA_MAXLEN_EMAIL				        30			/*最大邮件封数*/
#define	LXDTCA_MAXLEN_EMAIL_CONTENT		        200			/*邮件内容的长度*/
#define	LXDTCA_MAXLEN_OSD				        200			/*OSD内容的最大长度*/
#define	OSD_TOP							        0x01		/*OSD风格：显示在屏幕上方*/
#define	OSD_BOTTOM						        0x02		/*OSD风格：显示在屏幕下方*/



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

/*---------------------------CAS相关数据结构--------------------------*/
typedef D_U64 				U64;
typedef D_S64 				I64;
typedef int   				I32;
typedef short 			    I16;
typedef signed char		    I8;
typedef unsigned int   		LXDTCA_Semaphore ;
#define	LXDTCA_DATE		    U16	//LXDTCA服务器本地时间:以2000-1-1为0开始计算，每一天加一，列如：2000-1-8是7



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
	LXDTCA_DATE		    u16ExpriData;//LXDTCA服务器本地时间的相对值
}SLXDTCAEntitle;

typedef struct _LXDTCAEntitles
{
	U16	u16ProductCount;
	SLXDTCAEntitle		StEntitles[LXDTCA_MAXLEN_ENTITL];
}SLXDTCAEntitles;


typedef struct _LXDTCAIppvfo
{
	U16 u16ProductID;   //节目的ID
	U16	u16Price;       //节目价格
	U16	u16ExpiredDate;	//节目过期时间
}SLXDTCAIppvInfo;


typedef struct _LXDTCATVSSlotInfo
{
	U8	u8SlotID;	
	U8 	u8Ver;          //充值版本
	U16	u16CreditLimit; //信用度
	U16	u16Balance;     //已花的点数
}SLXDTCATVSSlotInfo;


typedef struct _AREA_INFO_S
{
	U8 u8CheckFlag;
	U8 u8AreaID;
   	U16 u16Frequency;
}AREA_INFO_t;


typedef struct _LXDTCAEmailHead
{
	
	U8	u8EmailFlag;    //0是删除邮件,1 是已读邮件, 3是新邮件
	U8	u8CreatTime[2]; //EMAIL创建的时间
	U8  u8EmailHead[LXDTCA_MAXLEN_EMAIL_TITLE+1];//邮件标题，最长为30
	U16	u16ActionID;    //Email ID  
	U16 u16Importance;  //重要性, 0：普通，1：重要
	
}SLXDTCAEmailHead;

typedef struct _LXDTCAEmailContent
{
	U8	u8Email[LXDTCA_MAXLEN_EMAIL_CONTENT+1];
}SLXDTCAEmailContent;


typedef struct _LXDTCAIppvBuyInfo
{
	U8			u8SlotID;
	U16			u16TVSID;            //运营商ID
	SLXDTCAIppvInfo	stLxDtCaIppvInfo;//IPPV节目信息
}SLXDTCAIppvBuyInfo;


#endif

/*---------------------------CAS相关函数结构--------------------------*/

/*机顶盒需要实现的的接口*/
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
/*该函数用于设置EMM,ECM过滤器*/
extern bool LXDTSTB2CA_GetPrivateData(U8 u8ReqID, const U8* pu8Filter, const U8* pu8Mask,U8 u8Len, U16 u16Pid, U8 u8WaitSeconds);
extern void LXDTSTB2CA_ScrSetCW(U16 u16EcmPID, const U8* pu8OddKey, const U8* pu8EvenKey,U8 u8KeyLen);
extern bool LXDTSTB2CA_SCPBRun( const U8 * pu8Command, U16 u16CommandLen,U8 *pu8Reply, U16 * pu16ReplyLen,U8 *pu8StatusWord);
extern void LXDTSTB2CA_ShowBuyMessage(U16 u16EcmPID,U8 u8MessageType);
/*机顶盒序列号暂时定为9个字节*/
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




/*CA内核需要实现的接口:*/

extern bool  LXDTCA2STB_Init(U8 u8Prior);
extern bool  LXDTCA2STB_IsLx(U16 u16CaId);
extern  void LXDTCA2STB_VersionGet(U8 *pu8CaVersion);//获取当前邋CA版本号,不超过12个字符
extern bool  LXDTCA2STB_CardIn(void);
extern void  LXDTCA2STB_CardOut(void);
extern U16  LXDTCA2STB_AreaCheck(U8 u8IsCheckArea,U8 *pu8Sec);
extern void  LXDTCA2STB_SetEcmPid(SLXDTCAServiceInfo* pServiceInfo);
extern void  LXDTCA2STB_SetEmmPid(U16 u16EmmPid);
extern void  LXDTCA2STB_EmmDataGet(U8 u8ReqID,bool bOK, U16 u16EmmPid, U8* pu8Rec, U16 u16Length);
/*
extern void  LXDTCA2STB_EmmDataGet(U8 u8ReqID,bool bOK, U16 u16Pid, U8* pu8ReceiveData, U16 u16Len);
8ReqID：		当前请求收取私有表的请求号，与LXDTSTB2CA_GetPrivateData相对应
bOK：     		确定 收取数据是否成功
pu8ReceiveData：收取的私有数据
u16Len：		收取到的私有数据的长度
注意:
1、这个函数和LXDTSTB2CA_GetPrivateData相对应，有一次LXDTSTB2CA_GetPrivateData调用就必须有一次LXDTCA2STB_EmmDataGet
2、CA内内核会保存过滤器的设置，如果没有调用LXDTCA2STB_EmmDataGet,那么CA内核认为这个过滤器正在过滤数据，此时不能重新设置过滤器
*/
extern void LXDTCA2STB_EcmDataGet(U8 u8ReqID,bool bOK, U16 u16EcmPid, U8* pu8Rec, U16 u16Length);//同上
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
	if(购买)调用如下
	{
		用户输入PIN;
		u16Ret = LXDTCA2STB_StopIPPVBuyDlg(TRUE, u16EcmPid,u8Pin);
		switch(u16Ret)
		{
			case LXDTCA_OK;
				printf("购买成功");
				break;
			case other:
				printf("购买失败");
				break;
			default:
				break;
		}
	}	
	else不购买调用如下
	{
		LXDTCA2STB_StopIPPVBuyDlg(FLASE,u16EcmPid,NULL,NULL);
	}

*/
extern U16 LXDTCA2STB_GetEmailHeads( SLXDTCAEmailHead* pEmailHead,U8*  pu8Count,U8*  pu8FromIndex);
/*
extern U16 LXDTCA2STB_GetEmailHeads( SLXDTCAEmailHead* pEmailHead,U8*  pu8Count,U8*  pu8FromIndex);
说明:
1、从前向后查询邮件头信息
2、pEmailHead :指向返回的EMAIL信息的数组
3、pu8Count   :输入数组的长度，返回实际获得的邮件个数
4、pu8FromIndex:输入的是从第几个EMAIL空间开始取,返回下次取的位置;如果想获得全部EAMIL信息，
	那么第一次调用的时候这个参数是0,以后每次调用都是用上次返回的值
*/
extern U16 LXDTCA2STB_GetEmailHead(U16 u16EmailID, SLXDTCAEmailHead* pEmailHead);
extern U16 LXDTCA2STB_GetEmailContent(U16 u16EmailID, SLXDTCAEmailContent* pEmailContent);
extern void LXDTCA2STB_DelEmail(U16 u16EmailID);
extern U16 LXDTCA2STB_GetEmailSpaceInfo( U8*  pu8EmailNum, U8* pu8EmptyNum);
extern void LXDTCA2STB_FormatMailBox(void);
extern U16 LXDTCA2STB_GetCardStatus(U16 u16TSID,bool *pbIsSubCard,U16 *pu16FeedCircle,U16 *pu16LastFeedDate,U8 *pu8MunCardNo);

#endif
