#ifndef _P_HAIER_PVR_H
#define _P_HAIER_PVR_H

#include "dTypes.h"


#ifdef  __cplusplus
extern "C"
{
#endif

/** @brief ¼�����ݴ���ص������ش���Ľ���������Ǵ�����룬0�������Ǵ�����ֽ���*/
typedef D_Size (*D_HaierPvrDataDealCallback) (D_U32 dev_id, D_U8 *pbuf, D_Size dlen) D_FUNCPOSTFIT;

/** @brief ע��pvr¼�ƺ�����ݴ���ص�
* @return �ɹ�����D_OK
*/
D_Result p_haier_pvr_record_register(D_U32 dev_id, D_HaierPvrDataDealCallback callback) D_FUNCPOSTFIT;


/** @brief ��ʼ��
* @return �ɹ�����D_OK
*/
D_Result p_haier_pvr_record_open(void) D_FUNCPOSTFIT;


/** @brief ����ʼ��
* @return �ɹ�����D_OK
*/
D_Result p_haier_pvr_record_close(void) D_FUNCPOSTFIT;


/** @brief ��ʼpvr¼��
* @param[in] dev_id �豸�ţ������ڱ�ʶ��һ·�⸴��
* @param[in] dbsrvid ¼�ƵĽ�Ŀ��dbsrvid
* @return �ɹ�����D_OK
*/
D_Result p_haier_pvr_record_start(D_U32 dev_id, D_ID dbsrvid) D_FUNCPOSTFIT;


/** @brief pvrrec stop����
* @param[in] dev_id �豸�ţ������ڱ�ʶ��һ·�⸴��
* @return  �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result p_haier_pvr_record_stop(D_U32 dev_id)D_FUNCPOSTFIT;


#ifdef  __cplusplus
}
#endif
#endif
