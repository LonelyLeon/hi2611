/** @file
* @brief CRCУ��
* @author �
* @date 2013-07-22 lc: �����ļ�
*/
#ifndef __D_CRC_H
#define __D_CRC_H
#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief crc-32У�麯��
* @param[in] crc32 ��ʼcrcֵ
* @param[in] data ҪУ����ֶ�
* @param[in] size �ֶδ�С
* @return crc У����
*/
D_U32 d_crc_compute_32_ex(D_U32 crc32, D_U8 *data, D_U32 size) D_FUNCPOSTFIT;

/** @brief crc-32У�麯��
* @param[in] data ҪУ����ֶ�
* @param[in] size �ֶδ�С
* @return crc У����
*/
#define d_crc_compute_32(_d, _s)    d_crc_compute_32_ex((D_U32)-1, (_d), (_s))

/** @brief crc-9У�麯��
* @param[in] buf ҪУ����ֶ�
* @param[in] size �ֶδ�С
* @return crc У����
*/
D_U8 d_crc_compute_8(D_U8 *buf, D_U32 size) D_FUNCPOSTFIT;

/** @brief crc-16-CCITTУ�麯��
* @param[in] data ҪУ����ֶ�
* @param[in] size �ֶδ�С
* @return crc У����
*/
D_U16 d_crc_compute_16_ccitt(D_U8 *buf, D_U32 size) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif

