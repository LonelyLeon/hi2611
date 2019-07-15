/** @file
* @brief 频道搜索模块
* @author 龚克
* @date 2005-6-30 龚克: 建立文件
* @date 2013-05-16 lc: 统一平台, 代码整理
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
/***频点SI表搜索，用于手动搜索与自动搜索***/
/**************************************************************/
#define TABLE_MASK_NIT 			0x01
#define TABLE_MASK_PAT 		0x02
#define TABLE_MASK_PMT 		0x04
#define TABLE_MASK_SDT 		0x08
#define TABLE_MASK_SDT_OTH 	0x10
#define TABLE_MASK_CAT 		0x20
#define TABLE_MASK_BAT 		0x40
#define TABLE_MASK_PRIVATES	0x80


/*私有表si搜索配置*/
typedef struct
{
	D_Bool	valid;
	D_U16 	pid;
	D_U8	table_id;
	D_U16	table_ext_id;
	D_U32	timeout;
	D_List*	(*d_si_parse_private)(D_U8 *sec_buf, D_S16 length, D_HMMan hmm) D_FUNCPOSTFIT;
}D_SiScanPrivateConf;


/*单频点si 搜索任务配置信息结构*/
typedef struct 
{
	D_S8 			priority;			/*任务优先级*/
	D_HQueue 		hqueue;			/*注册任务消息队列*/
	D_Bool			lock_enable;	/*是否需要锁定频点*/
	D_FEndParam	 	fend_param;	/*频点参数*/
	D_FEndType		fend_type;		/*频点类型*/
	D_FEndAttr		fend_attr;		/*前端设备属性*/
	D_HMMan		hmm;			/*内存管理句柄*/
	D_HFMan 		hfman;			/*前端管理器句柄*/
	D_U16 			table_mask;		/*表搜索配置*/
	D_U32			pat_timeout;	/*PAT表超时*/
	D_U32			pmt_timeout;	/*PMT表超时*/
	D_U32			nit_timeout;		/*NIT表超时*/
	D_U32			sdt_timeout;		/*SDT表超时*/
	D_U32			sdt_oth_timeout;/*SDT OTH表超时*/
	D_U32			cat_timeout;		/*CAT表超时*/
	D_U32			bat_timeout;	/*BAT表超时*/
	D_U16			network_id;		/*NIT表network_id*/	

       D_Bool                  cmp_bat;    /*是否要比较bouqid*/
       D_U8			bouq_cnt;  /*要搜索的bat个数*/    
	D_U16			*bouq_id;	/*BAT表业务群id (数组指针)*/

	D_Bool			progress_enable;/*是否上报搜索进度*/
	D_SiScanPrivateConf private[2];	/*搜索私有表时的配置*/

} D_TpSiScanTaskConfig;


