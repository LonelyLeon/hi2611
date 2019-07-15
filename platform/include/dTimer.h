/** @file
* @brief ��ʱ������
* @author ����
* @date 2005-5-16 ����: �����ļ�
*/

#ifndef _D_TIMER_H_
#define _D_TIMER_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief ��ʱ�����*/
typedef D_Handle	D_HTimer;

/** @brief ��ʱ������*/
typedef struct {
	D_ID		id;				/**< �豸ID*/
	D_Bool	one_shot;	/**< �Ƿ��ǵ����Ͷ�ʱ��*/
} D_TimerAttr;

/** @brief ��ȱʡֵ��ʼ����ʱ������*/
#define D_TIMER_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->one_shot = D_FALSE;\
	D_MACRO_END

/** @brief ��ʱ�������Ļص�����
* @param htimer	�������Ķ�ʱ�����
* @handle handle	������ʱ��ʱע��Ĳ������
*/
typedef D_Result (*D_TimerCallback) (D_HTimer htimer, D_Handle handle) D_FUNCPOSTFIT;

/** @brief ��ʱ������ϵͳ��ʼ��
*
*	�ڵ��ö�ʱ������ʱ���ȵ��ô˺���
* @retval D_OK	��ʼ���ɹ�
* @retval D_ERR	��ʼ��ʧ��
*/
D_Result	d_timer_open (void) D_FUNCPOSTFIT;

/** @brief ��ʱ������ϵͳ��ֹ
*
* �������ʱ���ͷŶ�ʱ������ϵͳ�ڵ���Դ
* @retval D_OK	�����ɹ�
* @retval D_ERR	����ʧ��
*/
D_Result	d_timer_close (void) D_FUNCPOSTFIT;

/** @brief ����һ����ʱ��
* @param attr	��ʱ�����Խṹָ�룬ΪNULLʱʹ��ȱʡֵ(one_shot=D_FALSE)
* @param ms	����Ϊ��λ�ĳ�ʱʱ��
* @param handle	�������,��ʱ�������Ļص��н��䴫���ص�����
* @return �ɹ�ʱ���ض�ʱ�������ʧ�ܷ���D_INVALID_HANDLE
*/
D_HTimer	d_timer_create (D_TimerAttr *attr, D_MSec ms, D_Handle handle) D_FUNCPOSTFIT;

/** @brief �����趨��ʱ���ĳ�ʱʱ��
* @param htimer ��ʱ�����
* @param ms	����Ϊ��λ�ĳ�ʱʱ��( (D_MSec)-1  ʱ����ԭ����ʱʱ��)
* @retval D_OK	�����ɹ�
* @retval D_ERR	����ʧ��
*/
D_Result	d_timer_reset (D_HTimer htimer, D_MSec ms) D_FUNCPOSTFIT;

/** @brief ����һ����ʱ��
* @param htimer ��ʱ�����
* @retval D_OK	�ͷųɹ�
* @retval	D_ERR_INVALID_HANDLE	�����Ч
*/
D_Result	d_timer_destroy (D_HTimer htimer) D_FUNCPOSTFIT;

/** @brief ע�ᶨʱ�������ص�����
* @param callback	�ص�����ָ��
* @param old �����NULL,���ؾɵĻص�����ָ��
* @retval D_OK	ע��ɹ�
* @retval	D_ERR	ע��ʧ��
*/
D_Result	d_timer_register_callback (D_TimerCallback callback, D_TimerCallback *old) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
