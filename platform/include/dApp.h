/** @file
* @brief 应用模块
*
* 一个应用对应一个任务和一个消息队列
* @author 龚克
* @date 2005-6-16 龚克: 建立文件
* @date 2013-03-19 lc: 统一平台, 代码整理
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

/** @brief 应用句柄*/
typedef D_Handle	D_HApp;

/** @brief 应用消息回调函数*/
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

/** @brief 应用管理系统初始化
* @param create_main	是否为主任务创建应用资源
* @param qsize				主任务应用的消息队列大小
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_app_open (D_Bool create_main, D_Size qsize) D_FUNCPOSTFIT;

/** @brief 应用管理系统终止
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_app_close (void) D_FUNCPOSTFIT;

/** @brief 创建一个新应用
* @param name	任务名
* @param priority	任务优先级
* @param stk_size	任务栈大小
* @param qsize 任务消息队列大小
* @param callback	应用消息回调函数
* @param arg	应用初始化参数
* @return 成功返回应用句柄,失败返回D_INVALID_HANDLE
*/
D_HApp		d_app_create (D_Char *name, D_S8 priority, D_Size stk_size, D_Size qsize, D_AppCallback callback, D_Ptr arg) D_FUNCPOSTFIT;

/** @brief 结束一个应用
* @param happ 应用句柄
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_app_destroy (D_HApp	happ) D_FUNCPOSTFIT;

/** @brief 和一个应用进行消息同步
* @param happ 应用句柄
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_app_sync (D_HApp happ) D_FUNCPOSTFIT;

/** @brief 向一个应用发送消息,如果消息队列满,返回错误
* @param happ 应用句柄
* @param msg 消息缓冲区
* @param size 消息缓冲区大小
* @param ms	发送超时时间
* @retval D_OK	操作成功
* @retval D_ERR_FULL	消息队列满
*/
D_Result	d_app_timed_send (D_HApp happ, D_Msg *msg, D_Size size, D_MSec ms) D_FUNCPOSTFIT;

/** @brief 向一个应用发送消息,如果消息队列满,当前应用被挂起
* @param happ 应用句柄
* @param msg 消息缓冲区
* @param size 消息缓冲区大小
* @return 成功返回D_OK,失败返回D_ERR
*/
#define d_app_send(a,b,c)			d_app_timed_send(a,b,c,(D_MSec)-1)

/** @brief 向一个应用发送消息,如果消息队列满,返回错误
* @param happ 应用句柄
* @param msg 消息缓冲区
* @param size 消息缓冲区大小
* @retval D_OK	操作成功
* @retval D_ERR_FULL	消息队列满
*/
#define d_app_try_send(a,b,c)	d_app_timed_send(a,b,c,0)

/** @brief 返回当前应用对应的消息队列句柄
* @param happ 应用句柄
* @retval 成功返回消息队列句柄，失败返回D_INVALID_HANDLE
*/
D_HQueue	d_app_get_queue (D_HApp happ) D_FUNCPOSTFIT;

/** @brief 设定应用相关的私有数据
* @param happ 应用句柄
* @param pd	私有数据指针
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_app_set_data (D_HApp happ, D_Ptr pd) D_FUNCPOSTFIT;

/** @brief 取得应用相关的私有数据指针
* @param happ 应用句柄
* @return 返回私有数据指针
*/
D_Ptr			d_app_get_data (D_HApp	happ) D_FUNCPOSTFIT;

/** @brief 返回当前应用的句柄
*/
D_HApp		d_app_self (void) D_FUNCPOSTFIT;

/** @brief 设定应用消息接收超时
* @param happ 应用句柄
* @param ms	超时时间
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_app_set_timeout (D_HApp happ, D_MSec ms) D_FUNCPOSTFIT;

/** @brief 通过app句柄取得任务句柄
* @param happ 应用句柄
* @return 成功返回任务句柄,失败返回D_INVALID_HANDLE
*/
D_HTask d_app_get_task_handle(D_HApp happ) D_FUNCPOSTFIT;


#ifdef  __cplusplus
}
#endif

#endif
