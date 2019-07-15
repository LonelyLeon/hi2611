/*------------------------------------------------------------------------------------------*
filename    :      Tr_Cas.h
Description :      The TOPREAL CAS API 
Version     :      V2.0.1
**-----------------------------------------------------------------------------------------*/
/* Copyright:   (C) BEIJING Topreal TECHNOLOGIES CO.LTD All Rights Reserved. */

/*
There are two kinds of function interface.
MC_XX..(): It resides in MCELL library, and called by user's application.
TRDRV_XX..(): It should be accomplished by user, and called by MCELL.
*/

#ifndef  _TR_CAS_H
#define  _TR_CAS_H 

#ifdef  __cplusplus
extern "C" {
#endif

#include "../ca/camid/include/hrca_config.h"

/***************************************************************************************/
/*------------------------- Micro, data type and structure ----------------------------*/
/***************************************************************************************/
typedef     signed char     S8;         //!< 8 bit signed integer.
typedef     signed short    S16;        //!< 16 bit signed integer.
typedef     signed long     S32;        //!< 32 bit signed integer.

#ifdef TFALSE
    #undef TFALSE
#endif
#ifdef TTRUE
    #undef TTRUE
#endif

#ifndef NULL
    #define NULL 0
#endif

typedef enum
{
    TFALSE = 0,     //!< Logical false.
    TTRUE  = 1     //!< Logical true.
} TBOOL;


/* General return values */
typedef S16 TR_STATUS;

#define MC_OK                   0
#define MC_NOT_OK               1
#define MC_PARAMETER_ERROR      2
#define MC_DATA_ERROR           3
#define MC_MEMORY_RW_ERROR      4
#define MC_NOT_SUPPORTED        5
#define MC_STATE_ERROR          6
#define MC_SCSN_UNMATCHED       7
#define MC_UNKNOWN_ERROR        9


/*---------- The direction definition of the parameter in function call ---------------*/
#define		OUT		/*- The parameter will be given a initial data and returned data. -*/
#define		IN		/*- The parameter must be given a initial data before it is called. -*/						
#define		INOUT	/*- The parameter must be given a initial data before it is called
                        and return data during it is called. -*/


/*---------- The length definition of string buffer --------------------------*/
#define FP_SCNUM_MAX_LENGTH     22
#define FP_TEXT_MAX_LENGTH      158
#define MSG_TITLE_MAX_LENGTH    128
#define MSG_DATA_MAX_LENGTH     1024


/* DEMUX */
#define CAS_DEMUX_INVALID_CHANNEL_ID        ((U32)0xFFFFFFFF)
#define CAS_DEMUX_INVALID_FILTER_ID         ((U32)0xFFFFFFFF)
#define CAS_DEMUX_INVALID_DESCRAMBLER_ID    ((U32)0xFFFFFFFF)

typedef enum
{ 
	CAS_DEMUX_DISABLE_CHANNEL,      /*stop*/
	CAS_DEMUX_ENABLE_CHANNEL, 	    /*start*/
	CAS_DEMUX_RESET_CHANNEL         /*reset*/
} CAS_DEMUX_CTRL;


/* OS */
union CAS_OS_Msg_Content 
{
   U8    c[8];
   U16   s[4];
   U32   l[2];
   PVOID vfp[2];
};

typedef struct
{
	U32                      ulType;
	union CAS_OS_Msg_Content uInfo;
} CAS_OS_MESSAGE;


/* SC */
typedef enum   
{ 
	CAS_SCARD_INSERT,   /*in*/
	CAS_SCARD_REMOVE,   /*out*/
	CAS_SCARD_ERROR,    /*err*/
	CAS_SCARD_UNKNOWN   /*unknown card*/
} CAS_SCARD_STATUS; 


/* CA Manager */
typedef enum   
{ 
	CAS_CAT_UPDATE,
	CAS_PMT_UPDATE
} CAS_ACTION_EN; 


typedef enum
{
	CAS_MSG_MAIL,
	CAS_MSG_ANNOUNCE,
	CAS_MSG_NOTIFICATION
} CAS_MSG_TYPE;


typedef enum
{
	CAS_MSG_NORMAL,
	CAS_MSG_TIMED,      /* Automatic erase after wRemainTime seconds. */
	CAS_MSG_FORCED      /* Forced display message. */
} CAS_MSG_CLASS;


typedef enum
{
	CAS_MSG_PRIORITY_LOW,
	CAS_MSG_PRIORITY_MED,
	CAS_MSG_PRIORITY_HIGH,
	CAS_MSG_PRIORITY_URGENT
} CAS_MSG_PRIORITY;


typedef enum
{
	CAS_MC_DECODER_INFO,
	CAS_MC_SERVICE_INFO,
	CAS_MC_SC_ACCESS,
	CAS_MC_PIN_CODE_CHANGE,
	CAS_MC_PIN_CODE_CHECK,
	CAS_MC_MONITOR_ECM,
	CAS_MC_MONITOR_EMM,
	CAS_MC_IPP_NOTIFY,
	CAS_MC_IPP_INFO_UPDATE,
	CAS_MC_ENHANCED_SHORT_MESSAGE,
	CAS_MC_ENHANCED_FINGER_PRINT,
	CAS_MC_FORCE_CHANNEL,
	CAS_MC_FINGER_PRINT,
	CAS_MC_EMM_DOWNLOAD,
	CAS_MC_EMM_CHANGEPIN,
	CAS_MC_NOTIFY_EXPIRY_STATE,
	CAS_MC_NOTIFY_CURRENT_STATE,
	CAS_MC_NOTIFY_SHORT_MESSAGE,
	CAS_MC_MAX_MESSAGE
} CAS_MESSAGE_CONTROL;


typedef enum
{
	CAS_MC_QUERY_SUCCESS,
	CAS_MC_QUERY_FAIL,
	CAS_MC_QUERY_NOT_AVAILABLE
} CAS_QUERY_STATUS;

/* CA */
typedef enum
{
    CAS_STATE_E00,  // Service not scrambled
    CAS_STATE_E01,  // 
    CAS_STATE_E02,  // 
    CAS_STATE_E03,  // 
    CAS_STATE_E04,  // Please insert smart card
    CAS_STATE_E05,  // Unknown smart card
    CAS_STATE_E06,  // Smart card failure
    CAS_STATE_E07,  // Checking smart card
    CAS_STATE_E08,  // 
    CAS_STATE_E09,  // Smart card EEPROM failure
    CAS_STATE_E10,  // 
    CAS_STATE_E11,  // Card marriage unmatched
    CAS_STATE_E12,  // Please feed smart card
    CAS_STATE_E13,  // No service available
    CAS_STATE_E14,  // No authorization
    CAS_STATE_E15,  // Valid authorization available
    CAS_STATE_E16,  // Service is currently scrambled
    CAS_STATE_E17,  // Service is currently scrambled
    CAS_STATE_E18,  // 
    CAS_STATE_E19,  // 
    CAS_STATE_E20,  // Not allowed in this broadcaster
    CAS_STATE_E21,  // 
    CAS_STATE_E22,  // 
    CAS_STATE_E23,  // Service is currently descrambled
    CAS_STATE_E24,  // Not allowed in this region
    CAS_STATE_E25,  // Smart card not compatible(AS)
    CAS_STATE_E26,  // Unknown service(No TOPREAL CA)
    CAS_STATE_E27,  // Service is not currently running
    CAS_STATE_E28,  // Smart card is locked
    CAS_STATE_E29,  // 
    CAS_STATE_E30,  // 
    CAS_STATE_E31,  // Parental control locked
    CAS_STATE_E32,  // Not allowed in this country
    CAS_STATE_E33,  // No authorization data.
    CAS_STATE_E34,  // Illegal box
    CAS_STATE_E35,  // No Signal
    CAS_STATE_E36
} CAS_CUTTENT_STATE;


typedef struct
{
	U8 bYear[2];    /* for example 1998, bYear[0]=19, bYear[1]=98 */
	U8 bMonth;      /* 1 to 12 */
	U8 bDay;        /* 1 to 31 */
	U8 bHour;       /* 0 to 23 */
	U8 bMinute;     /* 0 to 59 */
	U8 bSecond;     /* 0 to 59 */
} CAS_TIMESTAMP;


typedef struct
{
    U16 wTitleLen;
    U8  bMsgTitle[80];
    U16 wDataLen;
    U8  bMsgData[880];
    U16 wIndex;
    U8  bType;
    U8  bClass;
    U8  bPriority;
    U16 wPeriod;
    CAS_TIMESTAMP sMsgTime;
    CAS_TIMESTAMP sCreateTime;
} CAS_MSG_STRUCT;


typedef struct
{
    CAS_TIMESTAMP sCreateTime;
    U16 wIndex;
    U8  bType;                      /* CAS_MSG_TYPE */
    U8  bClass;                     /* CAS_MSG_CLASS */
    U8  bPriority;                  /* CAS_MSG_PRIORITY */
    U8  bBlockFlag;                 /* Can be interrupted or not. 0: Unblock, 1: Blocking operation */
    U32 dwRemainTime;               /* Seconds */
    U32 dwPeriod;                   /* Seconds. Just for compatible with the notification of MSG1. */
    U8  bXPos;                      /* 0%--100%, (0, 0) is user-defined. */
    U8  bYPos;
    U8  bWidth;                     /* 0%--100%, (0, 0) is user-defined. (100, 100) is full screen. */
    U8  bHeight;
    U8  bTitleLen;
    U8  MsgTitle[MSG_TITLE_MAX_LENGTH];
    U16 wDataLen;
    U8  MsgData[MSG_DATA_MAX_LENGTH];
} CAS_ENHANCED_MSG_STRUCT;


typedef struct
{
	U8  bHashedNumLen;
	U8 *pbHashedNum;
	U8  bContentLen;
	U8 *pbContentData;
} CAS_FINGERPRINT_STRUCT;


typedef struct
{
    CAS_TIMESTAMP sActivateTime;
    U32 dwOnTime;                   /* Seconds */
    U32 dwOffTime;                  /* Seconds */
    U8  bRepeatNum;                 /* 0: Unique, 1---- */
    U8  bFontSize;
    U8  bXPos;                      /* 0%--100%, (0, 0) is random position. */
    U8  bYPos;
    U8  bWidth;                     /* 0%--100%, (0, 0) is user-defined. (100, 100) is full screen. */
    U8  bHeight;
    U8  bTextColorRed;
    U8  bTextColorGreen;
    U8  bTextColorBlue;
    U8  bTextOpacity;               /* 0%--100%, 0:transparent; 100:opaque */
    U8  bBackgColorRed;
    U8  bBackgColorGreen;
    U8  bBackgColorBlue;
    U8  bBackgOpacity;              /* 0%--100%, 0:transparent; 100:opaque */
    U8  bBlockFlag;                 /* Can be interrupted or not. 0: Unblock, 1: Blocking operation */
    U8  bDispType;                  /* 0: Overt; 1: Covert */
    U8  bDispScNum;                 /* If display sc number. */
    U8  bDispText;                  /* If display text message. */
    U8  bScNumLen;
	U8  ScNumString[FP_SCNUM_MAX_LENGTH];
	U8  bTextLen;
    U8  TextString[FP_TEXT_MAX_LENGTH];
} CAS_ENHANCED_FP_STRUCT;


typedef struct
{
    U8  bLockFlag;
	U16 wNetwrokId;
	U16 wTsId;
	U16 wServId;
	U16 wContentLen;
	U8 *pbContent;
} CAS_FORCECHANNEL_STRUCT;


typedef struct {
    U32 ulCashValue;
    U32 ulCreditValue;
    U16 wRecordIndex;
} CAS_EPURSEINFO_STRUCT;


typedef struct {
    U8  bProductType;   // 0:ippv; 1:ippt
    U32 ulRunningNum;
    CAS_TIMESTAMP ulStartTime;
    CAS_TIMESTAMP ulEndTime;
} CAS_IPPPRODUCT_STRUCT;


typedef struct {
    U8  bStateFlag;             /* Charging or consume flag, 0:consume; 1:charge. */
    CAS_TIMESTAMP ulExchTime;
    U32 ulExchRunningNum;
    U32 ulExchValue;
    U8  bContentLen;
    U8  pbContent[34];
} CAS_IPPRECORD_STRUCT;


typedef struct {
    U16 wChannelId;
    U8  bIppType;       /* 0:ippv; 1:ippt */
    U32 ulIppCharge;    /* charge value of one unit time */
    U32 ulIppUnitTime;
    U32 ulIppRunningNum;
    CAS_TIMESTAMP ulIppStart;
    CAS_TIMESTAMP ulIppEnd;
    U8  bContentLen;
    U8 *pbContent;
} CAS_IPPNOTIFY_STRUCT;


typedef struct {
    U16 wChannelId;
    U8  bIppType;       /* 0:ippv; 1:ippt */
    U16 ulPurchaseNum;
    U32 ulIppCharge;    /* charge value of one unit time */
    U32 ulIppUnitTime;
    U32 ulIppRunningNum;
} CAS_IPPPURCHASE_STRUCT;


typedef void (*CAS_NOTIFY)(CAS_MESSAGE_CONTROL eCaMsg, U16 wDemux, U32 ulParam);
/*-------------------------------------------------------------------------------------*/


/***************************************************************************************/
/*---- The below functions are provided by MCELL and called by user's application. ----*/
/***************************************************************************************/
/*Core*/
S16   MC_CoreInit(S16 iLevel);
U8   *MC_GetRevisionString(void);

S16   MC_GetProductType(OUT U8 *pbType);
S16   MC_GetSmartCardVersion(OUT char *string, U8 maxLen);

S16   MC_GetEPurseState(OUT CAS_EPURSEINFO_STRUCT *psEPurseInfo, U8 bIndex);
S16   MC_GetIppProduct(OUT CAS_IPPPRODUCT_STRUCT *psProduct, U16 wIndex);
S16   MC_GetIppRecord(OUT CAS_IPPRECORD_STRUCT *psRecordData, U16 wIndex);
S16   MC_IppPurchase(IN U8 *pbPin, U8 bPinLen, CAS_IPPPURCHASE_STRUCT sProduct);

void  MC_MNGR_PostChanChangeState(U16 wChannelId, U8 bState);
S16   MC_MNGR_PostPsiTable(CAS_ACTION_EN eAction, IN PVOID pvTableData);

S16   MC_AbGetState(char *string, U8 maxLen);
      /* Return value, 0: OK; 1: Not OK; 2: Bad parameter; 4: Memory error;
                       6: Wrong Sc state; 7: Unmatched, Display sn; */
S16   MC_GetScSerialNumber(OUT char *pcString, U8 bMaxLen);
S16   MC_GetScStatus(OUT CAS_SCARD_STATUS *state);
S16   MC_SCARD_ChangePin(IN U8 *pbOldPin, IN U8 *pbNewPin, U8 bPinLen);
S16   MC_SCARD_GetRating(OUT U8 *pbRating);
S16   MC_SCARD_SetRating(IN U8 *pbPin, U8 bPinLen, U8 bRating);
S16   MC_SCARD_ParentalCtrlUnlock(IN U8 *pbPin, U8 bPinLen);

S16   MC_PostRegionCode(U16 wCode);

S16   MC_GetScAttribute(OUT U8 *pbType);   /* 0: mother card; 1: son card */
S16   MC_ReadFeedDataFromMaster(OUT U8 *pbFeedData, OUT U8 *pbLen);
      /* Return value, 5: MC_NOT_SUPPORTED. Attribute error, it is not son card. */
S16   MC_WriteFeedDataToSlaver(IN U8 *pbFeedData, U8 bLen);
      /* Return value, 5: MC_NOT_SUPPORTED. Attribute error, it is not mother card. */

CAS_QUERY_STATUS MC_STATE_QueryControl(CAS_MESSAGE_CONTROL eQuery, U16 wDemux, OUT PVOID pvParams);
S16   MC_STATE_RegisterCaNotify(IN CAS_NOTIFY funcCallback);

S16   MC_TIME_GetEntitleInfo(OUT U8 *pbStart, OUT U8 *pbEnd, OUT U32 *pulRemain, U16 wProduct);
      /* Return value, 0: Valid entitle; 1: Input parameters error; 2: No entitle info;
                       3: Valid entitle, but limited; 4: Entitle closed; 5: Entitle paused;  */

U32   MC_SECENG_Close(U32 *handleP);                        /* for advanced security chip. */
U32   MC_SECENG_Open(U8 tsdInput, U16 pid, U32 *handleP);   /* for advanced security chip. */


/***************************************************************************************/
/*--------- The blow functions are accomplished by user, and called by MCELL ----------*/
/***************************************************************************************/
/*API*/
/*-----------------OS--------------------------------------------------------*/
PVOID TRDRV_OS_AllocateMemory(U32 ulSize);
void  TRDRV_OS_FreeMemory(IN PVOID pvMemory);

U32   TRDRV_OS_CreateTask(IN void(*task)(void *arg), S16 iPriority, U32 ulStackSize);
void  TRDRV_OS_DelayTask(U32 ulDelayTime);
//U32   TRDRV_OS_GetSysMsTick(void);

S16   TRDRV_OS_SendMessage(U32 tTaskId, IN CAS_OS_MESSAGE *psMsg);
CAS_OS_MESSAGE *TRDRV_OS_ReceiveMessage(U32 tTaskId);

U32   TRDRV_OS_CreateSemaphore(U32 ulInitialCount);
void  TRDRV_OS_SignalSemaphore(U32 ulSemaphore);
void  TRDRV_OS_WaitSemaphore(U32 ulSemaphore);

/*-----------------SC--------------------------------------------------------*/
S16   TRDRV_SCARD_Initialise(IN S16 (*SC_ATR_Notify)(U8 bCardNumber, U8 bStatus, U8 *pbATR, U8 bProtocol));
void  TRDRV_SCARD_ResetCard(U8 bCardNumber);
S16   TRDRV_SCARD_AdpuFunction(U8 bCardNumber, IN U8 *pbTxData, U32 ulTxLength, OUT U8 *pbRxData, OUT U32 *pulRxLength);
S16   TRDRV_SCARD_GetSlotState(U8 bCardNumber, OUT U8 *pbSlotState);

/*----------------DEMUX------------------------------------------------------*/
S16   TRDRV_DEMUX_Initialise(void);
U32   TRDRV_DEMUX_AllocateSectionChannel(U16 wMaxFilterNumber, U16 wMaxFilterSize, U32 ulBufferSize);
void  TRDRV_DEMUX_SetChannelPid(U32 ulChannelId, U16 wChannelPid);
void  TRDRV_DEMUX_ControlChannel(U32 ulChannelId, CAS_DEMUX_CTRL eAction);
void  TRDRV_DEMUX_RegisterChannelUpcallFct(U32 ulChannelId, IN void (*chUpcallFct)(U32 ulChannelId));
void  TRDRV_DEMUX_FreeSectionChannel(U32 ulChannelId);
U32   TRDRV_DEMUX_AllocateFilter(U32 ulChannelId);
S16   TRDRV_DEMUX_SetFilter(U32 ulChannelId, U32 ulFilterId, IN U8 *pbMask, IN U8 *pbData);
S16   TRDRV_DEMUX_FreeFilter(U32 ulChannelId, U32 ulFilterId);
U8   *TRDRV_DEMUX_GetSectionData(U32 ulChannelId, OUT U32 *pulSectionSize);
void  TRDRV_DEMUX_FreeSectionData(U32 ulChannelId, U32 ulSectionSize);

/*---------------DESC--------------------------------------------------------*/
U32   TRDRV_DESC_OpenDescrambler(void);
void  TRDRV_DESC_CloseDescrambler(U32 ulDescId);
void  TRDRV_DESC_SetDescramblerPid(U32 ulDescId, U16 wPid);
void  TRDRV_DESC_SetDescramblerEvenKey(U32 ulDescId, IN U8 *pbEvenKey, U8 bEvenLen);
void  TRDRV_DESC_SetDescramblerOddKey(U32 ulDescId, IN U8 *pbOddKey, U8 bOddLen);

/*---------------NVRAM-------------------------------------------------------*/
S16   TRDRV_NVRAM_Initialise(void);
S16   TRDRV_NVRAM_Read(U32 ulOffset, OUT U8 *pbData, U16 wLength);
S16   TRDRV_NVRAM_Write(U32 ulOffset, IN U8 *pbData,  U16 wLength);

/*---------------PRINT-------------------------------------------------------*/
void  MC_Printf(char *format, ...);

#ifdef __cplusplus
}
#endif
#endif
