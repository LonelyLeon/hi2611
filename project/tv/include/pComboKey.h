/**@defgroup stb 组合键功能 
*@{*/
/** @file
* @brief 组合键功能 
* @author 刘伟峰
* @date 2013-09-06 刘伟峰: 建立文件
*/

#ifndef _P_COMBO_KEY_H_
#define _P_COMBO_KEY_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief 设置组合键数目、序列键值及初始化组合键缓存
* @param[in] key_seq 组合键序列键值的指针
* @param[in] len 组合键数目
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result p_combo_key_seq_init(D_U8 *key_seq, D_U8 len) D_FUNCPOSTFIT;
D_Result p_combo_key_seq_init1(D_U8 *key_seq, D_U8 len) D_FUNCPOSTFIT;

/** @brief 注销组合键所申请的资源
*/
void p_combo_key_seq_dinit(void) D_FUNCPOSTFIT;
void p_combo_key_seq_dinit1(void) D_FUNCPOSTFIT;

/** @brief 输入组合键
* @param[in] key 组合键按键枚举值
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result p_combo_key_input(D_U8 key) D_FUNCPOSTFIT;
D_Result p_combo_key_input1(D_U8 key) D_FUNCPOSTFIT;


#ifdef  __cplusplus
}
#endif

#endif

/**@}*/
