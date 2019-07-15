/**@defgroup cc �ַ�����ת��
*@{*/
/** @file
* @brief �ַ�����ת��
* @author ����
* @date 2014-5-14 ����: �����ļ�
* ���ж�����ʱ���������Զ����˽������(syscode)��unicode��֮���ת��ʱ��
* ��Ҫ��sys_to_utf16 �� utf16_to_sys������޸ģ����б���ת����
*/
#include "pConvCode.h"

/** @brief ת��syscode��utf16*/
static D_Size
sys_to_utf16(D_U8 *utf16, D_Size utf_len, D_U8 *sys, D_Size sys_len) D_FUNCPOSTFIT
{
	return d_cc_gb2312_to_utf16(utf16, utf_len, sys, sys_len);
}

/** @brief ת��utf16��syscode*/
static D_Size
utf16_to_sys(D_U8 *sys, D_Size sys_len, D_U8 *utf16, D_Size utf_len) D_FUNCPOSTFIT
{
	return d_cc_utf16_to_gb2312(sys, sys_len, utf16, utf_len);
}

/** @brief ת��utf8��syscode, �Զ���ת������ַ�����β��ӽ�����"\0" */
D_Size
p_cc_utf8_to_sys(D_U8 *sys, D_Size sys_len, D_U8 *utf8, D_Size utf8_len) D_FUNCPOSTFIT
{
    D_Size len;
    len = d_cc_utf8_to_sys (sys, sys_len, utf8, utf8_len);
    len = D_MIN(len, sys_len - 1);
    sys[len] = 0;
    return len;
}

/** @brief ת��utf16��syscode, �Զ���ת������ַ�����β��ӽ�����"\0" */
D_Size
p_cc_utf16_to_sys(D_U8 *sys, D_Size sys_len, D_U8 *utf16, D_Size utf16_len) D_FUNCPOSTFIT
{
    D_Size len;
    len = d_cc_utf16_to_sys (sys, sys_len, utf16, utf16_len);
    len = D_MIN(len, sys_len - 1);
    sys[len] = 0;
    return len;
}

/** @brief �ַ�����ϵͳ��ʼ��, ע�ắ��*/
D_Result 
p_cc_open(void) D_FUNCPOSTFIT
{
	d_cc_open((D_Ptr)sys_to_utf16, (D_Ptr)utf16_to_sys);
	return D_OK;
}

/**@}*/