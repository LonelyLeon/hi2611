/** @file
* @brief 任务的创建和管理
* @author 龚克
* @date 2005-5-16 龚克: 建立文件
*/

#ifndef _D_TASK_H_
#define _D_TASK_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief 任务句柄*/
typedef D_Handle	D_HTask;

#define D_DEF_STACK_SIZE		0x1000
#define D_DEF_TASK_PRIORITY	    4

/** @brief 任务属性*/
typedef struct {
	D_ID		id;					/**< 设备ID*/
	D_Size	stack_size;	/**< 以字节为单位的堆栈大小*/
	D_Char *name;				/**< 任务名*/
	D_U8		priority;		/**< 任务优先级 (1-15),1优先级最低，15最高*/
} D_TaskAttr;

/** @brief 用缺省值初始化任务属性*/
#define D_TASK_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
		(_a)->stack_size = D_DEF_STACK_SIZE;\
		(_a)->name = (D_Char *)"Task";\
		(_a)->priority = D_DEF_TASK_PRIORITY;\
	D_MACRO_END

/** @brief 任务入口函数*/
typedef void (*D_TaskEntry) (D_Ptr ptr) D_FUNCPOSTFIT;

/** @brief 任务系统初始化
*
*	在调用任务函数时首先调用此函数
* @retval D_OK	初始化成功
* @retval D_ERR	初始化失败
*/
D_Result	d_task_open (void) D_FUNCPOSTFIT;

/** @brief 任务系统中止
*
* 程序结束时，释放任务系统内的资源
* @retval D_OK	操作成功
* @retval D_ERR	操作失败
*/
D_Result	d_task_close (void) D_FUNCPOSTFIT;

/** @brief 创建一个新任务
* @param attr		任务属性结构指针,如果为NULL,采用缺省值
* @param entry	任务入口函数
* @param arg		传递给任务入口函数的参数
* @return	正确时返回任务句柄,错误时返回D_INVALID_HANDLE。
*/
D_HTask		d_task_create (D_TaskAttr *attr, D_TaskEntry entry, D_Ptr arg) D_FUNCPOSTFIT;

/** @brief 返回调用任务的任务句柄
* @return 调用任务的句柄
*/
D_HTask		d_task_self (void) D_FUNCPOSTFIT;

/** @brief 结束调用任务
* @return 该函数不会返回
*/
void			d_task_exit (void) D_FUNCPOSTFIT;

/** @brief 将调用任务阻塞一段时间
*
*	系统保证调用任务在规定的时间内处于阻塞状态，不被执行
* @param ms	以毫秒为单位的阻塞时间
* @return 正确时返回D_OK,错误时返回D_ERR。
*/
D_Result	d_task_wait (D_MSec ms) D_FUNCPOSTFIT;

/** @brief 等待一个任务结束
* @param ht	任务句柄
* @retval D_OK	操作成功
* @retval D_ERR	操作失败
*/
D_Result	d_task_join (D_HTask ht) D_FUNCPOSTFIT;

D_Result d_task_join_timeout(D_HTask ht, D_MSec timeout)D_FUNCPOSTFIT;

/** @brief 杀死指定任务
* @return 正确时返回D_OK,错误时返回D_ERR。
*/
D_Result d_task_kill (D_HTask ht) D_FUNCPOSTFIT;

/** @brief 设置任务私有数据
* @return 无
*/
void d_task_priv_set (D_HTask ht, void *priv) D_FUNCPOSTFIT;

/** @brief 获得任务私有数据
* @return 私有数据指针
*/
void* d_task_priv_get (D_HTask ht) D_FUNCPOSTFIT;

/** @brief 将调用任务阻塞一段时间
*
*	系统保证调用任务在规定的时间内处于阻塞状态，不被执行
* @param ms	以tick为单位的阻塞时间
* @return 正确时返回D_OK,错误时返回D_ERR。
*/
D_Result	d_task_delay (D_U32 tick) D_FUNCPOSTFIT;

/** @brief 将任务阻塞一段时间
*
*	系统保证任务处于阻塞状态，不被执行
* @param ht 阻塞的任务句柄
* @return 正确时返回D_OK,错误时返回D_ERR。
*/
D_Result	d_task_suspend (D_HTask ht) D_FUNCPOSTFIT;

/** @brief 恢复任务运行
*
*	系统保证任务恢复正常运行
* @param ht 恢复的任务句柄
* @return 正确时返回D_OK,错误时返回D_ERR。
*/
D_Result	d_task_resume (D_HTask ht) D_FUNCPOSTFIT;

/** @brief 获得任务当前优先级
*
* @param ht 任务句柄
* @return 正确返回任务优先级(1-15), 错误返回D_ERR
*/
D_Result d_task_get_prio(D_HTask ht) D_FUNCPOSTFIT;

/** @brief 设置任务当前优先级
*
* @param ht 任务句柄
* @param prio 要设置的任务优先级(1-15)
* @return 正确返回D_OK, 错误返回D_ERR
*/
D_Result d_task_set_prio(D_HTask ht, D_Int prio) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif

