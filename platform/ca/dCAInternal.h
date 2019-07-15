/** @file
* @brief CAģ���ڲ��ӿ�
* @author ����
* @date 2005-9-8 ����: �����ļ�
*/

#ifndef _D_CA_INTERNAL_H_
#define _D_CA_INTERNAL_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dCA.h"
#include "dSCI.h"
#include "dDemux.h"
#include "dTimer.h"

/** @brief CA�����ܿ����*/
extern D_HSCI	ca_hsci;

/** @brief CAģ���ʼ��*/
D_Result	ca_init (void) D_FUNCPOSTFIT;

/** @brief CAģ�鷴��ʼ��*/
D_Result	ca_deinit (void) D_FUNCPOSTFIT;

/** @brief ֪ͨCAģ�����ܿ�����*/
D_Result	ca_card_in (void) D_FUNCPOSTFIT;

/** @brief ֪ͨCAģ�����ܿ��γ�*/
D_Result	ca_card_out (void) D_FUNCPOSTFIT;

/** @brief ֪ͨCAϵͳ��ʼ����һ��TS���е��û���Ȩ����*/
D_Result	ca_start_ts (D_CATSParam *param) D_FUNCPOSTFIT;

/** @brief ֪ͨCAϵͳֹͣ����һ��TS���е��û���Ȩ����*/
D_Result	ca_stop_ts (D_DBTSID db_ts_id) D_FUNCPOSTFIT;

/** @brief ֪ͨCAϵͳ��ʼ����һ��������û���������*/
D_Result	ca_start_srv (D_CASrvParam *param) D_FUNCPOSTFIT;

/** @brief ֪ͨCAϵͳֹͣ����һ��������û���������*/
D_Result	ca_stop_srv (D_DBSrvID db_srv_id) D_FUNCPOSTFIT;

/** @brief ��GUI�и����¼�������ʾ*/
//D_Result	ca_gui_solve_evt (D_CAEventType type, D_Ptr param) D_FUNCPOSTFIT;

/** @brief �յ�Demux����*/
D_Result	ca_demux_data (D_HDemux hdemux, D_U8 *buf, D_Size size) D_FUNCPOSTFIT;

/** @brief ��ʱ������*/
D_Result	ca_on_timer (D_HTimer htimer) D_FUNCPOSTFIT;

/** @brief ����CA�¼���֪ͨ�û��ص�*/
D_Result	ca_event (D_CAEventType type, D_Ptr param) D_FUNCPOSTFIT;

/** @brief ��ȡ��ǰ�ѱ���CA��*/
D_Result    ca_complied (D_U32* param) D_FUNCPOSTFIT;

/** @brief ��ȡCA��ID*/
//D_Result	ca_card_id (D_U32 *id) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
