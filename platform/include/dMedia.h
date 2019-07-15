/** @file dMedia.h
* @brief Media模块
* @author wangyq
* @date 2013-10-10 wangyq: 建立文件
* @date 2014-05-04 wangyq: 整理代码注释
*/

#ifndef _D_Media_H_
#define _D_Media_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dGUI.h"
#include "dControl.h"


/** @brief 用户定义的消息里的参数*/
#define D_MSG_USER_PARAM1_MEDIA_INFO        0xff5a0100

/*针对高清电视解码视频高宽控制*/
#define D_Media_Movie_Codec_Width_Max	(1920)
#define D_Media_Movie_Codec_Height_Max	(1088)

#define D_Media_Movie_Codec_Width_Limit		(256)
#define D_Media_Movie_Codec_Height_LImit	(192)

/**@brief  图片类型*/
typedef enum 
{
	IMGTYPE_JPEG = 0, /**< JPEG格式图片*/
	IMGTYPE_BMP,      /**< BMP格式图片 */
	IMGTYPE_GIF,      /**< GIF格式图片*/
	IMGTYPE_PNG,      /**< PNG格式图片 */
	IMGTPYE_MAX
}D_PictureType;

/**@breif 图片播放模式*/
typedef enum
{
	PICTURE_PLAY_SINGLE_ONE=0,
	PICTUREC_PLAY_SINGLE_REAPEAT,	
	PICTURE_PLAY_ALL_ONE,
	PICTURE_PLAY_ALL_REAPEAT
}D_PictureCycleMode;

/**@brief 图片播放状态*/
typedef enum 
{
	PICTURE_STATUS_STOP = 0,//空闲
	PICTURE_STATUS_RUN,//解码中
	PICTURE_STATUS_PAUSE //暂停
}D_PictureStatus;

/**@brief 图片打开方式与dfp模块对应定义*/
typedef enum 
{
    PICTURE_OPEN_MODE_NORMAL = 0,
    PICTURE_OPEN_MODE_PREVIEW,
} D_PictureOpenMode;

/**@brief 音乐播放模式*/
typedef enum
{
	MUSIC_PLAY_SINGLE_ONE=0,
	MUSIC_PLAY_SINGLE_REPEAT,	
	MUSIC_PLAY_ALL_ONE,
	MUSIC_PLAY_ALL_REPEAT
}D_MusicCycleMode;

/**@brief 音乐播放状态*/
typedef enum 
{
	MUSIC_STATUS_STOP = 0,//空闲
	MUSIC_STATUS_RUN,//播放中
	MUSIC_STATUS_PAUSE //暂停中
}D_MusicStatus;

/**@brief ebk播放状态*/
typedef enum {
    EBK_STATUS_STOP = 0,
    EBK_STATUS_RUN,
    EBK_STATUS_PAUSE,
}D_EbkStatus;

/**@brief 视频ffmpeg版本*/
typedef enum
{
	MOVIE_FFMPEG_VER_OLD=0,  /* 旧版本，不支持网络播放*/
	MOVIE_FFMPEG_VER_NEW_V34, /* 3.4版本，支持网络播放*/
}D_MovieFFmepgVersion;

/**@brief 视频播放模式*/
typedef enum
{
	MOVIE_PLAY_SINGLE_ONE=0,
	MOVIE_PLAY_SINGLE_REAPEAT,	
	MOVIE_PLAY_ALL_ONE,
	MOVIE_PLAY_ALL_REAPEAT
}D_MovieCycleMode;

/**@brief 视频播放状态*/
typedef enum 
{
	MOVIE_STATUS_STOP = 0,//暂停
	MOVIE_STATUS_PLAY,//播放中
	MOVIE_STATUS_PAUSE,//暂停中
	MOVIE_STATUS_SEEK,
	MOVIE_STATUS_WAITING, //缓冲中
}D_MovieStatus;

/** @brief定义显示区域*/
typedef struct
{
	D_U32 offset_x;//水平偏移	
	D_U32 offset_y;//垂直偏移
	
	D_U32 out_width;//	显示宽度	
	D_U32 out_height;//显示高度
}D_ShowRect;

