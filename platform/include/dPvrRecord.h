/** @file dPvrRecord.h
* @brief pvr 录像模块
* PVR创建 功能录像功能
* @author 蔡刚
* @date 2013-11-28 蔡刚:创建文件 
*/

#ifndef _DPVR_RECORD_H_
#define _DPVR_RECORD_H_

#ifdef  __cplusplus
extern "C"
{
#endif
#include "dTypes.h"
#include "dSem.h"
#include "dApp.h"
#include "dPvrPorting.h"
#include "dPvrFileSort.h"

typedef enum {
	D_MSG_PVR_Record_Msg_NULL = -1,	
	D_MSG_PVR_Record_Timeout_Msg = 0xff5a0200,
	D_MSG_PVR_Record_Spackeout_Msg,
	D_MSG_PVR_Record_Fileeout_Msg,	
	D_MSG_PVR_Record_Forbid,
	D_MSG_PVR_Record_NavValue_OverFlow_Msg,	
	D_MSG_PVR_Record_Data_OverFlow_Msg,	
} D_PVR_Record_MsgType;

// 录像过程中维护的结构体
// 在sdram中临时存放导航数据的个数
// 录像时: 当条目数达到128个后，将其写入导航文件中
typedef struct  __str_rec_info
{
	// 缓冲区
	D_U32 buffer[NAV_NUM_PER_BUFF];
	// 当前缓冲区中活动的导航条目号
	D_U8 buff_act_index;
	// 当前活动的导航条目号(0~一共导航点数)
	// 这个变量也可以看成是当前一共录制的导航点数
	// .info 文件的头部记录了该值
	D_U32 act_index;   

} str_rec_info;


/*录像任务的所有数据*/
typedef struct __D_PvrRecordData
{
	//
	D_HApp	hpvr_record;
	D_PvrHandle	dev_id;	
	D_HQueue guiqueue;

	//录像缓冲区寄存器和导航寄存器配置
	D_Bool recbuf_use_sys;  /**< 录像缓冲区是否使用程序分区 */
	D_U32 recbuf_addr ;//       
	D_U32 recbuf_physaddr;  /**< 录像缓冲区物理地址, 驱动使用 */
    D_U8 *recbuf_align_addr;
	D_U32 recbuf_size;//
	D_Bool drmbuf_use_sys;  /**< DRM缓冲区是否使用程序分区 */
    D_Ptr drmbuf_addr;  /**< DRM缓冲区, 16字节对齐 */
    D_Ptr drmbuf_physaddr;
    D_U8 *drmbuf_align_addr;
    D_U32 drmbuf_size;
    D_U32 recbuf_int_value;//
	D_U32 rec_nav_int_value;//

	//原来的PVR_REC_PARA结构体
//	HI_U32	min_nav_len;		
//	HI_U32 	min_rec_len;
//	HI_U32 	pvr_rec_buf_base;
//	HI_U32 	pvr_rec_buf_len;
	D_U16	pvr_rec_pid[24];
	PVR_CH_OUT_MODE	channel_out_mode;
	PVR_REC_NAV_TYPE	pvr_rec_nav_type[4];	//0x00-- mpeg nav, 0x01-- h264 nav, 0x02-- avs nav, 0x03-- user define
	D_U8  	pvr_rec_cw[8];
	D_U8	rec_tv_num;
	D_U8	rec_interrupt_state;

	//原来的info文件结构体

	/* 录放像共有的*/
	D_U8 is_scrambled;
	// 录像时所用的通道号0~3
	// 设置视频pid 的通道号记录在这
	D_U8 channel_no; 
	D_U8 pvr_state;

		// 所录节目的视频格式 0=MPEG2,1=h264,2=AVS
	D_U8 video_stream_type:4;
	// 音频流的格式1=MPEG1, 2=MPEG2, 3=AAC, 4=AC3
	D_U8 audio_stream_type:4;

	// PVR文件是否锁定
	D_U8 is_locked;
	// pid 维护
//	D_U8 pid_arr[PVR_PID_TOTAL];
	u_pid pid_arr[PVR_PID_TOTAL];

	// 时间
	str_time start_time;
	str_time end_time;
	D_U32 drt_time;  // 持续时间,单位秒
	// like "CCTV4"
	D_S8 pro_name[PROGRAM_NAME_LENGTH];
	// like "CCTV4_20110513132727"
	D_S8 dir_name[DIR_NAME_LENGTH]; 
	// like "C:/AVDATA/CCTV4_20110513132727"
	D_S8 dir_path[REC_FILEPATH_LENGTH_MAX];
	// 文件大小
	D_U32 file_size; 
	// 指向存放该录制节目ts流文件的指针
	D_FsoutFile * ts_file_p;
	// 指向存放该录制节目导航信息文件的指针
	D_FsoutFile * nav_file_p;
	// 指向存放该录制节目信息文件的指针
	D_FsoutFile * info_file_p;
	/* 录像过程中维护的*/
	// 录像导航信息指针。
	str_rec_info * rec_nav_info_p;
	/* 放像过程中维护的*/
	// 放像导航信息指针
//	str_rep_info * rep_nav_info_p;
//	str_rep_info * storebuf_rep_info_p;
	// 放像书签指针
//	str_book_mark * rep_bookmark_p;
    D_Handle pvr_rec_int_handle;
    D_HSem Pvr_Rec_IntSemaphore;
    D_U32 pvr_rec_support_max_duration_sec;  /**< pvr录像支持最长时间, 秒单位 */
    D_U32 pvr_rec_support_min_disk_space;  /**< pvr录像支持最小磁盘空间 */
    D_S64 pvr_rec_support_max_file_size;  /**< pvr录像支持最大文件尺寸 */
    D_Bool need_drm;  /**< 是否使用DRM加密 */
    D_U8 drm_key[32];
    D_Handle hdrm;
    D_Bool rec_osd_msg; /*是否记录osd, 目前驱动里只进行文件创建，记录在应用里进行*/    
    D_Bool is_timeshift; /*纯时移标志*/
}D_PvrRecordData;



// 录放时要保存的当前节目信息的结构体
// 有待与继续添加
typedef	struct
{
	/* 录放像共有的*/
	D_U8 is_scrambled;
	// 录像时所用的通道号0~3
	// 设置视频pid 的通道号记录在这
	D_U8 channel_no; 
	D_U8 pvr_state;


		// 所录节目的视频格式 0=MPEG2,1=h264,2=AVS
	D_U8 video_stream_type:4;
	// 音频流的格式1=MPEG1, 2=MPEG2, 3=AAC, 4=AC3
	D_U8 audio_stream_type:4;
	
	D_U16	pvr_rec_pid[24];
	PVR_CH_OUT_MODE	channel_out_mode;
	PVR_REC_NAV_TYPE	pvr_rec_nav_type[4];	//0x00-- mpeg nav, 0x01-- h264 nav, 0x02-- avs nav, 0x03-- user define
	D_U8  	pvr_rec_cw[8];
	D_U8	rec_tv_num;
	D_U8	rec_interrupt_state;

	// PVR文件是否锁定
	D_U8 is_locked;
	// pid 维护
	u_pid pid_arr[PVR_PID_TOTAL];
	// 时间
	str_time start_time;
	str_time end_time;
	D_U32 drt_time;  // 持续时间,单位秒
	// like "CCTV4"
	D_S8 pro_name[PROGRAM_NAME_LENGTH];
	// like "AVDATA"
	D_S8 dir_name[DIR_NAME_LENGTH]; 
	// like "C:/"
	D_S8 dir_path[REC_FILEPATH_LENGTH_MAX];
	// 文件大小
	D_U32 file_size;

    D_U32 pvr_rec_support_max_duration_sec;  /**< pvr录像支持最长时间, 秒单位 */
    D_U32 pvr_rec_support_min_disk_space;  /**< pvr录像支持最小磁盘空间 */
    D_S64 pvr_rec_support_max_file_size;  /**< pvr录像支持最大文件尺寸 */

    D_Bool need_drm;  /**< 是否使用DRM加密 */
    D_U8 drm_key[32];
    D_Bool rec_osd_msg;/*是否记录osd, 目前驱动里只进行文件创建，记录在应用里进行*/  
    D_Bool is_timeshift; /*时移标志*/
    D_U32  timeshift_nav_file_save_max;/*时移时导航文件保存的最大导航条目数*/
} str_pvr_rec_config_info;

D_Result	d_pvr_rec_open(void)D_FUNCPOSTFIT;
D_Result	d_pvr_rec_close(void)D_FUNCPOSTFIT;
D_Result 	d_pvr_rec_start(D_Handle handle)D_FUNCPOSTFIT;
D_Result 	d_pvr_rec_pause(D_Handle handle)D_FUNCPOSTFIT;
D_Result 	d_pvr_rec_resume(D_Handle handle)D_FUNCPOSTFIT;
D_Result 	d_pvr_rec_stop(D_Handle handle)D_FUNCPOSTFIT;
D_HApp d_pvr_rec_create_ex(D_HQueue guiqueue, str_pvr_rec_config_info *config) D_FUNCPOSTFIT;
#define d_pvr_rec_create(_a1_, _a2_)    d_pvr_rec_create_ex((_a1_), &(_a2_))
D_Result d_pvr_rec_destroy(D_Handle handle) D_FUNCPOSTFIT;

/** @brief PVR设置录像时间
* @param[in]	handle  PVR句柄
* @return  成功返回D_OK, 失败返回D_ERR
*/
D_Result d_pvr_rec_set_total_time(D_Handle handle, D_Time rec_total_time) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif

