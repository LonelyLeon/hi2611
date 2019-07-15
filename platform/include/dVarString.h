/** @file
* @brief 可变字符串存储
* @author 龚克
* @date 2005-9-21 龚克: 建立文件
* @date 2013-03-19 lc: 统一平台, 代码整理
*/
#ifndef _D_VAR_STRING_H_
#define _D_VAR_STRING_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

typedef struct _D_VarString	D_VarString;

/** @brief 初始化字符串结点链表*/
D_Result	d_var_string_open (D_Size node_cnt) D_FUNCPOSTFIT;

/** @brief 退出字符串模块*/
D_Result	d_var_string_close (void) D_FUNCPOSTFIT;

/** @brief 分配并拷贝字符串*/
D_VarString*	d_var_string_set (D_Char *text, D_Size size) D_FUNCPOSTFIT;

/** @brief 取出字符串*/
D_Size		d_var_string_get (D_VarString *str, D_Char *text, D_Size size) D_FUNCPOSTFIT;

/** @brief 释放字符串*/
D_Result	d_var_string_del (D_VarString *str) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
