/** @file
* @brief ͬ���¼�����
* @author ����
* @date 2005-5-16 ����: �����ļ�
*/

#ifndef _D_EVENT_H_
#define _D_EVENT_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief ͬ���¼����*/
typedef D_Handle	D_HEvent;

/** @brief ͬ���¼�����*/
typedef struct {
	D_ID		id;				/**< �豸ID*/
	D_Bool	init_val;	/**< �¼��ĳ�ʼֵ*/
} D_EventAttr;

/** @brief ��ȱʡ���ó�ʼ��Event����*/
#define D_EVENT_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
		(_a)->init_val = 0;\
	D_MACRO_END

/** @brief ͬ���¼�����ϵͳ��ʼ��
*
*	�ڵ���ͬ���¼�����ʱ���ȵ��ô˺���
* @retval D_OK	��ʼ���ɹ�
* @retval D_ERR	��ʼ��ʧ��
*/
D_Result	d_event_open (void) D_FUNCPOSTFIT;

/** @brief ͬ���¼�����ϵͳ��ֹ
*
* �������ʱ���ͷ�ͬ���¼�����ϵͳ�ڵ���Դ
* @retval D_OK	�����ɹ�
* @retval D_ERR	����ʧ��
*/
D_Result	d_event_close (void) D_FUNCPOSTFIT;

/** @brief ����һ��ͬ���¼�
* @param attr	ͬ���¼����Խṹָ�룬ΪNULLʱʹ��ȱʡֵ(init_val=D_FALSE)
* @return �ɹ�ʱ�����¼������ʧ�ܷ���D_INVALID_HANDLE
*/
D_HEvent	d_event_create (D_EventAttr *attr) D_FUNCPOSTFIT;

/** @brief ����һ��ͬ���¼�
* @param hevent	ͬ���¼����
* @retval D_OK	�ͷųɹ�
* @retval	D_ERR_INVALID_HANDLE	�����Ч
*/
D_Result	d_event_destroy (D_HEvent hevent) D_FUNCPOSTFIT;

/** @brief ���һ���ȴ�ָ��ʱ������������״̬
*
*	���¼�ֵ��Ϊ�棬ֻ����һ���ȴ��¼�������,����ж������ȴ��¼�,�����ѵ�����ȷ����
* @param hevent	�¼����
* @retval D_OK	�����ɹ�
* @retval D_ERR_INVALID_HANDLE	�����Ч
*/
D_Result	d_event_signal (D_HEvent hevent) D_FUNCPOSTFIT;

/** @brief ������еȴ�ָ��ʱ������������״̬
*
*	���¼�ֵ��Ϊ�棬�������еȴ��¼�������
* @param hevent	�¼����
* @retval D_OK	�����ɹ�
* @retval D_ERR_INVALID_HANDLE	�����Ч
*/
D_Result	d_event_broadcast (D_HEvent hevent) D_FUNCPOSTFIT;

/** @brief �ȴ�һ���¼��ķ�����
*
*	���¼�ֵΪ�٣������������Ϊ����״̬���ȴ��¼��ķ�����ֱ���¼�ֵΪ�棬���߳�ʱ��
* @param hevent	�¼����
* @param ms	�Ժ���Ϊ��λ�ĳ�ʱʱ�䣬���Ϊ-1,����Զ�ȴ��¼��ķ���
* @retval D_OK	�����ɹ�
* @retval D_ERR_INVALID_HANDLE	�����Ч
* @retval D_ERR_TIMEOUT	ʱ�䳬ʱ���¼���û�з���
*/
D_Result	d_event_wait (D_HEvent hevent, D_MSec ms) D_FUNCPOSTFIT;

/** @brief ���¼�ֵ��Ϊ��
* @param hevent	�¼����
* @retval D_OK	�����ɹ�
* @retval D_ERR_INVALID_HANDLE	�����Ч
*/
D_Result	d_event_clear (D_HEvent hevent) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
