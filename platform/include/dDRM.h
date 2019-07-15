/** @file
* @brief  ���ܺͽ���ģ��
* @author
* @date
*/
#ifndef __D_DRM_H
#define __D_DRM_H

#include "dTypes.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/** @brief drm�ӽ����㷨ѡ��*/
typedef enum
{
    DRM_AES_CBC = 0,
    DRM_AES_CTR,
    DRM_AES_ECB,
    DRM_AES_CFB,
    DRM_AES_OFB,
    DRM_SMS4_CBC,
    DRM_SMS4_CTR,
    DRM_SMS4_ECB,
    DRM_SMS4_CFB,
    DRM_SMS4_OFB,
}D_DrmMode;

/** @brief DRM�豸����*/
typedef struct
{
	D_ID id; /**< �豸ID*/
}D_DrmAttr;

/** @brief ��ȱʡֵ��ʼ��DRM�豸����*/
#define D_DRM_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
	D_MACRO_END

/** @brief DRMģ���ʼ��
* @return  D_OK�ɹ�;����, ʧ��
*/
D_Result d_drm_open(void) D_FUNCPOSTFIT;

/** @brief DRMģ���ͷ�
* @return  D_OK�ɹ�;����, ʧ��
*/
D_Result d_drm_close(void) D_FUNCPOSTFIT;

/** @brief ����һ��DRM�豸
* @param[in] attr	DRM�豸���Խṹָ�룬ΪNULLʱʹ��ȱʡֵ
* @return �ɹ�ʱ����DRM�豸�����ʧ�ܷ���D_INVALID_HANDLE
*/
D_Handle d_drm_create(D_DrmAttr *attr) D_FUNCPOSTFIT;

/** @brief ����һ��DRM�豸
* @param[in] hdrm  DRM�豸���
* @retval D_OK �ͷųɹ�
* @retval D_ERR_INVALID_HANDLE �����Ч
*/
D_Result d_drm_destroy(D_Handle hdrm) D_FUNCPOSTFIT;

/** @brief ����һ��DRM�豸
* @param[in] hdrm  DRM�豸���
* @retval D_OK �����ɹ�, ����豸�Ѿ�������, ��ȴ��豸���ͷ�
* @retval D_ERR_INVALID_HANDLE �����Ч
*/
D_Result d_drm_lock(D_Handle hdrm) D_FUNCPOSTFIT;

/** @brief �ͷ�����һ��DRM�豸
* @param[in] hdrm  DRM�豸���
* @retval D_OK �ɹ�
* @retval D_ERR_INVALID_HANDLE �����Ч
*/
D_Result d_drm_unlock(D_Handle hdrm) D_FUNCPOSTFIT;

/** @brief ���ü��ܻ����ʹ�õ�key
* @param[in] hdrm  DRM�豸���
* @param[in] key  ���ܻ�����õ�key, 128bit
* @param[in] iv  ���ܻ�����õ�iv, 128bit
* @retval D_OK �ɹ�
* @retval D_ERR_INVALID_HANDLE �����Ч
*/
D_Result d_drm_set_key(D_Handle hdrm, const D_U8 *key, const D_U8 *iv) D_FUNCPOSTFIT;

/** @brief ��������
* @param[in] hdrm  DRM�豸���
* @param[in] data_in  �������������, ��ַ8K�ֽڶ���
* @param[in] in_size  ��������ݳ���, 64K����
* @param[out] data_out ���ܺ����������, ��ַ8K�ֽڶ���
* @param[out] out_size ���ܺ���������ݳ���
* @retval D_OK �ɹ�
* @retval D_ERR_INVALID_HANDLE �����Ч
*/
D_Result d_drm_encrypt(D_Handle hdrm, const D_U8 *data_in, D_Size in_size, D_U8 *data_out, D_Size *out_size) D_FUNCPOSTFIT;

/** @brief ��������
* @param[in] hdrm  DRM�豸���
* @param[in] data_in  �������������, ��ַ1024�ֽڶ���
* @param[in] in_size  ��������ݳ���, 64K����
* @param[out] data_out ���ܺ������������, ��ַ1024�ֽڶ���
* @param[out] out_size ���ܺ���������ݳ���
* @retval D_OK �ɹ�
* @retval D_ERR_INVALID_HANDLE �����Ч
*/
D_Result d_drm_decrypt(D_Handle hdrm, const D_U8 *data_in, D_Size in_size, D_U8 *data_out, D_Size *out_size) D_FUNCPOSTFIT;



/** @brief ��������
* @param[in] hdrm  DRM�豸���
* @param[in] data_in  �������������, ��ַ8K�ֽڶ���
* @param[in] in_size  ��������ݳ���, 16����
* @param[out] data_out ���ܺ����������, ��ַ8K�ֽڶ���
* @param[out] out_size ���ܺ���������ݳ���
* @param[in] emode �����㷨ѡ��
* @retval D_OK �ɹ�
* @retval D_ERR_INVALID_HANDLE �����Ч
*/
D_Result d_drm_encrypt_ex(D_Handle hdrm, const D_U8 *data_in, D_Size in_size, D_U8 *data_out, D_Size *out_size, D_DrmMode emode) D_FUNCPOSTFIT;


/** @brief ��������
* @param[in] hdrm  DRM�豸���
* @param[in] data_in  �������������, ��ַ8K�ֽڶ���
* @param[in] in_size  ��������ݳ���, 16����
* @param[out] data_out ���ܺ������������, ��ַ8K�ֽڶ���
* @param[out] out_size ���ܺ���������ݳ���
* @param[in] dmode �����㷨ѡ��
* @retval D_OK �ɹ�
* @retval D_ERR_INVALID_HANDLE �����Ч
*/
D_Result d_drm_decrypt_ex(D_Handle hdrm, const D_U8 *data_in, D_Size in_size, D_U8 *data_out, D_Size *out_size, D_DrmMode dmode) D_FUNCPOSTFIT;



#ifdef  __cplusplus
}
#endif
#endif

