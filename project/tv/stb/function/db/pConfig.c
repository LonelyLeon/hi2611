/**@defgroup db 数据库定制应用
*@{*/
/** @file
* @brief    配置信息模块
* @author 龚克
* @date 2005-9-7 龚克: 建立文件
* @date 2013-03-19 lc: 统一平台, 代码整理
* @date 2013-04-22 lwf,sunzy: 统一平台, 代码整理
*/
#include <stdio.h>
#include <string.h>
#include "dDBaseInternal.h"
#include "dConfigFile.h"
#include "dTime.h"
#include "pConfig.h"
#include "dNVPart.h"
#include "dMutex.h"
#include "dSys.h"
#include "dMem.h"
#include "dDebug.h"
#include "dEEPRom.h"
#include "dCrc.h"


/*默认ca*/
#define CA_VAL D_CA_SUPPORT_DEF

static D_StbConfig *config;
#ifdef D_SUPPORT_EEPROM
static D_Bool loaded = D_FALSE;
#endif
static D_U8 config_block_id;

/** @brief 定义数据区*/
extern D_DBBlock config_blk;

#define LOADER_PARAM_OFFSET_IN_EEPROM       0
#define PANEL_PARAM_OFFSET_IN_EEPROM       512

#define LOCK()      D_DB_LOCK()
#define UNLOCK()    D_DB_UNLOCK()
#define DIRTY()     D_BLOCK_DIRTY(&config_blk)
#define CONFIG      (*config)

static D_StbConfig
def_config =
{
    /*厂家id, 只用于检查config块数据是否初始化*/
    D_MANUFACTORY_ID,
    /*STB param*/
    {
        D_SOFTWARE_MAJOR_VER,
        D_SOFTWARE_MINOR_VER,
        D_SOFTWARE_BUILD_NUM,
        {"1000000019800312"},
    },
    /*SI param*/
    {
        {
            610, 6875, D_FEND_QAM64,
        },
        0,//复用为节目搜索模式dvbc/dtmb
        0xFF,
#ifdef D_CA_SUPPORT_XGCA
        0xFF,
        0xFFFF,
#endif
        0xFFFF,
        {0},
        0,
    },
    /*User param*/
    {
        -1,
            D_VID_FMT_768P_50,
            D_VID_OUTPUT_YPBPR,
        {50, 50, 50},
        0,
        D_VidRatio_TYPE_Auto,/*开机默认自动*/
        D_AUD_STEREO,
        D_FALSE,
        20,
        D_CONF_DEF_LANG,
        1,
        D_CONF_MAX_INFO_TIME,
        0, 0, 0,
        8 * 3600,
        0,
        1,
        0, 0,
        0,
        0,
        4,
        {D_CONF_DEF_PASSWORD},
        D_TRUE,
        0,
        0,
        {"FAV0", "FAV1", "FAV2", "FAV3", "FAV4", "FAV5", "FAV6", "FAV7"},
        CA_VAL,
        -1,/*强制播放节目*/
        {
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, \
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, \
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, \
            0xFF, 0xFF
        },   /*存放CA模块保存的信息*/
#ifdef D_CA_SUPPORT_XGCA
        0,
#endif
        D_VID_IUTPUT_TV,//输入源
        50,
        0,
        -1,   /* 广告版本号，主要是记录开机LOGO版本号， 初始化为-1 */
    },
#ifdef D_USE_NETWORK
    /*Network param*/
    {
        0,
        0xFFFFFF00,
        0,
        0,
        0,
        {'\0'},
        {0x00, 0x80, 0xE2, 0x11, 0x1A, 0x53},
        0,
        0,
        {'\0'},
        {'\0'},
        {'\0'},
        {'\0'},
        1,
        0,
    },
#endif
};

static D_LoaderParam def_loader_param =
    /*Loader param*/
{
    0,
    1,
    0,
    0,//reserved0;//电视机中已占用
    0,
    0,
    0x01000001,
    0,
    0,
    0,
    0,
    {
        474, 6875, D_FEND_QAM64,
    },
    5150,
    9750,
    D_DISEQC_TYPE_10,
    D_PORT_OFF,
    D_F22KOff,
    0x83,
    0x1BBC,
    (D_U8)D_VID_OUTPUT_AV1,
    0,
    0,
    {0,},
    0xFFFFFFFF,
};

static D_PanelParam def_panel_param =
    /*panel param*/
{
    0,
    {0,},//screenparam;
    {20, 300, 400, 30, 0, 0,}, //lvds_sequence
    {0,},//lvds_init_param;
    {0,},//tven_para;
    0,
    {0,},//tcon_param;
    {0, 0,}, //D_SPModel_Param;
    0xFFFFFFFF,
};

static void conf_save_in_rec(D_U32 offset, D_U32 data_size)
{
    if(config_blk.store)
    {
        DIRTY();

        d_dbase_record_flash_flush_blk(config_block_id, \
                                       D_CONF_OFFSET_IN_TBL + offset, data_size, (((D_U8*)(&CONFIG)) + offset), 1);
    }
}

/** @brief 恢复缺省配置信息*/
static D_Result
config_restore (D_Bool update, D_Bool fully) D_FUNCPOSTFIT
{
    //D_U8 pwd_len;
    //D_U8 passwd[D_CONF_PASSWORD_LEN + 1];
    D_Char stb_id[D_CONF_DEF_STB_ID_LEN];
    D_U8   ca_info[D_CONF_CA_INFO_LEN];
#ifdef D_USE_NETWORK
    D_U8 mac[6];
#endif
    D_SIParam si_param;
    D_U32 curr_ca;

    D_DUMP ("Restore default config\n");

    LOCK();

    if(fully == 1)
    {
        /*第一次开机初始化*/
        memcpy(&CONFIG, (D_U8*)&def_config, sizeof(D_StbConfig));
    }
    if(fully == 2)//主频点
    {
        CONFIG.si_param.main = def_config.si_param.main;
    }
    else //0
    {
        /*平时的恢复出厂设置*/

        /*记录恢复之前的一些参数*/
        memcpy(stb_id, CONFIG.stb_param.stb_id, D_CONF_DEF_STB_ID_LEN);
#ifdef D_USE_NETWORK
        memcpy(mac, CONFIG.net_param.mac, 6);
#endif
        si_param = CONFIG.si_param;
        //pwd_len = CONFIG.user_param.passwd_len;
        //memcpy(passwd, CONFIG.user_param.passwd, (D_CONF_PASSWORD_LEN + 1));

        curr_ca = CONFIG.user_param.curr_ca;
        memcpy(ca_info, CONFIG.user_param.ca_info, D_CONF_CA_INFO_LEN);

        /*默认参数*/
        memcpy(&CONFIG, (D_U8*)&def_config, sizeof(D_StbConfig));


        /*重新设置记录的参数*/
        memcpy(CONFIG.stb_param.stb_id, stb_id, D_CONF_DEF_STB_ID_LEN);
#ifdef D_USE_NETWORK
        memcpy(CONFIG.net_param.mac, mac, 6);
#endif
        CONFIG.si_param.main = si_param.main;
        CONFIG.si_param.epg_strategy = si_param.epg_strategy;
        //CONFIG.user_param.passwd_len = pwd_len;
        //memcpy(CONFIG.user_param.passwd, passwd, (D_CONF_PASSWORD_LEN + 1));
        CONFIG.user_param.curr_ca = curr_ca;
        memcpy(CONFIG.user_param.ca_info, ca_info, D_CONF_CA_INFO_LEN);
    }

#ifdef D_SUPPORT_EEPROM
    d_dbase_eeprom_store_data (&config_blk, D_CONF_OFFSET_IN_TBL, sizeof(D_StbConfig));
#else
    conf_save_in_rec(0, sizeof(D_StbConfig));
#endif

    UNLOCK();

    return D_OK;
}

/** @brief 取得loader 升级配置
* @param 无
* @return 无
*/
static void custom_config_parse_upgrade_tag(D_LoaderParam *loader_param) D_FUNCPOSTFIT
{
    D_U8 *payload;
    D_U16   len;

    /*loader 升级配置*/
    payload = (D_U8*)d_conf_file_search_tag(CUSTOM_CONFIG_TAG_UPGRADE, &len);
    if(payload && len >= 23)
    {
        loader_param->fe_ts_sel = payload[0];
        loader_param->fparam.freq = ((D_U32)payload[1] << 16) | ((D_U32)payload[2] << 8) | payload[3];
        loader_param->fparam.baud = d_make_u16(payload[4], payload[5]);
        loader_param->fparam.mod = (D_FEndMod)payload[6];
        loader_param->lnbfreq1 = ((D_U32)payload[7] << 16) | ((D_U32)payload[8] << 8) | payload[9];
        loader_param->lnbfreq2 = ((D_U32)payload[10] << 16) | ((D_U32)payload[11] << 8) | payload[12];
        loader_param->diseqc_type = payload[13];
        loader_param->diseqc_port = payload[14];
        loader_param->f22kstate = payload[15];
        loader_param->tid = payload[16];
        loader_param->pid = d_make_u16(payload[17], payload[18]);
        loader_param->font_addr_in_flash = ((D_U32)payload[19] << 24) | ((D_U32)payload[20] << 16) | ((D_U32)payload[21] << 8) | payload[22];
    }
}

/** @brief 取得屏参数配置
* @param 无
* @return 无
*/
static void custom_config_parse_panel_tag(D_PanelParam* panle_param) D_FUNCPOSTFIT
{
    D_U8 *payload;
    D_U16   len;
    D_U16   val;

    payload = d_conf_file_search_tag(CUSTOM_CONFIG_TAG_PANEL_CONFIG, &len);
    if(payload)
    {
        D_U16 h_total, v_total_50, v_total_60, h_active_width, h_sync_width, h_active_start;
        D_U16 v_active_width, v_sync_width, v_active_start, pll_freq;
        D_U8 channel_mode, exchange_mode, exchange_pn, lvds_foramt, lvds_da_tx_pds, lvds_clk_tx_pds, vp_div, lvds_x;
        D_U8 invert, lvds_type;

        exchange_mode = (payload[0] >> 7) & 0x01;
        exchange_pn = (payload[0] >> 6) & 0x01;
        lvds_foramt =  (payload[0] >> 5) & 0x01;
        channel_mode = (payload[0] >> 4) & 0x01;
        lvds_da_tx_pds = (payload[1] >> 4) & 0x0f;
        lvds_clk_tx_pds = (payload[1] >> 0) & 0x0f;
        val = 2;
        h_active_width = ((D_U16)payload[val++] << 8 ) | payload[val++];
        v_active_width = ((D_U16)payload[val++] << 8 ) | payload[val++];
        h_total = ((D_U16)payload[val++] << 8 ) | payload[val++];
        v_total_50 = ((D_U16)payload[val++] << 8 ) | payload[val++];
        v_total_60 = ((D_U16)payload[val++] << 8 ) | payload[val++];
        h_active_start = ((D_U16)payload[val++] << 8 ) | payload[val++];
        v_active_start = ((D_U16)payload[val++] << 8 ) | payload[val++];
        h_sync_width = ((D_U16)payload[val++] << 8 ) | payload[val++];
        v_sync_width = ((D_U16)payload[val++] << 8 ) | payload[val++];
        pll_freq = ((D_U16)payload[val++] << 8 ) | payload[val++];
        vp_div = payload[val++];
        lvds_x = payload[val++];
        invert = (payload[val] >> 6) & 0x03;
        lvds_type = (payload[val]) & 0x3F;

        panle_param->lvds_init_param.lvds_v_total = v_total_60;
        panle_param->lvds_init_param.lvds_h_active_width = h_active_width;
        panle_param->lvds_init_param.lvds_h_sync_width = h_sync_width;
        panle_param->lvds_init_param.lvds_h_active_start = h_active_start;
        panle_param->lvds_init_param.lvds_v_active_height = v_active_width;
        panle_param->lvds_init_param.lvds_v_sync_width = v_sync_width;
        panle_param->lvds_init_param.lvds_v_active_start = v_active_start;
        panle_param->lvds_init_param.lvds_v_active_end = v_active_start + v_active_width;
       
        panle_param->lvds_init_param.lvds_channel_mode = channel_mode;
        panle_param->lvds_init_param.lvds_exchange_mode = exchange_mode;
        panle_param->lvds_init_param.lvds_foramt = lvds_foramt;
        panle_param->lvds_init_param.lvds_div = 0;
        if(channel_mode)
        {
            panle_param->lvds_init_param.lvds_h_total = h_total / 2+10;
			panle_param->lvds_init_param.lvds_h_active_end = h_active_start + h_active_width/2 ;
        }
        else
        {
            panle_param->lvds_init_param.lvds_h_total = h_total;
            panle_param->lvds_init_param.lvds_h_active_end = h_active_start + h_active_width ;
        }
        if(channel_mode == 1 )
        {
            panle_param->lvds_init_param.lvds_sync_mode = 1;
        }
        else
        {
            panle_param->lvds_init_param.lvds_sync_mode = 0;
        }
        panle_param->lvds_init_param.lvds_l_p_n_sel = 0xff;
        panle_param->lvds_init_param.lvds_r_p_n_sel = 0xff;
        panle_param->lvds_init_param.lvds_da_tx_pds = lvds_da_tx_pds;
        panle_param->lvds_init_param.lvds_clk_tx_pds = lvds_clk_tx_pds;
        panle_param->lvds_init_param.pll_freq = pll_freq;//lvds_clk = pll_freq/vp_div
        panle_param->lvds_init_param.vp_div = vp_div;
        panle_param->lvds_init_param.lvds_x = lvds_x;

        panle_param->lvds_type = lvds_type;//mini是1，lvds是0

        if((h_active_width == 1366) && (v_active_width == 768))
        {
            panle_param->screenparam.OSD_set_line_to_top = 0x12;
            panle_param->screenparam.OSD_set_pix_to = 0x32;
            panle_param->screenparam.VCOM_DE_start_pix = 0x4a;
            panle_param->screenparam.VCOM_DE_start_line = 0x35;
        }
        else if((h_active_width == 1920) && (v_active_width == 1080))
        {
            panle_param->screenparam.OSD_set_line_to_top = 0x04;
            panle_param->screenparam.OSD_set_pix_to = 0x28;
            panle_param->screenparam.VCOM_DE_start_pix = 0x4a;
            panle_param->screenparam.VCOM_DE_start_line = 0x35;
        }
        else if((h_active_width == 1440) && (v_active_width == 900))
        {
            panle_param->screenparam.OSD_set_line_to_top = 13;
            panle_param->screenparam.OSD_set_pix_to = 56;
            panle_param->screenparam.VCOM_DE_start_pix = 0x4a;
            panle_param->screenparam.VCOM_DE_start_line = 0x35;
        }
        else if((h_active_width == 1024) && (v_active_width == 600))
        {
            panle_param->screenparam.OSD_set_pix_to = 0x18;
            panle_param->screenparam.OSD_set_line_to_top = 0x1f;
            panle_param->screenparam.VCOM_DE_start_pix = 0x4a;
            panle_param->screenparam.VCOM_DE_start_line = 0x35;
        }
        else if((h_active_width == 1280) && (v_active_width == 1024))
        {
            panle_param->screenparam.OSD_set_line_to_top = 0x0a;
            panle_param->screenparam.OSD_set_pix_to = 0x2c;
            panle_param->screenparam.VCOM_DE_start_pix = 0x4a;
            panle_param->screenparam.VCOM_DE_start_line = 0x35;
        }
        else if((h_active_width == 800) && (v_active_width == 480))
        {
            panle_param->screenparam.OSD_set_line_to_top = 24;
            panle_param->screenparam.OSD_set_pix_to = 29;
            panle_param->screenparam.VCOM_DE_start_pix = 0x4a;
            panle_param->screenparam.VCOM_DE_start_line = 0x35;
			panle_param->lvds_init_param.lvds_v_active_end = v_total_50;//v_active_start + v_active_width;
        }
        else
        {
            panle_param->screenparam.OSD_set_line_to_top = 0x10;
            panle_param->screenparam.OSD_set_pix_to = 0x2c;
            panle_param->screenparam.VCOM_DE_start_pix = 0x4a;
            panle_param->screenparam.VCOM_DE_start_line = 0x35;
        }
        if (invert & 0x2)
            panle_param->screenparam.SP_StartLine = 0x33;//纵向翻转----------tanys==0x34->0x33,,,要对上下翻转的倒装作区分
        else
            panle_param->screenparam.SP_StartLine = 0x34;//纵向不翻转
        panle_param->screenparam.SP_StartPix = 0x02;
        panle_param->screenparam.VCOM_StartLine = 0x35;
        panle_param->screenparam.VCOM_StartPix = 0x45;
        panle_param->screenparam.VO_feeder_vsync_line = 0x3;
        panle_param->screenparam.VO_hs_vsync_line = 0x31;
        panle_param->screenparam.VO_hs_vsync_pix = 0x53;
        panle_param->screenparam.VO_set_pix_to_VeBypass = 0xf7;
        panle_param->screenparam.VO_set_pix_to_VeEnable = 0xf7;
        panle_param->screenparam.AV_Pal_x = 5;
        panle_param->screenparam.AV_Pal_y = 5;
        panle_param->screenparam.AV_NTSC_x = 5;
        panle_param->screenparam.AV_NTSC_y = 5;

        panle_param->tven_para.display_invert = invert;
        panle_param->tven_para.v_max_50 = 1280;
        panle_param->tven_para.v_min_60 = 778;
        panle_param->tven_para.out_freq_50 = (D_U32)pll_freq * 1000000 / vp_div; //148500000;
        panle_param->tven_para.out_freq_60 = (D_U32)pll_freq * 1000000 / vp_div; //148500000;
        panle_param->tven_para.total_line_50 = v_total_50;
        panle_param->tven_para.total_line_60 = v_total_60;
        panle_param->tven_para.total_pix_per_line_50 = h_total;
        panle_param->tven_para.total_pix_per_line_60 = h_total;
        panle_param->tven_para.screenwidth = h_active_width;
        panle_param->tven_para.screenheight = v_active_width;

        switch(lvds_type)
        {
            case 1://,BOE_768P_N56,BOE_768P_N56
            case 3://,BOE_768P_N81,BOE_768P_N81
                panle_param->tven_para.vsync_lastde_delay_50 = 0xd4;
                panle_param->tven_para.vsync_lastde_delay_60 = 0x30;
                panle_param->tven_para.speed_adj_line = 0;
                panle_param->screenparam.VCOM_DE_end_line = v_active_width + 3;
                panle_param->screenparam.VCOM_DE_start_line = 0x35;
                break;
            case 2://,BOE_768P_N86,BOE_768P_N86
                panle_param->tven_para.vsync_lastde_delay_50 = 0xd4;
                panle_param->tven_para.vsync_lastde_delay_60 = 0x30;
                panle_param->tven_para.speed_adj_line = 0;
                panle_param->screenparam.VCOM_DE_end_line = v_active_width + 3;
                panle_param->screenparam.VCOM_DE_start_line = 0x35;
                break;
            case 4://,HK_768P_PT320,HK_768P_PT320
                panle_param->tven_para.vsync_lastde_delay_50 = 0xd6;
                panle_param->tven_para.vsync_lastde_delay_60 = 0x32;
                panle_param->tven_para.speed_adj_line = 0;
                panle_param->screenparam.VCOM_DE_end_line = v_active_width + 1;
                panle_param->screenparam.VCOM_DE_start_line = 0x35;
                break;
            case 5://,BOE_1080P_N10,BOE_1080P_N10
            case 6://,BOE_1080P_N40,BOE_1080P_N40
            case 7://,TCL_1080P_ST48,TCL_1080P_ST48
            default:
                panle_param->tven_para.vsync_lastde_delay_50 = 0x04;
                panle_param->tven_para.vsync_lastde_delay_60 = 0x04;
#ifdef D_TV_PEOJECT_TOUYY
                panle_param->tven_para.speed_adj_line = 0x00;
#else
                panle_param->tven_para.speed_adj_line = 0x10;
#endif
                panle_param->screenparam.VCOM_DE_end_line = v_active_width;
                break;
        }
        p_panel_get_tcon_info(lvds_type, &panle_param->tcon_param);
        p_panel_color_config(lvds_type);
    }
}

static void check_loader_param(D_Bool forced)
{
    D_HEEPRom he2p;
    D_LoaderParam loader_param;

    he2p = d_eeprom_create(NULL);

    d_eeprom_read(he2p, LOADER_PARAM_OFFSET_IN_EEPROM, (D_U8*)&loader_param, sizeof(D_LoaderParam));

    /* stb序列号保留, loader可以在loader结构错误的情况下写入一个序列号 */
    memcpy(CONFIG.stb_param.stb_id, loader_param.stb_param_copy.stb_id, D_CONF_DEF_STB_ID_LEN);

    if((d_crc_compute_32((D_U8*)&loader_param, (D_U8*)&loader_param.crc - (D_U8*)&loader_param) != loader_param.crc) || forced)
    {
        memcpy(&loader_param, &def_loader_param, sizeof(D_LoaderParam));
        loader_param.stb_param_copy.sw_major = CONFIG.stb_param.sw_major;
        loader_param.stb_param_copy.sw_minor = CONFIG.stb_param.sw_minor;
        loader_param.stb_param_copy.sw_build_num = CONFIG.stb_param.sw_build_num;

        loader_param.vid_output = CONFIG.user_param.vid_output;

        loader_param.size = sizeof(D_LoaderParam);
        loader_param.crc = d_crc_compute_32((D_U8*)&loader_param, (D_U8*)&loader_param.crc - (D_U8*)&loader_param);

        d_eeprom_write(he2p, LOADER_PARAM_OFFSET_IN_EEPROM, (D_U8*)&loader_param, sizeof(D_LoaderParam));
    }

    d_eeprom_destroy(he2p);
}

static void check_panel_param(D_Bool forced)
{
    D_HEEPRom he2p;
    D_PanelParam panle_param;
    /* 请保持在512字节内 */
    if(sizeof(D_PanelParam) > 512)
    {
        D_ERROR("Please make sure sizeof 'D_PanelParam' no more than 512B, thanks a lot!\n");
        return ;
    }

    he2p = d_eeprom_create(NULL);

    d_eeprom_read(he2p, PANEL_PARAM_OFFSET_IN_EEPROM, (D_U8*)&panle_param, sizeof(D_PanelParam));
    if((d_crc_compute_32((D_U8*)&panle_param, (D_U8*)&panle_param.crc - (D_U8*)&panle_param) != panle_param.crc) || forced||(panle_param.size != sizeof(D_PanelParam)))
    {
        memcpy(&panle_param, &def_panel_param, sizeof(D_PanelParam));
        panle_param.size = sizeof(D_PanelParam);
        panle_param.crc = d_crc_compute_32((D_U8*)&panle_param, (D_U8*)&panle_param.crc - (D_U8*)&panle_param);

        d_eeprom_write(he2p, PANEL_PARAM_OFFSET_IN_EEPROM, (D_U8*)&panle_param, sizeof(D_PanelParam));
    }

    d_eeprom_destroy(he2p);
}

/** @brief 初始化配置信息*/
D_Result
p_conf_init (void) D_FUNCPOSTFIT
{
    D_Bool forced = D_FALSE;

    /* 请保持在512字节内 */
    if(sizeof(D_StbConfig) > P_CONFIG_BLOCK_SIZE)
    {
        D_ERROR("Please make sure sizeof 'D_StbConfig' no more than 512B, thanks a lot!\n");
        return D_ERR;
    }

    config_block_id = d_dbase_get_block_id((D_DBBlock*)(&config_blk));

    config = (D_StbConfig*)(config_blk.buf + D_CONF_OFFSET_IN_TBL);

#ifdef D_SUPPORT_EEPROM
    loaded = D_TRUE;
#endif

    def_config.manu_id = (((D_U32)(sizeof(D_StbConfig))) << 16) + ((D_U16)D_MANUFACTORY_ID); //高两位字节存放系统配置结构体的大小
    D_DUMP("Size of struct D_StbConfig is %d bytes!\n", sizeof(D_StbConfig));
    /*主频点*/
    def_config.si_param.main.freq = g_custom_config.dvbc_main.freq;
    def_config.si_param.main.baud = g_custom_config.dvbc_main.baud;
    def_config.si_param.main.mod = g_custom_config.dvbc_main.mod;
    def_config.si_param.network_id = g_custom_config.dvbc_main.network_id;
    memcpy(def_config.si_param.network_name, g_custom_config.dvbc_main.network_name, D_CUSTOM_CONF_NETWORK_NAME_LEN);
    def_config.si_param.network_name[D_CUSTOM_CONF_NETWORK_NAME_LEN] = '\0';

    /*密码配置*/
    def_config.user_param.passwd_en = g_custom_config.password.stbmenu;
    def_config.user_param.passwd_en_power_on = g_custom_config.password.power_on;
    def_config.user_param.passwd_en_prog_lock = g_custom_config.password.prog_lock;
    if(g_custom_config.password.pwd_len)
    {
        def_config.user_param.passwd_len = D_MIN(g_custom_config.password.pwd_len, D_CONF_PASSWORD_LEN);
        memcpy(def_config.user_param.passwd, (D_U8*)(g_custom_config.password.def_pwd), def_config.user_param.passwd_len);
        def_config.user_param.passwd[def_config.user_param.passwd_len] = (D_U8)( '\0');
    }

    /*其它默认配置*/
    def_config.user_param.aud_track = (D_AudTrack)g_custom_config.sys_setup.track;
    def_config.user_param.volume = g_custom_config.sys_setup.def_voice;
    def_config.user_param.channel_change_mode = (D_U32)g_custom_config.sys_setup.change_mode;
    def_config.user_param.lang = (D_AudTrack)g_custom_config.sys_setup.def_language;
    def_config.user_param.smart_voice = (D_Bool)g_custom_config.sys_setup.smart_voice;
    def_config.user_param.save_type = (D_U8)g_custom_config.sys_setup.chan_save;

#ifdef D_CA_SUPPORT_XGCA
    def_config.user_param.user_sort = g_custom_config.scan.asort;
#endif
#ifdef D_TV_PEOJECT_TOUYY
    def_config.user_param.vid_input = D_VID_IUTPUT_AV1;
#endif
    def_config.stb_param.sw_major = (D_U8)(g_custom_config.dvbc_main.software_version >> 24);
    def_config.stb_param.sw_minor = (D_U8)(g_custom_config.dvbc_main.software_version >> 16);
    def_config.stb_param.sw_build_num = (D_U16)g_custom_config.dvbc_main.software_version;
    {
        D_U8 *payload;
        D_U16 len;
        D_U16 manu_id, manu_id1, size;

        payload = d_conf_file_search_tag(CUSTOM_CONFIG_TAG_RESTORE, &len);
        if(!payload || (len < 3))
        {
            /*如果Flash中没有有效数据，用缺省值初始化*/
            if(CONFIG.manu_id != def_config.manu_id)
            {
                config_restore(D_FALSE, 1);
                forced = D_TRUE;
            }
        }
        else if(len == 3)
        {
            manu_id = ((payload[0] << 8) | payload[1]);
            manu_id1 = (CONFIG.manu_id & 0x0000ffff);
            size = ((CONFIG.manu_id >> 16) & 0x0000ffff);

            if(sizeof(D_StbConfig) != size)
            {
                /*如果Flash中没有有效数据，用缺省值初始化*/
                if(CONFIG.manu_id != def_config.manu_id)
                {
                    config_restore(D_FALSE, 1);
                    forced = D_TRUE;
                }

            }
            else if(manu_id != manu_id1)
            {
                CONFIG.manu_id = (((D_U32)(sizeof(D_StbConfig))) << 16) + ((D_U16)manu_id); //高两位字节存放系统配置结构体的大小
                if(payload[2] && 0x01) //主频点
                    config_restore(D_FALSE, 2);
            }
        }
    }

    /*设置loader参数*/
    custom_config_parse_upgrade_tag(&def_loader_param);
    /* 如果e2p里的数据无效, 用缺省值初始化 */
    check_loader_param(forced);
    custom_config_parse_panel_tag(&def_panel_param);
    check_panel_param(forced);

    return D_OK;
}

