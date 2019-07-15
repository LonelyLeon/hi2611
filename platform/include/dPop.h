/** @file
* @brief 信息窗口模块内部
* @author 龚克
* @date 2005-9-17 龚克: 建立文件
* @date 2013-05-09 lc: 统一平台, 代码整理
*/

#ifndef _D_POP_MSG_INTERNAL_H_
#define _D_POP_MSG_INTERNAL_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dGUI.h"

#define D_POP_PRIO_MAX			(12)

/** @brief 弹出框加载frame前回调函数类型*/
typedef D_Result (*D_PopShowFuncPtr)(D_U16 prio, D_GUILayer layer, D_Frame *frm);

/** @brief 分配一个指定优先级的弹出式消息结构*/
D_Result d_pop_new (D_U16 prio, D_GUILayer layer, D_Frame *frm, D_PopShowFuncPtr pop_show) D_FUNCPOSTFIT;

/** @brief 释放一个指定优先级的弹出式消息结构*/
D_Result d_pop_free (D_U16 prio) D_FUNCPOSTFIT;

/** @brief 如果新的窗口是最高优先级窗口,显示此窗口*/
D_Result d_pop_show (D_U16 prio) D_FUNCPOSTFIT;

/** @brief 清空所有弹出式消息*/
D_Result d_pop_msg_clear () D_FUNCPOSTFIT;

/** @brief 强制重新显示当前最高优先级pop msg*/
D_Result d_pop_msg_reshow(void) D_FUNCPOSTFIT;

/** @brief 是否允许显示pop msg*/
D_Result d_pop_show_enable(D_Bool enable) D_FUNCPOSTFIT;

/** @brief 是否允许显示pop msg*/
D_Bool d_pop_show_get_enable(void) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
