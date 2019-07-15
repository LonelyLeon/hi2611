/**@defgroup sn-burn 序列号烧写模块 
*@{*/
/** @file
* @brief 序列号烧写模块
* @author 刘伟峰
* @date 2013-08-20 刘伟峰: 建立文件
*/

#ifndef _P_BURNSERIALNUMBER_H_
#define _P_BURNSERIALNUMBER_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dSerial.h"
#include "dTask.h"

typedef enum
{
	INITIALIZE, //初始化
	HANDLE,		//处理
	DESTROY,	//销毁
}OPERATE_TYPE;

/**@brief 定义函数指针*/
typedef D_Result (* FUNCTION)(D_HSerial s_hdl, OPERATE_TYPE type)D_FUNCPOSTFIT;


/** @brief 烧写序列号
* @param[in] flag 1：开机启动进行到某时段烧写序列号；0：进入本机信息界面烧写序列号
	进入本机信息界面烧写是防止开机时烧写不成功，可以在进入界面时烧写一次，若开机时已烧写成功，进入界面时不会重复烧写。
* @param[in] surf 图形表面句柄，用于描画提示语
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result p_burn_serial_number(D_U8 flag, D_GSurface * surf) D_FUNCPOSTFIT;

/** @brief 创建串口监控任务
* @param[in] priority 任务优先级
* @param[in] func 注册的外部函数指针
* @param[in] total_time 串口监控的总时间
* @param[in] if_strt_up 是否开机时烧写序列号，D_TRUE：是；D_FALSE：否
* @return 成功返回任务句柄,失败返回D_INVALID_HANDLE
*/
D_HTask p_serial_monitor_create(D_S8 priority, FUNCTION func, D_U32 total_time, D_Bool if_strt_up)D_FUNCPOSTFIT; 

/** @brief  检查是否是开机时烧写序列号
* @return 烧写方式标记
*/
D_Bool p_serial_check_if_bur_when_start_up (void)D_FUNCPOSTFIT;
 
/** @brief  获得串口监控任务句柄
* @return 任务句柄
*/
D_HTask p_serial_monitor_get_task_hdl (void)D_FUNCPOSTFIT;
 
/** @brief  结束串口监控任务
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result p_serial_monitor_destroy (void)D_FUNCPOSTFIT; 

/** @brief 烧写序列号
* @param[in] sl_hdl：串口句柄
* @param[in] type：操作类型
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result p_bur_sn_handle(D_HSerial sl_hdl, OPERATE_TYPE type) D_FUNCPOSTFIT;

/** @brief 烧写调白平衡
* @param[in] sl_hdl：串口句柄
* @param[in] type：操作类型
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result p_tv_bur_sn_handle(D_HSerial sl_hdl, OPERATE_TYPE type) D_FUNCPOSTFIT;

D_Result p_js_bur_sn_handle(D_HSerial sl_hdl, OPERATE_TYPE type) D_FUNCPOSTFIT;
D_Result p_es_bur_sn_handle(D_HSerial sl_hdl, OPERATE_TYPE type) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif

/**@}*/
