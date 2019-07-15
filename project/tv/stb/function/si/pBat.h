 /**@file pbat.h
*@brief BAT 所用到的结构宏定义等
*详细描述
*@author wansb
*@copyright Haier-IC
*@date 2014-04-01  
*/
#ifndef _P_BAT_H_
#define _P_BAT_H_
#ifdef  __cplusplus

extern "C"
{
#endif

#include "dTypes.h"
#include "dDBase.h"




typedef struct {
	D_U8			*buf;
	D_HMMan		     hmm;
	D_TabMask		*bat_mask;
	D_Bat			 *Bat;
	D_U8			version;
} D_BatScan;

 /** @brief  BAT 开始接收入口函数
* @param[in] void   注释
* @retval 无
*/ 
void p_bat_start(void)D_FUNCPOSTFIT;


 /** @brief  BAT 注销接收函数
* @param[in] void   注释
* @retval 无
*/ 
void p_bat_stop(void)D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif







