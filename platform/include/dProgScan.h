/**@defgroup MonitorTable SI����
*@{*/
/** @file
* @brief ��Ŀ����SI����ģ��
* @author ����
* @date 2006-622 ����: �����ļ�
* @date 2013-05-16 lc: ͳһƽ̨, ��������
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
/** @brief Ƶ��������PMT��Ŀ*/
#define D_PS_PROG_MAP_CNT		(128)

/** @brief ��Ŀ����Ϣ*/
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

/** @brief ����ȫ����Ŀ�����Ϣ*/
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

/** @brief ����pat����pmt������ص���ʱ������Ϣ*/
typedef struct {
	D_U8			prog_map_cnt;
	D_ProgMap		prog_maps[D_PS_PROG_MAP_CNT];
} D_ProgTempPat;

/** @brief ��ʼ�����ݽṹ
*@param[in] htv ��Ŀ���
*@return ps ��Ŀ��Ϣ 
*/
D_ProgScan*	d_prog_scan_new (D_Handle htv) D_FUNCPOSTFIT;

/** @brief ����ʼ�����ݽṹ
*@param[in] ps ��Ŀ���
*@return D_ERR ʧ�� D_OK �ɹ� 
*/
D_Result	d_prog_scan_free (D_ProgScan *ps) D_FUNCPOSTFIT;

/** @brief ������ݽṹ
*@param[in] ps ��Ŀ���
*@return D_ERR ʧ�� D_OK �ɹ� 
*/
D_Result	d_prog_scan_clear (D_ProgScan *ps) D_FUNCPOSTFIT;

/** @brief �趨��ǰTS
*@param[in] ps ��Ŀ���
*@param[in] net ����D_id
*@param[in] ftype ǰ������
*@param[in] param ǰ�˲���
*@param[in] ts_id ת����D_id
*@param[in] org_net_id ����id
*@return D_ERR ʧ�� D_OK �ɹ� 
*/
D_Result	d_prog_scan_set_ts (D_ProgScan *ps, D_DBNetID net, D_FEndType ftype, D_FEndParam *param, D_U16 ts_id, D_U16 org_net_id) D_FUNCPOSTFIT;

/** @brief �õ�һ����Ŀ��PMT
*@param[in] ps ��Ŀ���
*@param[in] prog_num ��Ŀ��
*@return 	prog ��Ŀ��Ϣ
*/
D_ProgMap*	d_prog_scan_get_pmt (D_ProgScan *ps, D_U16 prog_num) D_FUNCPOSTFIT;

/** @brief ����PAT
*@param[in] ps ��Ŀ���
*@param[in] buf ����
*@param[in] size ���ݴ�С
*@return D_ERR ʧ�� D_OK �ɹ� 
*/
D_Result	d_prog_scan_parse_pat (D_ProgScan *ps, D_U8 *buf, D_Size size) D_FUNCPOSTFIT;

/** @brief ����PMT
*@param[in] ps ��Ŀ���
*@param[in] buf ����
*@param[in] size ���ݴ�С
*@return D_ERR ʧ�� D_OK �ɹ� 
*/
D_Result	d_prog_scan_parse_pmt (D_ProgScan *ps, D_U8 *buf, D_Size size) D_FUNCPOSTFIT;

/** @brief ����CAT
*@param[in] ps ��Ŀ���
*@param[in] buf ����
*@param[in] size ���ݴ�С
*@return D_ERR ʧ�� D_OK �ɹ� 
*/
D_Result	d_prog_scan_parse_cat (D_ProgScan *ps, D_U8 *buf, D_Size size) D_FUNCPOSTFIT;

/** @brief ����TDT TOT
*@param[in] ps ��Ŀ���
*@param[in] buf ����
*@param[in] size ���ݴ�С
*@return D_ERR ʧ�� D_OK �ɹ� 
*/
D_Result	d_prog_scan_parse_tdt (D_ProgScan *ps, D_U8 *buf, D_Size size) D_FUNCPOSTFIT;

/** @brief ����NIT
*@param[in] ps ��Ŀ���
*@param[in] buf ����
*@param[in] size ���ݴ�С
*@return D_ERR ʧ�� D_OK �ɹ� 
*/
D_Result	d_prog_scan_parse_nit (D_ProgScan *ps, D_U8 *buf, D_Size size) D_FUNCPOSTFIT;

/** @brief ����SDT
*@param[in] ps ��Ŀ���
*@param[in] buf ����
*@param[in] size ���ݴ�С
*@return D_ERR ʧ�� D_OK �ɹ� 
*/
D_Result	d_prog_scan_parse_sdt (D_ProgScan *ps, D_U8 *buf, D_Size size) D_FUNCPOSTFIT;
#ifdef  __cplusplus
}
#endif

#endif
/**@}*/


