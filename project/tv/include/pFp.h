/** @brief ��������*/

#ifndef _P_FP_H_
#define _P_FP_H_
#ifdef  __cplusplus

extern "C"
{
#endif

#include "dFP.h"
#include "dPowerOff.h"
/*��dFP.h*/
typedef enum { 
	D_KEY_SATELLITE= D_KEY_PROJECT_EXT,	/* 0xA6����*/
	D_KEY_SEARCH,	/* 0xA7 ����*/
	D_KEY_SINGAL_STRENGTH,	/* 0xA8�ź�ǿ��*/
	D_KEY_CALENDAR,	/* 0xA9����*/
	D_KEY_SUBSCRIBE,	/* 0xAA��ĿԤԼ*/
	D_KEY_LANGUAGE,	/* 0xAB�����л�*/
	D_KEY_STOP,	/* 0xACֹͣ*/
	D_KEY_FORMATS,	/* 0xAD��Ŀ��ʽ*/
	D_KEY_SMART_CARD,	/* 0xAE���ܿ�*/
	D_KEY_AUTHORIZATION,	/* 0xAF��Ȩ״̬*/
	D_KEY_PVR,	/* 0xB0 PVR*/
	D_KEY_PLAY_MODE,	/* 0xB1����ģʽ*/
	D_KEY_RESOLUTION,	/* 0xB2�ֱ���*/
	D_KEY_AUTO_SERACH,	/* 0xB3�Զ�����*/
	D_KEY_SEARCH_ALL,	/* 0xB4ȫƵ������*/
  	D_KEY_SCREEN,	/* 0xB5 SCREEN ��ݼ�*/
	D_KEY_PNL_SOURCE,/* 0xB6 ǰ���SOURCE��*/
	D_KEY_RESTORE,/* 0xB7 ��λ��*/
	D_KEY_OLDMODE,/* 0xB8 �ϻ�ģʽ*/
	D_KEY_SWINFO,/* 0xB9 */
	D_KEY_VIPMENU,/* 0xBA �����˵�*/
	D_KEY_INITIAl,/* 0xBB ��ʼ��*/
	D_KEY_IMPORTPROM,/* 0xBC ��̨*/
	D_KEY_EXITOLDMODE,/* 0xBD ���ϻ�ģʽ*/
	D_KEY_HDMI1,/* 0xBE HDMI1*/
	D_KEY_HDMI2,/* 0xBF HDMI2*/
	D_KEY_HDMI3,/* 0xC0 HDMI3*/
	D_KEY_AV1,/* 0xC1 AV1*/
	D_KEY_AV2,/* 0xC2 AV2*/
	D_KEY_YPBPR1,/* 0xC3 YPBPR1*/
	D_KEY_YPBPR2,/* 0xC4 YPBPR2*/
	D_KEY_VGA,/* 0xC5 VGA*/
	D_KEY_DTV_ATV,/* 0xC6 DTV_ATV*/
	D_KEY_SHOWVERSION,/* 0xC7 ���汾*/
	D_KEY_HIDEVERSION,/* 0xC8 ���ذ汾*/
	D_KEY_ADC,/* 0xC9  ADC*/
	D_KEY_FACTORYSET,/* 0xCA ADC*/
	D_KEY_CAKEY,/* 0xCB ���к�*/
  	D_KEY_OFFSCREEN,/* 0xCC ����*/
	D_KEY_IMAGE,/* 0xCD ͼ��*/	
	D_KEY_SOUND,/* 0xCE ����*/	
	D_KEY_ZOOM,/* 0xCF ��ʾ*/	
	
	D_KEY_ZHILIAN = 0xE0,/* 0xE0 �������Ӱ���*/	
	D_KEY_MIRACAST = 0xE1,/* 0xE1 miracast����Ͷ��*/		
	D_KEY_DLNA = 0xE2,/* 0xE2 DLNA����Ͷ��*/	
	D_KEY_TS2NET = 0xE3,/* 0xE3 tsת��*/	
	D_KEY_RECALL = 0xE4,

} P_D_KeyCode;

D_U8 p_get_remote_key(D_KeyCode key, P_POWERKEY* key_buf, D_U8 remote_size)D_FUNCPOSTFIT;
D_U8 p_get_multiple_remote_key(D_KeyCode key1, D_KeyCode key2, P_POWERKEY* key_buf, D_U8 remote_size)D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif
