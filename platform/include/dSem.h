/** @file
* @brief �ź�������
* @author ����
* @date 2005-5-16 ����: �����ļ�
*/

#ifndef _D_SEM_H_
#define _D_SEM_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief �ź������*/
typedef D_Handle	D_HSem;

/** @brief �ź�������*/
typedef struct {
	D_ID	id;				/**< �豸ID*/
	D_Int	init_val;	/**< �ź�����ʼֵ*/
} D_SemAttr;

/** @brief ��ȱʡֵ��ʼ���ź�������*/
#define D_SEM_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
		(_a)->init_val = 0;\
	D_MACRO_END

/** @brief �ź�������ϵͳ��ʼ��
*
*	�ڵ����ź�������ʱ���ȵ��ô˺���
* @retval D_OK	��ʼ���ɹ�
* @retval D_ERR	��ʼ��ʧ��
*/
D_Result	d_sem_open (void) D_FUNCPOSTFIT;

/** @brief �ź�������ϵͳ��ֹ
*
* �������ʱ���ͷ��ź�������ϵͳ�ڵ���Դ
* @retval D_OK	�����ɹ�
* @retval D_ERR	����ʧ��
*/
D_Result	d_sem_close (void) D_FUNCPOSTFIT;

/** @brief ����һ���ź���
* @param attr	�ź������Խṹָ�룬ΪNULLʱʹ��ȱʡֵ(��ʼֵΪ0)
* @return �ɹ�ʱ�����ź��������ʧ�ܷ���D_INVALID_HANDLE
*/
D_HSem		d_sem_create (D_SemAttr *attr) D_FUNCPOSTFIT;

/** @brief ����һ���ź���
* @param hsem �ź������
* @retval D_OK	�ͷųɹ�
* @retval	D_ERR_INVALID_HANDLE	�����Ч
*/
D_Result	d_sem_destroy (D_HSem hsem) D_FUNCPOSTFIT;

/** @brief ����һ���ź���
*
*	�Զ������ź������ڲ�����ֵ��
* @param hsem �ź������
* @retval D_OK	�����ɹ�
* @retval	D_ERR_INVALID_HANDLE	�����Ч
*/
D_Result	d_sem_post (D_HSem hsem) D_FUNCPOSTFIT;

/** @brief �ȴ�һ���ź���
*
*	����ź�������С��1��������������ֱ���ź�������
*	���ڵ���1����ʱ���ź���������1���������ء�
* @param hsem �ź������
* @retval D_OK	�����ɹ�
* @retval	D_ERR_INVALID_HANDLE	�����Ч
*/
D_Result	d_sem_wait (D_HSem hsem) D_FUNCPOSTFIT;


/*
* @brief ��������ʱ��ȴ�һ���ź��� 
* ����ź�������С��1��������������ֱ���ź�������
* ���ڵ���1����ʱ���ź���������1���������ء�
* @param hsem �ź������
* @param 
* @retval D_OK	�����ɹ�
* @retval D_ERR_INVALID_HANDLE	�����Ч
*/
D_Result d_sem_wait_timeout (D_HSem hsem,D_Time ms) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
