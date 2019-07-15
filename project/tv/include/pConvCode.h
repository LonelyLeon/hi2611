/**@defgroup cc �ַ�����ת��
*@{*/
/** @file
* @brief �ַ�����ת��
* @author ����
* @date 2014-5-14 ����: �����ļ�
*/

#ifndef _D_P_CONV_CODE_H_
#define _D_P_CONV_CODE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dConvCode.h"

/** @brief ת��utf8��syscode, �Զ���ת������ַ�����β��ӽ�����"\0" */
D_Size p_cc_utf8_to_sys(D_U8 *sys, D_Size sys_len, D_U8 *utf8, D_Size utf8_len) D_FUNCPOSTFIT;

/** @brief ת��utf16��syscode, �Զ���ת������ַ�����β��ӽ�����"\0" */
D_Size p_cc_utf16_to_sys(D_U8 *sys, D_Size sys_len, D_U8 *utf16, D_Size utf16_len) D_FUNCPOSTFIT;

/** @brief �ַ�����ϵͳ��ʼ��, ע�ắ��*/
D_Result p_cc_open(void) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
