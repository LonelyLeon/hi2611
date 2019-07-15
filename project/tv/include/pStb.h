/** @file
* @brief STB控制模块
*/

#ifndef _D_STB_H_
#define _D_STB_H_

#ifdef  __cplusplus
extern "C"
{
#endif
#include "pSdk.h"
#include "pPlayer.h"



#define D_STB_MAIN_PLAYER	(0)
#define D_STB_VOLUME_MAX	P_VOLUME_MAX



/** @brief 机顶盒状态*/
typedef enum {
	D_STB_ST_PLAYING,		/**< 节目播放状态*/
	D_STB_ST_MENU,		/**< 菜单操作状态*/
	D_STB_ST_STANDBY,		/**< 待机状态*/
	D_STB_ST_LOCKED,
} D_StbStatus;;

/**@当前的菜单状态*/
typedef enum
{
    NULL_STATUS = 0,			/*无菜单，视频播放*/   
    MAIN_MENU_STATUS = 1,		/*主菜单*/
    SUB_MENU_STATUS = 2,		/*子菜单*/
    TOOL_MENU_STATUS = 4,		/*工具菜单*/
    CHAN_EDIT_STATUS = 8,		/*频道编辑*/
    CHAN_LIST_STATUS = 16,		/*频道列表*/
    CHAN_FAVOR_STATUS = 32,		/*喜爱频道列表*/    
    
    MEDIA_VIDEO_STATUS = 64,/*多媒体视频菜单*/
    MEDIA_MUSIC_STATUS = 128,/*多媒体音乐菜单*/
    MEDIA_PHOTO_STATUS = 256,/*多媒体相片菜单*/
    FM_LIST_STATUS = 512,/*FM菜单*/
}D_MenuStatus;


/** @brief 机顶盒参数*/
typedef struct {
	D_StbPlayer	*player;			/**< 播放器设备*/
	D_StbStatus	status;			/**< 机顶盒当前状态*/
    D_MenuStatus menu_status;     /**< 当前菜单状态(只在需要记录的菜单进行记录)*/
} D_Stb;


/** @brief 用户定义的消息里的参数*/
#define	USER_MSG_PARAM1_UPDATE_SCREEN		0xff5a0001
#define	USER_MSG_PARAM1_LANGUAGE_CHANGE	0xff5a0002
#define	USER_MSG_PARAM1_INPUTFMT_CHANGE	0xff5a0003
#define	USER_MSG_PARAM1_INPUT_STATUS	0xff5a0004
#define	USER_MSG_PARAM1_SCROLL_STATUS	0xff5a0005
#define	USER_MSG_PARAM1_WINDOW_START	0xff5a0006

#define USER_MSG_PARAM1_MEDIA_INFO      D_MSG_USER_PARAM1_MEDIA_INFO
#define USER_MSG_PARAM1_PVR_REC_TIME_FULL D_MSG_PVR_Record_Timeout_Msg
#define USER_MSG_PARAM1_PVR_REC_DISK_FULL D_MSG_PVR_Record_Spackeout_Msg
#define USER_MSG_PARAM1_PVR_REC_FILE_FULL D_MSG_PVR_Record_Fileeout_Msg
#define USER_MSG_PARAM1_PVR_REC_DATA_OVERFLOW D_MSG_PVR_Record_Data_OverFlow_Msg 

#define	USER_MSG_PARAM2_XXX	0xffa50001
#define	USER_MSG_PARAM2_YYY	0xffa50002

#define	USER_MSG_PARAM1_HP_STATUS	0xff6a0001
#define	USER_MSG_PARAM1_RS232_CHANGEINPUT	0xff7a0001

#define	USER_MSG_PARAM1_MEDIA_PIC_PLAY_END	0xff8a0001
#define	USER_MSG_PARAM1_MEDIA_MOV_PLAY_END	0xff8a0002
#define	USER_MSG_PARAM1_MEDIA_PVR_PLAY_END	0xff8a0003

#define	USER_MSG_PARAM1_WIFIDISPLAY_MENU	0xff9a0001
#define	USER_MSG_PARAM1_WIFIDISPLAY_SCAN	0xff9a0002
#define	USER_MSG_PARAM1_WIFIDISPLAY_CONNECT	0xff9a0003

#define	USER_MSG_PARAM1_DLNA_CONNECT	0xffaa0001
#define	USER_MSG_PARAM1_DLNA_NO_CONNECT	0xffaa0002
#define	USER_MSG_PARAM1_DLNA_VOLUME	0xffaa0003
#define	USER_MSG_PARAM1_DLNA_SEEK 	0xffaa0004
#define	USER_MSG_PARAM1_DLNA_NEXT_MOVIE 	0xffaa0005
#define	USER_MSG_PARAM1_DLNA_STATUS	0xffaa0006
#define	USER_MSG_PARAM1_DLNA_MUTE	0xffaa0007

#define	USER_MSG_PARAM1_LIULINK_MENU	0xffba0001

#define	USER_MSG_PARAM1_IPTV_PASSCODE	0xffca0001
#define	USER_MSG_PARAM1_IPTV_TVLIST	 	0xffca0002
#define	USER_MSG_PARAM1_IPTV_TIPSHOW		0xffca0003
#define	USER_MSG_PARAM1_IPTV_TIPHIDE		0xffca0004
#define	USER_MSG_PARAM1_IPTV_LOGLABLE	0xffca0005 //更新LOGIN标签
#define	USER_MSG_PARAM1_IPTV_LISTDATE	0xffca0006 //跟新节目列表



/** @brief 机顶盒相关数据*/
extern D_Stb	*g_stb;

/** @brief 机顶盒库初始化*/
D_Result	d_stb_open (void) D_FUNCPOSTFIT;

/** @brief 进行机顶盒开机检查*/
D_Result	d_stb_power_on (D_Bool power_on) D_FUNCPOSTFIT;

/** @brief 机顶盒进入待机状态*/
D_Result	d_stb_stand_by (void) D_FUNCPOSTFIT;

/** @brief 机顶盒从待机状态唤醒*/
D_Result	d_stb_wake_up (void) D_FUNCPOSTFIT;

/** @brief 机顶盒库关闭*/
D_Result	d_stb_close (void) D_FUNCPOSTFIT;

/** @brief 提示用户保存数据*/
D_Result	d_stb_store (void) D_FUNCPOSTFIT;

/** @brief 暂停所有播放器的播放和前端设备使用*/
D_Result	d_stb_stop_play (void) D_FUNCPOSTFIT;


#ifdef  __cplusplus
}
#endif

#endif
