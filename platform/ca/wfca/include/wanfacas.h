#ifndef	__wanfacas_h
#define __wanfacas_h
/*
**=============================================================================
* Copyright (C) 2003,ChengDu Wanfa Catv & Communication equipment co.,ltd
* All rights reserved.
* File name           : wanfacas.h
* Abstract            : prototype define for wanfaca system
* Current version     : V1.0
* Init version        : V1.0
* Author              : ZhouYong
* Date created        : 2003-07-02
* Date finished       : 2003-07-22
* Modification history: Mender     Date        Description
*                       ZhouYong   2008-10-07  WFCAS_SendPPTOkFlag is added
*                       ZhouYong   2004-10-27  The interface function is modified
*                       ZhouYong   2004-12-22  WFCAS_GetStbNo is added
*                       ZhouYong   2005-12-13  Adapt to huaxu smt card
*                       ZhouYong   2006-05-16  The function WFCAS_GetEntitlement is added
* 
**=============================================================================
*/

#include "wftype.h"

typedef struct
{
	U16	Mjd;/* MJD */
	U32	Utc;/* ����ֽ�Ϊ0�������ֽ�ΪUTC */
}WFCAS_DateTime_t;

typedef struct
{
	BOOL	ChildCard;/* �Ƿ����ӿ�,TRUE�����ӿ�, FALSE����ĸ�� */
	U08		Card_No[8];/* Compact BCD */
	U16		Issuance_Date;/* ��MJD��ʾ */
	U16		Expire_Date;/* ��MJD��ʾ */
	U08		Provider[32];/* String,���ķ����� */
	U32		PairingStbNo;/* ��ÿ���Ե�StbNo */
/* ���µ���ֻ���ӿ�����Ч */
	U08		MotherCardNo[8];/* ĸ���Ŀ���*/
	WFCAS_DateTime_t	UpdateOrigination;/* ĸ�����ӿ���Ȩʱ��ʱ����� */
	WFCAS_DateTime_t	UpdateExpiration; /* ĸ�����ӿ���Ȩʱ��ʱ���յ� */
}WFCAS_User_t;

typedef struct
{
	U16	Cas_Id;
	U16	Sub_Id;
	U08	Version;
	U08	Description[32];/* String,CAS��˵�� */
}WFCAS_Version_t;

typedef struct
{
	U08	Mode;/* �����λ��ʾ���Ƶķ�ʽ���߼����ķ�ʽ,���λB7��ʾLOADERƵ��,B6��ʾNITƵ��,B5��ʾ���ݹ㲥Ƶ�� */
	U32	Frequency;/* ��KHzΪ��λ */
	U32	SymbolRate;/* ��KS/SecΪ��λ */
}WFCAS_Delivery_t;

typedef struct
{
	U32	Product_Id;/* Product identifier */
	U16	Ori_Date;/* original date,MJD */
	U32	Ori_Time;/* original time,UTC */
	U16	Exp_Date;/* expire date,MJD */
	U32	Exp_Time;/* expire time,UTC */
}WFCAS_Entitlement_t;

typedef enum
{
	FIRST,/* ��һ�� */
	PREV,/* ǰһ�� */
	NEXT,/* ��һ�� */
	LAST/* ���һ�� */
}WFCAS_Direction_t;

typedef struct
{
	U16	Network_Id;
	U16	Stream_Id;
	U16	Program_No;
}WFCAS_Program_t;

typedef struct
{
	U08	TableId;/* Table id:CAT,PMT,CMT */
	U16	Bytes;/* Number of data in byte,Must be <= 256 */
	U08	*Array;/* Body of data */
}WFCAS_CaTable_t;

typedef struct
{
	BOOL	Delivery;/* TRUE�����ߴ���,FALSE�����Ǵ��� */
	U08		Identity[8];
}WFSTB_Identity_t;

typedef struct
{
	U32	Money;/* �û���ǰ�ܽ�����С���ҵ�λΪ��λ*/
	U32	Balance;/*�û��������ܶ�: ����С���ҵ�λΪ��λ*/
}WFCAS_Purse_t;

U32 WFCAS_GetStbNo(U32 *StbNo)PARAM_PAST_IN_STACK;
U32 WFCAS_GetPurseInfo(WFCAS_Purse_t *Purse)PARAM_PAST_IN_STACK;
U32 WFCAS_GetUserInfo(WFCAS_User_t *UserInfo)PARAM_PAST_IN_STACK;
U32 WFCAS_GetVerInfo(WFCAS_Version_t *VerInfo)PARAM_PAST_IN_STACK;
U32 WFCAS_GetDateTime(WFCAS_DateTime_t *DateTime)PARAM_PAST_IN_STACK;
U32 WFCAS_GetDelivery(WFCAS_Delivery_t *Delivery,WFCAS_Direction_t Direction)PARAM_PAST_IN_STACK;
U32 WFCAS_GetEntitlement(WFCAS_Entitlement_t *Entitlement,WFCAS_Direction_t Direction)PARAM_PAST_IN_STACK;
U32 WFCAS_CardEventNotify(BOOL Inserted)PARAM_PAST_IN_STACK;
U32 WFCAS_SendPPTOkFlag(BOOL IsPPV)PARAM_PAST_IN_STACK;
VOID WFCAS_ReceiveIsrForCom(CHAR Ch)PARAM_PAST_IN_STACK;
U32 WFCAS_SubmitPduFromCom(U32 *BytesReceived)PARAM_PAST_IN_STACK;
U32 WFCAS_LicensedToSubStb(VOID)PARAM_PAST_IN_STACK;
U32 WFCAS_ProgramSwitch(U32 StbTicks/* 1��/tick */,U32 ProgramId/* 0����ʹ�� */)PARAM_PAST_IN_STACK;
U32 WFCAS_ParseCaTable(U32 ProgramId/* 0����ʹ�� */,WFCAS_CaTable_t *CaTable)PARAM_PAST_IN_STACK;
U32 WFCAS_SetZone(U08 *Zone/* 8���ֽ� */)PARAM_PAST_IN_STACK;
U32 WFCAS_ParentalRatingOk(U32 StbTicks/* 1��/tick */)PARAM_PAST_IN_STACK;
U32 WFCAS_SetParentalRating(U08 Rating,U16 TimeOutInterval/* ����Ϊ��λ */)PARAM_PAST_IN_STACK;
U32 WFCAS_Initialize(WFSTB_Identity_t *Identity)PARAM_PAST_IN_STACK;
void WFCAS_MakeStbId(U08 *StbId/* 8�ֽ� */,U32 StbNo)PARAM_PAST_IN_STACK;//haier ��ӣ�ca����ԭ��
#endif

