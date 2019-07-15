/** @file
* @brief ����Ĵ����͹���
* @author ����
* @date 2005-5-16 ����: �����ļ�
*/

#ifndef _D_TASK_H_
#define _D_TASK_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief ������*/
typedef D_Handle	D_HTask;

#define D_DEF_STACK_SIZE		0x1000
#define D_DEF_TASK_PRIORITY	    4

/** @brief ��������*/
typedef struct {
	D_ID		id;					/**< �豸ID*/
	D_Size	stack_size;	/**< ���ֽ�Ϊ��λ�Ķ�ջ��С*/
	D_Char *name;				/**< ������*/
	D_U8		priority;		/**< �������ȼ� (1-15),1���ȼ���ͣ�15���*/
} D_TaskAttr;

/** @brief ��ȱʡֵ��ʼ����������*/
#define D_TASK_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
		(_a)->stack_size = D_DEF_STACK_SIZE;\
		(_a)->name = (D_Char *)"Task";\
		(_a)->priority = D_DEF_TASK_PRIORITY;\
	D_MACRO_END

/** @brief ������ں���*/
typedef void (*D_TaskEntry) (D_Ptr ptr) D_FUNCPOSTFIT;

/** @brief ����ϵͳ��ʼ��
*
*	�ڵ���������ʱ���ȵ��ô˺���
* @retval D_OK	��ʼ���ɹ�
* @retval D_ERR	��ʼ��ʧ��
*/
D_Result	d_task_open (void) D_FUNCPOSTFIT;

/** @brief ����ϵͳ��ֹ
*
* �������ʱ���ͷ�����ϵͳ�ڵ���Դ
* @retval D_OK	�����ɹ�
* @retval D_ERR	����ʧ��
*/
D_Result	d_task_close (void) D_FUNCPOSTFIT;

/** @brief ����һ��������
* @param attr		�������Խṹָ��,���ΪNULL,����ȱʡֵ
* @param entry	������ں���
* @param arg		���ݸ�������ں����Ĳ���
* @return	��ȷʱ����������,����ʱ����D_INVALID_HANDLE��
*/
D_HTask		d_task_create (D_TaskAttr *attr, D_TaskEntry entry, D_Ptr arg) D_FUNCPOSTFIT;

/** @brief ���ص��������������
* @return ��������ľ��
*/
D_HTask		d_task_self (void) D_FUNCPOSTFIT;

/** @brief ������������
* @return �ú������᷵��
*/
void			d_task_exit (void) D_FUNCPOSTFIT;

/** @brief ��������������һ��ʱ��
*
*	ϵͳ��֤���������ڹ涨��ʱ���ڴ�������״̬������ִ��
* @param ms	�Ժ���Ϊ��λ������ʱ��
* @return ��ȷʱ����D_OK,����ʱ����D_ERR��
*/
D_Result	d_task_wait (D_MSec ms) D_FUNCPOSTFIT;

/** @brief �ȴ�һ���������
* @param ht	������
* @retval D_OK	�����ɹ�
* @retval D_ERR	����ʧ��
*/
D_Result	d_task_join (D_HTask ht) D_FUNCPOSTFIT;

D_Result d_task_join_timeout(D_HTask ht, D_MSec timeout)D_FUNCPOSTFIT;

/** @brief ɱ��ָ������
* @return ��ȷʱ����D_OK,����ʱ����D_ERR��
*/
D_Result d_task_kill (D_HTask ht) D_FUNCPOSTFIT;

/** @brief ��������˽������
* @return ��
*/
void d_task_priv_set (D_HTask ht, void *priv) D_FUNCPOSTFIT;

/** @brief �������˽������
* @return ˽������ָ��
*/
void* d_task_priv_get (D_HTask ht) D_FUNCPOSTFIT;

/** @brief ��������������һ��ʱ��
*
*	ϵͳ��֤���������ڹ涨��ʱ���ڴ�������״̬������ִ��
* @param ms	��tickΪ��λ������ʱ��
* @return ��ȷʱ����D_OK,����ʱ����D_ERR��
*/
D_Result	d_task_delay (D_U32 tick) D_FUNCPOSTFIT;

/** @brief ����������һ��ʱ��
*
*	ϵͳ��֤����������״̬������ִ��
* @param ht ������������
* @return ��ȷʱ����D_OK,����ʱ����D_ERR��
*/
D_Result	d_task_suspend (D_HTask ht) D_FUNCPOSTFIT;

/** @brief �ָ���������
*
*	ϵͳ��֤����ָ���������
* @param ht �ָ���������
* @return ��ȷʱ����D_OK,����ʱ����D_ERR��
*/
D_Result	d_task_resume (D_HTask ht) D_FUNCPOSTFIT;

/** @brief �������ǰ���ȼ�
*
* @param ht ������
* @return ��ȷ�����������ȼ�(1-15), ���󷵻�D_ERR
*/
D_Result d_task_get_prio(D_HTask ht) D_FUNCPOSTFIT;

/** @brief ��������ǰ���ȼ�
*
* @param ht ������
* @param prio Ҫ���õ��������ȼ�(1-15)
* @return ��ȷ����D_OK, ���󷵻�D_ERR
*/
D_Result d_task_set_prio(D_HTask ht, D_Int prio) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif

