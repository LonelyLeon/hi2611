/** @file
* @brief 信号量操作
* @author 龚克
* @date 2005-5-16 龚克: 建立文件
*/

#ifndef _D_SEM_H_
#define _D_SEM_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief 信号量句柄*/
typedef D_Handle	D_HSem;

/** @brief 信号量属性*/
typedef struct {
	D_ID	id;				/**< 设备ID*/
	D_Int	init_val;	/**< 信号量初始值*/
} D_SemAttr;

/** @brief 用缺省值初始化信号量属性*/
#define D_SEM_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
		(_a)->init_val = 0;\
	D_MACRO_END

/** @brief 信号量管理系统初始化
*
*	在调用信号量函数时首先调用此函数
* @retval D_OK	初始化成功
* @retval D_ERR	初始化失败
*/
D_Result	d_sem_open (void) D_FUNCPOSTFIT;

/** @brief 信号量管理系统中止
*
* 程序结束时，释放信号量管理系统内的资源
* @retval D_OK	操作成功
* @retval D_ERR	操作失败
*/
D_Result	d_sem_close (void) D_FUNCPOSTFIT;

/** @brief 创建一个信号量
* @param attr	信号量属性结构指针，为NULL时使用缺省值(初始值为0)
* @return 成功时返回信号量句柄，失败返回D_INVALID_HANDLE
*/
D_HSem		d_sem_create (D_SemAttr *attr) D_FUNCPOSTFIT;

/** @brief 销毁一个信号量
* @param hsem 信号量句柄
* @retval D_OK	释放成功
* @retval	D_ERR_INVALID_HANDLE	句柄无效
*/
D_Result	d_sem_destroy (D_HSem hsem) D_FUNCPOSTFIT;

/** @brief 设置一个信号量
*
*	自动增加信号量的内部计数值。
* @param hsem 信号量句柄
* @retval D_OK	操作成功
* @retval	D_ERR_INVALID_HANDLE	句柄无效
*/
D_Result	d_sem_post (D_HSem hsem) D_FUNCPOSTFIT;

/** @brief 等待一个信号量
*
*	如果信号量计数小于1，阻塞调用任务，直到信号量计数
*	大于等于1。此时将信号量计数减1，函数返回。
* @param hsem 信号量句柄
* @retval D_OK	操作成功
* @retval	D_ERR_INVALID_HANDLE	句柄无效
*/
D_Result	d_sem_wait (D_HSem hsem) D_FUNCPOSTFIT;


/*
* @brief 根据设置时间等待一个信号量 
* 如果信号量计数小于1，阻塞调用任务，直到信号量计数
* 大于等于1。此时将信号量计数减1，函数返回。
* @param hsem 信号量句柄
* @param 
* @retval D_OK	操作成功
* @retval D_ERR_INVALID_HANDLE	句柄无效
*/
D_Result d_sem_wait_timeout (D_HSem hsem,D_Time ms) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
