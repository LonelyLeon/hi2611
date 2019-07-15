/**@defgroup MonitorTable SI����
*@{*/
/** @file
* @brief ��Ŀ���ģ��
* @author ����
* @date 2005-7-11 ����: �����ļ�
* @date 2013-06-03 sunzy: ���ý�Ŀ��صĺ�����dtv.c���������ɸ��ļ�
* @date 2013-06-29 sunzy��Ϊ��������Ӷ�ʱ��ع���
* @date 2013-07-25 hegx: ��Ҫ���޸ġ���Ӻ���
*/
#ifndef _D_MONITORTABLE_H_
#define _D_MONITORTABLE_H_

#ifdef  __cplusplus
extern "C"
{
#endif
#include "dTV.h" 
#include "dApp.h"
/** @brief �ص��������Ͷ��� */
typedef D_U8 (*D_NitFunc)(D_FEndType ftype, D_FEndParam fparam);
/** @brief nit����Ʋ��� */ 
typedef struct {
	D_Bool	enable;//ʹ�ܣ�  0---���ܹرգ�Ĭ�ϣ���1-���ܿ�����
	D_U8	moniter_mode;//��ط�ʽ��1---���ݰ汾�ż�أ�ֻ������һ���汾�ŵ���Ϣ�� 2---��ʱ��أ��ȽϽ�Ŀ���֣������һ���͸��¡�    
	D_U8	freq_mode;
	D_U32	time_out;
    D_HTimer time_hand;
    D_NitFunc freq_check;
 } D_NITConfigMoniter;

/** @brief sdt����Ʋ��� */ 
typedef struct {
	D_Bool	enable;//ʹ�ܣ�  0---���ܹرգ�Ĭ�ϣ���1-���ܿ�����
	D_Bool	caenable;//ʹ�ܣ�  0---���ܹرգ�Ĭ�ϣ���1-���ܿ�����
	D_Bool	nameenable;//ʹ�ܣ�  0---���ܹرգ�Ĭ�ϣ���1-���ܿ�����
	D_U8	moniter_mode;//��ط�ʽ��1---���ݰ汾�ż�أ�ֻ������һ���汾�ŵ���Ϣ�� 2---��ʱ��أ��ȽϽ�Ŀ���֣������һ���͸��¡�    
	D_U32	time_out;
    D_HTimer time_hand;
} D_SDTConfigMoniter;
/** @brief pat����Ʋ��� */ 
typedef struct {
	D_Bool	enable;//ʹ�ܣ�  0---���ܹرգ�Ĭ�ϣ���1-���ܿ�����
	D_U8	moniter_mode;//��ط�ʽ��1---���ݰ汾�ż�أ�ֻ������һ���汾�ŵ���Ϣ�� 2---��ʱ��أ��ȽϽ�Ŀ���֣������һ���͸��¡�    
	D_U32	time_out;
    D_HTimer time_hand;
} D_PATConfigMoniter;
/** @brief cat����Ʋ��� */ 
typedef struct {
	D_Bool	enable;//ʹ�ܣ�  0---���ܹرգ�Ĭ�ϣ���1-���ܿ�����
	D_U8	moniter_mode;//��ط�ʽ��1---���ݰ汾�ż�أ�ֻ������һ���汾�ŵ���Ϣ�� 2---��ʱ��أ��ȽϽ�Ŀ���֣������һ���͸��¡�    
	D_U32	time_out;
    D_HTimer time_hand;
} D_CATConfigMoniter;
/** @brief tdt tot����Ʋ��� */ 
typedef struct {
	D_Bool	enable;//ʹ�ܣ�  0---���ܹرգ�Ĭ�ϣ���1-���ܿ�����
	D_U8	moniter_mode;//��ط�ʽ��1---���ݰ汾�ż�أ�ֻ������һ���汾�ŵ���Ϣ�� 2---��ʱ��أ��ȽϽ�Ŀ���֣������һ���͸��¡�    
	D_U32	time_out;
    D_HTimer time_hand;
} D_TDTConfigMoniter;

/** @brief ���ؾ��*/ 
typedef D_Handle D_MonitorHandle;

/** @brief �Զ�����ؽ�������*/
typedef D_Result (*D_MonitorParse) (TVData *tv, D_U8 *buf, D_Size size)D_FUNCPOSTFIT;

/** @brief �Զ������ע���������*/
#define MAX_REG_MONITOR 4

/**@brief ��ע�����
*@param  app Ӧ�þ��
*@return D_OK �ɹ� D_ERR ʧ��
*/
D_Result d_monitor_open(D_HApp app)D_FUNCPOSTFIT;

/**@brief �ر�ע�����
*@return D_OK �ɹ� D_ERR ʧ��
*/
D_Result d_monitor_close(void)D_FUNCPOSTFIT;

/**@brief �������ؾ��
*@return D_Moniter_Handle ���ؾ��
*/
D_MonitorHandle d_monitor_create(D_MonitorParse parse,D_TimerAttr ta,D_U32 time_out)D_FUNCPOSTFIT;
D_MonitorHandle d_monitor_create_ex(D_MonitorParse parse,D_TimerAttr ta,D_U32 time_out,  D_Bool bfm)D_FUNCPOSTFIT;

/**@brief ���ñ��ع��˲���
*@param handle ���ؾ��
*@return D_OK �ɹ� D_ERR ʧ��
*/
D_Result d_monitor_set_param(D_MonitorHandle handle,D_DemuxFilter filter)D_FUNCPOSTFIT;

/**@brief �������ؾ��
*@param handle ���ؾ��
*@return D_OK �ɹ� D_ERR ʧ��
*/
D_Result d_monitor_start(D_MonitorHandle handle)D_FUNCPOSTFIT;

/**@brief �������ؾ��
*@param msg ��Ϣ
*@param tv_data ��������
*@param size ���ݴ�С
*@return D_OK �ɹ� D_ERR ʧ��
*/
D_Result 
d_moniter_parse (D_Msg *msg,TVData* tv_data, D_Size size) D_FUNCPOSTFIT;
/**@brief ֹͣ���ؾ��
*@param handle ���ؾ��
*@return D_OK �ɹ� D_ERR ʧ��
*/
D_Result d_monitor_stop(D_MonitorHandle handle)D_FUNCPOSTFIT;

/**@brief �ͷű��ؾ��
*@param handle ���ؾ��
*@return D_OK �ɹ� D_ERR ʧ��
*/
D_Result d_monitor_destory(D_MonitorHandle handle)D_FUNCPOSTFIT;

/** @brief ����TS SI����
*@param[in] tv ��Ŀ����
*@return D_OK �����ɹ� D_ERR ����ʧ��
*/
 D_Result d_tv_start_ts_si(TVData *tv)D_FUNCPOSTFIT; 

/** @brief ֹͣTS SI����
*@param[in] tv ��Ŀ����
*@return D_OK ִ�гɹ�
*/
 D_Result d_tv_stop_ts_si (TVData *tv)D_FUNCPOSTFIT ;
/** @brief ��ʼPMT SI����
*@param[in] tv ��Ŀ����
*@return D_OK �����ɹ� D_ERR ����ʧ��
*/
 D_Result d_tv_start_srv_si(TVData *tv)D_FUNCPOSTFIT;
/** @brief ֹͣPMT SI����
*@param[in] tv ��Ŀ����
*@return D_OK ִ�гɹ�
*/
 D_Result d_tv_stop_srv_si (TVData *tv)D_FUNCPOSTFIT;
 
/** @brief ����ʱ���ã����nit�������ſ�����ӦӦ���㲥  qiny@2011-10-14
*@return D_OK ִ�гɹ� D_ERR ִ��ʧ��
*/
D_Result d_tv_resume_scan_nit(void)D_FUNCPOSTFIT;
/*** @brief����ʱ�źŲ���ʱ���ã�ֹͣ���nit�� qiny@2011-10-14
*@return D_OK ִ�гɹ�
*/
D_Result d_tv_stop_scan_nit(void)D_FUNCPOSTFIT;
 
/** @brief ����PAT
*@param[in] tv data_tv ����
*@param[in] buf ����������
*@param[in] size ���ݴ�С
*@return D_OK �����ɹ� D_ERR ����ʧ��
*/
 D_Result d_tv_parse_pat (TVData *tv, D_U8 *buf, D_Size size)D_FUNCPOSTFIT ;
/** @brief ����PMT
*@param[in] tv data_tv ����
*@param[in] buf ����������
*@param[in] size ���ݴ�С
*@return D_OK �����ɹ� D_ERR ����ʧ��
*/
 D_Result d_tv_parse_pmt (TVData *tv, D_U8 *buf, D_Size size)D_FUNCPOSTFIT ;
/** @brief ����CAT
*@param[in] tv data_tv ����
*@param[in] buf ����������
*@param[in] size ���ݴ�С
*@return D_OK �����ɹ� D_ERR ����ʧ��
*/
 D_Result d_tv_parse_cat (TVData *tv, D_U8 *buf, D_Size size)D_FUNCPOSTFIT;
/** @brief ����TDT
*@param[in] tv data_tv ����
*@param[in] buf ����������
*@param[in] size ���ݴ�С
*@return D_OK �����ɹ� D_ERR ����ʧ��
*/
 D_Result d_tv_parse_tdt (TVData *tv, D_U8 *buf, D_Size size)D_FUNCPOSTFIT;
/** @brief ����NIT
*@param[in] tv data_tv ����
*@param[in] buf ����������
*@param[in] size ���ݴ�С
*@return D_OK �����ɹ� D_ERR ����ʧ��
*/
 D_Result d_tv_parse_nit (TVData *tv, D_U8 *buf, D_Size size)D_FUNCPOSTFIT;

/** @brief ����SDT
*@param[in] tv data_tv ����
*@param[in] buf ����������
*@param[in] size ���ݴ�С
*@return D_OK �����ɹ� D_ERR ����ʧ��
*/
 D_Result d_tv_parse_sdt (TVData *tv, D_U8 *buf, D_Size size)D_FUNCPOSTFIT;

/**@brief �����Ƿ���Ҫ����
*@param[in] mask ��Ӧ��
*@param[in] fdata ���ò���
*@return D_OK ���óɹ�
*/
D_Result d_set_need_version (D_TVScanMode mask,D_Ptr fdata)D_FUNCPOSTFIT;
/** @brief ��ʱ��������*/
D_Result d_moniter_timer(D_Msg *msg,TVData* tv_data)D_FUNCPOSTFIT;

/**@brief ����Ƿ���Ҫ�汾���Ʊ�־
*@param[in] mask ��Ӧ��
*@return 1 ��Ҫ���� 0 ����Ҫ����
*/
D_U8 d_get_need_version (D_TVScanMode mask) D_FUNCPOSTFIT;
/** @brief ����Ƿ���Ҫnit����
*@param[in] ps data_tv��ps����
*@return D_TRUE ��Ҫ D_FALSE ����Ҫ
*/
D_Bool d_moniter_nit_check(D_ProgScan* ps)D_FUNCPOSTFIT;
#ifdef  __cplusplus
}
#endif

#endif
/**@}*/
