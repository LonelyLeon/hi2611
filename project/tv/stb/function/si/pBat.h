 /**@file pbat.h
*@brief BAT ���õ��Ľṹ�궨���
*��ϸ����
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

 /** @brief  BAT ��ʼ������ں���
* @param[in] void   ע��
* @retval ��
*/ 
void p_bat_start(void)D_FUNCPOSTFIT;


 /** @brief  BAT ע�����պ���
* @param[in] void   ע��
* @retval ��
*/ 
void p_bat_stop(void)D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif







