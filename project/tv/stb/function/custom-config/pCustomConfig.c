/** @file
* @brief 用户配置数据加载
* @author 李臣
* @date 2013-07-25 李臣: 建立文件
*/
#include "dTypes.h"
#include "dDebug.h"
#include "dNVRam.h"
#include "dCrc.h"
#include "dEEPRom.h"
#include "dConfigFile.h"
#include "dAppImageHeader.h"
#include "pCustomConfig.h"
#include "pMem.h"
#include "pConfig.h"
#include "pStb.h"

#include <string.h>

#include "DefaultCustomConfig.h"

#if defined(P_BOARD_HIC_2610D_DTMB_DVBC)
#include "P_BOARD_HIC_2610D_DTMB_DVBC_bin.c"
#elif defined(P_BOARD_HIC_2610E_DTMB_DVBC)
#include "P_BOARD_HIC_2610E_DTMB_DVBC_bin.c"
#else
/* 其它板型暂无配置文件 */
#include "P_BOARD_HIC_2610D_DTMB_DVBC_bin.c"
#endif

#if defined(P_BOARD_HIC_2610D_DTMB_DVBC)
#include "DEFAULT_SW_bin.c"
#elif defined(P_BOARD_HIC_2610E_DTMB_DVBC)
#include "DEFAULT_SW_bin.c"
#else
#include "DEFAULT_SW_bin.c"
#endif

#define CUSTOM_CONFIG_BIN_SIZE_OFFSET   2  /* 起始有两个字节的版本号, 目前没有使用 */
#define CUSTOM_CONFIG_BIN_SUBFIX_LEN    4  /* 总长度需要4个字节的补偿, (版本号+长度) */

static D_U32 app_in_flash_offset = D_APP_PART_DEFAULT_OFFSET;

static D_S32 custom_config_load_eeprom(D_U8 *temp_buf) D_FUNCPOSTFIT
{
    return 0;
}

static void custom_config_check_eeprom(D_U8 *temp_buf, D_S32 total_size) D_FUNCPOSTFIT
{
}

static void* p_custom_config_load_ex(D_U32 block_in_flash_offset, D_U32 block_size, D_Bool check_eeprom, D_U16 *rsize) D_FUNCPOSTFIT
{
    D_HNVRam hnv;
    D_U8 *temp_buf;
    void *p = NULL;

    *rsize = 0;

    temp_buf = (D_U8*)PROJECT_ALLOC(block_size);
    if(temp_buf == NULL)
    {
        D_ERROR("Can not alloc mem for custom config!\n");
        return NULL;
    }

    hnv = d_nvram_create(NULL);

    do
    {
        D_S32 total_size;

        if(d_nvram_read(hnv, block_in_flash_offset, temp_buf, block_size) != block_size)
        {
            D_ERROR("Can not read flash block 0x[%08X] for custrom config!\n", block_in_flash_offset);
            break;
        }

        total_size = d_make_u16(temp_buf[CUSTOM_CONFIG_BIN_SIZE_OFFSET], temp_buf[CUSTOM_CONFIG_BIN_SIZE_OFFSET + 1]);
        total_size += CUSTOM_CONFIG_BIN_SUBFIX_LEN;
        if((total_size > (block_size - CUSTOM_CONFIG_BIN_SUBFIX_LEN)) \
            || (total_size < 9 + CUSTOM_CONFIG_BIN_SIZE_OFFSET) \
            || d_crc_compute_32(temp_buf, total_size))
        {
            D_ERROR("No valid custom config found in flash[%08X]", block_in_flash_offset);
            if(check_eeprom)
            {
                D_ERROR(", try EEPRom.\n");
                total_size = custom_config_load_eeprom(temp_buf);
                if(total_size)
                {
                }
                else
                {
                    PROJECT_FREE(temp_buf);
                    /* flash和e2p里都没有可用的配置数据 */
                    D_ERROR("No valid custom config found in flash and EEPRom, restore default.\n");
                    break;
                }
            }
            else
            {
                PROJECT_FREE(temp_buf);
                D_ERROR(".\n");
                break;
            }
        }
        else if(check_eeprom)
        {
            custom_config_check_eeprom(temp_buf, total_size);
        }

        total_size -= CUSTOM_CONFIG_BIN_SUBFIX_LEN + 4; /* 去掉补偿和尾部的crc */

        p = &temp_buf[CUSTOM_CONFIG_BIN_SIZE_OFFSET + 2];
        *rsize = total_size;

        /* 从硬件配置中寻找app分区头部位置 */
        {
            D_U8 *pp = p;
            D_U8 tag;
            D_U16 payload_len;
            
            while(total_size > 0)
            {
                tag = *pp ++;
                payload_len = d_make_u16(pp[0], pp[1]);
                pp += 2;

                if(payload_len + 3 > total_size)
                {
                    D_ERROR("Unexpect payload length '%d' found in custom config!\n", payload_len);
                    break;
                }

                if((tag == CUSTOM_CONFIG_TAG_APP_OFFSET) && (payload_len >= 4))
                {
                    app_in_flash_offset = ((D_U32)pp[0] << 24) | ((D_U32)pp[1] << 16) | ((D_U32)pp[2] << 8) | pp[3];

                    D_DUMP("Found app offset [%08X]\n", app_in_flash_offset);
                }

                pp += payload_len;
                total_size -= payload_len + 3;
            }
        }
    }while(0);

    d_nvram_destroy(hnv);
    
    return p;
}


/** @brief 取得用户软件配置数据
* @param 无
* @return 无
*/
static void custom_config_parse_sw_tags(void) D_FUNCPOSTFIT
{
    D_U8 *payload;
    D_U16 len;

    /* 厂家id, 硬件版本号 */
    payload = d_conf_file_search_tag(CUSTOM_CONFIG_TAG_SYS, &len);
    if(payload && (len >=8))
    {
        g_custom_config.sys.manu_id = ((D_U32)payload[0] << 24) | ((D_U32)payload[1] << 16) | ((D_U32)payload[2] << 8) | payload[3];
        g_custom_config.sys.hw_id = payload[4];
        g_custom_config.sys.hw_major = payload[5];
        g_custom_config.sys.hw_minor = ((D_U16)payload[6] << 8) | payload[7];
    }

    /*主频点配置*/
    payload = (D_U8*)d_conf_file_search_tag(CUSTOM_CONFIG_TAG_DVBC_MAIN, &len);
    if(payload && len >= 6)
    {
        g_custom_config.dvbc_main.freq = ((D_U32)payload[0] << 16) | ((D_U32)payload[1] << 8) | payload[2];
        g_custom_config.dvbc_main.baud = d_make_u16(payload[3], payload[4]);
        g_custom_config.dvbc_main.mod = (D_FEndMod)payload[5];
    }

    /*系统默认配置*/
    payload = (D_U8*)d_conf_file_search_tag(CUSTOM_CONFIG_TAG_SYS_DEFAULT, &len);
    if(payload && len >= 0x45)
    {    
        g_custom_config.sys_setup.change_mode = payload[0] >> 7;
        g_custom_config.sys_setup.def_language = (payload[0] >> 3) & 0x0F; 
        g_custom_config.sys_setup.track = (payload[0] >> 1) & 0x03; 
        g_custom_config.sys_setup.smart_voice = (payload[0]) & 0x01;           
        g_custom_config.sys_setup.def_voice = D_MIN(payload[1], D_STB_VOLUME_MAX);       
        g_custom_config.sys_setup.vol_compensate = (payload[2]) ? 1 : 0;       
        
        memcpy(g_custom_config.sys.manuf_name, &payload[3], D_CUSTOM_CONF_MANUF_NAME_LEN);  
        g_custom_config.sys.manuf_name[D_CUSTOM_CONF_MANUF_NAME_LEN] = '\0';     
        
        g_custom_config.dvbc_main.network_id = d_make_u16(payload[35], payload[36]);
        memcpy(g_custom_config.dvbc_main.network_name, &payload[37], D_CUSTOM_CONF_NETWORK_NAME_LEN);  
        g_custom_config.dvbc_main.network_name[D_CUSTOM_CONF_NETWORK_NAME_LEN] = '\0';

        g_custom_config.dvbc_main.software_version = ((D_U32)payload[69] << 24) | ((D_U32)payload[70] << 16) | ((D_U32)payload[71] << 8) | payload[72];
        g_custom_config.sys_setup.chan_save = (len >= 74 ? ((payload[73] >> 4) & 0x0F):0);       
    }

    /*开机SI检查配置*/
    payload = (D_U8*)d_conf_file_search_tag(CUSTOM_CONFIG_TAG_SI_POWER_ON, &len);
    if(payload && len >= 9)
    {    
        g_custom_config.si_mon.power_on.enable = payload[0] >> 7;        
        g_custom_config.si_mon.power_on.flag = 0;
        if((payload[0] >> 6) & 0x01)
        {
            g_custom_config.si_mon.power_on.flag |= P_SIMON_NIT_EN; 
        }
        if((payload[0] >> 5) & 0x01)
        {
            g_custom_config.si_mon.power_on.flag |= P_SIMON_NIT_NETWORK_ID; 
        }        
        if((payload[0] >> 4) & 0x01)
        {
            g_custom_config.si_mon.power_on.flag |= P_SIMON_NIT_NETWORK_NAME; 
        }         
        if((payload[0] >> 3) & 0x01)
        {
            g_custom_config.si_mon.power_on.flag |= P_SIMON_UMT_EN; 
        } 
        g_custom_config.si_mon.power_on.use_main = (payload[0] >> 2) & 0x01; 
        g_custom_config.si_mon.power_on.freq = ((D_U32)payload[1] << 16) | ((D_U32)payload[2] << 8) | payload[3]; 
        g_custom_config.si_mon.power_on.baud = d_make_u16(payload[4], payload[5]); 
        g_custom_config.si_mon.power_on.mod = (D_FEndMod)payload[6]; 
        g_custom_config.si_mon.power_on.timeout = (D_U32)d_make_u16(payload[7], payload[8]);        
    }
    
    /*SI表监控配置*/
    payload = (D_U8*)d_conf_file_search_tag(CUSTOM_CONFIG_TAG_SI_MON, &len);
    if(payload && len >= 2)
    {
        g_custom_config.si_mon.flag = ((D_U32)payload[0] << 24) | ((D_U32)payload[1] << 16) | ((D_U32)payload[2] << 8) | payload[3];
    }

    /*节目搜索相关配置*/
    payload = (D_U8*)d_conf_file_search_tag(CUSTOM_CONFIG_CHANNEL_SCAN, &len);
    if(payload && len >= 10)
    {
        g_custom_config.scan.use_lcn = (payload[0] >> 7) & 0x01;
        g_custom_config.scan.caflag = (payload[0] >> 4) & 0x07;
        g_custom_config.scan.adelete = (payload[1] >> 4) & 0x0F;
        g_custom_config.scan.asort = (payload[1]) & 0x0F;
        g_custom_config.scan.mdelete = (payload[2] >> 4) & 0x0F;
        g_custom_config.scan.msort = (payload[2]) & 0x0F;
        
        g_custom_config.scan.full_mode = (payload[3] >> 4) & 0x0F;
        g_custom_config.scan.start_freq = ((D_U32)(payload[3] & 0x0F) << 16) | ((D_U32)payload[4] << 8) | payload[5];    
        g_custom_config.scan.end_freq = ((D_U32)payload[6] << 16) | ((D_U32)payload[7] << 8) | payload[8];     
        g_custom_config.scan.band = (payload[9] == 0) ? 8: payload[9];
        g_custom_config.scan.multi_maintp =(len>=11?((payload[10] >> 7) & 0x01):0);
		g_custom_config.scan.exit_to_save = (len>=12 ? ((payload[11]>>7)&0x01):0);
    }

    /*密码相关配置*/
    payload = (D_U8*)d_conf_file_search_tag(CUSTOM_CONFIG_PASSWORD, &len);
    if(payload && len >= 13)
    {
        len = payload[0] & 0x07;
        if(len && (len <= D_CUSTOM_CONF_PASSWORD_LEN))
        {
            g_custom_config.password.pwd_len = len;
            g_custom_config.password.power_on = (payload[0] >> 7) & 0x01;
            g_custom_config.password.stbmenu = (payload[0] >> 6) & 0x01;
            g_custom_config.password.prog_lock = (payload[0] >> 5) & 0x01;
            memcpy(g_custom_config.password.def_pwd, &payload[1], len);
            g_custom_config.password.def_pwd[len] = '\0';
            memcpy(g_custom_config.password.super_pwd, &payload[7], len);
            g_custom_config.password.super_pwd[len] = '\0';
        }
    }

    /*开机无节目操作配置*/
    payload = (D_U8*)d_conf_file_search_tag(CUSTOM_CONFIG_MACHINE_START, &len);
    if(payload && len >= 1)
    {
        g_custom_config.power_on.scan_enable = payload[0] >> 7;
        g_custom_config.power_on.scan_mode = (payload[0] >> 3) & 0x0F;        
    }
    /*播放缓冲区长度选择设置*/
    payload = (D_U8*)d_conf_file_search_tag(CUSTOM_CONFIG_DECODE_SWITCH, &len);
    if(payload && len >= 1)
    {
        g_custom_config.decode_switch.decodetype = payload[0] >> 6;
    }

    /*等同步方式选择配置*/
    payload = (D_U8*)d_conf_file_search_tag(CUSTOM_CONFIG_SWITCHPLAY, &len);
    if(payload && len >= 1)
    {
        g_custom_config.switch_play.wait_sync_type = payload[0] >> 6;
    }
    /*节目更新处理方式选择配置*/
    payload = (D_U8*)d_conf_file_search_tag(CUSTOM_CONFIG_CHANUPDATE_MODE, &len);
    if(payload && len >= 1)
    {
        g_custom_config.chan_update.scan_enable = payload[0] >> 7;
        g_custom_config.chan_update.deal_mode = (payload[0] >> 3) & 0x0F;        
        g_custom_config.chan_update.scan_mode = (payload[0]) & 0x07;        
    }
    /*节目变化处理方式选择配置*/
    payload = (D_U8*)d_conf_file_search_tag(CUSTOM_CONFIG_CHANCHAGE_MODE, &len);
    if(payload && len >= 1)
    {
        g_custom_config.chan_change.scan_enable = payload[0] >> 7;
        g_custom_config.chan_change.deal_mode = (payload[0] >> 3) & 0x0F;        
    }

    /* epg搜索配置*/
    g_custom_config.epg.scan_mode = 0;    
    payload = (D_U8*)d_conf_file_search_tag(CUSTOM_CONFIG_TAG_EPG_SCAN_CONFIG, &len);
    if(payload && len >= 8)
    {
        g_custom_config.epg.scan_mode = (D_U32)payload[0];
        g_custom_config.epg.freq = ((D_U32)payload[1] << 16) | ((D_U32)payload[2] << 8) | payload[3];  
        g_custom_config.epg.baud= d_make_u16(payload[4], payload[5]);
        g_custom_config.epg.mod = (D_FEndMod)payload[6];
        g_custom_config.epg.timeout = ((D_U32)payload[7]) * 1000; 
    }

    /*相关配置处理*/
    g_custom_config.scan.volume = g_custom_config.sys_setup.def_voice;
    g_custom_config.scan.track = g_custom_config.sys_setup.track;  

    if(g_custom_config.scan.caflag != 2 && g_custom_config.scan.caflag != 3)
    {
        g_custom_config.si_mon.flag &= (~P_SIMON_SDT_CA_FREEMODE_EN);
    }
}

/** @brief 加载用户配置数据
* @param 无
* @return 无
*/
void p_custom_config_load(void) D_FUNCPOSTFIT
{
    D_ConfigFileOpenParam OpenParam;
    D_U8 *p1, *p2 = NULL;

    p1 = (D_U8*)p_custom_config_load_ex(0x2000 + 512, 0x1000 - 512, D_FALSE, &OpenParam.hw_data_size);
    p2 = (D_U8*)p_custom_config_load_ex((D_U32)((D_AppImageHeader*)app_in_flash_offset)->ih_reserved, IH_RESERVED_LEN, D_FALSE, &OpenParam.sw_data_size);

#ifndef D_BOARD_CONFIG_USE_LOCAL
    if(p1)
    {
        OpenParam.hw_data = p1;
    }
    else
#endif
    {
        OpenParam.hw_data = (D_U8*)(&DEFAULT_HW_BIN[CUSTOM_CONFIG_BIN_SIZE_OFFSET + 2]);
        OpenParam.hw_data_size = sizeof(DEFAULT_HW_BIN) - (CUSTOM_CONFIG_BIN_SUBFIX_LEN + 4);
    }

#ifndef D_BOARD_CONFIG_USE_LOCAL
    if(p2)
    {
        OpenParam.sw_data = p2;
    }
    else
#endif
    {
        OpenParam.sw_data = (D_U8*)(&DEFAULT_SW_BIN[CUSTOM_CONFIG_BIN_SIZE_OFFSET + 2]);
        OpenParam.sw_data_size = sizeof(DEFAULT_SW_BIN) - (CUSTOM_CONFIG_BIN_SUBFIX_LEN + 4);
    }
    
    if(d_conf_file_open(&OpenParam) != D_OK)
        D_ERROR("Config file open failed!\n");

    if(p1)
        PROJECT_FREE(p1 - (CUSTOM_CONFIG_BIN_SIZE_OFFSET + 2));
    if(p2)
        PROJECT_FREE(p2 - (CUSTOM_CONFIG_BIN_SIZE_OFFSET + 2));

    /*分析用户软件配置*/
    custom_config_parse_sw_tags();
}

/** @brief 打印用户配置数据
* @param 无
* @return 无
*/
void p_custom_config_dump(void) D_FUNCPOSTFIT
{
    D_DUMP("MANU: %08X\tHW: %02X%02X%04X\n", 
        g_custom_config.sys.manu_id, g_custom_config.sys.hw_id, g_custom_config.sys.hw_major, g_custom_config.sys.hw_minor);

    D_DUMP("\tDVBC main:\tFreq\t%d\n", g_custom_config.dvbc_main.freq);
    D_DUMP("\t\tBaud\t%d\n", g_custom_config.dvbc_main.baud);
    D_DUMP("\t\tMod\t%d\n", g_custom_config.dvbc_main.mod);
    D_DUMP("\t\tNetwork_id\t0x%04x\n", g_custom_config.dvbc_main.network_id);
    D_DUMP("\t\tNetwork_name\t%s\n\n", g_custom_config.dvbc_main.network_name);

    D_DUMP("\tSys default:\tchange mode\t%d\n", g_custom_config.sys_setup.change_mode);
    D_DUMP("\t\tdefault language\t%d\n", g_custom_config.sys_setup.def_language);
    D_DUMP("\t\ttrack\t%d\n", g_custom_config.sys_setup.track);
    D_DUMP("\t\tvoice\t%d\n", g_custom_config.sys_setup.def_voice);
    D_DUMP("\t\tsmart_voice\t0x%02x\n", g_custom_config.sys_setup.smart_voice);
    D_DUMP("\t\tvol_compensate\t0x%02x\n\n", g_custom_config.sys_setup.vol_compensate);

    D_DUMP("\tPower on Si:\tenable\t%02X\n", g_custom_config.si_mon.power_on.enable);
    D_DUMP("\t\tFlag\t%08X\n", g_custom_config.si_mon.power_on.flag); 
    D_DUMP("\t\tTimeout\t%d\n", g_custom_config.si_mon.power_on.timeout);        
    D_DUMP("\t\tUse_main\t%02X\n", g_custom_config.si_mon.power_on.use_main);    
    D_DUMP("\t\tFreq\t%d\n", g_custom_config.si_mon.power_on.freq);
    D_DUMP("\t\tBaud\t%d\n", g_custom_config.si_mon.power_on.baud);
    D_DUMP("\t\tMod\t%d\n\n", g_custom_config.si_mon.power_on.mod);    
    
    D_DUMP("\tSi mon:\tFlag\t%08X\n\n", g_custom_config.si_mon.flag);

    D_DUMP("\tUpgrade:\tNone\n\n");

    D_DUMP("\tChannel Scan:\n");
    D_DUMP("\t\tvolume\t%d\n", g_custom_config.scan.volume);
    D_DUMP("\t\ttrack\t%d\n", g_custom_config.scan.track);
    D_DUMP("\t\tuse_lcn\t%d\n", g_custom_config.scan.use_lcn);
    D_DUMP("\t\tcaflag\t%d\n", g_custom_config.scan.caflag);    
    D_DUMP("\t\tadelete\t%d\n", g_custom_config.scan.adelete);
    D_DUMP("\t\tasort\t%d\n", g_custom_config.scan.asort);
    D_DUMP("\t\tmdelete\t%d\n", g_custom_config.scan.mdelete);
    D_DUMP("\t\tmsort\t%d\n", g_custom_config.scan.msort);
    D_DUMP("\t\tStart Freq\t%d\n", g_custom_config.scan.start_freq);
    D_DUMP("\t\tStart Freq\t%d\n", g_custom_config.scan.end_freq);
    D_DUMP("\t\tBW\t%d\n\n", g_custom_config.scan.band);    

    D_DUMP("\tPassword Conf:\n");
    D_DUMP("\t\tpower_on\t%d\n", g_custom_config.password.power_on);
    D_DUMP("\t\tstbmenu\t%d\n", g_custom_config.password.stbmenu);
    D_DUMP("\t\tprog_lock\t%d\n", g_custom_config.password.prog_lock);
    D_DUMP("\t\tpwd_len\t%d\n", g_custom_config.password.pwd_len);
    D_DUMP("\t\tdef_pwd\t%s\n", g_custom_config.password.def_pwd);
    D_DUMP("\t\tsuper_pwd\t%s\n\n", g_custom_config.password.super_pwd);

    D_DUMP("\tPower On Scan enable:\t%02X\n", g_custom_config.power_on.scan_enable);
    D_DUMP("\tPower On Scan Mode:\t%02X\n\n", g_custom_config.power_on.scan_mode);    
}

/** @brief 获得app镜像在flash中偏移地址
* @param 无
* @return app镜像在flash中偏移地址
*/
D_U32 p_custom_config_get_app_offset(void) D_FUNCPOSTFIT
{
    return app_in_flash_offset;
}