/** @brief 恢复为最初配置信息*/
D_Result
p_conf_restore (D_Bool update) D_FUNCPOSTFIT
{
    config_restore(update, 0);

    return D_OK;
}

D_Result
p_conf_restore_eep (void) D_FUNCPOSTFIT
{
    config_restore(D_TRUE, 1);
    check_loader_param(D_TRUE);
    check_panel_param(D_TRUE);

    return D_OK;
}

/** @brief 取得视频制式设置*/
D_VidFormat
p_conf_get_vid_fmt(void) D_FUNCPOSTFIT
{
    D_VidFormat fmt;

#ifdef D_SUPPORT_EEPROM
    /*为提高启动速度,在没有加载数据库时,可通过EEPROM直接访问数据*/
    if (! loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.vid_fmt - (D_U8*)&CONFIG + D_CONF_OFFSET_IN_TBL,
                                  sizeof (CONFIG.user_param.vid_fmt));
        return CONFIG.user_param.vid_fmt;
    }
#endif

    LOCK();
    fmt = CONFIG.user_param.vid_fmt;
    UNLOCK();

    return fmt;
}

/** @brief 设置视频制式设置*/
D_Result
p_conf_set_vid_fmt (D_VidFormat fmt) D_FUNCPOSTFIT
{
    LOCK();
    if (CONFIG.user_param.vid_fmt != fmt)
    {
        CONFIG.user_param.vid_fmt = fmt;

#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.vid_fmt - (D_U8*)&CONFIG + D_CONF_OFFSET_IN_TBL,
                                   sizeof (CONFIG.user_param.vid_fmt));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.vid_fmt - (D_U8*)&CONFIG, \
                         sizeof(CONFIG.user_param.vid_fmt));
#endif
    }
    UNLOCK();

    return D_OK;
}


#ifdef D_CA_SUPPORT_XGCA

/** @brief 取得排序方式设置*/
D_U8
p_conf_get_user_sort(void) D_FUNCPOSTFIT
{
    D_U8    sort;

#ifdef D_SUPPORT_EEPROM
    /*为提高启动速度,在没有加载数据库时,可通过EEPROM直接访问数据*/
    if (! loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.user_sort - (D_U8*)&CONFIG + D_CONF_OFFSET_IN_TBL,
                                  sizeof (CONFIG.user_param.user_sort));
        return CONFIG.user_param.user_sort;
    }
#endif

    LOCK();
    sort = CONFIG.user_param.user_sort;
    UNLOCK();

    return sort;
}

/** @brief 设置排序方式设置*/
D_Result
p_conf_set_user_sort (D_U8 sort) D_FUNCPOSTFIT
{
    LOCK();
    if (CONFIG.user_param.user_sort != sort)
    {
        CONFIG.user_param.user_sort = sort;

#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.user_sort - (D_U8*)&CONFIG + D_CONF_OFFSET_IN_TBL,
                                   sizeof (CONFIG.user_param.user_sort));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.user_sort - (D_U8*)&CONFIG, \
                         sizeof(CONFIG.user_param.user_sort));
#endif
    }
    UNLOCK();

    return D_OK;
}

#endif


/** @brief 取得声道设置*/
D_AudTrack
p_conf_get_aud_track (void) D_FUNCPOSTFIT
{
    D_AudTrack  t;

#ifdef D_SUPPORT_EEPROM
    /*为提高启动速度,在没有加载数据库时,可通过EEPROM直接访问数据*/
    if (! loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.aud_track - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.aud_track));
        return CONFIG.user_param.aud_track;
    }
#endif

    LOCK ();
    t = CONFIG.user_param.aud_track;
    UNLOCK ();

    return t;
}

/** @brief 设置声道设置*/
D_Result
p_conf_set_aud_track (D_AudTrack track) D_FUNCPOSTFIT
{
    LOCK ();
    if (CONFIG.user_param.aud_track != track)
    {
        CONFIG.user_param.aud_track = track;
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.aud_track - (D_U8*)&CONFIG,
                                   sizeof (CONFIG.user_param.aud_track));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.aud_track - (D_U8*)&CONFIG,
                         sizeof (CONFIG.user_param.aud_track));
#endif
    }
    UNLOCK ();

    return D_OK;
}

/** @brief 取得时区设置*/
D_S32
p_conf_get_time_offset (void) D_FUNCPOSTFIT
{
    D_S32   off;

#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.time_offset - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.time_offset));
        return CONFIG.user_param.time_offset;
    }
#endif

    LOCK ();
    off = CONFIG.user_param.time_offset;
    UNLOCK ();

    return off;
}

/** @brief 设置时区*/
D_S32
p_conf_set_time_offset (D_S32 off) D_FUNCPOSTFIT
{
    LOCK ();
    if (CONFIG.user_param.time_offset != off)
    {
        CONFIG.user_param.time_offset = off;
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.time_offset - (D_U8*)&CONFIG,
                                   sizeof (CONFIG.user_param.time_offset));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.time_offset - (D_U8*)&CONFIG,
                         sizeof (CONFIG.user_param.time_offset));
#endif
    }
    UNLOCK ();

    return D_OK;
}

/** @brief 取得SI设置*/
D_Result
p_conf_get_si_param (D_SIParam *si_param) D_FUNCPOSTFIT
{
    if (! si_param)
        return D_ERR_INVALID_ARGUMENT;

#ifdef D_SUPPORT_EEPROM
    /*为提高启动速度,在没有加载数据库时,可通过EEPROM直接访问数据*/
    if (! loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.si_param - (D_U8*)&CONFIG,
                                  sizeof (D_SIParam));
        *si_param = CONFIG.si_param;
        return D_OK;
    }
#endif
    LOCK ();
    memcpy (si_param, &CONFIG.si_param, sizeof (D_SIParam));
    UNLOCK ();

    return D_OK;
}

/** @brief 设置SI设置*/
D_Result
p_conf_set_si_param (D_SIParam *si_param) D_FUNCPOSTFIT
{
    if (! si_param)
        return D_ERR_INVALID_ARGUMENT;

    LOCK ();
    if(memcmp (&CONFIG.si_param, si_param, sizeof (D_SIParam)) != 0)
    {
        memcpy (&CONFIG.si_param, si_param, sizeof (D_SIParam));
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.si_param - (D_U8*)&CONFIG,
                                   sizeof (D_SIParam));
#else
        conf_save_in_rec((D_U8*)&CONFIG.si_param - (D_U8*)&CONFIG,
                         sizeof (D_SIParam));
#endif
    }
    UNLOCK ();

    return D_OK;
}

/** @brief 取得Loader参数设置*/
D_Result p_conf_get_loader_param (D_LoaderParam *loader_param) D_FUNCPOSTFIT
{
    D_HEEPRom he2p;

    if (! loader_param)
        return D_ERR_INVALID_ARGUMENT;

    he2p = d_eeprom_create(NULL);

    d_eeprom_read(he2p, LOADER_PARAM_OFFSET_IN_EEPROM, (D_U8*)loader_param, sizeof(D_LoaderParam));

    d_eeprom_destroy(he2p);

    return D_OK;
}

/** @brief 设置Loader参数设置*/
D_Result p_conf_set_loader_param (D_LoaderParam *loader_param) D_FUNCPOSTFIT
{
    D_HEEPRom he2p;

    if (! loader_param)
        return D_ERR_INVALID_ARGUMENT;

    he2p = d_eeprom_create(NULL);

    loader_param->crc = d_crc_compute_32((D_U8*)loader_param, (D_U8*)&loader_param->crc - (D_U8*)loader_param);

    d_eeprom_write(he2p, LOADER_PARAM_OFFSET_IN_EEPROM, (D_U8*)loader_param, sizeof(D_LoaderParam));

    d_eeprom_destroy(he2p);

    return D_OK;
}

/** @brief 取得音量设置*/
D_U8
p_conf_get_volume (void) D_FUNCPOSTFIT
{
    D_U8    vol;

#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.volume - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.volume));
        return CONFIG.user_param.volume;
    }
#endif

    LOCK ();
    vol = CONFIG.user_param.volume;
    UNLOCK ();

    return vol;
}

/** @brief 设置声道设置*/
D_Result
p_conf_set_volume (D_U8 vol) D_FUNCPOSTFIT
{
    LOCK ();
    if (CONFIG.user_param.volume != vol)
    {
        CONFIG.user_param.volume = vol;
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.volume - (D_U8*)&CONFIG,
                                   sizeof (CONFIG.user_param.volume));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.volume - (D_U8*)&CONFIG,
                         sizeof (CONFIG.user_param.volume));
#endif
    }
    UNLOCK ();

    return D_OK;
}

/** @brief 取得当前服务ID*/
D_DBSrvID
p_conf_get_curr_srv () D_FUNCPOSTFIT
{
    D_DBSrvID   srv;

#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.curr_srv - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.curr_srv));

        srv = (D_DBSrvID)((D_S16)((D_U16)(CONFIG.user_param.curr_srv & 0xFFFF))); /* 低16位存 dtv, 高16位存 atv */
        return srv;
    }
#endif

    LOCK ();
    srv = (D_DBSrvID)((D_S16)((D_U16)(CONFIG.user_param.curr_srv & 0xFFFF))); /* 低16位存 dtv, 高16位存 atv */
    //srv = CONFIG.user_param.curr_srv;
    UNLOCK ();

    return srv;
}

/** @brief 设置当前服务ID*/
D_Result
p_conf_set_curr_srv (D_DBSrvID id) D_FUNCPOSTFIT
{
    LOCK ();
    /* 低16位存 dtv, 高16位存 atv */
    if ((CONFIG.user_param.curr_srv & 0xFFFF) !=  (id & 0xFFFF))
    {
        CONFIG.user_param.curr_srv &= 0xFFFF0000;
        CONFIG.user_param.curr_srv |= (0xFFFF & id);
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.curr_srv - (D_U8*)&CONFIG,
                                   sizeof (CONFIG.user_param.curr_srv));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.curr_srv - (D_U8*)&CONFIG,
                         sizeof (CONFIG.user_param.curr_srv));
#endif
    }
    UNLOCK ();

    return D_OK;
}

/** @brief 取得当前服务ID*/
D_DBSrvID
p_conf_get_curr_atv_srv () D_FUNCPOSTFIT
{
    D_DBSrvID   srv;

#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.curr_srv - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.curr_srv));

        srv = (D_DBSrvID)((D_S16)((D_U16)((CONFIG.user_param.curr_srv >> 16) & 0xFFFF))); /* 低16位存 dtv, 高16位存 atv */
        return srv;
    }
#endif

    LOCK ();
    srv = (D_DBSrvID)((D_S16)((D_U16)((CONFIG.user_param.curr_srv >> 16) & 0xFFFF))); /* 低16位存 dtv, 高16位存 atv */
    //srv = CONFIG.user_param.curr_srv;
    UNLOCK ();

    return srv;
}

/** @brief 设置当前服务ID*/
D_Result
p_conf_set_curr_atv_srv (D_DBSrvID id) D_FUNCPOSTFIT
{
    LOCK ();
    /* 低16位存 dtv, 高16位存 atv */
    if (((CONFIG.user_param.curr_srv >> 16) & 0xFFFF) !=  (id & 0xFFFF))
    {
        CONFIG.user_param.curr_srv &= 0x0000FFFF;
        CONFIG.user_param.curr_srv |= (0xFFFF0000 & (id << 16));
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.curr_srv - (D_U8*)&CONFIG,
                                   sizeof (CONFIG.user_param.curr_srv));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.curr_srv - (D_U8*)&CONFIG,
                         sizeof (CONFIG.user_param.curr_srv));
#endif
    }
    UNLOCK ();

    return D_OK;
}

/** @brief 取得语言设置*/
D_U8
p_conf_get_lang() D_FUNCPOSTFIT
{
    D_U8    lang;

#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.lang - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.lang));
        return CONFIG.user_param.lang;
    }
#endif

    LOCK ();
    lang = CONFIG.user_param.lang;
    UNLOCK ();

    return lang;
}

/** @brief 设置语言*/
D_U8
p_conf_set_lang(D_U8 lang) D_FUNCPOSTFIT
{
    LOCK ();
    if (CONFIG.user_param.lang != lang)
    {
        CONFIG.user_param.lang = lang;
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.lang - (D_U8*)&CONFIG,
                                   sizeof (CONFIG.user_param.lang));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.lang - (D_U8*)&CONFIG,
                         sizeof (CONFIG.user_param.lang));
#endif
    }
    UNLOCK ();

    return D_OK;
}

/** @brief 取得透明度设置*/
D_U8
p_conf_get_transp() D_FUNCPOSTFIT
{
    D_U8    transp;

#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.transp - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.transp));
        return CONFIG.user_param.transp;
    }
#endif

    LOCK ();
    transp = CONFIG.user_param.transp;
    UNLOCK ();

    return transp;
}

/** @brief 设置透明度*/
D_U8
p_conf_set_transp(D_U8  transp) D_FUNCPOSTFIT
{
    LOCK ();
    if (CONFIG.user_param.transp != transp)
    {
        CONFIG.user_param.transp = transp;
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.transp - (D_U8*)&CONFIG,
                                   sizeof (CONFIG.user_param.transp));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.transp - (D_U8*)&CONFIG,
                         sizeof (CONFIG.user_param.transp));
#endif
    }
    UNLOCK ();

    return D_OK;
}

/** @brief 取得信息条显示时间设置*/
D_U8
p_conf_get_info_time() D_FUNCPOSTFIT
{
    D_U8    info_time;

#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.info_time - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.info_time));
        return CONFIG.user_param.info_time;
    }
#endif

    LOCK ();
    info_time = CONFIG.user_param.info_time;
    UNLOCK ();

    return info_time;
}

/** @brief 设置信息条显示时间*/
D_U8
p_conf_set_info_time(D_U8   info_time) D_FUNCPOSTFIT
{
    LOCK ();
    if (CONFIG.user_param.info_time != info_time)
    {
        CONFIG.user_param.info_time = info_time;
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.info_time - (D_U8*)&CONFIG,
                                   sizeof (CONFIG.user_param.info_time));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.info_time - (D_U8*)&CONFIG,
                         sizeof (CONFIG.user_param.info_time));
#endif
    }
    UNLOCK ();

    return D_OK;
}

/** @brief 取得视频输出*/
D_VidOutput
p_conf_get_vid_output (void) D_FUNCPOSTFIT
{
    D_VidOutput out;

#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.vid_output - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.vid_output));
        return CONFIG.user_param.vid_output;
    }
#endif

    LOCK ();
    out = CONFIG.user_param.vid_output;
    UNLOCK ();

    return out;
}

/** @brief 设置视频输出*/
D_Result
p_conf_set_vid_output (D_VidOutput out) D_FUNCPOSTFIT
{
    D_LoaderParam loader_param;

    LOCK ();
    if (CONFIG.user_param.vid_output != out)
    {
        CONFIG.user_param.vid_output = out;
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.vid_output - (D_U8*)&CONFIG,
                                   sizeof (CONFIG.user_param.vid_output));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.vid_output - (D_U8*)&CONFIG,
                         sizeof (CONFIG.user_param.vid_output));
#endif
    }

    p_conf_get_loader_param(&loader_param);
    loader_param.vid_output = (D_U8)out;
    p_conf_set_loader_param(&loader_param);

    UNLOCK ();

    return D_OK;
}

/** @brief 取得静音标志*/
D_Bool
p_conf_get_aud_mute (void) D_FUNCPOSTFIT
{
    D_Bool  mute;

#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.aud_mute - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.aud_mute));
        return (D_Bool)CONFIG.user_param.aud_mute;
    }
#endif

    LOCK ();
    mute = (D_Bool)CONFIG.user_param.aud_mute;
    UNLOCK ();

    return mute;
}

/** @brief 设置静音标志*/
D_Result
p_conf_set_aud_mute (D_Bool mute) D_FUNCPOSTFIT
{
    LOCK ();
    CONFIG.user_param.aud_mute = mute;
#if 0 /*静音功能掉电不保存 @qiny 2015.08.20*/
#ifdef D_SUPPORT_EEPROM
    d_dbase_eeprom_store_data (&config_blk,
                               (D_U8*)&CONFIG.user_param.aud_mute - (D_U8*)&CONFIG,
                               sizeof (CONFIG.user_param.aud_mute));
#else
    conf_save_in_rec((D_U8*)&CONFIG.user_param.aud_mute - (D_U8*)&CONFIG,
                     sizeof (CONFIG.user_param.aud_mute));
#endif
#endif
    UNLOCK ();

    return D_OK;
}

#ifdef D_GUI_SUPPORT_LNB
/** @brief 取得lnb开关标志*/
D_Bool
p_conf_get_lnb (void) D_FUNCPOSTFIT
{
    D_Bool  lnb_state;

#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.lnb_switch - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.lnb_switch));
        return (D_Bool)CONFIG.user_param.lnb_switch;
    }
#endif

    LOCK ();
    lnb_state = (D_Bool)CONFIG.user_param.lnb_switch;
    UNLOCK ();

    return lnb_state;
}


/** @brief 设置lnb 开关标志*/
D_Result
p_conf_set_lnb (D_Bool switch_state) D_FUNCPOSTFIT
{
    LOCK ();
    if(CONFIG.user_param.lnb_switch != switch_state)
    {
        CONFIG.user_param.lnb_switch = switch_state;
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.lnb_switch - (D_U8*)&CONFIG,
                                   sizeof (CONFIG.user_param.lnb_switch));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.lnb_switch - (D_U8*)&CONFIG,
                         sizeof (CONFIG.user_param.lnb_switch));
#endif
    }
    UNLOCK ();

    return D_OK;
}
#endif

#ifdef D_GUI_SUPPORT_STB_CHANGE
/** @brief 取得stb_change开关标志*/
D_Bool
p_conf_get_stb_change (void) D_FUNCPOSTFIT
{
    D_U8 stb_change_state;

#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.stb_change - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.stb_change));
        return (D_Bool)CONFIG.user_param.stb_change;
    }
#endif

    LOCK ();
    stb_change_state = (D_Bool)CONFIG.user_param.stb_change;
    UNLOCK ();

    return stb_change_state;
}


/** @brief 设置lnb 开关标志*/
D_Result
p_conf_set_stb_change (D_U8 switch_state) D_FUNCPOSTFIT
{
    LOCK ();
    if(CONFIG.user_param.stb_change != switch_state)
    {
        CONFIG.user_param.stb_change = switch_state;
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.stb_change - (D_U8*)&CONFIG,
                                   sizeof (CONFIG.user_param.stb_change));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.stb_change - (D_U8*)&CONFIG,
                         sizeof (CONFIG.user_param.stb_change));
#endif
    }
    UNLOCK ();

    return D_OK;
}
#endif

/** @brief 设置视频参数*/
D_Result
p_conf_set_vid_pic_param (D_VidPicParam *param)D_FUNCPOSTFIT
{
    LOCK ();
    if ((CONFIG.user_param.vid_param.brightness != param->brightness) ||
        (CONFIG.user_param.vid_param.chroma != param->chroma) ||
        (CONFIG.user_param.vid_param.contrast != param->contrast))
    {
        CONFIG.user_param.vid_param = *param;
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.vid_param - (D_U8*)&CONFIG,
                                   sizeof (CONFIG.user_param.vid_param));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.vid_param - (D_U8*)&CONFIG,
                         sizeof (CONFIG.user_param.vid_param));
#endif
    }
    UNLOCK ();

    return D_OK;
}

/** @brief 获得视频参数 */
D_Result
p_conf_get_vid_pic_param (D_VidPicParam *param)D_FUNCPOSTFIT
{
    if (! param)
        return D_ERR;

#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.vid_param - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.vid_param));
        *param = CONFIG.user_param.vid_param;
        return D_OK;
    }
#endif

    LOCK ();
    *param = CONFIG.user_param.vid_param;
    UNLOCK ();

    return D_OK;
}

/** @brief 设置视频宽高比例 */
D_Result
p_conf_set_vid_pic_ratio (D_VidPicRatio ratio)D_FUNCPOSTFIT
{
    LOCK ();
    if (CONFIG.user_param.vid_ratio != ratio)
    {
        CONFIG.user_param.vid_ratio = ratio;
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.vid_ratio - (D_U8*)&CONFIG,
                                   sizeof (CONFIG.user_param.vid_ratio));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.vid_ratio - (D_U8*)&CONFIG,
                         sizeof (CONFIG.user_param.vid_ratio));
#endif
    }
    UNLOCK ();

    return D_OK;
}

/** @brief 获得视频宽高比例*/
D_VidPicRatio
p_conf_get_vid_pic_ratio (void)D_FUNCPOSTFIT
{
    D_VidPicRatio ratio;

#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.vid_ratio - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.vid_ratio));
        return CONFIG.user_param.vid_ratio;
    }
#endif

    LOCK ();
    ratio = CONFIG.user_param.vid_ratio;
    UNLOCK ();

    return ratio;
}

/** @brief 获得智能音量*/
D_Bool p_conf_get_smart_voice_en (void) D_FUNCPOSTFIT
{
    D_Bool smart_voice;

#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.smart_voice - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.smart_voice));
        return (D_Bool)CONFIG.user_param.smart_voice;
    }
#endif

    LOCK ();
    smart_voice = (D_Bool)CONFIG.user_param.smart_voice;
    UNLOCK ();

    return smart_voice;
}

/** @brief 设置智能音量*/
D_Result p_conf_set_smart_voice_en (D_Bool en) D_FUNCPOSTFIT
{
    LOCK ();
    if(CONFIG.user_param.smart_voice != en)
    {
        CONFIG.user_param.smart_voice = en;
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.smart_voice - (D_U8*)&CONFIG,
                                   sizeof (CONFIG.user_param.smart_voice));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.smart_voice - (D_U8*)&CONFIG,
                         sizeof (CONFIG.user_param.smart_voice));
#endif
    }
    UNLOCK ();

    return D_OK;
}


/** @brief 获得菜单密码是否使能*/
D_Bool p_conf_get_passwd_en (void) D_FUNCPOSTFIT
{
    D_Bool passwd_en;

#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.passwd_en - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.passwd_en));
        return (D_Bool)CONFIG.user_param.passwd_en;
    }
#endif

    LOCK ();
    passwd_en = (D_Bool)CONFIG.user_param.passwd_en;
    UNLOCK ();

    return passwd_en;
}

/** @brief 设置菜单密码是否使能*/
D_Result p_conf_set_passwd_en (D_Bool en) D_FUNCPOSTFIT
{
    LOCK ();
    if(CONFIG.user_param.passwd_en != en)
    {
        CONFIG.user_param.passwd_en = en;
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.passwd_en - (D_U8*)&CONFIG,
                                   sizeof (CONFIG.user_param.passwd_en));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.passwd_en - (D_U8*)&CONFIG,
                         sizeof (CONFIG.user_param.passwd_en));
#endif
    }
    UNLOCK ();

    return D_OK;
}


/** @brief 获得开机密码是否使能*/
D_Bool p_conf_get_poweron_passwd_en (void) D_FUNCPOSTFIT
{
    D_Bool passwd_en;

#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.passwd_en_power_on - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.passwd_en_power_on));
        return (D_Bool)CONFIG.user_param.passwd_en_power_on;
    }
#endif

    LOCK ();
    passwd_en = (D_Bool)CONFIG.user_param.passwd_en_power_on;
    UNLOCK ();

    return passwd_en;
}

/** @brief 设置开机密码是否使能*/
D_Result p_conf_set_poweron_passwd_en (D_Bool en) D_FUNCPOSTFIT
{
    LOCK ();
    if(CONFIG.user_param.passwd_en_power_on != en)
    {
        CONFIG.user_param.passwd_en_power_on = en;
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.passwd_en_power_on - (D_U8*)&CONFIG,
                                   sizeof (CONFIG.user_param.passwd_en_power_on));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.passwd_en_power_on - (D_U8*)&CONFIG,
                         sizeof (CONFIG.user_param.passwd_en_power_on));
#endif
    }
    UNLOCK ();

    return D_OK;
}

/** @brief 获得节目锁密码是否使能*/
D_Bool p_conf_get_prog_passwd_en (void) D_FUNCPOSTFIT
{
    D_Bool passwd_en;

#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.passwd_en_prog_lock - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.passwd_en_prog_lock));
        return (D_Bool)CONFIG.user_param.passwd_en_prog_lock;
    }
#endif

    LOCK ();
    passwd_en = (D_Bool)CONFIG.user_param.passwd_en_prog_lock;
    UNLOCK ();

    return passwd_en;
}

/** @brief 设置节目锁密码是否使能*/
D_Result p_conf_set_prog_passwd_en (D_Bool en) D_FUNCPOSTFIT
{
    LOCK ();
    if(CONFIG.user_param.passwd_en_prog_lock != en)
    {
        CONFIG.user_param.passwd_en_prog_lock = en;
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.passwd_en_prog_lock - (D_U8*)&CONFIG,
                                   sizeof (CONFIG.user_param.passwd_en_prog_lock));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.passwd_en_prog_lock - (D_U8*)&CONFIG,
                         sizeof (CONFIG.user_param.passwd_en_prog_lock));
#endif
    }
    UNLOCK ();

    return D_OK;
}

/** @brief 获得密码长度*/
D_U8 p_conf_get_passwd_len (void) D_FUNCPOSTFIT
{
    LOCK ();
#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.passwd_len - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.passwd_len));
    }
#endif
    UNLOCK ();

    return (CONFIG.user_param.passwd_len);
}


/** @brief 获得密码*/
D_Result p_conf_get_passwd (D_Char *pass) D_FUNCPOSTFIT
{
    if (! pass)
        return D_ERR;

#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.passwd - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.passwd));
        memcpy(pass, CONFIG.user_param.passwd, sizeof(CONFIG.user_param.passwd));
        return D_OK;
    }
#endif

    LOCK ();
    memcpy(pass, CONFIG.user_param.passwd, sizeof(CONFIG.user_param.passwd));
    UNLOCK ();

    return D_OK;
}

/** @brief 设置密码*/
D_Result p_conf_set_passwd (D_Char *pass) D_FUNCPOSTFIT
{
    D_U8 len;

    LOCK ();

    memcpy(&CONFIG.user_param.passwd, pass, sizeof(CONFIG.user_param.passwd));
    len = D_MIN(CONFIG.user_param.passwd_len, D_CONF_PASSWORD_LEN);
    CONFIG.user_param.passwd[len] = (D_U8)( '\0');
#ifdef D_SUPPORT_EEPROM
    d_dbase_eeprom_store_data (&config_blk,
                               (D_U8*)&CONFIG.user_param.passwd - (D_U8*)&CONFIG,
                               sizeof (CONFIG.user_param.passwd));
#else
    conf_save_in_rec((D_U8*)&CONFIG.user_param.passwd - (D_U8*)&CONFIG,
                     sizeof (CONFIG.user_param.passwd));
#endif

    UNLOCK ();

    return D_OK;
}

/** @brief 密码比较*/
static D_U8 cmp_passwd (D_Char *pass, D_U8 len) D_FUNCPOSTFIT
{
    D_U8 ret = 0;

    if (pass)
    {
        if (! strncmp (pass, (D_Char*)(CONFIG.user_param.passwd), len))
        {
            ret = 1;
        }
        else if (! strncmp (pass, g_custom_config.password.super_pwd, len))
        {
            ret = 2;
        }
    }

    return ret;
}

/** @brief 检查密码设置
返回值:     0  密码错误
            1 密码正确，与设置的密码相同
            2 密码正确，与超级密码相同
*/
D_U8 p_conf_check_passwd (D_Char *pass) D_FUNCPOSTFIT
{
    D_U8    ret;

#ifdef D_SUPPORT_EEPROM
    /*为提高启动速度,在没有加载数据库时,可通过EEPROM直接访问数据*/
    if (! loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.passwd - (D_U8*)&config,
                                  sizeof (CONFIG.user_param.passwd));
        return cmp_passwd (pass, CONFIG.user_param.passwd_len);
    }
#endif

    LOCK ();
    ret = cmp_passwd (pass, CONFIG.user_param.passwd_len);
    UNLOCK ();

    return ret;
}


/** @brief 得到当前换台静帧黑屏模式,黑屏(0)静帧(1)
** @param
*/
D_U8 p_conf_get_channel_change_mode() D_FUNCPOSTFIT
{
    D_U8 mode;
    LOCK ();
#ifdef D_SUPPORT_EEPROM
    /*为提高启动速度,在没有加载数据库时,可通过EEPROM直接访问数据*/
    if (! loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.channel_change_mode - (D_U8*)&CONFIG, sizeof(CONFIG.user_param.channel_change_mode));
    }
#endif

    mode = (CONFIG.user_param.channel_change_mode);

    UNLOCK ();
    return mode;
}

/** @brief 设置当前换台静帧黑屏模式,黑屏(0)静帧(1)
** @param
*/
D_Result p_conf_set_channel_change_mode(D_U8 mode) D_FUNCPOSTFIT
{
    LOCK ();

    if(CONFIG.user_param.channel_change_mode != mode)
    {
        CONFIG.user_param.channel_change_mode = mode;
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.channel_change_mode - (D_U8*)&CONFIG, sizeof(CONFIG.user_param.channel_change_mode));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.channel_change_mode - (D_U8*)&CONFIG, sizeof(CONFIG.user_param.channel_change_mode));
#endif
    }
    UNLOCK ();

    return D_OK;
}

/** @brief 取得开机的次数*/
D_U32 p_conf_get_stb_startup_time(void) D_FUNCPOSTFIT
{
    LOCK ();
#ifdef D_SUPPORT_EEPROM
    /*为提高启动速度,在没有加载数据库时,可通过EEPROM直接访问数据*/
    if (! loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.stb_startup_time - (D_U8*)&CONFIG, sizeof(CONFIG.user_param.stb_startup_time));
    }
#endif
    UNLOCK ();

    return CONFIG.user_param.stb_startup_time;
}

/** @brief 开机的次数加1*/
D_Result    p_conf_add_stb_startup_time() D_FUNCPOSTFIT
{
    LOCK ();
    CONFIG.user_param.stb_startup_time += 1;
#ifdef D_SUPPORT_EEPROM
    d_dbase_eeprom_store_data (&config_blk,
                               (D_U8*)&CONFIG.user_param.stb_startup_time - (D_U8*)&CONFIG, sizeof(CONFIG.user_param.stb_startup_time));
#else
    conf_save_in_rec((D_U8*)&CONFIG.user_param.stb_startup_time - (D_U8*)&CONFIG, sizeof(CONFIG.user_param.stb_startup_time));
#endif
    UNLOCK ();

    return D_OK;
}

#ifdef D_USE_NETWORK
/** @brief 获得网络参数*/
D_Result p_conf_get_network_param(D_NetworkParam *net_param)
{
    if (! net_param)
        return D_ERR_INVALID_ARGUMENT;

#ifdef D_SUPPORT_EEPROM
    /*为提高启动速度,在没有加载数据库时,可通过EEPROM直接访问数据*/
    if (! loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.net_param - (D_U8*)&CONFIG,
                                  sizeof (D_NetworkParam));
        *net_param = CONFIG.net_param;
        return D_OK;
    }
#endif
    LOCK ();
    memcpy (net_param, &CONFIG.net_param, sizeof (D_NetworkParam));
    UNLOCK ();

    return D_OK;
}

/** @brief 设置网络参数*/
D_Result p_conf_set_network_param(D_NetworkParam *net_param)
{
    if (! net_param)
        return D_ERR_INVALID_ARGUMENT;

    LOCK ();
    memcpy (&CONFIG.net_param, net_param, sizeof (D_NetworkParam));
#ifdef D_SUPPORT_EEPROM
    d_dbase_eeprom_store_data (&config_blk,
                               (D_U8*)&CONFIG.net_param - (D_U8*)&CONFIG,
                               sizeof (D_NetworkParam));
#else
    conf_save_in_rec((D_U8*)&CONFIG.net_param - (D_U8*)&CONFIG,
                     sizeof (D_NetworkParam));
#endif
    UNLOCK ();

    return D_OK;
}
#endif

/** @brief 取得喜爱组名称
* @param[in] num 喜爱组编号，目前只支持8个喜爱组，编号为0~7
* @param[out] name 喜爱组名称字符串指针（必须为该指针分配了足够空间才能使用）
* @retval D_ERR 获取失败
* @retval D_OK  获取成功
*/
D_Result
p_conf_get_favor_name(D_U8 num, D_Char* name) D_FUNCPOSTFIT
{
    if((name == NULL) || (num > 7)) //目前只支持8个喜爱组，编号为0~7。
    {
        return D_ERR;
    }
#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.favor_name[num] - (D_U8*)&CONFIG,
                                  D_CONF_FAVOR_NAME_LEN);
        memcpy(name, &CONFIG.user_param.favor_name[num], D_CONF_FAVOR_NAME_LEN);
        return D_OK;
    }
#endif

    LOCK ();
    memcpy(name, &CONFIG.user_param.favor_name[num], D_CONF_FAVOR_NAME_LEN);
    UNLOCK ();

    return D_OK;
}

/** @brief 设置喜爱组名称
* @param[in] num 喜爱组编号，目前只支持8个喜爱组，编号为0~7
* @param[in] name 喜爱组名称字符串指针
* @retval D_ERR 设置失败
* @retval D_OK  设置成功
*/
D_Result
p_conf_set_favor_name(D_U8 num, D_Char* name) D_FUNCPOSTFIT
{
    if((name == NULL) || (num > 7)) //目前只支持8个喜爱组，编号为0~7。
    {
        return D_ERR;
    }

    LOCK ();
    memcpy(&CONFIG.user_param.favor_name[num], name, D_CONF_FAVOR_NAME_LEN);
#ifdef D_SUPPORT_EEPROM
    d_dbase_eeprom_store_data (&config_blk,
                               (D_U8*)&CONFIG.user_param.favor_name[num] - (D_U8*)&CONFIG,
                               D_CONF_FAVOR_NAME_LEN);
#else
    conf_save_in_rec((D_U8*)&CONFIG.user_param.favor_name[num] - (D_U8*)&CONFIG,
                     D_CONF_FAVOR_NAME_LEN);
#endif
    UNLOCK ();

    return D_OK;
}

/** @brief 取得当前CA*/
D_U32
p_conf_get_curr_ca(void) D_FUNCPOSTFIT
{
    D_U32 curr_ca;

#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.curr_ca - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.curr_ca));
        return CONFIG.user_param.curr_ca;
    }
#endif

    LOCK ();
    curr_ca = CONFIG.user_param.curr_ca;
    UNLOCK ();

    return curr_ca;
}

/** @brief 设置当前CA*/
D_Result
p_conf_set_curr_ca(D_U32 curr_ca) D_FUNCPOSTFIT
{
    LOCK ();
    if (CONFIG.user_param.curr_ca != curr_ca)
    {
        CONFIG.user_param.curr_ca = curr_ca;
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.curr_ca - (D_U8*)&CONFIG,
                                   sizeof (CONFIG.user_param.curr_ca));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.curr_ca - (D_U8*)&CONFIG,
                         sizeof (CONFIG.user_param.curr_ca));
#endif
    }
    UNLOCK ();

    return D_OK;
}

/** @brief 取得记录的服务ID*/
D_DBSrvID
p_conf_get_force_srv (void) D_FUNCPOSTFIT
{
    D_DBSrvID   srv;

#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.force_srv - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.force_srv));
        return CONFIG.user_param.force_srv;
    }
#endif

    LOCK ();
    srv = CONFIG.user_param.force_srv;
    UNLOCK ();

    return srv;
}

/** @brief 设置当前服务ID*/
D_Result
p_conf_set_force_srv (D_DBSrvID id) D_FUNCPOSTFIT
{
    LOCK ();
    if (CONFIG.user_param.force_srv != id)
    {
        CONFIG.user_param.force_srv = id;
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.force_srv - (D_U8*)&CONFIG,
                                   sizeof (CONFIG.user_param.force_srv));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.force_srv - (D_U8*)&CONFIG,
                         sizeof (CONFIG.user_param.force_srv));
#endif
    }
    UNLOCK ();

    return D_OK;
}

/** @brief 取得CA模块存储的相关信息
* @param[out] buf CA相关信息存放区指针（必须为该指针分配了足够空间才能使用）
* @retval D_ERR 获取失败
* @retval D_OK  获取成功
*/
D_Result
p_conf_get_ca_related_info(D_U8* buf) D_FUNCPOSTFIT
{
    if(buf == NULL)
    {
        return D_ERR;
    }
#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.ca_info - (D_U8*)&CONFIG,
                                  D_CONF_CA_INFO_LEN);
        memcpy(buf, &CONFIG.user_param.ca_info, D_CONF_CA_INFO_LEN);
        return D_OK;
    }
#endif

    LOCK ();
    memcpy(buf, &CONFIG.user_param.ca_info, D_CONF_CA_INFO_LEN);
    UNLOCK ();

    return D_OK;
}

/** @brief 设置CA模块存储的相关信息
* @param[out] buf CA相关信息存放区指针
* @retval D_ERR 设置失败
* @retval D_OK  设置成功
*/
D_Result
p_conf_set_ca_related_info(D_U8* buf) D_FUNCPOSTFIT
{
    if(buf == NULL)
    {
        return D_ERR;
    }

    LOCK ();
    memcpy(&CONFIG.user_param.ca_info, buf, D_CONF_CA_INFO_LEN);
#ifdef D_SUPPORT_EEPROM
    d_dbase_eeprom_store_data (&config_blk,
                               (D_U8*)&CONFIG.user_param.ca_info - (D_U8*)&CONFIG,
                               D_CONF_CA_INFO_LEN);
#else
    conf_save_in_rec((D_U8*)&CONFIG.user_param.ca_info - (D_U8*)&CONFIG,
                     D_CONF_CA_INFO_LEN);
#endif
    UNLOCK ();

    return D_OK;
}

/** @brief 取得搜索设置*/
D_U8
p_conf_get_scan_config (void) D_FUNCPOSTFIT
{

    D_U8    flag;

#ifdef D_SUPPORT_EEPROM
    /*为提高启动速度,在没有加载数据库时,可通过EEPROM直接访问数据*/
    if (! loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.si_param.epg_strategy - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.si_param.epg_strategy));
        return CONFIG.si_param.epg_strategy;//1-dvbc 0-dtmb
    }
#endif
    LOCK ();
    flag = CONFIG.si_param.epg_strategy;
    UNLOCK ();

    return flag;
}

/** @brief 设置搜索设置*/
D_Result
p_conf_set_scan_config (D_U8 cable_en) D_FUNCPOSTFIT
{
    LOCK ();
    if (CONFIG.si_param.epg_strategy != cable_en)
    {
        CONFIG.si_param.epg_strategy = cable_en;
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.si_param.epg_strategy - (D_U8*)&CONFIG,
                                   sizeof (CONFIG.si_param.epg_strategy));
#else
        conf_save_in_rec((D_U8*)&CONFIG.si_param.epg_strategy - (D_U8*)&CONFIG,
                         sizeof (CONFIG.si_param.epg_strategy));
#endif
    }
    UNLOCK ();

    return D_OK;
}

/** @brief 获得频率组序号*/
D_U8 p_conf_get_scan_list_num (void) D_FUNCPOSTFIT
{
    D_U8 num;

#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.cur_scanlist - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.cur_scanlist));
        return (D_Bool)CONFIG.user_param.cur_scanlist;
    }
#endif

    LOCK ();
    num = (D_Bool)CONFIG.user_param.cur_scanlist;
    UNLOCK ();

    return num;
}

/** @brief 设置频率组序号*/
D_Result p_conf_set_scan_list_num (D_U8 num) D_FUNCPOSTFIT
{
    LOCK ();
    if (CONFIG.user_param.cur_scanlist != num)
    {
        CONFIG.user_param.cur_scanlist = num;
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.cur_scanlist - (D_U8*)&CONFIG,
                                   sizeof (CONFIG.user_param.cur_scanlist));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.cur_scanlist - (D_U8*)&CONFIG,
                         sizeof (CONFIG.user_param.cur_scanlist));
#endif
    }
    UNLOCK ();

    return D_OK;
}

/** @brief 取得视频输入*/
D_VidInput
p_conf_get_vid_input (void) D_FUNCPOSTFIT
{
    D_VidInput input;

#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.vid_input - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.vid_input));
        return CONFIG.user_param.vid_input;
    }
#endif

    LOCK ();
    input = CONFIG.user_param.vid_input;
    UNLOCK ();

    return input;
}

/** @brief 设置视频输入*/
D_Result
p_conf_set_vid_input (D_VidInput input) D_FUNCPOSTFIT
{
    LOCK ();
    if (CONFIG.user_param.vid_input != input)
    {
        CONFIG.user_param.vid_input = input;
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.vid_input - (D_U8*)&CONFIG,
                                   sizeof (CONFIG.user_param.vid_input));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.vid_input - (D_U8*)&CONFIG,
                         sizeof (CONFIG.user_param.vid_input));
#endif
    }
    UNLOCK ();

    return D_OK;
}
/** @brief 取得音量设置*/
D_U8
p_conf_get_balance (void) D_FUNCPOSTFIT
{
    D_U8    val;

#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.balance - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.balance));
        return CONFIG.user_param.balance;
    }
#endif

    LOCK ();
    val = CONFIG.user_param.balance;
    UNLOCK ();

    return val;
}

/** @brief 设置声道设置*/
D_Result
p_conf_set_balance (D_U8 val) D_FUNCPOSTFIT
{
    LOCK ();
    if (CONFIG.user_param.balance != val)
    {
        CONFIG.user_param.balance = val;
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.balance - (D_U8*)&CONFIG,
                                   sizeof (CONFIG.user_param.balance));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.balance - (D_U8*)&CONFIG,
                         sizeof (CONFIG.user_param.balance));
#endif
    }
    UNLOCK ();

    return D_OK;
}
D_U8
p_conf_get_save_type() D_FUNCPOSTFIT
{
    D_U8    scan_save_type;

#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.save_type - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.save_type));
        return CONFIG.user_param.save_type;
    }
#endif

    LOCK ();
    scan_save_type = CONFIG.user_param.save_type;
    UNLOCK ();

    return scan_save_type;
}

D_U8
p_conf_set_save_type(D_U8 scan_save_type) D_FUNCPOSTFIT
{
    LOCK ();
    if (CONFIG.user_param.save_type != scan_save_type)
    {
        CONFIG.user_param.save_type = scan_save_type;
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.save_type - (D_U8*)&CONFIG,
                                   sizeof (CONFIG.user_param.save_type));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.save_type - (D_U8*)&CONFIG,
                         sizeof (CONFIG.user_param.save_type));
#endif
    }
    UNLOCK ();

    return D_OK;
}


D_U8
p_conf_get_ad_version() D_FUNCPOSTFIT
{
    D_U8    ad_version;

#ifdef D_SUPPORT_EEPROM
    if (!loaded)
    {
        d_dbase_eeprom_read_data (&config_blk,
                                  (D_U8*)&CONFIG.user_param.ad_version - (D_U8*)&CONFIG,
                                  sizeof (CONFIG.user_param.ad_version));
        return CONFIG.user_param.ad_version;
    }
#endif

    LOCK ();
    ad_version = CONFIG.user_param.ad_version;
    UNLOCK ();

    return ad_version;
}

D_U8
p_conf_set_ad_version( D_S8 ad_version  ) D_FUNCPOSTFIT
{
    LOCK ();
    if (CONFIG.user_param.ad_version != ad_version)
    {
        CONFIG.user_param.ad_version = ad_version;
#ifdef D_SUPPORT_EEPROM
        d_dbase_eeprom_store_data (&config_blk,
                                   (D_U8*)&CONFIG.user_param.ad_version - (D_U8*)&CONFIG,
                                   sizeof (CONFIG.user_param.ad_version));
#else
        conf_save_in_rec((D_U8*)&CONFIG.user_param.ad_version - (D_U8*)&CONFIG,
                         sizeof (CONFIG.user_param.ad_version));
#endif
    }
    UNLOCK ();

    return D_OK;
}
/** @brief 取得Loader参数设置*/
D_Result p_conf_get_panel_param (D_PanelParam *panel_param) D_FUNCPOSTFIT
{
    D_HEEPRom he2p;

    if (! panel_param)
        return D_ERR_INVALID_ARGUMENT;

    he2p = d_eeprom_create(NULL);

    d_eeprom_read(he2p, PANEL_PARAM_OFFSET_IN_EEPROM, (D_U8*)panel_param, sizeof(D_PanelParam));

    d_eeprom_destroy(he2p);

    return D_OK;
}

/** @brief 设置Loader参数设置*/
D_Result p_conf_set_panel_param (D_PanelParam *panel_param) D_FUNCPOSTFIT
{
    D_HEEPRom he2p;

    if (! panel_param)
        return D_ERR_INVALID_ARGUMENT;

    he2p = d_eeprom_create(NULL);

    panel_param->crc = d_crc_compute_32((D_U8*)panel_param, (D_U8*)&panel_param->crc - (D_U8*)panel_param);

    d_eeprom_write(he2p, PANEL_PARAM_OFFSET_IN_EEPROM, (D_U8*)panel_param, sizeof(D_PanelParam));

    d_eeprom_destroy(he2p);

    return D_OK;
}

/**@}*/
