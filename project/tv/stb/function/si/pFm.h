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




/** @brief BAT��*/
typedef struct {
	D_List	 list;
	D_List	*tses;
	D_List	*descrs;
} D_Fm;

typedef struct {
	D_U8			*buf;
	D_HMMan		 hmm;
	D_TabMask		*fm_mask;
} D_fmScan;

 /** @brief  BAT ��ʼ������ں���
* @param[in] void   ע��
* @retval ��
*/ 
void p_fm_start(void)D_FUNCPOSTFIT;


 /** @brief  BAT ע�����պ���
* @param[in] void   ע��
* @retval ��
*/ 
void p_fm_stop(void)D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif







