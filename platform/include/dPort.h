/** @file
* @brief  JD_Port�ӿ�
* @author ����
* @date 2005-6-4 ����: �����ļ�
*/
#ifndef _D_PORT_H_
#define _D_PORT_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief JD_Port��ʼ��
* @return �����ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_port_open (void) D_FUNCPOSTFIT;

/** @brief �˳�JD_Port
* @return �����ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_port_close (void) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