/**@brief 图片信息*/
typedef struct
{
	D_U16 file_type;//// 0:jpeg.  1:bmp
	D_U16 jpeg_type;
	D_U32 width;//原始宽
	D_U32 height;//原始高
	D_S64 filesize;//文件大小，字节
}D_PictureInfo;

typedef struct
{
    D_U16 pic_x;
    D_U16 pic_y;
    D_U16 pic_w;
    D_U16 pic_h;
    D_U16 win_w;
    D_U16 win_h;
    D_Ptr dst_addr;
}D_Bmp_Data;

/**@brief 图片信息*/
typedef struct
{
	/*callback 给菜单提示信息使用*/
	D_U8 pic_decode_ret;/*图片解码信息  0: 解码失败 1:内存不足*/
	D_Char path[256];
        D_Bmp_Data bmp_data;
}D_Pic_Cb;


/**@brief 音乐信息*/
typedef struct
{
	
	D_U32 codec_id;//音频编码格式方便上层过滤支持的播放格式
	D_U8 channel;//通道数
	D_U32 BitsPerSec;//比特率
	D_U32 sample_rate;//采样率
	D_S64 filesize;//文件大小，字节
	D_Double totaltime;//总时长，秒
       D_Char title[32];
	D_Char artist[32];
	D_Char album[32];
    D_Char year[32];
	D_U8 tag_encoding_type; // 0--ansi(mp3); 1--utf8(mp3); 2--utf16(wma)
}D_MusicInfo;

/**@brief 视频信息*/
typedef struct
{
	D_U32 width;//原始宽
	D_U32 height;//原始高
	D_Double totaltime;//总时长
	D_Double  frame_rate; //帧率
	D_S64 filesize;//文件大小，字节
	D_U32 sample_rate;
	D_U32 channels;
}D_MovieInfo;

typedef enum
{
    D_MoviePlayRate_1X = 0,
    D_MoviePlayRate_2X,
    D_MoviePlayRate_4X,
    D_MoviePlayRate_8X,
    D_MoviePlayRate_16X,
    D_MoviePlayRate_32X,
}D_MoviePlayRate;

#define MOVIE_AUDIO_LANGUAGE_LENGTH 4

/**@brief 音频信息 */
typedef struct
{
    D_Int audio_index;  /**< 用于传递给音轨选择的索引值 */
    D_U32 sample_rate;
    D_U32 channels;
    D_Char language[MOVIE_AUDIO_LANGUAGE_LENGTH];
	D_U32 codec_id;
}D_MovieAudioInfo;

#define MEDIA_SUBTITLE_LINE_CNT (3)
#define MEDIA_SUBTITLE_LINE_SIZE (512)
/**@brief 字幕信息*/
typedef struct
{
	D_U32 sub_id;
	D_U32 line_cnt;
    D_Char sub_text[MEDIA_SUBTITLE_LINE_CNT][MEDIA_SUBTITLE_LINE_SIZE];
}D_SubtitleInfo;



/**@brief 图片相关接口声明*/

/** @brief Media 图片模块初始化
*@retval 有效返回值:D_OK  无效返回值:D_ERR_FAULT
*/
D_Result	d_media_picture_open (void) D_FUNCPOSTFIT;

/** @brief Media 图片模块释放
*@retval 返回值:D_OK
*/
D_Result	d_media_picture_close (void) D_FUNCPOSTFIT;

/** @brief Media 图片模块设定图片显示所在的gui层
gif图是在osd上创建控件显示的，所以要指定显示层
一般在d_media_picture_open后调用一次
*@retval 返回值:D_OK
*/
D_Result d_media_picture_set_layer (D_GUILayer layer) D_FUNCPOSTFIT;

/** @brief 获取 图片信息
*@param[in] path 文件名全路径信息
*@param[out] info 返回图片信息结构体
*@retval 成功返回D_OK; 失败返回D_ERR_NOT_SUPPORT
*/
D_Result d_media_picture_get_info (D_Char* path, D_PictureInfo* info) D_FUNCPOSTFIT;

/** @brief 播放一个图片
*@param[in] path: 文件绝对路径
*@param[in] x,y,w,h:播放窗口大小
*@param[in] type:文件类型
*@param[in] rotate_flag:图片播放旋转角度0--0; 1--90; 2--180; 3--270
*@param[in] codec_flag:图片解码方式0:正常播放 1:预览方式播放
*@retval 成功返回D_OK  失败返回D_ERR_FAULT
*/
D_Result d_media_picture_play(D_Char* path, D_U32 x, D_U32 y, D_U32 w, D_U32 h,D_S8 type,D_U8 rotate_flag, D_U8 codec_flag) D_FUNCPOSTFIT;

