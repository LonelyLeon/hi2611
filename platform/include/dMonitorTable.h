/**@defgroup MonitorTable SI表监控
*@{*/
/** @file
* @brief 节目监控模块
* @author 龚克
* @date 2005-7-11 龚克: 建立文件
* @date 2013-06-03 sunzy: 将该节目监控的函数从dtv.c分离出来组成该文件
* @date 2013-06-29 sunzy：为几个表添加定时监控功能
* @date 2013-07-25 hegx: 按要求修改、添加函数
*/
#ifndef _D_MONITORTABLE_H_
#define _D_MONITORTABLE_H_

#ifdef  __cplusplus
extern "C"
{
#endif
#include "dTV.h" 
#include "dApp.h"
/** @brief 回调函数类型定义 */
typedef D_U8 (*D_NitFunc)(D_FEndType ftype, D_FEndParam fparam);
/** @brief nit表控制参数 */ 
typedef struct {
	D_Bool	enable;//使能：  0---功能关闭（默认），1-功能开启。
	D_U8	moniter_mode;//监控方式：1---根据版本号监控，只搜索下一个版本号的信息。 2---随时监控，比较节目名字，如果不一样就更新。    
	D_U8	freq_mode;
	D_U32	time_out;
    D_HTimer time_hand;
    D_NitFunc freq_check;
 } D_NITConfigMoniter;

/** @brief sdt表控制参数 */ 
typedef struct {
	D_Bool	enable;//使能：  0---功能关闭（默认），1-功能开启。
	D_Bool	caenable;//使能：  0---功能关闭（默认），1-功能开启。
	D_Bool	nameenable;//使能：  0---功能关闭（默认），1-功能开启。
	D_U8	moniter_mode;//监控方式：1---根据版本号监控，只搜索下一个版本号的信息。 2---随时监控，比较节目名字，如果不一样就更新。    
	D_U32	time_out;
    D_HTimer time_hand;
} D_SDTConfigMoniter;
/** @brief pat表控制参数 */ 
typedef struct {
	D_Bool	enable;//使能：  0---功能关闭（默认），1-功能开启。
	D_U8	moniter_mode;//监控方式：1---根据版本号监控，只搜索下一个版本号的信息。 2---随时监控，比较节目名字，如果不一样就更新。    
	D_U32	time_out;
    D_HTimer time_hand;
} D_PATConfigMoniter;
/** @brief cat表控制参数 */ 
typedef struct {
	D_Bool	enable;//使能：  0---功能关闭（默认），1-功能开启。
	D_U8	moniter_mode;//监控方式：1---根据版本号监控，只搜索下一个版本号的信息。 2---随时监控，比较节目名字，如果不一样就更新。    
	D_U32	time_out;
    D_HTimer time_hand;
} D_CATConfigMoniter;
/** @brief tdt tot表控制参数 */ 
typedef struct {
	D_Bool	enable;//使能：  0---功能关闭（默认），1-功能开启。
	D_U8	moniter_mode;//监控方式：1---根据版本号监控，只搜索下一个版本号的信息。 2---随时监控，比较节目名字，如果不一样就更新。    
	D_U32	time_out;
    D_HTimer time_hand;
} D_TDTConfigMoniter;

/** @brief 表监控句柄*/ 
typedef D_Handle D_MonitorHandle;

/** @brief 自定义表监控解析函数*/
typedef D_Result (*D_MonitorParse) (TVData *tv, D_U8 *buf, D_Size size)D_FUNCPOSTFIT;

/** @brief 自定义表监控注册的最大个数*/
#define MAX_REG_MONITOR 4

/**@brief 打开注册表监控
*@param  app 应用句柄
*@return D_OK 成功 D_ERR 失败
*/
D_Result d_monitor_open(D_HApp app)D_FUNCPOSTFIT;

/**@brief 关闭注册表监控
*@return D_OK 成功 D_ERR 失败
*/
D_Result d_monitor_close(void)D_FUNCPOSTFIT;

/**@brief 创建表监控句柄
*@return D_Moniter_Handle 表监控句柄
*/
D_MonitorHandle d_monitor_create(D_MonitorParse parse,D_TimerAttr ta,D_U32 time_out)D_FUNCPOSTFIT;
D_MonitorHandle d_monitor_create_ex(D_MonitorParse parse,D_TimerAttr ta,D_U32 time_out,  D_Bool bfm)D_FUNCPOSTFIT;

/**@brief 设置表监控过滤参数
*@param handle 表监控句柄
*@return D_OK 成功 D_ERR 失败
*/
D_Result d_monitor_set_param(D_MonitorHandle handle,D_DemuxFilter filter)D_FUNCPOSTFIT;

/**@brief 开启表监控句柄
*@param handle 表监控句柄
*@return D_OK 成功 D_ERR 失败
*/
D_Result d_monitor_start(D_MonitorHandle handle)D_FUNCPOSTFIT;

/**@brief 开启表监控句柄
*@param msg 消息
*@param tv_data 电视数据
*@param size 数据大小
*@return D_OK 成功 D_ERR 失败
*/
D_Result 
d_moniter_parse (D_Msg *msg,TVData* tv_data, D_Size size) D_FUNCPOSTFIT;
/**@brief 停止表监控句柄
*@param handle 表监控句柄
*@return D_OK 成功 D_ERR 失败
*/
D_Result d_monitor_stop(D_MonitorHandle handle)D_FUNCPOSTFIT;

/**@brief 释放表监控句柄
*@param handle 表监控句柄
*@return D_OK 成功 D_ERR 失败
*/
D_Result d_monitor_destory(D_MonitorHandle handle)D_FUNCPOSTFIT;

/** @brief 开启TS SI分析
*@param[in] tv 节目数据
*@return D_OK 开启成功 D_ERR 开启失败
*/
 D_Result d_tv_start_ts_si(TVData *tv)D_FUNCPOSTFIT; 

/** @brief 停止TS SI分析
*@param[in] tv 节目数据
*@return D_OK 执行成功
*/
 D_Result d_tv_stop_ts_si (TVData *tv)D_FUNCPOSTFIT ;
/** @brief 开始PMT SI分析
*@param[in] tv 节目数据
*@return D_OK 开启成功 D_ERR 开启失败
*/
 D_Result d_tv_start_srv_si(TVData *tv)D_FUNCPOSTFIT;
/** @brief 停止PMT SI分析
*@param[in] tv 节目数据
*@return D_OK 执行成功
*/
 D_Result d_tv_stop_srv_si (TVData *tv)D_FUNCPOSTFIT;
 
/** @brief 待机时调用，监控nit表，这样才可以响应应急广播  qiny@2011-10-14
*@return D_OK 执行成功 D_ERR 执行失败
*/
D_Result d_tv_resume_scan_nit(void)D_FUNCPOSTFIT;
/*** @brief待机时信号不好时调用，停止监控nit表 qiny@2011-10-14
*@return D_OK 执行成功
*/
D_Result d_tv_stop_scan_nit(void)D_FUNCPOSTFIT;
 
/** @brief 分析PAT
*@param[in] tv data_tv 数据
*@param[in] buf 缓冲区数据
*@param[in] size 数据大小
*@return D_OK 解析成功 D_ERR 解析失败
*/
 D_Result d_tv_parse_pat (TVData *tv, D_U8 *buf, D_Size size)D_FUNCPOSTFIT ;
/** @brief 分析PMT
*@param[in] tv data_tv 数据
*@param[in] buf 缓冲区数据
*@param[in] size 数据大小
*@return D_OK 解析成功 D_ERR 解析失败
*/
 D_Result d_tv_parse_pmt (TVData *tv, D_U8 *buf, D_Size size)D_FUNCPOSTFIT ;
/** @brief 分析CAT
*@param[in] tv data_tv 数据
*@param[in] buf 缓冲区数据
*@param[in] size 数据大小
*@return D_OK 解析成功 D_ERR 解析失败
*/
 D_Result d_tv_parse_cat (TVData *tv, D_U8 *buf, D_Size size)D_FUNCPOSTFIT;
/** @brief 分析TDT
*@param[in] tv data_tv 数据
*@param[in] buf 缓冲区数据
*@param[in] size 数据大小
*@return D_OK 解析成功 D_ERR 解析失败
*/
 D_Result d_tv_parse_tdt (TVData *tv, D_U8 *buf, D_Size size)D_FUNCPOSTFIT;
/** @brief 分析NIT
*@param[in] tv data_tv 数据
*@param[in] buf 缓冲区数据
*@param[in] size 数据大小
*@return D_OK 解析成功 D_ERR 解析失败
*/
 D_Result d_tv_parse_nit (TVData *tv, D_U8 *buf, D_Size size)D_FUNCPOSTFIT;

/** @brief 分析SDT
*@param[in] tv data_tv 数据
*@param[in] buf 缓冲区数据
*@param[in] size 数据大小
*@return D_OK 解析成功 D_ERR 解析失败
*/
 D_Result d_tv_parse_sdt (TVData *tv, D_U8 *buf, D_Size size)D_FUNCPOSTFIT;

/**@brief 设置是否需要更新
*@param[in] mask 对应表
*@param[in] fdata 设置参数
*@return D_OK 设置成功
*/
D_Result d_set_need_version (D_TVScanMode mask,D_Ptr fdata)D_FUNCPOSTFIT;
/** @brief 定时开启表监控*/
D_Result d_moniter_timer(D_Msg *msg,TVData* tv_data)D_FUNCPOSTFIT;

/**@brief 获得是否需要版本控制标志
*@param[in] mask 对应表
*@return 1 需要表监控 0 不需要表监控
*/
D_U8 d_get_need_version (D_TVScanMode mask) D_FUNCPOSTFIT;
/** @brief 检查是否需要nit解析
*@param[in] ps data_tv的ps数据
*@return D_TRUE 需要 D_FALSE 不需要
*/
D_Bool d_moniter_nit_check(D_ProgScan* ps)D_FUNCPOSTFIT;
#ifdef  __cplusplus
}
#endif

#endif
/**@}*/
