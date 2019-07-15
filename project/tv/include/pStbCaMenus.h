/** @file
* @brief CA相关菜单接口
* @author 覃宜
* @date 2013-7-05 覃宜: 建立文件
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


/**< @brief CA子菜单类型*/
typedef enum {
	D_CA_SUBMENU_SC_IN,		
	D_CA_SUBMENU_MAIL_IN,	
	D_CA_SUBMENU_AUTHORIZATION_IN,
	D_CA_SUBMENU_SCMOTHER_IN,
	D_CA_SUBMENU_USER
} D_CAEnterSubmenuType;


/** @brief CA菜单初始化(根据当前ca类型选择对应的菜单)
* @param 无
* @return 成功返回D_OK
*/
D_Result
p_stb_ca_menu_init (void) D_FUNCPOSTFIT;

/** @brief 在GUI中处理ca事件
* @param type 事件类型
* @param param 事件参数
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result
p_ca_gui_solve_evt (D_CAEventType type, D_Ptr param) D_FUNCPOSTFIT;


/*********************公共接口***************************/
/** @breif 显示超级osd 显示窗口*/  
D_Result 
p_cdca_superosd_window_show(D_Ptr param)  D_FUNCPOSTFIT;

/**@breif 掩藏超级osd 显示窗口*/
D_Result         
p_cdca_superosd_window_hide (void) D_FUNCPOSTFIT;

/** @breif 显示ca 超级指纹窗口*/      
D_Result         
p_Ca_finger_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif 隐藏ca 超级指纹窗口*/      
D_Result         
p_Ca_finger_window_hide (void) D_FUNCPOSTFIT;

/** @breif 显示弹出框窗口*/      
D_Result
p_ca_dialog_window_show(D_CAEventType type, D_Ptr param)D_FUNCPOSTFIT;
/**********************END***************************/


/***********北京永新视博****************/
/** @breif 邮件具体内容窗口*/      
D_Result         
p_mail_detail_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示邮件管理窗口*/      
D_Result         
p_mail_manage_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示运营商信息窗口*/      
D_Result         
p_operator_info_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示钱包信息窗口*/      
D_Result         
p_purse_info_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示智能卡信息窗口*/      
D_Result         
p_smartcard_info_sub_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示智能卡信息窗口*/      
D_Result         
p_smartcard_info_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示反授权窗口*/        
D_Result         
p_antiauthorize_info_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示授权信息窗口*/      
D_Result         
p_authorization_info_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示子母卡信息窗口*/      
D_Result         
p_child_mother_card_window_show(void) D_FUNCPOSTFIT;

/** @brief 显示永新ca级别设置设置窗口*/
D_Result
p_level_set_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示机卡配对*/
D_Result p_card_pair_window_show () D_FUNCPOSTFIT;

/** @breif 显示工作时段*/
D_Result p_work_time_window_show () D_FUNCPOSTFIT;

/** @breif 显示pin码设置窗口*/  
D_Result p_modify_pin_window_show () D_FUNCPOSTFIT;

/** @breif 显示ca 高级预览窗口*/      
D_Result         
p_ca_senior_preview_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif 隐藏ca 高级预览窗口*/      
D_Result         
p_ca_senior_preview_window_hide (void) D_FUNCPOSTFIT;

/** @breif 显示ca进度条窗口*/
D_Result         
p_ca_progress_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif 隐藏ca进度条窗口*/
D_Result         
p_ca_progress_window_hide (void) D_FUNCPOSTFIT;

/** @breif 显示ippv窗口*/      
D_Result         
p_ippv_info_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示ca信息(邮件图标、指纹、反授权、ppv图标、预览图标)窗口*/      
D_Result         
p_Ca_osd_window_show (D_CAEventType type, D_Ptr param) D_FUNCPOSTFIT;

/** @breif 隐藏ca信息(邮件图标、指纹、反授权, 滚动条)窗口*/      
D_Result         
p_Ca_osd_window_hide (void) D_FUNCPOSTFIT;

/** @breif 备份ca信息(邮件图标、指纹、反授权, 滚动条)窗口的数据*/      
D_Result         
p_Ca_osd_window_bak (void) D_FUNCPOSTFIT;

/** @breif 显示ca ipptv 购买窗口*/      
D_Result         
p_ca_ipptv_buy_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif 隐藏ca ipptv 购买窗口*/      
D_Result         
p_ca_ipptv_buy_window_hide (void) D_FUNCPOSTFIT;

/***************************************/


