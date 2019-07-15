/** @file
* @brief ͼ�����������
* @author hegx
* @date 2005-6-8 hegx: �����ļ�
*/
#ifndef __DVIPPORTING_H
#define __DVIPPORTING_H

#include "dTypes.h"
#include "dAV.h"

#ifdef __cplusplus
extern "C" {
#endif


/** @brief  �����趨
* @param parm
*/
void d_vip_setBrightness(D_U8 val, D_U8* param)D_FUNCPOSTFIT;

/** @brief ɫ�ȵ���
* @param parm
*/
void d_vip_setSaturation(D_U8 val, D_U8* param)D_FUNCPOSTFIT;

/** @brief ɫ������
* @param parm
*/
void d_vip_setHue(D_U8 val, D_U8* param)D_FUNCPOSTFIT;

/** @brief ��ȵ���
* @param parm
*/
void d_vip_setSharpness(D_U8 val, D_U8* param)D_FUNCPOSTFIT;


/** @brief �Աȶ�
* @param parm
*/
void d_vip_setConstrast(D_U8 val, D_U8* param)D_FUNCPOSTFIT;

/** @brief ɫ�²����趨
* @param parm
*/
void d_vip_setTemperature(D_U32 input, D_U8* param,D_U8* csc_param)D_FUNCPOSTFIT;
/** @brief
* @param parm
*/
void d_vip_setBldim(D_U8* param,D_U8 backlight)D_FUNCPOSTFIT;

/** @brief
* @param parm
*/
void d_vip_setNr(D_U8* param)D_FUNCPOSTFIT;

void d_vip_setNr_Prog(D_U8 level)D_FUNCPOSTFIT;

/** @brief
* @param parm
*/
void d_vip_setDifm(D_U8* param)D_FUNCPOSTFIT;

/** @brief
* @param parm
*/
void d_vip_setDe(D_U8* param)D_FUNCPOSTFIT;

/** @brief
* @param parm
*/
void d_vip_setCe(D_U8* param)D_FUNCPOSTFIT;

/** @brief
* @param parm
*/
void d_vip_setAse(D_U8* param)D_FUNCPOSTFIT;

/** @brief
* @param parm
*/
void d_vip_setFtc(D_U8* param)D_FUNCPOSTFIT;

/** @brief
* @param parm
*/
void d_vip_setIcm(D_U8* param)D_FUNCPOSTFIT;

/** @brief
* @param parm
*/
void d_vip_setGamma(D_U8* param)D_FUNCPOSTFIT;
void d_vip_setDce(D_U8* param)D_FUNCPOSTFIT;

void d_vip_setChroma(D_U8* param)D_FUNCPOSTFIT;

/** @brief
* @param parm
*/
void d_vip_setGamma_Table(D_U8 nChannel, D_U8 nIdx, D_U16 nValue)D_FUNCPOSTFIT;
D_U16 d_vip_getGamma_Table(D_U8 nChannel, D_U8 nIdx)D_FUNCPOSTFIT;

/** @brief
* @param parm
*/
void d_vip_setComb(D_U8* param)D_FUNCPOSTFIT;

/** @brief ��ģ��
* @param parm
*/
void d_vip_Set_VE(D_U8* param)D_FUNCPOSTFIT;

void d_vip_Set_CM(D_U8* param)D_FUNCPOSTFIT;
/** @brief
* @param parm
*/
void d_vip_setComp(D_U8* param)D_FUNCPOSTFIT;
/** @brief
* @param parm
*/
void d_vip_setAdc(D_U8* param)D_FUNCPOSTFIT;

/** @brief ����չƵ
* @param parm
*/
void d_miu_Set_Sscg(D_U8 en,D_U8 mode,D_Float sscg_span , D_Float ssc_range)D_FUNCPOSTFIT;

/** @brief ����չƵ
* @param parm
*/
void d_lvds_Set_Sscg(D_U8 en,D_U8 mode,D_Float sscg_span , D_Float ssc_range)D_FUNCPOSTFIT;

/** @brief �����ϻ�ģʽ
* @param parm
*/
void d_lvds_Set_Aging(D_U8 en,D_U8 col_r,D_U8 col_g,D_U8 col_b)D_FUNCPOSTFIT;

D_Bool d_vip_AutoADC(D_U8 *param,D_U8 *compparam)D_FUNCPOSTFIT;
/** @brief ������ڵײ㲥��״̬�������Ƿ��ʺ����Զ��������
* @param parm
*/
D_Result d_vip_get_play_status(D_U8 mode)D_FUNCPOSTFIT;


void d_vip_set_PictureMode(D_U8 *pic_mode_set)D_FUNCPOSTFIT;

void d_vip_Set_Config(D_U8 *param)D_FUNCPOSTFIT;

void d_vip_Set_Ycclip(D_U8 *param)D_FUNCPOSTFIT;


// ���ϲ�����ICM/FCC��ز���
void d_vip_set_color_icm_fcc_config(D_U8* param)D_FUNCPOSTFIT;
//���ϲ�����DCE Static LUT��
void d_vip_set_dce_static_lut(D_U8 idx, D_U16* lut)D_FUNCPOSTFIT;
//���ϲ�����Gamma LUT Rͨ����
void d_vip_set_gamma_lut_r(D_U8 idx, D_U16* lut)D_FUNCPOSTFIT;
//���ϲ�����Gamma LUT Gͨ����
void d_vip_set_gamma_lut_g(D_U8 idx, D_U16* lut)D_FUNCPOSTFIT;
//���ϲ�����Gamma LUT Bͨ����
void d_vip_set_gamma_lut_b(D_U8 idx, D_U16* lut)D_FUNCPOSTFIT;
void d_vip_set_color_misc_config(D_U8* param)D_FUNCPOSTFIT;
void d_vip_pattern_CMI(D_U8 pat_sel,D_U16 pat_r,D_U16 pat_g,D_U16 pat_b,D_U8 pat_speed)D_FUNCPOSTFIT;
void d_vip_set_Hmdi_Dvi_Csc_Mode(D_U8 mode);
void d_vip_set_color_icm_fcc(void)D_FUNCPOSTFIT;
void d_vip_set_color_misc(void)D_FUNCPOSTFIT;

#ifdef __cplusplus
}
#endif

#endif /* ifndef __TESTTOOL_H */
