/** @file
* @brief  解密和解密模块
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

/** @brief drm加解密算法选择*/
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

/** @brief DRM设备属性*/
typedef struct
{
	D_ID id; /**< 设备ID*/
}D_DrmAttr;

/** @brief 按缺省值初始化DRM设备参数*/
#define D_DRM_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
	D_MACRO_END

/** @brief DRM模块初始化
* @return  D_OK成功;其它, 失败
*/
D_Result d_drm_open(void) D_FUNCPOSTFIT;

/** @brief DRM模块释放
* @return  D_OK成功;其它, 失败
*/
D_Result d_drm_close(void) D_FUNCPOSTFIT;

/** @brief 创建一个DRM设备
* @param[in] attr	DRM设备属性结构指针，为NULL时使用缺省值
* @return 成功时返回DRM设备句柄，失败返回D_INVALID_HANDLE
*/
D_Handle d_drm_create(D_DrmAttr *attr) D_FUNCPOSTFIT;

/** @brief 销毁一个DRM设备
* @param[in] hdrm  DRM设备句柄
* @retval D_OK 释放成功
* @retval D_ERR_INVALID_HANDLE 句柄无效
*/
D_Result d_drm_destroy(D_Handle hdrm) D_FUNCPOSTFIT;

/** @brief 锁定一个DRM设备
* @param[in] hdrm  DRM设备句柄
* @retval D_OK 锁定成功, 如果设备已经被锁定, 则等待设备被释放
* @retval D_ERR_INVALID_HANDLE 句柄无效
*/
D_Result d_drm_lock(D_Handle hdrm) D_FUNCPOSTFIT;

/** @brief 释放锁定一个DRM设备
* @param[in] hdrm  DRM设备句柄
* @retval D_OK 成功
* @retval D_ERR_INVALID_HANDLE 句柄无效
*/
D_Result d_drm_unlock(D_Handle hdrm) D_FUNCPOSTFIT;

/** @brief 设置加密或解密使用的key
* @param[in] hdrm  DRM设备句柄
* @param[in] key  加密或解密用的key, 128bit
* @param[in] iv  加密或解密用的iv, 128bit
* @retval D_OK 成功
* @retval D_ERR_INVALID_HANDLE 句柄无效
*/
D_Result d_drm_set_key(D_Handle hdrm, const D_U8 *key, const D_U8 *iv) D_FUNCPOSTFIT;

/** @brief 加密数据
* @param[in] hdrm  DRM设备句柄
* @param[in] data_in  输入的明文数据, 地址8K字节对齐
* @param[in] in_size  输入的数据长度, 64K对齐
* @param[out] data_out 加密后的密文数据, 地址8K字节对齐
* @param[out] out_size 加密后的密文数据长度
* @retval D_OK 成功
* @retval D_ERR_INVALID_HANDLE 句柄无效
*/
D_Result d_drm_encrypt(D_Handle hdrm, const D_U8 *data_in, D_Size in_size, D_U8 *data_out, D_Size *out_size) D_FUNCPOSTFIT;

/** @brief 解密数据
* @param[in] hdrm  DRM设备句柄
* @param[in] data_in  输入的密文数据, 地址1024字节对齐
* @param[in] in_size  输入的数据长度, 64K对齐
* @param[out] data_out 解密后的明文文数据, 地址1024字节对齐
* @param[out] out_size 解密后的明文数据长度
* @retval D_OK 成功
* @retval D_ERR_INVALID_HANDLE 句柄无效
*/
D_Result d_drm_decrypt(D_Handle hdrm, const D_U8 *data_in, D_Size in_size, D_U8 *data_out, D_Size *out_size) D_FUNCPOSTFIT;



/** @brief 加密数据
* @param[in] hdrm  DRM设备句柄
* @param[in] data_in  输入的明文数据, 地址8K字节对齐
* @param[in] in_size  输入的数据长度, 16对齐
* @param[out] data_out 加密后的密文数据, 地址8K字节对齐
* @param[out] out_size 加密后的密文数据长度
* @param[in] emode 加密算法选择
* @retval D_OK 成功
* @retval D_ERR_INVALID_HANDLE 句柄无效
*/
D_Result d_drm_encrypt_ex(D_Handle hdrm, const D_U8 *data_in, D_Size in_size, D_U8 *data_out, D_Size *out_size, D_DrmMode emode) D_FUNCPOSTFIT;


/** @brief 解密数据
* @param[in] hdrm  DRM设备句柄
* @param[in] data_in  输入的密文数据, 地址8K字节对齐
* @param[in] in_size  输入的数据长度, 16对齐
* @param[out] data_out 解密后的明文文数据, 地址8K字节对齐
* @param[out] out_size 解密后的明文数据长度
* @param[in] dmode 解密算法选择
* @retval D_OK 成功
* @retval D_ERR_INVALID_HANDLE 句柄无效
*/
D_Result d_drm_decrypt_ex(D_Handle hdrm, const D_U8 *data_in, D_Size in_size, D_U8 *data_out, D_Size *out_size, D_DrmMode dmode) D_FUNCPOSTFIT;



#ifdef  __cplusplus
}
#endif
#endif