/***********北京算通科技****************/
/** @breif 显示算通授权窗口*/  
D_Result         
p_CTICa_authorization_info_window_show(void) D_FUNCPOSTFIT;
/** @breif 算通IPPV信息*/ 
D_Result 
p_CTICa_auth_ippv_info_window_show(D_U8 flag) D_FUNCPOSTFIT;

/** @breif 算通邮件具体内容窗口*/   
D_Result         
p_CTICa_mail_detail_window_show(void) D_FUNCPOSTFIT;

/** @breif 算通显示邮件管理窗口*/      
D_Result         
p_CTICa_mail_manage_window_show(void) D_FUNCPOSTFIT;

/** @breif 准禁播管理*/
D_Result 
p_CTICa_allow_ban_setting_window_show(D_U8 *pin) D_FUNCPOSTFIT;

/** @breif 算通密码修改*/     
D_Result
p_CTICa_pin_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示算通智能卡信息窗口*/      
D_Result         
p_CTICa_smartcard_info_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示pin码设置窗口*/  
D_Result 
p_CTICa_modify_pin_window_show () D_FUNCPOSTFIT;

/** @breif 用户选择跳转*/   
D_Result   
p_CTICa_skip_select_window_show() D_FUNCPOSTFIT;

/** @brief 显示算通ca级别设置设置窗口*/
D_Result
p_CTICa_level_set_window_show(void) D_FUNCPOSTFIT;
/** @brief 隐藏ippv窗口*/
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

/***********德芯****************/
/** @breif 显示智能卡信息*/      
D_Result         
p_DSCa_smartcard_info_window_show(void) D_FUNCPOSTFIT;
/** @breif 显示授权信息*/ 
D_Result 
p_DSCa_smartcard_info_window_cos_show(void) D_FUNCPOSTFIT;

D_Result 
p_DSCa_authorization_info_window_show(void) D_FUNCPOSTFIT;
/** @breif 级别设置*/ 
D_Result 
p_DSCa_level_set_window_show(void) D_FUNCPOSTFIT;
/** @breif 邮件内容*/ 
D_Result 
p_DSCa_mail_detail_window_show(D_U8 num, D_U8 *sender) D_FUNCPOSTFIT;
/** @breif 邮件菜单*/ 
D_Result 
p_DSCa_mail_manage_window_show(void) D_FUNCPOSTFIT;
/** @breif 密码修改*/ 
D_Result 
p_DSCa_modify_pin_window_show(void) D_FUNCPOSTFIT;
/** @breif 显示运营商信息*/ 
D_Result 
p_DSCa_operator_info_window_show(void) D_FUNCPOSTFIT;
/** @breif 工作时段设置*/ 
D_Result 
p_DSCa_work_time_window_show(void) D_FUNCPOSTFIT;
/** @breif 钱包信息*/ 
D_Result 
p_DSCa_purse_info_window_show(void) D_FUNCPOSTFIT;
/** @breif 显示超级OSD*/
D_Result 
p_DSCa_superosd_window_show (D_Ptr param) D_FUNCPOSTFIT;
/** @breif 隐藏超级OSD*/
D_Result 
p_DSCa_superosd_window_hide (void) D_FUNCPOSTFIT;

/** @breif 显示或ECM指纹窗口*/   
D_Result         
p_DSCa_finger_window_show (D_Ptr param) D_FUNCPOSTFIT;

D_Result  
p_DSCa_ipptv_buy_window_show (D_Ptr param) D_FUNCPOSTFIT;

D_Result  
p_DSCa_ipptv_buy_window_hide(void) D_FUNCPOSTFIT;

/** @breif 隐藏ECM指纹窗口*/      
D_Result         
p_DSCa_finger_window_hide (void) D_FUNCPOSTFIT;

D_Result         
p_DSCa_progress_window_show (D_Ptr param) D_FUNCPOSTFIT;

D_Result         
p_DSCa_progress_window_hide(void) D_FUNCPOSTFIT;

/***************************************/

/***********四川成都高斯贝尔****************/
/** @breif 显示高斯贝尔授权窗口*/  
D_Result         
p_GOSCa_authorization_info_window_show(void) D_FUNCPOSTFIT;

D_Result  
p_GOSCa_authorization_info_window_reshow(void) D_FUNCPOSTFIT;

/** @breif 高斯贝尔邮件具体内容窗口*/   
D_Result         
p_GOSCa_mail_detail_window_show(D_U8 num) D_FUNCPOSTFIT;

/** @breif 高斯贝尔显示邮件管理窗口*/      
D_Result         
p_GOSCa_mail_manage_window_show(void) D_FUNCPOSTFIT;

/** @breif 高斯贝尔显示机卡绑定信息*/ 
D_Result
p_GOSCa_bind_info_window_show () D_FUNCPOSTFIT;

/** @breif 高斯贝尔密码修改*/     
D_Result
p_GOSCa_modify_pin_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示高斯贝尔智能卡信息窗口*/      
D_Result         
p_GOSCa_smartcard_info_window_show(void) D_FUNCPOSTFIT;


/** @brief 显示高斯贝尔ca级别设置设置窗口*/
D_Result
p_GOSCa_level_set_window_show(void) D_FUNCPOSTFIT;

D_Result
p_GOSCa_smartcard_info_window_reshow(void) D_FUNCPOSTFIT;

/** @brief 显示高斯贝尔ca运营商信息窗口*/
D_Result
p_GOSCa_operator_info_window_show(void)D_FUNCPOSTFIT;
D_Result
p_GOSCa_operator_info_window_reshow(void)D_FUNCPOSTFIT;


/***************************************/

/***********上海三洲迅驰****************/
/** @breif 显示窗口*/      
D_Result         
p_mgca_ipptv_window_show () D_FUNCPOSTFIT;

/** @breif 隐藏ca ipptv 购买窗口*/      
D_Result         
p_mgca_ipptv_window_hide () D_FUNCPOSTFIT;

/** @breif 显示mgca ipptv 购买窗口*/      
D_Result         
p_mgca_ipptv_buy_window_show () D_FUNCPOSTFIT;

/** @breif 隐藏mgca ipptv 购买窗口*/      
D_Result         
p_mgca_ipptv_buy_window_hide (void) D_FUNCPOSTFIT;

/** @breif 显示mgca 智能卡信息窗口*/  
D_Result
p_mgca_smartcard_info_window_show(void) D_FUNCPOSTFIT;

D_Result
/** @breif 显示mgca智能卡信息第二页窗口*/      
p_mgca_smartcard_info_sub_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示mgca子母卡窗口*/      
D_Result         
p_mgca_child_mother_card_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示mgca邮件窗口*/      
D_Result         
p_mgca_mail_manage_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示mgca邮件内容窗口*/      
D_Result         
p_mgca_mail_detail_window_show (void) D_FUNCPOSTFIT;

/***************************************/


/***********北京数码视讯****************/
/** @breif 显示dvtca 智能卡信息窗口*/  
D_Result
p_dvtca_smartcard_info_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示dvtca 智能卡子信息窗口*/  
D_Result
p_dvtca_smartcard_info_sub_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示窗口*/      
D_Result         
p_DVTCa_operator_info_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示运营商授权信息窗口*/      
D_Result         
p_dvtca_authorization_info_window_show () D_FUNCPOSTFIT;

/** @breif 显示钱包信息窗口*/      
D_Result         
p_dvtca_purse_info_window_show () D_FUNCPOSTFIT;

/** @breif 显示窗口*/        
D_Result         
p_dvtca_ippv_info_window_show () D_FUNCPOSTFIT;

/** @brief 	显示ca级别设置设置窗口
* @param 	无
* @return	函数正确执行返回D_OK,失败返回D_ERR
*/
D_Result
p_dvtca_level_set_window_show () D_FUNCPOSTFIT;

/** @breif 显示时段设置窗口*/
D_Result 
p_dvtca_work_time_window_show () D_FUNCPOSTFIT;

/** @breif 显示密码修改窗口*/  
D_Result 
p_dvtca_modify_pin_window_show () D_FUNCPOSTFIT;

/** @breif 显示子母卡窗口*/      
D_Result         
p_dvtca_child_mother_card_window_show () D_FUNCPOSTFIT;

/** @breif 显示IPPV购买或取消窗口*/      
D_Result p_dvtca_ippv_buy_cancel_window_show()D_FUNCPOSTFIT;

/** @breif 显示dvtca邮件窗口*/      
D_Result         
p_dvtca_mail_manage_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示dvtca邮件内容窗口*/ 
D_Result         
p_dvtca_mail_detail_window_show () D_FUNCPOSTFIT;

/** @breif 显示dvtca隐藏菜单*/ 
D_Result  
p_dvtca_hidemenu_set_window_show() D_FUNCPOSTFIT;

/** @breif 显示全屏公告窗口*/
D_Result         
p_DVTCa_tip_announcement_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif 隐藏全屏公告窗口*/      
D_Result         
p_DVTCa_tip_announcement_window_hide (void) D_FUNCPOSTFIT;

