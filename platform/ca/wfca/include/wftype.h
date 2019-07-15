#ifndef	__wftype_h
#define __wftype_h
/*
**=============================================================================
* Copyright (C) 2003,ChengDu Wanfa Catv & Communication equipment co.,ltd
* All rights reserved.
* File name           : wftype.h
* Abstract            : Basic type & constant define
* Current version     : V1.0
* Init version        : V1.0
* Author              : ZhouYong
* Date created        : 2003-04-20
* Date finished       : 2003-04-20
* Modification history: Mender     Date        Description
*                       ZhouYong   2013-04-10  Adapt to the dcas
*                       ZhouYong   2004-10-27  Command code is deleted for STB
*                       ZhouYong   2004-10-27  Operate code is added for CAS
* 
**=============================================================================
*/

/* Constant for Type */
#ifndef	CONST
#define CONST const
#endif

#ifndef	TRUE
#define TRUE 1
#endif

#ifndef	FALSE
#define FALSE 0
#endif

#ifndef	VOID
#define VOID void
#endif

#ifndef	CHAR
#define CHAR char
#endif

#ifndef	BOOL
#define BOOL unsigned char
#endif

#ifndef	UINT
#define UINT unsigned int
#endif

#ifndef	S08
#define S08 signed char
#endif

#ifndef	S16
#define S16 signed short
#endif

#ifndef	S32
#define S32 signed long
#endif

#ifndef	U08
#define U08 unsigned char
#endif

#ifndef	U16
#define U16 unsigned short
#endif

#ifndef	U32
#define U32 unsigned long
#endif

#if defined(__C51__) || defined(__CX51__)
#undef CONST
#define CONST	const far
#define PARAM_PAST_IN_STACK	large reentrant
#else
#define PARAM_PAST_IN_STACK
#endif

/* Ca table id,����CMTʱʹ�� */
#define WFCAS_EMMTABLE_ID	0x8f
#define WFCAS_ECMTABLE_ID1	0x80
#define WFCAS_ECMTABLE_ID2	0x81

/* Operate code for CAS */
#define WFCAS_OP_OPEN_BASE			0x00/* �������ܿ��е��ļ� */
#define WFCAS_OP_CLOSE_BASE			0x01/* �ر����ܿ��е��ļ� */
#define WFCAS_OP_SAVE_FILE			0x02/* �����ļ� */
#define WFCAS_OP_UPDATE_KEY			0x03/* �����ļ���Կ */
#define WFCAS_OP_PARTNERSHIP		0x04/* ������� */
#define WFCAS_OP_PROG_ENTITLE		0x05/* ��Ŀ��Ȩ */
#define WFCAS_OP_UPTATE_TIME		0x06/* ����ʱ�� */
#define WFCAS_OP_DESCRAMBLE			0x07/* ���� */
#define WFCAS_OP_PARSE_CADATA		0x08/* ����CA��ر��-CAT,PMT,CMT */
#define WFCAS_OP_CHILD_ENTITLE		0x09/* ĸ�����ӻ���Ȩ */
#define WFCAS_OP_ZONE_SET			0x0A/* ���������� */
#define WFCAS_OP_MODIFY_USERPROP	0x0B/* �޸����ܿ��û����� */
#define WFCAS_OP_CARD_INIT			0x0C/* ��ʼ��DCAS */

/* Constant for Error code */
#define	WFERR_COMMON_NO			0x00000000L/* û�д��� */
#define	WFERR_COMMON_PARAMETER	0x00000001L/* �����Ĳ����Ƿ� */
#define	WFERR_COMMON_MEMALLOC	0x00000002L/* ����洢��ʧ�� */
#define	WFERR_COMMON_MEMFREE	0x00000003L/* �ͷŴ洢��ʧ�� */
#define	WFERR_COMMON_ILLEAGAL	0x00000004L/* �Ƿ��Ĳ��� */
#define	WFERR_COMMON_VERIFY		0x00000005L/* У��ʧ�� */
#define	WFERR_COMMON_MEMEXEC	0x00000006L/* �ڴ��쳣 */

#define	WFERR_SMART_SW1SW2		0x00010000L/* ִ������ʱ״̬�ֲ�����0x9000,��16λΪ״̬��SW1SW2 */
#define	WFERR_SMART_RWSIZE		0x00020000L/* ʵ����Ӧ�ֽ�����Ҫ����� */
#define	WFERR_SMART_ABSENT		0x00020001L/* û�в������ܿ� */
#define	WFERR_SMART_INVALID		0x00020002L/* �Ƿ������ܿ� */
#define	WFERR_SMART_DRIVER		0x00021000L/* ���ܿ����������������￪ʼ��ţ���С��WFERR_FILE_FORMAT */

#define	WFERR_FILE_FORMAT		0x00030000L/* �ļ���ʽ���� */
#define	WFERR_FILE_CONFLICT		0x00030001L/* �����ͻ */
#define	WFERR_FILE_FULL			0x00030002L/* �ļ����� */
#define	WFERR_FILE_EMPTY		0x00030003L/* �ļ��ѿ� */
#define	WFERR_FILE_QUERY		0x00030004L/* δ�ܲ�ѯ����¼ */
#define	WFERR_FILE_ABNORMAL		0x00030005L/* �ļ������쳣 */

#define	WFERR_CAS_ABSENT		0x00040000L/* CAS��δ��ʼ�� */
#define	WFERR_CAS_PRESENT		0x00040001L/* CAS�Ѿ���ʼ�� */
#define	WFERR_CAS_INVALIDSTB	0x00040002L/* �Ƿ��Ļ�����,���߻�����ƥ�� */
#define	WFERR_CAS_UNLICENSED	0x00040003L/* ��Ŀδ����Ȩ */
#define	WFERR_CAS_OUTOFPERIOD	0x00040004L/* ��Ŀ������Ȩ���ڼ��� */
#define	WFERR_CAS_FORBIDDEN		0x00040005L/* ��ֹ���� */
#define	WFERR_CAS_COMMAND		0x00040006L/* �Ƿ���ǰ������ */
#define	WFERR_CAS_LENGTH		0x00040007L/* ����Ĳ������Ȳ���ȷ */
#define	WFERR_CAS_ADDRESS		0x00040008L/* ǰ��Ѱַû��Ѱ������ */
#define	WFERR_CAS_BALANCE		0x00040009L/* ���� */
#define	WFERR_CAS_UNMATCHED		0x0004000AL/* �ӻ���ĸ����ƥ�� */
#define	WFERR_CAS_EXPIRATION	0x0004000BL/* ���ڵ��ӻ���Ȩ */
#define	WFERR_CAS_ZONE			0x0004000CL/* ��������� */
#define	WFERR_CAS_PROTOCOL		0x0004000DL/* CMTЭ�鲻��ȷ */
#endif
