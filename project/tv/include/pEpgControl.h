/** @file
* @brief EPG����api
* @author �
* @date 2013-08-09 �: �����ļ�
*/
#ifndef __P_EPG_CONTROL_H
#define __P_EPG_CONTROL_H
#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief ��̨����EPG
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result p_epg_start(D_U32 param) D_FUNCPOSTFIT;

/** @brief �رպ�̨EPG
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result p_epg_stop(void) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif

