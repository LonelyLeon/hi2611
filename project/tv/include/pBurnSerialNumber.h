/**@defgroup sn-burn ���к���дģ�� 
*@{*/
/** @file
* @brief ���к���дģ��
* @author ��ΰ��
* @date 2013-08-20 ��ΰ��: �����ļ�
*/

#ifndef _P_BURNSERIALNUMBER_H_
#define _P_BURNSERIALNUMBER_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dSerial.h"
#include "dTask.h"

typedef enum
{
	INITIALIZE, //��ʼ��
	HANDLE,		//����
	DESTROY,	//����
}OPERATE_TYPE;

/**@brief ���庯��ָ��*/
typedef D_Result (* FUNCTION)(D_HSerial s_hdl, OPERATE_TYPE type)D_FUNCPOSTFIT;


/** @brief ��д���к�
* @param[in] flag 1�������������е�ĳʱ����д���кţ�0�����뱾����Ϣ������д���к�
	���뱾����Ϣ������д�Ƿ�ֹ����ʱ��д���ɹ��������ڽ������ʱ��дһ�Σ�������ʱ����д�ɹ����������ʱ�����ظ���д��
* @param[in] surf ͼ�α������������軭��ʾ��
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result p_burn_serial_number(D_U8 flag, D_GSurface * surf) D_FUNCPOSTFIT;

/** @brief �������ڼ������
* @param[in] priority �������ȼ�
* @param[in] func ע����ⲿ����ָ��
* @param[in] total_time ���ڼ�ص���ʱ��
* @param[in] if_strt_up �Ƿ񿪻�ʱ��д���кţ�D_TRUE���ǣ�D_FALSE����
* @return �ɹ�����������,ʧ�ܷ���D_INVALID_HANDLE
*/
D_HTask p_serial_monitor_create(D_S8 priority, FUNCTION func, D_U32 total_time, D_Bool if_strt_up)D_FUNCPOSTFIT; 

/** @brief  ����Ƿ��ǿ���ʱ��д���к�
* @return ��д��ʽ���
*/
D_Bool p_serial_check_if_bur_when_start_up (void)D_FUNCPOSTFIT;
 
/** @brief  ��ô��ڼ��������
* @return ������
*/
D_HTask p_serial_monitor_get_task_hdl (void)D_FUNCPOSTFIT;
 
/** @brief  �������ڼ������
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result p_serial_monitor_destroy (void)D_FUNCPOSTFIT; 

/** @brief ��д���к�
* @param[in] sl_hdl�����ھ��
* @param[in] type����������
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result p_bur_sn_handle(D_HSerial sl_hdl, OPERATE_TYPE type) D_FUNCPOSTFIT;

/** @brief ��д����ƽ��
* @param[in] sl_hdl�����ھ��
* @param[in] type����������
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result p_tv_bur_sn_handle(D_HSerial sl_hdl, OPERATE_TYPE type) D_FUNCPOSTFIT;

D_Result p_js_bur_sn_handle(D_HSerial sl_hdl, OPERATE_TYPE type) D_FUNCPOSTFIT;
D_Result p_es_bur_sn_handle(D_HSerial sl_hdl, OPERATE_TYPE type) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif

/**@}*/
