/**@defgroup MonitorTable SI表监控
*@{*/
/** @file
* @brief 节目播放SI搜索模块
* @author 龚克
* @date 2006-622 龚克: 建立文件
* @date 2013-05-16 lc: 统一平台, 代码整理
*/

#ifndef _D_PROG_SCAN_H_
#define _D_PROG_SCAN_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dAV.h"
#include "dFMan.h"
#include "dDBase.h"
#include "dFEnd.h"
#include "dDemux.h"
#include "dQueue.h"
#include "dMsg.h"
#include "dMMan.h"
#include "dSIParse.h"
#include "dScan.h"
/** @brief 频点中最大的PMT数目*/
#define D_PS_PROG_MAP_CNT		(128)

/** @brief 节目的信息*/
typedef struct {
	D_TabMask	*pmt_mask;
	D_U16			pmt_pid;
	D_U8			pmt_version;
	D_U16			prog_num;
	D_U16			vid_pid;
	D_VidCodecType	vid_codec;
	D_U16			aud1_pid;
	D_AudCodecType	aud1_codec;
	D_U16			aud2_pid;
	D_AudCodecType	aud2_codec;
    	D_U16			aud3_pid;
	D_AudCodecType	aud3_codec;
	D_U16			aud4_pid;
	D_AudCodecType	aud4_codec;    
	D_U16			pcr_pid;
	D_U16			ecm_ca_sys_id;
	D_U16			ecm_v_pid;
	D_U16			ecm_a1_pid;
	D_U16			ecm_a2_pid;
	D_U16			ecm_a3_pid;
	D_U16			ecm_a4_pid;
} D_ProgMap;

/** @brief 保存全部节目相关信息*/
typedef struct {
	D_Handle		htv;
	D_HQueue	hq;
	D_HMMan		hmm;
	D_HMMan		hsi_mm;
	D_DBNetID	db_net_id;
    D_ID		db_ts_id;
	D_FEndType	ftype;
	D_FEndParam	fparam;
	D_U16			ts_id;
	D_U16			org_net_id;
	D_U8		 	*buf;
	D_U8			prog_map_cnt;
	D_U8			pat_version;
	D_U8			cat_version;
	D_U8			nit_version;
	D_Bool			get_tdt;
	D_U16			emm_ca_sys_id;
	D_U16			emm_pid;
	D_U8   			sdt_version;//add for sdt 
	D_TabMask		*nit_mask;
	D_TabMask		*pat_mask;
	D_TabMask		*cat_mask;
	D_TabMask		*sdt_mask;//add for sdt 	
	D_HDemux		pat_demux;
	D_HDemux		pmt_demux;
	D_HDemux		tdt_demux;
	D_HDemux		cat_demux;
	D_HDemux		nit_demux;
	D_HDemux		sdt_demux;//add for sdt 
	D_U8			si_buf[DEMUX_DEFAULT_BUFFERSIZE];	
	D_ProgMap		prog_maps[D_PS_PROG_MAP_CNT];
       D_Bool               power_on_checking;
} D_ProgScan;

/** @brief 保存pat中与pmt搜索相关的临时数据信息*/
typedef struct {
	D_U8			prog_map_cnt;
	D_ProgMap		prog_maps[D_PS_PROG_MAP_CNT];
} D_ProgTempPat;

/** @brief 初始化数据结构
*@param[in] htv 节目句柄
*@return ps 节目信息 
*/
D_ProgScan*	d_prog_scan_new (D_Handle htv) D_FUNCPOSTFIT;

/** @brief 反初始化数据结构
*@param[in] ps 节目句柄
*@return D_ERR 失败 D_OK 成功 
*/
D_Result	d_prog_scan_free (D_ProgScan *ps) D_FUNCPOSTFIT;

/** @brief 清空数据结构
*@param[in] ps 节目句柄
*@return D_ERR 失败 D_OK 成功 
*/
D_Result	d_prog_scan_clear (D_ProgScan *ps) D_FUNCPOSTFIT;

/** @brief 设定当前TS
*@param[in] ps 节目句柄
*@param[in] net 网络D_id
*@param[in] ftype 前段类型
*@param[in] param 前端参数
*@param[in] ts_id 转发器D_id
*@param[in] org_net_id 网络id
*@return D_ERR 失败 D_OK 成功 
*/
D_Result	d_prog_scan_set_ts (D_ProgScan *ps, D_DBNetID net, D_FEndType ftype, D_FEndParam *param, D_U16 ts_id, D_U16 org_net_id) D_FUNCPOSTFIT;

/** @brief 得到一个节目的PMT
*@param[in] ps 节目句柄
*@param[in] prog_num 节目号
*@return 	prog 节目信息
*/
D_ProgMap*	d_prog_scan_get_pmt (D_ProgScan *ps, D_U16 prog_num) D_FUNCPOSTFIT;

/** @brief 分析PAT
*@param[in] ps 节目句柄
*@param[in] buf 数据
*@param[in] size 数据大小
*@return D_ERR 失败 D_OK 成功 
*/
D_Result	d_prog_scan_parse_pat (D_ProgScan *ps, D_U8 *buf, D_Size size) D_FUNCPOSTFIT;

/** @brief 分析PMT
*@param[in] ps 节目句柄
*@param[in] buf 数据
*@param[in] size 数据大小
*@return D_ERR 失败 D_OK 成功 
*/
D_Result	d_prog_scan_parse_pmt (D_ProgScan *ps, D_U8 *buf, D_Size size) D_FUNCPOSTFIT;

/** @brief 分析CAT
*@param[in] ps 节目句柄
*@param[in] buf 数据
*@param[in] size 数据大小
*@return D_ERR 失败 D_OK 成功 
*/
D_Result	d_prog_scan_parse_cat (D_ProgScan *ps, D_U8 *buf, D_Size size) D_FUNCPOSTFIT;

/** @brief 分析TDT TOT
*@param[in] ps 节目句柄
*@param[in] buf 数据
*@param[in] size 数据大小
*@return D_ERR 失败 D_OK 成功 
*/
D_Result	d_prog_scan_parse_tdt (D_ProgScan *ps, D_U8 *buf, D_Size size) D_FUNCPOSTFIT;

/** @brief 分析NIT
*@param[in] ps 节目句柄
*@param[in] buf 数据
*@param[in] size 数据大小
*@return D_ERR 失败 D_OK 成功 
*/
D_Result	d_prog_scan_parse_nit (D_ProgScan *ps, D_U8 *buf, D_Size size) D_FUNCPOSTFIT;

/** @brief 分析SDT
*@param[in] ps 节目句柄
*@param[in] buf 数据
*@param[in] size 数据大小
*@return D_ERR 失败 D_OK 成功 
*/
D_Result	d_prog_scan_parse_sdt (D_ProgScan *ps, D_U8 *buf, D_Size size) D_FUNCPOSTFIT;
#ifdef  __cplusplus
}
#endif

#endif
/**@}*/


