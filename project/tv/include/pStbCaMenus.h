/** @file
* @brief CA��ز˵��ӿ�
* @author ����
* @date 2013-7-05 ����: �����ļ�
*/

#ifndef _D_CA_MENUS_H_
#define _D_CA_MENUS_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dDebug.h"  
#include "dFP.h" 
#include "dGUI.h"
#include "dFrame.h"
#include "dControl.h"
#include "pPopMsg.h"
#include "pMenu.h"
#include "pMem.h"
#include "pStb.h"
#include "dCA.h"
#include "dSerial.h"
#include "pBurnSerialNumber.h"
#include "pcaGuiResource.h"


/**< @brief CA�Ӳ˵�����*/
typedef enum {
	D_CA_SUBMENU_SC_IN,		
	D_CA_SUBMENU_MAIL_IN,	
	D_CA_SUBMENU_AUTHORIZATION_IN,
	D_CA_SUBMENU_SCMOTHER_IN,
	D_CA_SUBMENU_USER
} D_CAEnterSubmenuType;


/** @brief CA�˵���ʼ��(���ݵ�ǰca����ѡ���Ӧ�Ĳ˵�)
* @param ��
* @return �ɹ�����D_OK
*/
D_Result
p_stb_ca_menu_init (void) D_FUNCPOSTFIT;

/** @brief ��GUI�д���ca�¼�
* @param type �¼�����
* @param param �¼�����
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result
p_ca_gui_solve_evt (D_CAEventType type, D_Ptr param) D_FUNCPOSTFIT;


/*********************�����ӿ�***************************/
/** @breif ��ʾ����osd ��ʾ����*/  
D_Result 
p_cdca_superosd_window_show(D_Ptr param)  D_FUNCPOSTFIT;

/**@breif �ڲس���osd ��ʾ����*/
D_Result         
p_cdca_superosd_window_hide (void) D_FUNCPOSTFIT;

/** @breif ��ʾca ����ָ�ƴ���*/      
D_Result         
p_Ca_finger_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif ����ca ����ָ�ƴ���*/      
D_Result         
p_Ca_finger_window_hide (void) D_FUNCPOSTFIT;

/** @breif ��ʾ�����򴰿�*/      
D_Result
p_ca_dialog_window_show(D_CAEventType type, D_Ptr param)D_FUNCPOSTFIT;
/**********************END***************************/


/***********���������Ӳ�****************/
/** @breif �ʼ��������ݴ���*/      
D_Result         
p_mail_detail_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾ�ʼ�������*/      
D_Result         
p_mail_manage_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾ��Ӫ����Ϣ����*/      
D_Result         
p_operator_info_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾǮ����Ϣ����*/      
D_Result         
p_purse_info_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾ���ܿ���Ϣ����*/      
D_Result         
p_smartcard_info_sub_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾ���ܿ���Ϣ����*/      
D_Result         
p_smartcard_info_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾ����Ȩ����*/        
D_Result         
p_antiauthorize_info_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾ��Ȩ��Ϣ����*/      
D_Result         
p_authorization_info_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾ��ĸ����Ϣ����*/      
D_Result         
p_child_mother_card_window_show(void) D_FUNCPOSTFIT;

/** @brief ��ʾ����ca�����������ô���*/
D_Result
p_level_set_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾ�������*/
D_Result p_card_pair_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾ����ʱ��*/
D_Result p_work_time_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾpin�����ô���*/  
D_Result p_modify_pin_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾca �߼�Ԥ������*/      
D_Result         
p_ca_senior_preview_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif ����ca �߼�Ԥ������*/      
D_Result         
p_ca_senior_preview_window_hide (void) D_FUNCPOSTFIT;

/** @breif ��ʾca����������*/
D_Result         
p_ca_progress_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif ����ca����������*/
D_Result         
p_ca_progress_window_hide (void) D_FUNCPOSTFIT;

/** @breif ��ʾippv����*/      
D_Result         
p_ippv_info_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾca��Ϣ(�ʼ�ͼ�ꡢָ�ơ�����Ȩ��ppvͼ�ꡢԤ��ͼ��)����*/      
D_Result         
p_Ca_osd_window_show (D_CAEventType type, D_Ptr param) D_FUNCPOSTFIT;

/** @breif ����ca��Ϣ(�ʼ�ͼ�ꡢָ�ơ�����Ȩ, ������)����*/      
D_Result         
p_Ca_osd_window_hide (void) D_FUNCPOSTFIT;

/** @breif ����ca��Ϣ(�ʼ�ͼ�ꡢָ�ơ�����Ȩ, ������)���ڵ�����*/      
D_Result         
p_Ca_osd_window_bak (void) D_FUNCPOSTFIT;

/** @breif ��ʾca ipptv ���򴰿�*/      
D_Result         
p_ca_ipptv_buy_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif ����ca ipptv ���򴰿�*/      
D_Result         
p_ca_ipptv_buy_window_hide (void) D_FUNCPOSTFIT;

/***************************************/


/***********������ͨ�Ƽ�****************/
/** @breif ��ʾ��ͨ��Ȩ����*/  
D_Result         
p_CTICa_authorization_info_window_show(void) D_FUNCPOSTFIT;
/** @breif ��ͨIPPV��Ϣ*/ 
D_Result 
p_CTICa_auth_ippv_info_window_show(D_U8 flag) D_FUNCPOSTFIT;

/** @breif ��ͨ�ʼ��������ݴ���*/   
D_Result         
p_CTICa_mail_detail_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ͨ��ʾ�ʼ�������*/      
D_Result         
p_CTICa_mail_manage_window_show(void) D_FUNCPOSTFIT;

/** @breif ׼��������*/
D_Result 
p_CTICa_allow_ban_setting_window_show(D_U8 *pin) D_FUNCPOSTFIT;

/** @breif ��ͨ�����޸�*/     
D_Result
p_CTICa_pin_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾ��ͨ���ܿ���Ϣ����*/      
D_Result         
p_CTICa_smartcard_info_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾpin�����ô���*/  
D_Result 
p_CTICa_modify_pin_window_show () D_FUNCPOSTFIT;

/** @breif �û�ѡ����ת*/   
D_Result   
p_CTICa_skip_select_window_show() D_FUNCPOSTFIT;

/** @brief ��ʾ��ͨca�����������ô���*/
D_Result
p_CTICa_level_set_window_show(void) D_FUNCPOSTFIT;
/** @brief ����ippv����*/
D_Result
p_CTICa_ipptv_buy_window_hide(void) D_FUNCPOSTFIT;

D_Result
p_CTICa_skip_select_window_hide(void) D_FUNCPOSTFIT;

D_Result
p_CTICa_authorization_info_window_reshow(void) D_FUNCPOSTFIT;

D_Result
p_CTICa_smartcard_info_window_reshow(void) D_FUNCPOSTFIT;

D_Result 
p_CTICa_auth_detail_info_window_return(void) D_FUNCPOSTFIT;

/***************************************/

/***********��о****************/
/** @breif ��ʾ���ܿ���Ϣ*/      
D_Result         
p_DSCa_smartcard_info_window_show(void) D_FUNCPOSTFIT;
/** @breif ��ʾ��Ȩ��Ϣ*/ 
D_Result 
p_DSCa_smartcard_info_window_cos_show(void) D_FUNCPOSTFIT;

D_Result 
p_DSCa_authorization_info_window_show(void) D_FUNCPOSTFIT;
/** @breif ��������*/ 
D_Result 
p_DSCa_level_set_window_show(void) D_FUNCPOSTFIT;
/** @breif �ʼ�����*/ 
D_Result 
p_DSCa_mail_detail_window_show(D_U8 num, D_U8 *sender) D_FUNCPOSTFIT;
/** @breif �ʼ��˵�*/ 
D_Result 
p_DSCa_mail_manage_window_show(void) D_FUNCPOSTFIT;
/** @breif �����޸�*/ 
D_Result 
p_DSCa_modify_pin_window_show(void) D_FUNCPOSTFIT;
/** @breif ��ʾ��Ӫ����Ϣ*/ 
D_Result 
p_DSCa_operator_info_window_show(void) D_FUNCPOSTFIT;
/** @breif ����ʱ������*/ 
D_Result 
p_DSCa_work_time_window_show(void) D_FUNCPOSTFIT;
/** @breif Ǯ����Ϣ*/ 
D_Result 
p_DSCa_purse_info_window_show(void) D_FUNCPOSTFIT;
/** @breif ��ʾ����OSD*/
D_Result 
p_DSCa_superosd_window_show (D_Ptr param) D_FUNCPOSTFIT;
/** @breif ���س���OSD*/
D_Result 
p_DSCa_superosd_window_hide (void) D_FUNCPOSTFIT;

/** @breif ��ʾ��ECMָ�ƴ���*/   
D_Result         
p_DSCa_finger_window_show (D_Ptr param) D_FUNCPOSTFIT;

D_Result  
p_DSCa_ipptv_buy_window_show (D_Ptr param) D_FUNCPOSTFIT;

D_Result  
p_DSCa_ipptv_buy_window_hide(void) D_FUNCPOSTFIT;

/** @breif ����ECMָ�ƴ���*/      
D_Result         
p_DSCa_finger_window_hide (void) D_FUNCPOSTFIT;

D_Result         
p_DSCa_progress_window_show (D_Ptr param) D_FUNCPOSTFIT;

D_Result         
p_DSCa_progress_window_hide(void) D_FUNCPOSTFIT;

/***************************************/

/***********�Ĵ��ɶ���˹����****************/
/** @breif ��ʾ��˹������Ȩ����*/  
D_Result         
p_GOSCa_authorization_info_window_show(void) D_FUNCPOSTFIT;

D_Result  
p_GOSCa_authorization_info_window_reshow(void) D_FUNCPOSTFIT;

/** @breif ��˹�����ʼ��������ݴ���*/   
D_Result         
p_GOSCa_mail_detail_window_show(D_U8 num) D_FUNCPOSTFIT;

/** @breif ��˹������ʾ�ʼ�������*/      
D_Result         
p_GOSCa_mail_manage_window_show(void) D_FUNCPOSTFIT;

/** @breif ��˹������ʾ��������Ϣ*/ 
D_Result
p_GOSCa_bind_info_window_show () D_FUNCPOSTFIT;

/** @breif ��˹���������޸�*/     
D_Result
p_GOSCa_modify_pin_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾ��˹�������ܿ���Ϣ����*/      
D_Result         
p_GOSCa_smartcard_info_window_show(void) D_FUNCPOSTFIT;


/** @brief ��ʾ��˹����ca�����������ô���*/
D_Result
p_GOSCa_level_set_window_show(void) D_FUNCPOSTFIT;

D_Result
p_GOSCa_smartcard_info_window_reshow(void) D_FUNCPOSTFIT;

/** @brief ��ʾ��˹����ca��Ӫ����Ϣ����*/
D_Result
p_GOSCa_operator_info_window_show(void)D_FUNCPOSTFIT;
D_Result
p_GOSCa_operator_info_window_reshow(void)D_FUNCPOSTFIT;


/***************************************/

/***********�Ϻ�����Ѹ��****************/
/** @breif ��ʾ����*/      
D_Result         
p_mgca_ipptv_window_show () D_FUNCPOSTFIT;

/** @breif ����ca ipptv ���򴰿�*/      
D_Result         
p_mgca_ipptv_window_hide () D_FUNCPOSTFIT;

/** @breif ��ʾmgca ipptv ���򴰿�*/      
D_Result         
p_mgca_ipptv_buy_window_show () D_FUNCPOSTFIT;

/** @breif ����mgca ipptv ���򴰿�*/      
D_Result         
p_mgca_ipptv_buy_window_hide (void) D_FUNCPOSTFIT;

/** @breif ��ʾmgca ���ܿ���Ϣ����*/  
D_Result
p_mgca_smartcard_info_window_show(void) D_FUNCPOSTFIT;

D_Result
/** @breif ��ʾmgca���ܿ���Ϣ�ڶ�ҳ����*/      
p_mgca_smartcard_info_sub_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾmgca��ĸ������*/      
D_Result         
p_mgca_child_mother_card_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾmgca�ʼ�����*/      
D_Result         
p_mgca_mail_manage_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾmgca�ʼ����ݴ���*/      
D_Result         
p_mgca_mail_detail_window_show (void) D_FUNCPOSTFIT;

/***************************************/


/***********����������Ѷ****************/
/** @breif ��ʾdvtca ���ܿ���Ϣ����*/  
D_Result
p_dvtca_smartcard_info_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾdvtca ���ܿ�����Ϣ����*/  
D_Result
p_dvtca_smartcard_info_sub_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾ����*/      
D_Result         
p_DVTCa_operator_info_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾ��Ӫ����Ȩ��Ϣ����*/      
D_Result         
p_dvtca_authorization_info_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾǮ����Ϣ����*/      
D_Result         
p_dvtca_purse_info_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾ����*/        
D_Result         
p_dvtca_ippv_info_window_show () D_FUNCPOSTFIT;

/** @brief 	��ʾca�����������ô���
* @param 	��
* @return	������ȷִ�з���D_OK,ʧ�ܷ���D_ERR
*/
D_Result
p_dvtca_level_set_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾʱ�����ô���*/
D_Result 
p_dvtca_work_time_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾ�����޸Ĵ���*/  
D_Result 
p_dvtca_modify_pin_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾ��ĸ������*/      
D_Result         
p_dvtca_child_mother_card_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾIPPV�����ȡ������*/      
D_Result p_dvtca_ippv_buy_cancel_window_show()D_FUNCPOSTFIT;

/** @breif ��ʾdvtca�ʼ�����*/      
D_Result         
p_dvtca_mail_manage_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾdvtca�ʼ����ݴ���*/ 
D_Result         
p_dvtca_mail_detail_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾdvtca���ز˵�*/ 
D_Result  
p_dvtca_hidemenu_set_window_show() D_FUNCPOSTFIT;

/** @breif ��ʾȫ�����洰��*/
D_Result         
p_DVTCa_tip_announcement_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif ����ȫ�����洰��*/      
D_Result         
p_DVTCa_tip_announcement_window_hide (void) D_FUNCPOSTFIT;

/** @breif ��ʾdvtca ����ָ�ƴ���*/      
D_Result         
p_DVTCa_finger_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif ����dvtca ����ָ�ƴ���*/      
D_Result         
p_DVTCa_finger_window_hide (void) D_FUNCPOSTFIT;

/***********��****************/
/** @breif ��ʾwfca ���ܿ���Ϣ����*/  
D_Result         
p_wfca_smartcard_info_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾwfca ���ܿ���Ϣ�ڶ�ҳ����*/  
D_Result         
p_wfca_smartcard_info_sub_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾwfca�ʼ���Ϣ����*/  
D_Result         
p_wfca_mail_manage_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾwfca�ʼ�������Ϣ����*/  
D_Result         
p_wfca_mail_detail_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾwfca��Ȩ��Ϣ����*/  
D_Result         
p_wfca_authorization_info_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾwfca ipptv ����*/  
D_Result         
p_wfca_ipptv_buy_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif ����wfca ipptv ����*/  
D_Result         
p_wfca_ipptv_buy_window_hide () D_FUNCPOSTFIT;

/** @breif ��ʾCAS ������Ϣ����*/      
D_Result         
p_wfca_error_info_window_show () D_FUNCPOSTFIT;

/** @breif �������*/
D_Result
p_wfca_level_set_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾ��ĸ����������*/      
D_Result         
p_wfca_tip_parentalctrl_window_show (void) D_FUNCPOSTFIT;

/** @breif �ڲظ�ĸ����������*/      
D_Result         
p_wfca_tip_parentalctrl_window_hide (void) D_FUNCPOSTFIT;

/** @breif ��ʾ�����޸Ĵ���*/  
D_Result 
p_wfca_modify_pin_window_show () D_FUNCPOSTFIT;
/***************************************/

/***********ȫ��****************/
/** @breif ��ʾqzca ���ܿ���Ϣ����*/      
D_Result   
p_QZCa_smartcard_info_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾqzca�ʼ�����*/     
D_Result         
p_QZCa_mail_manage_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾqzca�ʼ�������Ϣ����*/      
D_Result         
p_QZCa_mail_detail_window_show () D_FUNCPOSTFIT;
/***************************************/

/***********����������Ѷ****************/
/** @breif ������Ȩ��Ϣ����*/  
D_Result    
p_ABVCa_freeauthorization_info_window_show(void) D_FUNCPOSTFIT;

/** @breif ������Ȩ��Ϣ����*/  
D_Result    
p_ABVCa_ppcauthorization_info_window_show(void) D_FUNCPOSTFIT;

/** @breif ������Ȩ��Ϣ����*/  
D_Result    
p_ABVCa_ppvauthorization_info_window_show(void) D_FUNCPOSTFIT;

/** @breif ���ѻ��ֵ��ʷ��Ϣ*/  
D_Result         
p_ABVCa_consume_history_info_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾ�ʼ�������*/      
D_Result         
p_ABVCa_mail_manage_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾ���ܿ���Ϣ����*/      
D_Result         
p_ABVCa_smartcard_info_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾ��Ӫ����Ϣ����*/      
D_Result       
p_ABVCa_operator_info_window_show(void) D_FUNCPOSTFIT;

/** @brief ��ʾ����ca�����������ô���*/
D_Result
p_ABVCa_level_set_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾpin�����ô���*/  
D_Result
p_ABVCa_modify_pin_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾ����ʱ��*/
D_Result
p_ABVCa_work_time_window_show(void) D_FUNCPOSTFIT;

/** @breif �ʼ��������ݴ���*/      
D_Result         
p_ABVCa_mail_detail_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾ���ڲس���osd ��ʾ����*/  
D_Result 
p_ABVCa_superosd_window_show(D_Ptr param)  D_FUNCPOSTFIT;

/** @breif ��ʾca ipptv ���򴰿�*/      
D_Result         
p_ABVCa_ippv_buy_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif ����ca ipptv ���򴰿�*/      
D_Result         
p_ABVCa_ippv_buy_window_hide (void) D_FUNCPOSTFIT;

/** @brief 	��ʾ���˼���Ŀ����*/
D_Result
p_ABVCa_maurity_prog_window_show(void) D_FUNCPOSTFIT;

/** @breif ���س��˼���Ŀ����*/      
D_Result         
p_ABVCa_maurity_prog_window_hide (void) D_FUNCPOSTFIT;

/** @breif ��ʾECMָ�ƴ���*/      
D_Result         
p_ABVCa_finger_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif ����ECMָ�ƴ���*/      
D_Result         
p_ABVCa_finger_window_hide (void) D_FUNCPOSTFIT;

/** @breif ��ʾ����osd����*/      
D_Result         
p_ABVCa_superosd_window_hide (void) D_FUNCPOSTFIT;

/** @breif ��ʾ�û�ָ�ƴ���*/      
D_Result         
p_ABVCa_superfinger_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif �ڲ��û�ָ�ƴ���*/      
D_Result         
p_ABVCa_superfinger_window_hide (void) D_FUNCPOSTFIT;

/** @breif ��ʾEMMָ�ƴ���*/      
D_Result         
p_ABVCa_emmfinger_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif �ڲ�EMMָ�ƴ���*/      
D_Result         
p_ABVCa_emmfinger_window_hide (void) D_FUNCPOSTFIT;
/** @breif �ڲس���osd����*/      
D_Result         
p_ABVCa_convertfinger_window_show (D_Ptr param) D_FUNCPOSTFIT;
/** @brief ��д���к�*/
D_Result abvca_burn_serial_number(D_HSerial sl_hdl, OPERATE_TYPE type) D_FUNCPOSTFIT;

/** @ͨ�����ڷ�����Ϣ*/      
D_Result         
p_ABVCa_send_msg_from_ca_to_otherstb (D_Ptr param) D_FUNCPOSTFIT;
/***************************************/
/***********��������̫��****************/
/** @breif ��ʾunitendca udrm��Ϣ����*/  
D_Result
p_unitendca_udrm_info_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾunitendca PPC��Ȩ��Ϣ����*/  
D_Result
p_unitendca_ppc_info_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾnitendca�ʼ�����*/      
D_Result         
p_unitendca_mail_manage_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾunitendca�ʼ����ݴ���*/ 
D_Result         
p_unitendca_mail_detail_window_show () D_FUNCPOSTFIT;

/** @brief 	��ʾca�����������ô���*/ 
D_Result
p_unitendca_level_set_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾ�����޸Ĵ���*/  
D_Result 
p_unitendca_modify_pin_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾȫ����Ҫ�ʼ�����*/      
D_Result         
p_unitendca_tip_email_window_show(D_Ptr param) D_FUNCPOSTFIT;

/** @breif ����ȫ����Ҫ����(��ʱ����)*/      
D_Result         
p_unitendca_tip_email_window_hide(void) D_FUNCPOSTFIT;

/** @breif ��ʾ��ĸ����������*/      
D_Result         
p_UNITENDCa_tip_parentalctrl_window_show () D_FUNCPOSTFIT;

/** @breif �ڲظ�ĸ����������*/      
D_Result         
p_UNITENDCa_tip_parentalctrl_window_hide () D_FUNCPOSTFIT;
/***************************/

/***********�¹�****************/
/** @breif ��ʾxgca ���ܿ���Ϣ����*/  
D_Result         
p_xgca_smartcard_info_window_show (void) D_FUNCPOSTFIT;
/** @breif ��ʾ�޿�xgca ���ܿ���Ϣ����*/  
D_Result         
p_xgca_smartcard_info_window_show_cos (void) D_FUNCPOSTFIT;
/** @breif ��ʾxgca�ʼ���Ϣ����*/  
D_Result         
p_xgca_mail_manage_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾxgca�ʼ�������Ϣ����*/  
D_Result         
p_xgca_mail_detail_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾxgca��Ȩ��Ϣ����*/  
D_Result         
p_xgca_authorization_info_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾxgca��ĸ����Ϣ����*/  
D_Result         
p_xgca_card_pair_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾ����*/      
D_Result         
p_xgca_stb_card_pair_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾ����*/      
D_Result         
p_xgca_ippv_buy_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif ����ca ipptv ���򴰿�*/      
D_Result         
p_xgca_ippv_buy_window_hide (void) D_FUNCPOSTFIT;

/** @breif ��ʾ�Զ�ι������*/      
D_Result         
p_auto_xgca_card_pair_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif �����Զ�ι������*/      
D_Result         
p_auto_xgca_card_pair_window_hide () D_FUNCPOSTFIT;

/** @brief ��д���к�*/
D_Result 
xgca_burn_serial_number(D_HSerial sl_hdl, OPERATE_TYPE type) D_FUNCPOSTFIT;

/** @breif �߼����ܴ���*/  
D_Result         
p_xgca_senior_fun_window_show(void)D_FUNCPOSTFIT;

/** @breif ��ʾ����*/      
D_Result         
xgca_level_control_window_show(D_Ptr param) D_FUNCPOSTFIT;

/** @breif ���ش���*/      
D_Result         
xgca_level_control_window_hide() D_FUNCPOSTFIT;


/***********��������ͨ****************/
/** @breif ���ܿ���Ϣ�˵�*/      
D_Result         
p_DIVICa_smartcard_info_window_show (void) D_FUNCPOSTFIT;

/** @breif ��Ȩ��Ϣ�˵�*/ 
D_Result         
p_DIVICa_authorization_info_window_show (void) D_FUNCPOSTFIT;

/** @breif �����ʼ��˵�*/      
D_Result         
p_DIVICa_mail_manage_window_show (void) D_FUNCPOSTFIT;

/** @breif �����ʼ����ݲ˵�*/      
D_Result         
p_DIVICa_mail_detail_window_show (D_Char* frm , D_U8 TitleLen) D_FUNCPOSTFIT;

/** @breif �����޸Ĳ˵�*/  
D_Result 
p_DIVICa_modify_pin_window_show (void) D_FUNCPOSTFIT;

/** @breif �������ò˵�*/
D_Result
p_DIVICa_level_set_window_show (void) D_FUNCPOSTFIT;

/** @breif ����ʱ�β˵�*/
D_Result 
p_DIVICa_work_time_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ĸ���˵�*/      
D_Result         
p_DIVICa_cmcard_pair_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ĸ����ʾ��ش���*/      
D_Result         
p_DIVICa_cmcard_pair_monitor_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif �����ɷ�����*/  
D_Result         
p_DIVICa_tip_entitle_window_show (D_Ptr param) D_FUNCPOSTFIT;

/***********��������****************/
/** @breif ��ʾ���ܿ���Ϣ�˵�*/  
D_Result         
p_TRCa_smartcard_info_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾ��Ȩ��Ϣ�˵�*/   
D_Result         
p_TRCa_authorization_info_window_show(void) D_FUNCPOSTFIT;

/** @breif Ǯ����Ϣ�˵�*/      
D_Result         
p_TRCa_purse_info_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾipp�����˵�*/
D_Result 
p_TRCa_ipp_order_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾipp���Ѳ˵�*/     
D_Result
p_TRCa_ipp_consume_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾ�������ò˵�*/      
D_Result         
p_TRCa_level_set_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾpin�����ò˵�*/  
D_Result 
p_TRCa_modify_pin_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾ��ĸ����Բ˵�*/   
D_Result   
p_TRCa_cmcard_pair_window_show(void) D_FUNCPOSTFIT;

/** @brief ��ʾ�����ʼ��˵�*/
D_Result
p_TRCa_mail_manage_window_show(void) D_FUNCPOSTFIT;
    
/** @breif ��ʾ�ʼ����ݲ˵�*/      
D_Result         
p_TRCa_mail_detail_window_show (D_Char* frm , D_U8 TitleLen) D_FUNCPOSTFIT;
    
/** @breif ��ʾȫ�����洰��*/      
D_Result         
p_TRCa_tip_announcement_window_show(D_Ptr param) D_FUNCPOSTFIT;

/** @breif ����ȫ�����洰��(�ⲿ����̨����)*/      
D_Result         
p_TRCa_tip_announcement_window_hide(void) D_FUNCPOSTFIT;

/** @breif ��ʾca ipptv ���򴰿�*/      
D_Result         
p_TRCa_ipptv_buy_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif �ڲ�ca ipptv ���򴰿�(�ⲿ����̨����)*/      
D_Result         
p_TRCa_ipptv_buy_window_hide (void) D_FUNCPOSTFIT;

/** @breif ��ʾ��ĸ����������*/      
D_Result         
p_TRCa_tip_parentalctrl_window_show (void) D_FUNCPOSTFIT;

/** @breif �ڲظ�ĸ����������*/      
D_Result         
p_TRCa_tip_parentalctrl_window_hide (void) D_FUNCPOSTFIT;

/** @breif ��ʾָ����Ϣ����*/      
D_Result         
p_TRCa_finger_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif �ڲ�ָ����Ϣ����*/      
D_Result         
p_TRCa_finger_window_hide (void) D_FUNCPOSTFIT;
/***************************************/

/***********����ͬ����Ѷ****************/
/** @breif ��ʾ�û���Ϣ�˵�*/
D_Result         
p_THTFCa_user_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾ��Ӫ����Ϣ�˵�*/
D_Result         
p_THTFCa_operator_info_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾ��Ȩ��Ϣ�˵�*/
D_Result         
p_THTFCa_authorization_info_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾpin��״̬���ò˵�*/  
D_Result
p_THTFCa_pin_state_set_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾpin�����ò˵�*/  
D_Result 
p_THTFCa_modify_pin_window_show () D_FUNCPOSTFIT;

/** @breif �������ò˵�*/
D_Result
p_THTFCa_level_set_window_show () D_FUNCPOSTFIT;

/** @breif ����ʱ�β˵�*/
D_Result 
p_THTFCa_work_time_window_show () D_FUNCPOSTFIT;

/** @brief ��ʾ�����ʼ��˵�*/
D_Result         
p_THTFCa_mail_manage_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾ�ʼ����ݲ˵�*/ 
D_Result         
p_THTFCa_mail_detail_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾ�����Զ�֪ͨ�˵�*/ 
D_Result
p_THTFCa_overdue_inform_set_window_show () D_FUNCPOSTFIT;

/** @brief 	��ʾ���˼���Ŀ����*/
D_Result
p_THTFCa_maurity_prog_window_show(void) D_FUNCPOSTFIT;

/** @breif ���س��˼���Ŀ����*/      
D_Result         
p_THTFCa_maurity_prog_window_hide (void) D_FUNCPOSTFIT;

/***********�ɶ�����(��о)****************/

/** @breif ��ʾ���ܿ���Ϣ�˵�*/  
D_Result         
p_LXDTCa_smartcard_info_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾ��Ȩ��Ϣ�˵�*/   
D_Result         
p_LXDTCa_authorization_info_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾippv������Ϣ�˵�*/      
D_Result         
p_LXDTCa_ippv_order_info_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾippvǮ����Ϣ�˵�*/
D_Result 
p_LXDTCa_ippv_purse_info_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾ�������ò˵�*/      
D_Result         
p_LXDTCa_level_set_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾpin�����ò˵�*/  
D_Result 
p_LXDTCa_modify_pin_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾ������Ӧ�˵�*/  
D_Result 
p_LXDTCa_card_pair_window_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾ�����ʼ��˵�*/
D_Result
p_LXDTCa_mail_manage_window_show(void) D_FUNCPOSTFIT;
    
/** @breif ��ʾ�ʼ����ݲ˵�*/      
D_Result         
p_LXDTCa_mail_detail_window_show (D_Char* frm , D_U8 TitleLen) D_FUNCPOSTFIT;
    
/***************************************/
/***********�Ϻ����****************/

/** @breif ��ʾ���ܿ���Ϣ�˵�*/  
D_Result         
p_DVNCa_smartcard_info_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾ��Ȩ��Ϣ�˵�*/   
D_Result         
p_DVNCa_authorization_info_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾ��ֵ��¼�˵�*/      
D_Result         
p_DVNCa_charge_record_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾ�������ò˵�*/
D_Result 
p_DVNCa_level_set_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾ�����޸Ĳ˵�*/      
D_Result         
p_DVNCa_modify_pin_window_show(void) D_FUNCPOSTFIT;

/** @breif ��ʾ������Ӧ�˵�*/  
D_Result 
p_DVNCa_stb_card_pair_window_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾ�����ʼ��˵�*/
D_Result
p_DVNCa_mail_manage_window_show(void) D_FUNCPOSTFIT;
    
/** @breif ��ʾ�ʼ����ݲ˵�*/      
D_Result         
p_DVNCa_mail_detail_window_show (D_Char* frm , D_U8 TitleLen) D_FUNCPOSTFIT;

/** @breif ��ʾ����OSD��Ϣ*/      
D_Result
p_DVNCa_tip_osd_screen_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif �ڲع���OSD��Ϣ*/      
D_Result         
p_DVNCa_tip_osd_screen_window_hide (void) D_FUNCPOSTFIT;

/** @breif ��ʾ�Զ�������Ӧ��Ϣ*/ 
D_Result         
p_DVNCa_tip_stb_card_pair_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif �ڲ��Զ�������Ӧ��Ϣ*/      
D_Result         
p_DVNCa_tip_stb_card_pair_window_hide (void) D_FUNCPOSTFIT;

/** @breif ��ʾ�Զ���ֵ��Ϣ*/      
D_Result         
p_DVNCa_tip_auto_change_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif �ڲ��Զ���ֵ��Ϣ*/           
D_Result         
p_DVNCa_tip_auto_change_window_hide (void) D_FUNCPOSTFIT;

/** @breif ��ʾ�Զ�ι����Ϣ*/  
D_Result         
p_DVNCa_tip_auto_feed_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif �ڲ��Զ�ι����Ϣ*/      
D_Result         
p_DVNCa_tip_auto_feed_window_hide (void) D_FUNCPOSTFIT;

/** @breif IPP��Ϣ�˵�*/      
D_Result         
p_DVNCa_ippv_order_info_window_show (void) D_FUNCPOSTFIT;

/** @breif IPP������Ϣ*/      
D_Result         
p_DVNCa_ipptv_buy_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif ����ca ipptv ���򴰿�*/      
D_Result         
p_DVNCa_ipptv_buy_window_hide (void) D_FUNCPOSTFIT;
/***************************************/

/***********�ɶ�Ӣ��****************/
/** @breif ��ʾyjca ���ܿ���Ϣ����*/      
D_Result   
p_YJCa_smartcard_info_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾ��Ȩ����*/      
D_Result         
p_YJCa_authorization_info_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾyjca�ʼ�����*/     
D_Result         
p_YJCa_mail_manage_window_show () D_FUNCPOSTFIT;

/** @breif ��ʾyjca�ʼ�������Ϣ����*/      
D_Result         
p_YJCa_mail_detail_window_show () D_FUNCPOSTFIT;
/** @breif ��ʾ��ĸ����Ϣ����*/      
D_Result         
p_YJCa_child_mother_card_window_show () D_FUNCPOSTFIT;

/***************************************/
/******************�״�*********************/
/** @breif ��ʾscca ���ܿ���Ϣ����*/      
D_Result         
p_SCCa_smartcard_info_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾscca Ǯ����Ϣ����*/      
D_Result         
p_SCCa_purse_info_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾscca ��Ȩ��Ϣ����*/      
D_Result         
p_SCCa_authorization_info_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾscca ��Ӫ����Ϣ����*/		
D_Result         
p_SCCa_operator_info_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾscca �ʼ���Ϣ����*/		
D_Result         
p_SCCa_mail_manage_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾscca �ʼ�������Ϣ����*/		
D_Result         
p_SCCa_mail_detail_window_show (D_U8 num) D_FUNCPOSTFIT;

/** @breif ��ʾscca ����������Ϣ����*/		
D_Result 
p_SCCa_modify_pin_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾscca ����ʱ����Ϣ����*/		
D_Result 
p_SCCa_work_time_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾscca ����������Ϣ����*/		
D_Result
p_SCCa_level_set_window_show (void) D_FUNCPOSTFIT;

/***************************************/

/******************о��è*********************/
/** @breif ��ʾxsmca ���ܿ���Ϣ����*/      
D_Result         
p_XSMCa_smartcard_info_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾxsmca �ʼ���Ϣ����*/		
D_Result         
p_XSMCa_mail_manage_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾxsmca �ʼ�������Ϣ����*/		
D_Result         
p_XSMCa_mail_detail_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾxsmca ��ĸ��ι������*/		
D_Result         
p_XSMCa_child_mother_card_window_show () D_FUNCPOSTFIT;

/***************************************/


/***********��CA****************/
/** @breif ��CAѡ��˵�*/
D_Result
p_ca_hide_window_show () D_FUNCPOSTFIT;

/** @breif ��CA����ص�*/
D_Result
complie_cas_handler(D_U32* param)D_FUNCPOSTFIT;

/** @breif ������ʾca��ʾ��Ϣ����*/  
D_Result p_Ca_BuyMsg_reshow (void) D_FUNCPOSTFIT;

/** @breif ����ca��ʾ��Ϣ���������*/      
D_Result p_Ca_BuyMsg_bak (void) D_FUNCPOSTFIT;

/** @brief ����CA�Ӳ˵�
* @param submenu: D_CAEnterSubmenuType
* @return �ɹ�����D_OK
*/
D_Result
p_stb_ca_submenu_enter (D_CAEnterSubmenuType submenu) D_FUNCPOSTFIT;

/** @brief ��д�����к�*/
D_Result 
p_stb_ca_burn_serial_number(void) D_FUNCPOSTFIT;

/** @brief ����������дOTP��Ϣ������*/
D_Result 
p_stb_ca_serial_burn_otp_info(void) D_FUNCPOSTFIT;

/** @brief USB��дOTP  ��Ϣ*/
D_Result 
p_stb_ca_burn_otp_info_by_usb(void) D_FUNCPOSTFIT;

/** @brief�����ж�OTP ��Ϣ�Ƿ��Ѿ���д*/
D_Result 
p_stb_ca_get_chipid_info(void) D_FUNCPOSTFIT;

/** @brief  ������дOTP  ��Ϣ*/
D_Result 
p_ca_burn_otp_by_serial_port(D_U8 *otp, D_U16 len) D_FUNCPOSTFIT;

/** @brief ������дotp */
D_Result 
ca_serial_burn_otp(D_HSerial sl_hdl, OPERATE_TYPE type);


extern D_GUIMenu cdca_menu;
extern D_GUIMenu ctica_menu;
extern D_GUIMenu mgca_menu;
extern D_GUIMenu wfca_menu;
extern D_GUIMenu qzca_menu;
extern D_GUIMenu abvca_menu;
extern D_GUIMenu xgca_menu;
extern D_GUIMenu divica_menu;
extern D_GUIMenu trca_menu;
extern D_GUIMenu thtfca_menu;
extern D_GUIMenu lxdtca_menu;
extern D_GUIMenu scca_menu;
extern D_GUIMenu unitendca_menu;
extern D_GUIMenu xsmca_menu;

#ifdef  __cplusplus
}
#endif
#endif

