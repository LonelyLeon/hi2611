/** @file dpvr_replay.c
* @brief pvr ���� ģ��
* PVR���� ���ܿ��� ���� ��� ���� �ط�
* @author ������ ����
* @date 2013-11-28 ������: �����ļ�        
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

/** @brief PVR���񴴽����� */
typedef struct
{
    D_ID id;  /**< PVR����ʹ�õ��豸id */
}D_PvrRepPlayerAttr;

/** @brief ��ȱʡֵ��ʼ��PVR�������*/
#define D_PVRREP_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
	D_MACRO_END

/*�����ٶ�����*/
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

/*��ǰ������Ϣ*/
typedef struct
{
	D_SpeedType speed_type;			//��ǰ�ٶ�
	D_S32		step;				//��ǰ������Ϣ	
	D_U32		fact_index;			//��ǰʵ�ʽ�֡������
	D_U32		current_index;		//�ѿ�����I֡��������
	D_U32		total_index;		//һ��������������Ϣ
	D_U32		sectors_remain;		//��һ֡ʣ���ֽڴ�С
}D_NavInfo;

/*�ļ���Ϣ*/
typedef struct
{
	D_Handle handle;	
	D_U64	filesize;
}D_PvrRepFile;

/*PVR��Ԫ��Ϣ*/
typedef struct
{
	D_S8			filepath[MAX_FILE_PATH_LENGTH];
	D_S8			filename[MAX_FILE_NAME_LENGTH];
	D_U32			total_time;
	D_PvrRepFile 	ts_file;			//�����ļ��ṹ��
	D_PvrRepFile 	nav_file;			//�����ļ��ṹ��
	D_PvrRepFile 	info_file;			//��Ϣ�ļ��ṹ��	
}D_PvrRepUnit;

/*�������ò���*/
typedef enum
{
	PVR_INVALID,
	PVR_READY_OK = 1,
	PVR_PLAYING,
	PVR_STOP,
	PVR_PAUSE,
}D_PvrTaskState;

/* pvr����TSԴ������ */
typedef enum
{
	PVR_REP_HAIER_TS = 0,	//ԭʼts��������
	PVR_REP_NORMAL_TS,	//����¼����������
	PVR_REP_PVR_TIMESHIFT_TS,	//pvr(��¼�߲���)����
	PVR_REP_TIMESHIFT_TS,	//��ʱ�Ʋ�������
	PVR_REP_SPECIFIED_AVPID_TS,	//�ض�����Ƶpid�������ͣ���ts�ļ���û��PAT PMT����Ϣ
}D_PvrTsType;

typedef struct
{
    D_U16 aud_pid;
    D_AudCodecType aud_codec;
    D_Char language[PVR_REP_AUD_LANGUAGE_LENGTH];
}D_PvrAudInfo;

/* pvr��������ʱ�������� */
typedef struct{
	D_U16 PMT_pid;
    D_U16 pcr_pid;
	D_U16 vid_pid;
	D_U8  vid_codec;
    D_PvrAudInfo aud_info[PVR_REP_AUD_MAX];
}D_SiProgramInfo;

/**@brief tsƵ����Ϣ */
#define PVR_TS_PROG_CNT (64)
typedef struct
{
    D_U16   prog_cnt;
    D_U16   play_idx;
	D_SiProgramInfo prog_info[PVR_TS_PROG_CNT];
}D_PvrProgramInfo;


/*�������ò���*/
typedef struct
{
	D_S8		filepath[MAX_FILE_PATH_LENGTH];
	D_S8		filename[MAX_FILE_NAME_LENGTH];
	D_U8		Read_ok;
	D_PvrTsType	ts_type;		//Դ��������	
	D_PvrRepTsParm ts_param;	//Դ�ļ�����
    D_U8 drm_key[32];
	D_U32       prog_num;       //���ŵڼ�·��Ŀ    
}D_PvrRepTaskConfig;

/**@brief PVR ����������GUI��ص��õĽṹ��*/
typedef struct
{
	/*callback ���˵���ʾ��Ϣʹ��*/
	D_U8 pvr_ts_parse_res;/*������������*/
	D_Char path[256]; /*�����ļ�ȫ·������*/
}D_Pvr_Cb;


/*�����������������*/
typedef struct
{
	D_HPvrRep		hpvr_replay;	/*��������ľ��*/
	D_PvrHandle		dev_id;			/*�����豸��*/		

	D_U32 		rep_buff_wp;				/*���񻺴����ĵ�ַ*/
    D_Bool      rep_buff_use_sys;
	D_U32 		rep_buff_baseaddr;			/*���񻺴����Ļ���ַ*/
	D_U32       rep_buff_physaddr;  		/**< ����ʹ�õ������ַ */
    D_U32       rep_buff_size;
    D_U8        *rep_buff_align_addr;
    D_Bool      drm_buff_use_sys;
    D_U32 		drm_buff_baseaddr;			/*���񻺴����Ļ���ַ*/
	D_U32       drm_buff_physaddr;  		/**< ����ʹ�õ������ַ */
    D_U32       drm_buff_size;
    D_U8        *drm_buff_align_addr;
	D_PvrIntReason		PvrReplayIntStatus;	/*��¼��������ײ��ж�״̬*/	
	D_PvrRepTsParm 		ts_parm;			/*��¼ts�����������ڲ������ϲ�˵�����*/	
	D_PvrRepUnit 		file;				/*��¼��ǰ���ŵĵ�Ԫ�����ļ��������������С�����ơ�·����*/
	D_Bool				enable_nav;			//�Ƿ�ʹ�õ����ļ����������񻺴��������ȡ�ļ�ƫ��
	D_NavInfo 			nav_info;			//������Ϣ
	D_U32 				av_play_state;		/*��¼��ǰav����״̬*/
	D_PvrTaskState		state;				/*��¼�������񲥷�״̬*/
	D_PvrTsType	 		ts_type;			/*��ǰ����ts��ʱ�޵���ts��������������¼�Ƶ�Ԫ��*/
	D_PvrRepTaskConfig	config;				/*��¼�л����ŵ�Ԫ�Ĳ���*/
	D_Bool				need_sys;			/*���ڽ�������Ԫ���ò���ʱ���л���Ŀ��ͨ���˱�־��������ǰ������������̨Ч��*/
	D_Bool				disable_blank;		/*��¼��ǰ�Ƿ����״̬*/
	D_SiProgramInfo 	pvr_program[PMT_MAX];/*�������Ŀts�����н�Ŀ��Ϣ*/
    D_U32               pvr_program_count;  /* ������ʵ�ʰ���PMT���� */
    D_U32               pvr_play_count;     /* ��ǰ���ŵĽ�Ŀ���� */
    D_Handle            av_evt_handle;		/*av�¼��ص������ľ��*/
    D_Handle            pvr_rep_int_handle;	/*�ж��¼��ص����*/
    D_HSem              Pvr_Replay_IntSemaphore;/*�����������������ж��ź���*/
    D_S64               ts_read_limit; /* ����ts���������ȡ������ļ����� */
    D_Handle            hdrm;  /* DRM�豸��� */
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

/** @brief ��PVR���������Դ */
D_Result	d_pvr_rep_open(void)D_FUNCPOSTFIT;

/** @brief �ر�PVR�����Դ */
D_Result	d_pvr_rep_close(void)D_FUNCPOSTFIT;

/** @brief ������������*/
D_Result    d_pvr_rep_create_ex(D_PvrRepPlayerAttr *attr) D_FUNCPOSTFIT;
#define d_pvr_rep_create()    d_pvr_rep_create_ex(NULL)

/** @brief ���ٷ������� */
D_Result  	d_pvr_rep_destroy(D_HPvrRep handle)D_FUNCPOSTFIT;

/** @brief ���������� */
D_Result 	d_pvr_rep_start(D_HPvrRep handle)D_FUNCPOSTFIT;

/** @brief 	��ͣ*/
D_Result 	d_pvr_rep_pause(D_HPvrRep handle)D_FUNCPOSTFIT;

/** @brief �������� */
D_Result 	d_pvr_rep_resume(D_HPvrRep handle)D_FUNCPOSTFIT;

/** @brief ���²��� */
D_Result 	d_pvr_rep_restart(D_HPvrRep handle)D_FUNCPOSTFIT;

/** @brief ֹͣ */								
D_Result 	d_pvr_rep_stop(D_HPvrRep handle)D_FUNCPOSTFIT;

/** @brief ǰ�� */
D_Result 	d_pvr_rep_forward_ex(D_HPvrRep handle, D_SpeedType speed_flag, D_U32 param)D_FUNCPOSTFIT;
#define d_pvr_rep_forward(_handle, _speed) d_pvr_rep_forward_ex(_handle, _speed, 0)

/** @brief ����*/
D_Result 	d_pvr_rep_backward_ex(D_HPvrRep handle, D_SpeedType speed_flag, D_U32 param)D_FUNCPOSTFIT;
#define d_pvr_rep_backward(_handle, _speed) d_pvr_rep_backward_ex(_handle, _speed, 0)

/** @brief ����PVR���� */
D_Result 	d_pvr_rep_set_param_ptr(D_HPvrRep handle,D_PvrRepTaskConfig *config)D_FUNCPOSTFIT;

#define d_pvr_rep_set_param(__h, __t)   d_pvr_rep_set_param_ptr((__h), &(__t))

/** @brief �õ�PVR״̬ */
D_PvrTaskState d_pvr_rep_get_state(D_HPvrRep handle)D_FUNCPOSTFIT;

/** @brief �õ���ǰ�Ѳ���ʱ�� */
D_U32 	d_pvr_rep_get_time(D_HPvrRep handle)D_FUNCPOSTFIT;

/** @brief �õ�������ʱ�� */
D_U32 	d_pvr_rep_get_total_time(D_HPvrRep handle)D_FUNCPOSTFIT;

/** @brief �õ���ǰ����ts�ļ���С*/
D_U64 d_pvr_rep_get_file_size(D_HPvrRep handle)D_FUNCPOSTFIT;

/** @brief 		PVR��ת����
* @param[in]	jump_value ��ת��ʱ��ֵ
* @param[in]	handle ������
* @return 		�ɹ�D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_pvr_rep_set_jump(D_HPvrRep handle, D_U32 jump_value)D_FUNCPOSTFIT;

/** @brief ȡ��ts�ļ�����Ƶ��Ϣ, ֻ�в��ű�׼ts���ļ�����, hts�ļ�����Ӧ
*@param[in] pvr������
@retval ��Ƶ��Ϣ�ṹ����
*/
D_PvrAudInfo *d_pvr_rep_get_aud_info(D_HPvrRep handle) D_FUNCPOSTFIT;

/**@brief ѡ��һ·��Ƶ����
*@param[in] pvr������
*@param[in] ��Ƶ����
*@retval �ɹ�����D_OK, ����ʧ��
*/
D_Result d_pvr_rep_select_audio(D_HPvrRep handle, D_Int audio_index) D_FUNCPOSTFIT;

/** @brief ȡ��ts�ļ����Ƶ����Ϣ, ֻ�в��ű�׼ts���ļ�����, hts�ļ�����Ӧ
*@param[in] pvr������
@param[in/out] proginfo ��Ƶ����Ϣ
* @return       �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_pvr_rep_get_progs_info(D_HPvrRep handle, D_PvrProgramInfo *proginfo) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif
 
