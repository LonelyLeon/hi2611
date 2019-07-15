/** @file
* @brief 机顶盒设置参数结构
* @author 龚克
* @date 2005-6-30 龚克: 建立文件
* @date 2013-03-19 lc: 统一平台, 代码整理
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

/** @brief 英文*/
#define D_LANG_ENG	0

/** @brief 中文*/
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


/** @brief 机顶盒参数, 向后兼容*/
typedef struct {
	D_U8				sw_major;
	D_U8				sw_minor;
	D_U16				sw_build_num;
	D_Char 				stb_id[D_CONF_DEF_STB_ID_LEN];
} D_StbParam;


typedef struct {
    	D_U16               		size;  // loader结构大小
	D_U16				loader_ver;
	D_U8				download_flag;					// 下载标志，机顶盒启动时检测其值是否为0，如果非0则触发下载
	D_U8				reserved0;//电视机中已占用
	D_U8				reserved1;//电视机中已占用
	D_U8				reserved2;//电视机中已占用

	D_U32				new_loader_ver;
	D_U8				fe_ts_sel; /* 前端选择编号, 对于目标机, 根据编号就可以识别前端设备 */
	D_U8				reserved3;
	D_U8				reserved4;
	D_U8				reserved5;

	struct
	{
		D_FEndFreq freq;
		D_FEndBaud baud;
		D_FEndMod mod;
	}fparam; /* 升级频点信息 */
	D_FEndFreq			lnbfreq1;
	D_FEndFreq			lnbfreq2;
	D_U8				diseqc_type;
	D_U8				diseqc_port;
	D_U8				f22kstate;
	D_U8				tid;
	D_U16				pid;
    	D_U8                		vid_output;
	D_U8				reserved6;
	D_U32               font_addr_in_flash; /* 降成本方案, 有可能把字库放到flash上与loader共用 */
	D_StbParam          stb_param_copy;
    D_U32               crc;
} D_LoaderParam;
typedef struct
{
	D_U16   t2ms;//延时t2
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
    D_U16               size;  // loader结构大小
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

/** @brief SI参数*/
typedef struct {
	struct
	{
		D_FEndFreq freq;
		D_FEndBaud baud;
		D_FEndMod mod;
	}main; /* 只有DVBC需要主频点 */
	D_U8				epg_strategy;
	D_U8				nit_version;		/*保存节目表版本号 */
#ifdef D_CA_SUPPORT_XGCA                    
    D_U8				cdxg_desc_version_num;
    D_U16				cdxg_desc_pid;
#endif
       D_U16     network_id; 
       D_Char     network_name[D_CONF_NETWORK_NAME_LEN + 1];       
	D_U16				reserved;
} D_SIParam;

/** @brief 用户参数*/
typedef struct {
	/*当前节目*/
	D_DBSrvID			curr_srv;
	/*视频设置*/
	D_VidFormat			vid_fmt;
	D_VidOutput			vid_output;
	/*图像参数 */
	D_VidPicParam		vid_param;	/*亮色饱和*/
	D_U8						cur_scanlist;//Reserved1;/* 当前频率组 */
	D_VidPicRatio		vid_ratio;	/*长宽比*/
	/*音频设置*/
	D_AudTrack			aud_track;
	D_U8				aud_mute;
	D_U8				volume;
	D_U8				lang;
	D_U8				transp;
	D_U8				info_time;
	D_U8				Reserved2;
	D_U8				Reserved3;
	D_U8				Reserved4;
	/*时区选择*/
	D_S32				time_offset;
	/*当前喜爱组*/
	D_U8				curr_favor;
	D_U8				passwd_en;			/*是否启用菜单密码*/
	D_U8				Reserved5;
	D_U8				Reserved6;
	D_Bool			passwd_en_power_on;		/*是否启用开机密码*/
	D_Bool			passwd_en_prog_lock;		/*是否启用频道锁密码*/	
	D_U8				passwd_len;
	D_U8				passwd[D_CONF_PASSWORD_LEN  + 1];
	D_U32       channel_change_mode; /*换台时黑屏(0)静帧(1)模式*/
	D_Bool			smart_voice;		/*智能音量标志*/
	D_U32   		stb_startup_time; /*开机次数*/
	D_Char   		favor_name[8][D_CONF_FAVOR_NAME_LEN]; /*喜爱组名称*/
  D_U32       curr_ca; /*当前ca, ca自动识别保存用*/
  D_ID        force_srv; /*开机强制播放节目*/
  D_U8        ca_info[D_CONF_CA_INFO_LEN];   
	   
#ifdef D_CA_SUPPORT_XGCA
	D_U8			user_sort;
#endif
	D_VidInput 	       vid_input;
	D_U8		      balance;
	D_U8				save_type;/*搜索结果保存选择*/

	D_S8				ad_version; /*广告版本号，主要是记录开机LOGO版本号， 初始化为-1*/

} D_UserParam;

#ifdef D_USE_NETWORK
/** @brief 网络设置参数*/
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

/** @brief 机顶盒参数*/
/*若该数据结构的元素有调整，请务必计算该数据结构的大小，并与配置文件platform_cfg.mk中的D_DB_CONFIG_BLOCK_SIZE比较，相应的调整D_DB_CONFIG_BLOCK_SIZE的值，
切勿出现该数据结构的大小大于D_DB_CONFIG_BLOCK_SIZE的情况，否则将出现致命bug*/
typedef struct {
    D_ManufactoryID     manu_id;
	D_StbParam			stb_param;
	D_SIParam			si_param;
	D_UserParam			user_param;
#ifdef D_USE_NETWORK
	D_NetworkParam		net_param;
#endif
} D_StbConfig;

/** @brief 初始化配置信息*/
D_Result p_conf_init (void) D_FUNCPOSTFIT;

/** @brief 恢复为最初配置信息
* @param update	升级标志
*/
D_Result p_conf_restore (D_Bool update) D_FUNCPOSTFIT;

/** @brief 取得视频制式设置*/
D_VidFormat	p_conf_get_vid_fmt (void) D_FUNCPOSTFIT;

/** @brief 设置视频制式设置*/
D_Result p_conf_set_vid_fmt (D_VidFormat fmt) D_FUNCPOSTFIT;


#ifdef D_CA_SUPPORT_XGCA

D_Result p_conf_set_user_sort (D_U8 sort) D_FUNCPOSTFIT;

D_U8 p_conf_get_user_sort(void) D_FUNCPOSTFIT;

#endif

/** @brief 取得声道设置*/
D_AudTrack p_conf_get_aud_track (void) D_FUNCPOSTFIT;

/** @brief 设置声道设置*/
D_Result p_conf_set_aud_track (D_AudTrack track) D_FUNCPOSTFIT;

/** @brief 取得音量设置*/
D_U8 p_conf_get_volume (void) D_FUNCPOSTFIT;

/** @brief 设置声道设置*/
D_Result p_conf_set_volume (D_U8 vol) D_FUNCPOSTFIT;

/** @brief 取得当前服务ID*/
D_DBSrvID p_conf_get_curr_srv (void) D_FUNCPOSTFIT;

/** @brief 设置当前服务ID*/
D_Result p_conf_set_curr_srv (D_DBSrvID id) D_FUNCPOSTFIT;

/** @brief 取得当前服务ID*/
D_DBSrvID p_conf_get_curr_atv_srv (void) D_FUNCPOSTFIT;

/** @brief 设置当前服务ID*/
D_Result p_conf_set_curr_atv_srv (D_DBSrvID id) D_FUNCPOSTFIT;

/** @brief 取得时区设置*/
D_S32 p_conf_get_time_offset (void) D_FUNCPOSTFIT;

/** @brief 设置时区*/
D_Result p_conf_set_time_offset (D_S32 off) D_FUNCPOSTFIT;

/** @brief 取得SI设置*/
D_Result p_conf_get_si_param (D_SIParam *si_param) D_FUNCPOSTFIT;

/** @brief 设置SI设置*/
D_Result p_conf_set_si_param (D_SIParam *si_param) D_FUNCPOSTFIT;

/** @brief 取得Loader参数设置*/
D_Result p_conf_get_loader_param (D_LoaderParam *loader_param) D_FUNCPOSTFIT;

/** @brief 设置Loader参数设置*/
D_Result p_conf_set_loader_param (D_LoaderParam *loader_param) D_FUNCPOSTFIT;

/** @brief 取当前语言*/
D_U8 p_conf_get_lang(void) D_FUNCPOSTFIT;

/** @brief 设置语言*/
D_U8 p_conf_set_lang(D_U8 lang) D_FUNCPOSTFIT;

/** @brief 取透明度*/
D_U8 p_conf_get_transp(void) D_FUNCPOSTFIT;

/** @brief 设置透明度*/
D_U8 p_conf_set_transp(D_U8	transp) D_FUNCPOSTFIT;

/** @brief 取信息条显示时间*/
D_U8 p_conf_get_info_time(void) D_FUNCPOSTFIT;

/** @brief 设置信息条显示时间*/
D_U8 p_conf_set_info_time(D_U8	info_time) D_FUNCPOSTFIT;

/** @brief 取得视频输出*/
D_VidOutput p_conf_get_vid_output (void) D_FUNCPOSTFIT;

/** @brief 设置视频输出*/
D_Result p_conf_set_vid_output (D_VidOutput out) D_FUNCPOSTFIT;

/** @brief 取得静音标志*/
D_Bool p_conf_get_aud_mute (void) D_FUNCPOSTFIT;

/** @brief 设置静音标志*/
D_Result p_conf_set_aud_mute (D_Bool mute) D_FUNCPOSTFIT;

/** @brief 设置视频参数 */
D_Result p_conf_set_vid_pic_param (D_VidPicParam *param)D_FUNCPOSTFIT;

/** @brief 获得视频参数 */
D_Result p_conf_get_vid_pic_param (D_VidPicParam *param)D_FUNCPOSTFIT;

/** @brief 设置视频宽高比例 */
D_Result p_conf_set_vid_pic_ratio (D_VidPicRatio ratio)D_FUNCPOSTFIT;

/** @brief 获得视频宽高比例 */
D_VidPicRatio p_conf_get_vid_pic_ratio (void)D_FUNCPOSTFIT;

/** @brief 获得菜单密码是否使能*/
D_Bool p_conf_get_passwd_en (void) D_FUNCPOSTFIT;

/** @brief 设置菜单密码是否使能*/
D_Result p_conf_set_passwd_en (D_Bool en) D_FUNCPOSTFIT;

/** @brief 获得开机密码是否使能*/
D_Bool p_conf_get_poweron_passwd_en (void) D_FUNCPOSTFIT;

/** @brief 设置开机密码是否使能*/
D_Result p_conf_set_poweron_passwd_en (D_Bool en) D_FUNCPOSTFIT;

/** @brief 获得节目锁密码是否使能*/
D_Bool p_conf_get_prog_passwd_en (void) D_FUNCPOSTFIT;

/** @brief 设置节目锁密码是否使能*/
D_Result p_conf_set_prog_passwd_en (D_Bool en) D_FUNCPOSTFIT;

/** @brief 获得密码长度*/
D_U8 p_conf_get_passwd_len (void) D_FUNCPOSTFIT;

/** @brief 获得密码*/
D_Result p_conf_get_passwd (D_Char *pass) D_FUNCPOSTFIT;

/** @brief 设置密码*/
D_Result p_conf_set_passwd (D_Char *pass) D_FUNCPOSTFIT;

/** @brief 检查密码设置
返回值: 	0  密码错误
			1 密码正确，与设置的密码相同
			2 密码正确，与超级密码相同	
*/
D_U8 p_conf_check_passwd (D_Char *pass) D_FUNCPOSTFIT;


/** @brief 得到当前换台黑屏(0)  静帧(1) 模式*/
D_U8 p_conf_get_channel_change_mode(void) D_FUNCPOSTFIT;

/** @brief 设置当前换台黑屏(0)  静帧(1) 模式*/
D_Result p_conf_set_channel_change_mode(D_U8 mode) D_FUNCPOSTFIT;

/** @brief 取得开机的次数*/
D_U32 p_conf_get_stb_startup_time(void) D_FUNCPOSTFIT;

/** @brief 开机的次数加1*/
D_Result p_conf_add_stb_startup_time(void) D_FUNCPOSTFIT;

#ifdef D_USE_NETWORK
/** @brief 获得网络参数*/
D_Result p_conf_get_network_param(D_NetworkParam *net_param);

/** @brief 设置网络参数*/
D_Result p_conf_set_network_param(D_NetworkParam *net_param);
#endif

/** @brief 取得喜爱组名称
* @param[in] num 喜爱组编号，目前只支持8个喜爱组，编号为0~7
* @param[out] name 喜爱组名称字符串指针（必须为该指针分配了足够空间才能使用）
* @retval D_ERR	获取失败
* @retval D_OK	获取成功
*/
D_Result p_conf_get_favor_name(D_U8 num, D_Char* name) D_FUNCPOSTFIT;

/** @brief 设置喜爱组名称
* @param[in] num 喜爱组编号，目前只支持8个喜爱组，编号为0~7
* @param[in] name 喜爱组名称字符串指针
* @retval D_ERR	设置失败
* @retval D_OK	设置成功
*/
D_Result p_conf_set_favor_name(D_U8 num, D_Char* name) D_FUNCPOSTFIT;

/** @brief 取得当前CA*/
D_U32 p_conf_get_curr_ca(void) D_FUNCPOSTFIT;

/** @brief 设置当前CA*/
D_Result p_conf_set_curr_ca(D_U32 curr_ca) D_FUNCPOSTFIT;

/** @brief 取得记录的服务ID*/
D_DBSrvID p_conf_get_force_srv (void) D_FUNCPOSTFIT;

/** @brief 设置当前服务ID*/
D_Result p_conf_set_force_srv (D_DBSrvID id) D_FUNCPOSTFIT;

/** @brief 取得CA模块存储的相关信息
* @param[out] buf CA相关信息存放区指针（必须为该指针分配了足够空间才能使用）
* @retval D_ERR	获取失败
* @retval D_OK	获取成功
*/
D_Result
p_conf_get_ca_related_info(D_U8* buf) D_FUNCPOSTFIT;

/** @brief 设置CA模块存储的相关信息
* @param[out] buf CA相关信息存放区指针
* @retval D_ERR	设置失败
* @retval D_OK	设置成功
*/
D_Result
p_conf_set_ca_related_info(D_U8* buf) D_FUNCPOSTFIT;

/** @brief 取得搜索设置*/
D_U8
p_conf_get_scan_config (void) D_FUNCPOSTFIT;

/** @brief 设置搜索设置*/
D_Result
p_conf_set_scan_config (D_U8 cable_en) D_FUNCPOSTFIT;
/** @brief 获得频率组序号*/
D_U8 
p_conf_get_scan_list_num (void) D_FUNCPOSTFIT;
/** @brief 设置频率组序号*/
D_Result 
p_conf_set_scan_list_num (D_U8 num) D_FUNCPOSTFIT;
/** @brief 取得视频输入*/
D_VidInput
p_conf_get_vid_input (void) D_FUNCPOSTFIT;
/** @brief 设置视频输入*/
D_Result
p_conf_set_vid_input (D_VidInput input) D_FUNCPOSTFIT;

/** @brief 取得音量设置*/
D_U8 p_conf_get_balance (void) D_FUNCPOSTFIT;

/** @brief 设置声道设置*/
D_Result p_conf_set_balance (D_U8 val) D_FUNCPOSTFIT;

D_Result p_conf_restore_eep (void) D_FUNCPOSTFIT;
D_U8 p_conf_get_save_type() D_FUNCPOSTFIT;

/** @brief 取得Loader参数设置*/
D_Result p_conf_get_panel_param (D_PanelParam *panel_param) D_FUNCPOSTFIT;

/** @brief 设置Loader参数设置*/
D_Result p_conf_set_panel_param (D_PanelParam *panel_param) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif

