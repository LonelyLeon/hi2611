/** @brief 按键定义*/

#ifndef _P_FP_H_
#define _P_FP_H_
#ifdef  __cplusplus

extern "C"
{
#endif

#include "dFP.h"
#include "dPowerOff.h"
/*接dFP.h*/
typedef enum { 
	D_KEY_SATELLITE= D_KEY_PROJECT_EXT,	/* 0xA6卫星*/
	D_KEY_SEARCH,	/* 0xA7 搜索*/
	D_KEY_SINGAL_STRENGTH,	/* 0xA8信号强度*/
	D_KEY_CALENDAR,	/* 0xA9日历*/
	D_KEY_SUBSCRIBE,	/* 0xAA节目预约*/
	D_KEY_LANGUAGE,	/* 0xAB语言切换*/
	D_KEY_STOP,	/* 0xAC停止*/
	D_KEY_FORMATS,	/* 0xAD节目制式*/
	D_KEY_SMART_CARD,	/* 0xAE智能卡*/
	D_KEY_AUTHORIZATION,	/* 0xAF授权状态*/
	D_KEY_PVR,	/* 0xB0 PVR*/
	D_KEY_PLAY_MODE,	/* 0xB1播放模式*/
	D_KEY_RESOLUTION,	/* 0xB2分辨率*/
	D_KEY_AUTO_SERACH,	/* 0xB3自动搜索*/
	D_KEY_SEARCH_ALL,	/* 0xB4全频道搜索*/
  	D_KEY_SCREEN,	/* 0xB5 SCREEN 快捷键*/
	D_KEY_PNL_SOURCE,/* 0xB6 前面板SOURCE键*/
	D_KEY_RESTORE,/* 0xB7 复位键*/
	D_KEY_OLDMODE,/* 0xB8 老化模式*/
	D_KEY_SWINFO,/* 0xB9 */
	D_KEY_VIPMENU,/* 0xBA 工厂菜单*/
	D_KEY_INITIAl,/* 0xBB 初始化*/
	D_KEY_IMPORTPROM,/* 0xBC 导台*/
	D_KEY_EXITOLDMODE,/* 0xBD 退老化模式*/
	D_KEY_HDMI1,/* 0xBE HDMI1*/
	D_KEY_HDMI2,/* 0xBF HDMI2*/
	D_KEY_HDMI3,/* 0xC0 HDMI3*/
	D_KEY_AV1,/* 0xC1 AV1*/
	D_KEY_AV2,/* 0xC2 AV2*/
	D_KEY_YPBPR1,/* 0xC3 YPBPR1*/
	D_KEY_YPBPR2,/* 0xC4 YPBPR2*/
	D_KEY_VGA,/* 0xC5 VGA*/
	D_KEY_DTV_ATV,/* 0xC6 DTV_ATV*/
	D_KEY_SHOWVERSION,/* 0xC7 看版本*/
	D_KEY_HIDEVERSION,/* 0xC8 隐藏版本*/
	D_KEY_ADC,/* 0xC9  ADC*/
	D_KEY_FACTORYSET,/* 0xCA ADC*/
	D_KEY_CAKEY,/* 0xCB 序列号*/
  	D_KEY_OFFSCREEN,/* 0xCC 关屏*/
	D_KEY_IMAGE,/* 0xCD 图像*/	
	D_KEY_SOUND,/* 0xCE 声音*/	
	D_KEY_ZOOM,/* 0xCF 显示*/	
	
	D_KEY_ZHILIAN = 0xE0,/* 0xE0 智联电视按键*/	
	D_KEY_MIRACAST = 0xE1,/* 0xE1 miracast无线投屏*/		
	D_KEY_DLNA = 0xE2,/* 0xE2 DLNA无线投屏*/	
	D_KEY_TS2NET = 0xE3,/* 0xE3 ts转发*/	
	D_KEY_RECALL = 0xE4,

} P_D_KeyCode;

D_U8 p_get_remote_key(D_KeyCode key, P_POWERKEY* key_buf, D_U8 remote_size)D_FUNCPOSTFIT;
D_U8 p_get_multiple_remote_key(D_KeyCode key1, D_KeyCode key2, P_POWERKEY* key_buf, D_U8 remote_size)D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif
