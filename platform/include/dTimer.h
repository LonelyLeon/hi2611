/** @file
* @brief 定时器操作
* @author 龚克
* @date 2005-5-16 龚克: 建立文件
*/

#ifndef _D_TIMER_H_
#define _D_TIMER_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief 定时器句柄*/
typedef D_Handle	D_HTimer;

/** @brief 定时器属性*/
typedef struct {
	D_ID		id;				/**< 设备ID*/
	D_Bool	one_shot;	/**< 是否是单次型定时器*/
} D_TimerAttr;

/** @brief 用缺省值初始化定时器属性*/
#define D_TIMER_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->one_shot = D_FALSE;\
	D_MACRO_END

/** @brief 定时器触发的回调函数
* @param htimer	被触发的定时器句柄
* @handle handle	创建定时器时注册的参数句柄
*/
typedef D_Result (*D_TimerCallback) (D_HTimer htimer, D_Handle handle) D_FUNCPOSTFIT;

/** @brief 定时器管理系统初始化
*
*	在调用定时器函数时首先调用此函数
* @retval D_OK	初始化成功
* @retval D_ERR	初始化失败
*/
D_Result	d_timer_open (void) D_FUNCPOSTFIT;

/** @brief 定时器管理系统中止
*
* 程序结束时，释放定时器管理系统内的资源
* @retval D_OK	操作成功
* @retval D_ERR	操作失败
*/
D_Result	d_timer_close (void) D_FUNCPOSTFIT;

/** @brief 创建一个定时器
* @param attr	定时器属性结构指针，为NULL时使用缺省值(one_shot=D_FALSE)
* @param ms	毫秒为单位的超时时间
* @param handle	参数句柄,定时器触发的回调中将其传给回调函数
* @return 成功时返回定时器句柄，失败返回D_INVALID_HANDLE
*/
D_HTimer	d_timer_create (D_TimerAttr *attr, D_MSec ms, D_Handle handle) D_FUNCPOSTFIT;

/** @brief 重新设定定时器的超时时间
* @param htimer 定时器句柄
* @param ms	毫秒为单位的超时时间( (D_MSec)-1  时保留原来超时时间)
* @retval D_OK	操作成功
* @retval D_ERR	操作失败
*/
D_Result	d_timer_reset (D_HTimer htimer, D_MSec ms) D_FUNCPOSTFIT;

/** @brief 销毁一个定时器
* @param htimer 定时器句柄
* @retval D_OK	释放成功
* @retval	D_ERR_INVALID_HANDLE	句柄无效
*/
D_Result	d_timer_destroy (D_HTimer htimer) D_FUNCPOSTFIT;

/** @brief 注册定时器触发回调函数
* @param callback	回调函数指针
* @param old 如果非NULL,返回旧的回调函数指针
* @retval D_OK	注册成功
* @retval	D_ERR	注册失败
*/
D_Result	d_timer_register_callback (D_TimerCallback callback, D_TimerCallback *old) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
