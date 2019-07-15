/** @file
* @brief  JD_Port接口
* @author 龚克
* @date 2005-6-4 龚克: 建立文件
*/
#ifndef _D_PORT_H_
#define _D_PORT_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief JD_Port初始化
* @return 操作成功返回D_OK,失败返回D_ERR
*/
D_Result	d_port_open (void) D_FUNCPOSTFIT;

/** @brief 退出JD_Port
* @return 操作成功返回D_OK,失败返回D_ERR
*/
D_Result	d_port_close (void) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
