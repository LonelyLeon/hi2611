/**@defgroup cc 字符编码转换
*@{*/
/** @file
* @brief 字符编码转换
* @author 覃宜
* @date 2014-5-14 覃宜: 建立文件
*/

#ifndef _D_P_CONV_CODE_H_
#define _D_P_CONV_CODE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dConvCode.h"

/** @brief 转换utf8到syscode, 自动对转换后的字符串结尾添加结束符"\0" */
D_Size p_cc_utf8_to_sys(D_U8 *sys, D_Size sys_len, D_U8 *utf8, D_Size utf8_len) D_FUNCPOSTFIT;

/** @brief 转换utf16到syscode, 自动对转换后的字符串结尾添加结束符"\0" */
D_Size p_cc_utf16_to_sys(D_U8 *sys, D_Size sys_len, D_U8 *utf16, D_Size utf16_len) D_FUNCPOSTFIT;

/** @brief 字符编码系统初始化, 注册函数*/
D_Result p_cc_open(void) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
