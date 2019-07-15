/** @file
* @brief Ƶ������ģ��
* @author ����
* @date 2005-6-30 ����: �����ļ�
* @date 2013-05-16 lc: ͳһƽ̨, ��������
*/

#ifndef _D_SCAN_H_
#define _D_SCAN_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dFMan.h"
#include "dDBase.h"
#include "dFEnd.h"
#include "dDemux.h"
#include "dQueue.h"
#include "dMsg.h"
#include "dMMan.h"
#include "dDescr.h"
#include "dSIParse.h"
#include "dResource.h"


typedef D_Handle	D_HScan;
typedef struct _D_ASGroup	D_ASGroup;


/**************************************************************/
/***Ƶ��SI�������������ֶ��������Զ�����***/
/**************************************************************/
#define TABLE_MASK_NIT 			0x01
#define TABLE_MASK_PAT 		0x02
#define TABLE_MASK_PMT 		0x04
#define TABLE_MASK_SDT 		0x08
#define TABLE_MASK_SDT_OTH 	0x10
#define TABLE_MASK_CAT 		0x20
#define TABLE_MASK_BAT 		0x40
#define TABLE_MASK_PRIVATES	0x80


/*˽�б�si��������*/
typedef struct
{
	D_Bool	valid;
	D_U16 	pid;
	D_U8	table_id;
	D_U16	table_ext_id;
	D_U32	timeout;
	D_List*	(*d_si_parse_private)(D_U8 *sec_buf, D_S16 length, D_HMMan hmm) D_FUNCPOSTFIT;
}D_SiScanPrivateConf;


/*��Ƶ��si ��������������Ϣ�ṹ*/
typedef struct 
{
	D_S8 			priority;			/*�������ȼ�*/
	D_HQueue 		hqueue;			/*ע��������Ϣ����*/
	D_Bool			lock_enable;	/*�Ƿ���Ҫ����Ƶ��*/
	D_FEndParam	 	fend_param;	/*Ƶ�����*/
	D_FEndType		fend_type;		/*Ƶ������*/
	D_FEndAttr		fend_attr;		/*ǰ���豸����*/
	D_HMMan		hmm;			/*�ڴ������*/
	D_HFMan 		hfman;			/*ǰ�˹��������*/
	D_U16 			table_mask;		/*����������*/
	D_U32			pat_timeout;	/*PAT��ʱ*/
	D_U32			pmt_timeout;	/*PMT��ʱ*/
	D_U32			nit_timeout;		/*NIT��ʱ*/
	D_U32			sdt_timeout;		/*SDT��ʱ*/
	D_U32			sdt_oth_timeout;/*SDT OTH��ʱ*/
	D_U32			cat_timeout;		/*CAT��ʱ*/
	D_U32			bat_timeout;	/*BAT��ʱ*/
	D_U16			network_id;		/*NIT��network_id*/	

       D_Bool                  cmp_bat;    /*�Ƿ�Ҫ�Ƚ�bouqid*/
       D_U8			bouq_cnt;  /*Ҫ������bat����*/    
	D_U16			*bouq_id;	/*BAT��ҵ��Ⱥid (����ָ��)*/

	D_Bool			progress_enable;/*�Ƿ��ϱ���������*/
	D_SiScanPrivateConf private[2];	/*����˽�б�ʱ������*/

} D_TpSiScanTaskConfig;


/*Ƶ��si �����������*/
typedef struct 
{
	D_FEndParam	 param;	/*Ƶ�����*/
	D_FEndType    type;	/*Ƶ������*/
	D_Bool          locked;	/*Ƶ���Ƿ�����*/
	D_U16		ts_id;
	D_U16		org_net_id;
	D_List		*pats;
	D_List		*pmts;
	D_List		*cats;
	D_List		*bats;
	D_List		*nits;
	D_List		*sdts;
	D_List		*sdt_oths;
	D_List		*privates;
	D_List		*privates1;
} D_ScanTp;



#define D_SCAN_GROUP_MAX_CNT	10
#define D_SCAN_GROUP_MAX_TP_CNT	256
#define D_SCAN_MAX_BOUQ_CNT	64


/** @brief �Զ�����ģʽ*/
typedef enum {
	D_AUTO_SCAN_MODE_NIT,			/* NIT ����*/
	D_AUTO_SCAN_MODE_TP,				/* Ƶ���б�*/		
	D_AUTO_SCAN_MODE_FULL,			/* ȫƵ������*/
	D_AUTO_SCAN_MODE_BLIND,			/* äɨ����,����һ��Ƶ���������SI*/	
	D_AUTO_SCAN_MODE_ANALOG,		/*ģ���ź��Զ�����*/
	D_AUTO_SCAN_MODE_OTHER			/* ����*/
} D_AutoScanMode;


/** @brief ����ʱ��������*/
typedef enum {
	D_SCAN_PARSE_TP,		/*�ѵ�һ��Ƶ�����������*/
	D_SCAN_PARSE_GROUP,	/*����һ���ͽ���*/
	D_SCAN_PARSE_ALL,		/*ȫ�������Ž���*/
	D_SCAN_PARSE_OHERS	/*����*/
} D_ScanParseMode;



/** @brief �Զ�����ʱ��nit����صĲ���*/
typedef enum {
	D_NIT_STRA_NONE,				/*�ҵ�nit�󲻰�nit����*/
	D_NIT_STRA_NOT_COVER,		/*�ҵ�nit�󲻸���֮ǰ��������Ƶ��*/
	D_NIT_STRA_ALL_COVER,			/*�ҵ�nit�󸲸�֮ǰ������������Ƶ��*/
	D_NIT_STRA_SOME_COVER,		/*�ҵ�nit��nit��û�е�Ƶ���������������*/
	D_NIT_STRA_OTHER				/*����*/
}D_AutoScanNitStrategy;



/** @brief Ƶ��������������(�Զ�/�ֶ�)*/
typedef struct
{
	D_U32			buf_size;		/*�ڴ�ռ��С(byte)*/
	D_S8 			priority;			/*�������ȼ�*/
	D_HQueue 		hqueue;			/*ע��������Ϣ����*/
	D_HFMan 		hfman;			/*ǰ�˹��������*/
	
	D_U32			scan_type;		/*��������*/
	D_U32	        parse_mode;	/*����ģʽ(�����Զ�����)*/
	D_Bool			srv_name_en;	/*�Ƿ�֪ͨ�˵��������ķ�������*/
	D_DBID 			db_net_id;		/*db_net_id   = 0 */
	D_Bool			sdt_srv_type_en;	/*�Ƿ�ο�sdt�����srv type���жϷ��������(TV/Radio/others...), atv����ʱ���ڿ����Ƿ���Ӧ�÷��ͽ�����Ϣ*/       
	D_Bool          group_end_save; /*һ��������Ƿ�ֱ�ӱ���*/
	D_FEndType		fend_type;		/*Ƶ������*/	
	D_FEndParam		fend_param;	/*����Ƶ���������������Ƶ������ֶ�������atv����ʱ���ڴ�������Ƶģʽ*/

	D_DBAnteInfo 	AnteInfo;		/*���ݵ����߲���*/
	D_DBSateInfo	SateInfo;		/*���ݵ����������߲���*/
	D_DBID		    db_sat_id;		/*����id*/ 
	
	D_FEndFreq		startfreq;		/*��ʼƵ�ʣ�����ȫƵ������*/
	D_FEndBandWitch	bandwitch;		/*��������ȫƵ������*/
	D_FEndFreq		endfreq;		/*����Ƶ�ʣ�����ȫƵ������*/
	D_FEndFreq		stepfreq;		/*����Ƶ�ʣ�����ȫƵ������*/    

	D_U32			Reserved;		/*���ò���*/
	D_Ptr			pReserved;		/*���ò���ָ�룬���ƴ������н���*/
	D_Ptr			pScanOp;		/*ע��Ĳ������붨���йصĲ���*/
} D_ScanTaskConfig;



/*ע����Զ������Ĳ���*/
typedef struct 
{
	D_Result (*auto_scan_init)(D_ASGroup **group, D_U32*group_cnt, D_ScanTaskConfig *as_config, D_HMMan hmm);
	D_Result (*auto_scan_store)(D_ASGroup **group, D_U32 group_cnt, D_ScanTaskConfig *as_config);
	D_Result (*auto_scan_destroy)(D_ASGroup **group, D_U32 group_cnt, D_ScanTaskConfig *as_config);
}D_AutoScanOp;


/*��Ҫ������Ƶ������б�*/
typedef struct
{
	D_List list;
	D_FEndParam	fendparam;		/*Ƶ�����*/
}D_ScanFendParamNode;


/*Ƶ����Ϣ*/
typedef struct
{
    D_FEndParam param;  
    D_U16   ts_id;
    D_U16   org_net_id;
    D_U8    db_net_id;
    D_U8    db_sat_id;
    D_U8    prog_cnt;	/*��Ƶ����ҵ����*/
    D_U8    tv_cnt;		/*��Ƶ���µ���ҵ����*/
    D_U8    radio_cnt;	/*��Ƶ���¹㲥ҵ����*/
    D_U8    other_cnt;	/*��Ƶ��������ҵ����*/  
    D_U8    tuner_type;
    D_U8    found_nit;	/*Ƶ���Ƿ���nit*/
    D_U16   version;	/*��Ŀ�汾(��nit �汾)  (Ӧ������ֵ)��ʼΪ-1*/    
    D_U8    quality;    /*�ź�����*/
}D_ScanTsInfo;


/*Ƶ�����������Ϣ����ڵ�*/
typedef struct
{
    D_List  list;   
    D_U8    valid;		/*Ƶ���Ƿ���Ч*/
    D_U16   ts_no;		/*Ƶ�����(������������)*/
    D_ScanTsInfo    ts_info;	/*Ƶ����Ϣ*/    
    D_ScanTp    *scantp;	/*Ƶ�����������ı�����*/
}D_ScanTsInfoNode;


#define SRV_CA_MASK_PMT		0x01	/*PMT�����������������*/
#define SRV_CA_MASK_PMT_ES	0x02	/*PMT����������������������*/
#define SRV_CA_MASK_SDT		0x04	/*SDT����free_ca*/

#define SRV_NAME_LEN (32)   /*�������ռ䳤��*/ 
#define PROV_NAME_LEN (32)   /*�ṩ�����ռ䳤��*/ 

/*����ʱҵ����Ϣ*/
typedef struct
{  
    D_Char  name[SRV_NAME_LEN];   /*������*/
    
    /*������ص�id*/
    D_U16   srv_id;
    D_U16   pmt_pid;
    D_U16   pcr_pid;
    D_U16   vid_pid;
    D_U16   aud1_pid;
    D_U16   aud2_pid;
    D_U16   aud3_pid;
    D_U16   aud4_pid;
    D_U8 	valid;		/*�����Ƿ���Ч*/   
    
    /*����Ƶ��������MPEG2/AVS/AC3...*/
    D_U8    vid_codec;
    D_U8    aud1_codec; 
    D_U8    aud2_codec;
    D_U8    aud3_codec;
    D_U8    aud4_codec;
    D_U8    aud_select;     /*�ڼ�������*/  
    D_U8	aud_track;	/*����*/  
	D_U8	sdt_srv_type;
    D_U8	srv_type;       /*��������:TV/Radio/Data/...*/    
    D_U8	ca_mask;		/*��������*/   
    
    D_S8    volume;        /*��������ֵ*/   
    D_U16   chan_lcn;       /*�߼�Ƶ����*/
    D_U64   bouq_mask;  /*��Ӧ��ҵ��Ⱥ*/
    D_Char  prov_name[PROV_NAME_LEN];   /*�ṩ����*/
}D_ScanSrvInfo;