/*频点si 搜索结果数据*/
typedef struct 
{
	D_FEndParam	 param;	/*频点参数*/
	D_FEndType    type;	/*频点类型*/
	D_Bool          locked;	/*频点是否锁定*/
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


/** @brief 自动搜索模式*/
typedef enum {
	D_AUTO_SCAN_MODE_NIT,			/* NIT 搜索*/
	D_AUTO_SCAN_MODE_TP,				/* 频点列表*/		
	D_AUTO_SCAN_MODE_FULL,			/* 全频段搜索*/
	D_AUTO_SCAN_MODE_BLIND,			/* 盲扫搜索,锁定一个频点后马上搜SI*/	
	D_AUTO_SCAN_MODE_ANALOG,		/*模拟信号自动搜索*/
	D_AUTO_SCAN_MODE_OTHER			/* 其它*/
} D_AutoScanMode;


/** @brief 搜索时解析类型*/
typedef enum {
	D_SCAN_PARSE_TP,		/*搜到一个频点后立即解析*/
	D_SCAN_PARSE_GROUP,	/*搜完一组后就解析*/
	D_SCAN_PARSE_ALL,		/*全部搜完后才解析*/
	D_SCAN_PARSE_OHERS	/*其它*/
} D_ScanParseMode;



/** @brief 自动搜索时与nit表相关的策略*/
typedef enum {
	D_NIT_STRA_NONE,				/*找到nit后不按nit搜索*/
	D_NIT_STRA_NOT_COVER,		/*找到nit后不覆盖之前搜索到的频点*/
	D_NIT_STRA_ALL_COVER,			/*找到nit后覆盖之前搜索到的所有频点*/
	D_NIT_STRA_SOME_COVER,		/*找到nit后，nit里没有的频点的搜索结果将清除*/
	D_NIT_STRA_OTHER				/*其它*/
}D_AutoScanNitStrategy;



/** @brief 频道搜索任务配置(自动/手动)*/
typedef struct
{
	D_U32			buf_size;		/*内存空间大小(byte)*/
	D_S8 			priority;			/*任务优先级*/
	D_HQueue 		hqueue;			/*注册任务消息队列*/
	D_HFMan 		hfman;			/*前端管理器句柄*/
	
	D_U32			scan_type;		/*搜索类型*/
	D_U32	        parse_mode;	/*解析模式(用于自动搜索)*/
	D_Bool			srv_name_en;	/*是否通知菜单搜索到的服务名称*/
	D_DBID 			db_net_id;		/*db_net_id   = 0 */
	D_Bool			sdt_srv_type_en;	/*是否参考sdt表里的srv type来判断服务的类型(TV/Radio/others...), atv搜索时用于控制是否向应用发送进度消息*/       
	D_Bool          group_end_save; /*一组结束后是否直接保存*/
	D_FEndType		fend_type;		/*频点类型*/	
	D_FEndParam		fend_param;	/*传递频点参数，可用于主频点或是手动搜索，atv搜索时用于传递音视频模式*/

	D_DBAnteInfo 	AnteInfo;		/*传递的天线参数*/
	D_DBSateInfo	SateInfo;		/*传递的卫星与天线参数*/
	D_DBID		    db_sat_id;		/*卫星id*/ 
	
	D_FEndFreq		startfreq;		/*起始频率，可用全频段搜索*/
	D_FEndBandWitch	bandwitch;		/*带宽，可用全频段搜索*/
	D_FEndFreq		endfreq;		/*结束频率，可用全频段搜索*/
	D_FEndFreq		stepfreq;		/*步进频率，可用全频段搜索*/    

	D_U32			Reserved;		/*备用参数*/
	D_Ptr			pReserved;		/*备用参数指针，定制代码自行解析*/
	D_Ptr			pScanOp;		/*注册的操作，与定制有关的操作*/
} D_ScanTaskConfig;



/*注册的自动搜索的操作*/
typedef struct 
{
	D_Result (*auto_scan_init)(D_ASGroup **group, D_U32*group_cnt, D_ScanTaskConfig *as_config, D_HMMan hmm);
	D_Result (*auto_scan_store)(D_ASGroup **group, D_U32 group_cnt, D_ScanTaskConfig *as_config);
	D_Result (*auto_scan_destroy)(D_ASGroup **group, D_U32 group_cnt, D_ScanTaskConfig *as_config);
}D_AutoScanOp;


/*将要搜索的频点参数列表*/
typedef struct
{
	D_List list;
	D_FEndParam	fendparam;		/*频点参数*/
}D_ScanFendParamNode;


/*频点信息*/
typedef struct
{
    D_FEndParam param;  
    D_U16   ts_id;
    D_U16   org_net_id;
    D_U8    db_net_id;
    D_U8    db_sat_id;
    D_U8    prog_cnt;	/*该频点下业务数*/
    D_U8    tv_cnt;		/*该频点下电视业务数*/
    D_U8    radio_cnt;	/*该频点下广播业务数*/
    D_U8    other_cnt;	/*该频点下其它业务数*/  
    D_U8    tuner_type;
    D_U8    found_nit;	/*频点是否有nit*/
    D_U16   version;	/*节目版本(或nit 版本)  (应用来赋值)初始为-1*/    
    D_U8    quality;    /*信号质量*/
}D_ScanTsInfo;


/*频点搜索结果信息链表节点*/
typedef struct
{
    D_List  list;   
    D_U8    valid;		/*频点是否有效*/
    D_U16   ts_no;		/*频点序号(用于与服务关联)*/
    D_ScanTsInfo    ts_info;	/*频点信息*/    
    D_ScanTp    *scantp;	/*频点下搜索到的表描述*/
}D_ScanTsInfoNode;


#define SRV_CA_MASK_PMT		0x01	/*PMT表描述符里加扰描述*/
#define SRV_CA_MASK_PMT_ES	0x02	/*PMT表基础流描述符里加扰描述*/
#define SRV_CA_MASK_SDT		0x04	/*SDT表里free_ca*/

#define SRV_NAME_LEN (32)   /*服务名空间长度*/ 
#define PROV_NAME_LEN (32)   /*提供商名空间长度*/ 

/*搜索时业务信息*/
typedef struct
{  
    D_Char  name[SRV_NAME_LEN];   /*服务名*/
    
    /*流里相关的id*/
    D_U16   srv_id;
    D_U16   pmt_pid;
    D_U16   pcr_pid;
    D_U16   vid_pid;
    D_U16   aud1_pid;
    D_U16   aud2_pid;
    D_U16   aud3_pid;
    D_U16   aud4_pid;
    D_U8 	valid;		/*服务是否有效*/   
    
    /*音视频编码类型MPEG2/AVS/AC3...*/
    D_U8    vid_codec;
    D_U8    aud1_codec; 
    D_U8    aud2_codec;
    D_U8    aud3_codec;
    D_U8    aud4_codec;
    D_U8    aud_select;     /*第几个伴音*/  
    D_U8	aud_track;	/*声道*/  
	D_U8	sdt_srv_type;
    D_U8	srv_type;       /*服务类型:TV/Radio/Data/...*/    
    D_U8	ca_mask;		/*加扰描述*/   
    
    D_S8    volume;        /*音量补偿值*/   
    D_U16   chan_lcn;       /*逻辑频道号*/
    D_U64   bouq_mask;  /*对应的业务群*/
    D_Char  prov_name[PROV_NAME_LEN];   /*提供商名*/
}D_ScanSrvInfo;


/*搜索时业务信息链表节点*/
typedef struct
{
    D_List list;    
    D_U8 	valid;		/*服务是否有效*/
    D_U16   ts_no;		/*对应的搜索的频点序号*/    
    D_ScanSrvInfo srvinfo;	/*服务信息*/
}D_ScanSrvInfoNode;

/*搜索时业务信息*/
typedef struct
{
	D_U8	type;		/*sdt_srv_type 描述符里描述的类型*/
	D_DBSrvInfo *srvinfo;		/*服务信息*/
}D_SdtSrvInfo;

/*频点信息初始化*/
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

/*搜索时业务信息初始化*/
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


/*频点信息初始化*/
#define D_SCANTSINFO_TO_DBSRVINFO(_dbt, _st)\
		D_MACRO_BEGIN\
			(_dbt)->param = (_st)->param;\
			(_dbt)->db_net_id = (D_U8)((_st)->db_net_id);\
			(_dbt)->ts_id = (D_U16)((_st)->ts_id);\
			(_dbt)->org_net_id = (D_U16)((_st)->org_net_id);\
			(_dbt)->db_sat_id = (D_U8)((_st)->db_sat_id);\
			(_dbt)->tuner_type = (D_U8)((_st)->tuner_type);\
		D_MACRO_END

/*搜索时业务信息初始化*/
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
/*一个频点搜索的结果*/
typedef struct 
{
    D_HMMan         hmm;                /*内存管理句柄*/
	D_FEndType		fend_type;			/*频点类型*/
	D_DBID			db_net_id;
	D_Bool			locked_flag;			/**< 是否锁定频点*/
	D_Bool			found_nit;                  /**< 是否找到nit表*/
       D_U8			nit_version;		        /**< nit表版本号*/
	D_Bool			found_chan_ver;		/**< 是否找节目版本号*/
	D_U8			chan_version;		/**< 节目版本号*/

      	D_FEndParam	 main_fparam;	/*找到nit表的主频点参数*/

	D_DBAnteInfo 	*pAnteInfo;			/*天线参数*/
	D_DBSateInfo		*pSateInfo;			/*卫星参数*/

	D_U32			bouq_cnt;			/**< 业务群数目*/
	D_DBBouqInfo	*bouq_info[D_SCAN_MAX_BOUQ_CNT];/**< 业务群信息*/

	D_U32			scan_tsinfo_cnt;				/**< 搜到的频点总数*/
	D_List 		*scan_tsinfo_list;		/**< 搜到的频点列表 D_ScanTsInfoNode*/

    D_ScanTp			*main_tp;			/*主频点si搜索结果(用于nit搜索)*/	
	
	D_List 			*srvList_tv;		/*电视服务链表 D_ScanSrvInfoNode*/
	D_List 			*srvList_radio;		/*广播服务链表 D_ScanSrvInfoNode*/	
	D_List 			*srvList_other;		/*其它服务链表 D_ScanSrvInfoNode*/	

	D_U16			prog_cnt;			/**< 储存搜索节目总数*/
	D_U16			tv_cnt;				/**< 存储电视数目*/
	D_U16			radio_cnt;			/**< 存储广播数目*/
	D_U16			other_cnt;			/**< 其它服务数目*/
}D_ScanResultValue;




typedef struct
{
	D_Result (*group_start)(D_ASGroup *scan_group,D_ScanTaskConfig *as_config, D_HMMan hmm);				/*私有初始化*/
	D_Result (*group_end)(D_ASGroup *scan_group, D_ScanTaskConfig *as_config);			/*私有反初始化*/
	D_Result (*set_tpsiscan_config)(D_ASGroup *scan_group, D_TpSiScanTaskConfig *conf);/*单频点搜索配置*/
	D_Bool (*check_ca_sys_id)(D_U32 type, D_U16 ca_sys_id);		/*检查ca_sys_id*/
	D_Bool (*check_bouq_id)(D_U32 type, D_U16 bouq_id);			/*检查网络bouq_id*/
	D_Result (*group_end_private_op)(D_ASGroup *scan_group, D_HMMan hmm);/*一组频点搜完后的私有操作(直播星用到)*/
	D_Result (*get_freqlist_in_nit)(D_U32 type, D_ScanTsInfoNode *scants, D_FEndParam*fparam, D_U32 *fcnt);/*nit表里提取频率列表信息*/

	D_Result (*get_tp_info)(D_U32 type, D_ScanTsInfoNode *scants, D_ScanResultValue *scanResult);/*提取频点上关心的一些信息*/
	D_Result (*get_private_descrs_in_sdt)(D_U32 type, D_Descr *descr, D_ScanSrvInfo *srvinfo);/*sdt表里提取服务信息*/
	D_Result (*get_srvinfo_in_bat)(D_U32 type, D_ScanTsInfoNode *scants, D_ScanSrvInfo *srv_info, D_ScanResultValue *scanResult);/*bat表里提取服务信息*/
	D_Result (*get_srvinfo_in_nit)(D_U32 type, D_ScanTsInfoNode *scants, D_ScanSrvInfo *srvinfo, D_ScanResultValue *scanResult);/*nit表里提取服务信息*/
	D_Result (*get_srvinfo_in_others)(D_U32 type, D_ScanTsInfoNode *scants, D_ScanSrvInfo *srvinfo, D_ScanResultValue *scanResult);/*其它私有表里提取服务信息*/	
	D_Bool (*check_srv_valid)(D_U32 type, D_ScanSrvInfo *srvinfo);/*检查服务的有效性*/
}D_ASGroupOp;




/*自动搜索时组配置与结果  数据结构定义*/
struct _D_ASGroup
{
	D_U32				type;		/*组搜索类型(自定义、自解释)*/	
    D_U32               group_id;
	D_HFMan 			hfman;			/*前端管理器句柄*/
	D_AutoScanMode		scan_mode;		/*搜索模式*/
	D_AutoScanNitStrategy	nit_strategy;	/*搜索时与nit表相关的策略*/
			
	D_FEndType			fend_type;			/*前端类型*/
	
	D_U32				scanFendParamList_cnt;	/*要搜索的频点数目*/
	D_List 	*scanFendParamList;/*要搜索的频点列表   D_ScanFendParamNode*/

	/*<full===用于全频段搜索*/
	D_FEndParam			*base_fparam;	/*基础参数(记录除频率之外的参数)*/
	D_FEndFreq 			freq_start;		/*起始频率*/
	D_FEndFreq			freq_end;		/*结束频率*/
	D_FEndFreq			freq_step;		/*频率步进*/
	D_FEndFreq			freq_bw;		/*频率带宽(锁定频点后跳过此带宽,>= freq_step)*/	
	/*===full>*/

	D_DBAnteInfo 		AnteInfo;			/*天线参数*/
	D_DBSateInfo			SateInfo;			/*卫星参数*/
 	D_DBID		db_sat_id;			/*卫星id*/   

	/*<blind===用于盲扫*/
	D_U32				blindparam_cnt;		/*有几组盲扫参数*/
	D_FBlindParam		*blindparam;		/*各组盲扫参数*/
	/*===blind>*/
	
	D_Bool				findSrvInfoInMain;/*是否从主频点里查找其它频点里的节目的相关信息*/
    D_Bool			sdt_srv_type_en;	/*是否参考sdt表里的srv type来判断服务的类型(TV/Radio/others...)*/ 

	/*当前组在搜索与解析过程中的操作*/
	D_ASGroupOp		*groupOp;

	D_U8				progress_start;		/*当前组搜索进度的初始值*/
	D_U8				progress_end;		/*当前组搜索进度的最大值*/

	/*=========结果=========*/		
	D_ScanResultValue		scanResult;
    D_Bool have_save;   /*是否已经保存*/
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

/*注册的自动搜索的操作*/
typedef struct 
{
	D_Result (*manual_scan_init)(D_U32 type, D_ScanTaskConfig *ms_config);
	D_Result (*manual_scan_start)(D_U32 type, D_ScanTaskConfig *ms_config);
	D_Result (*manual_scan_store)(D_U32 type, D_ScanTaskConfig *ms_config, D_ScanResultValue*ms_result);
	D_Result (*manual_scan_destroy)(D_U32 type, D_ScanTaskConfig *ms_config, D_ScanResultValue *ms_result);
	D_Result (*set_tpsiscan_config)(D_U32 type, D_TpSiScanTaskConfig *conf);	/*单频点搜索配置*/
	D_Bool (*check_ca_sys_id)(D_U32 type, D_U16 ca_sys_id);		/*检查ca_sys_id*/
	D_Bool (*check_bouq_id)(D_U32 type, D_U16 bouq_id);					/*检查网络bouq_id*/
	D_Result (*get_tp_info)(D_U32 type, D_ScanTsInfoNode *scants, D_ScanResultValue *ms_result);/*提取频点上关心的一些信息*/
	D_Result (*get_private_descrs_in_sdt)(D_U32 type, D_Descr *descr, D_ScanSrvInfo *srvinfo);/*sdt表里提取服务信息*/
	D_Result (*get_srvinfo_in_bat)(D_U32 type, D_ScanTsInfoNode *scants, D_ScanSrvInfo *srv_info, D_ScanResultValue *ms_result);/*bat表里提取服务信息*/
	D_Result (*get_srvinfo_in_nit)(D_U32 type, D_ScanTsInfoNode *scants, D_ScanSrvInfo *srvinfo, D_ScanResultValue *ms_result);/*nit表里提取服务信息*/
	D_Result (*get_srvinfo_in_others)(D_U32 type, D_ScanTsInfoNode *scants, D_ScanSrvInfo *srvinfo, D_ScanResultValue *ms_result);/*其它私有表里提取服务信息*/	
	D_Bool (*check_srv_valid)(D_U32 type, D_ScanSrvInfo *srvinfo);/*检查服务的有效性*/
}D_ManualScanOp;



/** @brief atv 搜索类型*/
typedef enum {
	D_ATV_SCAN_TYPE_AUTO = 0,		/* 自动搜索，按频率表依次搜索*/        
	D_ATV_SCAN_TYPE_FULL,			/* 全频段搜索*/		
	D_ATV_SCAN_TYPE_MANUAL,			/* 手动搜索*/
	D_ATV_SCAN_TYPE_BLIND,
	D_ATV_SCAN_TYPE_OTHER			/* 其它*/
} D_AtvScanType;

/** @brief atv 搜索模式*/
typedef enum {
	D_ATV_SCAN_MODE_NORMAL = 0,			/* 通常类型搜索，参数(音视频类型)确定*/
	D_ATV_SCAN_MODE_TRAVERSAL,			/* 音视频类型遍历*/		
	D_ATV_SCAN_MODE_OTHER			/* 其它*/
} D_AtvScanMode;

typedef struct{
    D_FEndFreq *freq_list;
    D_U32       freq_cnt;
    D_U32       audiomode_cnt;
    D_U32       videomode_cnt;
    D_AudioMode audiomode[16];
    D_VideoMode videomode[16];
}D_AtvScanParam;


/** @brief 注册的atv自动搜索的操作*/
typedef struct 
{
	D_Result (*auto_scan_init)( D_ScanTaskConfig *as_config, D_HMMan hmm);
    D_Result (*auto_scan_locked_action)(D_FEndParam *param, D_Bool locked,D_U16 *cvbs_video_format); /*每锁一个频点后都调用用户的操作*/
	D_Result (*auto_scan_store)(D_ScanResultValue scanResult,D_ScanTaskConfig *as_config);
	D_Result (*auto_scan_destroy)(D_ScanTaskConfig *as_config);
}D_AtvAutoScanOp;

/** @brief 注册的atv手动搜索的操作*/
typedef struct 
{
	D_Result (*manual_scan_init)(D_ScanTaskConfig *ms_config);
	D_Result (*manual_scan_start)(D_ScanTaskConfig *ms_config);
	D_Result (*manual_scan_store)(D_ScanTaskConfig *ms_config, D_ScanResultValue*ms_result);
	D_Result (*manual_scan_destroy)(D_ScanTaskConfig *ms_config, D_ScanResultValue *ms_result);
}D_AtvManualScanOp;


/** @brief 基础流对应音视频类型*/
typedef enum {
	D_ESAV_TYPE_INVALID 		= 0,
	D_ESAV_TYPE_VIDEO 		= 1,
	D_ESAV_TYPE_AUDIO 		= 2,
	D_ESAV_TYPE_PRIVATE 		= 3,	
}D_ESAVType;

#define D_ESAV_AUDIO_LANGUAGE_LENGTH (4)
/** @brief 基础流对应音视频信息*/
typedef struct {
	D_ESAVType	type;
	D_U16	pid;
       D_U16	Private_type;
	D_VidCodecType vid_codec;
	D_AudCodecType aud_codec; 
	D_Char language[D_ESAV_AUDIO_LANGUAGE_LENGTH];
} D_ESAVInfo;

/*解析psi表时钩子数据结构*/
typedef struct {
    D_List		*psis;
    D_FEndType fend_type;
    D_Result result;
} D_ParsePsi;

/** @brief EPG搜索模式*/
typedef enum {
	D_SCAN_MODE_PF_EPG 	= 1,
	D_SCAN_MODE_SCH_EPG = 2,
	D_SCAN_MODE_PF_OTH_EPG	= 4,
	D_SCAN_MODE_SCH_OTH_EPG	= 8,
	D_SCAN_MODE_TDT_TOT_EPG	= 16,	/*是否搜索时间表 tdt tot*/
	D_SCAN_MODE_ALL_PF_EPG	= D_SCAN_MODE_PF_EPG | D_SCAN_MODE_PF_OTH_EPG,
	D_SCAN_MODE_ALL_SCH_EPG	= D_SCAN_MODE_SCH_EPG | D_SCAN_MODE_SCH_OTH_EPG,
	D_SCAN_MODE_ALL_ACT_EPG = D_SCAN_MODE_PF_EPG | D_SCAN_MODE_SCH_EPG,
	D_SCAN_MODE_ALL_OTH_EPG = D_SCAN_MODE_PF_OTH_EPG | D_SCAN_MODE_SCH_OTH_EPG,
	D_SCAN_MODE_ALL_EPG = D_SCAN_MODE_ALL_ACT_EPG | D_SCAN_MODE_ALL_OTH_EPG
} D_EPGScanMode;

/*brief  EPG FILTER 过滤模式*/
typedef enum {
	EPG_SEARCH_ALL,
	EPG_SEARCH_SERVICE_ID 	= 1,
	EPG_SEARCH_TS_ID = 2,
	EPG_SEARCH_NET_ID	= 4
} D_EPGFilterMode;

/*brief  EPG挂接相应service id 的查找方法*/
typedef enum {
	EPG_FIND_SERVICE_ID_NORMAL,/*常用方式，优先匹配srvid, 多个匹配时再比对ts id*/
	EPG_FIND_SERVICE_ID_ACT_AND_OTH,     /*区分当前频点和其他频点下查找，一般用于卫星项目*/
	EPG_FIND_SERVICE_ID_STANDARD,   /* 严格按dbv标准查找方式，tsid srvid都要匹配*/
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

/*过滤器设置函数*/
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
/*版本非控制*/
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
/*表屏蔽设置函数*/

/** @brief 分配一个表屏蔽数据结构
* @param hmm			内存管理器句柄
* @param sub_cnt	表中最多可容纳的子表数目
* @return 成功返回表屏蔽数据结构数据结构指针，失败返回NULL
*/
D_TabMask*		d_tab_mask_new (D_HMMan hmm, D_U32 sub_cnt) D_FUNCPOSTFIT;

/** @brief 向表屏蔽中增加一个section屏蔽
* @param tab	表屏蔽
* @param tab_ext	表扩展ID
* @param ver			表版本号
* @param sec	section number
* @param last	last section number
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result			d_tab_mask_add (D_TabMask *tab, D_U16 tab_ext, D_U8 ver, D_U8 sec, D_U8 last) D_FUNCPOSTFIT;

/** @brief 清空表屏蔽
* @param tab	表屏蔽
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result			d_tab_mask_clear (D_TabMask *tab) D_FUNCPOSTFIT;

/** @brief 向表屏蔽中增加一个section屏蔽
* @param tab	表屏蔽
* @param tab_ext	表扩展ID
* @param ver			表版本号
* @param sec	section number
* @param last	last section number
* @param seg_last	segment last section number
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result			d_tab_mask_add_ex (D_TabMask *tab, D_U16 tab_ext, D_U8 ver, D_U8 sec, D_U8 last, D_U8 seg_last) D_FUNCPOSTFIT;

/** @brief 检查表屏蔽中全部section是否都收齐
* @param tab	表屏蔽
* @return 如果全部section收齐返回D_TRUE,否则返回D_ERR
*/
D_Bool				d_tab_mask_full (D_TabMask *tab) D_FUNCPOSTFIT;

/** @brief 检查表屏蔽中是否已经含有指定的section
* @param tab	表屏蔽
* @param tab_ext	表扩展ID
* @param ver			表版本号
* @param sec	section number
* @return 如果含有此section返回D_TRUE,否则返回D_ERR
*/
D_Bool				d_tab_mask_is_set (D_TabMask *tab, D_U16 tab_ext, D_U8 ver, D_U8 sec) D_FUNCPOSTFIT;

/** @brief 根据pmt表里一个服务的基础流描述，
设置服务的相关pid与类型(例: 音视频PID与编码类型)。
 * @param[in] es  基础流描述
* @param[out] esav_info  相关pid与类型
* @return 有效返回D_OK, 无效返回D_ERR
* @note 用在节目搜索或监控(不管emm \ecm  pid)
*/
D_Result d_scan_parse_element_stream(D_ElementStream *es, D_ESAVInfo *esav_info) D_FUNCPOSTFIT;


/** @brief 根据sdt表里服务描述符(DESCR_SERVICE)里描述的类型，
设置服务的类型(电视、广播、等其它类型)。
* @param[in][out] *srvinfo  服务数据指针 
* @param[in] sdt_srv_type 描述符里描述的类型
* @return 有效返回D_OK, 无效返回D_ERR
* @note 用在节目搜索或监控
*/
D_Result d_scan_set_srv_type(D_DBSrvInfo *srvinfo, D_U8 sdt_srv_type) D_FUNCPOSTFIT;


/** @brief 打开频道搜索模块
* @return 成功返回D_OK, 失败返回D_ERR
*/
D_Result	d_scan_open (void) D_FUNCPOSTFIT;

/** @brief 关闭频道搜索模块
* @return 成功返回D_OK, 失败返回D_ERR
*/
D_Result	d_scan_close (void) D_FUNCPOSTFIT;

/** @brief 开始单频点搜索
* @return 成功返回搜索句柄, 失败返回D_INVALID_HANDLE
*/
D_HScan d_tp_si_scan_create (D_TpSiScanTaskConfig config)D_FUNCPOSTFIT;

/** @brief 结束单频点si搜索
* @param hscan	搜索句柄
* @return 成功返回D_OK, 失败返回D_ERR
*/
D_Result d_tp_si_scan_destroy (D_HScan hscan)D_FUNCPOSTFIT;


/** @brief 开始手动搜索
* @return 成功返回搜索句柄, 失败返回D_INVALID_HANDLE
*/
D_HScan		d_manual_scan_create (D_ScanTaskConfig config) D_FUNCPOSTFIT;

/** @brief 结束手动搜索
* @param hscan	搜索句柄
* @param store	是否存储搜索结果
* @return 成功返回D_OK, 失败返回D_ERR
*/
D_Result	d_manual_scan_destroy (D_HScan hscan, D_Bool store) D_FUNCPOSTFIT;

/** @brief 开始自动搜索
* @return 成功返回搜索句柄, 失败返回D_INVALID_HANDLE
*/
D_HScan d_auto_scan_create (D_ScanTaskConfig config) D_FUNCPOSTFIT;
/** @brief 结束自动搜索
* @param hscan	搜索句柄
* @param store	是否存储搜索结果
* @return 成功返回D_OK, 失败返回D_ERR
*/
D_Result	d_auto_scan_destroy (D_HScan hscan, D_Bool store) D_FUNCPOSTFIT;

/** @brief 开始EPG节目表搜索
* @param priority 任务优先级
* @param ScanMode	搜索模式
* @param btime_scan 是否定时搜
* @param pf_time	定时搜时简单事件时间ms
* @param sch_time 定时搜时详细事件时间ms
* @param[in] find_srvid_mode 解析完后查找待插入的服务的方式
* @return 成功返回搜索句柄, 失败返回D_INVALID_HANDLE
*/
D_HScan d_epg_scan_create(D_S8 priority, D_EPGScanMode ScanMode,D_Bool btime_scan,D_U32 pf_time,D_U32 sch_time,D_EPGFindSrvidMode find_srvid_mode)D_FUNCPOSTFIT; 

/** @brief 结束EPG节目表搜索
* @param hscan	搜索句柄
* @return 成功返回D_OK, 失败返回D_ERR
*/
D_Result	d_epg_scan_destroy (D_HScan hscan) D_FUNCPOSTFIT;

/** @brief 开始atv手动搜索
* @return 成功返回搜索句柄, 失败返回D_INVALID_HANDLE
*/
D_HScan		d_atv_manual_scan_create (D_ScanTaskConfig config) D_FUNCPOSTFIT;

/** @brief 结束atv手动搜索
* @param hscan  搜索句柄
* @param store  是否存储搜索结果
* @return 成功返回D_OK, 失败返回D_ERR
*/
D_Result d_atv_manual_scan_destroy (D_HScan hscan, D_Bool store) D_FUNCPOSTFIT;

/** @brief 开始atv自动搜索
* @return 成功返回搜索句柄, 失败返回D_INVALID_HANDLE
*/
D_HScan d_atv_auto_scan_create (D_ScanTaskConfig config) D_FUNCPOSTFIT;

/** @brief 结束atv自动搜索
* @param hscan  搜索句柄
* @param store  是否存储搜索结果
* @return 成功返回D_OK, 失败返回D_ERR
*/
D_Result d_atv_auto_scan_destroy (D_HScan hscan, D_Bool store) D_FUNCPOSTFIT;

/** @brief 开始atv盲扫
* @return 成功返回搜索句柄, 失败返回D_INVALID_HANDLE
*/
D_HScan d_atv_blind_scan_create (D_ScanTaskConfig config) D_FUNCPOSTFIT;

/** @brief 结束atv盲扫
* @param hscan  搜索句柄
* @param store  是否存储搜索结果
* @return 成功返回D_OK, 失败返回D_ERR
*/
D_Result d_atv_blind_scan_destroy (D_HScan hscan, D_Bool store) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
