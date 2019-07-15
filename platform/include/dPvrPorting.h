/** @file dPvrPorting.h 
* @brief PVR驱动提供给中间件的Porting接口
* @author 唐义平
* @date 2013-11-05 tangyp: 建立文件
*/
#ifndef _DPVR_PORTING_H_
#define _DPVR_PORTING_H_

#ifdef  __cplusplus
extern "C"
{
#endif
#include "dTypes.h"
#include "dAV.h"

typedef D_Handle	D_PvrHandle;

#define D_PVR_REP_DEV_CNT						(1)		/* device number, it is zero now */

#define NAV_NUM_PER_BUFF	(128)
#define ONE_NAV_LENGTH		 (4)

#define HAIER_TS_EXT_NAME   "hts"
#define HAIER_TIMESHIFT_TS_EXT_NAME   "tfts"
#define HAIER_PVR_FOLDER   "AVDATA"
#define HAIER_TIMESHIFT_TS_FILE_NAME   "timeshift"


/***@brief PVR底层中断类型状态*/
typedef enum
{
    D_PvrInt_Null = 0,
    D_PvrInt_RecDataReady = 0x00000001,
    D_PvrInt_RecNavReady = 0x00000002,
    D_PvrInt_RecDataOverflow = 0x00000004,
    D_PvrInt_RecNavOverflow = 0x00000008,
    D_PvrInt_RepDataRequest = 0x00000010,
    D_PvrInt_RepDataOverflow = 0x00000020,
}D_PvrIntMask;

typedef D_PvrIntMask D_PvrIntReason;

/**@brief PVR REC information struct*/                             
typedef struct                                   
{                                                
	                                         
	D_U32 recbuf_addr ;//                    
	D_U32 recbuf_size;//            
    D_U32 recbuf_int_value;//            
	D_U32 rec_nav_int_value;// 
                                         
}D_PvrRecSetRegValue;  
/***@brief 操作缓存区内存*/
typedef enum
{
	NAV_BUF,
	REC_BUF,
	REP_BUF,
}D_PvrBufType;

/***@brief 设备号*/
typedef enum
{
	TV0,
	TV1,
	TV_MAX,
}D_TV_DEV;

typedef struct
{
	D_S32 id;
}D_PvrRepAttr;
/***@brief 放像流的音、视频、同步pid*/
typedef struct
{
	D_U32 v_pid;
	D_U32 a_pid;
	D_U32 pcr_pid;	
}D_PvrRepPid;

/*PVRts信息*/
typedef struct
{
	D_PvrRepPid pid;
	D_U8 		scramble_flag;
	D_U8 		whole_freq_flag;
	D_U8 		audio_decode_type;
	D_U8 		video_decode_type;	
    D_AVSyncType type; /**< 同步类型*/	
}D_PvrRepTsParm;
/***@brief 放像设置参数*/
typedef struct                                   
{                                                	                                         
	D_U32 repbuf_baseaddr ; 	
	D_U32 repbuf_offsetaddr ;                   
	D_U32 repbuf_size;
	D_U32 min_rep_len;	
	D_U32 min_vcd_space;         		                          	
	D_U32 min_acd_space;	
    D_U32 TV_num;
	D_U32 rep_interrupt_state;
    D_PvrRepPid pid;					/* pid for av player */    	
}D_PvrRepSetRegValue; 

/**@brief PVR REP information struct*/  
typedef struct                                   
{                             
	D_ID		id;						/* device id, it is use for making a distinction of different devices */
	D_PvrRepSetRegValue param;			/* device param */
}D_PvrRepDev;  

typedef enum
{
	PVR_OUT_ES_OF_PES = 0,
	PVR_OUT_SUB_TITLE = 1,
	PVR_OUT_TS_PID = 2,
	PVR_OUT_PES = 3,
	PVR_OUT_TOTAL_TS = 6,
}PVR_CH_OUT_MODE;


typedef enum
{
	REC_MPEG_NAV_TYPE			= 0,
	REC_H264_NAV_TYPE			= 1,
	REC_AVS_NAV_TYPE			= 2,
	REC_USER_DEFINE_NAV_TYPE	= 3,	
} PVR_REC_NAV_TYPE;

/*录像时相关信息记录*/
typedef struct
{
    D_U32 pvr_rec_dur_time_ms;/*已录制数据大小*/
    D_U64 pvr_rec_total_size;/*已录制数据大小*/
    D_U64 pvr_rec_file_size;/*文件已写空间*/
    D_U64 pvr_rec_file_max_size; /*文件最大空间*/
    D_U32 pvr_rec_nav_cnt;  /*已记录的导航条目总数*/
    D_U32 pvr_rec_nav_save_cnt;  /*已存储在文件的导航条目总数*/
    D_U32 pvr_rec_nav_file_save_max;  /*存储在文件的导航条目最大数*/
    D_U32 pvr_rec_nav_data[NAV_NUM_PER_BUFF];
}D_PvrRecInfo;


D_Result 	d_pvr_porting_open(void)D_FUNCPOSTFIT;

D_Result	d_pvr_porting_rec_open(void)D_FUNCPOSTFIT;	
D_Result	d_pvr_porting_rec_close(void)D_FUNCPOSTFIT;                 
D_PvrHandle d_pvr_porting_rec_create(D_U8 TV_num, D_PvrRecSetRegValue rec_reg_value)D_FUNCPOSTFIT;        
D_Result  	d_pvr_porting_rec_destroy(D_PvrHandle handle)D_FUNCPOSTFIT;                                                                
D_Result 	d_pvr_porting_rec_set(D_PvrHandle handle, D_U16 *pid,D_U8 *cw,D_U8 *nav_type, D_U8 scramble_flag, D_U8 whole_freq_flag)D_FUNCPOSTFIT;         
D_PvrIntMask d_pvr_porting_get_rec_int_status(D_PvrHandle handle)D_FUNCPOSTFIT;                 
D_Result 	d_pvr_porting_get_recbuf_data(D_PvrHandle handle, D_U32 *buf, D_U32 *size, D_PvrBufType buf_type)D_FUNCPOSTFIT;             
D_Result    d_pvr_porting_set_recrp(D_PvrHandle handle,D_U32 length)D_FUNCPOSTFIT;
D_Result 	d_pvr_porting_set_navrp(D_PvrHandle handle,D_U32 length)D_FUNCPOSTFIT;                    
D_Result 	d_pvr_porting_rec_stop(D_PvrHandle handle)D_FUNCPOSTFIT;                                                      
D_Result    d_pvr_porting_rec_start(D_PvrHandle handle, D_U16 *pid,D_U8 *cw,D_U8 *nav_type, D_U8 scramble_flag, D_U8 whole_freq_flag)D_FUNCPOSTFIT;
D_Result    d_pvr_porting_rec_restart(D_PvrHandle handle) D_FUNCPOSTFIT;
D_Result    d_pvr_porting_rec_nav_enable(D_PvrHandle handle, D_Bool en) D_FUNCPOSTFIT;
D_Result 	d_pvr_porting_reset_rec_int_status(D_PvrHandle handle, D_PvrIntMask mask)D_FUNCPOSTFIT;

/*打开放像任务资源*/						
D_Result 	d_pvr_porting_rep_open(void)D_FUNCPOSTFIT;

/* 关闭放像任务资源*/
D_Result	d_pvr_porting_rep_close(void)D_FUNCPOSTFIT; 

/* 创建放像任务，包括初始化放像状态*/
D_Result 	d_pvr_porting_rep_create(D_PvrRepAttr attr,D_PvrRepDev *repdev)D_FUNCPOSTFIT;

/* 销毁放像相关资源、复位pvr放像相关寄存器状态*/
D_Result 	d_pvr_porting_rep_destroy(D_PvrHandle handle)D_FUNCPOSTFIT;

/* 设置放像参数，音视频pid、是否加密*/
D_Result 	d_pvr_porting_rep_set(D_PvrHandle handle, D_PvrRepPid *pid,D_U8 scramble_flag,D_U8 whole_freq_flag)D_FUNCPOSTFIT;

/* 得到放像中断请求状态*/
D_PvrIntMask d_pvr_porting_get_rep_int_status(D_PvrHandle handle)D_FUNCPOSTFIT; 

/* 复位放像中断请求状态*/
D_Result 	d_pvr_porting_reset_rep_int_status(D_PvrHandle handle, D_PvrIntMask mask)D_FUNCPOSTFIT;

/* 得到放像缓冲区数据，请求剩余空间数据大小、地址*/
D_Result 	d_pvr_porting_get_repbuf_data(D_PvrHandle handle,D_U32 *buf, D_U32 *size,D_PvrBufType buf_type,D_U8 speed_flag)D_FUNCPOSTFIT; 

/** @brief  得到放像缓冲区未读的数据量大小*/
D_U32 d_pvr_porting_get_repbuf_data_length(D_PvrHandle handle)D_FUNCPOSTFIT;

/* 更新放像缓冲区数据写指针*/
D_Result 	d_pvr_porting_set_repwp(D_PvrHandle handle,D_U32 length)D_FUNCPOSTFIT;   

/* 复位当前播放I帧计数*/
D_Result 	d_pvr_porting_set_IFrame_count(D_PvrHandle handle,D_U32 count)D_FUNCPOSTFIT;

/* 得到当前播放I帧计数*/
D_U32 		d_pvr_porting_get_IFrame_count(D_PvrHandle handle)D_FUNCPOSTFIT;

/* 停止播放*/
D_Result 	d_pvr_porting_rep_stop(D_PvrHandle handle)D_FUNCPOSTFIT;                        

/* 开始播放*/
D_Result 	d_pvr_porting_rep_start(D_PvrHandle handle, D_PvrRepTsParm *ts_parm)D_FUNCPOSTFIT;

/* 暂停播放*/
D_Result 	d_pvr_porting_rep_pause(D_PvrHandle handle)D_FUNCPOSTFIT;

/* 恢复播放*/
D_Result 	d_pvr_porting_rep_resume(D_PvrHandle handle)D_FUNCPOSTFIT; 

/* 重新播放*/
D_Result 	d_pvr_porting_rep_restart(D_PvrHandle handle)D_FUNCPOSTFIT; 

/*跳过VCD中数据*/
D_Result d_pvr_porting_rep_jump(D_PvrHandle handle, D_PvrRepTsParm *ts_parm)D_FUNCPOSTFIT;

/* 快进*/
D_Result 	d_pvr_porting_rep_forward(D_PvrHandle handle,D_U8 speed_flag, D_Bool simple)D_FUNCPOSTFIT;

/* 快退*/
D_Result 	d_pvr_porting_rep_backward(D_PvrHandle handle,D_U8 speed_flag, D_Bool simple)D_FUNCPOSTFIT;         

/** @brief  得到放像缓冲区未读的数据量大小*/
D_U32 d_pvr_porting_get_repbuf_data_length(D_PvrHandle handle)D_FUNCPOSTFIT;

/** @brief  PVR放像时取得acd 或vcd 的已有数据长度*/
D_U32 d_pvr_porting_get_repavcd_data_len(D_PvrHandle handle, D_U32 aorv, D_U32 *size)D_FUNCPOSTFIT;

#ifdef  __cplusplus
}

#endif

#endif