/*����ʱҵ����Ϣ����ڵ�*/
typedef struct
{
    D_List list;    
    D_U8 	valid;		/*�����Ƿ���Ч*/
    D_U16   ts_no;		/*��Ӧ��������Ƶ�����*/    
    D_ScanSrvInfo srvinfo;	/*������Ϣ*/
}D_ScanSrvInfoNode;

/*����ʱҵ����Ϣ*/
typedef struct
{
	D_U8	type;		/*sdt_srv_type ������������������*/
	D_DBSrvInfo *srvinfo;		/*������Ϣ*/
}D_SdtSrvInfo;

/*Ƶ����Ϣ��ʼ��*/
#define D_SCAN_TS_INFO_INIT(_t)\
		D_MACRO_BEGIN\
			memset(&((_t)->param), 0x00, sizeof(D_FEndParam));\
			(_t)->ts_id = 0xFFFF;\
			(_t)->org_net_id = 0xFFFF;\
			(_t)->db_sat_id = (D_U8)(-1);\
			(_t)->prog_cnt = 0;\
			(_t)->tv_cnt = 0;\
			(_t)->radio_cnt = 0;\
			(_t)->other_cnt = 0;\
			(_t)->found_nit = 0;\
			(_t)->version = (D_U16)(-1);\
			(_t)->tuner_type = 0;\
			(_t)->quality = 0;\
		D_MACRO_END

/*����ʱҵ����Ϣ��ʼ��*/
#define D_SCAN_SRV_INFO_INIT(_s)\
		D_MACRO_BEGIN\
			memset((_s)->name, 0, sizeof((_s)->name));\
			memset((_s)->prov_name, 0, sizeof((_s)->prov_name));\
			(_s)->srv_id=0;\
			(_s)->pmt_pid = 0x1FFF;\
			(_s)->pcr_pid=0x1FFF;\
			(_s)->vid_pid=0x1FFF;\
			(_s)->aud1_pid=0x1FFF;\
			(_s)->aud2_pid=0x1FFF;\
			(_s)->aud3_pid=0x1FFF;\
			(_s)->aud4_pid=0x1FFF;\
			(_s)->vid_codec=D_VID_CODEC_MAX;\
			(_s)->aud1_codec=D_AUD_CODEC_MAX;\
			(_s)->aud2_codec=D_AUD_CODEC_MAX;\
			(_s)->aud3_codec=D_AUD_CODEC_MAX;\
			(_s)->aud4_codec=D_AUD_CODEC_MAX;\
			(_s)->aud_select = 0;\
			(_s)->srv_type = (D_U8)D_DB_SRV_TV;\
			(_s)->ca_mask = 0;\
			(_s)->volume=0;\
			(_s)->chan_lcn = (D_U16)(-1);\
			(_s)->bouq_mask = 0;\
			(_s)->aud_track = 0;\
		D_MACRO_END


/*Ƶ����Ϣ��ʼ��*/
#define D_SCANTSINFO_TO_DBSRVINFO(_dbt, _st)\
		D_MACRO_BEGIN\
			(_dbt)->param = (_st)->param;\
			(_dbt)->db_net_id = (D_U8)((_st)->db_net_id);\
			(_dbt)->ts_id = (D_U16)((_st)->ts_id);\
			(_dbt)->org_net_id = (D_U16)((_st)->org_net_id);\
			(_dbt)->db_sat_id = (D_U8)((_st)->db_sat_id);\
			(_dbt)->tuner_type = (D_U8)((_st)->tuner_type);\
		D_MACRO_END

/*����ʱҵ����Ϣ��ʼ��*/
#ifdef D_DB_SRV_SUPPORT_4AUDIO
#define D_SCANSRVINFO_TO_DBSRVINFO(_dbs, _ss)\
		D_MACRO_BEGIN\
			memcpy((_dbs)->name, (_ss)->name, D_MIN(sizeof((_dbs)->name), sizeof((_ss)->name)));\
                     (_dbs)->name[sizeof((_ss)->name) - 1] = 0;\
			(_dbs)->srv_type = (D_U8)((_ss)->srv_type);\
			(_dbs)->volume = (D_S8)((_ss)->volume);\
			(_dbs)->srv_id = (D_U16)((_ss)->srv_id);\
			(_dbs)->pcr_pid = (D_U16)((_ss)->pcr_pid);\
			(_dbs)->vid_pid = (D_U16)((_ss)->vid_pid);\
			(_dbs)->vid_codec = (D_VidCodecType)((_ss)->vid_codec);\
			(_dbs)->aud1_pid = (D_U16)((_ss)->aud1_pid);\
			(_dbs)->aud1_codec = (D_AudCodecType)((_ss)->aud1_codec);\
			(_dbs)->aud2_pid = (D_U16)((_ss)->aud2_pid);\
			(_dbs)->aud2_codec = (D_AudCodecType)((_ss)->aud2_codec);\
			(_dbs)->chan_lcn = (D_U16)((_ss)->chan_lcn);\
			(_dbs)->pmt_pid = (D_U16)((_ss)->pmt_pid);\
			(_dbs)->aud_track = (D_U8)((_ss)->aud_track);\
			(_dbs)->aud3_pid = (D_U16)((_ss)->aud3_pid);\
			(_dbs)->aud3_codec = (D_AudCodecType)((_ss)->aud3_codec);\
			(_dbs)->aud4_pid = (D_U16)((_ss)->aud4_pid);\
			(_dbs)->aud4_codec = (D_AudCodecType)((_ss)->aud4_codec);\
		D_MACRO_END
#else
#define D_SCANSRVINFO_TO_DBSRVINFO(_dbs, _ss)\
		D_MACRO_BEGIN\
			memcpy((_dbs)->name, (_ss)->name, D_MIN(sizeof((_dbs)->name), sizeof((_ss)->name)));\
                     (_dbs)->name[sizeof((_ss)->name) - 1] = 0;\
			(_dbs)->srv_type = (D_U8)((_ss)->srv_type);\
			(_dbs)->volume = (D_S8)((_ss)->volume);\
			(_dbs)->srv_id = (D_U16)((_ss)->srv_id);\
			(_dbs)->pcr_pid = (D_U16)((_ss)->pcr_pid);\
			(_dbs)->vid_pid = (D_U16)((_ss)->vid_pid);\
			(_dbs)->vid_codec = (D_VidCodecType)((_ss)->vid_codec);\
			(_dbs)->aud1_pid = (D_U16)((_ss)->aud1_pid);\
			(_dbs)->aud1_codec = (D_AudCodecType)((_ss)->aud1_codec);\
			(_dbs)->aud2_pid = (D_U16)((_ss)->aud2_pid);\
			(_dbs)->aud2_codec = (D_AudCodecType)((_ss)->aud2_codec);\
			(_dbs)->chan_lcn = (D_U16)((_ss)->chan_lcn);\
			(_dbs)->pmt_pid = (D_U16)((_ss)->pmt_pid);\
			(_dbs)->aud_track = (D_U8)((_ss)->aud_track);\
		D_MACRO_END
#endif	
/*һ��Ƶ�������Ľ��*/
typedef struct 
{
    D_HMMan         hmm;                /*�ڴ������*/
	D_FEndType		fend_type;			/*Ƶ������*/
	D_DBID			db_net_id;
	D_Bool			locked_flag;			/**< �Ƿ�����Ƶ��*/
	D_Bool			found_nit;                  /**< �Ƿ��ҵ�nit��*/
       D_U8			nit_version;		        /**< nit��汾��*/
	D_Bool			found_chan_ver;		/**< �Ƿ��ҽ�Ŀ�汾��*/
	D_U8			chan_version;		/**< ��Ŀ�汾��*/

      	D_FEndParam	 main_fparam;	/*�ҵ�nit�����Ƶ�����*/

	D_DBAnteInfo 	*pAnteInfo;			/*���߲���*/
	D_DBSateInfo		*pSateInfo;			/*���ǲ���*/

	D_U32			bouq_cnt;			/**< ҵ��Ⱥ��Ŀ*/
	D_DBBouqInfo	*bouq_info[D_SCAN_MAX_BOUQ_CNT];/**< ҵ��Ⱥ��Ϣ*/

	D_U32			scan_tsinfo_cnt;				/**< �ѵ���Ƶ������*/
	D_List 		*scan_tsinfo_list;		/**< �ѵ���Ƶ���б� D_ScanTsInfoNode*/

    D_ScanTp			*main_tp;			/*��Ƶ��si�������(����nit����)*/	
	
	D_List 			*srvList_tv;		/*���ӷ������� D_ScanSrvInfoNode*/
	D_List 			*srvList_radio;		/*�㲥�������� D_ScanSrvInfoNode*/	
	D_List 			*srvList_other;		/*������������ D_ScanSrvInfoNode*/	

	D_U16			prog_cnt;			/**< ����������Ŀ����*/
	D_U16			tv_cnt;				/**< �洢������Ŀ*/
	D_U16			radio_cnt;			/**< �洢�㲥��Ŀ*/
	D_U16			other_cnt;			/**< ����������Ŀ*/
}D_ScanResultValue;




typedef struct
{
	D_Result (*group_start)(D_ASGroup *scan_group,D_ScanTaskConfig *as_config, D_HMMan hmm);				/*˽�г�ʼ��*/
	D_Result (*group_end)(D_ASGroup *scan_group, D_ScanTaskConfig *as_config);			/*˽�з���ʼ��*/
	D_Result (*set_tpsiscan_config)(D_ASGroup *scan_group, D_TpSiScanTaskConfig *conf);/*��Ƶ����������*/
	D_Bool (*check_ca_sys_id)(D_U32 type, D_U16 ca_sys_id);		/*���ca_sys_id*/
	D_Bool (*check_bouq_id)(D_U32 type, D_U16 bouq_id);			/*�������bouq_id*/
	D_Result (*group_end_private_op)(D_ASGroup *scan_group, D_HMMan hmm);/*һ��Ƶ��������˽�в���(ֱ�����õ�)*/
	D_Result (*get_freqlist_in_nit)(D_U32 type, D_ScanTsInfoNode *scants, D_FEndParam*fparam, D_U32 *fcnt);/*nit������ȡƵ���б���Ϣ*/

	D_Result (*get_tp_info)(D_U32 type, D_ScanTsInfoNode *scants, D_ScanResultValue *scanResult);/*��ȡƵ���Ϲ��ĵ�һЩ��Ϣ*/
	D_Result (*get_private_descrs_in_sdt)(D_U32 type, D_Descr *descr, D_ScanSrvInfo *srvinfo);/*sdt������ȡ������Ϣ*/
	D_Result (*get_srvinfo_in_bat)(D_U32 type, D_ScanTsInfoNode *scants, D_ScanSrvInfo *srv_info, D_ScanResultValue *scanResult);/*bat������ȡ������Ϣ*/
	D_Result (*get_srvinfo_in_nit)(D_U32 type, D_ScanTsInfoNode *scants, D_ScanSrvInfo *srvinfo, D_ScanResultValue *scanResult);/*nit������ȡ������Ϣ*/
	D_Result (*get_srvinfo_in_others)(D_U32 type, D_ScanTsInfoNode *scants, D_ScanSrvInfo *srvinfo, D_ScanResultValue *scanResult);/*����˽�б�����ȡ������Ϣ*/	
	D_Bool (*check_srv_valid)(D_U32 type, D_ScanSrvInfo *srvinfo);/*���������Ч��*/
}D_ASGroupOp;




/*�Զ�����ʱ����������  ���ݽṹ����*/
struct _D_ASGroup
{
	D_U32				type;		/*����������(�Զ��塢�Խ���)*/	
    D_U32               group_id;
	D_HFMan 			hfman;			/*ǰ�˹��������*/
	D_AutoScanMode		scan_mode;		/*����ģʽ*/
	D_AutoScanNitStrategy	nit_strategy;	/*����ʱ��nit����صĲ���*/
			
	D_FEndType			fend_type;			/*ǰ������*/
	
	D_U32				scanFendParamList_cnt;	/*Ҫ������Ƶ����Ŀ*/
	D_List 	*scanFendParamList;/*Ҫ������Ƶ���б�   D_ScanFendParamNode*/

	/*<full===����ȫƵ������*/
	D_FEndParam			*base_fparam;	/*��������(��¼��Ƶ��֮��Ĳ���)*/
	D_FEndFreq 			freq_start;		/*��ʼƵ��*/
	D_FEndFreq			freq_end;		/*����Ƶ��*/
	D_FEndFreq			freq_step;		/*Ƶ�ʲ���*/
	D_FEndFreq			freq_bw;		/*Ƶ�ʴ���(����Ƶ��������˴���,>= freq_step)*/	
	/*===full>*/

	D_DBAnteInfo 		AnteInfo;			/*���߲���*/
	D_DBSateInfo			SateInfo;			/*���ǲ���*/
 	D_DBID		db_sat_id;			/*����id*/   

	/*<blind===����äɨ*/
	D_U32				blindparam_cnt;		/*�м���äɨ����*/
	D_FBlindParam		*blindparam;		/*����äɨ����*/
	/*===blind>*/
	
	D_Bool				findSrvInfoInMain;/*�Ƿ����Ƶ�����������Ƶ����Ľ�Ŀ�������Ϣ*/
    D_Bool			sdt_srv_type_en;	/*�Ƿ�ο�sdt�����srv type���жϷ��������(TV/Radio/others...)*/ 

	/*��ǰ������������������еĲ���*/
	D_ASGroupOp		*groupOp;

	D_U8				progress_start;		/*��ǰ���������ȵĳ�ʼֵ*/
	D_U8				progress_end;		/*��ǰ���������ȵ����ֵ*/

	/*=========���=========*/		
	D_ScanResultValue		scanResult;
    D_Bool have_save;   /*�Ƿ��Ѿ�����*/
};


#define D_SCAN_GROUP_ALLOC(_hmm, _grp)\
    D_MACRO_BEGIN\
        _grp = (D_ASGroup*)d_mman_alloc (_hmm, sizeof (D_ASGroup));\
        if(_grp){\
            memset(_grp, 0, sizeof(D_ASGroup));\
            _grp->db_sat_id = -1;\
            _grp->hfman = D_INVALID_HANDLE;\
            _grp->sdt_srv_type_en = D_TRUE;\
        }\
    D_MACRO_END

/*ע����Զ������Ĳ���*/
typedef struct 
{
	D_Result (*manual_scan_init)(D_U32 type, D_ScanTaskConfig *ms_config);
	D_Result (*manual_scan_start)(D_U32 type, D_ScanTaskConfig *ms_config);
	D_Result (*manual_scan_store)(D_U32 type, D_ScanTaskConfig *ms_config, D_ScanResultValue*ms_result);
	D_Result (*manual_scan_destroy)(D_U32 type, D_ScanTaskConfig *ms_config, D_ScanResultValue *ms_result);
	D_Result (*set_tpsiscan_config)(D_U32 type, D_TpSiScanTaskConfig *conf);	/*��Ƶ����������*/
	D_Bool (*check_ca_sys_id)(D_U32 type, D_U16 ca_sys_id);		/*���ca_sys_id*/
	D_Bool (*check_bouq_id)(D_U32 type, D_U16 bouq_id);					/*�������bouq_id*/
	D_Result (*get_tp_info)(D_U32 type, D_ScanTsInfoNode *scants, D_ScanResultValue *ms_result);/*��ȡƵ���Ϲ��ĵ�һЩ��Ϣ*/
	D_Result (*get_private_descrs_in_sdt)(D_U32 type, D_Descr *descr, D_ScanSrvInfo *srvinfo);/*sdt������ȡ������Ϣ*/
	D_Result (*get_srvinfo_in_bat)(D_U32 type, D_ScanTsInfoNode *scants, D_ScanSrvInfo *srv_info, D_ScanResultValue *ms_result);/*bat������ȡ������Ϣ*/
	D_Result (*get_srvinfo_in_nit)(D_U32 type, D_ScanTsInfoNode *scants, D_ScanSrvInfo *srvinfo, D_ScanResultValue *ms_result);/*nit������ȡ������Ϣ*/
	D_Result (*get_srvinfo_in_others)(D_U32 type, D_ScanTsInfoNode *scants, D_ScanSrvInfo *srvinfo, D_ScanResultValue *ms_result);/*����˽�б�����ȡ������Ϣ*/	
	D_Bool (*check_srv_valid)(D_U32 type, D_ScanSrvInfo *srvinfo);/*���������Ч��*/
}D_ManualScanOp;



/** @brief atv ��������*/
typedef enum {
	D_ATV_SCAN_TYPE_AUTO = 0,		/* �Զ���������Ƶ�ʱ���������*/        
	D_ATV_SCAN_TYPE_FULL,			/* ȫƵ������*/		
	D_ATV_SCAN_TYPE_MANUAL,			/* �ֶ�����*/
	D_ATV_SCAN_TYPE_BLIND,
	D_ATV_SCAN_TYPE_OTHER			/* ����*/
} D_AtvScanType;

/** @brief atv ����ģʽ*/
typedef enum {
	D_ATV_SCAN_MODE_NORMAL = 0,			/* ͨ����������������(����Ƶ����)ȷ��*/
	D_ATV_SCAN_MODE_TRAVERSAL,			/* ����Ƶ���ͱ���*/		
	D_ATV_SCAN_MODE_OTHER			/* ����*/
} D_AtvScanMode;

typedef struct{
    D_FEndFreq *freq_list;
    D_U32       freq_cnt;
    D_U32       audiomode_cnt;
    D_U32       videomode_cnt;
    D_AudioMode audiomode[16];
    D_VideoMode videomode[16];
}D_AtvScanParam;


/** @brief ע���atv�Զ������Ĳ���*/
typedef struct 
{
	D_Result (*auto_scan_init)( D_ScanTaskConfig *as_config, D_HMMan hmm);
    D_Result (*auto_scan_locked_action)(D_FEndParam *param, D_Bool locked,D_U16 *cvbs_video_format); /*ÿ��һ��Ƶ��󶼵����û��Ĳ���*/
	D_Result (*auto_scan_store)(D_ScanResultValue scanResult,D_ScanTaskConfig *as_config);
	D_Result (*auto_scan_destroy)(D_ScanTaskConfig *as_config);
}D_AtvAutoScanOp;

/** @brief ע���atv�ֶ������Ĳ���*/
typedef struct 
{
	D_Result (*manual_scan_init)(D_ScanTaskConfig *ms_config);
	D_Result (*manual_scan_start)(D_ScanTaskConfig *ms_config);
	D_Result (*manual_scan_store)(D_ScanTaskConfig *ms_config, D_ScanResultValue*ms_result);
	D_Result (*manual_scan_destroy)(D_ScanTaskConfig *ms_config, D_ScanResultValue *ms_result);
}D_AtvManualScanOp;


/** @brief ��������Ӧ����Ƶ����*/
typedef enum {
	D_ESAV_TYPE_INVALID 		= 0,
	D_ESAV_TYPE_VIDEO 		= 1,
	D_ESAV_TYPE_AUDIO 		= 2,
	D_ESAV_TYPE_PRIVATE 		= 3,	
}D_ESAVType;

#define D_ESAV_AUDIO_LANGUAGE_LENGTH (4)
/** @brief ��������Ӧ����Ƶ��Ϣ*/
typedef struct {
	D_ESAVType	type;
	D_U16	pid;
       D_U16	Private_type;
	D_VidCodecType vid_codec;
	D_AudCodecType aud_codec; 
	D_Char language[D_ESAV_AUDIO_LANGUAGE_LENGTH];
} D_ESAVInfo;

/*����psi��ʱ�������ݽṹ*/
typedef struct {
    D_List		*psis;
    D_FEndType fend_type;
    D_Result result;
} D_ParsePsi;

/** @brief EPG����ģʽ*/
typedef enum {
	D_SCAN_MODE_PF_EPG 	= 1,
	D_SCAN_MODE_SCH_EPG = 2,
	D_SCAN_MODE_PF_OTH_EPG	= 4,
	D_SCAN_MODE_SCH_OTH_EPG	= 8,
	D_SCAN_MODE_TDT_TOT_EPG	= 16,	/*�Ƿ�����ʱ��� tdt tot*/
	D_SCAN_MODE_ALL_PF_EPG	= D_SCAN_MODE_PF_EPG | D_SCAN_MODE_PF_OTH_EPG,
	D_SCAN_MODE_ALL_SCH_EPG	= D_SCAN_MODE_SCH_EPG | D_SCAN_MODE_SCH_OTH_EPG,
	D_SCAN_MODE_ALL_ACT_EPG = D_SCAN_MODE_PF_EPG | D_SCAN_MODE_SCH_EPG,
	D_SCAN_MODE_ALL_OTH_EPG = D_SCAN_MODE_PF_OTH_EPG | D_SCAN_MODE_SCH_OTH_EPG,
	D_SCAN_MODE_ALL_EPG = D_SCAN_MODE_ALL_ACT_EPG | D_SCAN_MODE_ALL_OTH_EPG
} D_EPGScanMode;

/*brief  EPG FILTER ����ģʽ*/
typedef enum {
	EPG_SEARCH_ALL,
	EPG_SEARCH_SERVICE_ID 	= 1,
	EPG_SEARCH_TS_ID = 2,
	EPG_SEARCH_NET_ID	= 4
} D_EPGFilterMode;

/*brief  EPG�ҽ���Ӧservice id �Ĳ��ҷ���*/
typedef enum {
	EPG_FIND_SERVICE_ID_NORMAL,/*���÷�ʽ������ƥ��srvid, ���ƥ��ʱ�ٱȶ�ts id*/
	EPG_FIND_SERVICE_ID_ACT_AND_OTH,     /*���ֵ�ǰƵ�������Ƶ���²��ң�һ������������Ŀ*/
	EPG_FIND_SERVICE_ID_STANDARD,   /* �ϸ�dbv��׼���ҷ�ʽ��tsid srvid��Ҫƥ��*/
} D_EPGFindSrvidMode;

typedef struct {
	D_U16			ext_tab_id;
	D_U8			version;
	D_U8			last_sec_num;
	D_U8			mask[32];
} D_SubTabMask;

typedef struct {
	D_U16			sub_cnt;
	D_U16			sub_size;
	D_SubTabMask	subs[1];
} D_TabMask;

/*���������ú���*/
#define d_sec_filter_init(_f)\
		D_MACRO_BEGIN\
			memset ((_f), 0, sizeof (D_DemuxFilter));\
			(_f)->sec.length=16;\
		D_MACRO_END
		
#define d_sec_filter_set_pid(_f,_p)\
		D_MACRO_BEGIN\
			(_f)->pid = (_p);\
		D_MACRO_END
		
#define d_sec_filter_set_tid(_f,_t)\
		D_MACRO_BEGIN\
			(_f)->sec.filter[0]=(_t);\
			(_f)->sec.mask[0]=0xff;\
		D_MACRO_END

#define d_sec_filter_set_ext_tid(_f,_t)\
		D_MACRO_BEGIN\
			(_f)->sec.filter[3]=(((_t)>>8) & 0xFF);\
			(_f)->sec.filter[4]=((_t)&0xFF);\
			(_f)->sec.mask[3]=0xff;\
			(_f)->sec.mask[4]=0xff;\
		D_MACRO_END

#define d_sec_filter_set_ver(_f,_v)\
		D_MACRO_BEGIN\
			(_f)->sec.filter[5]|=((_f)->sec.filter[5] & 0xC1) | ((_v)<<1);\
			(_f)->sec.mask[5]|=0x3E;\
		D_MACRO_END
/*�汾�ǿ���*/
#define d_sec_filter_set_ver_differ(_f,_v)\
		D_MACRO_BEGIN\
			(_f)->sec.filter[5]|=((_f)->sec.filter[5] & 0xC1) | ((_v)<<1);\
			(_f)->sec.mask[5]|=0x3E;\
			(_f)->sec.positive[5]|=1;\
		D_MACRO_END	
		
#define d_sec_filter_set_ts_id(_f,_t)\
		D_MACRO_BEGIN\
			(_f)->sec.filter[8]=(((_t)>>8) & 0xFF);\
			(_f)->sec.filter[9]=((_t)&0xFF);\
			(_f)->sec.mask[8]=0xff;\
			(_f)->sec.mask[9]=0xff;\
		D_MACRO_END
		
#define d_sec_filter_set_net_id(_f,_t)\
		D_MACRO_BEGIN\
			(_f)->sec.filter[10]=(((_t)>>8) & 0xFF);\
			(_f)->sec.filter[11]=((_t)&0xFF);\
			(_f)->sec.mask[10]=0xff;\
			(_f)->sec.mask[11]=0xff;\
		D_MACRO_END
/*���������ú���*/

/** @brief ����һ�����������ݽṹ
* @param hmm			�ڴ���������
* @param sub_cnt	�����������ɵ��ӱ���Ŀ
* @return �ɹ����ر��������ݽṹ���ݽṹָ�룬ʧ�ܷ���NULL
*/
D_TabMask*		d_tab_mask_new (D_HMMan hmm, D_U32 sub_cnt) D_FUNCPOSTFIT;

/** @brief �������������һ��section����
* @param tab	������
* @param tab_ext	����չID
* @param ver			��汾��
* @param sec	section number
* @param last	last section number
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result			d_tab_mask_add (D_TabMask *tab, D_U16 tab_ext, D_U8 ver, D_U8 sec, D_U8 last) D_FUNCPOSTFIT;

/** @brief ��ձ�����
* @param tab	������
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result			d_tab_mask_clear (D_TabMask *tab) D_FUNCPOSTFIT;

/** @brief �������������һ��section����
* @param tab	������
* @param tab_ext	����չID
* @param ver			��汾��
* @param sec	section number
* @param last	last section number
* @param seg_last	segment last section number
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result			d_tab_mask_add_ex (D_TabMask *tab, D_U16 tab_ext, D_U8 ver, D_U8 sec, D_U8 last, D_U8 seg_last) D_FUNCPOSTFIT;

/** @brief ����������ȫ��section�Ƿ�����
* @param tab	������
* @return ���ȫ��section���뷵��D_TRUE,���򷵻�D_ERR
*/
D_Bool				d_tab_mask_full (D_TabMask *tab) D_FUNCPOSTFIT;

/** @brief �����������Ƿ��Ѿ�����ָ����section
* @param tab	������
* @param tab_ext	����չID
* @param ver			��汾��
* @param sec	section number
* @return ������д�section����D_TRUE,���򷵻�D_ERR
*/
D_Bool				d_tab_mask_is_set (D_TabMask *tab, D_U16 tab_ext, D_U8 ver, D_U8 sec) D_FUNCPOSTFIT;

/** @brief ����pmt����һ������Ļ�����������
���÷�������pid������(��: ����ƵPID���������)��
 * @param[in] es  ����������
* @param[out] esav_info  ���pid������
* @return ��Ч����D_OK, ��Ч����D_ERR
* @note ���ڽ�Ŀ��������(����emm \ecm  pid)
*/
D_Result d_scan_parse_element_stream(D_ElementStream *es, D_ESAVInfo *esav_info) D_FUNCPOSTFIT;


/** @brief ����sdt�������������(DESCR_SERVICE)�����������ͣ�
���÷��������(���ӡ��㲥������������)��
* @param[in][out] *srvinfo  ��������ָ�� 
* @param[in] sdt_srv_type ������������������
* @return ��Ч����D_OK, ��Ч����D_ERR
* @note ���ڽ�Ŀ��������
*/
D_Result d_scan_set_srv_type(D_DBSrvInfo *srvinfo, D_U8 sdt_srv_type) D_FUNCPOSTFIT;


/** @brief ��Ƶ������ģ��
* @return �ɹ�����D_OK, ʧ�ܷ���D_ERR
*/
D_Result	d_scan_open (void) D_FUNCPOSTFIT;

/** @brief �ر�Ƶ������ģ��
* @return �ɹ�����D_OK, ʧ�ܷ���D_ERR
*/
D_Result	d_scan_close (void) D_FUNCPOSTFIT;

/** @brief ��ʼ��Ƶ������
* @return �ɹ������������, ʧ�ܷ���D_INVALID_HANDLE
*/
D_HScan d_tp_si_scan_create (D_TpSiScanTaskConfig config)D_FUNCPOSTFIT;

/** @brief ������Ƶ��si����
* @param hscan	�������
* @return �ɹ�����D_OK, ʧ�ܷ���D_ERR
*/
D_Result d_tp_si_scan_destroy (D_HScan hscan)D_FUNCPOSTFIT;


/** @brief ��ʼ�ֶ�����
* @return �ɹ������������, ʧ�ܷ���D_INVALID_HANDLE
*/
D_HScan		d_manual_scan_create (D_ScanTaskConfig config) D_FUNCPOSTFIT;

/** @brief �����ֶ�����
* @param hscan	�������
* @param store	�Ƿ�洢�������
* @return �ɹ�����D_OK, ʧ�ܷ���D_ERR
*/
D_Result	d_manual_scan_destroy (D_HScan hscan, D_Bool store) D_FUNCPOSTFIT;

/** @brief ��ʼ�Զ�����
* @return �ɹ������������, ʧ�ܷ���D_INVALID_HANDLE
*/
D_HScan d_auto_scan_create (D_ScanTaskConfig config) D_FUNCPOSTFIT;
/** @brief �����Զ�����
* @param hscan	�������
* @param store	�Ƿ�洢�������
* @return �ɹ�����D_OK, ʧ�ܷ���D_ERR
*/
D_Result	d_auto_scan_destroy (D_HScan hscan, D_Bool store) D_FUNCPOSTFIT;

/** @brief ��ʼEPG��Ŀ������
* @param priority �������ȼ�
* @param ScanMode	����ģʽ
* @param btime_scan �Ƿ�ʱ��
* @param pf_time	��ʱ��ʱ���¼�ʱ��ms
* @param sch_time ��ʱ��ʱ��ϸ�¼�ʱ��ms
* @param[in] find_srvid_mode ���������Ҵ�����ķ���ķ�ʽ
* @return �ɹ������������, ʧ�ܷ���D_INVALID_HANDLE
*/
D_HScan d_epg_scan_create(D_S8 priority, D_EPGScanMode ScanMode,D_Bool btime_scan,D_U32 pf_time,D_U32 sch_time,D_EPGFindSrvidMode find_srvid_mode)D_FUNCPOSTFIT; 

/** @brief ����EPG��Ŀ������
* @param hscan	�������
* @return �ɹ�����D_OK, ʧ�ܷ���D_ERR
*/
D_Result	d_epg_scan_destroy (D_HScan hscan) D_FUNCPOSTFIT;

/** @brief ��ʼatv�ֶ�����
* @return �ɹ������������, ʧ�ܷ���D_INVALID_HANDLE
*/
D_HScan		d_atv_manual_scan_create (D_ScanTaskConfig config) D_FUNCPOSTFIT;

/** @brief ����atv�ֶ�����
* @param hscan  �������
* @param store  �Ƿ�洢�������
* @return �ɹ�����D_OK, ʧ�ܷ���D_ERR
*/
D_Result d_atv_manual_scan_destroy (D_HScan hscan, D_Bool store) D_FUNCPOSTFIT;

/** @brief ��ʼatv�Զ�����
* @return �ɹ������������, ʧ�ܷ���D_INVALID_HANDLE
*/
D_HScan d_atv_auto_scan_create (D_ScanTaskConfig config) D_FUNCPOSTFIT;

/** @brief ����atv�Զ�����
* @param hscan  �������
* @param store  �Ƿ�洢�������
* @return �ɹ�����D_OK, ʧ�ܷ���D_ERR
*/
D_Result d_atv_auto_scan_destroy (D_HScan hscan, D_Bool store) D_FUNCPOSTFIT;

/** @brief ��ʼatväɨ
* @return �ɹ������������, ʧ�ܷ���D_INVALID_HANDLE
*/
D_HScan d_atv_blind_scan_create (D_ScanTaskConfig config) D_FUNCPOSTFIT;

/** @brief ����atväɨ
* @param hscan  �������
* @param store  �Ƿ�洢�������
* @return �ɹ�����D_OK, ʧ�ܷ���D_ERR
*/
D_Result d_atv_blind_scan_destroy (D_HScan hscan, D_Bool store) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
