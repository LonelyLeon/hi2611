/** @file
* @brief 随机数生成
* @author 龚克
* @date 2005-9-24 龚克: 建立文件
*/

#ifndef _D_RAND_H_
#define _D_RAND_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dDebug.h"

/** @brief 设随机数种子
@param[in] v 种子
*/
void	d_scand (D_U32 v) D_FUNCPOSTFIT;

/** @brief 产生随机数
@return r 随机数
*/
D_U32	d_rand(void) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
