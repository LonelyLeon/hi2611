/** @file
* @brief TV模块
* @author 龚克
* @date 2006-5-18 龚克: 建立文件
	@date 2006-8-2 shanzs: 增加文字和图片广告处理
		增加d_tv_set_pic_param函数
		增加d_tv_set_pic_ratio函数
* @date 2013-05-16 lc: 统一平台, 代码整理
*/

#ifndef _D_TV_H_
#define _D_TV_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dDBase.h"
#include "dFMan.h"
#include "dQueue.h"
#include "dCA.h"
#include "dTimer.h"
#include "dDemux.h"
#include "dScan.h"
#include "dProgScan.h"
#include "dNVPart.h"
#include "dAV.h"

/** @brief 电视句柄*/
typedef D_Handle	D_HTV;

/** @brief SI搜索模式*/
typedef enum {
	D_TV_SCAN_NIT	= 1,
	D_TV_SCAN_TDT	= 2,
	D_TV_SCAN_EIT	= 4,
	D_TV_SCAN_CAT	= 8,
	D_TV_SCAN_PAT	= 16,
	D_TV_SCAN_PMT	= 32,
	D_TV_SCAN_SDT	= 64,
	D_TV_SCAN_ALL	= D_TV_SCAN_NIT | D_TV_SCAN_TDT | D_TV_SCAN_EIT |\
			D_TV_SCAN_CAT | D_TV_SCAN_PAT | D_TV_SCAN_PMT | D_TV_SCAN_SDT
} D_TVScanMode;


typedef struct {
	D_S32	x;
	D_S32	y;
	D_S32	w;
	D_S32	h;
} D_VidWindow;

/** @brief 电视数据*/
typedef struct 
{
	D_HAV			hav;
	D_VidFormat		fmt;
	D_VidPicParam	pic_param;
	D_VidPicRatio	pic_ratio;
	D_HFMan			hfman;
	D_HQueue		hq;
	D_DBSrvID		srv;
	D_DBTSID		ts;
	D_DBNetID		net;
	D_DBSrvID		temp_srv;
	D_DBTSID		temp_ts;
	D_ID			pic_I_id;
	D_Bool			locked;
	D_Bool			playing;
	D_Bool			vid_blank;
	D_Bool			aud_mute;
	D_Bool			aud_start;
	D_Bool			vid_start;
	D_FEndType		ftype;
	D_FEndParam		fparam;
	D_U16			vid_pid;
	D_U16			aud_pid;
	D_U16			pcr_pid;
	D_VidCodecType	vid_codec;
	D_AudCodecType	aud_codec;
	D_U16			ecm_v_pid;
	D_U16			ecm_a_pid;
	D_U16			ecm_ca_sys_id;
	D_U16			emm_pid;
	D_U16			emm_ca_sys_id;
	D_HTimer		mute_timer;
	D_TVScanMode	scan_mode;
	D_ProgScan* ps;
	D_VidWindow      vid_window;
	D_Bool     		is_full_screen;
	D_Bool 			blank_on_change_chan;
       D_Bool               play_lock;
       D_Bool               power_on_checking;
   D_Bool           playing_pic_I;
       
} TVData;

/*tv里在调用d_av_play 前钩子参数*/
typedef struct
{
	D_U8 srv_type;
    D_DBSrvID dbsrvid;
    D_AVPlayParam *pp;
}D_TvAvPlayHookParam;


/** @brief TV模块初始化*/
D_Result	d_tv_open (void) D_FUNCPOSTFIT;

/** @brief TV模块释放*/
D_Result	d_tv_close (void) D_FUNCPOSTFIT;

/** @brief 创建一个TV设备*/
D_HTV		d_tv_create (D_S8 priority, D_AVAttr *attr, D_HQueue hq) D_FUNCPOSTFIT;

/** @brief 设置电视对应的消息队列*/
D_Result	d_tv_set_queue (D_HTV htv, D_HQueue hq) D_FUNCPOSTFIT;

/** @brief 销毁一个TV设备*/
D_Result	d_tv_destroy (D_HTV htv) D_FUNCPOSTFIT;

/** @brief 播放一个服务*/
D_Result	d_tv_play_srv (D_HTV htv, D_DBSrvID srv) D_FUNCPOSTFIT;

/** @brief 显示I祯*/
#if 0
D_Result	d_tv_display_pic_I (D_HTV htv, D_ID pic) D_FUNCPOSTFIT;
#else
D_Result d_tv_display_pic_I (D_HTV htv, D_ID pic, D_U8 *buf,D_U32 size) D_FUNCPOSTFIT;
#endif

/** @brief 显示I祯*/
D_Result d_tv_display_pic_I_ext (D_HTV htv, D_U8 *buf,D_U32 size) D_FUNCPOSTFIT;

/** @brief 设置静音*/
D_Result	d_tv_set_aud_mute (D_HTV htv, D_Bool mute) D_FUNCPOSTFIT;

/** @brief 设置声道*/
D_Result	d_tv_set_aud_track (D_HTV htv, D_AudTrack track) D_FUNCPOSTFIT;

/** @brief 设置伴音*/
D_Result	d_tv_set_aud_acc (D_HTV htv, D_U8 acc) D_FUNCPOSTFIT;

/** @brief 设置视频窗口*/
D_Result	d_tv_set_vid_window (D_HTV htv, D_Coord x, D_Coord y, D_Coord w, D_Coord h) D_FUNCPOSTFIT;

/** @brief 设定视频制式*/
D_Result	d_tv_set_vid_format (D_HTV htv, D_VidFormat fmt) D_FUNCPOSTFIT;

/** @brief 设定视频输出*/
D_Result	d_tv_set_vid_output (D_HTV htv, D_VidOutput out) D_FUNCPOSTFIT;

/** @brief 设定视频黑屏*/
D_Result	d_tv_set_vid_blank (D_HTV htv, D_Bool blank) D_FUNCPOSTFIT;

/** @brief 设定声道*/
D_Result	d_tv_set_volume (D_HTV htv, D_U8 vol) D_FUNCPOSTFIT;

/** @brief 停止电视播放，同时关闭相应SI的搜索*/
D_Result	d_tv_suspend (D_HTV htv) D_FUNCPOSTFIT;

/** @brief 电视进入待机,同时开始监控指定TS上的数据*/
D_Result	d_tv_standby (D_HTV htv, D_DBTSID ts) D_FUNCPOSTFIT;

/** @brief 同步操作*/
D_Result	d_tv_sync (D_HTV htv) D_FUNCPOSTFIT;

/** @brief 设定SI分析模式*/
D_Result	d_tv_scan_si (D_HTV htv, D_TVScanMode mode) D_FUNCPOSTFIT;

/** @brief 停止当前服务播放*/
#define d_tv_stop_srv(a)		d_tv_play_srv(a,-1)

/** @brief 清除I祯显示*/
//#define d_tv_clear_pic_I(a)	d_tv_display_pic_I(a,-1)
#define d_tv_clear_pic_I(a)	d_tv_display_pic_I(a,-1,NULL,0)

/** @brief 恢复视频原始大小*/
#define d_tv_restore_vid_window(a)	d_tv_set_vid_window(a,0,0,-1,-1)

/** @brief 设置视频参数  added by shanzs@06/08/02
*/
D_Result	d_tv_set_pic_param (D_HTV htv, D_VidPicParam *param);

/** @brief 设置视频宽高比例  added by shanzs@06/08/02
*/
D_Result	d_tv_set_pic_ratio (D_HTV htv, D_VidPicRatio ratio);

/** @brief 设定换台静帧黑屏模式, blank : D_FALSE 静帧， D_TRUE 黑屏*/
D_Result d_tv_set_chan_change_blank (D_HTV htv, D_Bool blank) D_FUNCPOSTFIT;

/** @brief 锁定TV, 禁止播放节目*/
D_Result d_tv_set_play_lock(D_HTV htv, D_Bool lock) D_FUNCPOSTFIT;

/** @brief 开机锁定某频点，并启动si表监控，开机检查信息*/
D_Result
d_tv_power_on_check (D_HTV htv, D_Bool start, D_DBTSInfo ts_info, D_ID db_ts_id, D_TVScanMode scan_mode) D_FUNCPOSTFIT;

/** @brief 返回当前高清视频标志*/
D_U32 d_tv_get_hd_video_flag(void) D_FUNCPOSTFIT;
/** @brief 设定视频输出*/
D_Result d_tv_set_vid_input (D_HTV htv, D_VidInput input) D_FUNCPOSTFIT;

/** @brief 设定视频输出*/
D_Result d_tv_set_balance (D_HTV htv, D_S8 val) D_FUNCPOSTFIT;

/** @brief 返回当前视频窗口坐标*/
D_Result d_tv_get_vid_window(D_HTV htv, D_Coord* x, D_Coord* y, D_Coord* w, D_Coord* h) D_FUNCPOSTFIT;

/** @brief 清除视频*/
D_Result d_tv_clear_vid (D_HTV htv) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
