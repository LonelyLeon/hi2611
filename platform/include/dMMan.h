/** @file
* @brief �ڴ����ģ��
* @author ����
* @date 2005-6-17 ����: �����ļ�
*/

#ifndef _D_MMAN_H_
#define _D_MMAN_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief �ڴ���������*/
typedef D_Handle	D_HMMan;

/** @brief �ڴ�������*/
typedef enum {
	D_MMAN_SIMPLE,	/**< �򵥷�ʽ,���ͷ�*/
	D_MMAN_HEAP,	/**< ֧���ͷ�*/
	D_MMAN_HEAP_OPTIMISE_SPACE, /**< ����ռ��Ż���heap, �����ٶ�*/
} D_MManType;

/** @brief �ڴ�������������� */
typedef struct
{
    D_Ptr block;  /**< �ڴ���ʼ��ַ */
    D_Size size;  /**< �ڴ��С */
    D_Size align;  /**< �ڴ��������С */
    D_MManType type;  /**< �ڴ������� */
}D_MManAttr;

/** @brief �ڴ������������Ϣ*/
typedef struct
{
	D_MManType type;  /**<  �ڴ�������*/
	D_U32 size;  /**< �ڴ������С*/
	D_U32 free_size;  /**< �ɷ����С*/
	D_U32 largest_free_block_size;  /**< �ɷ��������С*/
	D_U32 alloc_blocks;  /**< �ѷ����ڴ�����*/
}D_MManInfo;

/** @brief �ڴ����ϵͳ��ʼ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_mman_open (void) D_FUNCPOSTFIT;

/** @brief �ڴ����ϵͳ�˳�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_mman_close (void) D_FUNCPOSTFIT;

/** @brief ����һ���ڴ������
* @param block	�ڴ���ʼ��ַ
* @param size		�ڴ��С
* @param type		�ڴ�������
* @return �ɹ�ʱ�����ڴ���������,ʧ��ʱ����D_INVALID_HANDLE
*/
D_HMMan		d_mman_create (D_Ptr block, D_Size size, D_MManType type) D_FUNCPOSTFIT;

/** @brief ����һ���ڴ������
* @param attr	�ڴ��������������
* @return �ɹ�ʱ�����ڴ���������,ʧ��ʱ����D_INVALID_HANDLE
*/
D_HMMan		d_mman_create_ex (D_MManAttr *attr) D_FUNCPOSTFIT;

/** @brief �ͷ�һ���ڴ������
* @param hmm	�ڴ���������
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_mman_destroy (D_HMMan hmm) D_FUNCPOSTFIT;

/** @brief ����ڴ��������ȫ���Է���Ŀռ�
* @param hmm	�ڴ���������
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_mman_clear (D_HMMan hmm) D_FUNCPOSTFIT;

/** @brief ͨ���ڴ����������һ���ڴ�
* @param hmm �ڴ���������
* @param size ����ռ��С
* @return �ɹ������ڴ�ָ��,ʧ�ܷ���NULL
*/
D_Ptr		d_mman_alloc (D_HMMan hmm, D_Size size) D_FUNCPOSTFIT;

/** @brief ͨ���ڴ�������ͷ�һ���ڴ�
* @param hmm �ڴ���������
* @param ptr �ͷſռ�ָ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_mman_free (D_HMMan hmm, D_Ptr ptr) D_FUNCPOSTFIT;

/** @brief ͨ���ڴ�����������趨һ���ڴ�Ĵ�С
* @param hmm �ڴ���������
* @param old ������ָ��
* @param size �µ������С
* @return �ɹ������ڴ�ָ��,ʧ�ܷ���NULL
*/
D_Ptr		d_mman_realloc (D_HMMan hmm, D_Ptr old, D_Size size) D_FUNCPOSTFIT;

/** @brief ����ڴ������������Ϣ
* @param hmm �ڴ���������
* @param info �ڴ������������Ϣ�ṹָ��
* @return �ɹ�����D_OK,ʧ�ܷ���errֵ
*/
D_Result	d_mman_get_info(D_HMMan hmm, D_MManInfo *info);

#ifdef  __cplusplus
}
#endif

#endif
