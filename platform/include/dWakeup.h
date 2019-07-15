/** @file
* @brief ���⻽��
* @author liuxz
* @date 2015-1-4 liuxz: �����ļ�
*/

#ifndef _D_WAKEUP_H_
#define _D_WAKEUP_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dFP.h"


/** @brief ң����������ֵ*/
typedef D_U32	D_RemoteKey;
typedef enum{
NEC = 1,
BESC,
DONGZHI,
RC_5
}D_RemoteCode;

/** @brief ���⻽��
* 
* @retval D_OK	��ʼ���ɹ� 
* @retval D_ERR	��ʼ��ʧ�� 
*/ 
D_Result d_wakeup_open (void) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
