/** @file
* @brief STB����ģ��
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



/** @brief ������״̬*/
typedef enum {
	D_STB_ST_PLAYING,		/**< ��Ŀ����״̬*/
	D_STB_ST_MENU,		/**< �˵�����״̬*/
	D_STB_ST_STANDBY,		/**< ����״̬*/
	D_STB_ST_LOCKED,
} D_StbStatus;;

/**@��ǰ�Ĳ˵�״̬*/
typedef enum
{
    NULL_STATUS = 0,			/*�޲˵�����Ƶ����*/   
    MAIN_MENU_STATUS = 1,		/*���˵�*/
    SUB_MENU_STATUS = 2,		/*�Ӳ˵�*/
    TOOL_MENU_STATUS = 4,		/*���߲˵�*/
    CHAN_EDIT_STATUS = 8,		/*Ƶ���༭*/
    CHAN_LIST_STATUS = 16,		/*Ƶ���б�*/
    CHAN_FAVOR_STATUS = 32,		/*ϲ��Ƶ���б�*/    
    
    MEDIA_VIDEO_STATUS = 64,/*��ý����Ƶ�˵�*/
    MEDIA_MUSIC_STATUS = 128,/*��ý�����ֲ˵�*/
    MEDIA_PHOTO_STATUS = 256,/*��ý����Ƭ�˵�*/
    FM_LIST_STATUS = 512,/*FM�˵�*/
}D_MenuStatus;


/** @brief �����в���*/
typedef struct {
	D_StbPlayer	*player;			/**< �������豸*/
	D_StbStatus	status;			/**< �����е�ǰ״̬*/
    D_MenuStatus menu_status;     /**< ��ǰ�˵�״̬(ֻ����Ҫ��¼�Ĳ˵����м�¼)*/
} D_Stb;


/** @brief �û��������Ϣ��Ĳ���*/
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
#define	USER_MSG_PARAM1_IPTV_LOGLABLE	0xffca0005 //����LOGIN��ǩ
#define	USER_MSG_PARAM1_IPTV_LISTDATE	0xffca0006 //���½�Ŀ�б�



/** @brief �������������*/
extern D_Stb	*g_stb;

/** @brief �����п��ʼ��*/
D_Result	d_stb_open (void) D_FUNCPOSTFIT;

/** @brief ���л����п������*/
D_Result	d_stb_power_on (D_Bool power_on) D_FUNCPOSTFIT;

/** @brief �����н������״̬*/
D_Result	d_stb_stand_by (void) D_FUNCPOSTFIT;

/** @brief �����дӴ���״̬����*/
D_Result	d_stb_wake_up (void) D_FUNCPOSTFIT;

/** @brief �����п�ر�*/
D_Result	d_stb_close (void) D_FUNCPOSTFIT;

/** @brief ��ʾ�û���������*/
D_Result	d_stb_store (void) D_FUNCPOSTFIT;

/** @brief ��ͣ���в������Ĳ��ź�ǰ���豸ʹ��*/
D_Result	d_stb_stop_play (void) D_FUNCPOSTFIT;


#ifdef  __cplusplus
}
#endif

#endif
