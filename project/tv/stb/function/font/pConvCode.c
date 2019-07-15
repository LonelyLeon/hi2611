/**@defgroup cc 字符编码转换
*@{*/
/** @file
* @brief 字符编码转换
* @author 覃宜
* @date 2014-5-14 覃宜: 建立文件
* 当有多语言时，或是有自定义的私有内码(syscode)与unicode码之间的转换时，
* 需要在sys_to_utf16 与 utf16_to_sys里进行修改，进行编码转换。
*/
#include "pConvCode.h"

/** @brief 转换syscode到utf16*/
static D_Size
sys_to_utf16(D_U8 *utf16, D_Size utf_len, D_U8 *sys, D_Size sys_len) D_FUNCPOSTFIT
{
	return d_cc_gb2312_to_utf16(utf16, utf_len, sys, sys_len);
}

/** @brief 转换utf16到syscode*/
static D_Size
utf16_to_sys(D_U8 *sys, D_Size sys_len, D_U8 *utf16, D_Size utf_len) D_FUNCPOSTFIT
{
	return d_cc_utf16_to_gb2312(sys, sys_len, utf16, utf_len);
}

/** @brief 转换utf8到syscode, 自动对转换后的字符串结尾添加结束符"\0" */
D_Size
p_cc_utf8_to_sys(D_U8 *sys, D_Size sys_len, D_U8 *utf8, D_Size utf8_len) D_FUNCPOSTFIT
{
    D_Size len;
    len = d_cc_utf8_to_sys (sys, sys_len, utf8, utf8_len);
    len = D_MIN(len, sys_len - 1);
    sys[len] = 0;
    return len;
}

/** @brief 转换utf16到syscode, 自动对转换后的字符串结尾添加结束符"\0" */
D_Size
p_cc_utf16_to_sys(D_U8 *sys, D_Size sys_len, D_U8 *utf16, D_Size utf16_len) D_FUNCPOSTFIT
{
    D_Size len;
    len = d_cc_utf16_to_sys (sys, sys_len, utf16, utf16_len);
    len = D_MIN(len, sys_len - 1);
    sys[len] = 0;
    return len;
}

/** @brief 字符编码系统初始化, 注册函数*/
D_Result 
p_cc_open(void) D_FUNCPOSTFIT
{
	d_cc_open((D_Ptr)sys_to_utf16, (D_Ptr)utf16_to_sys);
	return D_OK;
}

/**@}*/