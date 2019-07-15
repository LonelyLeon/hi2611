/** @file 
*@brief pvr播放控制模块
* @author zhuxl
* @date 2014-9-3
*/

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
#include "dDsc.h"
#include "pPvrPlay.h"


/*******************************************************************************************************/
/***************************************全局变量、常量区*/
/*******************************************************************************************************/

static D_HPvrRep  Pvr_Rep_Handle = D_INVALID_HANDLE;

/*******************************************************************************************************/
/***************************************函数体区*/
/*******************************************************************************************************/

/**@brief 启动pvr视频播放任务
*@retval 成功: D_OK,  失败: D_ERR
*/
D_Result d_media_pvr_open(void) D_FUNCPOSTFIT
{
	d_pvr_rep_open();
	return D_OK;
}


/**@brief 关闭pvr视频播放，释放资源
*@retval 成功: D_OK,  失败: D_ERR
*/
D_Result  d_media_pvr_close(void) D_FUNCPOSTFIT
{
	d_pvr_rep_close();
	return D_OK;
}

/**@brief 播放pvr视频文件
* retval 成功: D_OK,  失败: D_ERR
*/
D_Result d_media_pvr_play(D_Char* path) D_FUNCPOSTFIT
{
	D_Char* ch_pos;
	D_PvrRepTaskConfig pvr_config={0};

	d_pvr_rep_open();
	Pvr_Rep_Handle = d_pvr_rep_create();

	ch_pos = strrchr(path, '/');
	memcpy(pvr_config.filepath, path, (ch_pos + 1 - path));
	strcpy(pvr_config.filename, ch_pos+1);
	ch_pos = strrchr(pvr_config.filename, '.');
	*ch_pos = '\0';

	pvr_config.ts_type = PVR_REP_HAIER_TS;
	d_pvr_rep_set_param_ptr(Pvr_Rep_Handle, &pvr_config);
	
	d_pvr_rep_start(Pvr_Rep_Handle);

	return D_OK;
	
}

/**@brief 停止视频播放
*@retval 成功返回D_OK,失败返回D_ERR
*/
D_Result d_media_pvr_stop(void) D_FUNCPOSTFIT
{
	d_pvr_rep_stop(Pvr_Rep_Handle);
	d_pvr_rep_destroy(Pvr_Rep_Handle);
	d_pvr_rep_close();
	Pvr_Rep_Handle = D_INVALID_HANDLE;

	return D_OK;
}


/**@brief 暂停视频播放
*@retval 成功返回D_OK,失败返回D_ERR
*/
D_Result d_media_pvr_pause(void) D_FUNCPOSTFIT
{
	return d_pvr_rep_pause(Pvr_Rep_Handle);
}

/**@brief 恢复视频播放
*@retval 成功返回D_OK,失败返回D_ERR
*/
D_Result d_media_pvr_resume(void) D_FUNCPOSTFIT
{
	return d_pvr_rep_resume(Pvr_Rep_Handle);
}

/** @brief 取到文件里信息
*@retval 成功返回D_OK,失败返回D_ERR
*/
D_Result  d_pvr_rep_get_pvr_info(D_Char* path, D_PvrInfo* PvrInfo) D_FUNCPOSTFIT
{
	D_Char* ch_pos;
	D_PvrRepTaskConfig pvr_config={0};


	d_pvr_rep_open();
	Pvr_Rep_Handle = d_pvr_rep_create();

	ch_pos = strrchr(path, '/');
	memcpy(pvr_config.filepath, path, (ch_pos + 1 - path));
	strcpy(pvr_config.filename, ch_pos+1);
	ch_pos = strrchr(pvr_config.filename, '.');
	*ch_pos = '\0';

	pvr_config.ts_type = PVR_REP_HAIER_TS;
	d_pvr_rep_set_param_ptr(Pvr_Rep_Handle, &pvr_config);


	PvrInfo->totaltime = (D_Double)d_pvr_rep_get_total_time(Pvr_Rep_Handle);
    PvrInfo->filesize = (D_S64)d_pvr_rep_get_file_size(Pvr_Rep_Handle);

	d_app_sync(Pvr_Rep_Handle);

	d_media_pvr_stop();

	return D_OK;
}

/**@brief 获取播放状态
*@retval 返回视频枚举结构体D_MovieStatus中的值
*/
D_PvrStatus d_media_pvr_get_status(void) D_FUNCPOSTFIT
{
	D_PvrStatus pvr_state;
	D_PvrTaskState pvr_stat = d_pvr_rep_get_state(Pvr_Rep_Handle);

	switch(pvr_stat)
	{
	        case PVR_READY_OK:
	        case PVR_PLAYING:
	            pvr_state = PVR_STATUS_PLAY;
	            break;
	        case PVR_PAUSE:
	            pvr_state = PVR_STATUS_PAUSE;
	            break;
	        case PVR_STOP:
	        case PVR_INVALID:
	        default:
	            pvr_state = PVR_STATUS_STOP;
	            break;
	}

	return pvr_state;
}

/**@brief视频跳转到一个指定的时间点开始正常播放
*@param[in] pos:要seek播放的时间点
*@retval 成功返回D_OK,失败返回D_ERR
*/
D_Result d_media_pvr_seek(D_U64 pos) D_FUNCPOSTFIT
{
	return d_pvr_rep_set_jump(Pvr_Rep_Handle, (D_U32)pos);
}


/**@brief 获取当前播放时间
*@retval 返回值为D_Double类型的当前播放时间值
*/
D_U32 d_media_pvr_get_curtime(void) D_FUNCPOSTFIT
{
	return d_pvr_rep_get_time(Pvr_Rep_Handle);
}

/**@brief 获取视频的播放进度
*@retval 返回值为D_U32类型的播放进度
*/
D_U32 d_media_pvr_get_progress(void) D_FUNCPOSTFIT
{
	return d_pvr_rep_get_progress(Pvr_Rep_Handle);
}

