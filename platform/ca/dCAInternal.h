/** @file
* @brief CA模块内部接口
* @author 龚克
* @date 2005-9-8 龚克: 建立文件
*/

#ifndef _D_CA_INTERNAL_H_
#define _D_CA_INTERNAL_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dCA.h"
#include "dSCI.h"
#include "dDemux.h"
#include "dTimer.h"

/** @brief CA的智能卡句柄*/
extern D_HSCI	ca_hsci;

/** @brief CA模块初始化*/
D_Result	ca_init (void) D_FUNCPOSTFIT;

/** @brief CA模块反初始化*/
D_Result	ca_deinit (void) D_FUNCPOSTFIT;

/** @brief 通知CA模块智能卡插入*/
D_Result	ca_card_in (void) D_FUNCPOSTFIT;

/** @brief 通知CA模块智能卡拔出*/
D_Result	ca_card_out (void) D_FUNCPOSTFIT;

/** @brief 通知CA系统开始分析一个TS流中的用户授权数据*/
D_Result	ca_start_ts (D_CATSParam *param) D_FUNCPOSTFIT;

/** @brief 通知CA系统停止分析一个TS流中的用户授权数据*/
D_Result	ca_stop_ts (D_DBTSID db_ts_id) D_FUNCPOSTFIT;

/** @brief 通知CA系统开始分析一个服务的用户控制数据*/
D_Result	ca_start_srv (D_CASrvParam *param) D_FUNCPOSTFIT;

/** @brief 通知CA系统停止分析一个服务的用户控制数据*/
D_Result	ca_stop_srv (D_DBSrvID db_srv_id) D_FUNCPOSTFIT;

/** @brief 在GUI中根据事件更新显示*/
//D_Result	ca_gui_solve_evt (D_CAEventType type, D_Ptr param) D_FUNCPOSTFIT;

/** @brief 收到Demux数据*/
D_Result	ca_demux_data (D_HDemux hdemux, D_U8 *buf, D_Size size) D_FUNCPOSTFIT;

/** @brief 定时器处理*/
D_Result	ca_on_timer (D_HTimer htimer) D_FUNCPOSTFIT;

/** @brief 产生CA事件，通知用户回调*/
D_Result	ca_event (D_CAEventType type, D_Ptr param) D_FUNCPOSTFIT;

/** @brief 获取当前已编译CA的*/
D_Result    ca_complied (D_U32* param) D_FUNCPOSTFIT;

/** @brief 获取CA卡ID*/
//D_Result	ca_card_id (D_U32 *id) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
