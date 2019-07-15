/** @file
* @brief 互斥体操作
* @author 龚克
* @date 2005-5-16 龚克: 建立文件
*/

#ifndef _D_MUTEX_H_
#define _D_MUTEX_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief 互斥体句柄*/
typedef D_Handle	D_HMutex;

/** @brief 互斥体属性*/
typedef struct {
	D_ID		id;	/**< 设备ID*/
} D_MutexAttr;

/** @brief 用缺省参数初始化解复用设备属性*/
#define D_MUTEX_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
	D_MACRO_END

/** @brief 互斥体管理系统初始化
*
*	在调用互斥体函数时首先调用此函数
* @retval D_OK	初始化成功
* @retval D_ERR	初始化失败
*/
D_Result	d_mutex_open (void) D_FUNCPOSTFIT;

/** @brief 互斥体管理系统中止
*
* 程序结束时，释放互斥体管理系统内的资源
* @retval D_OK	操作成功
* @retval D_ERR	操作失败
*/
D_Result	d_mutex_close (void) D_FUNCPOSTFIT;

/** @brief 创建一个互斥体
* @param attr	互斥体属性结构指针，为NULL时使用缺省值
* @return 成功时返回互斥体句柄，失败返回D_INVALID_HANDLE
*/
D_HMutex	d_mutex_create (D_MutexAttr *attr) D_FUNCPOSTFIT;

/** @brief 销毁一个互斥体
* @param hmutex 互斥体句柄
* @retval D_OK	释放成功
* @retval	D_ERR_INVALID_HANDLE	句柄无效
*/
D_Result	d_mutex_destroy (D_HMutex hmutex) D_FUNCPOSTFIT;

/** @brief 互斥体加锁
*
* 如果互斥体状态为locked,调用任务被阻塞，直到
*	互斥体状态变为unlocked。互斥体状态变为locked,函数返回。
* @param hmutex	互斥体句柄
* @retval D_OK	操作成功
* @retval D_ERR_INVALID_HANDLE	句柄无效
*/
D_Result	d_mutex_lock (D_HMutex hmutex) D_FUNCPOSTFIT;

/** @brief 互斥体解锁
*
* 将互斥体状态变为unlocked。
* @param hmutex
* @retval D_OK
* @retval D_ERR_INVALID_HANDLE
*/
D_Result	d_mutex_unlock (D_HMutex hmutex) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
