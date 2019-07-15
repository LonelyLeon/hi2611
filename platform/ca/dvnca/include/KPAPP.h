#ifndef KPAPP_H_20101212
#define KPAPP_H_20101212

/***************************************
* @1-1KPlus 数据类型
***************************************/
#if 0
#ifndef U8
typedef unsigned char    U8;
#endif
#ifndef U16
typedef unsigned short   U16;
#endif
#ifndef U32
typedef unsigned int     U32;
#endif
#endif

typedef	unsigned int     KP_MSG_QUEUE;

typedef enum
{
    KP_RET_SUCCESS,
    KP_RET_SYSTEM_ERROR,
    KP_RET_PARAMETER_ERROR,
    KP_RET_MALLOC_ERROR,
    KP_RET_API_FAIL,

    KP_RET_SEMAPHORE_FAIL,
    KP_RET_QUEUE_FAIL,
    KP_RET_FILTER_FAIL,

    KP_RET_NO_ENOUGH_PID,
    KP_RET_PID_PROCESSED,
    KP_RET_PID_CLASH,
    KP_RET_NO_PID_FOUND,
    KP_RET_FAIL,

    KP_RET_INVALID_PROVIDER,
    KP_RET_PIN_LENGHT_INVALID,
    KP_RET_SAME_PIN,
    KP_RET_PIN_ERROR,

    KP_RET_UNKNOWN
}KP_RESULT;
typedef enum
{
    KP_QUEUE_BLOCKING,
    KP_QUEUE_NONBLOCKING
}KP_QUEUE_MODE;

/***************************************
* @1-2KPlus 宏定义
***************************************/
#define KPCAS_USERID_LEN             16
#define KPCAS_FEATURE_DATA_LEN       32

#define KPCAS_PIN_LEN                6
#define KPCAS_PRODUCT_CNT            512
#define KPCAS_IPP_CNT                256
#define KPCAS_WALLET_CNT             2
#define KPCAS_PROVIDER_CNT           2

#define KPCAS_MAIL_TITLE_LEN         32
#define KPCAS_MAIL_CONTENT_LEN       256
/***************************************
* @1-3KPlus 提示信息
***************************************/
#define KPCA_MESSAGE_CANCEL          0x0    //used
//@ CA 库版本与前端不匹配
#define KPCA_MESSAGE_NO_MATCH        0x1    //used
//@ CA 未激活, 请与运营商联系
#define KPCA_MESSAGE_NO_ACTIVE       0x2    //used
//@ 区域码不匹配
#define KPCA_MESSAGE_AREA_NOT_MATCH  0x3    //used
//@ 产品ID 错误, 网络里面没有该产品
#define KPCA_MESSAGE_ERROR_PRODUCT   0x7    //used
//@ 运营商ID 错误, 网络里面没有该运营商
#define KPCA_MESSAGE_ERROR_PROVIDER  0x8    //used
//@ 节目没有授权
#define KPCA_MESSAGE_NO_ENTITLE      0x9    //used
//@ 节目授权已过期
#define KPCA_MESSAGE_ENTITLE_EXPIRED 0xa    //used
//@ 节目授权未开始
#define KPCA_MESSAGE_ENTITLE_NOSTART 0xb    //used
//@ 产品ID 冲突
#define KPCA_MESSAGE_PRODUCT_CLASH   0xc    //used
//@ 条件禁播
#define KPCA_MESSAGE_SERVICE_FORCE   0xd    //used
//@ 观看等级不够
#define KPCA_MESSAGE_OUT_RATING      0x11   //used
//@ 不在工作时段内
#define KPCA_MESSAGE_OUT_WORKTIME    0x12   //used
//@ PIN 已重置
#define KPCA_MESSAGE_RESET_PIN       0x13   //used
//@ 分组禁播
#define KPCA_MESSAGE_GROUP_FORCE     0x14   //used
//@ 紧急事件
#define KPCA_MESSAGE_EMERGENCY       0x15   //used
//@ 产品信息已更新
#define KPCA_MESSAGE_PRODUCT_UPDATE  0x1A   //used
//@ CA 已过期
#define KPCA_MESSAGE_FREEZE          0x20   //used
/***************************************
* @2KPlus 数据结构
***************************************/
//@provider
typedef struct
{
    U16               p_providerID;
    U8                p_providerInfo[KPCAS_FEATURE_DATA_LEN + 1];
    U8                p_reserved[3];
}KPProvider;

//@wallet
typedef struct
{
    U8                p_walletID;
    U32               p_amount;  //余额
    U32               p_balance; //已消费的点数
}KPWallet;

