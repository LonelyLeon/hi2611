/** @file
* @brief 多媒体网络ts播放模块
* @author 覃宜
* @date 2019-02-22 覃宜: 建立文件
*/

#ifndef _D_NETTS_REPLAY_H_
#define _D_NETTS_REPLAY_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dTypes.h"
#include "dGUI.h"
#include "dControl.h"
#include "dMedia.h"
#include "dPvrPorting.h"
#include "dPvrReplay.h"

/**@brief 播放 网络ts文件
*@param[in] path:播放视频文件的绝对路径
*@param[in] id:直播节目list id
*@param[in] x,y,w,h:播放视频的窗口大小位置
*@param[in] type: 播放视频类型 (电影暂时未用 ， ts 第几路节目)
*@param[in] vis:播放视频文件如果有字幕文件的话，这个则是显示字幕的控件指针
*@retval 成功返回D_OK,失败返回D_ERR
*/
D_Result d_media_netts_play(D_Char* path, D_U32 id, D_U32 x, D_U32 y, D_U32 w, D_U32 h, D_S8 type, D_Visual *vis)D_FUNCPOSTFIT;

/**@brief 停止网络ts文件播放
*@retval 成功返回D_OK,失败返回D_ERR
*/
D_Result d_media_netts_stop(void)D_FUNCPOSTFIT;


/**@brief 获取网络ts文件播放状态
*@retval 返回视频枚举结构体D_MovieStatus中的值
*/
D_MovieStatus d_media_netts_get_status(void) D_FUNCPOSTFIT;


/**@brief 获取当前播放时间
*@retval 返回值为D_Double类型的当前播放时间值
*/
D_Double d_media_netts_get_curtime(void) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif
