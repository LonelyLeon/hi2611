/** @file
* @brief  ʱ�����
* @author ����
* @date 2005-10-26 ����: �����ļ�
* @date 2013-03-19 lc: ͳһƽ̨, ��������
*/

#ifndef _D_TIME_H_
#define _D_TIME_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief ʱ��ƫ��(����Ϊ��λ)*/
extern D_S16 const g_local_time_offset[];

/** @brief �������α�׼ʱ��*/
extern D_U8	const g_gmt_zone_id;

/** @brief �������ڶ�����*/
extern D_U8	const g_bj_zone_id;

/** @brief ʱ�������־��Ŀ*/
extern D_U8	g_local_time_offset_cnt;

/** @brief ȡ����ʱ��
* @param[in] t	��������ʱ��
* @param[in] off ʱ��ƫ��
* @reutrn ���ر���ʱ��
*/
D_Time	d_time_local (D_Time t, D_S32 offset) D_FUNCPOSTFIT;

/** @brief ȡ��������ʱ��
@param [in] t ��ǰʱ��
@param [in] off ʱ��ƫ��
@return utc ��������ʱ��
*/
D_Time	d_time_utc (D_Time t, D_S32 offset) D_FUNCPOSTFIT;

/** @brief ȡ�õ�ǰʱ��
@return curr ��ǰʱ��
*/
D_Time d_time_get_time (void) D_FUNCPOSTFIT;

/** @brief ȡ�õ�ǰ����ʱ��
@return time ����ʱ��
*/
D_Time d_time_get_local_time (void) D_FUNCPOSTFIT;

/** @brief ���õ�ǰʱ��
@param[in] t ����ʱ��
@return D_OK ���óɹ�
*/
D_Result d_time_set_time (D_Time t) D_FUNCPOSTFIT;

/** @brief ���õ�ǰ(utc)ʱ��, ��ʹ��ʱ��оƬ��ʱ��ʹ������ӿڣ�
���ú�d_time_set_time�ӿھ���Ч�ˡ�
@param[in] t ����ʱ��
@return D_OK ���óɹ�
*/
D_Result
d_time_set_time_by_timechip (D_Time t) D_FUNCPOSTFIT;

/** @brief �ж��Ƿ��Ѿ����õ�ǰʱ��
@return D_TRUE �Ѿ����ù�
*/
D_Bool
d_time_had_set_time (void) D_FUNCPOSTFIT;

/** @brief ȡ����ʱ��
@param [in] ��������ʱ��
@return lt  ����ʱ��
*/
D_Time d_time_local_time (D_Time t) D_FUNCPOSTFIT;


/** @brief ȡ��������ʱ��
@param[in] t ��ǰʱ��
@return utc ��������ʱ��
*/
D_Time d_time_utc_time (D_Time t) D_FUNCPOSTFIT;


/** @brief ȡ��ǰʱ��
@return time_offset ʱ��ƫ��
*/
D_S32 d_time_get_time_offset (void) D_FUNCPOSTFIT;

/** @brief ���õ�ǰʱ��
@param[in] off ʱ��ƫ��
*/
void d_time_set_time_offset (D_S32 off) D_FUNCPOSTFIT;

/** @brief 24Сʱ��תΪ12Сʱ��
* @param[in] hour24	24Сʱʱ��
* @param[out] hour12	���12Сʱʱ��Ļ�����
* @param[out] pm_am	���������
* @return D_OK ��ȷ��D_ERR����
*/
D_Result d_hour24_to_hour12( D_U8 hour24,D_U8* pm_am, D_U8* hour12 )D_FUNCPOSTFIT;

/** @brief 12Сʱ��תΪ24Сʱ��
* @param[in] hour12	12Сʱʱ��
* @param[in] pm_am	0:���磬1:���硣
* @param[out] hour24	���24Сʱʱ��Ļ�����
* @return ����D_OK
*/
D_Result d_hour12_to_hour24( D_U8 hour12,D_U8 pm_am,D_U8* hour24 )D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
