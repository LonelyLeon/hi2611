/** @file dPvrRecord.h
* @brief pvr ¼��ģ��
* PVR���� ����¼����
* @author �̸�
* @date 2013-11-28 �̸�:�����ļ� 
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

// ¼�������ά���Ľṹ��
// ��sdram����ʱ��ŵ������ݵĸ���
// ¼��ʱ: ����Ŀ���ﵽ128���󣬽���д�뵼���ļ���
typedef struct  __str_rec_info
{
	// ������
	D_U32 buffer[NAV_NUM_PER_BUFF];
	// ��ǰ�������л�ĵ�����Ŀ��
	D_U8 buff_act_index;
	// ��ǰ��ĵ�����Ŀ��(0~һ����������)
	// �������Ҳ���Կ����ǵ�ǰһ��¼�Ƶĵ�������
	// .info �ļ���ͷ����¼�˸�ֵ
	D_U32 act_index;   

} str_rec_info;


/*¼���������������*/
typedef struct __D_PvrRecordData
{
	//
	D_HApp	hpvr_record;
	D_PvrHandle	dev_id;	
	D_HQueue guiqueue;

	//¼�񻺳����Ĵ����͵����Ĵ�������
	D_Bool recbuf_use_sys;  /**< ¼�񻺳����Ƿ�ʹ�ó������ */
	D_U32 recbuf_addr ;//       
	D_U32 recbuf_physaddr;  /**< ¼�񻺳��������ַ, ����ʹ�� */
    D_U8 *recbuf_align_addr;
	D_U32 recbuf_size;//
	D_Bool drmbuf_use_sys;  /**< DRM�������Ƿ�ʹ�ó������ */
    D_Ptr drmbuf_addr;  /**< DRM������, 16�ֽڶ��� */
    D_Ptr drmbuf_physaddr;
    D_U8 *drmbuf_align_addr;
    D_U32 drmbuf_size;
    D_U32 recbuf_int_value;//
	D_U32 rec_nav_int_value;//

	//ԭ����PVR_REC_PARA�ṹ��
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

	//ԭ����info�ļ��ṹ��

	/* ¼�����е�*/
	D_U8 is_scrambled;
	// ¼��ʱ���õ�ͨ����0~3
	// ������Ƶpid ��ͨ���ż�¼����
	D_U8 channel_no; 
	D_U8 pvr_state;

		// ��¼��Ŀ����Ƶ��ʽ 0=MPEG2,1=h264,2=AVS
	D_U8 video_stream_type:4;
	// ��Ƶ���ĸ�ʽ1=MPEG1, 2=MPEG2, 3=AAC, 4=AC3
	D_U8 audio_stream_type:4;

	// PVR�ļ��Ƿ�����
	D_U8 is_locked;
	// pid ά��
//	D_U8 pid_arr[PVR_PID_TOTAL];
	u_pid pid_arr[PVR_PID_TOTAL];

	// ʱ��
	str_time start_time;
	str_time end_time;
	D_U32 drt_time;  // ����ʱ��,��λ��
	// like "CCTV4"
	D_S8 pro_name[PROGRAM_NAME_LENGTH];
	// like "CCTV4_20110513132727"
	D_S8 dir_name[DIR_NAME_LENGTH]; 
	// like "C:/AVDATA/CCTV4_20110513132727"
	D_S8 dir_path[REC_FILEPATH_LENGTH_MAX];
	// �ļ���С
	D_U32 file_size; 
	// ָ���Ÿ�¼�ƽ�Ŀts���ļ���ָ��
	D_FsoutFile * ts_file_p;
	// ָ���Ÿ�¼�ƽ�Ŀ������Ϣ�ļ���ָ��
	D_FsoutFile * nav_file_p;
	// ָ���Ÿ�¼�ƽ�Ŀ��Ϣ�ļ���ָ��
	D_FsoutFile * info_file_p;
	/* ¼�������ά����*/
	// ¼�񵼺���Ϣָ�롣
	str_rec_info * rec_nav_info_p;
	/* ���������ά����*/
	// ���񵼺���Ϣָ��
//	str_rep_info * rep_nav_info_p;
//	str_rep_info * storebuf_rep_info_p;
	// ������ǩָ��
//	str_book_mark * rep_bookmark_p;
    D_Handle pvr_rec_int_handle;
    D_HSem Pvr_Rec_IntSemaphore;
    D_U32 pvr_rec_support_max_duration_sec;  /**< pvr¼��֧���ʱ��, �뵥λ */
    D_U32 pvr_rec_support_min_disk_space;  /**< pvr¼��֧����С���̿ռ� */
    D_S64 pvr_rec_support_max_file_size;  /**< pvr¼��֧������ļ��ߴ� */
    D_Bool need_drm;  /**< �Ƿ�ʹ��DRM���� */
    D_U8 drm_key[32];
    D_Handle hdrm;
    D_Bool rec_osd_msg; /*�Ƿ��¼osd, Ŀǰ������ֻ�����ļ���������¼��Ӧ�������*/    
    D_Bool is_timeshift; /*��ʱ�Ʊ�־*/
}D_PvrRecordData;



// ¼��ʱҪ����ĵ�ǰ��Ŀ��Ϣ�Ľṹ��
// �д���������
typedef	struct
{
	/* ¼�����е�*/
	D_U8 is_scrambled;
	// ¼��ʱ���õ�ͨ����0~3
	// ������Ƶpid ��ͨ���ż�¼����
	D_U8 channel_no; 
	D_U8 pvr_state;


		// ��¼��Ŀ����Ƶ��ʽ 0=MPEG2,1=h264,2=AVS
	D_U8 video_stream_type:4;
	// ��Ƶ���ĸ�ʽ1=MPEG1, 2=MPEG2, 3=AAC, 4=AC3
	D_U8 audio_stream_type:4;
	
	D_U16	pvr_rec_pid[24];
	PVR_CH_OUT_MODE	channel_out_mode;
	PVR_REC_NAV_TYPE	pvr_rec_nav_type[4];	//0x00-- mpeg nav, 0x01-- h264 nav, 0x02-- avs nav, 0x03-- user define
	D_U8  	pvr_rec_cw[8];
	D_U8	rec_tv_num;
	D_U8	rec_interrupt_state;

	// PVR�ļ��Ƿ�����
	D_U8 is_locked;
	// pid ά��
	u_pid pid_arr[PVR_PID_TOTAL];
	// ʱ��
	str_time start_time;
	str_time end_time;
	D_U32 drt_time;  // ����ʱ��,��λ��
	// like "CCTV4"
	D_S8 pro_name[PROGRAM_NAME_LENGTH];
	// like "AVDATA"
	D_S8 dir_name[DIR_NAME_LENGTH]; 
	// like "C:/"
	D_S8 dir_path[REC_FILEPATH_LENGTH_MAX];
	// �ļ���С
	D_U32 file_size;

    D_U32 pvr_rec_support_max_duration_sec;  /**< pvr¼��֧���ʱ��, �뵥λ */
    D_U32 pvr_rec_support_min_disk_space;  /**< pvr¼��֧����С���̿ռ� */
    D_S64 pvr_rec_support_max_file_size;  /**< pvr¼��֧������ļ��ߴ� */

    D_Bool need_drm;  /**< �Ƿ�ʹ��DRM���� */
    D_U8 drm_key[32];
    D_Bool rec_osd_msg;/*�Ƿ��¼osd, Ŀǰ������ֻ�����ļ���������¼��Ӧ�������*/  
    D_Bool is_timeshift; /*ʱ�Ʊ�־*/
    D_U32  timeshift_nav_file_save_max;/*ʱ��ʱ�����ļ��������󵼺���Ŀ��*/
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

/** @brief PVR����¼��ʱ��
* @param[in]	handle  PVR���
* @return  �ɹ�����D_OK, ʧ�ܷ���D_ERR
*/
D_Result d_pvr_rec_set_total_time(D_Handle handle, D_Time rec_total_time) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif

