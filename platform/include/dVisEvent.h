/** @file
* @brief ͼ�οؼ��¼�
* @author ����
* @date 2005-8-4 ����: �����ļ�
*/

#ifndef _D_VIS_EVENT_H_
#define _D_VIS_EVENT_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dGraph.h"
#include "dAV.h"
#include "dFEnd.h"
#include "dFP.h"
#include "dDBase.h"
#include "dTouchScreen.h"
#include "dMouse.h"

/** @brief �ؼ��¼�����*/
typedef enum {
	D_EVT_DESTROY,
	D_EVT_FP,
	D_EVT_TIMER,
	D_EVT_FEND_LOCKED,
	D_EVT_FEND_UNLOCKED,
	D_EVT_FEND_STATUS,
	D_EVT_SHOW,
	D_EVT_HIDE,
	D_EVT_ENTER,
	D_EVT_LEAVE,
	D_EVT_SCAN_OK,
	D_EVT_SCAN_PROGRESS,
	D_EVT_SCAN_FEND_STATUS,
	D_EVT_SCAN_FREQ,
	D_EVT_SCAN_FREQ_END,
	D_EVT_SCAN_GROUP_START,
	D_EVT_SCAN_DATA,
	D_EVT_SI_GET_TDT,
	D_EVT_SI_GET_EIT,
	D_EVT_SI_GET_PMT,
	D_EVT_SI_GET_CAT,
	D_EVT_SI_SW_UPDATE,
	D_EVT_SI_CHAN_UPDATE,
	D_EVT_EPG,
	D_EVT_CA,
	D_EVT_PRESSED,
	D_EVT_SELECTED,
	D_EVT_UNSELECTED,
	D_EVT_DATA_CHANGED,
	D_EVT_DRAW,
	D_EVT_SUB_START,
	D_EVT_SUBTITLE_REDRAW,
	D_EVT_TELETEXT_REDRAW,
	D_EVT_CHAR,
	D_EVT_TV_VID_FMT_CHANGED,		/**< ��Ƶ��ʽ�ı�*/
	D_EVT_VIDEO_WINDOW_MSG,			/**<��ƵС������ʾ��Ϣ�¼�*/
	D_EVT_HOTPLUG_MSG,              /**< �Ȳ��֪ͨ�¼�*/
	D_EVT_MOUSE,                    /**< ����¼� */
	D_EVT_USER,						/**< �û������¼�*/
	D_EVT_USER1,					/**< �û������¼�1*/
	D_EVT_USER2,					/**< �û������¼�2*/
	D_EVT_USER3,					/**< �û������¼�3*/
} D_EventType;

/** @brief ǰ����¼�*/
typedef struct {
	D_EventType				type;
	D_FPKey					key;
	D_Bool 				repeat;
} D_FPEvent;

/** @brief ��ʱ���¼�*/
typedef struct {
	D_EventType				type;
	D_Handle				htimer;
} D_TimerEvent;

/** @brief ǰ���豸�¼�*/
typedef struct {
	D_EventType				type;
	D_Handle				hfman;
	D_FEndType                        fendtype;
	D_FEndParam				param;
	D_FEndStatus			status;
} D_FEndEvent;

/** @brief Ƶ�������¼�*/
typedef struct {
	D_EventType	type;		/**< �¼�����*/

	D_Handle		hscan;		/**< �������*/	
    D_FEndType  fendtype;   /**< ǰ������*/
	D_FEndParam fendparam;		/**< ����Ƶ��*/
	D_FEndStatus	fendstatus;	/**< ǰ��״̬*/	
	D_U16		freq_cnt;	/**< ��������Ƶ�����*/

	D_U16		prog_cnt;	/**< �������Ľ�Ŀ��*/
	
	D_U16		tv_cnt;		/**< �������ĵ�����Ŀ*/
	D_U16		radio_cnt;	/**< �������Ĺ㲥��Ŀ*/
	D_U16		other_cnt;	/**< ������������ҵ����Ŀ*/
	
	D_U16		tv_cnt_1;	/**< �������ĵ�����Ŀ*/
	D_U16		radio_cnt_1;	/**< �������Ĺ㲥��Ŀ*/
	D_U16		other_cnt_1;/**< ������������ҵ����Ŀ*/
	D_U8		progress;/**< ��������*/	
	D_U32		param;	/**< ������Ϣ�����������ȡ��Ƿ�������*/
	D_Ptr 		*ptr;	/**< ������Ϣָ�룬�����ڽ�Ŀ����*/	
	D_DBSrvInfo srvinfo;
} D_ScanEvent;

/** @brief CA�¼�*/
typedef struct {
	D_EventType	type;
	D_U32				param1;
	D_U32				param2;
} D_CAEvent;

typedef struct {
	D_U32	montype;
	D_U8	version;
	D_Ptr	pdata;
}D_SiEvtparam;

/** @brief SI�¼�*/
typedef struct {
	D_EventType	type;
	D_Handle	hscan;
	D_SiEvtparam siparam;
} D_SIEvent;

/** @brief ��ͼ�¼�*/
typedef struct {
	D_EventType	type;
	D_Rect	rect;
} D_DrawEvent;

/** @brief Ԥ���¼�����*/
typedef struct {
	D_EventType	type;
	D_ID				sub_id;
} D_SubEvent;

