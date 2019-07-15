/** @file
* @brief 红外唤醒
* @author liuxz
* @date 2015-1-4 liuxz: 建立文件
*/

#ifndef _D_WAKEUP_H_
#define _D_WAKEUP_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dFP.h"


/** @brief 遥控器按键键值*/
typedef D_U32	D_RemoteKey;
typedef enum{
NEC = 1,
BESC,
DONGZHI,
RC_5
}D_RemoteCode;

/** @brief 红外唤醒
* 
* @retval D_OK	初始化成功 
* @retval D_ERR	初始化失败 
*/ 
D_Result d_wakeup_open (void) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
