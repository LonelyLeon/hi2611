/** @file
* @brief �û��������ݼ���
* @author �
* @date 2013-07-25 �: �����ļ�
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


/** @brief ������õ�TAG���� */
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
#define CUSTOM_CONFIG_TAG_SCAN_DISABLE_FREQ_LIST      0x35 /*����ʱ���ε�Ƶ���б�*/
#define CUSTOM_CONFIG_TAG_EPG_SCAN_CONFIG      0x36 /* EPG��������*/
#define CUSTOM_CONFIG_TAG_PANEL_CONFIG      0x37 /* ����������*/

#define D_CUSTOM_CONF_MANUF_NAME_LEN (32)
#define D_CUSTOM_CONF_NETWORK_NAME_LEN (32)


/** @brief ��������ID*/
typedef D_U32 D_ManufactoryID;

/** @brief �û�ϵͳ����, Ŀǰ���� */
typedef struct
{
    D_ManufactoryID manu_id;
	D_U8 hw_id;
	D_U8 hw_major;
	D_U16 hw_minor;
    D_Char manuf_name[D_CUSTOM_CONF_MANUF_NAME_LEN + 1]; /*������*/
}P_CustomSysConfig;

typedef struct
{
    D_U16 source_code;
    D_KeyCode mapped_key;
}P_CustomIrKey;

/** @brief �û�ң������ */
typedef struct
{
    D_U8 guid_code;
    D_U16 machine_code;
    P_CustomIrKey *keys;
}P_CustomIrConfig;

/** @brief �û�ǰ������� */
typedef struct
{
    D_GPIO_PortBit clock;
    D_GPIO_PortBit data;
    P_CustomIrKey *keys;
}P_CustomFpConfig;

/** @brief �û����tuner���� */
typedef struct
{
    DemodType_t type;
    D_U8 demo_i2c_addr; //Ƭ�ڽ��Ϊ����ֵ,����Ҫ����
    D_U32 demo_xtalFreqKHz;//Ƭ�ڽ��Ϊ����ֵ,����Ҫ����
    TS_SELECT_CONSTANT ts_sel;//Ƭ�ڽ��оƬ�ڲ�����ΪTS0
    D_U8 i2c_no;//Ƭ�ڽ��оƬ,��I2C�������ø�Ƶͷ
    D_GPIO_PortBit reset;
    D_GPIO_PortBit sw_13_18v;
    D_GPIO_PortBit lnb;
}P_CustomDemodConfig;

/** @brief �û���������, ���� */
typedef struct
{
    D_U32 dummy;
}P_CustomUartConfig;

/** @brief �û�Smartcard���� */
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

/** @brief �û�I2C���� */
typedef struct
{
    D_GPIO_PortBit clock;
    D_GPIO_PortBit data;
}P_CustomIICConfig;

/** @brief �û�E2P����, ���� */
typedef struct
{
    D_U32 dummy;
}P_CustomE2PConfig;

/** @brief �û���Ƶ����, ���� */
typedef struct
{
    D_GPIO_PortBit audio_mute;//���ڿ�����Ƶ���˷��Ƿ���
    D_GPIO_PortBit audio_broadcast_mute;//���ڿ���Ӧ���㲥�Ƿ���
    D_U8 audio_spdif_en;//�Ƿ�֧��spdif
    D_U8 dac_mode;
}P_CustomaudioConfig;

/** @brief �û�����Ӳ������, ���� */
typedef struct
{
    D_U32 dummy;
}P_CustomNetConfig;

/** @brief �û�LCD����, ���� */
typedef struct
{
    D_U32 dummy;
}P_CustomLcdConfig;

#define P_SIMON_PAT_PMT_CHNAGED_EN  	(1 << 31)    /**< ����PMT pid ����ƵPID��� */
#define P_SIMON_PAT_PMT_CHANGED_NOTIFY  (1 << 30) /**< PMT pid�ı�ʱ�Ƿ�֪ͨӦ��Ƶ���ı� */
#define P_SIMON_PAT_SERVICE_CHANGED_EN  (1 << 29) /**< ����service��Ŀ��� */
#define P_SIMON_PAT_NONE_VER        	(1 << 28)    /**< PAT�ް汾���ģʽ */

#define P_SIMON_CAT_EN              (1 << 27)    /**< ����CAT��� */
#define P_SIMON_CAT_NONE_VER        (1 << 26)    /**< CAT�ް汾���ģʽ */

#define P_SIMON_SDT_NAME_EN         (1 << 25)    /**< SDT������ؽ�Ŀ�� */
#define P_SIMON_SDT_CA_FREEMODE_EN  (1 << 24)    /**< SDT������ؼ��ű�־ */
#define P_SIMON_SDT_NONE_VER        (1 << 23)    /**< SDT�ް汾���ģʽ */

#define P_SIMON_NIT_EN              (1 << 22)    /**< ����NIT��� */
#define P_SIMON_NIT_MAIN_FREQ       (1 << 21)    /**< �Ƿ�ֻ�����Ƶ���NIT */
#define P_SIMON_NIT_NONE_VER        (1 << 20)    /**< NIT�ް汾���ģʽ */
#define P_SIMON_NIT_VER_CHANGED_NOTIFY (1 << 19) /**< NIT�汾�仯�Ƿ�֪ͨӦ��Ƶ���ı� */
#define P_SIMON_NIT_NETWORK_ID        (1 << 18)    /**< NETWORK_ID���*/
#define P_SIMON_NIT_NETWORK_NAME (1 << 17) /**< NETWORK_NAME���*/

#define P_SIMON_UMT_EN              (1 << 16)    /**< ����UMT��� */

//#define others  bit15~bit0



/** @brief �û�SI������� */
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

/** @brief �û���������, ���� */
typedef struct
{
    D_U32 dummy;
}P_CustomUpgradeConfig;


/** @brief �û�������������*/
typedef struct
{
    D_Bool enable;
}P_CustomVolCompensationConfig;


/** @brief �û�Ƶ�������������
����ʽ: 
	0, ������
	1, Ƶ��,Sort
	2, ServiceID,Sort
	3, �߼�Ƶ����,Sort
	4, �շ�/���,Sort
	5, ����ĸ,Sort
	6, ����,Sort

����ɾ����ʽ:
�Զ�
	0 , �ѵ���Ŀ��ɾ�����н�Ŀ
	1 , �����Ƿ��ѵ���ɾ�����н�Ŀ
	2 , 
�ֶ�
	0 , �ѵ���Ŀ��ɾ����Ƶ�������н�Ŀ
	1 , �����Ƿ��ѵ���ɾ����Ƶ�������н�Ŀ
	2 ,

�����˳��Ƿ񱣴�:
	0 , ������
	1 , ����
 */
typedef struct
{
	D_U8 	volume;		/*����ʱĬ������( <= 32 )*/
	D_U8 	track;		/*����ʱĬ������(��D_AudTrack�����Ӧ)*/
	D_Bool	use_lcn;		/*�Ƿ�ʹ��si������߼�Ƶ������Ϊ��Ŀ��Ƶ����*/
	D_U8 	caflag;		/*���ܱ�־ѡ��*/    
	D_U8	adelete;		/*�Զ�����ɾ����ʽ*/
	D_U8	asort;		/*�Զ������������ʽ*/
	D_U8	mdelete;	/*�ֶ�����ɾ����ʽ*/
	D_U8	msort;		/*�ֶ������������ʽ*/
    
    D_U8	full_mode;		/*ȫƵ������ģʽ: 0����׼Ƶ�ʱ�������1:����Ƶ�ʱ�*/
       D_FEndFreq   start_freq;/*ȫƵ��������ʼƵ��(MHz)*/
       D_FEndFreq   end_freq;/*ȫƵ����������Ƶ��(MHz)*/
       D_FEndBandWitch   band;/*ȫƵ����������(MHz)*/
	D_U8    multi_maintp;	   /*�Զ������Ƿ�ʹ�ö����Ƶ��������ʽ*/
	D_U8    exit_to_save;	/*�����˳��Ƿ񱣴�*/
}P_CustomScanConfig;


/** @brief �û������������*/
#define D_CUSTOM_CONF_PASSWORD_LEN (6)
typedef struct
{
	D_U8 	pwd_len;		/*�������볤��<= D_CUSTOM_CONF_PASSWORD_LEN*/
	D_Bool	power_on;		/*�Ƿ����ÿ�������*/
	D_Bool	stbmenu;		/*�Ƿ����ò˵�����*/
	D_Bool	prog_lock;		/*�Ƿ�����Ƶ��������*/
	D_Char 	def_pwd[D_CUSTOM_CONF_PASSWORD_LEN + 1];		/*Ĭ�ϳ�ʼ����*/
	D_Char 	super_pwd[D_CUSTOM_CONF_PASSWORD_LEN + 1];	/*������������*/
}P_CustomPasswordConfig;


/** @brief �����������*/
typedef struct
{
    D_Bool  scan_enable;
    D_U8 	scan_mode;		/*0 : �Զ������� 1: ȫƵ�������� 2: Ԥ��Ƶ������*/
}P_CustomPowerConfig;


/** @brief ϵͳ����Ĭ������*/
typedef struct
{
	D_U8 change_mode;     /*��̨��ʽ��0 : ������ 1: ��֡*/
 	D_U8 def_language;     /*���ԣ�0 : Ӣ�ģ� 1: ���� */
       D_U8 track;                  /*������0 : ���� 1: ��2: ��*/
       D_U8 smart_voice;       /*����������0 : �رգ� 1: ����*/
       D_U8 def_voice;       /*Ĭ��������0-32*/   
       D_U8 vol_compensate;  /*����������0 : �رգ� 1: ����*/
       D_U8 chan_save;  /*��Ŀ���淽ʽ��0 : ȫ�����棬 1: ��������Ž�Ŀ, 2:ֻ������Ž�Ŀ*/
}P_CustomSysSetupConfig;

/** @brief ��Ƶ��Ĭ������*/
typedef struct
{
    D_FEndFreq freq;
    D_FEndBaud baud;
    D_FEndMod mod;
    D_U16    network_id; /*���� ID*/
    D_Char network_name[D_CUSTOM_CONF_NETWORK_NAME_LEN + 1]; /*������*/
    D_U32 software_version; /* ����汾�� */
}P_CustomMainConfig;
/** @brief ����������*/
typedef struct
{
    D_U8    decodetype; /*frame-4��frame-9��frame-20*/
}P_CustomDecodeTypeconfig;
/** @brief ��̨ͬ������*/
typedef struct
{
    D_U8  wait_sync_type; /*0��ͬ����ǰһ����Ŀ��1��ͬ���ں�һ����Ŀ*/
}P_CustomSwitchPlayconfig;


/** @brief ��Ŀ���´���ʽ�������*/
typedef struct
{
    D_Bool  scan_enable;
    D_U8 	deal_mode;		/*0 : �������� 1: ������ʾ��Ϣ�� 2: ֱ������*/
    D_U8 	scan_mode;		/*0 : �Զ������� 1: ȫƵ�������� 2: Ԥ��Ƶ������*/
}P_CustomChanUpdateConfig;

/** @brief ��Ŀ�仯����ʽ�������*/
typedef struct
{
    D_Bool  scan_enable;
    D_U8 	deal_mode;		/*0 : �������� 1: ������ʾ��Ϣ�� 2: ֱ������*/
}P_CustomChanChageConfig;

/** @brief Epg�������� */
typedef struct
{
    D_U32      scan_mode; /*0 : ȫ��Ƶ������epg�� 1: ��Ƶ������epg�� 2: �̶�Ƶ������epg*/
    D_FEndFreq freq;
    D_FEndBaud baud;
    D_FEndMod mod;
    D_U32 timeout;
    D_U32 reserved;
}P_CustomEpgScanConfig;

/** @brief �û����ýṹ */
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

/** @brief �����û���������
* @param ��
* @return ��
*/
void p_custom_config_load(void) D_FUNCPOSTFIT;

/** @brief ��ӡ�û���������
* @param ��
* @return ��
*/
void p_custom_config_dump(void) D_FUNCPOSTFIT;

/** @brief ���app������flash��ƫ�Ƶ�ַ
* @param ��
* @return app������flash��ƫ�Ƶ�ַ
*/
D_U32 p_custom_config_get_app_offset(void) D_FUNCPOSTFIT;

/** @brief �ṩ���ⲿʹ�õ��û�����,һ�������ʹ�� */
extern P_CustomConfig g_custom_config;

#define CUSTOM_CONFIG   g_custom_config

#ifdef  __cplusplus
}
#endif
#endif
