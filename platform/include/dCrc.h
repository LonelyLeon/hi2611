/** @file
* @brief CRC校验
* @author 李臣
* @date 2013-07-22 lc: 建立文件
*/
#ifndef __D_CRC_H
#define __D_CRC_H
#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief crc-32校验函数
* @param[in] crc32 初始crc值
* @param[in] data 要校验的字段
* @param[in] size 字段大小
* @return crc 校验结果
*/
D_U32 d_crc_compute_32_ex(D_U32 crc32, D_U8 *data, D_U32 size) D_FUNCPOSTFIT;

/** @brief crc-32校验函数
* @param[in] data 要校验的字段
* @param[in] size 字段大小
* @return crc 校验结果
*/
#define d_crc_compute_32(_d, _s)    d_crc_compute_32_ex((D_U32)-1, (_d), (_s))

/** @brief crc-9校验函数
* @param[in] buf 要校验的字段
* @param[in] size 字段大小
* @return crc 校验结果
*/
D_U8 d_crc_compute_8(D_U8 *buf, D_U32 size) D_FUNCPOSTFIT;

/** @brief crc-16-CCITT校验函数
* @param[in] data 要校验的字段
* @param[in] size 字段大小
* @return crc 校验结果
*/
D_U16 d_crc_compute_16_ccitt(D_U8 *buf, D_U32 size) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif

