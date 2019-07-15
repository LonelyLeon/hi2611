/** @file
* @brief 定制搜索相关接口与数据定义
* @author 覃宜
* @date 2013-7-05 覃宜: 建立文件
*/

#ifndef _D_STB_SCAN_H_
#define _D_STB_SCAN_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dScan.h"


extern D_AutoScanOp DVBC_AutoScan_Op;
extern D_ManualScanOp DVBC_ManualScan_Op;

extern D_AutoScanOp DVBT_AutoScan_Op;
extern D_ManualScanOp DVBT_ManualScan_Op;

extern D_AtvManualScanOp ATV_ManualScan_Op;
extern D_AtvAutoScanOp ATV_AutoScan_Op;

extern D_AutoScanOp DVBS_AutoScan_Op;
extern D_ManualScanOp DVBS_ManualScan_Op;

/** @brief 搜索结果排序方式*/
typedef enum {
	D_SCAN_SORT_MODE_NOT 	= 0,    /*不排序*/
	D_SCAN_SORT_MODE_TS		= 1,    /*频点,即频率*/
	D_SCAN_SORT_MODE_SRVID 	= 2,    /*service id*/
	D_SCAN_SORT_MODE_LCN 	= 3,    /*逻辑频道号*/
	D_SCAN_SORT_MODE_FREECA = 4,    /*免费/加扰*/
	D_SCAN_SORT_MODE_NAME 	= 5,    /*节目名*/
	D_SCAN_SORT_MODE_TSID   = 6,    /*TSID排序, TSID相同，按freq排*/
	D_SCAN_SORT_MODE_TSID_SRVID = 7,  /*不同频点按照TSID排，同频点内的节目按照serviceID排序, TSID相同，按freq排*/
	D_SCAN_SORT_MODE_CAFREE_TS_SRVID = 8,  /*先按加密/免费排成两段，段内不同频点按照频点排，频点内的节目按照serviceID排序*/
	
	D_SCAN_SORT_MODE_TS_CONTRARY,                /*频点倒序*/
	D_SCAN_SORT_MODE_SRVID_CONTRARY,         /*service id 倒序*/
	D_SCAN_SORT_MODE_LCN_CONTRARY,           /*逻辑频道号倒序*/
	D_SCAN_SORT_MODE_FREECA_CONTRARY,        /*免费/加扰倒序*/
	D_SCAN_SORT_MODE_NAME_CONTRARY,          /*节目名倒序*/	
	
	D_SCAN_SORT_MODE_OTHERS	
}D_ScanSortMode;

/*搜索类型*/
typedef enum
{
	STB_SCAN_TYPE_MANUAL = 0,/*手动搜索*/
	STB_SCAN_TYPE_AUTO = 1,/*自动搜索*/
	STB_SCAN_TYPE_FULL = 2,/*全频段搜索*/
	STB_SCAN_TYPE_LIST = 3,/*预置搜索*/
	STB_SCAN_TYPE_TP = 4,/*转发器搜索*/
	STB_SCAN_TYPE_SINGLE_SATELLITE = 5,/*单卫星搜索*/
	STB_SCAN_TYPE_OTHERS
}D_StbScanType;

/*搜索模式*/
typedef enum
{
	STB_SCAN_MODE_BLIND = 0,      /*盲扫*/
	STB_SCAN_MODE_PRESET = 1,              /*预制搜索*/
	STB_SCAN_MODE_OTHERS
}P_StbScanMode;

/*搜索节目类型*/
typedef enum
{
	STB_SCAN_PROG_TYPE_TV_RADIO = 0, /*电视+广播*/
	STB_SCAN_PROG_TYPE_TV = 1,          /*电视*/
	STB_SCAN_PROG_TYPE_RADIO = 2,  /*广播*/
	STB_SCAN_PROG_OTHERS
}P_StbScanProgType;

/*应用搜索配置*/
typedef struct
{
    D_Bool  valid;
    D_StbScanType   type;
    D_U32 satelliteNo;
    D_FEndParam	fendparam;	/**< 频点信息*/
    D_FEndType   fendtype;		/**< 前端类型*/	    
    D_U32   freeFlag;
    P_StbScanProgType progType; 
    P_StbScanMode mode;
    D_Bool  netFlag;
}P_ScanConfig;

#define CA_FLAG_IN_PMT 0x01
#define CA_FLAG_IN_SDT 0x02


/**/
typedef struct
{
	D_FEndFreq start_freq;
	D_FEndFreq end_freq;
	D_FEndBandWitch band;
}D_WaveBand;

/** @brief 搜索后排序所用的dbtsid列表*/
D_Result p_scan_sort_srv_set_dbtsid_list(D_ID *list, D_U32 cnt)D_FUNCPOSTFIT;

/** @brief 对搜索的结果进行排序，冒泡排序法
* @param [in][out] srvlist 业务链表
* @param [in] mode 排序方式
* @return 成功D_OK, 失败D_ERR
*/
D_Result p_scan_sort_srv(D_ScanSrvInfoNode*srvlist, D_ScanSortMode mode)D_FUNCPOSTFIT;

/** @brief 与用户软件配置里的频点屏蔽列表比较，判断频点是否有效
* @return 有效D_TRUE, 无效D_FALSE
*/
D_Bool p_scan_judge_freq_valid(D_U32 freq)D_FUNCPOSTFIT;

/** @brief 对数据库的结果进行排序
* @param [in] type 电视广播
* @param [in] mode 排序方式
* @param [in] reset_num 是否重新设置频道号
* @return 成功D_OK, 失败D_ERR
*/
D_Result p_scan_sort_all_srv(D_DBSrvType type, D_ScanSortMode mode, D_Bool reset_num)D_FUNCPOSTFIT;

/** @brief 开始手动搜索
* @param config 搜索配置
* @return 成功返回搜索句柄, 失败返回D_INVALID_HANDLE
*/
D_HScan p_atv_manual_scan_create (D_ScanTaskConfig config) D_FUNCPOSTFIT;

/** @brief 结束手动搜索
* @param hscan  搜索句柄
* @param store  是否存储搜索结果
* @return 成功返回D_OK, 失败返回D_ERR
*/
D_Result p_atv_manual_scan_destroy (D_HScan hscan, D_Bool store) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif

