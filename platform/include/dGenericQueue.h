#ifndef __D_GENERICQUEUE_H
#define __D_GENERICQUEUE_H

#include "dTypes.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/** @brief ��Ϣ���о��*/
typedef D_Handle D_HGenQueue;

/** @brief ��Ϣ��������*/
typedef struct {
	D_ID id;		    /**< �豸ID*/
	D_Size queue_size;	/**< ��Ϣ���д�С*/
	D_Size item_size;   /**< ��Ϣ��С*/
} D_GenQueueAttr;

#define D_DEF_GENQUEUE_SIZE	 (32)
#define D_DEF_GENQUEUE_ITEM_SIZE (32)

/** @brief ��ȱʡֵ��ʼ����Ϣ��������*/
#define D_GENQUEUE_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
		(_a)->queue_size = D_DEF_GENQUEUE_SIZE;\
		(_a)->item_size = D_DEF_GENQUEUE_ITEM_SIZE;\
	D_MACRO_END

/** @brief ��Ϣ���й���ϵͳ��ʼ��
*
*	�ڵ�����Ϣ���к���ʱ���ȵ��ô˺���
* @retval D_OK	��ʼ���ɹ�
* @retval D_ERR	��ʼ��ʧ��
*/
D_Result	d_gen_queue_open (void) D_FUNCPOSTFIT;

/** @brief ��Ϣ���й���ϵͳ��ֹ
*
* �������ʱ���ͷ���Ϣ���й���ϵͳ�ڵ���Դ
* @retval D_OK	�����ɹ�
* @retval D_ERR	����ʧ��
*/
D_Result	d_gen_queue_close (void) D_FUNCPOSTFIT;

/** @brief ����һ���µ���Ϣ����
* @param attr	��Ϣ�������Խṹָ��,���ΪNULL,ʹ��ȱʡֵ
* @return	��ȷʱ��Ϣ���о��,����ʱ����D_INVALID_HANDLE��
*/
D_HGenQueue	d_gen_queue_create (D_GenQueueAttr *attr) D_FUNCPOSTFIT;

/** @brief ����һ����Ϣ����
* @param hq	Ҫ���ٵ���Ϣ���о��
* @retval D_OK	�����ɹ�
* @retval D_ERR_INVALID_HANDLE	�����Ч
*/
D_Result	d_gen_queue_destroy (D_HGenQueue hq) D_FUNCPOSTFIT;

/** @brief ������һ����Ϣ�����з�������
 *
 *	�����Ϣ������û���㹻��Ŀռ�����Ҫ���͵�����,
 *	����������������D_ERR_FULL������пռ䣬
 *	�����ݿ�������Ϣ���л�������
 *	�������ء�
 * @param hq		��Ϣ���о��
 * @param msg		Ҫ���͵����ݻ�����ָ��
 * @param size	Ҫ���͵������ֽ���
 * @param ms		�ȴ���ʱ(0��ʾ�������أ�-1��ʾһֱ�ȴ�)
 * @retval D_OK	���ݷ��ͳɹ�
 * @retval D_ERR_INVALID_HANDLE		�����Ч
 * @retval D_ERR_INVALID_ARGUMENT	�����������(msg=NULL)
 * @retval D_ERR_NO_SPACE	���������ڶ������������ֽ���
 * @retval D_ERR_FULL	��Ϣ����û���㹻�ռ���������
 */
D_Result	d_gen_queue_timed_send (D_HGenQueue hq, D_U8 *msg, D_U32 size, D_MSec ms) D_FUNCPOSTFIT;

/** @brief ���Դ�һ����Ϣ�����н�������(����ʱ)
 *
 *	�����Ϣ������û������,����������������D_ERR_EMPTY��
 *	��������ݣ������ݴ���Ϣ���п������������У��������ء�
 * @param hq		��Ϣ���о��
 * @param buf		�������ݵĻ�����ָ��
 * @param size	�������ݵĻ������Ĵ�С
 * @param ms		�ȴ���ʱ(0��ʾ�������أ�-1��ʾһֱ�ȴ�)
 * @return �ɹ�ʱ����ʵ�ʽ��յ��ֽ���
 * @retval D_ERR_INVALID_HANDLE		�����Ч
 * @retval D_ERR_INVALID_ARGUMENT	�����������(msg=NULL����recv_size=NULL)
 * @retval D_ERR_NO_SPACE	��������СС�ڶ�������Ϣ�Ĵ�С
 * @retval D_ERR_EMPTY	��Ϣ������û������
 */
D_Result	d_gen_queue_timed_recv (D_HGenQueue hq, D_U8 *buf, D_U32 size, D_MSec ms) D_FUNCPOSTFIT;