//@subscription
typedef struct
{
    U16               p_productID;
    unsigned int      p_beginTime;
    unsigned int      p_endTime;
}KPProduct;
typedef struct
{
    U16               p_productCount;
    KPProduct         s_product[KPCAS_PRODUCT_CNT];
}KPSubscription;

/***************************************
* @3KPlus 实现,提供给APP使用
***************************************/
U8   KPCAAPP_init(void);
void KPCAAPP_timer(void);
void KPCAAPP_close(void);
//@获取KPCAS system id
U16  KPCAAPP_GetCASID(void);

//@输入ECM/EMM pid给CAS
U8   KPCAAPP_StartECMPid(U16 pid);
U8   KPCAAPP_StartEMMPid(U16 pid);
U8   KPCAAPP_StopPid(U16 pid);
U8   KPCAAPP_SetPrivateData(U8 queueID, U8 *buf, U16 len);

//@
U8   KPCAAPP_GetCAVersion(U8 *buf);
U8   KPCAAPP_GetLicenceid(U8 *buf);
U8   KPCAAPP_GetUniqueid(U8 *buf);
U8   KPCAAPP_GetGroupid(U8 *buf);
U8   KPCAAPP_GetAreaCode(U32 *value);
U8   KPCAAPP_GetAttribute(U8 *buf);
U8   KPCAAPP_GetExtendDescriptor(U8 u8index, U8 *buf);

//@获取provider Info
U8   KPCAAPP_GetProviderInfo(KPProvider *providerIDInfo);
//@获取钱包
U8   KPCAAPP_GetWalletsInfo(U16 providerID, KPWallet *Info);
//@获取授权列表
U8   KPCAAPP_GetSubscriptionsInfo(U16 providerID, KPSubscription *Info);

//@pin
U8   KPCAAPP_SetPIN(U8 *oldPIN, U8 *newPIN);
//@rating
U8   KPCAAPP_GetRating(U8 *rating);
U8   KPCAAPP_SetRating(U8 *PIN, U8 rating);
//@worktime
U8   KPCAAPP_GetWorkTime(U8 *sHour, U8 *sMin, U8 *sSec, U8 *eHour, U8 *eMin, U8 *eSec);
U8   KPCAAPP_SetWorkTime(U8 *PIN, U8 sHour, U8 sMin, U8 sSec, U8 eHour, U8 eMin, U8 eSec);

/***************************************
* @4APP实现,提供给KPlus使用
***************************************/
//@Queue
U8   KPAPPCA_QueueCreate(U8* queueName, U16 maxElements, U16 elementSize, KP_MSG_QUEUE* queueID);
U8   KPAPPCA_QueueDestroy(KP_MSG_QUEUE queueID);
U8   KPAPPCA_QueueEmpty(KP_MSG_QUEUE queueID);
U8   KPAPPCA_QueueSend(KP_MSG_QUEUE queueID, U8 *data);
U8   KPAPPCA_QueueRecv(KP_MSG_QUEUE queueID, U8 mode, U32 timeout, U8 *data);
//@Memory
void *KPAPPCA_Alloc(U32 size);
void KPAPPCA_Free(void *p);
U8   KPAPPCA_Memcpy(void *dptr, const void *sptr, U16 len);
//@获取User id + STBID + CHIPID, buf have 8 bytes
//U16  KPAPPCA_GetLicenceId(U8 *buf);
//U16  KPAPPCA_GetSTBId(U8 *buf);
//U16  KPAPPCA_GetChipId(U8 *buf);
//@输出CAS状态给STB
void KPAPPCA_Report(U16 ecmpid, U16 code);
//@输出Filter参数给STB
U16  KPAPPCA_StartFilter(U8 FilterID, U16 PID, U16 TableID, U8 Period, U16 *SectByte, U32 QueueID);
U16  KPAPPCA_StopFilter(U8 FilterID);
//@操作Flash
U16  KPAPPCA_ReadFlash(U16 offsetAddr, U8 *data, U16 len);
U16  KPAPPCA_WriteFlash(U16 offsetAddr, U8 *data, U16 len);

//@操作解扰器
U16  KPAPPCA_GetDescrambleNum(void);
//@输出CW 给STB
U8   KPAPPCA_SetCW(U16 ecmpid, U8 *oddKey, U8 *evenKey, U8 keyLen);

//@输出格式化文本
U8   KPAPPCA_FormatText(U8 *text, U16 len);

//@Other api
U8   KPAPPCA_ShowFinger(U16 ecmpid, U8 *msg);
U8   KPAPPCA_ShowWatermark(U8 *msg);

//@打印信息接口
void KPAPPCA_PrintMsg(const char *fmt, ...);

unsigned long hi2610_getTick(void);

#endif
