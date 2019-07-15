/** @file
* @brief Ӧ�����õ���һЩ���ýӿں���
* @author ����
* @date 2014-06-20 ����: �����ļ�
*/

#ifndef _D_STB_FUNCTIONS_H_
#define _D_STB_FUNCTIONS_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dGUI.h"

/** @brief �������ݿ��������趨�����������������*/
D_Result p_stb_reset_mute_track_volume( void )D_FUNCPOSTFIT;

/** @brief �������ݿ������趨����״̬*/
D_Result p_stb_reset_mute_status( void )D_FUNCPOSTFIT;

/**@brief ���ռ��С����Ϊ�ַ���*/
D_Result p_unit_converter( D_Double orisize , D_Char * output )D_FUNCPOSTFIT;


/** @brief ����ca�˵�(TV_STB)*/
D_Result p_stb_set_ca_menu(D_GUIMenu *camenu) D_FUNCPOSTFIT;

/** @brief ����ca�˵�(TV)*/
D_Result
p_stb_set_atv_ca_menu(D_GUIMenu *camenu) D_FUNCPOSTFIT;
/** @brief �����л�Դ*/
D_Result p_sys_set_input_mode(D_VidInput lastinput,D_VidInput input) D_FUNCPOSTFIT;

void p_set_ratio_mode(D_U8 mode)D_FUNCPOSTFIT;

/** @brief ȡ���û����õı���ɫ*/
D_U32 p_sys_get_user_background_color(void) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif

