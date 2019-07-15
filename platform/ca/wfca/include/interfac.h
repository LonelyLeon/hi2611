#ifndef	__interfac_h
#define __interfac_h
/*
**=============================================================================
* Copyright (C) 2003,ChengDu Wanfa Catv & Communication equipment co.,ltd
* All rights reserved.
* File name           : interfac.h
* Abstract            : define interface with other platform for wanfaca system
* Current version     : V1.0
* Init version        : V1.0
* Author              : ZhouYong
* Date created        : 2003-04-20
* Date finished       : 2003-04-20
* Modification history: Mender     Date        Description
*                       ZhouYong   2008-10-07  WFSTB_PPTNotify is modified
*                       ZhouYong   2008-10-07  WFSTB_GetPPTOkFlag is deleted
*                       ZhouYong   2004-10-26  WFSTB_Interpreter is deleted
*                       ZhouYong   2004-10-26  A few interface function is added
*                       ZhouYong   2006-05-15  The function WFSTB_EmailNotify is modified
* 
**=============================================================================
*/

#include "wanfacas.h"

typedef struct
{
	U08		Cw[8];
	BOOL	Parity;/* TRUE＝odd，FALSE＝even */
}WFSTB_DesCw_t;

typedef struct
{
	BOOL	Type;/* TRUE=email,FALSE=OSD msg */
	U32		Identfier;/* Info identfier */
	CHAR	*Text;/* content of Info,最长1123个字符 */
	union
	{
		struct
		{
			U16	Year;
			U08	Month;
			U08	Day;
			U08	Hour;
			U08	Minute;
			U08	Second;
		}DateTime;/* 对于邮件使用该域,发送时间 */
		struct
		{
			U08	Position;/* 0在底部，1在顶部，2在左边，3在右边 */
			U08	Direction;/* 0自右向左，1自左向右，2自上而下，3自下而上 */
			U32	BkColor;/* 背景颜色 */
			U32	FtColor;/* 前景颜色 */
		}DisplayCtrl;/* 对于屏显使用该域,显示控制 */
	}Property;
}WFSTB_Email_t;

typedef struct
{
	U08	TableId;
	U16	Bytes;/* 段长字段之后开始过滤的字节数 */
	U08	Data[9];
	U08	Mask[9];
}WFSTB_FilterData_t;

typedef VOID (*WFOS_Task_t)(VOID *Parameter)PARAM_PAST_IN_STACK;

/* for smart card */
U32		WFSMART_OpenCard(U08 *History,U08 *HistoryLen)PARAM_PAST_IN_STACK;
U32		WFSMART_Transfer(U08 CmdL,U08 *Cmd,U08 RespL,U08 *Resp)PARAM_PAST_IN_STACK;
U32		WFSMART_CloseCard(VOID)PARAM_PAST_IN_STACK;

/* for stb */
VOID	WFSTB_Power(BOOL On)PARAM_PAST_IN_STACK;
VOID	WFSTB_Panel(BOOL Lock)PARAM_PAST_IN_STACK;
VOID	WFSTB_ParentalRatingNotify(U08 Rating)PARAM_PAST_IN_STACK;
VOID	WFSTB_PPTNotify(BOOL IsPPV,U16 Interval,U16 UnitPrice)PARAM_PAST_IN_STACK;
VOID	WFSTB_EmailNotify(WFSTB_Email_t *Email)PARAM_PAST_IN_STACK;
VOID	WFSTB_EntitlementNotify(U16 Remains)PARAM_PAST_IN_STACK;
VOID	WFSTB_DownLoadNotify(U08 Type,U08 Version,U16 CurrentPiece,U16 LastPiece,U08 Bytes,U08 *Data)PARAM_PAST_IN_STACK;
VOID	WFSTB_SetDesDck(U08 *Dck/* 16字节 */)PARAM_PAST_IN_STACK;
VOID	WFSTB_SetDesCw(BOOL IsCipherCw/* TRUE=CW加密，否则CW是明文 */,WFSTB_DesCw_t *DesCw)PARAM_PAST_IN_STACK;
VOID	WFSTB_SwitchProgram(WFCAS_Program_t *Program)PARAM_PAST_IN_STACK;
VOID	WFSTB_OpReport(U08 OperateCode,U32 ErrorCode)PARAM_PAST_IN_STACK;
VOID	WFSTB_SendStringToCom(CHAR *String)PARAM_PAST_IN_STACK;
VOID	WFSTB_EmmFilterNotify(UINT Count,WFSTB_FilterData_t *FilterData)PARAM_PAST_IN_STACK;

/* for C runtime lib or os */
VOID	*WFMEM_Malloc(UINT Size)PARAM_PAST_IN_STACK;
VOID	WFMEM_Free(VOID *Ptr)PARAM_PAST_IN_STACK;

/* for os */
VOID	WFOS_SemWait(VOID *Semaphore)PARAM_PAST_IN_STACK;
VOID	WFOS_SemSignal(VOID *Semaphore)PARAM_PAST_IN_STACK;
VOID	WFOS_SemDestroy(VOID *Semaphore)PARAM_PAST_IN_STACK;
VOID	*WFOS_SemCreate(S32 InitCount)PARAM_PAST_IN_STACK;
VOID	*WFOS_TaskCreate(WFOS_Task_t Task,VOID *Parameter,UINT StackSize)PARAM_PAST_IN_STACK;
#endif
