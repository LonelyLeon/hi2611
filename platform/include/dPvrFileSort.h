/** @file
* @brief PVR��Ԫ�Ľ�����.info,.nav,.ts�ļ��Ľ���������
* @author:liux
* @date 2013-12-07 liux: �����ļ�
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
// ¼���ļ�·������󳤶�// like "C:/AVDATA/CCTV4_201105131327" is 28
#define REC_FILEPATH_LENGTH_MAX					1024

#define REC_CHANNEL_NUM							24
#define FILE_PATH_MAX							1024
#define FILE_NAME_MAX							256	


#define PVR_DATA_BUFF_SIZE								1024


// info �ļ��и����ݶ�λ�ö���
// ���¶���512�ֽ�Ϊinfo �ļ���ͷ��Ϣ
#define HEADTAG_OFFSET								0
#define HEADTAG_LENGTH								9	// INFOFILE+�ַ���������־
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

// ����ʱ��ṹ��
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


// PVR��PID��ά��
typedef struct
{
	// ��ǰ��pid �Ƿ���Ч
	pvr_u8 pid_valid : 1;
	// ��ǰpid �����ͣ��ο�e_pid_type
	pvr_u8 pid_type : 7;
	// ��ǰpid ��ֵ
	pvr_u16 pid_value : 13;
	// ��������һ��Ԫ���Ƿ����
	pvr_u16 pid_next : 3;

} str_pid;
// ��pid ����ṹ��ͬu32 ���һ��������
// ���������򻺳�����д��д��
typedef union 
{
	str_pid pid_str;
	pvr_u32 pid_str_value;

} u_pid;

// pid �����Ͷ���
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
	pvr_u8 video_stream_type:4; // ��¼��Ŀ����Ƶ��ʽ 0=MPEG2,1=h264,2=AVS
	pvr_u8 audio_stream_type:4; // ��Ƶ���ĸ�ʽ1=MPEG1, 2=MPEG2, 3=AAC, 4=AC3
	u_pid pid_arr[PVR_PID_TOTAL];
	pvr_u32 last_point;
	pvr_u32 nav_total;

}str_info_header;

// ��ǩ�Ĵ�����������: .info �ļ��ĵڶ���512 �ֽڴ����ǩ��Ϣ
// ��ǩͷ(��¼��ǩ�ĸ���:4  �ֽ�) +   127*ÿ����ǩ��(4�ֽ�)
// ��������ʱ:��.info�ļ��е���ǩ��д���ڴ棬���ڴ�����
// ������ά����ǩ���õ�����Ľڵ����Խڵ��ֵ(nav_index) 
// ��С�������еģ���Ҫ���һ���µ���ǩʱ(��bookmark��)��
// �鿴����ǩ�Ƿ��������У���:��ɾ���ýڵ�(ɾ��һ����ǩ)
// û��:������ǩ��ӵĺ��ʵ�λ�ã�����bookmark_num
// ALI�лὫ���Ĺ�������д���ļ��У����Բο���������������
// ĳ��ʱ�̸��»�.info �ļ���
// ������ǩ�ڵ�
typedef struct bookmark
{
	// ��¼��ǰ��ǩ��Ӧ�ĵ���������
	pvr_u32 nav_index;
	// ָ����һ����ǩ
	struct bookmark * next;

}node_bookmark;

// ��ǩ�ṹ��
typedef struct
{
	// ��ǩ���������仯��ǣ�����ǰ�ı仯�Ѿ�д��.info�ļ��󽫸ñ�����
	pvr_u8 bookmark_chg;
	// ��ǩ�ĸ���
	pvr_u32 bookmark_num;
	// ����ָ����ǩ������ĵ�һ����ǩ�ڵ�
	node_bookmark * bookmark_first;
	// ��ǰ����ǩ�ڵ�
	// �Ե�ǰ���ſ����˳�����ǩ����û�������䶯ʱbookmark_currtΪ��Ч��
	// ����bookmark_currt���ǵ���bookmark_first
	node_bookmark * bookmark_currt;	

}str_book_mark;

// ���岻�����ļ�ϵͳ���ļ��ṹ��
typedef struct
{
	D_U32	curp_write;
	D_U32	curp_read;
	
	D_S8	filename[FILE_NAME_MAX];
	D_U8	type;
	D_U32	filesize;
	void* 	file_p; // ָ������ļ�ϵͳ�ļ���ָ��
	D_Handle handle;
}D_FsoutFile;

struct __str_rec_info;

// ¼��ʱҪ����ĵ�ǰ��Ŀ��Ϣ�Ľṹ��
// �д���������
typedef	struct
{
	/* ¼�����е�*/
	pvr_u8 is_scrambled;
	// ¼��ʱ���õ�ͨ����0~3
	// ������Ƶpid ��ͨ���ż�¼����
	pvr_u8 channel_no; 
	pvr_u8 pvr_state;


	// ��¼��Ŀ����Ƶ��ʽ 0=MPEG2,1=h264,2=AVS
	pvr_u8 video_stream_type:4;
	// ��Ƶ���ĸ�ʽ1=MPEG1, 2=MPEG2, 3=AAC, 4=AC3
	pvr_u8 audio_stream_type:4;

	// PVR�ļ��Ƿ�����
	pvr_u8 is_locked;
	// pid ά��
	u_pid pid_arr[PVR_PID_TOTAL];
	// ʱ��
	str_time start_time;
	str_time end_time;
	pvr_u32 drt_time;  // ����ʱ��,��λ��
	// like "CCTV4"
	pvr_char pro_name[PROGRAM_NAME_LENGTH];
	// like "CCTV4_20110513132727"
	pvr_char dir_name[DIR_NAME_LENGTH]; 
	// like "C:/AVDATA/CCTV4_20110513132727"
	pvr_char dir_path[REC_FILEPATH_LENGTH_MAX];
	// �ļ���С
	pvr_u32 file_size; 
	// ָ���Ÿ�¼�ƽ�Ŀts���ļ���ָ��
	D_FsoutFile * ts_file_p;
	// ָ���Ÿ�¼�ƽ�Ŀ������Ϣ�ļ���ָ��
	D_FsoutFile * nav_file_p;
	// ָ���Ÿ�¼�ƽ�Ŀ��Ϣ�ļ���ָ��
	D_FsoutFile * info_file_p;


	/* ¼�������ά����*/
	// ¼�񵼺���Ϣָ�롣
	struct __str_rec_info/*str_rec_info*/ * rec_nav_info_p;

	
	/* ���������ά����*/
	// ���񵼺���Ϣָ��
	//str_rep_info * rep_nav_info_p;
	//str_rep_info * storebuf_rep_info_p;
	// ������ǩָ��
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
