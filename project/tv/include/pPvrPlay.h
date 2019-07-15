/**@file
* @brief pvr播放控制模块
* @author  zhuxl
* @date 2014-9-3
*/

#ifndef  _P_PVR_PLAY_H_
#define _P_PVR_PLAY_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include <string.h>
#include "dTypes.h"
#include "dMedia.h"
#include "dDebug.h"
#include "dMsg.h"
#include "dFileSystem.h"
#include "dMutex.h"
#include "dMem.h"
#include "dQueue.h"
#include "dApp.h"
#include "dPvrReplay.h"


typedef enum 
{
	PVR_STATUS_STOP = 0,//暂停
	PVR_STATUS_PLAY,//播放中
	PVR_STATUS_PAUSE,//暂停中
	PVR_STATUS_SEEK
}D_PvrStatus;

/**@brief 视频信息*/
typedef struct
{
	D_U32 width;	//原始宽
	D_U32 height;	//原始高
	D_Double totaltime;	//总时长
	D_S64 filesize;	//文件大小，字节
	D_U32 sample_rate;
	D_U32 channels;
}D_PvrInfo;





/**@brief 启动pvr视频播放任务
*@retval 成功: D_OK,  失败: D_ERR
*/
D_Result d_media_pvr_open(void) D_FUNCPOSTFIT;


/**@brief 关闭pvr视频播放，释放资源
*@retval 成功: D_OK,  失败: D_ERR
*/
D_Result  d_media_pvr_close(void) D_FUNCPOSTFIT;

/**@brief 播放pvr视频文件
* retval 成功: D_OK,  失败: D_ERR
*/

D_Result d_media_pvr_play() D_FUNCPOSTFIT;

/**@brief 停止视频播放
*@retval 成功返回D_OK,失败返回D_ERR
*/
D_Result d_media_pvr_stop(void) D_FUNCPOSTFIT;


/**@brief 暂停视频播放
*@retval 成功返回D_OK,失败返回D_ERR
*/
D_Result d_media_pvr_pause(void) D_FUNCPOSTFIT;	

/**@brief 恢复视频播放
*@retval 成功返回D_OK,失败返回D_ERR
*/
D_Result d_media_pvr_resume(void) D_FUNCPOSTFIT;

/** @brief 取到文件里信息
*@retval 成功返回D_OK,失败返回D_ERR
*/
D_Result  d_pvr_rep_get_pvr_info() D_FUNCPOSTFIT;

/**@brief 获取播放状态
*@retval 返回视频枚举结构体D_MovieStatus中的值
*/
D_PvrStatus d_media_pvr_get_status(void) D_FUNCPOSTFIT;


/**@brief视频跳转到一个指定的时间点开始正常播放
*@param[in] pos:要seek播放的时间点
*@retval 成功返回D_OK,失败返回D_ERR
*/
D_Result d_media_pvr_seek(D_U64 pos) D_FUNCPOSTFIT;


/**@brief 获取视频的播放进度
*@retval 返回值为D_U32类型的播放进度
*/
D_U32 d_media_pvr_get_progress(void) D_FUNCPOSTFIT;


/**@brief 获取当前播放时间
*@retval 返回值为D_Double类型的当前播放时间值
*/
D_U32 d_media_pvr_get_curtime(void) D_FUNCPOSTFIT;


#ifdef  __cplusplus
}

#endif

#endif