/** @brief ��һ����Ϣ�����з�������
 *
 *	�����Ϣ������û���㹻��Ŀռ�����Ҫ���͵�����,
 *	���������������״̬,ֱ����������Ӷ�����ȡ������,
 *	ʹ�������㹻�ռ�Ϊֹ�������ݿ�������Ϣ���л�������
 *	�������ء�
 * @param a		��Ϣ���о��
 * @param b		Ҫ���͵����ݻ�����ָ��
 * @param c	Ҫ���͵������ֽ���
 * @retval D_OK	���ݷ��ͳɹ�
 * @retval D_ERR_INVALID_HANDLE		�����Ч
 * @retval D_ERR_INVALID_ARGUMENT	�����������(msg=NULL)
 * @retval D_ERR_NO_SPACE	���������ڶ������������ֽ���
 */
#define d_gen_queue_send(a,b,c)			d_gen_queue_timed_send(a,b,c,(D_MSec)-1)

/** @brief ������һ����Ϣ�����з�������
 *
 *	�����Ϣ������û���㹻��Ŀռ�����Ҫ���͵�����,
 *	����������������D_ERR_FULL������пռ䣬
 *	�����ݿ�������Ϣ���л�������
 *	�������ء�
 * @param a		��Ϣ���о��
 * @param b		Ҫ���͵����ݻ�����ָ��
 * @param c	Ҫ���͵������ֽ���
 * @retval D_OK	���ݷ��ͳɹ�
 * @retval D_ERR_INVALID_HANDLE		�����Ч
 * @retval D_ERR_INVALID_ARGUMENT	�����������(msg=NULL)
 * @retval D_ERR_NO_SPACE	���������ڶ������������ֽ���
 * @retval D_ERR_FULL	��Ϣ����û���㹻�ռ���������
 */
#define d_gen_queue_try_send(a,b,c)	d_gen_queue_timed_send(a,b,c,0)

/** @brief ��һ����Ϣ�����н�������
 *
 *	�����Ϣ������û������,��������������ֱ��������������Ϊֹ��
 *	�����ݴ���Ϣ���п������������У��������ء�
 * @param a		��Ϣ���о��
 * @param b		�������ݵĻ�����ָ��
 * @param c	�������ݵĻ������Ĵ�С
 * @return �ɹ�ʱ����ʵ�ʽ��յ��ֽ���
 * @retval D_ERR_INVALID_HANDLE		�����Ч
 * @retval D_ERR_INVALID_ARGUMENT	�����������(msg=NULL����recv_size=NULL)
 * @retval D_ERR_NO_SPACE	��������СС�ڶ�������Ϣ�Ĵ�С
 */
#define d_gen_queue_recv(a,b,c)			d_gen_queue_timed_recv(a,b,c,(D_MSec)-1)

/** @brief ���Դ�һ����Ϣ�����н�������
 *
 *	�����Ϣ������û������,����������������D_ERR_EMPTY��
 *	��������ݣ������ݴ���Ϣ���п������������У��������ء�
 * @param a		��Ϣ���о��
 * @param b		�������ݵĻ�����ָ��
 * @param c	�������ݵĻ������Ĵ�С
 * @return �ɹ�ʱ����ʵ�ʽ��յ��ֽ���
 * @retval D_ERR_INVALID_HANDLE		�����Ч
 * @retval D_ERR_INVALID_ARGUMENT	�����������(msg=NULL����recv_size=NULL)
 * @retval D_ERR_NO_SPACE	��������СС�ڶ�������Ϣ�Ĵ�С
 * @retval D_ERR_EMPTY	��Ϣ������û������
 */
#define d_gen_queue_try_recv(a,b,c)	d_gen_queue_timed_recv(a,b,c,0)

/** @brief �ӿ���Ϣ��������һ�������ڷ��͵���Ϣ
* @param[in] hq ��Ϣ���о��
* @param[in] ms ��ʱʱ����뵥λ
* @return �ɹ�������Ϣָ��, ���󷵻�NULL
*/
void* d_gen_queue_timed_claim_from_queue(D_HGenQueue hq, D_MSec ms) D_FUNCPOSTFIT;

/** @brief ����Ϣ���͵����ݶ�����
* @param[in] hq ��Ϣ���о��
* @param[in] msg ��Ϣָ��
* @return �ɹ�D_OK, ����D_ERR
*/
D_Result d_gen_queue_send_to_queue(D_HGenQueue hq, void *msg) D_FUNCPOSTFIT;

/** @brief �����ݶ�����ȡ��һ����Ϣ
* @param[in] hq ��Ϣ���о��
* @param[in] ms ��ʱʱ����뵥λ
* @return �ɹ�������Ϣָ��, ���󷵻�NULL
*/
void* d_gen_queue_timed_recv_from_queue(D_HGenQueue hq, D_MSec ms) D_FUNCPOSTFIT;

/** @brief ����Ϣ�ͷŻؿն���
* @param[in] hq ��Ϣ���о��
* @param[in] msg ��Ϣָ��
* @return �ɹ�D_OK, ����D_ERR
*/
D_Result d_gen_queue_release_to_queue(D_HGenQueue hq, void *msg) D_FUNCPOSTFIT;

/** @brief �����Ϣ����
* @param[in] hq ��Ϣ���о��
* @return �ɹ�D_OK, ����D_ERR
*/
D_Result d_gen_queue_empty_queue(D_HGenQueue hq) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif
