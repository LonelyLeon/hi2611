/** @file
* @brief 消息队列操作
* @author 龚克
* @date 2005-5-16 龚克: 建立文件
*/

#ifndef _D_QUEUE_H_
#define _D_QUEUE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief 消息队列句柄*/
typedef D_Handle	D_HQueue;

/** @brief 消息队列属性*/
typedef struct {
	D_ID		id;		/**< 设备ID*/
	D_Size	size;	/**< 消息队列大小*/
} D_QueueAttr;

#define D_DEF_QUEUE_SIZE	(1024)

/** @brief 用缺省值初始化消息队列属性*/
#define D_QUEUE_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
		(_a)->size = D_DEF_QUEUE_SIZE;\
	D_MACRO_END

/** @brief 消息队列管理系统初始化
*
*	在调用消息队列函数时首先调用此函数
* @retval D_OK	初始化成功
* @retval D_ERR	初始化失败
*/
D_Result	d_queue_open (void) D_FUNCPOSTFIT;

/** @brief 消息队列管理系统中止
*
* 程序结束时，释放消息队列管理系统内的资源
* @retval D_OK	操作成功
* @retval D_ERR	操作失败
*/
D_Result	d_queue_close (void) D_FUNCPOSTFIT;

/** @brief 创建一个新的消息队列
* @param attr	消息队列属性结构指针,如果为NULL,使用缺省值
* @return	正确时消息队列句柄,错误时返回D_INVALID_HANDLE。
*/
D_HQueue	d_queue_create (D_QueueAttr *attr) D_FUNCPOSTFIT;

/** @brief 销毁一个消息队列
* @param hq	要销毁的消息队列句柄
* @retval D_OK	操作成功
* @retval D_ERR_INVALID_HANDLE	句柄无效
*/
D_Result	d_queue_destroy (D_HQueue hq) D_FUNCPOSTFIT;

/** @brief 尝试向一个消息队列中发送数据
 *
 *	如果消息队列中没有足够大的空间容纳要发送的数据,
 *	调用任务立即返回D_ERR_FULL。如果有空间，
 *	将数据拷贝到消息队列缓冲区，
 *	函数返回。
 * @param hq		消息队列句柄
 * @param msg		要发送的数据缓冲区指针
 * @param size	要发送的数据字节数
 * @param ms		等待超时(0表示立即返回，-1表示一直等待)
 * @retval D_OK	数据发送成功
 * @retval D_ERR_INVALID_HANDLE		句柄无效
 * @retval D_ERR_INVALID_ARGUMENT	输入参数错误(msg=NULL)
 * @retval D_ERR_NO_SPACE	数据量大于队列最大可容纳字节数
 * @retval D_ERR_FULL	消息队列没有足够空间容纳数据
 */
D_Result	d_queue_timed_send (D_HQueue hq, D_U8 *msg, D_U32 size, D_MSec ms) D_FUNCPOSTFIT;

/** @brief 尝试从一个消息队列中接收数据(带超时)
 *
 *	如果消息队列中没有数据,调用任务立即返回D_ERR_EMPTY。
 *	如果有数据，将数据从消息队列拷贝到缓冲区中，函数返回。
 * @param hq		消息队列句柄
 * @param buf		接收数据的缓冲区指针
 * @param size	接收数据的缓冲区的大小
 * @param ms		等待超时(0表示立即返回，-1表示一直等待)
 * @return 成功时返回实际接收的字节数
 * @retval D_ERR_INVALID_HANDLE		句柄无效
 * @retval D_ERR_INVALID_ARGUMENT	输入参数错误(msg=NULL，或recv_size=NULL)
 * @retval D_ERR_NO_SPACE	缓冲区大小小于队列中消息的大小
 * @retval D_ERR_EMPTY	消息队列中没有数据
 */
D_Result	d_queue_timed_recv (D_HQueue hq, D_U8 *buf, D_U32 size, D_MSec ms) D_FUNCPOSTFIT;

/** @brief 向一个消息队列中发送数据
 *
 *	如果消息队列中没有足够大的空间容纳要发送的数据,
 *	调用任务进入阻塞状态,直到其他任务从队列中取出数据,
 *	使队列有足够空间为止。将数据拷贝到消息队列缓冲区，
 *	函数返回。
 * @param a		消息队列句柄
 * @param b		要发送的数据缓冲区指针
 * @param c	要发送的数据字节数
 * @retval D_OK	数据发送成功
 * @retval D_ERR_INVALID_HANDLE		句柄无效
 * @retval D_ERR_INVALID_ARGUMENT	输入参数错误(msg=NULL)
 * @retval D_ERR_NO_SPACE	数据量大于队列最大可容纳字节数
 */
#define d_queue_send(a,b,c)			d_queue_timed_send(a,b,c,(D_MSec)-1)

/** @brief 尝试向一个消息队列中发送数据
 *
 *	如果消息队列中没有足够大的空间容纳要发送的数据,
 *	调用任务立即返回D_ERR_FULL。如果有空间，
 *	将数据拷贝到消息队列缓冲区，
 *	函数返回。
 * @param a		消息队列句柄
 * @param b		要发送的数据缓冲区指针
 * @param c	要发送的数据字节数
 * @retval D_OK	数据发送成功
 * @retval D_ERR_INVALID_HANDLE		句柄无效
 * @retval D_ERR_INVALID_ARGUMENT	输入参数错误(msg=NULL)
 * @retval D_ERR_NO_SPACE	数据量大于队列最大可容纳字节数
 * @retval D_ERR_FULL	消息队列没有足够空间容纳数据
 */
#define d_queue_try_send(a,b,c)	d_queue_timed_send(a,b,c,0)

/** @brief 从一个消息队列中接收数据
 *
 *	如果消息队列中没有数据,调用任务阻塞。直到队列中有数据为止，
 *	将数据从消息队列拷贝到缓冲区中，函数返回。
 * @param a		消息队列句柄
 * @param b		接收数据的缓冲区指针
 * @param c	接收数据的缓冲区的大小
 * @return 成功时返回实际接收的字节数
 * @retval D_ERR_INVALID_HANDLE		句柄无效
 * @retval D_ERR_INVALID_ARGUMENT	输入参数错误(msg=NULL，或recv_size=NULL)
 * @retval D_ERR_NO_SPACE	缓冲区大小小于队列中消息的大小
 */
#define d_queue_recv(a,b,c)			d_queue_timed_recv(a,b,c,(D_MSec)-1)

/** @brief 尝试从一个消息队列中接收数据
 *
 *	如果消息队列中没有数据,调用任务立即返回D_ERR_EMPTY。
 *	如果有数据，将数据从消息队列拷贝到缓冲区中，函数返回。
 * @param a		消息队列句柄
 * @param b		接收数据的缓冲区指针
 * @param c	接收数据的缓冲区的大小
 * @return 成功时返回实际接收的字节数
 * @retval D_ERR_INVALID_HANDLE		句柄无效
 * @retval D_ERR_INVALID_ARGUMENT	输入参数错误(msg=NULL，或recv_size=NULL)
 * @retval D_ERR_NO_SPACE	缓冲区大小小于队列中消息的大小
 * @retval D_ERR_EMPTY	消息队列中没有数据
 */
#define d_queue_try_recv(a,b,c)	d_queue_timed_recv(a,b,c,0)

#ifdef  __cplusplus
}
#endif

#endif
