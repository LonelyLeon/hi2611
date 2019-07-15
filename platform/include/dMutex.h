/** @file
* @brief ���������
* @author ����
* @date 2005-5-16 ����: �����ļ�
*/

#ifndef _D_MUTEX_H_
#define _D_MUTEX_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief ��������*/
typedef D_Handle	D_HMutex;

/** @brief ����������*/
typedef struct {
	D_ID		id;	/**< �豸ID*/
} D_MutexAttr;

/** @brief ��ȱʡ������ʼ���⸴���豸����*/
#define D_MUTEX_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
	D_MACRO_END

/** @brief ���������ϵͳ��ʼ��
*
*	�ڵ��û����庯��ʱ���ȵ��ô˺���
* @retval D_OK	��ʼ���ɹ�
* @retval D_ERR	��ʼ��ʧ��
*/
D_Result	d_mutex_open (void) D_FUNCPOSTFIT;

/** @brief ���������ϵͳ��ֹ
*
* �������ʱ���ͷŻ��������ϵͳ�ڵ���Դ
* @retval D_OK	�����ɹ�
* @retval D_ERR	����ʧ��
*/
D_Result	d_mutex_close (void) D_FUNCPOSTFIT;

/** @brief ����һ��������
* @param attr	���������Խṹָ�룬ΪNULLʱʹ��ȱʡֵ
* @return �ɹ�ʱ���ػ���������ʧ�ܷ���D_INVALID_HANDLE
*/
D_HMutex	d_mutex_create (D_MutexAttr *attr) D_FUNCPOSTFIT;

/** @brief ����һ��������
* @param hmutex ��������
* @retval D_OK	�ͷųɹ�
* @retval	D_ERR_INVALID_HANDLE	�����Ч
*/
D_Result	d_mutex_destroy (D_HMutex hmutex) D_FUNCPOSTFIT;

/** @brief ���������
*
* ���������״̬Ϊlocked,��������������ֱ��
*	������״̬��Ϊunlocked��������״̬��Ϊlocked,�������ء�
* @param hmutex	��������
* @retval D_OK	�����ɹ�
* @retval D_ERR_INVALID_HANDLE	�����Ч
*/
D_Result	d_mutex_lock (D_HMutex hmutex) D_FUNCPOSTFIT;

/** @brief ���������
*
* ��������״̬��Ϊunlocked��
* @param hmutex
* @retval D_OK
* @retval D_ERR_INVALID_HANDLE
*/
D_Result	d_mutex_unlock (D_HMutex hmutex) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
