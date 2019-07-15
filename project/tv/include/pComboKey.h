/**@defgroup stb ��ϼ����� 
*@{*/
/** @file
* @brief ��ϼ����� 
* @author ��ΰ��
* @date 2013-09-06 ��ΰ��: �����ļ�
*/

#ifndef _P_COMBO_KEY_H_
#define _P_COMBO_KEY_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief ������ϼ���Ŀ�����м�ֵ����ʼ����ϼ�����
* @param[in] key_seq ��ϼ����м�ֵ��ָ��
* @param[in] len ��ϼ���Ŀ
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result p_combo_key_seq_init(D_U8 *key_seq, D_U8 len) D_FUNCPOSTFIT;
D_Result p_combo_key_seq_init1(D_U8 *key_seq, D_U8 len) D_FUNCPOSTFIT;

/** @brief ע����ϼ����������Դ
*/
void p_combo_key_seq_dinit(void) D_FUNCPOSTFIT;
void p_combo_key_seq_dinit1(void) D_FUNCPOSTFIT;

/** @brief ������ϼ�
* @param[in] key ��ϼ�����ö��ֵ
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result p_combo_key_input(D_U8 key) D_FUNCPOSTFIT;
D_Result p_combo_key_input1(D_U8 key) D_FUNCPOSTFIT;


#ifdef  __cplusplus
}
#endif

#endif

/**@}*/
