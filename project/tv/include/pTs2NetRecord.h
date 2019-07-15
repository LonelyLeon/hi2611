#ifndef _P_HAIER_PVR_TS_H
#define _P_HAIER_PVR_TS_H

#include "dTypes.h"


#ifdef  __cplusplus
extern "C"
{
#endif

/** @brief ¼�����ݴ���ص������ش���Ľ���������Ǵ�����룬0�������Ǵ�����ֽ���*/
typedef D_Size (*D_Ts2NetDataCBFunc) (D_U32 cb_data, D_U8 *pbuf, D_Size dlen) D_FUNCPOSTFIT;

/** @brief ��ʼ��
* @return �ɹ�����D_OK
*/
D_Result p_ts2net_record_open(void) D_FUNCPOSTFIT;


/** @brief ����ʼ��
* @return �ɹ�����D_OK
*/
D_Result p_ts2net_record_close(void) D_FUNCPOSTFIT;


/** @brief ��ʼts2net¼��
* @param[in] user_id �û���ʶ�ţ��û��Լ�ά������stopʱƥ��
* @param[in] dbsrvid ¼�ƵĽ�Ŀ��dbsrvid
* @param[in] cb ¼�����ݴ���ص������ش���Ľ���������Ǵ�����룬0�������Ǵ�����ֽ���
* @param cb_data �ص�ע�ᴫ�����, �ص����������˲�����������user_id
* @return �ɹ�����D_OK
*/
D_Result p_ts2net_record_start(D_U32 user_id, D_ID dbsrvid, D_Ts2NetDataCBFunc cb, D_U32 cb_data) D_FUNCPOSTFIT;


/** @brief ts2net ֹͣ¼�ƺ���
* @param[in] user_id �û���ʶ�ţ��û��Լ�ά������startʱƥ��
* @return  �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result p_ts2net_record_stop(D_U32 user_id)D_FUNCPOSTFIT;


/** @brief ���ӻ��л�Ƶ��ʱ���ã��жϵ���Ҫ���ŵ�Ƶ���Ƿ��뵱ǰ¼�Ƶ�Ƶ����ͬ��
�Ա㴦������ͬһ·demux������ͬ��pid��ʧ�ܵ�����
* @return �ɹ�����D_OK
*/
D_Result p_ts2net_record_swich_channel(D_ID dbsrvid) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif
