/**@defgroup plogo logo�͹��ģ��
*@{*/

/** @file
* @brief ����logo��������
* @author qiny
* @date 2014-02-26 qiny: �����ļ�
*/
#include "stdio.h"
#include "dTypes.h"

typedef void (*PLOGO_CALLBACK)(D_U32 event);

/** @brief ��������logo����������
* @return def_time Ĭ��һ֡����ʱ��
* @return �������
*/
D_Result 
p_power_on_logo_play_start(D_Time def_time)D_FUNCPOSTFIT;

/** @brief ����logo����������
* @return �������
*/
D_Result 
p_power_on_logo_play_end(void)D_FUNCPOSTFIT;

/* @}*/

