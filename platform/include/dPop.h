/** @file
* @brief ��Ϣ����ģ���ڲ�
* @author ����
* @date 2005-9-17 ����: �����ļ�
* @date 2013-05-09 lc: ͳһƽ̨, ��������
*/

#ifndef _D_POP_MSG_INTERNAL_H_
#define _D_POP_MSG_INTERNAL_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dGUI.h"

#define D_POP_PRIO_MAX			(12)

/** @brief ���������frameǰ�ص���������*/
typedef D_Result (*D_PopShowFuncPtr)(D_U16 prio, D_GUILayer layer, D_Frame *frm);

/** @brief ����һ��ָ�����ȼ��ĵ���ʽ��Ϣ�ṹ*/
D_Result d_pop_new (D_U16 prio, D_GUILayer layer, D_Frame *frm, D_PopShowFuncPtr pop_show) D_FUNCPOSTFIT;

/** @brief �ͷ�һ��ָ�����ȼ��ĵ���ʽ��Ϣ�ṹ*/
D_Result d_pop_free (D_U16 prio) D_FUNCPOSTFIT;

/** @brief ����µĴ�����������ȼ�����,��ʾ�˴���*/
D_Result d_pop_show (D_U16 prio) D_FUNCPOSTFIT;

/** @brief ������е���ʽ��Ϣ*/
D_Result d_pop_msg_clear () D_FUNCPOSTFIT;

/** @brief ǿ��������ʾ��ǰ������ȼ�pop msg*/
D_Result d_pop_msg_reshow(void) D_FUNCPOSTFIT;

/** @brief �Ƿ�������ʾpop msg*/
D_Result d_pop_show_enable(D_Bool enable) D_FUNCPOSTFIT;

/** @brief �Ƿ�������ʾpop msg*/
D_Bool d_pop_show_get_enable(void) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
