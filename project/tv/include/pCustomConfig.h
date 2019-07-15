/** @file
* @brief 用户配置数据加载
* @author 李臣
* @date 2013-07-25 李臣: 建立文件
*/
#ifndef __P_CUSTOM_CONFIG_H
#define __P_CUSTOM_CONFIG_H
#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dFP.h"
#include "dIO.h"
#include "dFEnd.h"
#include "dDBase.h"
#include "dTS.h"


/** @brief 软件配置的TAG定义 */
#define CUSTOM_CONFIG_TAG_DVBC_MAIN     0x20
#define CUSTOM_CONFIG_TAG_SYS_DEFAULT      0x21
#define CUSTOM_CONFIG_TAG_UPGRADE       0x22
#define CUSTOM_CONFIG_TAG_SI_POWER_ON       0x23
#define CUSTOM_CONFIG_TAG_SI_MON        0x24
#define CUSTOM_CONFIG_CHANNEL_SCAN      0x25
#define CUSTOM_CONFIG_PASSWORD          0x26
#define CUSTOM_CONFIG_MACHINE_START     0x27
#define CUSTOM_CONFIG_DECODE_SWITCH     0x28
#define CUSTOM_CONFIG_SWITCHPLAY        0x29
#define CUSTOM_CONFIG_SEARCH_LIST       0x2a
#define CUSTOM_CONFIG_CHANUPDATE_MODE   0x2b
#define CUSTOM_CONFIG_CHANCHAGE_MODE    0x2c
#define CUSTOM_CONFIG_FREQ_GROUP    	0x2d
#define CUSTOM_CONFIG_TAG_IR3        0x30
#define CUSTOM_CONFIG_TAG_RESTORE       0x31
#define CUSTOM_CONF_CAOSD_SET       0x32
#define CUSTOM_CONF_FACTORY_SET       0x33
#define CUSTOM_CONFIG_TAG_KEY_TRANSFER       0x34
#define CUSTOM_CONFIG_TAG_SCAN_DISABLE_FREQ_LIST      0x35 /*搜索时屏蔽的频点列表*/
#define CUSTOM_CONFIG_TAG_EPG_SCAN_CONFIG      0x36 /* EPG搜索配置*/
#define CUSTOM_CONFIG_TAG_PANEL_CONFIG      0x37 /* 屏参数配置*/

#define D_CUSTOM_CONF_MANUF_NAME_LEN (32)
#define D_CUSTOM_CONF_NETWORK_NAME_LEN (32)


/** @brief 生产厂商ID*/
typedef D_U32 D_ManufactoryID;

/** @brief 用户系统配置, 目前保留 */
typedef struct
{
    D_ManufactoryID manu_id;
	D_U8 hw_id;
	D_U8 hw_major;
	D_U16 hw_minor;
    D_Char manuf_name[D_CUSTOM_CONF_MANUF_NAME_LEN + 1]; /*网络名*/
}P_CustomSysConfig;

typedef struct
{
    D_U16 source_code;
    D_KeyCode mapped_key;
}P_CustomIrKey;

/** @brief 用户遥控配置 */
typedef struct
{
    D_U8 guid_code;
    D_U16 machine_code;
    P_CustomIrKey *keys;
}P_CustomIrConfig;

/** @brief 用户前面板配置 */
typedef struct
{
    D_GPIO_PortBit clock;
    D_GPIO_PortBit data;
    P_CustomIrKey *keys;
}P_CustomFpConfig;

/** @brief 用户解调tuner配置 */
typedef struct
{
    DemodType_t type;
    D_U8 demo_i2c_addr; //片内解调为任意值,不需要设置
    D_U32 demo_xtalFreqKHz;//片内解调为任意值,不需要设置
    TS_SELECT_CONSTANT ts_sel;//片内解调芯片内部设置为TS0
    D_U8 i2c_no;//片内解调芯片,此I2C用于设置高频头
    D_GPIO_PortBit reset;
    D_GPIO_PortBit sw_13_18v;
    D_GPIO_PortBit lnb;
}P_CustomDemodConfig;

/** @brief 用户串口配置, 保留 */
typedef struct
{
    D_U32 dummy;
}P_CustomUartConfig;

/** @brief 用户Smartcard配置 */
typedef struct
{
    D_GPIO_PortBit detect;
    D_GPIO_PortBit reset;
    D_GPIO_PortBit vcc_cmd;
    D_Bool open_close;
    D_U8 uart_no;
    D_U8 pwm_sel;
    D_GPIO_PortBit sw_3_5v;
}P_CustomSCConfig;

/** @brief 用户I2C配置 */
typedef struct
{
    D_GPIO_PortBit clock;
    D_GPIO_PortBit data;
}P_CustomIICConfig;

/** @brief 用户E2P配置, 保留 */
typedef struct
{
    D_U32 dummy;
}P_CustomE2PConfig;

/** @brief 用户音频配置, 保留 */
typedef struct
{
    D_GPIO_PortBit audio_mute;//用于控制音频的运放是否工作
    D_GPIO_PortBit audio_broadcast_mute;//用于控制应急广播是否工作
    D_U8 audio_spdif_en;//是否支持spdif
    D_U8 dac_mode;
}P_CustomaudioConfig;

/** @brief 用户网络硬件配置, 保留 */
typedef struct
{
    D_U32 dummy;
}P_CustomNetConfig;

/** @brief 用户LCD配置, 保留 */
typedef struct
{
    D_U32 dummy;
}P_CustomLcdConfig;

#define P_SIMON_PAT_PMT_CHNAGED_EN  	(1 << 31)    /**< 开启PMT pid 音视频PID监控 */
#define P_SIMON_PAT_PMT_CHANGED_NOTIFY  (1 << 30) /**< PMT pid改变时是否通知应用频道改变 */
#define P_SIMON_PAT_SERVICE_CHANGED_EN  (1 << 29) /**< 开启service数目监控 */
#define P_SIMON_PAT_NONE_VER        	(1 << 28)    /**< PAT无版本监控模式 */

#define P_SIMON_CAT_EN              (1 << 27)    /**< 开启CAT监控 */
#define P_SIMON_CAT_NONE_VER        (1 << 26)    /**< CAT无版本监控模式 */

#define P_SIMON_SDT_NAME_EN         (1 << 25)    /**< SDT开启监控节目名 */
#define P_SIMON_SDT_CA_FREEMODE_EN  (1 << 24)    /**< SDT开启监控加扰标志 */
#define P_SIMON_SDT_NONE_VER        (1 << 23)    /**< SDT无版本监控模式 */

#define P_SIMON_NIT_EN              (1 << 22)    /**< 开启NIT监控 */
#define P_SIMON_NIT_MAIN_FREQ       (1 << 21)    /**< 是否只监控主频点的NIT */
#define P_SIMON_NIT_NONE_VER        (1 << 20)    /**< NIT无版本监控模式 */
#define P_SIMON_NIT_VER_CHANGED_NOTIFY (1 << 19) /**< NIT版本变化是否通知应用频道改变 */
#define P_SIMON_NIT_NETWORK_ID        (1 << 18)    /**< NETWORK_ID监控*/
#define P_SIMON_NIT_NETWORK_NAME (1 << 17) /**< NETWORK_NAME监控*/

#define P_SIMON_UMT_EN              (1 << 16)    /**< 开启UMT监控 */

//#define others  bit15~bit0



/** @brief 用户SI监控配置 */
typedef struct
{
    D_U32 flag;

    struct
    {
        D_Bool enable;
        D_Bool use_main;  
        D_FEndFreq freq;
        D_FEndBaud baud;
        D_FEndMod mod;
        D_U32 flag;
        D_U32 timeout;
    }power_on;
    D_U16 reserved;
}P_CustomSIMonConfig;

/** @brief 用户升级配置, 保留 */
typedef struct
{
    D_U32 dummy;
}P_CustomUpgradeConfig;


/** @brief 用户音量补偿配置*/
typedef struct
{
    D_Bool enable;
}P_CustomVolCompensationConfig;


/** @brief 用户频道搜索相关配置
排序方式: 
	0, 不排序
	1, 频点,Sort
	2, ServiceID,Sort
	3, 逻辑频道号,Sort
	4, 收费/免费,Sort
	5, 首字母,Sort
	6, 其它,Sort

搜索删除方式:
自动
	0 , 搜到节目后删除所有节目
	1 , 不管是否搜到，删除所有节目
	2 , 
手动
	0 , 搜到节目后删除该频点下所有节目
	1 , 不管是否搜到，删除该频点下所有节目
	2 ,

搜索退出是否保存:
	0 , 不保存
	1 , 保存
 */
typedef struct
{
	D_U8 	volume;		/*搜索时默认音量( <= 32 )*/
	D_U8 	track;		/*搜索时默认声道(与D_AudTrack定义对应)*/
	D_Bool	use_lcn;		/*是否使用si表里的逻辑频道号作为节目的频道号*/
	D_U8 	caflag;		/*加密标志选择*/    
	D_U8	adelete;		/*自动搜索删除方式*/
	D_U8	asort;		/*自动搜索结果排序方式*/
	D_U8	mdelete;	/*手动搜索删除方式*/
	D_U8	msort;		/*手动搜索结果排序方式*/
    
    D_U8	full_mode;		/*全频段搜索模式: 0按标准频率表搜索，1:不按频率表*/
       D_FEndFreq   start_freq;/*全频段搜索起始频率(MHz)*/
       D_FEndFreq   end_freq;/*全频段搜索结束频率(MHz)*/
       D_FEndBandWitch   band;/*全频段搜索带宽(MHz)*/
	D_U8    multi_maintp;	   /*自动搜索是否使用多个主频点搜索方式*/
	D_U8    exit_to_save;	/*搜索退出是否保存*/
}P_CustomScanConfig;


/** @brief 用户密码相关配置*/
#define D_CUSTOM_CONF_PASSWORD_LEN (6)
typedef struct
{
	D_U8 	pwd_len;		/*配置密码长度<= D_CUSTOM_CONF_PASSWORD_LEN*/
	D_Bool	power_on;		/*是否启用开机密码*/
	D_Bool	stbmenu;		/*是否启用菜单密码*/
	D_Bool	prog_lock;		/*是否启用频道锁密码*/
	D_Char 	def_pwd[D_CUSTOM_CONF_PASSWORD_LEN + 1];		/*默认初始密码*/
	D_Char 	super_pwd[D_CUSTOM_CONF_PASSWORD_LEN + 1];	/*超级密码设置*/
}P_CustomPasswordConfig;


/** @brief 开机相关配置*/
typedef struct
{
    D_Bool  scan_enable;
    D_U8 	scan_mode;		/*0 : 自动搜索， 1: 全频段搜索， 2: 预置频点搜索*/
}P_CustomPowerConfig;


/** @brief 系统设置默认配置*/
typedef struct
{
	D_U8 change_mode;     /*换台方式，0 : 黑屏， 1: 静帧*/
 	D_U8 def_language;     /*语言，0 : 英文， 1: 中文 */
       D_U8 track;                  /*声道，0 : 立， 1: 左，2: 右*/
       D_U8 smart_voice;       /*智能音量，0 : 关闭， 1: 开启*/
       D_U8 def_voice;       /*默认音量，0-32*/   
       D_U8 vol_compensate;  /*音量补偿，0 : 关闭， 1: 开启*/
       D_U8 chan_save;  /*节目保存方式，0 : 全部保存， 1: 不保存加扰节目, 2:只保存加扰节目*/
}P_CustomSysSetupConfig;

/** @brief 主频点默认配置*/
typedef struct
{
    D_FEndFreq freq;
    D_FEndBaud baud;
    D_FEndMod mod;
    D_U16    network_id; /*网络 ID*/
    D_Char network_name[D_CUSTOM_CONF_NETWORK_NAME_LEN + 1]; /*网络名*/
    D_U32 software_version; /* 软件版本号 */
}P_CustomMainConfig;
/** @brief 解码宽度设置*/
typedef struct
{
    D_U8    decodetype; /*frame-4，frame-9，frame-20*/
}P_CustomDecodeTypeconfig;
/** @brief 切台同步播放*/
typedef struct
{
    D_U8  wait_sync_type; /*0等同步在前一个节目，1等同步在后一个节目*/
}P_CustomSwitchPlayconfig;


/** @brief 节目更新处理方式相关配置*/
typedef struct
{
    D_Bool  scan_enable;
    D_U8 	deal_mode;		/*0 : 不做处理， 1: 弹出提示信息， 2: 直接搜索*/
    D_U8 	scan_mode;		/*0 : 自动搜索， 1: 全频段搜索， 2: 预置频点搜索*/
}P_CustomChanUpdateConfig;

/** @brief 节目变化处理方式相关配置*/
typedef struct
{
    D_Bool  scan_enable;
    D_U8 	deal_mode;		/*0 : 不做处理， 1: 弹出提示信息， 2: 直接搜索*/
}P_CustomChanChageConfig;

/** @brief Epg搜索配置 */
typedef struct
{
    D_U32      scan_mode; /*0 : 全部频点搜索epg， 1: 主频点搜索epg， 2: 固定频点搜索epg*/
    D_FEndFreq freq;
    D_FEndBaud baud;
    D_FEndMod mod;
    D_U32 timeout;
    D_U32 reserved;
}P_CustomEpgScanConfig;

/** @brief 用户配置结构 */
typedef struct
{
    P_CustomSysConfig sys;
    P_CustomIrConfig ir[4];
    P_CustomFpConfig fp;
    P_CustomDemodConfig demod[2];
    P_CustomUartConfig uart;
    P_CustomSCConfig sc;
    P_CustomIICConfig i2c[4];
    P_CustomE2PConfig e2p;
    P_CustomNetConfig net;
    P_CustomLcdConfig lcd;
    P_CustomaudioConfig audio;
    P_CustomMainConfig dvbc_main;
    P_CustomSysSetupConfig sys_setup;
    P_CustomSIMonConfig si_mon;
    P_CustomUpgradeConfig upgrade;
	P_CustomScanConfig scan;
	P_CustomPasswordConfig password;
	P_CustomPowerConfig  power_on;
    P_CustomDecodeTypeconfig decode_switch;
    P_CustomSwitchPlayconfig switch_play;
	P_CustomChanUpdateConfig  chan_update;
	P_CustomChanChageConfig   chan_change;
    P_CustomEpgScanConfig epg;
}P_CustomConfig;

/** @brief 加载用户配置数据
* @param 无
* @return 无
*/
void p_custom_config_load(void) D_FUNCPOSTFIT;

/** @brief 打印用户配置数据
* @param 无
* @return 无
*/
void p_custom_config_dump(void) D_FUNCPOSTFIT;

/** @brief 获得app镜像在flash中偏移地址
* @param 无
* @return app镜像在flash中偏移地址
*/
D_U32 p_custom_config_get_app_offset(void) D_FUNCPOSTFIT;

/** @brief 提供给外部使用的用户配置,一个特殊的使用 */
extern P_CustomConfig g_custom_config;

#define CUSTOM_CONFIG   g_custom_config

#ifdef  __cplusplus
}
#endif
#endif
