/** @file
* @brief 字符编码转换
* @author 龚克
* @date 2005-11-15 龚克: 建立文件
* @date 2013-03-19 lc: 统一平台, 代码整理
*/

#ifndef _D_CONV_CODE_H_
#define _D_CONV_CODE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief 转换utf8编码到gb2312编码*/
D_Size  d_cc_utf8_to_gb2312 (D_U8 *gb2312, D_Size gb_len, D_U8 *utf8, D_Size utf8_len) D_FUNCPOSTFIT;

/** @brief 转换utf16编码到gb2312编码*/
D_Size	d_cc_utf16_to_gb2312 (D_U8 *gb2312, D_Size gb_len, D_U8 *utf16, D_Size utf_len) D_FUNCPOSTFIT;

/** @brief 转换gb2312到utf16*/
D_Size	d_cc_gb2312_to_utf16 (D_U8 *utf16, D_Size utf_len, D_U8 *gb2312, D_Size gb_len) D_FUNCPOSTFIT;

/** @brief 转换gb2312到utf8*/
D_Size  d_cc_gb2312_to_utf8(D_U8 *utf8, D_Size utf_len, D_U8 *gb2312, D_Size gb_len) D_FUNCPOSTFIT;

/** @brief 转换big5编码到gb2312编码*/
D_Size d_cc_big5_to_gb2312 (D_U8 *gb2312, D_Size gb_len, D_U8 *big5, D_Size big5_len) D_FUNCPOSTFIT;

/** @brief 转换syscode到utf16*/
D_Size d_cc_sys_to_utf16(D_U8 *utf16, D_Size utf_len, D_U8 *sys, D_Size sys_len) D_FUNCPOSTFIT;

/** @brief 转换utf16编码到syscode编码*/
D_Size d_cc_utf16_to_sys (D_U8 *sys, D_Size sys_len, D_U8 *utf16, D_Size utf_len) D_FUNCPOSTFIT;

/** @brief 转换syscode到utf8*/
D_Size d_cc_sys_to_utf8(D_U8 *utf8, D_Size utf_len, D_U8 *sys, D_Size sys_len) D_FUNCPOSTFIT;

/** @brief 转换utf8到syscode*/
D_Size d_cc_utf8_to_sys (D_U8 *sys, D_Size sys_len, D_U8 *utf8, D_Size utf8_len) D_FUNCPOSTFIT;

/*字符编码系统初始化*/
D_Result d_cc_open(D_Ptr callback_sys_to_unicode, D_Ptr callback_unicode_to_sys)D_FUNCPOSTFIT;


/** @brief 转换utf16编码到gb2312编码
* @param[in] utf16  unicode数据
* @param[out] gb2312    gb2312数据
* @return   返回gb2312的值的字节数, 0: 说明不是gb2312
*/
D_U32 d_utf16_to_gb2312(D_U8 *gb2312, D_U8 *utf16)D_FUNCPOSTFIT;

/** @brief 转换utf16编码到gb2312编码
* @param[in] c_utf16    unicode编码值
* @return   返回gb2312的值, 0: 说明不是gb2312
*/
D_U16 d_utf16_to_gb2312_code(D_U16 c_utf16)D_FUNCPOSTFIT;

/** @brief 转换gb2312编码到utf16编码
* @param[in] gb2312    gb2312编码串
* @param[in/out] utf16    unicode编码值
* @return   返回gb2312的值, 0: 说明不是gb2312
*/
D_U16 d_gb2312_to_utf16(D_U16 *utf16, D_U8 *gb2312)D_FUNCPOSTFIT;

/** @brief 转换gb2312编码到utf16编码
* @param[in] c_utf16    unicode编码值
* @return   返回gb2312的值, 0: 说明不是gb2312
*/
D_U16 d_gb2312_to_utf16_code(D_U16 c_gb2312)D_FUNCPOSTFIT;

/** @brief 转换utf16编码到gbk编码
* @param[in] utf16  unicode数据
* @param[out] gbk   gbk数据
* @return   返回gbk的值的字节数, 0: 说明不是gbk
*/
D_U32 d_utf16_to_gbk(D_U8 *gbk, D_U8 *utf16)D_FUNCPOSTFIT;

/** @brief 转换utf16编码到gbk编码
* @param[in] c_utf16    unicode编码值
* @return   返回gbk的值, 0: 说明不是gbk
*/
D_U16 d_utf16_to_gbk_code(D_U16 c_utf16)D_FUNCPOSTFIT;

/** @brief 转换gbk编码到utf16编码
* @param[in] gbk    gbk编码串
* @param[in/out] utf16    unicode编码值
* @return   返回gbk的值, 0: 说明不gbk
*/
D_U16 d_gbk_to_utf16(D_U16 *utf16, D_U8 *gbk)D_FUNCPOSTFIT;

/** @brief 转换gbk编码到utf16编码
* @param[in] c_utf16    unicode编码值
* @return   返回gbk的值, 0: 说明不gbk
*/
D_U16 d_gbk_to_utf16_code(D_U16 c_gbk)D_FUNCPOSTFIT;

/** @brief 转换繁体中文big5编码到简体中文gb2312编码*/
int d_big5_to_gb2312(D_U8 *gb2312, D_U8 *big5)D_FUNCPOSTFIT;


/** @brief 遍历检查是否是utf8编码格式，但符合这格式的不一定是utf8，
巧合情况下，2312或unicode也有可能符合这个格式*/
D_Bool d_cc_check_utf8 (D_U8 *buf, D_Size len) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
