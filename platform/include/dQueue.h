/** @file
* @brief ��Ϣ���в���
* @author ����
* @date 2005-5-16 ����: �����ļ�
*/

#ifndef _D_QUEUE_H_
#define _D_QUEUE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief ��Ϣ���о��*/
typedef D_Handle	D_HQueue;

/** @brief ��Ϣ��������*/
typedef struct {
	D_ID		id;		/**< �豸ID*/
	D_Size	size;	/**< ��Ϣ���д�С*/
} D_QueueAttr;

#define D_DEF_QUEUE_SIZE	(1024)

/** @brief ��ȱʡֵ��ʼ����Ϣ��������*/
#define D_QUEUE_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
		(_a)->size = D_DEF_QUEUE_SIZE;\
	D_MACRO_END

/** @brief ��Ϣ���й���ϵͳ��ʼ��
*
*	�ڵ�����Ϣ���к���ʱ���ȵ��ô˺���
* @retval D_OK	��ʼ���ɹ�
* @retval D_ERR	��ʼ��ʧ��
*/
D_Result	d_queue_open (void) D_FUNCPOSTFIT;

/** @brief ��Ϣ���й���ϵͳ��ֹ
*
* �������ʱ���ͷ���Ϣ���й���ϵͳ�ڵ���Դ
* @retval D_OK	�����ɹ�
* @retval D_ERR	����ʧ��
*/
D_Result	d_queue_close (void) D_FUNCPOSTFIT;

/** @brief ����һ���µ���Ϣ����
* @param attr	��Ϣ�������Խṹָ��,���ΪNULL,ʹ��ȱʡֵ
* @return	��ȷʱ��Ϣ���о��,����ʱ����D_INVALID_HANDLE��
*/
D_HQueue	d_queue_create (D_QueueAttr *attr) D_FUNCPOSTFIT;

/** @brief ����һ����Ϣ����
* @param hq	Ҫ���ٵ���Ϣ���о��
* @retval D_OK	�����ɹ�
* @retval D_ERR_INVALID_HANDLE	�����Ч
*/
D_Result	d_queue_destroy (D_HQueue hq) D_FUNCPOSTFIT;

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
D_Result	d_queue_timed_send (D_HQueue hq, D_U8 *msg, D_U32 size, D_MSec ms) D_FUNCPOSTFIT;

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
D_Result	d_queue_timed_recv (D_HQueue hq, D_U8 *buf, D_U32 size, D_MSec ms) D_FUNCPOSTFIT;

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
#define d_queue_send(a,b,c)			d_queue_timed_send(a,b,c,(D_MSec)-1)

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
#define d_queue_try_send(a,b,c)	d_queue_timed_send(a,b,c,0)

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
#define d_queue_recv(a,b,c)			d_queue_timed_recv(a,b,c,(D_MSec)-1)

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
#define d_queue_try_recv(a,b,c)	d_queue_timed_recv(a,b,c,0)

#ifdef  __cplusplus
}
#endif

#endif