/** @brief 停止播放Media图片
*@retval 成功返回D_OK 失败返回D_ERR
*/
D_Result	d_media_picture_stop (void) D_FUNCPOSTFIT;

/** @brief 获取Media图片播放状态
*@retval 返回当前图片状态D_PictureStatus 枚举值
*/
D_PictureStatus d_media_picture_get_status(void)D_FUNCPOSTFIT;

/** @brief 旋转YUV数据
*@x,y,w,h:播放窗口大小
*@rotate_flag:图片播放旋转角度0--0; 1--90; 2--180; 3--270
*/
D_Result d_media_picture_sw_rotate(D_Char* srcbuf, D_U32 x, D_U32 y, D_U32 w, D_U32 h,D_U16 src_store_w,D_U16 src_store_h,D_U8 rotate_flag) D_FUNCPOSTFIT;

/**@brief 音乐相关接口声明*/
/**@brief 初始化播放状态和media任务
*@retval 有效返回值:D_OK  无效返回值:D_ERR
*/
D_Result d_media_music_open(void) D_FUNCPOSTFIT;

/**@brief 还原电视播放设置和任务
*@retval 返回值为D_OK
*/
D_Result d_media_music_close(void) D_FUNCPOSTFIT;

/**@brief 停止音乐播放
*@ retval 成功返回D_OK 失败返回D_ERR
*/
D_Result d_media_music_stop(void) D_FUNCPOSTFIT;

/**@brief 播放音乐
*@param[in] path:要播放音乐的绝对路径
*@param[in] type: 音乐类型 暂时未用，没有实际作用
*@param[in] vis 音乐播放时如果有音乐字幕的话，显示字幕的控件指针
*@retval 成功返回D_OK  失败返回D_ERR
*/
D_Result d_media_music_play(D_Char* path, D_U8 type, D_Visual *vis) D_FUNCPOSTFIT;

/**@breif 音乐暂停播放
*@retval 成功返回D_OK  失败返回D_ERR
*/
D_Result d_media_music_pause(void) D_FUNCPOSTFIT;

/**@breif 继续播放音乐
*@retval 成功返回D_OK  失败返回D_ERR
*/
D_Result d_media_music_resume(void) D_FUNCPOSTFIT;

/**@breif 获取当前音乐状态
*@retval 返回值为结构体中D_MusicStatus的枚举值
*/
D_U8 d_media_music_get_status(void) D_FUNCPOSTFIT;

/**@brief 获取当前音乐播放时间
*@retval 返回值为float类型的当前时间值
*/
float d_media_music_get_curtime(void) D_FUNCPOSTFIT;

/**@brief 获取音乐信息用来显示在UI上
*@param[in] path:要获取音乐的绝对路径
*@param[out] info:返回音乐信息结构体D_MusicInfo中的相关内容
*@retval 成功返回D_OK,失败返回D_ERR
*/
D_Result d_media_music_get_info(D_Char* path, D_MusicInfo* info) D_FUNCPOSTFIT;

/**@brief 初始化音乐播放画波形图的柱状列数和每列的块数
*@param[in] block:每一列的柱状块数
*@param[in] column在UI上需要画的柱状列数
*@retval 成功返回D_OK,失败返回D_ERR
*注意:该函数在画每首音乐文件波形图时只需调用一次即可
*/
D_Result d_media_music_init_sound_param(D_U16 *block, D_U16 *column) D_FUNCPOSTFIT;

/**@brief 获取音乐播放数据图表来画到UI上
*@param[out] size:数组数据个数
*@param[out] histogram:返回音乐信息图数据
*@retval 成功返回D_OK,失败返回D_ERR
*/
D_Result d_media_music_get_sound_param(D_U16 histogram[]) D_FUNCPOSTFIT;

/**@brief 视频相关接口声明*/

/**@brief 设置使用ffmpeg的版本，请在d_media_movie_open之前调用
*@retval 成功返回D_OK,失败返回D_ERR
*/
D_Result d_media_movie_set_version(D_MovieFFmepgVersion version) D_FUNCPOSTFIT;

