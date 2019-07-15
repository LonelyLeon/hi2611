/** @file dpvr_replay.c
* @brief pvr 播放 模块
* PVR创建 功能控制 播放 快放 慢放 回放
* @author 于龙朕 刘行
* @date 2013-11-28 于龙朕: 建立文件        
*/

#ifndef _DPVR_REPLAY_H_
#define _DPVR_REPLAY_H_

#ifdef  __cplusplus
extern "C"
{
#endif
#include "dTypes.h"
#include "dPvrPorting.h"
#include "dSem.h"
#include "dFileSystem.h"

#define MAX_FILE_PATH_LENGTH (MAX_PATH)
#define MAX_FILE_NAME_LENGTH (MAX_PATH)
#define ONE_NAV_LENGTH		 (4)
#define PMT_MAX (128)
#define PVR_REP_AUD_LANGUAGE_LENGTH 4
#define PVR_REP_AUD_MAX      7

typedef D_Handle D_HPvrRep;

/** @brief PVR放像创建参数 */
typedef struct
{
    D_ID id;  /**< PVR放像使用的设备id */
}D_PvrRepPlayerAttr;

/** @brief 按缺省值初始化PVR放像参数*/
#define D_PVRREP_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
	D_MACRO_END

/*放像速度类型*/
typedef enum{
	FORWARD_1_16PIX,
	FORWARD_1_8PIX,
	FORWARD_1_4PIX,	
	FORWARD_1_2PIX,
	FORWARD_1PIX,
	FORWARD_2PIX,
	FORWARD_4PIX,	
	FORWARD_8PIX,
	FORWARD_16PIX,
	FORWARD_32PIX,
	BACKWARD_2PIX,	
	BACKWARD_4PIX,
	BACKWARD_8PIX,
	BACKWARD_16PIX,
	BACKWARD_32PIX,	
}D_SpeedType;

/*当前导航信息*/
typedef struct
{
	D_SpeedType speed_type;			//当前速度
	D_S32		step;				//当前导航信息	
	D_U32		fact_index;			//当前实际解帧索引号
	D_U32		current_index;		//已拷贝的I帧的索引号
	D_U32		total_index;		//一共多少条导航信息
	D_U32		sectors_remain;		//上一帧剩余字节大小
}D_NavInfo;

/*文件信息*/
typedef struct
{
	D_Handle handle;	
	D_U64	filesize;
}D_PvrRepFile;

/*PVR单元信息*/
typedef struct
{
	D_S8			filepath[MAX_FILE_PATH_LENGTH];
	D_S8			filename[MAX_FILE_NAME_LENGTH];
	D_U32			total_time;
	D_PvrRepFile 	ts_file;			//放像文件结构体
	D_PvrRepFile 	nav_file;			//导航文件结构体
	D_PvrRepFile 	info_file;			//信息文件结构体	
}D_PvrRepUnit;

/*任务配置参数*/
typedef enum
{
	PVR_INVALID,
	PVR_READY_OK = 1,
	PVR_PLAYING,
	PVR_STOP,
	PVR_PAUSE,
}D_PvrTaskState;

/* pvr放像TS源的类型 */
typedef enum
{
	PVR_REP_HAIER_TS = 0,	//原始ts码流类型
	PVR_REP_NORMAL_TS,	//正常录制码流类型
	PVR_REP_PVR_TIMESHIFT_TS,	//pvr(边录边播放)类型
	PVR_REP_TIMESHIFT_TS,	//纯时移播放类型
	PVR_REP_SPECIFIED_AVPID_TS,	//特定音视频pid播放类型，即ts文件里没有PAT PMT等信息
}D_PvrTsType;

typedef struct
{
    D_U16 aud_pid;
    D_AudCodecType aud_codec;
    D_Char language[PVR_REP_AUD_LANGUAGE_LENGTH];
}D_PvrAudInfo;

/* pvr解析清流时数据类型 */
typedef struct{
	D_U16 PMT_pid;
    D_U16 pcr_pid;
	D_U16 vid_pid;
	D_U8  vid_codec;
    D_PvrAudInfo aud_info[PVR_REP_AUD_MAX];
}D_SiProgramInfo;

/**@brief ts频道信息 */
#define PVR_TS_PROG_CNT (64)
typedef struct
{
    D_U16   prog_cnt;
    D_U16   play_idx;
	D_SiProgramInfo prog_info[PVR_TS_PROG_CNT];
}D_PvrProgramInfo;


/*任务配置参数*/
typedef struct
{
	D_S8		filepath[MAX_FILE_PATH_LENGTH];
	D_S8		filename[MAX_FILE_NAME_LENGTH];
	D_U8		Read_ok;
	D_PvrTsType	ts_type;		//源数据类型	
	D_PvrRepTsParm ts_param;	//源文件参数
    D_U8 drm_key[32];
	D_U32       prog_num;       //播放第几路节目    
}D_PvrRepTaskConfig;

/**@brief PVR 解析码流给GUI层回调用的结构体*/
typedef struct
{
	/*callback 给菜单提示信息使用*/
	D_U8 pvr_ts_parse_res;/*解析出错类型*/
	D_Char path[256]; /*解析文件全路径名称*/
}D_Pvr_Cb;


/*播放任务的所有数据*/
typedef struct
{
	D_HPvrRep		hpvr_replay;	/*放像任务的句柄*/
	D_PvrHandle		dev_id;			/*放像设备号*/		

	D_U32 		rep_buff_wp;				/*放像缓存区的地址*/
    D_Bool      rep_buff_use_sys;
	D_U32 		rep_buff_baseaddr;			/*放像缓存区的基地址*/
	D_U32       rep_buff_physaddr;  		/**< 驱动使用的物理地址 */
    D_U32       rep_buff_size;
    D_U8        *rep_buff_align_addr;
    D_Bool      drm_buff_use_sys;
    D_U32 		drm_buff_baseaddr;			/*放像缓存区的基地址*/
	D_U32       drm_buff_physaddr;  		/**< 驱动使用的物理地址 */
    D_U32       drm_buff_size;
    D_U8        *drm_buff_align_addr;
	D_PvrIntReason		PvrReplayIntStatus;	/*记录放像任务底层中断状态*/	
	D_PvrRepTsParm 		ts_parm;			/*记录ts流参数，用于播放有上层菜单传入*/	
	D_PvrRepUnit 		file;				/*记录当前播放的单元所有文件参数，句柄、大小、名称、路径等*/
	D_Bool				enable_nav;			//是否使用导航文件，在填充放像缓存区计算读取文件偏移
	D_NavInfo 			nav_info;			//导航信息
	D_U32 				av_play_state;		/*记录当前av播放状态*/
	D_PvrTaskState		state;				/*记录放像任务播放状态*/
	D_PvrTsType	 		ts_type;			/*当前播放ts流时无导航ts清流、还是正常录制单元流*/
	D_PvrRepTaskConfig	config;				/*记录切换播放单元的参数*/
	D_Bool				need_sys;			/*正在解析放像单元设置参数时，切换节目可通过此标志来结束当前解析，立即换台效果*/
	D_Bool				disable_blank;		/*记录当前是否黑屏状态*/
	D_SiProgramInfo 	pvr_program[PMT_MAX];/*包含多节目ts中所有节目信息*/
    D_U32               pvr_program_count;  /* 码流中实际包含PMT数量 */
    D_U32               pvr_play_count;     /* 当前播放的节目索引 */
    D_Handle            av_evt_handle;		/*av事件回调函数的句柄*/
    D_Handle            pvr_rep_int_handle;	/*中断事件回调句柄*/
    D_HSem              Pvr_Replay_IntSemaphore;/*放像任务数据请求、中断信号量*/
    D_S64               ts_read_limit; /* 分析ts数据允许读取的最大文件长度 */
    D_Handle            hdrm;  /* DRM设备句柄 */
    D_Bool              need_drm;
    struct
    {
        D_U32   last_eof_time;
        D_U32   last_vid_cnt;
        D_U32   last_aud_cnt;
    }ts_end_control;
    D_PvrRepPlayerAttr attr;
    D_U64 timeshift_read_offset;
    D_PvrProgramInfo pvr_program_info;
}D_PvrReplayData;

/** @brief 打开PVR放像相关资源 */
D_Result	d_pvr_rep_open(void)D_FUNCPOSTFIT;

/** @brief 关闭PVR相关资源 */
D_Result	d_pvr_rep_close(void)D_FUNCPOSTFIT;

/** @brief 创建放像任务*/
D_Result    d_pvr_rep_create_ex(D_PvrRepPlayerAttr *attr) D_FUNCPOSTFIT;
#define d_pvr_rep_create()    d_pvr_rep_create_ex(NULL)

/** @brief 销毁放像任务 */
D_Result  	d_pvr_rep_destroy(D_HPvrRep handle)D_FUNCPOSTFIT;

/** @brief 启动放像功能 */
D_Result 	d_pvr_rep_start(D_HPvrRep handle)D_FUNCPOSTFIT;

/** @brief 	暂停*/
D_Result 	d_pvr_rep_pause(D_HPvrRep handle)D_FUNCPOSTFIT;

/** @brief 继续播放 */
D_Result 	d_pvr_rep_resume(D_HPvrRep handle)D_FUNCPOSTFIT;

/** @brief 重新播放 */
D_Result 	d_pvr_rep_restart(D_HPvrRep handle)D_FUNCPOSTFIT;

/** @brief 停止 */								
D_Result 	d_pvr_rep_stop(D_HPvrRep handle)D_FUNCPOSTFIT;

/** @brief 前进 */
D_Result 	d_pvr_rep_forward_ex(D_HPvrRep handle, D_SpeedType speed_flag, D_U32 param)D_FUNCPOSTFIT;
#define d_pvr_rep_forward(_handle, _speed) d_pvr_rep_forward_ex(_handle, _speed, 0)

/** @brief 后退*/
D_Result 	d_pvr_rep_backward_ex(D_HPvrRep handle, D_SpeedType speed_flag, D_U32 param)D_FUNCPOSTFIT;
#define d_pvr_rep_backward(_handle, _speed) d_pvr_rep_backward_ex(_handle, _speed, 0)

/** @brief 设置PVR参数 */
D_Result 	d_pvr_rep_set_param_ptr(D_HPvrRep handle,D_PvrRepTaskConfig *config)D_FUNCPOSTFIT;

#define d_pvr_rep_set_param(__h, __t)   d_pvr_rep_set_param_ptr((__h), &(__t))

/** @brief 得到PVR状态 */
D_PvrTaskState d_pvr_rep_get_state(D_HPvrRep handle)D_FUNCPOSTFIT;

/** @brief 得到当前已播放时间 */
D_U32 	d_pvr_rep_get_time(D_HPvrRep handle)D_FUNCPOSTFIT;

/** @brief 得到播放总时间 */
D_U32 	d_pvr_rep_get_total_time(D_HPvrRep handle)D_FUNCPOSTFIT;

/** @brief 得到当前播放ts文件大小*/
D_U64 d_pvr_rep_get_file_size(D_HPvrRep handle)D_FUNCPOSTFIT;

/** @brief 		PVR跳转播放
* @param[in]	jump_value 跳转的时间值
* @param[in]	handle 任务句柄
* @return 		成功D_OK,失败返回D_ERR
*/
D_Result d_pvr_rep_set_jump(D_HPvrRep handle, D_U32 jump_value)D_FUNCPOSTFIT;

/** @brief 取到ts文件里音频信息, 只有播放标准ts流文件可用, hts文件不适应
*@param[in] pvr放像句柄
@retval 音频信息结构数组
*/
D_PvrAudInfo *d_pvr_rep_get_aud_info(D_HPvrRep handle) D_FUNCPOSTFIT;

/**@brief 选择一路音频播放
*@param[in] pvr放像句柄
*@param[in] 音频索引
*@retval 成功返回D_OK, 其它失败
*/
D_Result d_pvr_rep_select_audio(D_HPvrRep handle, D_Int audio_index) D_FUNCPOSTFIT;

/** @brief 取到ts文件里多频道信息, 只有播放标准ts流文件可用, hts文件不适应
*@param[in] pvr放像句柄
@param[in/out] proginfo 多频道信息
* @return       成功返回D_OK,失败返回D_ERR
*/
D_Result d_pvr_rep_get_progs_info(D_HPvrRep handle, D_PvrProgramInfo *proginfo) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif
 
