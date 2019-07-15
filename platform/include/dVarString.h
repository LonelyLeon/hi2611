/** @file
* @brief �ɱ��ַ����洢
* @author ����
* @date 2005-9-21 ����: �����ļ�
* @date 2013-03-19 lc: ͳһƽ̨, ��������
*/
#ifndef _D_VAR_STRING_H_
#define _D_VAR_STRING_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

typedef struct _D_VarString	D_VarString;

/** @brief ��ʼ���ַ����������*/
D_Result	d_var_string_open (D_Size node_cnt) D_FUNCPOSTFIT;

/** @brief �˳��ַ���ģ��*/
D_Result	d_var_string_close (void) D_FUNCPOSTFIT;

/** @brief ���䲢�����ַ���*/
D_VarString*	d_var_string_set (D_Char *text, D_Size size) D_FUNCPOSTFIT;

/** @brief ȡ���ַ���*/
D_Size		d_var_string_get (D_VarString *str, D_Char *text, D_Size size) D_FUNCPOSTFIT;

/** @brief �ͷ��ַ���*/
D_Result	d_var_string_del (D_VarString *str) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
