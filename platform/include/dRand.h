/** @file
* @brief ���������
* @author ����
* @date 2005-9-24 ����: �����ļ�
*/

#ifndef _D_RAND_H_
#define _D_RAND_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dDebug.h"

/** @brief �����������
@param[in] v ����
*/
void	d_scand (D_U32 v) D_FUNCPOSTFIT;

/** @brief ���������
@return r �����
*/
D_U32	d_rand(void) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
