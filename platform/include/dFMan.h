/** @file
* @brief ǰ�˹���ģ��
*
* ǰ�˹�������
* @author ����
* @date 2005-6-16 ����: �����ļ�
*/

#ifndef _D_FMAN_H_
#define _D_FMAN_H_

#include "dApp.h"
#include "dDBase.h"

#ifdef  __cplusplus
extern "C"
{
#endif


/** @brief ǰ�˹��������*/
typedef D_HApp	D_HFMan;

/** @brief ǰ�˹�������������*/
typedef struct
{
    D_FEndType ftype;
    D_FEndParam param;
    D_FEndLnbInfo lnbsetinfo;
}D_FManParam;


D_Result	d_fman_open (void) D_FUNCPOSTFIT;
D_Result	d_fman_close (void) D_FUNCPOSTFIT;
D_HFMan		d_fman_create (D_S8 priority, D_FEndAttr *attr) D_FUNCPOSTFIT;
D_Result 	d_fman_set_param (D_HFMan fm, D_FEndParam *param, D_Bool track, D_FEndType fendtype, D_DBSateInfo *sateinfo, D_DBAnteInfo *anteinfo) D_FUNCPOSTFIT;
D_Result 	d_fman_get_locked_req (D_HFMan fm, D_HQueue hq) D_FUNCPOSTFIT;
D_Result 	d_fman_get_status_req (D_HFMan fm, D_HQueue hq) D_FUNCPOSTFIT;
D_Result	d_fman_set_locked_detector (D_HFMan fm, D_HQueue hq) D_FUNCPOSTFIT;
D_Result	d_fman_get_dev_attr (D_HFMan fm, D_FEndAttr *attr) D_FUNCPOSTFIT;
D_Result	d_fman_get_param (D_HFMan fm, D_FEndParam *param, D_FEndType  *fendtype) D_FUNCPOSTFIT;
D_Result 	d_fman_blind_set_param (D_HFMan fm, D_FEndBlindCmd cmd, D_FEndType fendtype, D_FBlindParam *param, D_HQueue hq) D_FUNCPOSTFIT;
D_Result	d_fman_destroy (D_HFMan fm) D_FUNCPOSTFIT;
D_HFMan d_fman_get_handle_by_type(D_FEndType type, D_Int order) D_FUNCPOSTFIT;
D_Result d_fman_select_lnb_osc_dvbs(D_FEndLnbInfo *antinfo, D_FEndParam *param, D_FEndLnbInfo *lsi)D_FUNCPOSTFIT;

/** @brief ͨ��ǰ�˹������趨diseqc����
* @param fm ǰ���豸���
* @param diseqc diseqc����
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_fman_set_diseqc_cmd(D_HFMan fm, D_FEndDiSEqC *diseqc) D_FUNCPOSTFIT;

/** @brief ͨ��ǰ�˹������趨tuner���粻��
* @param fm ǰ���豸���
* @param enable �������
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_fman_set_lnb_power_enable(D_HFMan fm, D_Bool enable) D_FUNCPOSTFIT;

/** @brief ��ǰ����״̬��ѯ����
* @param fm ǰ�˹����豸���
* @param hq	��Ϣ���о��,ǰ�˹�����ͨ�����������״̬��Ϣ
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_fman_clear_lock_req(D_HFMan fm, D_HQueue hq) D_FUNCPOSTFIT;

/** @brief ��ǰ���豸״̬��ѯ����
* @param fm ǰ�˹����豸���
* @param hq	��Ϣ���о��,ǰ�˹�����ͨ����������豸״̬��Ϣ
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_fman_clear_status_req(D_HFMan fm, D_HQueue hq) D_FUNCPOSTFIT;
D_Result d_fman_set_stdby (D_HFMan fm) D_FUNCPOSTFIT;

/** @brief ͨ��ǰ�˹������趨�Ӵ����ָ�
* @param fm ǰ���豸���
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result
d_fman_set_wakeup(D_HFMan fm) D_FUNCPOSTFIT;
/** @brief ����fman ����ʱ�����Ƶģʽ��
* @param fm ǰ�˹����豸���
* @param monitor_mode	�Ƿ�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_fman_set_monitor_mode(D_HFMan fm, D_Bool monitor_mode) D_FUNCPOSTFIT;

/** @brief ����fman ���ٴ�����Ϣģʽ��(dvbs�����ź�ʱʹ��D_TRUE�����˳��˵�ʱ�ָ�D_FALSE)
dvbs��������ʱ��Ҫʵʱ��ʾ�ź�ǿ�����������Լ���ʱ����diseqc���
��decoder��Ƶ��ʱ��ѭ������Ե���patchʹfman��������Ķ��������Ϣ���¼���
* @param fm ǰ�˹����豸���
* @param fast	����ģʽ
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_fman_set_fast_mode(D_HFMan fm, D_Bool fast) D_FUNCPOSTFIT;

/** @brief ����fman ������ģʽ����ʱ��Ƶʱ�����趨diseqc,��Ӧ�õ��������
* @param fm ǰ�˹����豸���
* @param motor_mode	�Ƿ�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_fman_set_motor_mode(D_HFMan fm, D_Bool motor_mode) D_FUNCPOSTFIT;

/** @brief ��ס22k,��ʱ��Ƶʱ�����趨22k,��Ӧ�õ��������
* @param fm ǰ�˹����豸���
* @param lock	�Ƿ���ס
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_fman_lock_22k_ctrl(D_HFMan fm, D_Bool lock) D_FUNCPOSTFIT;

/** @brief ����22K���ء�(ֱ�ӵ���fend�ӿ�)
* @param fm ǰ�˹����豸���
* @param on	�Ƿ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_fman_set_22k_direct(D_HFMan fm, D_Bool on) D_FUNCPOSTFIT;

/** @brief ͨ��ǰ�˹������趨ǰ���豸äɨ����(ֱ�ӵ���fend�ӿڣ������)
* @param fm ǰ���豸���
* @param scantype äɨ����
* @param cmd äɨ����
* @param fendtype ǰ������
* @param param ǰ���豸äɨ����
* @param hq ��Ϣ����
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result
d_fman_blind_set_param_direct (D_HFMan fm, D_FEndBlindCmd cmd, D_FEndParam *re_param,D_FBlindParam *blindparam) D_FUNCPOSTFIT;

/** @brief ͨ��ǰ�˹������趨ǰ���豸����(ֱ�ӵ���fend�ӿ�)
* @param fm ǰ���豸���
* @param param ǰ���豸����
* @param lnb_freq ����Ƶ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_fman_set_param_direct(D_HFMan fm, D_FEndParam *param, D_FEndFreq lnb_freq) D_FUNCPOSTFIT;

/** @brief ȡ������״̬��(ֱ�ӵ���fend�ӿ�)
* @param fm ǰ�˹����豸���
* @return ��������D_TRUE, ����������D_FALSE
*/
D_Bool d_fman_get_lock_direct(D_HFMan fm) D_FUNCPOSTFIT;

/** @brief ȡ��ǰ���豸״̬��(ֱ�ӵ���fend�ӿ�)
* @param fm ǰ�˹����豸���
* @param status	״̬
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_fman_get_status_direct(D_HFMan fm, D_FEndStatus *status) D_FUNCPOSTFIT;

/** @brief ȡ��ǰ���豸Ƶ�׵���ϸ��Ϣ״̬��(ֱ�ӵ���fend�ӿڣ������)
* @param fm ǰ�˹����豸���
* @param status	״̬
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_fman_get_advance_status_direct(D_HFMan fm, D_FEndadvanceStatus *status) D_FUNCPOSTFIT;

/** @brief�趨fman�����ָ�
* @param fm     ǰ�˹����豸���
* @param suspend   �������
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_fman_set_suspend(D_HFMan fm, D_Bool suspend) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
