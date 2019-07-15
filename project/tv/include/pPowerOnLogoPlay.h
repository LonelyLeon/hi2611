/**@defgroup plogo logo和广告模块
*@{*/

/** @file
* @brief 开机logo播放任务
* @author qiny
* @date 2014-02-26 qiny: 创建文件
*/
#include "stdio.h"
#include "dTypes.h"

typedef void (*PLOGO_CALLBACK)(D_U32 event);

/** @brief 启动开机logo播放任务函数
* @return def_time 默认一帧播放时间
* @return 错误代码
*/
D_Result 
p_power_on_logo_play_start(D_Time def_time)D_FUNCPOSTFIT;

/** @brief 线束logo播放任务函数
* @return 错误代码
*/
D_Result 
p_power_on_logo_play_end(void)D_FUNCPOSTFIT;

/* @}*/

