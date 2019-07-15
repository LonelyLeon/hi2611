/** @file
* @brief SI私有表、私有描述符分析模块
* @author 覃宜
* @date 2013-08-30 覃宜: 建立文件
*/

#ifndef _D_PROJECT_SI_PARSE_H_
#define _D_PROJECT_SI_PARSE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dMMan.h"
#include "dTypes.h"
#include "dFEnd.h"
#include "dSI.h"
#include "dDescr.h"
#include "dSIParse.h"



/* 私有tag 定义*/
#define P_DESCR_LOADER_TAG		0x85    /*Haier ic 升级描述符*/
#define P_YONGXIN_DESCR_LOADER_TAG 0xa1 /*永新升级描述符*/
#ifdef D_CA_SUPPORT_XGCA                
#define DESCR_CDXG_SERVICE_UPDATE			 0x86
#define CDXG_DESCR_LEN	10
#endif
#define P_DESCR_ABV_LCN_TAG		0x83    /*LCN 逻辑频道号描述符*/

#define P_DESCR_DSAD_TAG		0xA6    /*德赛广告描述符*/
#define P_DESCR_MGAD_TAG		0xFE    /*三洲广告描述符*/
#define P_DESCR_DIVIAD_TAG			0x84    /*数视通广告描述符*/
#define P_DESCR_DVTAD_TAG			0xAF //0x89    /*数码视讯广告描述符*/


#ifdef D_STB_SUPPORT_HAIER_PROGRAM_VERSION
#ifndef P_DESCR_HAIER_PROGRAM_VERSION_TAG
#define P_DESCR_HAIER_PROGRAM_VERSION_TAG 0xC5    /*Haier节目版本号描述符*/
#endif
#endif

/*私有描述符长度定义*/
#define ABV_LCN_DESCR_BODY_LEN	 		(4)





/** @brief Haier ic 升级描述符内部数据描述*/
typedef struct 
{
	D_List						list;
	D_U8						download_table_id; 
	D_U16						download_pid;
	D_U32						download_info_len;
	D_U32						hardware_version;
	D_U32						software_version;
	D_U32						stb_sn_start;
	D_U32						stb_sn_end;
	D_U8						upgrade_mode;
	D_Descr						*delivery; /*内部描述系统类型-c \ -t \ -s*/
}D_Loader_Descr;

/** @brief Haier ic 升级描述符tag:0x85*/
typedef struct 
{
	D_List	 list;
	D_U8		 tag;
	D_U16						manufacturer_code;
	D_Loader_Descr	*loader_list;
}D_Loader;


#ifdef D_CA_SUPPORT_XGCA                
/** @brief 成都新光节目更新描述符*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_U8		 update_flag;
	D_U8		 version_number;
	D_U16      fm_pid;
} D_CDXGDescr;
#endif

/** @brief LCN逻辑频道号描述符*/
typedef struct {
    D_List	    list;
    D_U8	    tag;
    D_U16	    srv_id;
    D_U16       lcn;
    D_U32   reserved;
} D_LCNDescr;

/** @brief 德赛广告描述符*/
typedef struct {
    D_List	    list;
    D_U8	    tag;
    D_U16	    datapid;
    D_U32   reserved;
} D_DSADDescr;

/** @brief三洲广告描述符*/
typedef struct {
    D_List	    list;
    D_U8	    tag;
    D_U16	    picpid;
    D_U16	    txtpid;
    D_U16	    corpid;
} D_MGADDescr;

/** @brief通用描述符，
用户自己分析private_dat里的数据*/
typedef struct {
    D_List	    list;
    D_U8	    tag;
    D_U8	    len;
    D_U8        *dat;
} D_NormalDescr;

/** @brief 节目版本描述符*/
typedef struct {
    D_List	    list;
    D_U8	    tag;
    D_U8	    force;    
    D_U8	    version;
    D_U8        match;
    D_U16	    match_code;
} D_HrProgramVersionDescr;


/** @brief 打开si私有描述符解析功能(注册私有解析函数)
* @param 无
* @return 无
*/
void p_private_si_parse_open (void) D_FUNCPOSTFIT;


/** @brief 关闭si私有描述符解析功能(反注册私有解析函数)
* @param 无
* @return 无
*/
void p_private_si_parse_close (void) D_FUNCPOSTFIT;



/** @brief 分析一个xxx section
* @param [in] buf	缓冲区地址
* @param [in]length	缓冲区大小
* @param [in]hmm		内存管理器句柄,函数通过此句柄分配内存
* @return 成功返回PAT结构链表,失败返回NULL
*/
D_List*	p_si_parse_xxx (D_U8 *buf, D_S16 length, D_HMMan hmm) D_FUNCPOSTFIT;






#ifdef  __cplusplus
}
#endif

#endif
