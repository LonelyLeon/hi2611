/** @file
* @brief Sdk
*
* @author �
* @date 2013-07-10 �: �����ļ�
*/
#ifndef __STB_SDK_H
#define __STB_SDK_H
#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dGDev.h"
#include "dGraph.h"
#include "dTV.h"
#include "dFP.h"
#include "dPowerOff.h"

extern D_HTV g_htv; 

D_Result p_port_init(void) D_FUNCPOSTFIT;
D_Result p_auxi_init(void) D_FUNCPOSTFIT;
D_Result p_gui_init(void) D_FUNCPOSTFIT;
D_Result p_cas_init(void) D_FUNCPOSTFIT;
D_Result p_tv_init(void) D_FUNCPOSTFIT;
D_Result p_fp_init(void) D_FUNCPOSTFIT;

D_HGDev p_gui_get_hgdev(void) D_FUNCPOSTFIT;
D_Result p_gui_set_format(D_VidFormat fmt) D_FUNCPOSTFIT;
D_GSurface *p_gui_get_dev_surface(void) D_FUNCPOSTFIT;

/** @brief ͨ��ң����ӳ��ֵ��ȡ��Ӧ���û���ͼ�ֵ)
* @param[in] key ң����ӳ��ֵ
* @param[in] remote_size  ��ȡ��ң������ֵ����
* @param[out] key_buf  ��ȡ��ֵ���û�������
* @retval ��ȡ��ң����ֵ����
*/
D_U8 d_get_remote_key(D_KeyCode key,P_POWERKEY* key_buf, D_U8 remote_size)D_FUNCPOSTFIT;

/** @brief �趨���ң����ʹ�����
* @param[in] enable ʹ�����
* @retval D_OK
*/
D_Result p_fp_set_enable(D_Bool enable) D_FUNCPOSTFIT;

/** @brief ȡ�õ�ǰ�İ���
* @param[in] param ����
* @retval D_OK
*/
D_KeyCode
p_fp_get_curr_key(D_U32 param) D_FUNCPOSTFIT;

/** @brief �趨���ң�������˵İ���ֵ�б�(�б�֮��ļ�ֵ��Ч)
* @param[in] filter_keys ���˼�ֵ���ݶ����ɹ���16������
* @param[in] keys_cnt ���˼�ֵ����Ŀ
(�ݶ����Ϊ16����Ϊ(D_U16)-1 ��0xfffffʱ˵��ȡ�����˲���)
* @retval D_OK
*/
D_Result p_fp_set_filter_keys(D_KeyCode *filter_keys, D_U16 keys_cnt) D_FUNCPOSTFIT;

/*���ݵ�ǰ��ʽ�Զ�ƥ��С��������*/
D_Result p_gui_auto_match_window_format(D_Coord* x, D_Coord* y, D_Coord* w, D_Coord* h)D_FUNCPOSTFIT;

/** @brief ������Ƶ����ɫ�������������ȣ���project��װΪ����Ӿ���������
direct ���������ã����Ǹ���osd���»���ʱ������
*/
D_Result p_av_set_vid_background(D_HAV hav, D_VidBackGroundColor_t BackGround, D_Bool direct)D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif

