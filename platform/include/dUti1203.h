/** @file
* @brief uti1203�豸����
* @author gaozh
* @date 2013-11-20 gaozh: �����ļ�
*/

#ifndef _D_UTI1203_H_
#define _D_UTI1203_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dIO.h"

/** @brief uti1203�豸��ʼ���ṹ */
typedef struct
{
    D_GPIO_PortBit reset;
}D_Uti1203OpenParam;


D_Result d_uti1203_open_ex (void) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif



