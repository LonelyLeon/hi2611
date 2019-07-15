/** @file
* @brief �����ļ�����
* @author �
* @date 2013-09-16 �: �����ļ�
*/
#ifndef __D_CONFIG_FILE_H
#define __D_CONFIG_FILE_H
#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief �����ļ������ʼ���ṹ */
typedef struct
{
    D_U8 *hw_data; /**< Ӳ���������� */
    D_U16 hw_data_size; /**< Ӳ���������ݴ�С */
    D_U8 *sw_data; /**< ����������� */
    D_U16 sw_data_size; /**< ����������ݴ�С */
}D_ConfigFileOpenParam;

/** @brief �����ļ������ʼ������
* @param[in] OpenParam ��ʼ���ṹ
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_conf_file_open(D_ConfigFileOpenParam *OpenParam) D_FUNCPOSTFIT;

/** @brief �����ļ������ͷ�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_conf_file_close(void) D_FUNCPOSTFIT;

/** @brief �����ļ���������tag
* @param[in] tag ������8λ
* @param[out] length ����tag�غ����ݳ���
* @return �ɹ������غ�����ָ��,ʧ�ܷ���NULL
*/
void* d_conf_file_search_tag(D_U8 tag, D_U16 *length) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif

