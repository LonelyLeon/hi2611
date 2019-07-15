/** @file
* @brief ���������ò����ṹ
* @author ����
* @date 2005-6-30 ����: �����ļ�
* @date 2013-03-19 lc: ͳһƽ̨, ��������
*/

#ifndef _D_CONFIG_H_
#define _D_CONFIG_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dDBase.h"
#include "dTypes.h"
#include "dFEnd.h"
#include "dAV.h"
#include "dDate.h"
#include "pCustomConfig.h"

/** @brief Ӣ��*/
#define D_LANG_ENG	0

/** @brief ����*/
#define D_LANG_CHN	1

#ifndef D_CONF_DEF_LANG
#define	D_CONF_DEF_LANG	D_LANG_CHN
#endif

#ifndef D_CONF_PASSWORD_LEN
#define D_CONF_PASSWORD_LEN  D_CUSTOM_CONF_PASSWORD_LEN
#endif

#ifndef D_CONF_DEF_PASSWORD
#define D_CONF_DEF_PASSWORD			"0000"
#endif

#ifndef D_CONF_SUPER_PASSWORD
#define D_CONF_SUPER_PASSWORD		"9999"
#endif

#ifndef D_CONF_DEF_INFO_TIME
#define D_CONF_DEF_INFO_TIME	5
#define D_CONF_MAX_INFO_TIME	15
#define D_CONF_MIN_INFO_TIME	3
#endif

#ifndef D_CONF_DEF_STB_ID_LEN
#define D_CONF_DEF_STB_ID_LEN   20
#endif

#ifndef D_CONF_FAVOR_NAME_LEN
#define D_CONF_FAVOR_NAME_LEN   32
#endif

#ifndef D_CONF_NETWORK_NAME_LEN
#define D_CONF_NETWORK_NAME_LEN (32)
#endif

#define D_CONF_CA_INFO_LEN (32)


/** @brief �����в���, ������*/
typedef struct {
	D_U8				sw_major;
	D_U8				sw_minor;
	D_U16				sw_build_num;
	D_Char 				stb_id[D_CONF_DEF_STB_ID_LEN];
} D_StbParam;


typedef struct {
    	D_U16               		size;  // loader�ṹ��С
	D_U16				loader_ver;
	D_U8				download_flag;					// ���ر�־������������ʱ�����ֵ�Ƿ�Ϊ0�������0�򴥷�����
	D_U8				reserved0;//���ӻ�����ռ��
	D_U8				reserved1;//���ӻ�����ռ��
	D_U8				reserved2;//���ӻ�����ռ��

	D_U32				new_loader_ver;
	D_U8				fe_ts_sel; /* ǰ��ѡ����, ����Ŀ���, ���ݱ�žͿ���ʶ��ǰ���豸 */
	D_U8				reserved3;
	D_U8				reserved4;
	D_U8				reserved5;

	struct
	{
		D_FEndFreq freq;
		D_FEndBaud baud;
		D_FEndMod mod;
	}fparam; /* ����Ƶ����Ϣ */
	D_FEndFreq			lnbfreq1;
	D_FEndFreq			lnbfreq2;
	D_U8				diseqc_type;
	D_U8				diseqc_port;
	D_U8				f22kstate;
	D_U8				tid;
	D_U16				pid;
    	D_U8                		vid_output;
	D_U8				reserved6;
	D_U32               font_addr_in_flash; /* ���ɱ�����, �п��ܰ��ֿ�ŵ�flash����loader���� */
	D_StbParam          stb_param_copy;
    D_U32               crc;
} D_LoaderParam;
typedef struct
{
	D_U16   t2ms;//��ʱt2
	D_U16   t3ms;
	D_U16   t4ms;
	D_U16   t5ms;
	D_U8    vcc_bl_swapon;
	D_U8    vcc_bl_swapoff;
} D_Lvds_Sequence; //

typedef struct
{
	D_U8    channel_mode;
	D_U8    exchange_mode;
	D_U8    exchange_pn;
	D_U8    lvds_foramt;
	D_U8    lvds_da_tx_pds;
	D_U8    lvds_clk_tx_pds;
	D_U8    vp_div;
	D_U8    lvds_x;
	D_U8    invert;
	D_U8    lvds_type;
	D_U16   h_total;
	D_U16   v_total_50;
	D_U16   v_total_60;
	D_U16   h_active_width;
	D_U16   h_sync_width;
	D_U16   h_active_start;
	D_U16   v_active_width;
	D_U16   v_sync_width;
	D_U16   v_active_start;
	D_U16   pll_freq;
} D_PartPanelParam; 

typedef struct
{
	D_U8    rp;
	D_U8    model;
} D_SPModel_Param; 

typedef struct {
    D_U16               size;  // loader�ṹ��С
	D_DisplayParam      screenparam;
	D_Lvds_Sequence     lvds_sequence;
	D_LvdsInitParam    lvds_init_param;
	D_TvenLvdsParam 	tven_para;	
	D_U8 lvds_type;
	D_TCON_INIT_PARAM    tcon_param;
	D_SPModel_Param spmodel_param;
     D_U32               crc;
} D_PanelParam;


#define D_CONF_FULL_EPG_IN_MAIN		0
#define D_CONF_FULL_EPG_IN_EVERY	1
#define D_CONF_EPG_IN_CURR			2

/** @brief SI����*/
typedef struct {
	struct
	{
		D_FEndFreq freq;
		D_FEndBaud baud;
		D_FEndMod mod;
	}main; /* ֻ��DVBC��Ҫ��Ƶ�� */
	D_U8				epg_strategy;
	D_U8				nit_version;		/*�����Ŀ��汾�� */
#ifdef D_CA_SUPPORT_XGCA                    
    D_U8				cdxg_desc_version_num;
    D_U16				cdxg_desc_pid;
#endif
       D_U16     network_id; 
       D_Char     network_name[D_CONF_NETWORK_NAME_LEN + 1];       
	D_U16				reserved;
} D_SIParam;

/** @brief �û�����*/
typedef struct {
	/*��ǰ��Ŀ*/
	D_DBSrvID			curr_srv;
	/*��Ƶ����*/
	D_VidFormat			vid_fmt;
	D_VidOutput			vid_output;
	/*ͼ����� */
	D_VidPicParam		vid_param;	/*��ɫ����*/
	D_U8						cur_scanlist;//Reserved1;/* ��ǰƵ���� */
	D_VidPicRatio		vid_ratio;	/*�����*/
	/*��Ƶ����*/
	D_AudTrack			aud_track;
	D_U8				aud_mute;
	D_U8				volume;
	D_U8				lang;
	D_U8				transp;
	D_U8				info_time;
	D_U8				Reserved2;
	D_U8				Reserved3;
	D_U8				Reserved4;
	/*ʱ��ѡ��*/
	D_S32				time_offset;
	/*��ǰϲ����*/
	D_U8				curr_favor;
	D_U8				passwd_en;			/*�Ƿ����ò˵�����*/
	D_U8				Reserved5;
	D_U8				Reserved6;
	D_Bool			passwd_en_power_on;		/*�Ƿ����ÿ�������*/
	D_Bool			passwd_en_prog_lock;		/*�Ƿ�����Ƶ��������*/	
	D_U8				passwd_len;
	D_U8				passwd[D_CONF_PASSWORD_LEN  + 1];
	D_U32       channel_change_mode; /*��̨ʱ����(0)��֡(1)ģʽ*/
	D_Bool			smart_voice;		/*����������־*/
	D_U32   		stb_startup_time; /*��������*/
	D_Char   		favor_name[8][D_CONF_FAVOR_NAME_LEN]; /*ϲ��������*/
  D_U32       curr_ca; /*��ǰca, ca�Զ�ʶ�𱣴���*/
  D_ID        force_srv; /*����ǿ�Ʋ��Ž�Ŀ*/
  D_U8        ca_info[D_CONF_CA_INFO_LEN];   
	   
#ifdef D_CA_SUPPORT_XGCA
	D_U8			user_sort;
#endif
	D_VidInput 	       vid_input;
	D_U8		      balance;
	D_U8				save_type;/*�����������ѡ��*/

	D_S8				ad_version; /*���汾�ţ���Ҫ�Ǽ�¼����LOGO�汾�ţ� ��ʼ��Ϊ-1*/

} D_UserParam;

#ifdef D_USE_NETWORK
/** @brief �������ò���*/
#define IP_LEN						4
#define D_CONF_HOME_PAGE_LENGTH		30
#define D_CONF_USERNAME_LENGTH		20

typedef struct{
	D_U32	ip;
	D_U32	mask;
	D_U32	gateway;
	D_U32	main_dns;
	D_U32	second_dns;
	D_U8	home_page[D_CONF_HOME_PAGE_LENGTH];
	D_U8	mac[6];
	D_U32   proxy_addr;
	D_U16   proxy_port;
	D_Char  proxy_user[D_CONF_USERNAME_LENGTH];
	D_Char  proxy_password[D_CONF_USERNAME_LENGTH];
	D_Char  pppoe_user[D_CONF_USERNAME_LENGTH];
	D_Char  pppoe_password[D_CONF_USERNAME_LENGTH];
	D_U8	dhcp;
	D_U8	auto_dial_up_booting_time;
}D_NetworkParam;
#endif

/** @brief �����в���*/
/*�������ݽṹ��Ԫ���е���������ؼ�������ݽṹ�Ĵ�С�����������ļ�platform_cfg.mk�е�D_DB_CONFIG_BLOCK_SIZE�Ƚϣ���Ӧ�ĵ���D_DB_CONFIG_BLOCK_SIZE��ֵ��
������ָ����ݽṹ�Ĵ�С����D_DB_CONFIG_BLOCK_SIZE����������򽫳�������bug*/
typedef struct {
    D_ManufactoryID     manu_id;
	D_StbParam			stb_param;
	D_SIParam			si_param;
	D_UserParam			user_param;
#ifdef D_USE_NETWORK
	D_NetworkParam		net_param;
#endif
} D_StbConfig;

/** @brief ��ʼ��������Ϣ*/
D_Result p_conf_init (void) D_FUNCPOSTFIT;

/** @brief �ָ�Ϊ���������Ϣ
* @param update	������־
*/
D_Result p_conf_restore (D_Bool update) D_FUNCPOSTFIT;

/** @brief ȡ����Ƶ��ʽ����*/
D_VidFormat	p_conf_get_vid_fmt (void) D_FUNCPOSTFIT;

/** @brief ������Ƶ��ʽ����*/
D_Result p_conf_set_vid_fmt (D_VidFormat fmt) D_FUNCPOSTFIT;


#ifdef D_CA_SUPPORT_XGCA

D_Result p_conf_set_user_sort (D_U8 sort) D_FUNCPOSTFIT;

D_U8 p_conf_get_user_sort(void) D_FUNCPOSTFIT;

#endif

/** @brief ȡ����������*/
D_AudTrack p_conf_get_aud_track (void) D_FUNCPOSTFIT;

/** @brief ������������*/
D_Result p_conf_set_aud_track (D_AudTrack track) D_FUNCPOSTFIT;

/** @brief ȡ����������*/
D_U8 p_conf_get_volume (void) D_FUNCPOSTFIT;

/** @brief ������������*/
D_Result p_conf_set_volume (D_U8 vol) D_FUNCPOSTFIT;

/** @brief ȡ�õ�ǰ����ID*/
D_DBSrvID p_conf_get_curr_srv (void) D_FUNCPOSTFIT;

/** @brief ���õ�ǰ����ID*/
D_Result p_conf_set_curr_srv (D_DBSrvID id) D_FUNCPOSTFIT;

/** @brief ȡ�õ�ǰ����ID*/
D_DBSrvID p_conf_get_curr_atv_srv (void) D_FUNCPOSTFIT;

/** @brief ���õ�ǰ����ID*/
D_Result p_conf_set_curr_atv_srv (D_DBSrvID id) D_FUNCPOSTFIT;

/** @brief ȡ��ʱ������*/
D_S32 p_conf_get_time_offset (void) D_FUNCPOSTFIT;

/** @brief ����ʱ��*/
D_Result p_conf_set_time_offset (D_S32 off) D_FUNCPOSTFIT;

/** @brief ȡ��SI����*/
D_Result p_conf_get_si_param (D_SIParam *si_param) D_FUNCPOSTFIT;

/** @brief ����SI����*/
D_Result p_conf_set_si_param (D_SIParam *si_param) D_FUNCPOSTFIT;

/** @brief ȡ��Loader��������*/
D_Result p_conf_get_loader_param (D_LoaderParam *loader_param) D_FUNCPOSTFIT;

/** @brief ����Loader��������*/
D_Result p_conf_set_loader_param (D_LoaderParam *loader_param) D_FUNCPOSTFIT;

/** @brief ȡ��ǰ����*/
D_U8 p_conf_get_lang(void) D_FUNCPOSTFIT;

/** @brief ��������*/
D_U8 p_conf_set_lang(D_U8 lang) D_FUNCPOSTFIT;

/** @brief ȡ͸����*/
D_U8 p_conf_get_transp(void) D_FUNCPOSTFIT;

/** @brief ����͸����*/
D_U8 p_conf_set_transp(D_U8	transp) D_FUNCPOSTFIT;

/** @brief ȡ��Ϣ����ʾʱ��*/
D_U8 p_conf_get_info_time(void) D_FUNCPOSTFIT;

/** @brief ������Ϣ����ʾʱ��*/
D_U8 p_conf_set_info_time(D_U8	info_time) D_FUNCPOSTFIT;

/** @brief ȡ����Ƶ���*/
D_VidOutput p_conf_get_vid_output (void) D_FUNCPOSTFIT;

/** @brief ������Ƶ���*/
D_Result p_conf_set_vid_output (D_VidOutput out) D_FUNCPOSTFIT;

/** @brief ȡ�þ�����־*/
D_Bool p_conf_get_aud_mute (void) D_FUNCPOSTFIT;

/** @brief ���þ�����־*/
D_Result p_conf_set_aud_mute (D_Bool mute) D_FUNCPOSTFIT;

/** @brief ������Ƶ���� */
D_Result p_conf_set_vid_pic_param (D_VidPicParam *param)D_FUNCPOSTFIT;

/** @brief �����Ƶ���� */
D_Result p_conf_get_vid_pic_param (D_VidPicParam *param)D_FUNCPOSTFIT;

/** @brief ������Ƶ��߱��� */
D_Result p_conf_set_vid_pic_ratio (D_VidPicRatio ratio)D_FUNCPOSTFIT;

/** @brief �����Ƶ��߱��� */
D_VidPicRatio p_conf_get_vid_pic_ratio (void)D_FUNCPOSTFIT;

/** @brief ��ò˵������Ƿ�ʹ��*/
D_Bool p_conf_get_passwd_en (void) D_FUNCPOSTFIT;

/** @brief ���ò˵������Ƿ�ʹ��*/
D_Result p_conf_set_passwd_en (D_Bool en) D_FUNCPOSTFIT;

/** @brief ��ÿ��������Ƿ�ʹ��*/
D_Bool p_conf_get_poweron_passwd_en (void) D_FUNCPOSTFIT;

/** @brief ���ÿ��������Ƿ�ʹ��*/
D_Result p_conf_set_poweron_passwd_en (D_Bool en) D_FUNCPOSTFIT;

/** @brief ��ý�Ŀ�������Ƿ�ʹ��*/
D_Bool p_conf_get_prog_passwd_en (void) D_FUNCPOSTFIT;

/** @brief ���ý�Ŀ�������Ƿ�ʹ��*/
D_Result p_conf_set_prog_passwd_en (D_Bool en) D_FUNCPOSTFIT;

/** @brief ������볤��*/
D_U8 p_conf_get_passwd_len (void) D_FUNCPOSTFIT;

/** @brief �������*/
D_Result p_conf_get_passwd (D_Char *pass) D_FUNCPOSTFIT;

/** @brief ��������*/
D_Result p_conf_set_passwd (D_Char *pass) D_FUNCPOSTFIT;

/** @brief �����������
����ֵ: 	0  �������
			1 ������ȷ�������õ�������ͬ
			2 ������ȷ���볬��������ͬ	
*/
D_U8 p_conf_check_passwd (D_Char *pass) D_FUNCPOSTFIT;


/** @brief �õ���ǰ��̨����(0)  ��֡(1) ģʽ*/
D_U8 p_conf_get_channel_change_mode(void) D_FUNCPOSTFIT;

/** @brief ���õ�ǰ��̨����(0)  ��֡(1) ģʽ*/
D_Result p_conf_set_channel_change_mode(D_U8 mode) D_FUNCPOSTFIT;

/** @brief ȡ�ÿ����Ĵ���*/
D_U32 p_conf_get_stb_startup_time(void) D_FUNCPOSTFIT;

/** @brief �����Ĵ�����1*/
D_Result p_conf_add_stb_startup_time(void) D_FUNCPOSTFIT;

#ifdef D_USE_NETWORK
/** @brief ����������*/
D_Result p_conf_get_network_param(D_NetworkParam *net_param);

/** @brief �����������*/
D_Result p_conf_set_network_param(D_NetworkParam *net_param);
#endif

/** @brief ȡ��ϲ��������
* @param[in] num ϲ�����ţ�Ŀǰֻ֧��8��ϲ���飬���Ϊ0~7
* @param[out] name ϲ���������ַ���ָ�루����Ϊ��ָ��������㹻�ռ����ʹ�ã�
* @retval D_ERR	��ȡʧ��
* @retval D_OK	��ȡ�ɹ�
*/
D_Result p_conf_get_favor_name(D_U8 num, D_Char* name) D_FUNCPOSTFIT;

/** @brief ����ϲ��������
* @param[in] num ϲ�����ţ�Ŀǰֻ֧��8��ϲ���飬���Ϊ0~7
* @param[in] name ϲ���������ַ���ָ��
* @retval D_ERR	����ʧ��
* @retval D_OK	���óɹ�
*/
D_Result p_conf_set_favor_name(D_U8 num, D_Char* name) D_FUNCPOSTFIT;

/** @brief ȡ�õ�ǰCA*/
D_U32 p_conf_get_curr_ca(void) D_FUNCPOSTFIT;

/** @brief ���õ�ǰCA*/
D_Result p_conf_set_curr_ca(D_U32 curr_ca) D_FUNCPOSTFIT;

/** @brief ȡ�ü�¼�ķ���ID*/
D_DBSrvID p_conf_get_force_srv (void) D_FUNCPOSTFIT;

/** @brief ���õ�ǰ����ID*/
D_Result p_conf_set_force_srv (D_DBSrvID id) D_FUNCPOSTFIT;

/** @brief ȡ��CAģ��洢�������Ϣ
* @param[out] buf CA�����Ϣ�����ָ�루����Ϊ��ָ��������㹻�ռ����ʹ�ã�
* @retval D_ERR	��ȡʧ��
* @retval D_OK	��ȡ�ɹ�
*/
D_Result
p_conf_get_ca_related_info(D_U8* buf) D_FUNCPOSTFIT;

/** @brief ����CAģ��洢�������Ϣ
* @param[out] buf CA�����Ϣ�����ָ��
* @retval D_ERR	����ʧ��
* @retval D_OK	���óɹ�
*/
D_Result
p_conf_set_ca_related_info(D_U8* buf) D_FUNCPOSTFIT;

/** @brief ȡ����������*/
D_U8
p_conf_get_scan_config (void) D_FUNCPOSTFIT;

/** @brief ������������*/
D_Result
p_conf_set_scan_config (D_U8 cable_en) D_FUNCPOSTFIT;
/** @brief ���Ƶ�������*/
D_U8 
p_conf_get_scan_list_num (void) D_FUNCPOSTFIT;
/** @brief ����Ƶ�������*/
D_Result 
p_conf_set_scan_list_num (D_U8 num) D_FUNCPOSTFIT;
/** @brief ȡ����Ƶ����*/
D_VidInput
p_conf_get_vid_input (void) D_FUNCPOSTFIT;
/** @brief ������Ƶ����*/
D_Result
p_conf_set_vid_input (D_VidInput input) D_FUNCPOSTFIT;

/** @brief ȡ����������*/
D_U8 p_conf_get_balance (void) D_FUNCPOSTFIT;

/** @brief ������������*/
D_Result p_conf_set_balance (D_U8 val) D_FUNCPOSTFIT;

D_Result p_conf_restore_eep (void) D_FUNCPOSTFIT;
D_U8 p_conf_get_save_type() D_FUNCPOSTFIT;

/** @brief ȡ��Loader��������*/
D_Result p_conf_get_panel_param (D_PanelParam *panel_param) D_FUNCPOSTFIT;

/** @brief ����Loader��������*/
D_Result p_conf_set_panel_param (D_PanelParam *panel_param) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif

