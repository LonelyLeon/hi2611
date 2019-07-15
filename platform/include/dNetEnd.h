/** @file
* @brief ��������������
* @author �
* @date 2014-05-07 : �
                     �����ļ�
*/
#ifndef _D_NETEND_H_
#define _D_NETEND_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief �����豸���*/
typedef D_Handle D_HNEnd;
/** @brief ���ջص����� */
typedef void (*D_NEnd_ReceiveIndicate_Func)(D_HNEnd hnend, D_Ptr packet, D_U32 packet_length, D_Ptr ctx) D_FUNCPOSTFIT;

/** @brief �����豸������Ϣ���� */
#define NEND_OIDDATA_BASE                       0x80000000

#define NEND_OIDDATA_GETMACADDRESS              (NEND_OIDDATA_BASE + 1)   /**< ���MAC��ַ */
#define NEND_OIDDATA_SETMACADDRESS              (NEND_OIDDATA_BASE + 2)   /**< ����MAC��ַ */
#define NEND_OIDDATA_GETMULTICASTADDRLIST       (NEND_OIDDATA_BASE + 3)   /**< ��öಥ�б� */
#define NEND_OIDDATA_SETMULTICASTADDRLIST       (NEND_OIDDATA_BASE + 4)   /**< ���öಥ�б� */
#define NEND_OIDDATA_GETFILTER                  (NEND_OIDDATA_BASE + 5)   /**< ��ù���ģʽ */
#define NEND_OIDDATA_SETFILTER                  (NEND_OIDDATA_BASE + 6)   /**< ���ù���ģʽ */
#define NEND_OIDDATA_RESET                      (NEND_OIDDATA_BASE + 7)   /**< ��λ�豸 */

/** @brief ����ģʽ*/
typedef enum
{
    NEND_FILTERMODE_DIRECT = 1,  /**< ֱ��ģʽ, ֻ������ձ���MAC��ַ������ */
    NEND_FILTERMODE_BROADCAST,   /**< �㲥ģʽ, ֻ������չ㲥���� */
    NEND_FILTERMODE_PROMISCUOUS, /**< ����ģʽ, ���ս������������κ����� */
}D_NEndParamFilterMode;

/** @brief �����豸״ֵ̬*/
#define NEND_STATUS_LINKED                      0x00000001

/** @brief �������ò���*/
typedef struct
{
    D_U32 oid_type; /**< ������Ϣ���� */
    D_Ptr oid_data;  /**< ������Ϣ���ݻ����� */
    D_U32 oid_datalength; /**< ������Ϣ���ݳ��� */
}D_NEndParam;

/** @brief ����״̬*/
typedef struct {
    D_U32 status;
} D_NEndStatus;

/** @brief �����豸����*/
typedef struct {
	D_ID id; /**< �����豸ID*/
} D_NEndAttr;

/** @brief ��ȱʡ���ó�ʼ�������豸����*/
#define D_NEND_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
	D_MACRO_END

/** @brief ����ϵͳ��ʼ��
*
*	�ڵ������˲�������ʱ���ȵ��ô˺���
* @retval D_OK	��ʼ���ɹ�
* @retval D_ERR	��ʼn��ʧ��
*/
D_Result d_nend_open(void) D_FUNCPOSTFIT;

/** @brief ���˹���ϵͳ��ֹ
*
* �������ʱ���ͷ�����ϵͳ�ڵ���Դ
* @retval D_OK	�����ɹ�
* @retval D_ERR	����ʧ��
*/
D_Result d_nend_close(void) D_FUNCPOSTFIT;

/** @brief ����һ�������豸
* @param attr	�����豸���Խṹָ�룬ΪNULLʱʹ��ȱʡֵ
* @return �ɹ�ʱ���������豸�����ʧ�ܷ���D_INVALID_HANDLE
*/
D_HNEnd	d_nend_create(D_NEndAttr *attr) D_FUNCPOSTFIT;

/** @brief ����һ�������豸
* @param hnend �����豸���
* @retval D_OK	�ͷųɹ�
* @retval	D_ERR_INVALID_HANDLE	�����Ч
*/
D_Result d_nend_destroy(D_HNEnd hnend) D_FUNCPOSTFIT;

/** @brief �趨һ�������豸�Ĳ���
* @param hnend	�����豸���
* @param param	���˲���
* @retval D_OK	�����ɹ�
* @retval	D_ERR_INVALID_HANDLE		�����Ч
* @retval	D_ERR_INVALID_ARGUMENT	���� @a param ��Ч
*/
D_Result d_nend_set_param(D_HNEnd hnend, D_NEndParam *param) D_FUNCPOSTFIT;


/** @brief ȡ��һ�������豸��ǰ״̬
* @param hnend	�����豸���
* @param status	�����豸״̬�ṹ������ָ��
* @retval D_OK	�����ɹ�
* @retval D_ERR_INVALID_HANDLE		�����Ч
* @retval D_ERR_INVALID_ARGUMENT	statusΪNULL
*/
D_Result d_nend_get_status(D_HNEnd hnend, D_NEndStatus *status) D_FUNCPOSTFIT;


/** @brief ��һ�������豸��������
* @param hnend	�����豸���
* @param buf 	���ݻ�����ָ��
* @param buf_length ���ݳ���
* @retval D_OK	�����ɹ�
* @retval D_ERR_INVALID_HANDLE		�����Ч
* @retval D_ERR_INVALID_ARGUMENT	bufΪNULL, ��buf_lengthΪ0
*/
D_Result d_nend_send_data(D_HNEnd hnend, D_U8* buf, D_U32 buf_length) D_FUNCPOSTFIT;

/** @brief ע��һ�����ջص�����
* @param hnend	�����豸���
* @param receiveindicate_func �ص�ָ��
* @param ctx  �ص�����
* @retval D_ERR_INVALID_ARGUMENT	receiveindicate_funcΪNULL
*/
D_Result d_nend_register_receiveindicate_callback(D_HNEnd hnend, D_NEnd_ReceiveIndicate_Func receiveindicate_func, D_Ptr ctx) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif

