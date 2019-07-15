/** @file
* @brief 图形控件事件
* @author 龚克
* @date 2005-8-4 龚克: 建立文件
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

/** @brief 控件事件类型*/
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
	D_EVT_TV_VID_FMT_CHANGED,		/**< 视频制式改变*/
	D_EVT_VIDEO_WINDOW_MSG,			/**<视频小窗口显示消息事件*/
	D_EVT_HOTPLUG_MSG,              /**< 热插拔通知事件*/
	D_EVT_MOUSE,                    /**< 鼠标事件 */
	D_EVT_USER,						/**< 用户定义事件*/
	D_EVT_USER1,					/**< 用户定义事件1*/
	D_EVT_USER2,					/**< 用户定义事件2*/
	D_EVT_USER3,					/**< 用户定义事件3*/
} D_EventType;

/** @brief 前面板事件*/
typedef struct {
	D_EventType				type;
	D_FPKey					key;
	D_Bool 				repeat;
} D_FPEvent;

/** @brief 定时器事件*/
typedef struct {
	D_EventType				type;
	D_Handle				htimer;
} D_TimerEvent;

/** @brief 前端设备事件*/
typedef struct {
	D_EventType				type;
	D_Handle				hfman;
	D_FEndType                        fendtype;
	D_FEndParam				param;
	D_FEndStatus			status;
} D_FEndEvent;

/** @brief 频道搜索事件*/
typedef struct {
	D_EventType	type;		/**< 事件类型*/

	D_Handle		hscan;		/**< 搜索句柄*/	
    D_FEndType  fendtype;   /**< 前端类型*/
	D_FEndParam fendparam;		/**< 搜索频率*/
	D_FEndStatus	fendstatus;	/**< 前端状态*/	
	D_U16		freq_cnt;	/**< 搜索到的频点个数*/

	D_U16		prog_cnt;	/**< 搜索到的节目数*/
	
	D_U16		tv_cnt;		/**< 搜索到的电视数目*/
	D_U16		radio_cnt;	/**< 搜索到的广播数目*/
	D_U16		other_cnt;	/**< 搜索到的其它业务数目*/
	
	D_U16		tv_cnt_1;	/**< 搜索到的电视数目*/
	D_U16		radio_cnt_1;	/**< 搜索到的广播数目*/
	D_U16		other_cnt_1;/**< 搜索到的其它业务数目*/
	D_U8		progress;/**< 搜索进度*/	
	D_U32		param;	/**< 其它信息，如搜索进度、是否锁定等*/
	D_Ptr 		*ptr;	/**< 其它信息指针，可用于节目名等*/	
	D_DBSrvInfo srvinfo;
} D_ScanEvent;

/** @brief CA事件*/
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

/** @brief SI事件*/
typedef struct {
	D_EventType	type;
	D_Handle	hscan;
	D_SiEvtparam siparam;
} D_SIEvent;

/** @brief 绘图事件*/
typedef struct {
	D_EventType	type;
	D_Rect	rect;
} D_DrawEvent;

/** @brief 预订事件到期*/
typedef struct {
	D_EventType	type;
	D_ID				sub_id;
} D_SubEvent;

/** @brief 字幕重绘事件*/
typedef struct {
	D_EventType	type;
	D_Handle		hsubt;
} D_SubtitleEvent;

/**@brief TELETEXT 重绘事件*/
typedef struct {
	D_EventType	type;
	D_Handle		httxt;
} D_TeletextEvent;

/** @brief 字符输入事件*/
typedef struct {
	D_EventType type;
	D_Bool			edit;
	D_U8				buf[16];
	D_Size			len;
} D_CharEvent;

/** @brief 视频事件*/
typedef struct {
	D_EventType	type;
	D_Handle		htv;
	D_VidFormat	fmt;
} D_TVEvent;

/** @brief 用户定义事件*/
typedef struct {
	D_EventType	type;
	D_Handle		handle;
	D_U32				param1;
	D_U32				param2;
	D_U32				param3;
	D_U32				param4;
} D_UserEvent;

/** @brief 视频小窗口提示信息事件*/
typedef struct {
	D_EventType type;
	D_Bool show; /*为D_TRUE时显示消息，D_FALSE时清除消息*/
	D_Char *msg; /*显示的消息内容，必须为全局的字符串*/
}D_VideoWinMsgEvent;

typedef struct
{
    D_EventType type;
    D_Bool plug; /**< 设备是否插入 */
    D_Ptr arg; /**< 设备信息, 如: 磁盘设备的分区索引 */
}D_HotplugMsgEvent;

typedef struct
{
    D_EventType type; /**< 事件类型 */
    D_MouseEvent sub_type; /**< 鼠标从事件类型 */
    D_Handle handle; /**< 鼠标设备句柄, 保留 */
    D_U16 button_mask; /**< 按下的鼠标按键掩码 */
    D_U16 x; /**< 鼠标x坐标, 相对于控件坐标 */
    D_U16 y; /**< 鼠标y坐标, 相对于控件坐标 */
    D_S16 z_delta; /**< 鼠标滑轮滑动位移 */
}D_MouseMsgEvent;

/** @brief 控件事件*/
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


/** @brief 图形控件事件屏蔽*/
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