/**@brief 初始化视频文件播放状态和启动视频播放任务和解码任务
*@retval 成功返回D_OK,失败返回D_ERR
*/
D_Result d_media_movie_open(void) D_FUNCPOSTFIT;

/**@brief 还原电视播放设置和停止视频播放任务
*@retval 成功返回D_OK,失败返回D_ERR
*/
D_Result d_media_movie_close(void) D_FUNCPOSTFIT;

/**@brief 停止视频播放
*@retval 成功返回D_OK,失败返回D_ERR
*/
D_Result d_media_movie_stop(void) D_FUNCPOSTFIT;

/**@brief 播放视频文件
*@param[in] path:播放视频文件的绝对路径
*@param[in] x,y,w,h:播放视频的窗口大小位置
*@param[in] type: 播放视频类型 (电影暂时未用 ， ts 第几路节目)
*@param[in] vis:播放视频文件如果有字幕文件的话，这个则是显示字幕的控件指针
*@retval 成功返回D_OK,失败返回D_ERR
*/
D_Result d_media_movie_play(D_Char* path, D_U32 x, D_U32 y, D_U32 w, D_U32 h,D_S8 type, D_Visual *vis) D_FUNCPOSTFIT;

/**@brief 暂停视频播放
*@retval 成功返回D_OK,失败返回D_ERR
*/
D_Result d_media_movie_pause(void) D_FUNCPOSTFIT;

/**@brief 恢复视频播放
*@retval 成功返回D_OK,失败返回D_ERR
*/
D_Result d_media_movie_resume(void) D_FUNCPOSTFIT;

/**@brief 以不同的速度播放视频慢播
*@note 函数暂时未使用，不实现
*/
D_Result d_media_movie_slow(D_MoviePlayRate rate) D_FUNCPOSTFIT;

/**@brief 以不同的速度播放视频快播
*@note 函数暂时未使用，不实现
*/
D_Result d_media_movie_forward(D_MoviePlayRate rate) D_FUNCPOSTFIT;

/**@brief 以不同的速度回退播放视频
*@note 函数暂时未使用，不实现
*/
D_Result d_media_movie_rewind(D_MoviePlayRate rate) D_FUNCPOSTFIT;

/**@brief视频跳转到一个指定的时间点开始正常播放
*@param[in] pos:要seek播放的时间点
*@retval 成功返回D_OK,失败返回D_ERR
*/
D_Result d_media_movie_seek(D_U64 pos) D_FUNCPOSTFIT;

/**@brief 获取播放状态
*@D_MovieStatus 返回视频枚举结构体D_MovieStatus中的值
*/
D_MovieStatus d_media_movie_get_status(void) D_FUNCPOSTFIT;

/**@brief 获取当前播放时间
*@retval 返回值为D_Double类型的当前播放时间值
*/
D_Double d_media_movie_get_curtime(void) D_FUNCPOSTFIT;

/**@brief 获取视频文件信息用来显示在UI上
*@param[in] path:要获取的视频文件绝对路径
*@param[in] x,y,w,h:需要显示视频的窗口大小
*@param[in] type: 播放视频类型 (电影暂时未用 ， ts 第几路节目)
*@param[out] info:要返回的视频文件信息结构体内容D_MovieInfo
*@retval 成功返回D_OK 失败返回D_ERR
*/
D_Result d_media_movie_get_info_ex (D_Char* path, D_MovieInfo* info, D_U32 x, D_U32 y, D_U32 w, D_U32 h, D_S8 type) D_FUNCPOSTFIT;
#define d_media_movie_get_info(path, info, x, y, w, h) d_media_movie_get_info_ex (path, info, x, y, w, h, 0)

/**@brief 视频预览功能显示视频中的第一帧图片信息
*@param[in] path:要预览的视频文件绝对路径
*@param[in] x,y,w,h:预览显示视频帧的窗口大小
*@retval 成功返回D_OK 失败返回D_ERR
*/
D_Result d_media_movie_preview(D_Char* path, D_U32 x, D_U32 y, D_U32 w, D_U32 h) D_FUNCPOSTFIT;