/** @breif 显示dvtca 超级指纹窗口*/      
D_Result         
p_DVTCa_finger_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif 隐藏dvtca 超级指纹窗口*/      
D_Result         
p_DVTCa_finger_window_hide (void) D_FUNCPOSTFIT;

/***********万发****************/
/** @breif 显示wfca 智能卡信息窗口*/  
D_Result         
p_wfca_smartcard_info_window_show () D_FUNCPOSTFIT;

/** @breif 显示wfca 智能卡信息第二页窗口*/  
D_Result         
p_wfca_smartcard_info_sub_window_show () D_FUNCPOSTFIT;

/** @breif 显示wfca邮件信息窗口*/  
D_Result         
p_wfca_mail_manage_window_show () D_FUNCPOSTFIT;

/** @breif 显示wfca邮件内容信息窗口*/  
D_Result         
p_wfca_mail_detail_window_show () D_FUNCPOSTFIT;

/** @breif 显示wfca授权信息窗口*/  
D_Result         
p_wfca_authorization_info_window_show () D_FUNCPOSTFIT;

/** @breif 显示wfca ipptv 窗口*/  
D_Result         
p_wfca_ipptv_buy_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif 隐藏wfca ipptv 窗口*/  
D_Result         
p_wfca_ipptv_buy_window_hide () D_FUNCPOSTFIT;

/** @breif 显示CAS 出错信息窗口*/      
D_Result         
p_wfca_error_info_window_show () D_FUNCPOSTFIT;

/** @breif 级别控制*/
D_Result
p_wfca_level_set_window_show () D_FUNCPOSTFIT;

/** @breif 显示父母锁解锁窗口*/      
D_Result         
p_wfca_tip_parentalctrl_window_show (void) D_FUNCPOSTFIT;

/** @breif 掩藏父母锁解锁窗口*/      
D_Result         
p_wfca_tip_parentalctrl_window_hide (void) D_FUNCPOSTFIT;

/** @breif 显示密码修改窗口*/  
D_Result 
p_wfca_modify_pin_window_show () D_FUNCPOSTFIT;
/***************************************/

/***********全智****************/
/** @breif 显示qzca 智能卡信息窗口*/      
D_Result   
p_QZCa_smartcard_info_window_show () D_FUNCPOSTFIT;

/** @breif 显示qzca邮件窗口*/     
D_Result         
p_QZCa_mail_manage_window_show () D_FUNCPOSTFIT;

/** @breif 显示qzca邮件内容信息窗口*/      
D_Result         
p_QZCa_mail_detail_window_show () D_FUNCPOSTFIT;
/***************************************/

/***********北京联广视讯****************/
/** @breif 基本授权信息窗口*/  
D_Result    
p_ABVCa_freeauthorization_info_window_show(void) D_FUNCPOSTFIT;

/** @breif 基本授权信息窗口*/  
D_Result    
p_ABVCa_ppcauthorization_info_window_show(void) D_FUNCPOSTFIT;

/** @breif 基本授权信息窗口*/  
D_Result    
p_ABVCa_ppvauthorization_info_window_show(void) D_FUNCPOSTFIT;

/** @breif 消费或充值历史信息*/  
D_Result         
p_ABVCa_consume_history_info_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示邮件管理窗口*/      
D_Result         
p_ABVCa_mail_manage_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示智能卡信息窗口*/      
D_Result         
p_ABVCa_smartcard_info_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示运营商信息窗口*/      
D_Result       
p_ABVCa_operator_info_window_show(void) D_FUNCPOSTFIT;

/** @brief 显示永新ca级别设置设置窗口*/
D_Result
p_ABVCa_level_set_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示pin码设置窗口*/  
D_Result
p_ABVCa_modify_pin_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示工作时段*/
D_Result
p_ABVCa_work_time_window_show(void) D_FUNCPOSTFIT;

/** @breif 邮件具体内容窗口*/      
D_Result         
p_ABVCa_mail_detail_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示和掩藏超级osd 显示窗口*/  
D_Result 
p_ABVCa_superosd_window_show(D_Ptr param)  D_FUNCPOSTFIT;

/** @breif 显示ca ipptv 购买窗口*/      
D_Result         
p_ABVCa_ippv_buy_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif 隐藏ca ipptv 购买窗口*/      
D_Result         
p_ABVCa_ippv_buy_window_hide (void) D_FUNCPOSTFIT;

/** @brief 	显示成人级节目窗口*/
D_Result
p_ABVCa_maurity_prog_window_show(void) D_FUNCPOSTFIT;

/** @breif 隐藏成人级节目窗口*/      
D_Result         
p_ABVCa_maurity_prog_window_hide (void) D_FUNCPOSTFIT;

/** @breif 显示ECM指纹窗口*/      
D_Result         
p_ABVCa_finger_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif 隐藏ECM指纹窗口*/      
D_Result         
p_ABVCa_finger_window_hide (void) D_FUNCPOSTFIT;

/** @breif 显示超级osd窗口*/      
D_Result         
p_ABVCa_superosd_window_hide (void) D_FUNCPOSTFIT;

/** @breif 显示用户指纹窗口*/      
D_Result         
p_ABVCa_superfinger_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif 掩藏用户指纹窗口*/      
D_Result         
p_ABVCa_superfinger_window_hide (void) D_FUNCPOSTFIT;

/** @breif 显示EMM指纹窗口*/      
D_Result         
p_ABVCa_emmfinger_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif 掩藏EMM指纹窗口*/      
D_Result         
p_ABVCa_emmfinger_window_hide (void) D_FUNCPOSTFIT;
/** @breif 掩藏超级osd窗口*/      
D_Result         
p_ABVCa_convertfinger_window_show (D_Ptr param) D_FUNCPOSTFIT;
/** @brief 烧写序列号*/
D_Result abvca_burn_serial_number(D_HSerial sl_hdl, OPERATE_TYPE type) D_FUNCPOSTFIT;

/** @通过串口发送信息*/      
D_Result         
p_ABVCa_send_msg_from_ca_to_otherstb (D_Ptr param) D_FUNCPOSTFIT;
/***************************************/
/***********北京数字太和****************/
/** @breif 显示unitendca udrm信息窗口*/  
D_Result
p_unitendca_udrm_info_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示unitendca PPC授权信息窗口*/  
D_Result
p_unitendca_ppc_info_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示nitendca邮件窗口*/      
D_Result         
p_unitendca_mail_manage_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示unitendca邮件内容窗口*/ 
D_Result         
p_unitendca_mail_detail_window_show () D_FUNCPOSTFIT;

/** @brief 	显示ca级别设置设置窗口*/ 
D_Result
p_unitendca_level_set_window_show () D_FUNCPOSTFIT;

/** @breif 显示密码修改窗口*/  
D_Result 
p_unitendca_modify_pin_window_show () D_FUNCPOSTFIT;

/** @breif 显示全屏重要邮件窗口*/      
D_Result         
p_unitendca_tip_email_window_show(D_Ptr param) D_FUNCPOSTFIT;

/** @breif 隐藏全屏重要窗口(暂时无用)*/      
D_Result         
p_unitendca_tip_email_window_hide(void) D_FUNCPOSTFIT;

/** @breif 显示父母锁解锁窗口*/      
D_Result         
p_UNITENDCa_tip_parentalctrl_window_show () D_FUNCPOSTFIT;

/** @breif 掩藏父母锁解锁窗口*/      
D_Result         
p_UNITENDCa_tip_parentalctrl_window_hide () D_FUNCPOSTFIT;
/***************************/

/***********新光****************/
/** @breif 显示xgca 智能卡信息窗口*/  
D_Result         
p_xgca_smartcard_info_window_show (void) D_FUNCPOSTFIT;
/** @breif 显示无卡xgca 智能卡信息窗口*/  
D_Result         
p_xgca_smartcard_info_window_show_cos (void) D_FUNCPOSTFIT;
/** @breif 显示xgca邮件信息窗口*/  
D_Result         
p_xgca_mail_manage_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示xgca邮件内容信息窗口*/  
D_Result         
p_xgca_mail_detail_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示xgca授权信息窗口*/  
D_Result         
p_xgca_authorization_info_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示xgca子母卡信息窗口*/  
D_Result         
p_xgca_card_pair_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示窗口*/      
D_Result         
p_xgca_stb_card_pair_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示窗口*/      
D_Result         
p_xgca_ippv_buy_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif 隐藏ca ipptv 购买窗口*/      
D_Result         
p_xgca_ippv_buy_window_hide (void) D_FUNCPOSTFIT;

/** @breif 显示自动喂卡窗口*/      
D_Result         
p_auto_xgca_card_pair_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif 隐藏自动喂卡窗口*/      
D_Result         
p_auto_xgca_card_pair_window_hide () D_FUNCPOSTFIT;

/** @brief 烧写序列号*/
D_Result 
xgca_burn_serial_number(D_HSerial sl_hdl, OPERATE_TYPE type) D_FUNCPOSTFIT;

/** @breif 高级功能窗口*/  
D_Result         
p_xgca_senior_fun_window_show(void)D_FUNCPOSTFIT;

/** @breif 显示窗口*/      
D_Result         
xgca_level_control_window_show(D_Ptr param) D_FUNCPOSTFIT;

/** @breif 隐藏窗口*/      
D_Result         
xgca_level_control_window_hide() D_FUNCPOSTFIT;


/***********深圳数视通****************/
/** @breif 智能卡信息菜单*/      
D_Result         
p_DIVICa_smartcard_info_window_show (void) D_FUNCPOSTFIT;

/** @breif 授权信息菜单*/ 
D_Result         
p_DIVICa_authorization_info_window_show (void) D_FUNCPOSTFIT;

/** @breif 电子邮件菜单*/      
D_Result         
p_DIVICa_mail_manage_window_show (void) D_FUNCPOSTFIT;

/** @breif 电子邮件内容菜单*/      
D_Result         
p_DIVICa_mail_detail_window_show (D_Char* frm , D_U8 TitleLen) D_FUNCPOSTFIT;

/** @breif 密码修改菜单*/  
D_Result 
p_DIVICa_modify_pin_window_show (void) D_FUNCPOSTFIT;

/** @breif 级别设置菜单*/
D_Result
p_DIVICa_level_set_window_show (void) D_FUNCPOSTFIT;

/** @breif 工作时段菜单*/
D_Result 
p_DIVICa_work_time_window_show (void) D_FUNCPOSTFIT;

/** @breif 子母卡菜单*/      
D_Result         
p_DIVICa_cmcard_pair_window_show (void) D_FUNCPOSTFIT;

/** @breif 子母卡提示监控窗口*/      
D_Result         
p_DIVICa_cmcard_pair_monitor_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif 开机缴费提醒*/  
D_Result         
p_DIVICa_tip_entitle_window_show (D_Ptr param) D_FUNCPOSTFIT;

/***********北京腾锐****************/
/** @breif 显示智能卡信息菜单*/  
D_Result         
p_TRCa_smartcard_info_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示授权信息菜单*/   
D_Result         
p_TRCa_authorization_info_window_show(void) D_FUNCPOSTFIT;

/** @breif 钱包信息菜单*/      
D_Result         
p_TRCa_purse_info_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示ipp订购菜单*/
D_Result 
p_TRCa_ipp_order_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示ipp消费菜单*/     
D_Result
p_TRCa_ipp_consume_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示级别设置菜单*/      
D_Result         
p_TRCa_level_set_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示pin码设置菜单*/  
D_Result 
p_TRCa_modify_pin_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示子母卡配对菜单*/   
D_Result   
p_TRCa_cmcard_pair_window_show(void) D_FUNCPOSTFIT;

/** @brief 显示电子邮件菜单*/
D_Result
p_TRCa_mail_manage_window_show(void) D_FUNCPOSTFIT;
    
/** @breif 显示邮件内容菜单*/      
D_Result         
p_TRCa_mail_detail_window_show (D_Char* frm , D_U8 TitleLen) D_FUNCPOSTFIT;
    
/** @breif 显示全屏公告窗口*/      
D_Result         
p_TRCa_tip_announcement_window_show(D_Ptr param) D_FUNCPOSTFIT;

/** @breif 隐藏全屏公告窗口(外部仅换台调用)*/      
D_Result         
p_TRCa_tip_announcement_window_hide(void) D_FUNCPOSTFIT;

/** @breif 显示ca ipptv 购买窗口*/      
D_Result         
p_TRCa_ipptv_buy_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif 掩藏ca ipptv 购买窗口(外部仅换台调用)*/      
D_Result         
p_TRCa_ipptv_buy_window_hide (void) D_FUNCPOSTFIT;

/** @breif 显示父母锁解锁窗口*/      
D_Result         
p_TRCa_tip_parentalctrl_window_show (void) D_FUNCPOSTFIT;

/** @breif 掩藏父母锁解锁窗口*/      
D_Result         
p_TRCa_tip_parentalctrl_window_hide (void) D_FUNCPOSTFIT;

/** @breif 显示指纹信息窗口*/      
D_Result         
p_TRCa_finger_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif 掩藏指纹信息窗口*/      
D_Result         
p_TRCa_finger_window_hide (void) D_FUNCPOSTFIT;
/***************************************/

/***********北京同方凌讯****************/
/** @breif 显示用户信息菜单*/
D_Result         
p_THTFCa_user_window_show () D_FUNCPOSTFIT;

/** @breif 显示运营商信息菜单*/
D_Result         
p_THTFCa_operator_info_window_show () D_FUNCPOSTFIT;

/** @breif 显示授权信息菜单*/
D_Result         
p_THTFCa_authorization_info_window_show () D_FUNCPOSTFIT;

/** @breif 显示pin码状态设置菜单*/  
D_Result
p_THTFCa_pin_state_set_window_show () D_FUNCPOSTFIT;

/** @breif 显示pin码设置菜单*/  
D_Result 
p_THTFCa_modify_pin_window_show () D_FUNCPOSTFIT;

/** @breif 级别设置菜单*/
D_Result
p_THTFCa_level_set_window_show () D_FUNCPOSTFIT;

/** @breif 工作时段菜单*/
D_Result 
p_THTFCa_work_time_window_show () D_FUNCPOSTFIT;

/** @brief 显示电子邮件菜单*/
D_Result         
p_THTFCa_mail_manage_window_show () D_FUNCPOSTFIT;

/** @breif 显示邮件内容菜单*/ 
D_Result         
p_THTFCa_mail_detail_window_show () D_FUNCPOSTFIT;

/** @breif 显示续费自动通知菜单*/ 
D_Result
p_THTFCa_overdue_inform_set_window_show () D_FUNCPOSTFIT;

/** @brief 	显示成人级节目窗口*/
D_Result
p_THTFCa_maurity_prog_window_show(void) D_FUNCPOSTFIT;

/** @breif 隐藏成人级节目窗口*/      
D_Result         
p_THTFCa_maurity_prog_window_hide (void) D_FUNCPOSTFIT;

/***********成都锐逸(力芯)****************/

/** @breif 显示智能卡信息菜单*/  
D_Result         
p_LXDTCa_smartcard_info_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示授权信息菜单*/   
D_Result         
p_LXDTCa_authorization_info_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示ippv订购信息菜单*/      
D_Result         
p_LXDTCa_ippv_order_info_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示ippv钱包信息菜单*/
D_Result 
p_LXDTCa_ippv_purse_info_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示级别设置菜单*/      
D_Result         
p_LXDTCa_level_set_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示pin码设置菜单*/  
D_Result 
p_LXDTCa_modify_pin_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示机卡对应菜单*/  
D_Result 
p_LXDTCa_card_pair_window_show (void) D_FUNCPOSTFIT;

/** @brief 显示电子邮件菜单*/
D_Result
p_LXDTCa_mail_manage_window_show(void) D_FUNCPOSTFIT;
    
/** @breif 显示邮件内容菜单*/      
D_Result         
p_LXDTCa_mail_detail_window_show (D_Char* frm , D_U8 TitleLen) D_FUNCPOSTFIT;
    
/***************************************/
/***********上海天柏****************/

/** @breif 显示智能卡信息菜单*/  
D_Result         
p_DVNCa_smartcard_info_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示授权信息菜单*/   
D_Result         
p_DVNCa_authorization_info_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示充值记录菜单*/      
D_Result         
p_DVNCa_charge_record_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示级别设置菜单*/
D_Result 
p_DVNCa_level_set_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示密码修改菜单*/      
D_Result         
p_DVNCa_modify_pin_window_show(void) D_FUNCPOSTFIT;

/** @breif 显示机卡对应菜单*/  
D_Result 
p_DVNCa_stb_card_pair_window_show (void) D_FUNCPOSTFIT;

/** @brief 显示电子邮件菜单*/
D_Result
p_DVNCa_mail_manage_window_show(void) D_FUNCPOSTFIT;
    
/** @breif 显示邮件内容菜单*/      
D_Result         
p_DVNCa_mail_detail_window_show (D_Char* frm , D_U8 TitleLen) D_FUNCPOSTFIT;

/** @breif 显示滚屏OSD消息*/      
D_Result
p_DVNCa_tip_osd_screen_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif 掩藏滚屏OSD消息*/      
D_Result         
p_DVNCa_tip_osd_screen_window_hide (void) D_FUNCPOSTFIT;

/** @breif 显示自动机卡对应消息*/ 
D_Result         
p_DVNCa_tip_stb_card_pair_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif 掩藏自动机卡对应消息*/      
D_Result         
p_DVNCa_tip_stb_card_pair_window_hide (void) D_FUNCPOSTFIT;

/** @breif 显示自动充值消息*/      
D_Result         
p_DVNCa_tip_auto_change_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif 掩藏自动充值消息*/           
D_Result         
p_DVNCa_tip_auto_change_window_hide (void) D_FUNCPOSTFIT;

/** @breif 显示自动喂养消息*/  
D_Result         
p_DVNCa_tip_auto_feed_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif 掩藏自动喂养消息*/      
D_Result         
p_DVNCa_tip_auto_feed_window_hide (void) D_FUNCPOSTFIT;

/** @breif IPP信息菜单*/      
D_Result         
p_DVNCa_ippv_order_info_window_show (void) D_FUNCPOSTFIT;

/** @breif IPP购买信息*/      
D_Result         
p_DVNCa_ipptv_buy_window_show (D_Ptr param) D_FUNCPOSTFIT;

/** @breif 隐藏ca ipptv 购买窗口*/      
D_Result         
p_DVNCa_ipptv_buy_window_hide (void) D_FUNCPOSTFIT;
/***************************************/

/***********成都英集****************/
/** @breif 显示yjca 智能卡信息窗口*/      
D_Result   
p_YJCa_smartcard_info_window_show () D_FUNCPOSTFIT;

/** @breif 显示授权窗口*/      
D_Result         
p_YJCa_authorization_info_window_show () D_FUNCPOSTFIT;

/** @breif 显示yjca邮件窗口*/     
D_Result         
p_YJCa_mail_manage_window_show () D_FUNCPOSTFIT;

/** @breif 显示yjca邮件内容信息窗口*/      
D_Result         
p_YJCa_mail_detail_window_show () D_FUNCPOSTFIT;
/** @breif 显示子母卡信息窗口*/      
D_Result         
p_YJCa_child_mother_card_window_show () D_FUNCPOSTFIT;

/***************************************/
/******************首创*********************/
/** @breif 显示scca 智能卡信息窗口*/      
D_Result         
p_SCCa_smartcard_info_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示scca 钱包信息窗口*/      
D_Result         
p_SCCa_purse_info_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示scca 授权信息窗口*/      
D_Result         
p_SCCa_authorization_info_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示scca 运营商信息窗口*/		
D_Result         
p_SCCa_operator_info_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示scca 邮件信息窗口*/		
D_Result         
p_SCCa_mail_manage_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示scca 邮件内容信息窗口*/		
D_Result         
p_SCCa_mail_detail_window_show (D_U8 num) D_FUNCPOSTFIT;

/** @breif 显示scca 密码设置信息窗口*/		
D_Result 
p_SCCa_modify_pin_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示scca 工作时段信息窗口*/		
D_Result 
p_SCCa_work_time_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示scca 级别设置信息窗口*/		
D_Result
p_SCCa_level_set_window_show (void) D_FUNCPOSTFIT;

/***************************************/

/******************芯视猫*********************/
/** @breif 显示xsmca 智能卡信息窗口*/      
D_Result         
p_XSMCa_smartcard_info_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示xsmca 邮件信息窗口*/		
D_Result         
p_XSMCa_mail_manage_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示xsmca 邮件内容信息窗口*/		
D_Result         
p_XSMCa_mail_detail_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示xsmca 子母卡喂养窗口*/		
D_Result         
p_XSMCa_child_mother_card_window_show () D_FUNCPOSTFIT;

/***************************************/


/***********多CA****************/
/** @breif 多CA选择菜单*/
D_Result
p_ca_hide_window_show () D_FUNCPOSTFIT;

/** @breif 多CA编译回调*/
D_Result
complie_cas_handler(D_U32* param)D_FUNCPOSTFIT;

/** @breif 重新显示ca提示信息窗口*/  
D_Result p_Ca_BuyMsg_reshow (void) D_FUNCPOSTFIT;

/** @breif 备份ca提示信息的相关数据*/      
D_Result p_Ca_BuyMsg_bak (void) D_FUNCPOSTFIT;

/** @brief 进入CA子菜单
* @param submenu: D_CAEnterSubmenuType
* @return 成功返回D_OK
*/
D_Result
p_stb_ca_submenu_enter (D_CAEnterSubmenuType submenu) D_FUNCPOSTFIT;

/** @brief 烧写机顶盒号*/
D_Result 
p_stb_ca_burn_serial_number(void) D_FUNCPOSTFIT;

/** @brief 创建串口烧写OTP信息的任务*/
D_Result 
p_stb_ca_serial_burn_otp_info(void) D_FUNCPOSTFIT;

/** @brief USB烧写OTP  信息*/
D_Result 
p_stb_ca_burn_otp_info_by_usb(void) D_FUNCPOSTFIT;

/** @brief用于判断OTP 信息是否已经烧写*/
D_Result 
p_stb_ca_get_chipid_info(void) D_FUNCPOSTFIT;

/** @brief  串口烧写OTP  信息*/
D_Result 
p_ca_burn_otp_by_serial_port(D_U8 *otp, D_U16 len) D_FUNCPOSTFIT;

/** @brief 串口烧写otp */
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

