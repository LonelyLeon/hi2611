/** @file
* @brief PVR单元的解析：.info,.nav,.ts文件的解析及保存
* @author:liux
* @date 2013-12-07 liux: 建立文件
*/

#ifndef _DPVR_FILESORT_H_
#define _DPVR_FILESORT_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"


typedef D_U8  			pvr_u8;
typedef char			pvr_char;
typedef D_U16			pvr_u16;
typedef unsigned int	pvr_u32;
typedef int				pvr_int;



#define PROGRAM_NAME_LENGTH						32 
#define DIR_NAME_LENGTH							128  // (PROGRAM_NAME_LENGTH + TIME_STR_LENGTH)
// 录像文件路径的最大长度// like "C:/AVDATA/CCTV4_201105131327" is 28
#define REC_FILEPATH_LENGTH_MAX					1024

#define REC_CHANNEL_NUM							24
#define FILE_PATH_MAX							1024
#define FILE_NAME_MAX							256	


#define PVR_DATA_BUFF_SIZE								1024


// info 文件中各数据段位置定义
// 以下定义512字节为info 文件的头信息
#define HEADTAG_OFFSET								0
#define HEADTAG_LENGTH								9	// INFOFILE+字符串结束标志
#define FILENAME_OFFSET								(HEADTAG_OFFSET + HEADTAG_LENGTH)    
#define FILENAME_LENGTH								50	// CCTV4_201110100859
#define RECTIME_OFFSET								(FILENAME_OFFSET +  FILENAME_LENGTH)
#define RECTIME_LENGTH								21	//38  20111010085959_20111010105959_00007200
#define FILESIZE_OFFSET								(RECTIME_OFFSET +  RECTIME_LENGTH)
#define FILESIZE_LENGTH								4	// u32
#define SCRAMBLE_OFFSET								(FILESIZE_OFFSET + FILESIZE_LENGTH)  
#define SCRAMBLE_LENGTH								1    // 1
#define LOCKED_OFFSET								(SCRAMBLE_OFFSET + SCRAMBLE_LENGTH)
#define LOCKED_LENGTH								1
#define PID_OFFSET									(LOCKED_OFFSET + LOCKED_LENGTH)
#define PID_PER_LENGTH								4
#define PID_LENGTH									(total_pid *PID_PER_LENGTH)
#define LASTPOINT_OFFSET							(PID_OFFSET + PID_LENGTH)
#define LASTPOINT_LENGTH							4 // u32
#define NAV_TOTAL_OFFSET							(LASTPOINT_OFFSET + LASTPOINT_LENGTH)					
#define NAV_TOTAL_LENGTH							4 // u32 
#define INFOFILE_HEADER_LENGTH						512   // to be continue


//struct __D_PvrRecordData;

// 日期时间结构体
typedef struct
{
	pvr_u16 year;
	pvr_u8 month;
	pvr_u8 day;
	pvr_u8 hour;
	pvr_u8 minute;	
	pvr_u8 second;
	//pvr_u8 reserved[RECTIME_LENGTH-11];
}str_time;
typedef struct
{
	str_time start_time;
	str_time end_time;
	pvr_u32 last_second;
}str_time_info;


// PVR中PID的维护
typedef struct
{
	// 当前的pid 是否有效
	pvr_u8 pid_valid : 1;
	// 当前pid 的类型，参考e_pid_type
	pvr_u8 pid_type : 7;
	// 当前pid 的值
	pvr_u16 pid_value : 13;
	// 数组中下一个元素是否存在
	pvr_u16 pid_next : 3;

} str_pid;
// 将pid 这个结构体同u32 组成一个联合体
// 方便数据向缓冲区中写入写出
typedef union 
{
	str_pid pid_str;
	pvr_u32 pid_str_value;

} u_pid;

// pid 的类型定义
typedef enum
{
	PVR_VEDIO_PID,
	PVR_AUDIO_PID,
	PVR_PCR_PID,
	
	PVR_PID_TOTAL = REC_CHANNEL_NUM,

} e_pid_type;

typedef enum
{
	pvr_file_info,
	pvr_file_nav,
	pvr_file_ts,
	pvr_file_timeshift_ts,
	pvr_file_caosdinfo, //wangyq  20140613  16:59
	pvr_file_total,
	
} pvr_file_kind_e;



typedef struct
{
	char head_tag[HEADTAG_LENGTH];
	char file_name[FILENAME_LENGTH];
	str_time_info time_info;//38*8
	pvr_u32 file_size;
	pvr_u8 is_scrambled : 4;
    pvr_u8 use_drm : 4;
	pvr_u8 format; //is_locked;
	pvr_u8 video_stream_type:4; // 所录节目的视频格式 0=MPEG2,1=h264,2=AVS
	pvr_u8 audio_stream_type:4; // 音频流的格式1=MPEG1, 2=MPEG2, 3=AAC, 4=AC3
	u_pid pid_arr[PVR_PID_TOTAL];
	pvr_u32 last_point;
	pvr_u32 nav_total;

}str_info_header;

// 书签的处理是这样的: .info 文件的第二个512 字节存放书签信息
// 书签头(记录书签的个数:4  字节) +   127*每个书签项(4字节)
// 放像启动时:将.info文件中的书签项写入内存，在内存中用
// 单链表维护书签，该单链表的节点是以节点的值(nav_index) 
// 从小到大排列的，当要添加一个新的书签时(按bookmark键)，
// 查看该书签是否在链表中，有:则删除该节点(删除一个书签)
// 没有:将该书签添加的合适的位置，更新bookmark_num
// ALI中会将更改过的马上写入文件中，可以参考这样做，或者在
// 某个时刻更新回.info 文件中
// 定义书签节点
typedef struct bookmark
{
	// 记录当前书签对应的导航点的序号
	pvr_u32 nav_index;
	// 指向下一个书签
	struct bookmark * next;

}node_bookmark;

// 书签结构体
typedef struct
{
	// 书签单链表发生变化标记，当当前的变化已经写入.info文件后将该标记清除
	pvr_u8 bookmark_chg;
	// 书签的个数
	pvr_u32 bookmark_num;
	// 总是指向书签单链表的第一个书签节点
	node_bookmark * bookmark_first;
	// 当前的书签节点
	// 对当前播放框不曾退出和书签链表没有做过变动时bookmark_currt为有效的
	// 否则bookmark_currt总是等于bookmark_first
	node_bookmark * bookmark_currt;	

}str_book_mark;

// 定义不区分文件系统的文件结构体
typedef struct
{
	D_U32	curp_write;
	D_U32	curp_read;
	
	D_S8	filename[FILE_NAME_MAX];
	D_U8	type;
	D_U32	filesize;
	void* 	file_p; // 指向具体文件系统文件的指针
	D_Handle handle;
}D_FsoutFile;

struct __str_rec_info;

// 录放时要保存的当前节目信息的结构体
// 有待与继续添加
typedef	struct
{
	/* 录放像共有的*/
	pvr_u8 is_scrambled;
	// 录像时所用的通道号0~3
	// 设置视频pid 的通道号记录在这
	pvr_u8 channel_no; 
	pvr_u8 pvr_state;


	// 所录节目的视频格式 0=MPEG2,1=h264,2=AVS
	pvr_u8 video_stream_type:4;
	// 音频流的格式1=MPEG1, 2=MPEG2, 3=AAC, 4=AC3
	pvr_u8 audio_stream_type:4;

	// PVR文件是否锁定
	pvr_u8 is_locked;
	// pid 维护
	u_pid pid_arr[PVR_PID_TOTAL];
	// 时间
	str_time start_time;
	str_time end_time;
	pvr_u32 drt_time;  // 持续时间,单位秒
	// like "CCTV4"
	pvr_char pro_name[PROGRAM_NAME_LENGTH];
	// like "CCTV4_20110513132727"
	pvr_char dir_name[DIR_NAME_LENGTH]; 
	// like "C:/AVDATA/CCTV4_20110513132727"
	pvr_char dir_path[REC_FILEPATH_LENGTH_MAX];
	// 文件大小
	pvr_u32 file_size; 
	// 指向存放该录制节目ts流文件的指针
	D_FsoutFile * ts_file_p;
	// 指向存放该录制节目导航信息文件的指针
	D_FsoutFile * nav_file_p;
	// 指向存放该录制节目信息文件的指针
	D_FsoutFile * info_file_p;


	/* 录像过程中维护的*/
	// 录像导航信息指针。
	struct __str_rec_info/*str_rec_info*/ * rec_nav_info_p;

	
	/* 放像过程中维护的*/
	// 放像导航信息指针
	//str_rep_info * rep_nav_info_p;
	//str_rep_info * storebuf_rep_info_p;
	// 放像书签指针
	str_book_mark * rep_bookmark_p;

	
} str_pvr_info;


D_Result file_parse_set_value(str_pvr_info* pvr_info_p);
D_Result file_parse_info(str_pvr_info* pvr_info_p);
D_S8* sd_pvrdir_in( D_S8 * src1,  D_S8 *src2, D_S8* rlt_buf);
D_S8* sd_filesfxl_in(D_S8* src1, D_U8 file_kind, D_S8* rlt_buf);
void mi_recinfo_init(void);
//D_Result unitfun_pvrunitcreate(str_pvr_info * pvr_info_p);
//D_Result unitfun_pvrunitcreate(str_pvr_info * pvr_info_p,D_PvrRecordData *rec );
//D_Result file_pvr_rec_creat( D_PvrRecordData *rec  );
D_S32 fileparse_rectime_write(str_time_info *time_info_p,  str_time * start_time_p, str_time * end_time_p, D_U32 drt_time);
D_S32 fileparse_infoheader_write_tobuf(void);
D_S32 fileparse_infoheader_write(void);
D_Handle fileparse_get_ca_osd_info_handle(void);
D_Result fileparse_close_ca_osd_file(void);

//void PVR_file_test();
#ifdef  __cplusplus
}
#endif

#endif
