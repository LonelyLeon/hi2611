/** @file
* @brief 播放器模块
* @author 龚克
* @date 2005-9-13 龚克: 建立文件
*/

#ifndef _D_STB_PLAYER_H_
#define _D_STB_PLAYER_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTV.h"


#define P_VOLUME_MAX 100


/** @brief 播放器状态*/
typedef enum {
	D_STB_PLAYER_STATUS_STOPPED,
	D_STB_PLAYER_STATUS_PLAYING
} D_StbPlayerStatus;


#define D_PLAYER_FLAGS_EN_CHANNEL_CHANGE	1	/**< 允许用户进行换台*/
#define D_PLAYER_FLAGS_URGENCY				2	/**< 在应急广播模式*/

#define D_PLAYER_FLAGS_PVR				              4	/**< 在PVR 模式*/

/** @brief 机顶盒节目播放设备*/
typedef struct {
	D_StbPlayerStatus	status;			/**< 播放器当前状态*/
	D_HTV			htv;				/**< TV设备句柄*/
	D_FEndType	   	fendtype;		/**< 当前播放节目的前端类型*/	
	D_HFMan			hfman;			/**< 前端设备管理句柄*/

	D_Bool                  play_emc_flag; 	/**< 正在播放应急广播频道*/	
	D_Bool			play_srv;		/**< 正在服务播放状态*/	

	D_DBSrvID		tv_id;			/**< 正在播放的电视节目*/
	D_S16			tv_num;			/**< 当前电视节目频道号*/
	D_DBSrvID		prev_tv_id;		/**< 上一个播放的电视节目*/
	
	D_Bool			play_radio;		/**< 正在播放广播节目*/	
	D_DBSrvID		radio_id;		/**< 正在播放的广播节目*/
	D_S16			radio_num;		/**< 当前广播节目频道号*/
	D_DBSrvID		prev_radio_id;	/**< 上一个播放的广播节目*/
	
	D_Bool			play_atv;		/**< 正在播放模拟节目*/	
	D_DBSrvID		atv_id;		/**< 正在播放的模拟节目*/
	D_S16			atv_num;		/**< 当前模拟节目频道号*/
	D_DBSrvID		prev_atv_id;	/**< 上一个播放的模拟节目*/

	D_DBSrvID		srv_id;			/**< 固定播放的服务ID*/
	
	D_DBSrvID		unlock_srv_id;	/**< 当前已经解锁的服务ID*/	
	
	D_HTimer		urgency_timer;	/**< 应急广播定时器*/
	D_DBSrvID		urgency_prev_srv_id;	/**< 应急广播播放播放前的服务*/
	D_U32			playflags;			/**< 播放器状态标志*/
} D_StbPlayer;



/** @brief 返回指定ID的播放器*/
D_StbPlayer*	p_stb_get_player (D_ID player_id) D_FUNCPOSTFIT;

/** @brief 初始化一个播放器
* @param player_id		播放器ID
* @param hfman	前端设备句柄,可用D_INVALID_HANDLE
* @param htv		TV设备句柄
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	p_stb_player_init (D_ID player_id, D_HFMan hfman, D_HTV htv) D_FUNCPOSTFIT;

/** @brief 重新设置播放器内部数据
* @param player_id		播放器ID
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	p_stb_player_reset (D_ID player_id) D_FUNCPOSTFIT;

/** @brief 设定播放器播放标志
* @param player_id 播放器ID
* @param flags	播放器标志
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	p_stb_player_set_flags (D_ID player_id, D_U32 flags) D_FUNCPOSTFIT;

/** @brief 取得播放器播放标志
* @param player_id 播放器ID
* @return 返回当前的播放状态
*/
D_U32	p_stb_player_get_flags (D_ID player_id) D_FUNCPOSTFIT;

/** @brief 尝试播放一个频道
* @param 	player_id	播放器ID
* @param	num	节目频道号
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	p_stb_player_play (D_ID player_id, D_U16 num) D_FUNCPOSTFIT;

/** @brief 尝试播放一个服务
* @param 	player_id	播放器ID
* @param	srv	节目记录ID
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	p_stb_player_play_srv (D_ID player_id, D_DBSrvID srv) D_FUNCPOSTFIT;

/** @brief 进行应急广播
* @param[in] player_id	播放器ID
* @param[in] srv	节目记录ID
* @param[in] ms	应急广播延迟时间(毫秒)，<= 0表示一直播放
* @retval D_OK 正确, D_ERR失败
*/
D_Result	p_stb_player_play_urgency_srv (D_ID player_id, D_DBSrvID srv, D_MSec ms) D_FUNCPOSTFIT;

/** @brief 停止应急广播
* @param[in] player_id	播放器ID
* @param[in] play_prev 是否返回播放之前的节目
* @retval D_OK 正确, D_ERR失败
*/
D_Result	p_stb_player_stop_urgency_srv (D_ID player_id, D_Bool play_prev) D_FUNCPOSTFIT;

/** @brief 尝试进行音视频播放并设置CA
* @param 	player_id	播放器ID
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	p_stb_player_try_play (D_ID player_id) D_FUNCPOSTFIT;

/** @brief 尝试播放各种可能的节目
* @param 	player_id	播放器ID
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	p_stb_player_play_valid (D_ID player_id) D_FUNCPOSTFIT;

/** @brief 停止播放
* @param 	player_id	播放器ID
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	p_stb_player_stop (D_ID player_id) D_FUNCPOSTFIT;

/** @brief 播放下一个频道
* @param 	player_id	播放器ID
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	p_stb_player_channel_up (D_ID player_id) D_FUNCPOSTFIT;

/** @brief 播放上一个频道
* @param 	player_id	播放器ID
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	p_stb_player_channel_down (D_ID player_id) D_FUNCPOSTFIT;

/** @brief 切换电视和广播播放模式
* @param 	player_id	播放器ID
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	p_stb_player_switch_tv_radio (D_ID player_id,D_Bool play_tv) D_FUNCPOSTFIT;


/** @brief 取得当前播放的服务ID*/
D_DBSrvID	p_stb_player_get_curr_srv (D_ID player_id) D_FUNCPOSTFIT;

/** @brief 取得当前播放的频道号和服务类型*/
D_S16			p_stb_player_get_curr_chan_num (D_ID player_id, D_DBSrvType *type) D_FUNCPOSTFIT;

/**@brief 交替节目显示(Added by licc 2006-07-06)*/
/* @param 	player_id	播放器ID
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result p_stb_player_alt_srv(D_ID player_id) D_FUNCPOSTFIT;

/** @brief 得到播放器中记录的服务ID*/
D_DBSrvID	p_stb_player_get_rec_srv (D_ID player_id, D_DBSrvType type) D_FUNCPOSTFIT;

/** @brief 播放I帧*/
D_Result p_stb_player_display_pic_I (D_ID player_id, D_ID pic, D_ID no) D_FUNCPOSTFIT;

/** @brief 清除残留视频 帧(黑屏操作)，stop之后调用*/	
D_Result p_stb_player_clear_vid(D_ID player_id)  D_FUNCPOSTFIT;

/** @brief 设置音量，将音量值转换为驱动所需音量值*/
D_Result p_stb_player_set_vol (D_ID player_id, D_U8 vol) D_FUNCPOSTFIT;

/** @brief 设置声道*/
D_Result p_stb_player_set_track (D_ID player_id, D_AudTrack track) D_FUNCPOSTFIT;


#ifdef  __cplusplus
}
#endif

#endif
