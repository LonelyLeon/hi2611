 /**@file pUmt.h
*@brief umt 所用到的结构宏定义等
*详细描述
*@author dingl
*@copyright Haier-IC
*@date 2013-09-10  dingl 操作说明
*@note 注解
*/
#ifndef _D_UMT_H_
#define _D_UMT_H_
#ifdef  __cplusplus

extern "C"
{
#endif

#include "dTypes.h"


#define UMT 0xffff
#define _M_FLASH_BBCB_ADDR			0x3FFEC

#define	UPDATE_INFO_PID			0x1a0b
#define	UPDATE_INFO_TABLEID		0xca
//#define 	MANUAL_UMT_SW_UPDATE  	1
//#define 	FORCE_UMT_SW_UPDATE  	2
//#define POW_ON_SW_UPDATE  		3
//#define 	NONE_LOADER_UI		4

#define 	UMT_DESCR_LOADER_TAG	0x85    /*Haier ic 升级描述符*/

typedef struct
{
	D_U8		EnableOtaDL;/*1:need  download，0:no download need */
	D_U8		FlashCorrupted;/*1: some of data in flash has been modified during dl. */
	/*---------------------------tranponder parameter ----------------------------*/
	D_U16		service_id;  	
	D_U32		TransponderFreq;		/* KHz */
	D_U32		SymbolRate;	
	D_U8		Modulation;
	D_U16		DataPID;
	D_U16		TableID;
	D_U32		new_software_version;	
	D_U32		current_software_version;	
	D_U32		new_logo_version;
	D_U32		current_logo_version;
	D_U8		download_type;
	D_U16		Start_Freq;
	D_U16		Start_SymbolRate;
	D_U8		Start_SourceLnb;
	D_U16		HighBand;
	D_U16		LowBand;
	D_U32		crc_32;
}SdataDpcb_T,DPCB_STRUCT;


 /** @brief  umt 开始接收入口函数
* @param[in] void   注释
* @retval 无
*/ 
void p_umt_start( D_U8 poweron)D_FUNCPOSTFIT;

 
 /** @brief  umt 注销接收函数
* @param[in] void   注释
* @retval 无
*/ 
void p_umt_stop(void)D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif
