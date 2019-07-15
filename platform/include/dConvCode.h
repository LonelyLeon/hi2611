/** @file
* @brief �ַ�����ת��
* @author ����
* @date 2005-11-15 ����: �����ļ�
* @date 2013-03-19 lc: ͳһƽ̨, ��������
*/

#ifndef _D_CONV_CODE_H_
#define _D_CONV_CODE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief ת��utf8���뵽gb2312����*/
D_Size  d_cc_utf8_to_gb2312 (D_U8 *gb2312, D_Size gb_len, D_U8 *utf8, D_Size utf8_len) D_FUNCPOSTFIT;

/** @brief ת��utf16���뵽gb2312����*/
D_Size	d_cc_utf16_to_gb2312 (D_U8 *gb2312, D_Size gb_len, D_U8 *utf16, D_Size utf_len) D_FUNCPOSTFIT;

/** @brief ת��gb2312��utf16*/
D_Size	d_cc_gb2312_to_utf16 (D_U8 *utf16, D_Size utf_len, D_U8 *gb2312, D_Size gb_len) D_FUNCPOSTFIT;

/** @brief ת��gb2312��utf8*/
D_Size  d_cc_gb2312_to_utf8(D_U8 *utf8, D_Size utf_len, D_U8 *gb2312, D_Size gb_len) D_FUNCPOSTFIT;

/** @brief ת��big5���뵽gb2312����*/
D_Size d_cc_big5_to_gb2312 (D_U8 *gb2312, D_Size gb_len, D_U8 *big5, D_Size big5_len) D_FUNCPOSTFIT;

/** @brief ת��syscode��utf16*/
D_Size d_cc_sys_to_utf16(D_U8 *utf16, D_Size utf_len, D_U8 *sys, D_Size sys_len) D_FUNCPOSTFIT;

/** @brief ת��utf16���뵽syscode����*/
D_Size d_cc_utf16_to_sys (D_U8 *sys, D_Size sys_len, D_U8 *utf16, D_Size utf_len) D_FUNCPOSTFIT;

/** @brief ת��syscode��utf8*/
D_Size d_cc_sys_to_utf8(D_U8 *utf8, D_Size utf_len, D_U8 *sys, D_Size sys_len) D_FUNCPOSTFIT;

/** @brief ת��utf8��syscode*/
D_Size d_cc_utf8_to_sys (D_U8 *sys, D_Size sys_len, D_U8 *utf8, D_Size utf8_len) D_FUNCPOSTFIT;

/*�ַ�����ϵͳ��ʼ��*/
D_Result d_cc_open(D_Ptr callback_sys_to_unicode, D_Ptr callback_unicode_to_sys)D_FUNCPOSTFIT;


/** @brief ת��utf16���뵽gb2312����
* @param[in] utf16  unicode����
* @param[out] gb2312    gb2312����
* @return   ����gb2312��ֵ���ֽ���, 0: ˵������gb2312
*/
D_U32 d_utf16_to_gb2312(D_U8 *gb2312, D_U8 *utf16)D_FUNCPOSTFIT;

/** @brief ת��utf16���뵽gb2312����
* @param[in] c_utf16    unicode����ֵ
* @return   ����gb2312��ֵ, 0: ˵������gb2312
*/
D_U16 d_utf16_to_gb2312_code(D_U16 c_utf16)D_FUNCPOSTFIT;

/** @brief ת��gb2312���뵽utf16����
* @param[in] gb2312    gb2312���봮
* @param[in/out] utf16    unicode����ֵ
* @return   ����gb2312��ֵ, 0: ˵������gb2312
*/
D_U16 d_gb2312_to_utf16(D_U16 *utf16, D_U8 *gb2312)D_FUNCPOSTFIT;

/** @brief ת��gb2312���뵽utf16����
* @param[in] c_utf16    unicode����ֵ
* @return   ����gb2312��ֵ, 0: ˵������gb2312
*/
D_U16 d_gb2312_to_utf16_code(D_U16 c_gb2312)D_FUNCPOSTFIT;

/** @brief ת��utf16���뵽gbk����
* @param[in] utf16  unicode����
* @param[out] gbk   gbk����
* @return   ����gbk��ֵ���ֽ���, 0: ˵������gbk
*/
D_U32 d_utf16_to_gbk(D_U8 *gbk, D_U8 *utf16)D_FUNCPOSTFIT;

/** @brief ת��utf16���뵽gbk����
* @param[in] c_utf16    unicode����ֵ
* @return   ����gbk��ֵ, 0: ˵������gbk
*/
D_U16 d_utf16_to_gbk_code(D_U16 c_utf16)D_FUNCPOSTFIT;

/** @brief ת��gbk���뵽utf16����
* @param[in] gbk    gbk���봮
* @param[in/out] utf16    unicode����ֵ
* @return   ����gbk��ֵ, 0: ˵����gbk
*/
D_U16 d_gbk_to_utf16(D_U16 *utf16, D_U8 *gbk)D_FUNCPOSTFIT;

/** @brief ת��gbk���뵽utf16����
* @param[in] c_utf16    unicode����ֵ
* @return   ����gbk��ֵ, 0: ˵����gbk
*/
D_U16 d_gbk_to_utf16_code(D_U16 c_gbk)D_FUNCPOSTFIT;

/** @brief ת����������big5���뵽��������gb2312����*/
int d_big5_to_gb2312(D_U8 *gb2312, D_U8 *big5)D_FUNCPOSTFIT;


/** @brief ��������Ƿ���utf8�����ʽ�����������ʽ�Ĳ�һ����utf8��
�ɺ�����£�2312��unicodeҲ�п��ܷ��������ʽ*/
D_Bool d_cc_check_utf8 (D_U8 *buf, D_Size len) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