/** @brief ��Ļ�ػ��¼�*/
typedef struct {
	D_EventType	type;
	D_Handle		hsubt;
} D_SubtitleEvent;

/**@brief TELETEXT �ػ��¼�*/
typedef struct {
	D_EventType	type;
	D_Handle		httxt;
} D_TeletextEvent;

/** @brief �ַ������¼�*/
typedef struct {
	D_EventType type;
	D_Bool			edit;
	D_U8				buf[16];
	D_Size			len;
} D_CharEvent;

/** @brief ��Ƶ�¼�*/
typedef struct {
	D_EventType	type;
	D_Handle		htv;
	D_VidFormat	fmt;
} D_TVEvent;

/** @brief �û������¼�*/
typedef struct {
	D_EventType	type;
	D_Handle		handle;
	D_U32				param1;
	D_U32				param2;
	D_U32				param3;
	D_U32				param4;
} D_UserEvent;

/** @brief ��ƵС������ʾ��Ϣ�¼�*/
typedef struct {
	D_EventType type;
	D_Bool show; /*ΪD_TRUEʱ��ʾ��Ϣ��D_FALSEʱ�����Ϣ*/
	D_Char *msg; /*��ʾ����Ϣ���ݣ�����Ϊȫ�ֵ��ַ���*/
}D_VideoWinMsgEvent;

typedef struct
{
    D_EventType type;
    D_Bool plug; /**< �豸�Ƿ���� */
    D_Ptr arg; /**< �豸��Ϣ, ��: �����豸�ķ������� */
}D_HotplugMsgEvent;

typedef struct
{
    D_EventType type; /**< �¼����� */
    D_MouseEvent sub_type; /**< �����¼����� */
    D_Handle handle; /**< ����豸���, ���� */
    D_U16 button_mask; /**< ���µ���갴������ */
    D_U16 x; /**< ���x����, ����ڿؼ����� */
    D_U16 y; /**< ���y����, ����ڿؼ����� */
    D_S16 z_delta; /**< ��껬�ֻ���λ�� */
}D_MouseMsgEvent;

/** @brief �ؼ��¼�*/
typedef union {
	D_EventType		type;
	D_FPEvent		fp;
	D_TimerEvent	timer;
	D_FEndEvent		fend;
	D_ScanEvent		scan;
	D_CAEvent		ca;
	D_SIEvent		si;
	D_DrawEvent		draw;
	D_SubEvent		sub;
	D_SubtitleEvent	subtitle;
	D_TeletextEvent teletext;
	D_CharEvent		chr;
	D_TVEvent		tv;
	D_UserEvent		user;
	D_VideoWinMsgEvent  vid_win;
    D_HotplugMsgEvent   hotplug;
    D_MouseMsgEvent mouse;
} D_Event;


/** @brief ͼ�οؼ��¼�����*/
typedef enum {
	D_EVT_UP_DOWN_KEY_MASK 			= 1,
	D_EVT_LEFT_RIGHT_KEY_MASK 	= (1<<1),
	D_EVT_COLOR_KEY_MASK				= (1<<2),
	D_EVT_ESC_KEY_MASK					= (1<<3),
	D_EVT_OK_KEY_MASK						= (1<<4),
	D_EVT_NUM_KEY_MASK					= (1<<5),
	D_EVT_PG_UP_DOWN_KEY_MASK		= (1<<6),
	D_EVT_FEND_MASK							= (1<<7),
	D_EVT_TIMER_MASK						= (1<<8),
	D_EVT_SCAN_MASK							= (1<<9),
	D_EVT_SI_TDT_MASK						= (1<<10),
	D_EVT_SI_EIT_MASK						= (1<<11),
	D_EVT_SI_CAT_MASK						= (1<<12),
	D_EVT_SI_PMT_MASK						= (1<<13),
	D_EVT_CA_MASK								= (1<<14),
	D_EVT_KEY_MASK							= (1<<15),
	D_EVT_SUB_MASK							= (1<<16),
	D_EVT_SUBTITLE_MASK					= (1<<17),
	D_EVT_POWER_KEY_MASK				= (1<<18),
	D_EVT_TELETEXT_MASK					= (1<<19),
	D_EVT_AUDIO_KEY_MASK 				= (1<<20),
	D_EVT_PROGRAM_PLUS_MINUS_KEY_MASK = (1<<21),
	D_EVT_TV_MASK								= (1<<22),
	D_EVT_USER_MASK							= (1<<23),
	D_EVT_VIDEO_WIN_MSG_MASK				= (1<<24),
	D_EVT_HOTPLUG_MSG_MASK              = (1 << 25),
	D_EVT_MOUSE_MASK                = (1 << 26),
	D_EVT_ALL_KEY_MASK					= D_EVT_UP_DOWN_KEY_MASK |
			D_EVT_LEFT_RIGHT_KEY_MASK | D_EVT_COLOR_KEY_MASK | 
			D_EVT_ESC_KEY_MASK | D_EVT_OK_KEY_MASK | 
			D_EVT_NUM_KEY_MASK	| D_EVT_PG_UP_DOWN_KEY_MASK |
			D_EVT_KEY_MASK
} D_EventMask;

#ifdef  __cplusplus
}
#endif

#endif
