/** @file
* @brief Ӧ��ģ��
*
* һ��Ӧ�ö�Ӧһ�������һ����Ϣ����
* @author ����
* @date 2005-6-16 ����: �����ļ�
* @date 2013-03-19 lc: ͳһƽ̨, ��������
*/

#ifndef _D_APP_H_
#define _D_APP_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dTask.h"
#include "dQueue.h"
#include "dSem.h"
#include "dMsg.h"

/** @brief Ӧ�þ��*/
typedef D_Handle	D_HApp;

/** @brief Ӧ����Ϣ�ص�����*/
typedef D_Result (*D_AppCallback) (D_Msg *msg) D_FUNCPOSTFIT;

typedef enum
{
    D_AppLock_Sync = 0,
    D_AppLock_SendMsg,
    D_AppLock_Destroy,
}D_AppSyncLockReason;

typedef struct
{
    D_HApp happ;
    D_AppSyncLockReason reason;
    D_Bool *force_exit;
}D_AppSyncLockHookParam;

/** @brief Ӧ�ù���ϵͳ��ʼ��
* @param create_main	�Ƿ�Ϊ�����񴴽�Ӧ����Դ
* @param qsize				������Ӧ�õ���Ϣ���д�С
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_app_open (D_Bool create_main, D_Size qsize) D_FUNCPOSTFIT;

/** @brief Ӧ�ù���ϵͳ��ֹ
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_app_close (void) D_FUNCPOSTFIT;

/** @brief ����һ����Ӧ��
* @param name	������
* @param priority	�������ȼ�
* @param stk_size	����ջ��С
* @param qsize ������Ϣ���д�С
* @param callback	Ӧ����Ϣ�ص�����
* @param arg	Ӧ�ó�ʼ������
* @return �ɹ�����Ӧ�þ��,ʧ�ܷ���D_INVALID_HANDLE
*/
D_HApp		d_app_create (D_Char *name, D_S8 priority, D_Size stk_size, D_Size qsize, D_AppCallback callback, D_Ptr arg) D_FUNCPOSTFIT;

/** @brief ����һ��Ӧ��
* @param happ Ӧ�þ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_app_destroy (D_HApp	happ) D_FUNCPOSTFIT;

/** @brief ��һ��Ӧ�ý�����Ϣͬ��
* @param happ Ӧ�þ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_app_sync (D_HApp happ) D_FUNCPOSTFIT;

/** @brief ��һ��Ӧ�÷�����Ϣ,�����Ϣ������,���ش���
* @param happ Ӧ�þ��
* @param msg ��Ϣ������
* @param size ��Ϣ��������С
* @param ms	���ͳ�ʱʱ��
* @retval D_OK	�����ɹ�
* @retval D_ERR_FULL	��Ϣ������
*/
D_Result	d_app_timed_send (D_HApp happ, D_Msg *msg, D_Size size, D_MSec ms) D_FUNCPOSTFIT;

/** @brief ��һ��Ӧ�÷�����Ϣ,�����Ϣ������,��ǰӦ�ñ�����
* @param happ Ӧ�þ��
* @param msg ��Ϣ������
* @param size ��Ϣ��������С
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
#define d_app_send(a,b,c)			d_app_timed_send(a,b,c,(D_MSec)-1)

/** @brief ��һ��Ӧ�÷�����Ϣ,�����Ϣ������,���ش���
* @param happ Ӧ�þ��
* @param msg ��Ϣ������
* @param size ��Ϣ��������С
* @retval D_OK	�����ɹ�
* @retval D_ERR_FULL	��Ϣ������
*/
#define d_app_try_send(a,b,c)	d_app_timed_send(a,b,c,0)

/** @brief ���ص�ǰӦ�ö�Ӧ����Ϣ���о��
* @param happ Ӧ�þ��
* @retval �ɹ�������Ϣ���о����ʧ�ܷ���D_INVALID_HANDLE
*/
D_HQueue	d_app_get_queue (D_HApp happ) D_FUNCPOSTFIT;

/** @brief �趨Ӧ����ص�˽������
* @param happ Ӧ�þ��
* @param pd	˽������ָ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_app_set_data (D_HApp happ, D_Ptr pd) D_FUNCPOSTFIT;

/** @brief ȡ��Ӧ����ص�˽������ָ��
* @param happ Ӧ�þ��
* @return ����˽������ָ��
*/
D_Ptr			d_app_get_data (D_HApp	happ) D_FUNCPOSTFIT;

/** @brief ���ص�ǰӦ�õľ��
*/
D_HApp		d_app_self (void) D_FUNCPOSTFIT;

/** @brief �趨Ӧ����Ϣ���ճ�ʱ
* @param happ Ӧ�þ��
* @param ms	��ʱʱ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_app_set_timeout (D_HApp happ, D_MSec ms) D_FUNCPOSTFIT;

/** @brief ͨ��app���ȡ��������
* @param happ Ӧ�þ��
* @return �ɹ�����������,ʧ�ܷ���D_INVALID_HANDLE
*/
D_HTask d_app_get_task_handle(D_HApp happ) D_FUNCPOSTFIT;


#ifdef  __cplusplus
}
#endif

#endif