/**@brief 设备视频播放位置
*@param[in] x,y,w,h:需要显示视频的窗口大小
*@param[in] mode: 0 -- full screen; 1 -- window mode
*@retval 成功返回D_OK 失败返回D_ERR
*@note 函数暂时未用到
*/
D_Result d_media_movie_set_video_location(D_U32 x, D_U32 y, D_U32 w, D_U32 h,D_U8 mode)D_FUNCPOSTFIT;

/**@brief 关闭视频VO层显示
*@retval 成功返回D_OK 
*/
D_Result d_media_movie_hide_screen(void) D_FUNCPOSTFIT;

/**@brief 打开视频VO层显示一般在函数d_movie_set_param()即函数d_media_movie_hide_screen()后调用
*@retval 成功返回D_OK 
*/
D_Result d_media_movie_show_screen(void) D_FUNCPOSTFIT;


/**@brief 设置视频播放的状态
*@param[in] status:要设置的视频状态，参数为枚举值D_MovieStatus中的成员变量
*@retval 成功返回D_OK 
*/
D_Result d_media_movie_set_status(D_MovieStatus status) D_FUNCPOSTFIT;

/**@brief 获取当前播放文件的总时间长度
*@retval 返回值为当前播放视频文件的总时长
*/
D_Double d_media_movie_get_play_file_total_time(void) D_FUNCPOSTFIT;

/** @brief 获得媒体文件里的音频信息
*@param[out] 音频信息结构数组
*@param[in]  传入的结构数组长度
@retval 实际获得音频信息的数量, 失败返回小于0
*/
D_Result d_media_movie_get_audio_info(D_MovieAudioInfo *info, D_Size info_array_count) D_FUNCPOSTFIT;

/**@brief 选择音轨
*@param[in] 从音频信息里获得的音频索引值
*@retval 成功返回D_OK, 其它失败
*/
D_Result d_media_movie_select_audio(D_Int audio_index) D_FUNCPOSTFIT;

/**@brief 获取视频流畅状态
*@retval 成功返回D_OK, 其它失败
*/
D_Result d_media_movie_get_video_smooth(void) D_FUNCPOSTFIT;

/** @brief 获得媒体ts文件里的多频道信息
*@param[in/out] info D_PvrProgramInfo结构指针
*@retval 成功返回D_OK, 其它失败
*/
D_Result d_media_movie_get_ts_progs_info(D_Ptr info) D_FUNCPOSTFIT;

/**@brief EBK相关接口声明*/

/**@brief 初始化播放状态和ebk任务
*@retval 成功返回D_OK,失败返回D_ERR
*/
D_Result d_media_ebk_open(void) D_FUNCPOSTFIT;

/**@brief销毁ebk播放任务
*@retval 成功返回D_OK,失败返回D_ERR
*/
D_Result d_media_ebk_close(void) D_FUNCPOSTFIT;

/**@brief ebk文件播放
*@param[in] path:要播放的ebk文件的绝对路径
*@param[in] x,y,w,h:播放ebk图片的窗口位置大小
*@retval 成功返回D_OK,失败返回D_ERR
*/
D_Result d_media_ebk_play(D_Char* path, D_U32 x, D_U32 y, D_U32 w, D_U32 h) D_FUNCPOSTFIT;

/**@brief 停止ebk播放
*@retval 成功返回D_OK,失败返回D_ERR
*/
D_Result d_media_ebk_stop(void) D_FUNCPOSTFIT;

/**@breif 获取ebk当前状态
*@retval 返回值为结构体枚举值D_EbkStatus中的成员变量
*/
D_U8 d_media_ebk_get_status(void) D_FUNCPOSTFIT;

/**@breif 设置ebk按键操作
*@param[in] key:从页面上传过来的按键值设置到ebk解码文件中去
*@retval 成功返回D_OK
*/
D_Result d_media_ebk_set_key(D_U8 key) D_FUNCPOSTFIT;

/**@brief 取得字幕信息
* @param[in/out]  sub_text  保存字幕文本
* @param[in]  cnt  sub_text空间最大值
*@retval 有效返回值:-1 失败  0 与上次相同 1 成功
*/
int d_media_get_curr_subtitle(D_SubtitleInfo* sub) D_FUNCPOSTFIT;


#ifdef  __cplusplus
}
#endif
#endif

