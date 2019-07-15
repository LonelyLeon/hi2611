/** @file
* @brief 同步事件操作
* @author 龚克
* @date 2005-5-16 龚克: 建立文件
*/

#ifndef _D_EVENT_H_
#define _D_EVENT_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief 同步事件句柄*/
typedef D_Handle	D_HEvent;

/** @brief 同步事件属性*/
typedef struct {
	D_ID		id;				/**< 设备ID*/
	D_Bool	init_val;	/**< 事件的初始值*/
} D_EventAttr;

/** @brief 按缺省配置初始化Event属性*/
#define D_EVENT_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
		(_a)->init_val = 0;\
	D_MACRO_END

/** @brief 同步事件管理系统初始化
*
*	在调用同步事件函数时首先调用此函数
* @retval D_OK	初始化成功
* @retval D_ERR	初始化失败
*/
D_Result	d_event_open (void) D_FUNCPOSTFIT;

/** @brief 同步事件管理系统中止
*
* 程序结束时，释放同步事件管理系统内的资源
* @retval D_OK	操作成功
* @retval D_ERR	操作失败
*/
D_Result	d_event_close (void) D_FUNCPOSTFIT;

/** @brief 创建一个同步事件
* @param attr	同步事件属性结构指针，为NULL时使用缺省值(init_val=D_FALSE)
* @return 成功时返回事件句柄，失败返回D_INVALID_HANDLE
*/
D_HEvent	d_event_create (D_EventAttr *attr) D_FUNCPOSTFIT;

/** @brief 销毁一个同步事件
* @param hevent	同步事件句柄
* @retval D_OK	释放成功
* @retval	D_ERR_INVALID_HANDLE	句柄无效
*/
D_Result	d_event_destroy (D_HEvent hevent) D_FUNCPOSTFIT;

/** @brief 解除一个等待指定时间的任务的阻塞状态
*
*	将事件值设为真，只唤醒一个等待事件的任务,如果有多个任务等待事件,被唤醒的任务不确定。
* @param hevent	事件句柄
* @retval D_OK	操作成功
* @retval D_ERR_INVALID_HANDLE	句柄无效
*/
D_Result	d_event_signal (D_HEvent hevent) D_FUNCPOSTFIT;

/** @brief 解除所有等待指定时间的任务的阻塞状态
*
*	将事件值设为真，唤醒所有等待事件的任务。
* @param hevent	事件句柄
* @retval D_OK	操作成功
* @retval D_ERR_INVALID_HANDLE	句柄无效
*/
D_Result	d_event_broadcast (D_HEvent hevent) D_FUNCPOSTFIT;

/** @brief 等待一个事件的发生。
*
*	如事件值为假，将调用任务变为阻塞状态，等待事件的发生。直到事件值为真，或者超时。
* @param hevent	事件句柄
* @param ms	以毫秒为单位的超时时间，如果为-1,将永远等待事件的发生
* @retval D_OK	操作成功
* @retval D_ERR_INVALID_HANDLE	句柄无效
* @retval D_ERR_TIMEOUT	时间超时，事件还没有发生
*/
D_Result	d_event_wait (D_HEvent hevent, D_MSec ms) D_FUNCPOSTFIT;

/** @brief 将事件值设为假
* @param hevent	事件句柄
* @retval D_OK	操作成功
* @retval D_ERR_INVALID_HANDLE	句柄无效
*/
D_Result	d_event_clear (D_HEvent hevent) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
