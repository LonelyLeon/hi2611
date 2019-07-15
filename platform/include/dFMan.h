/** @file
* @brief 前端管理模块
*
* 前端管理任务
* @author 龚克
* @date 2005-6-16 龚克: 建立文件
*/

#ifndef _D_FMAN_H_
#define _D_FMAN_H_

#include "dApp.h"
#include "dDBase.h"

#ifdef  __cplusplus
extern "C"
{
#endif


/** @brief 前端管理器句柄*/
typedef D_HApp	D_HFMan;

/** @brief 前端管理器任务数据*/
typedef struct
{
    D_FEndType ftype;
    D_FEndParam param;
    D_FEndLnbInfo lnbsetinfo;
}D_FManParam;


D_Result	d_fman_open (void) D_FUNCPOSTFIT;
D_Result	d_fman_close (void) D_FUNCPOSTFIT;
D_HFMan		d_fman_create (D_S8 priority, D_FEndAttr *attr) D_FUNCPOSTFIT;
D_Result 	d_fman_set_param (D_HFMan fm, D_FEndParam *param, D_Bool track, D_FEndType fendtype, D_DBSateInfo *sateinfo, D_DBAnteInfo *anteinfo) D_FUNCPOSTFIT;
D_Result 	d_fman_get_locked_req (D_HFMan fm, D_HQueue hq) D_FUNCPOSTFIT;
D_Result 	d_fman_get_status_req (D_HFMan fm, D_HQueue hq) D_FUNCPOSTFIT;
D_Result	d_fman_set_locked_detector (D_HFMan fm, D_HQueue hq) D_FUNCPOSTFIT;
D_Result	d_fman_get_dev_attr (D_HFMan fm, D_FEndAttr *attr) D_FUNCPOSTFIT;
D_Result	d_fman_get_param (D_HFMan fm, D_FEndParam *param, D_FEndType  *fendtype) D_FUNCPOSTFIT;
D_Result 	d_fman_blind_set_param (D_HFMan fm, D_FEndBlindCmd cmd, D_FEndType fendtype, D_FBlindParam *param, D_HQueue hq) D_FUNCPOSTFIT;
D_Result	d_fman_destroy (D_HFMan fm) D_FUNCPOSTFIT;
D_HFMan d_fman_get_handle_by_type(D_FEndType type, D_Int order) D_FUNCPOSTFIT;
D_Result d_fman_select_lnb_osc_dvbs(D_FEndLnbInfo *antinfo, D_FEndParam *param, D_FEndLnbInfo *lsi)D_FUNCPOSTFIT;

/** @brief 通过前端管理器设定diseqc命令
* @param fm 前端设备句柄
* @param diseqc diseqc命令
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_fman_set_diseqc_cmd(D_HFMan fm, D_FEndDiSEqC *diseqc) D_FUNCPOSTFIT;

/** @brief 通过前端管理器设定tuner供电不否
* @param fm 前端设备句柄
* @param enable 供电与否
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_fman_set_lnb_power_enable(D_HFMan fm, D_Bool enable) D_FUNCPOSTFIT;

/** @brief 清前端锁状态查询请求
* @param fm 前端管理设备句柄
* @param hq	消息队列句柄,前端管理器通过句柄返回锁状态消息
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_fman_clear_lock_req(D_HFMan fm, D_HQueue hq) D_FUNCPOSTFIT;

/** @brief 清前端设备状态查询请求
* @param fm 前端管理设备句柄
* @param hq	消息队列句柄,前端管理器通过句柄返回设备状态消息
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_fman_clear_status_req(D_HFMan fm, D_HQueue hq) D_FUNCPOSTFIT;
D_Result d_fman_set_stdby (D_HFMan fm) D_FUNCPOSTFIT;

/** @brief 通过前端管理器设定从待机恢复
* @param fm 前端设备句柄
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result
d_fman_set_wakeup(D_HFMan fm) D_FUNCPOSTFIT;
/** @brief 设置fman 空闲时监控锁频模式。
* @param fm 前端管理设备句柄
* @param monitor_mode	是否
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_fman_set_monitor_mode(D_HFMan fm, D_Bool monitor_mode) D_FUNCPOSTFIT;

/** @brief 设置fman 快速处理消息模式。(dvbs调试信号时使用D_TRUE，当退出菜单时恢复D_FALSE)
dvbs调试天线时需要实时显示信号强度与质量，以及及时处理diseqc命令，
在decoder锁频超时的循环里可以调用patch使fman任务处理里的队列里的消息与事件。
* @param fm 前端管理设备句柄
* @param fast	快速模式
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_fman_set_fast_mode(D_HFMan fm, D_Bool fast) D_FUNCPOSTFIT;

/** @brief 设置fman 马达调节模式，此时锁频时不再设定diseqc,由应用单独发命令。
* @param fm 前端管理设备句柄
* @param motor_mode	是否
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_fman_set_motor_mode(D_HFMan fm, D_Bool motor_mode) D_FUNCPOSTFIT;

/** @brief 锁住22k,此时锁频时不再设定22k,由应用单独发命令。
* @param fm 前端管理设备句柄
* @param lock	是否锁住
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_fman_lock_22k_ctrl(D_HFMan fm, D_Bool lock) D_FUNCPOSTFIT;

/** @brief 设置22K开关。(直接调用fend接口)
* @param fm 前端管理设备句柄
* @param on	是否打开
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_fman_set_22k_direct(D_HFMan fm, D_Bool on) D_FUNCPOSTFIT;

/** @brief 通过前端管理器设定前端设备盲扫参数(直接调用fend接口，请谨慎)
* @param fm 前端设备句柄
* @param scantype 盲扫类型
* @param cmd 盲扫命令
* @param fendtype 前端类型
* @param param 前端设备盲扫参数
* @param hq 消息队列
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result
d_fman_blind_set_param_direct (D_HFMan fm, D_FEndBlindCmd cmd, D_FEndParam *re_param,D_FBlindParam *blindparam) D_FUNCPOSTFIT;

/** @brief 通过前端管理器设定前端设备参数(直接调用fend接口)
* @param fm 前端设备句柄
* @param param 前端设备参数
* @param lnb_freq 本振频率
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_fman_set_param_direct(D_HFMan fm, D_FEndParam *param, D_FEndFreq lnb_freq) D_FUNCPOSTFIT;

/** @brief 取得锁定状态。(直接调用fend接口)
* @param fm 前端管理设备句柄
* @return 锁定返回D_TRUE, 不锁定返回D_FALSE
*/
D_Bool d_fman_get_lock_direct(D_HFMan fm) D_FUNCPOSTFIT;

/** @brief 取得前端设备状态。(直接调用fend接口)
* @param fm 前端管理设备句柄
* @param status	状态
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_fman_get_status_direct(D_HFMan fm, D_FEndStatus *status) D_FUNCPOSTFIT;

/** @brief 取得前端设备频谱等详细信息状态。(直接调用fend接口，请谨慎)
* @param fm 前端管理设备句柄
* @param status	状态
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_fman_get_advance_status_direct(D_HFMan fm, D_FEndadvanceStatus *status) D_FUNCPOSTFIT;

/** @brief设定fman挂起或恢复
* @param fm     前端管理设备句柄
* @param suspend   挂起与否
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_fman_set_suspend(D_HFMan fm, D_Bool suspend) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
