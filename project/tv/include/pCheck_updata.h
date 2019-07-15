/**@file pCheck_updata.h
*@brief ¼ì²éÉý¼¶Ìõ¼þÅÐ¶Ï
*ÏêÏ¸ÃèÊö
*@author dingl
*@copyright Haier-IC
*@date 2014-06-26
*/
#ifndef _P_CHECK_UPDATA_H_
#define _P_CHECK_UPDATA_H_
#ifdef  __cplusplus

extern "C"
{
#endif

#include "dTypes.h"
#include "pSIParse.h"

#define   MANUAL_SW_UPDATE  0x1
#define   FORCE_SW_UPDATE  0x2
#define   POW_ON_SW_UPDATE  		3
#define 	NONE_LOADER_UI			4

D_Result p_dvbs_set_tp_info(D_Loader_Descr *descr_info)D_FUNCPOSTFIT;
D_Result p_set_tp_info(D_Loader_Descr *descr_info)D_FUNCPOSTFIT;
D_Result p_check_download_condition(D_Loader *loader_list, D_U8 tag)D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif
































